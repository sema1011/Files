#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xe22d2560, "module_layout" },
	{ 0xcc62e93f, "register_netdevice" },
	{ 0x9a1dfd65, "strpbrk" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xf9a482f9, "msleep" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x349cba85, "strchr" },
	{ 0xd0d8621b, "strlen" },
	{ 0xc7ec6c27, "strspn" },
	{ 0xec5ade25, "dev_set_drvdata" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x3a013b7d, "remove_wait_queue" },
	{ 0x47939e0d, "__tasklet_hi_schedule" },
	{ 0xc8056c24, "netif_carrier_on" },
	{ 0xa4eb4eff, "_raw_spin_lock_bh" },
	{ 0x4b2569db, "skb_clone" },
	{ 0xf48caeeb, "dev_get_by_name" },
	{ 0x2addc0be, "down_interruptible" },
	{ 0x7525c0ac, "netif_carrier_off" },
	{ 0x3ded7885, "usb_kill_urb" },
	{ 0x26d78de7, "filp_close" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0x85df9b6c, "strsep" },
	{ 0x999e8297, "vfree" },
	{ 0x91715312, "sprintf" },
	{ 0xb52283f9, "kthread_create_on_node" },
	{ 0x7d11c268, "jiffies" },
	{ 0xea068623, "skb_trim" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x5c63747b, "netif_rx" },
	{ 0x48eb0c0d, "__init_waitqueue_head" },
	{ 0xffd5a395, "default_wake_function" },
	{ 0x72aa82c6, "param_ops_charp" },
	{ 0xd5f2172f, "del_timer_sync" },
	{ 0x36faf5f1, "dev_alloc_skb" },
	{ 0x11089ac7, "_ctype" },
	{ 0xf97456ea, "_raw_spin_unlock_irqrestore" },
	{ 0x43d17f5f, "current_task" },
	{ 0xefef6a4e, "usb_deregister" },
	{ 0x50eedeb8, "printk" },
	{ 0x42224298, "sscanf" },
	{ 0xa5e908f9, "kthread_stop" },
	{ 0x4141f80, "__tracepoint_module_get" },
	{ 0x5152e605, "memcmp" },
	{ 0x1fc85bad, "free_netdev" },
	{ 0x2da418b5, "copy_to_user" },
	{ 0xb6ed1e53, "strncpy" },
	{ 0x420ca98d, "register_netdev" },
	{ 0x5e47b1bb, "wireless_send_event" },
	{ 0x56f56a62, "usb_control_msg" },
	{ 0x6c2e3320, "strncmp" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x862c8d72, "skb_push" },
	{ 0x60c82dc0, "dev_close" },
	{ 0x9545af6d, "tasklet_init" },
	{ 0x8834396c, "mod_timer" },
	{ 0xbe2c0274, "add_timer" },
	{ 0xb8f76fee, "kill_pid" },
	{ 0x2c47988c, "skb_pull" },
	{ 0x9fe6e9d0, "usb_free_coherent" },
	{ 0x56e0b79a, "dev_kfree_skb_any" },
	{ 0x61651be, "strcat" },
	{ 0x82072614, "tasklet_kill" },
	{ 0x25f4f3b9, "module_put" },
	{ 0xad7acb3a, "skb_copy_expand" },
	{ 0x5564f7e7, "netif_device_attach" },
	{ 0xc16f0e0a, "usb_submit_urb" },
	{ 0x42e657d4, "netif_device_detach" },
	{ 0xb80f93c5, "__alloc_skb" },
	{ 0x616e0ffc, "usb_get_dev" },
	{ 0x8bf826c, "_raw_spin_unlock_bh" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xbaabe8a2, "usb_put_dev" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0x4292364c, "schedule" },
	{ 0x139d6559, "eth_type_trans" },
	{ 0x531313c5, "wake_up_process" },
	{ 0xd4f56b60, "pskb_expand_head" },
	{ 0x21fb443e, "_raw_spin_lock_irqsave" },
	{ 0xe45f60d8, "__wake_up" },
	{ 0xd2965f6f, "kthread_should_stop" },
	{ 0xd7bd3af2, "add_wait_queue" },
	{ 0x37a0cba, "kfree" },
	{ 0x801678, "flush_scheduled_work" },
	{ 0x622fa02a, "prepare_to_wait" },
	{ 0xc4554217, "up" },
	{ 0x349883ed, "usb_register_driver" },
	{ 0x75bb675a, "finish_wait" },
	{ 0xa6124ecb, "unregister_netdev" },
	{ 0xb742fd7, "simple_strtol" },
	{ 0xb81960ca, "snprintf" },
	{ 0x259c6d41, "__netif_schedule" },
	{ 0x8235805b, "memmove" },
	{ 0x362f1266, "usb_alloc_coherent" },
	{ 0xa63d465f, "skb_put" },
	{ 0x33d169c9, "_copy_from_user" },
	{ 0x45cfde91, "dev_get_drvdata" },
	{ 0x62d53c10, "usb_free_urb" },
	{ 0x9e7d6bd0, "__udelay" },
	{ 0xf0180b77, "usb_alloc_urb" },
	{ 0xe914e41e, "strcpy" },
	{ 0xb13016ed, "filp_open" },
	{ 0xedbf2306, "alloc_etherdev_mqs" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbcore";

MODULE_ALIAS("usb:v148Fp3070d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v148Fp3071d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v148Fp3072d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p3820d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p871Cd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p822Cd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p871Bd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p822Bd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DF6p003Ed*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DF6p0042d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DF6p0048d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DF6p0047d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DF6p005Fd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v14B2p3C12d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v18C5p0012d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v083Ap7511d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v083ApA701d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v083ApA702d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1740p9703d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1740p9705d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1740p9706d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1740p9707d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1740p9708d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1740p9709d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v13D3p3273d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v13D3p3305d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1044p800Dd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v2019pAB25d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v2019p5201d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v07B8p3070d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v07B8p3071d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v07B8p3072d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v7392p7711d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v7392p4085d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1A32p0304d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1EDAp2310d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v07D1p3C0Ad*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v07D1p3C0Dd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v07D1p3C0Ed*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v07D1p3C0Fd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v07D1p3C16d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v07D1p3C17d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1D4Dp000Cd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1D4Dp000Ed*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1D4Dp0011d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v5A57p5257d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v5A57p0283d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v04BBp0945d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v04BBp0947d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v04BBp0948d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v203Dp1480d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v20B8p8888d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0B05p1784d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v203Dp14A9d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p899Ad*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p3870d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p870Ad*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p6899d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p3822d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p3871d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p871Ad*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p822Ad*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p3821d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DB0p821Ad*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v5A57p0282d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v083ApA703d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v13D3p3307d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v13D3p3321d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v07FAp7712d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0789p0166d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0586p341Ad*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0586p341Ed*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0586p343Ed*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v1EDAp2012d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v148Fp3370d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v0DF6p0050d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v148Fp5370d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v148Fp5372d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v13D3p3365d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v13D3p3329d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v2001p3C15d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v2001p3C19d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v2001p3C1Cd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v2001p3C1Dd*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v043Ep7A12d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v043Ep7A22d*dc*dsc*dp*ic*isc*ip*");

MODULE_INFO(srcversion, "B5F68EDB8F10C7E19E04080");
