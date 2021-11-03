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


ssize_t read (struct file* file_, char __user* data, size_t n, loff_t *offset );
ssize_t write (struct file* file_, const char __user* data, size_t n, loff_t *offset );
ssize_t open (struct inode *, struct file *);
ssize_t release (struct inode *, struct file *);


static struct class *mi_class;
static struct cdev _cdev;

static struct file_operations _fops = {
.owner = THIS_MODULE,
.read = read,
.write = write,
.open = open,
.release = release,
};

dev_t num;
char *nulo = "letras123";
char espacios[3] = {'0','0','0'};
unsigned long ocupados[3] = {0,0,0}


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

ssize_t read (struct file* file_, char __user* data, size_t n, loff_t *offset ){
	void *buffer = kmalloc(500, 0);

	unsigned int random;
	get_random_bytes((void*) &random, 4);
	random %= number;
	printk(KERN_ALERT "el numero fue %d\n", random);
	int res= snprintf(buffer,40 , "%u", random);

	if(copy_to_user(data, buffer, n)!=0){
		printk(KERN_ALERT "error de copia\n");
	}
	kfree(buffer);
	
	return 40;
}

ssize_t write (struct file* file_, const char __user* data, size_t n, loff_t *offset ){
	char *buffer = kmalloc(500, 0);
	if(copy_from_user(buffer, data, n)!=0){
		printk(KERN_ALERT "error de copia\n");
	}
	espacios[]

	return n;
}


ssize_t open (struct inode *_inode, struct file *){
	if(ocupados[0]==0){
		ocupados[0] = _inode->i_ino;
	} else {
		if(ocupados[1]==0){
			ocupados[1] = _inode->i_ino;
		} else {
			if(ocupados[2]==0){
				ocupados[2] = _inode->i_ino;
			} else 
				return -1;
		}
	}
}

ssize_t release (struct inode *_inode, struct file *){
	if(ocupados[0]==_inode->i_ino){
		ocupados[0] = 0;
	} else {
		if(ocupados[1]==_inode->i_ino){
			ocupados[1] = 0;
		} else {
			if(ocupados[2]==_inode->i_ino){
				ocupados[2] = 0;
			} else 
				return -1;
		}
	}
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Una suerte de 'Hola, mundo'");
