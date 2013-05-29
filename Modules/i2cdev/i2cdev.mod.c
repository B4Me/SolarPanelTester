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
	{ 0xeb5269b2, "module_layout" },
	{ 0x914897a2, "__class_create" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x8503dbb3, "cdev_del" },
	{ 0xdfd98a03, "class_destroy" },
	{ 0x2e62cd4e, "device_destroy" },
	{ 0x7d95f2af, "device_create" },
	{ 0x6cbd6c1b, "cdev_add" },
	{ 0xd8dad454, "cdev_init" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x5f754e5a, "memset" },
	{ 0xd269a2fb, "i2c_del_driver" },
	{ 0x7f869429, "i2c_unregister_device" },
	{ 0xd0b3e9ec, "i2c_put_adapter" },
	{ 0x51dabb02, "i2c_new_device" },
	{ 0xf07021f1, "i2c_get_adapter" },
	{ 0x43743f61, "i2c_register_driver" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xae972eab, "i2c_master_recv" },
	{ 0x69a1ebee, "i2c_master_send" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0xff178f6, "__aeabi_idivmod" },
	{ 0x2196324, "__aeabi_idiv" },
	{ 0x4fe38dbd, "down_interruptible" },
	{ 0x27e1a049, "printk" },
	{ 0x364b3fff, "up" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "37F8D2BA1D6B480589194CD");
