#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/random.h>
#include <linux/kernel.h>
#include <linux/slab.h> 


static ssize_t read (struct file* file_, char __user* data, size_t n, loff_t *offset );
static ssize_t write (struct file* file_, const char __user* data, size_t n, loff_t *offset );

static struct class *mi_class;
static struct cdev _cdev;

static struct file_operations _fops = {
.owner = THIS_MODULE,
.read = read,
.write = write,
};

dev_t num;
char *nulo = "azar";
int number = -1;


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
	printk(KERN_ALERT "Hola, Sistemas Operativos!\n");
	return 0;
}

static void __exit hello_exit(void) {
	unregister_chrdev_region(num, 1);
	cdev_del(&_cdev);
	device_destroy(mi_class, num);
	class_destroy(mi_class);
	printk(KERN_ALERT "Adios, mundo cruel...\n");
}

static ssize_t read (struct file* file_, char __user* data, size_t n, loff_t *offset ){
	if(number == -1){
		return -1;
	}
	char *buffer = (char *)(kmalloc(n, GFP_KERNEL));

	void *random = kmalloc(n, GFP_KERNEL);
	
	get_random_bytes(random, 8);
	printk(KERN_ALERT "chars: %s\n", (char *)(random));
	unsigned int rNumber = *(unsigned int *)(random);
	rNumber %= number;
	printk(KERN_ALERT "el numero fue %d\n", rNumber);
	snprintf(buffer,n , "%u\n", rNumber);

	if(copy_to_user(data, buffer, n)!=0){
		printk(KERN_ALERT "error de copia\n");
	}
	kfree(buffer);
	kfree(random);
	
	return n;
}

static ssize_t write (struct file* file_, const char __user* data, size_t n, loff_t *offset ){
	char *buffer = kmalloc(n, 0);
	if(copy_from_user(buffer, data, n)!=0){
		printk(KERN_ALERT "error de copia\n");
	}
	buffer[n] = '\0';	
	if(kstrtoint(buffer, 10, &number)!=0){
		printk(KERN_ALERT "pasaste algo mal\n");
		return -1;
	}
	printk(KERN_ALERT "el entero quedo en %d\n", number);
	return n;
}




module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Una suerte de 'Hola, mundo'");
