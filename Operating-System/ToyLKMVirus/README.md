# ToyLKMVirus
A toy virus for loadable kernel module, in linux 2.6.32-38. It is tested under Ubuntu Desktop 10.04.0, x86-64.

# Hiding (by Junru Shao)

As we all know, command *lsmod* will expose all kernel modules loaded. A good virus should hide itself from being detected so easily. Additionally, *sysfs* is a virtual file system recording all module information, and we should take it into careful consideration.

Some tricks are applied to delete the kernel from linked lists that maintains all kernel modules. In fact, two lines of code are enough.

```{c}
list_del_init(&THIS_MODULE->list);
kobject_del(&THIS_MODULE->mkobj.kobj);
```

The first line make the module hide from the command *lsmod*, while the second line make it hide from *sysfs*.

Note that debugging information will be detected in command *dmesg*, it is easy to handle because we only need to comment all *printk* usage.

# Infecting & Speading (by Jian Weng)
When unmounting, the Virus's `.ko` file will be copied to the U-disk, and then the virus will append an insertion command after every `.sh` file (If this file has alread been appended such command, do nothing). The computer will be infected when some `.sh` file copied from this U-dist excuted in root promission on a uninfected machine.

## Technical Details
Reading and writing files in the kernel module is a bad idea, because when the operating system is updated the path of the file might be changed, which means the writers have to rewrite this kernel module. Typically, reading and writing files in kernel module is to read and write configuring options, so, without reading and writing any files, we can use some command options when kernel injection to achieve this effect. However, here is a `virus`, which means we can do anything to violates the concepts of the operating system. The essential difference between reading and writing files in kernel modules and in user applications is buffer. There are two different buffers in Linux operating system. What we have to do is just to set the buffer to users' buffer when reading and writing so that we can deceive the operating system, which is corresponds to the code segment in the `.c` file:

```{c}
void enter_usr_space(void) {
	old_fs = get_fs();
	set_fs(get_ds());
}

void quit_usr_space(void) {
	set_fs(old_fs);
}
```

After reading and writing is done, we have to restore the buffer in avoid of potential error cause by our behaviours.

# Attacking (by Yan Ji)
The kernel module will hide every process begin with `gedit`.

# System Call Hooking (by Junru Shao)
Our virus is designed to replace system calls with our own, which is called *system call hooking*.

In old versions of linux kernel, it is quite convenient to hook system calls, because the system call table, where pointers to system calls are stored, is an exposed global variable. What we should do is a simple replacement of the table entry.

In a little newer versions, system call table is removed from global namespace. Our coping strategy is to find the table in a small range in memory, from *\&sys_close* to *\&loops_per_jiffy*.

Also in some versions of linux kernel, the *lsm*(linux securiy module) is exposed and makes it possible to hack the system call table from the security module.

In our experimental version (2.6.32-38), all of coping strategies turn into failure, because both lsm and system call tables are invisible to kernel module programmers, and attempts to override the system call table are invalid because the write-protection mechanism of it.

It finally turns out that we could use asm language to manually and forcefully set the *wp* (write-protection) bit of cr0 to 0. It works.

# ~~Elevation of Privilege (by Jian Weng)~~
~~To be decided.~~ The vulnerability has been fixed in 2.6.*

