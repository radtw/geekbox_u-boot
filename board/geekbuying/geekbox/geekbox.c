/*
 * Copyright (c) 2016 Andreas Färber
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm/device.h>
#include <dm/uclass.h>

#include <asm/io.h>
#include "usb.h"

DECLARE_GLOBAL_DATA_PTR;

#if TSAI && defined(CONFIG_TARGET_GEEKBOX)
/* TSAI: for additional configs, put in include/configs/geekbox.h */

extern int tsai_geekbox_probe_display(void);
extern int ctrlc(void);

#endif

extern int board_usb_init(int index, enum usb_init_type init);


static void probe_pmic(void) {
	int ret;
	struct udevice* pdev = NULL;
	int totalprobed = 0;
	printf("TSAI: probe_pmic[in] workaround for geekbox, force probe@%s\n", __FILE__);
	ret = uclass_first_device_check(UCLASS_PMIC, &pdev);
	while (ret==0 && pdev) {
		if (pdev) {
			debug("DONE probe[%d] for %s \n", totalprobed, pdev->name);
			totalprobed++;
		}
		ret = uclass_next_device_check(&pdev);
	}
	debug("TSAI:probe_pmic[out] totalprobed=%d \n", totalprobed);
	return;
}

//TSAI: for backward compatibility, called from boot_from_udisk()
int rkparm_partition_parse(char *param, struct blk_desc *dev_desc)
{
	const char *cmdline = strstr(param, "CMDLINE:");
	//const char *blkdev_parts;
	char *cmdline_end;
//__asm("hlt #0");
	if (!cmdline) {
		debug("RKPARM: Invalid parameter part table from storage\n");
		return -EINVAL;
	}

	//blkdev_parts = strstr(cmdline, "mtdparts");
	cmdline_end = strstr(cmdline, "\n"); /* end by '\n' */
	*cmdline_end = '\0';
	/*
	 * 1. skip "CMDLINE:"
	 * 2. Initrd fixup: remove unused "initrd=0x...,0x...", this for
	 *    compatible with legacy parameter.txt
	 */
	env_update_filter("bootargs", cmdline + strlen("CMDLINE:"), "initrd=");
	//env_append("bootargs", cmdline + strlen("CMDLINE:") );
	printf("TSAI: rkparm_partition_parse @%s\n", __FILE__);
	return 0;
}

void reset_some_hardware(void) {
	//disable USB so that overriding uboot can start it fresh
	char cmdbuf[64];
	printf("TSAI: stopping USB...\n");
	snprintf(cmdbuf, 64, "usb stop f");
	run_command(cmdbuf, 0);
	//__asm("hlt #0");
	//suspend otg-phys
	writel(0x01ff01d1, 0xff770700);
}

//TSAI: if usb-stick contains uboot partition, transfer execution to that uboot, can be stopped by ctrl-c
//this is for legacy device
//called from boot_from_udisk()
int load_overriding_uboot(struct blk_desc *dev_desc, disk_partition_t *info)
{
	long r;
	unsigned char header[512];
	r = blk_dread(dev_desc, info->start, 1, header);
	if (strncmp((char*)header, "LOADER  ", 8)==0) {
		int size = *(uint32_t*)(header+0x14);
		int szlba = (size / 512) + 4;
		ulong use = env_get_ulong("tsai_uboot_override",10, 0);
		if (ctrlc()) {
			printf("TSAI: Ctrl-C skip overriding uboot partition \n");
		}
		else if (use) {
			printf("TSAI: found overriding uboot partition, %d blocks @%s\n", szlba, __FILE__);
			r = blk_dread(dev_desc, (info->start + 4), szlba, (void*)0x200000);
			if (r==szlba) {
				void (*pfn)(void);
				reset_some_hardware();
				printf("TSAI: jumping to uboot partition on %s:%s @%s\n",
						dev_desc->vendor, dev_desc->product, __FILE__);
				puts("==============================================\n");
				pfn = (void*)0x200000;
				pfn();
			}
		}
		else {
			printf("TSAI: skip overriding uboot partition because tsai_uboot_override=%ld\n", use);
		}
	}
	return 0;
}

#if 0
static void probe_regulators(void) {
	int ret;
	struct udevice* pdev = NULL;
	int totalprobed = 0;
	printf("TSAI: probe_regulators[in] workaround for geekbox, force probe@%s\n", __FILE__);
	ret = uclass_first_device_check(UCLASS_REGULATOR, &pdev);
	while (ret==0 && pdev) {
		if (pdev) {
			printf("DONE probe[%d] for %s \n", totalprobed, pdev->name);
			totalprobed++;
		}
		ret = uclass_next_device_check(&pdev);
	}
	printf("TSAI:probe_regulators[out] totalprobed=%d \n", totalprobed);
	return;
}
#endif

//called from board_init
int rk_board_init(void)
{
	debug("rk_board_init @%s\n", __FILE__);
	probe_pmic();
#if TSAI && defined(CONFIG_DRM_ROCKCHIP)
	tsai_geekbox_probe_display();
#endif
	return 0;
}

//will be called from board_late_init()
int rk_board_late_init(void) {
	printf("rk_board_late_init @%s\n", __FILE__);


	return 0;
}
