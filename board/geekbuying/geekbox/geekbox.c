/*
 * Copyright (c) 2016 Andreas Färber
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm/device.h>
#include <dm/uclass.h>

DECLARE_GLOBAL_DATA_PTR;

#if TSAI && defined(CONFIG_TARGET_GEEKBOX)
extern int tsai_geekbox_probe_display(void);
#endif


static void probe_pmic(void) {
	int ret;
	struct udevice* pdev = NULL;
	int totalprobed = 0;
	printf("TSAI: probe_pmic[in] workaround for geekbox, force probe@%s\n", __FILE__);
	ret = uclass_first_device_check(UCLASS_PMIC, &pdev);
	while (ret==0 && pdev) {
		if (pdev) {
			printf("DONE probe[%d] for %s \n", totalprobed, pdev->name);
			totalprobed++;
		}
		ret = uclass_next_device_check(&pdev);
	}
	printf("TSAI:probe_pmic[out] totalprobed=%d \n", totalprobed);
	return;
}

//TSAI: for backward compatibility
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
	printf("rk_board_init @%s\n", __FILE__);
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
