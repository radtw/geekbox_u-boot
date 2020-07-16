/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <command.h>

#if TSAI
	extern struct blk_desc *rockchip_get_bootdev(void);
#endif

static int do_download(cmd_tbl_t *cmdtp, int flag,
		       int argc, char * const argv[])
{
#ifdef CONFIG_CMD_ROCKUSB
#if TSAI //Sanity check see if usb stop has been called
	//__asm("hlt #0");
	rockchip_get_bootdev();
#endif

	run_command("rockusb 0 $devtype $devnum", 0);
#endif
#ifdef CONFIG_CMD_GO
	printf("Enter rockusb failed, fallback to bootrom...\n");
	flushc();
	run_command("rbrom", 0);
#endif
	return 0;
}

U_BOOT_CMD(
	download, 1, 1, do_download,
	"enter rockusb/bootrom download mode", ""
);
