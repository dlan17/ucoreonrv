#include <clock.h>
#include <console.h>
#include <defs.h>
#include <intr.h>
#include <kdebug.h>
#include <kmonitor.h>
#include <pmm.h>
#include <riscv.h>
#include <stdio.h>
#include <string.h>
#include <trap.h>

int kern_init(void) __attribute__((noreturn));
void grade_backtrace(void);
static void lab1_switch_test(void);

int kern_init(void) {
    extern char edata[], end[];
    memset(edata, 0, end - edata);

    cons_init();  // init the console

    const char *message = "(THU.CST) os is loading ...\n";
    cprintf("%s\n\n", message);

    print_kerninfo();

    // grade_backtrace();

    idt_init();  // init interrupt descriptor table

    // rdtime in mbare mode crashes
    clock_init();  // init clock interrupt

    intr_enable();  // enable irq interrupt

    asm volatile("ebreak"::);

    // LAB1: CAHLLENGE 1 If you try to do it, uncomment lab1_switch_test()
    // user/kernel mode switch test
    // lab1_switch_test();
    /* do nothing */
    while (1)
        ;
}

void __attribute__((noinline))
grade_backtrace2(unsigned long long arg0, unsigned long long arg1, unsigned long long arg2, unsigned long long arg3) {
    mon_backtrace(0, NULL, NULL);
}

void __attribute__((noinline)) grade_backtrace1(int arg0, int arg1) {
    grade_backtrace2(arg0, (unsigned long long)&arg0, arg1, (unsigned long long)&arg1);
}

void __attribute__((noinline)) grade_backtrace0(int arg0, int arg1, int arg2) {
    grade_backtrace1(arg0, arg2);
}

void grade_backtrace(void) { grade_backtrace0(0, (unsigned long long)kern_init, 0xffff0000); }

static void lab1_print_cur_status(void) {
    static int round = 0;
    round++;
}

static void lab1_switch_to_user(void) {
    // LAB1 CHALLENGE 1 : TODO
}

static void lab1_switch_to_kernel(void) {
    // LAB1 CHALLENGE 1 :  TODO
}

static void lab1_switch_test(void) {
    lab1_print_cur_status();
    cprintf("+++ switch to  user  mode +++\n");
    lab1_switch_to_user();
    lab1_print_cur_status();
    cprintf("+++ switch to kernel mode +++\n");
    lab1_switch_to_kernel();
    lab1_print_cur_status();
}
