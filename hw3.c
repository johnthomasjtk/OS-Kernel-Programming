#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */

#define AUTHOR_DESC "t_r3x @ r3xnation.wordpress.com"
#define MODULE_DESC "A simple helloworld driver"

static int __init init_hello_4(void)
{
        printk(KERN_INFO "Hello, world 4\n");
        return 0;
}

static void __exit cleanup_hello_4(void)
{
        printk(KERN_INFO "Goodbye, world 4\n");
}

module_init(init_hello_4);
module_exit(cleanup_hello_4);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR_DESC);
MODULE_DESCRIPTION(MODULE_DESC);
