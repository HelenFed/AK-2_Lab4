//TASK II - being able to include hello1.h header file from /inc directory
//only using it's name (and not path)
#include "hello1.h"

//Change description to better fit laboratory work 4
MODULE_AUTHOR("Olena Fedosieieva <fedosieieva.olena@lll.kpi.ua>");
MODULE_DESCRIPTION("Hello, world - module 1. cContains main function which is called from hello2 module");
MODULE_LICENSE("Dual BSD/GPL");


struct my_struct {
	struct list_head list;
	ktime_t kernel_time;

	//TASK I - B. Initializing a new variable of ktime type
	//it will later be used to determine kernel time after printing
	ktime_t additional_time;
};

static LIST_HEAD(my_list);


//TASK I - A. print_hello function that is exported at the end of the file
//it will be called from hello2 module, which will pass count parameter
int print_hello(uint count){
	uint i;
	struct my_struct *new_node;

	//TASK III - Replacing printk with pr_err, pr_info and pr_warn
	//Additional changes: instead of few if statements implemented if - else if;
	//cheking if count is negative and returning error if it is.
	if (count == 0 || (count >= 5 && count <= 10)){
		pr_warn("Warning: count parameter has been changed from default 1 to (%u).\n", count);
	} else if (count > 10){
		pr_err("Error: Count should be inside 0 - 10 range.\n");
		return -EINVAL;
	} else if (count < 0){
		pr_err("Count can't be less than 0.\n");
		return -EINVAL;
	}

	for(i = 0; i < count; i++){
		new_node = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
		if (!new_node){
			pr_err("Error: couldn't allocate memory\n");
			return -ENOMEM;
		}

		INIT_LIST_HEAD(&new_node->list);
		new_node->kernel_time = ktime_get();

		pr_info("Hello, world! Current kernel time: %lld\n", ktime_to_ns(new_node->kernel_time));
		
		//TASK I - B. Calculating time spent printing greetings
		//using additional_time variable and subtracting initial kernel_time
		new_node->additional_time = ktime_get();
		new_node->additional_time = ktime_sub(ktime_get(), new_node->kernel_time);
		list_add_tail(&new_node->list, &my_list);
		pr_info("Time taken for one print: %lld nanoseconds\n", ktime_to_ns(new_node->additional_time));
	}
	return 0;
}

static int __init hello_init(void){
	pr_info("hello1 has been initiated\n");
	return 0;
}

static void __exit hello_exit(void){
	struct my_struct *pos, *tmp;
	pr_info("List of greeting and kernel times: \n");
	
	list_for_each_entry(pos, &my_list, list){
		pr_info("Greeting with kernel time: %lld\n", ktime_to_ns(pos->kernel_time));
	}

	list_for_each_entry_safe(pos, tmp, &my_list, list){
		list_del(&pos->list);
		kfree(pos);
	}

	pr_info("Goodbye, world! (from hello1)\n");
}

module_init(hello_init);
module_exit(hello_exit);

//TASK I - A. Exporting print_hello function
EXPORT_SYMBOL(print_hello);
