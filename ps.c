#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

void 
pstree(struct task_struct *init_task)
{
	struct task_struct *next_task;
	struct list_head *list;
	list_for_each(list, &init_task->children) {
		next_task = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO " Name: %s Pid: [%d] State: [%ld]\n", next_task->comm, next_task->pid, next_task->state);
		pstree(next_task);
	}	
}

int
ps_init(void)
{
  printk(KERN_INFO "Loading module ps\n");
  pstree(&init_task);

  return 0;
}

void
ps_exit(void)
{
  printk(KERN_INFO "Removing module ps\n");
}

module_init(ps_init);
module_exit(ps_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PS Module");
