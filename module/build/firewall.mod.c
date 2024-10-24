#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x2b4dfa79, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x47283f92, "kernel_write" },
	{ 0xbb49aaf1, "kmalloc_caches" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x349cba85, "strchr" },
	{ 0x754d539c, "strlen" },
	{ 0x1b6314fd, "in_aton" },
	{ 0xfff5afc, "time64_to_tm" },
	{ 0x41273767, "device_destroy" },
	{ 0xb302ead0, "__register_chrdev" },
	{ 0x4176d998, "filp_close" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x85df9b6c, "strsep" },
	{ 0x15ba50a6, "jiffies" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x25327573, "kernel_read" },
	{ 0x9ec6ca96, "ktime_get_real_ts64" },
	{ 0x58b96629, "class_unregister" },
	{ 0x1b2f621, "device_create" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0x8c8569cb, "kstrtoint" },
	{ 0x44be1682, "init_net" },
	{ 0x1a3ea70, "nf_register_net_hook" },
	{ 0xe34d55b0, "nf_unregister_net_hook" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0xac5fcec0, "in4_pton" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0xa3859b3a, "kmem_cache_alloc_trace" },
	{ 0x82ee90dc, "timer_delete_sync" },
	{ 0x37a0cba, "kfree" },
	{ 0x3b6c41ea, "kstrtouint" },
	{ 0x69acdf38, "memcpy" },
	{ 0xdd7d16aa, "class_destroy" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x1683011b, "__class_create" },
	{ 0xaa0c318b, "vscnprintf" },
	{ 0xd6729abe, "filp_open" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "48A29A3CF283F944B8C773C");
