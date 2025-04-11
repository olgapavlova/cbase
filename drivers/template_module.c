#include <linux/init.h>
#include <linux/module.h>

static  int __init your_module_init(void) { return 0; }
static void __exit your_module_exit(void) { }

module_init(your_module_init);
module_exit(your_module_exit);

MODULE_LICENSE("GPL");
// MODULE_AUTHOR("Your Name");
