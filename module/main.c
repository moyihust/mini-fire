#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include "rule_filter.h"
#include "driver.h" // 包含 driver.h
#include "stateful_check.h" // 包含 stateful_check.h
#include "nat.h" // 包含 nat.h

static struct nf_hook_ops nat_hook = {
    .hook = nat_apply,
    .pf = PF_INET,
    .hooknum = NF_INET_POST_ROUTING,
    .priority = NF_IP_PRI_FIRST,
};

static int __init firewall_init(void) {
    printk(KERN_INFO "Loading firewall module\n");

    // 注册字符设备
    if (register_firewall_device() < 0) {
        printk(KERN_ALERT "Failed to register firewall device\n");
        return -1;
    }

    if (rule_filter_load_rules() != 0) {
        printk(KERN_ALERT "Failed to load rules\n");
        unregister_firewall_device(); // 注销字符设备
        return -1;
    }

    // 设置钩子函数
    firewall_in_hook.hook = rule_filter_apply_inbound;
    firewall_out_hook.hook = rule_filter_apply_outbound;

    // 注册入站钩子
    if (nf_register_net_hook(&init_net, &firewall_in_hook) < 0) {
        printk(KERN_ALERT "Failed to register inbound firewall hook\n");
        unregister_firewall_device(); // 注销字符设备
        return -1;
    }

    // 注册出站钩子
    if (nf_register_net_hook(&init_net, &firewall_out_hook) < 0) {
        printk(KERN_ALERT "Failed to register outbound firewall hook\n");
        nf_unregister_net_hook(&init_net, &firewall_in_hook); // 注销已注册的入站钩子
        unregister_firewall_device(); // 注销字符设备
        return -1;
    }

    // 初始化状态检测功能
    if (stateful_firewall_init() != 0) {
        printk(KERN_ALERT "Failed to initialize stateful firewall\n");
        nf_unregister_net_hook(&init_net, &firewall_in_hook); // 注销入站钩子
        nf_unregister_net_hook(&init_net, &firewall_out_hook); // 注销出站钩子
        unregister_firewall_device(); // 注销字符设备
        return -1;
    }

    // 注册NAT钩子
    if (nf_register_net_hook(&init_net, &nat_hook) < 0) {
        printk(KERN_ALERT "Failed to register NAT hook\n");
        nf_unregister_net_hook(&init_net, &firewall_in_hook); // 注销入站钩子
        nf_unregister_net_hook(&init_net, &firewall_out_hook); // 注销出站钩子
        stateful_firewall_exit(); // 清理状态检测功能
        unregister_firewall_device(); // 注销字符设备
        return -1;
    }

    // 加载NAT规则
    if (nat_load_rules(get_nat_rule_file_path()) != 0) {
        printk(KERN_ALERT "Failed to load NAT rules\n");
        nf_unregister_net_hook(&init_net, &firewall_in_hook); // 注销入站钩子
        nf_unregister_net_hook(&init_net, &firewall_out_hook); // 注销出站钩子
        nf_unregister_net_hook(&init_net, &nat_hook); // 注销NAT钩子
        stateful_firewall_exit(); // 清理状态检测功能
        unregister_firewall_device(); // 注销字符设备
        return -1;
    }

    filter_status = 1; // 开启过滤器
    return 0;
}

static void __exit firewall_exit(void) {
    struct firewall_rule *rule, *tmp;
    list_for_each_entry_safe(rule, tmp, &rule_list, list) {
        list_del(&rule->list);
        kfree(rule);
    }

    // 注销钩子
    nf_unregister_net_hook(&init_net, &firewall_in_hook);
    nf_unregister_net_hook(&init_net, &firewall_out_hook);
    nf_unregister_net_hook(&init_net, &nat_hook);
    filter_status = 0; // 关闭过滤器

    // 清理状态检测功能
    stateful_firewall_exit();

    // 注销字符设备
    unregister_firewall_device();

    // 清理NAT规则
    while (!list_empty(&nat_rule_list)) {
        nat_rule_t *rule = list_first_entry(&nat_rule_list, nat_rule_t, list);
        list_del(&rule->list);
        kfree(rule);
    }

    printk(KERN_INFO "Unloading firewall module\n");
}

module_init(firewall_init);
module_exit(firewall_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Firewall Module with NAT support");