#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

ssize_t read (struct file* file_, char __user* data, size_t n, loff_t *offset );
ssize_t write (struct file* file_, const char __user* data, size_t n, loff_t *offset );

static struct class *mi_class;
static struct cdev _cdev;

static struct file_operations _fops = {
.owner = THIS_MODULE,
.read = read,
.write = write,
};

dev_t num;
char *nulo = "nulo";



static int __init hello_init(void) {
	cdev_init(&_cdev, &_fops);
	if(alloc_chrdev_region(&num, 0, 1, nulo)<0){
		printk(KERN_ALERT "Error en alloc\n");
	}
	if(cdev_add(&_cdev,num, 1)<0){
		printk(KERN_ALERT "Error en add\n");
	}	
	mi_class = class_create(THIS_MODULE, nulo);
	device_create(mi_class, NULL, num, NULL, nulo);
	printk(KERN_ALERT "Nulo cargado!\n");
	return 0;
}

static void __exit hello_exit(void) {
	unregister_chrdev_region(num, 1);
	cdev_del(&_cdev);
	device_destroy(mi_class, num);
	class_destroy(mi_class);
	printk(KERN_ALERT "Nulo a muerto :(\n");
}

ssize_t read (struct file* file_, char __user* data, size_t n, loff_t *offset ){
	return 0;
}

ssize_t write (struct file* file_, const char __user* data, size_t n, loff_t *offset ){
	return n;
}




module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Una suerte de 'Hola, mundo'");
