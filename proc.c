#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/proc_fs.h>
#include<asm/uaccess.h>

#define procfs_name "helloword"

struct proc_dir_entry *Our_Proc_File;

static ssize_t procfile_read(struct file *file, char *buffer, size_t length, loff_t *offset) {

    static int finished = 0;
    if (finished) {
        printk(KERN_ALERT "Fully read");
        finished = 0;
        return 0;
    }
    finished = 1;
    if (copy_to_user(buffer, "Hello", 6)) {
        printk(KERN_ALERT "Nothing saved in the file");
        return -EFAULT;
    }
    return 6;
}

static struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .read = procfile_read,
};

int init_module()
 {
    Our_Proc_File=proc_create(procfs_name, 0644, NULL,&hello_fops);
     if(Our_Proc_File == NULL) {
        remove_proc_entry(procfs_name,NULL);
        printk(KERN_ALERT "Error : could not intialize /proc/%s\n",procfs_name);
        return -ENOMEM;
    }

    printk(KERN_INFO "/proc/%s created\n",procfs_name);
    return 0;
}
 
void cleanup_module () {
    remove_proc_entry(procfs_name,NULL);
    printk(KERN_INFO "/proc/%s removed \n",procfs_name);

}
