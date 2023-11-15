//TASK II - Including hello1.h header file from directory /inc
//using only it's name (not path)
#include "hello1.h"

//Changed description to better fit laboratory work 4
MODULE_AUTHOR("Olena Fedosieieva <fedosieieva.olena@lll.kpi.ua>");
MODULE_DESCRIPTION("Hello, world - module 2. Contains count parameter which calles print_hello function from hello1 with.");
MODULE_LICENSE("Dual BSD/GPL");

//TASK I - A. Parameter count has been moved to hello2 module
static uint count = 1;

module_param(count, uint, S_IRUGO);
MODULE_PARM_DESC(count, "Number of times to print \"Hello, world!\" (default=1)");

//TASK I - A. Upon initializing module hello2 it will call print_hello function
//from module hello1 while passing it count variable
static int __init hello_init(void){
	pr_info("hello2 has been initiated.\n");
	print_hello(count);
	return 0;
}

static void __exit hello_exit(void){
	pr_info("Goodbye, world! (from hello2)\n");
}

module_init(hello_init);
module_exit(hello_exit);
