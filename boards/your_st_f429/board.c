// C Includes
#include <stdio.h>

// Zephyr Includes
#include <zephyr/init.h>
#include <zephyr/kernel.h>

/**
 * @brief Init Hook
 */
static int board_your_st_f429_init() {

    printk("Board initialized\n");
    return 0;
}

// Run Init POST KERNEL
SYS_INIT(board_your_st_f429_init, POST_KERNEL, 50);