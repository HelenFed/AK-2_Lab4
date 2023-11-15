#ifndef HELLO1_H
#define HELLO1_H

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/ktime.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/slab.h>

int print_hello(uint count);

#endif
