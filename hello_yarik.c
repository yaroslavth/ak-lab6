#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>

struct head_list {
struct head_list *next;
ktime_t time;
};

MODULE_AUTHOR("Drovnin Pasha IV-83");
MODULE_DESCRIPTION("Lab6");
MODULE_LICENSE("Dual BSD/GPL");

static struct head_list *head;

static int amount = 1;
module_param(amount, uint, 0444);
MODULE_PARM_DESC(amount, "Amount");

static int __init thisinit(void)
{
uint i;

struct head_list *var_1, *var_2;

head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);

var_1 = head;
if (amount == 0) {
	pr_warn("Entered parameter equals 0");
} else if (amount >= 5 && amount <= 10) {
	pr_warn("Entered parameter is between 5 and 10");
} else if (amount > 10) {
	pr_warn("Entered parameter is bigger than 10");
return -EINVAL;
}

for (i = 0; i < amount; i++) {
	var_1->next = kmalloc(sizeof(struct head_list), GFP_KERNEL);
	var_1->time = ktime_get();
	pr_info("Hello World!");
	var_2 = var_1;
	var_1 = var_1->next;
}

if (amount != 0) {
	kfree(var_2->next);
	var_2->next = NULL;
}

pr_info("Amount: %d\n", amount);

return 0;
}

static void __exit thisexit(void)
{
struct head_list *var;

while (head != NULL && amount != 0) {
	var = head;
	pr_info("Time: %lld", var->time);
	head = var->next;
	kfree(var);
}
pr_info("");
}

module_init(thisinit);
module_exit(thisexit);
