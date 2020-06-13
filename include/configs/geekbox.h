/*
 * Copyright (c) 2016 Andreas Färber
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __CONFIGS_GEEKBOX_H
#define __CONFIGS_GEEKBOX_H

/*TSAI*/
#define CONFIG_BOOTCOMMAND "bootrkp"


#include <configs/rk3368_common.h>

#if defined(CONFIG_CONSOLE_SCROLL_LINES)
#undef CONFIG_CONSOLE_SCROLL_LINES
#endif
#define CONFIG_CONSOLE_SCROLL_LINES		10

#endif
