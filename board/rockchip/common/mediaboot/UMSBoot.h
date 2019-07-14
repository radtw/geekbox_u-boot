/*
 * (C) Copyright 2008-2015 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef _UMS_BOOT_H
#define _UMS_BOOT_H

#define     UMS_BOOT		(1)	// UMS boot
#define     UMS_UPDATE		(2)	// UMS update

/******************************************************************************/
extern uint32 UMSInit(uint32 ChipSel);
extern uint32 UMSReadPBA(uint8 ChipSel, uint32 PBA, void *pbuf, uint32 nSec);
extern uint32 UMSReadLBA(uint8 ChipSel, uint32 LBA, void *pbuf, uint32 nSec);
#if TSAI
extern uint32 UMSWriteLBA(uint8 ChipSel, uint32 LBA, void *pbuf, uint32 nSec, uint32 mode);
#endif
extern uint32 UMSSysDataLoad(uint8 ChipSel, uint32 LBA, void *pbuf);

extern void UMSReadID(uint8 ChipSel, void *buf);
extern void UMSReadFlashInfo(void *buf);
extern uint32 UMSGetCapacity(uint8 ChipSel);
extern uint32 UMSGetBootMode(void);

#if TSAI
extern void UMSDeInit(uint32 ChipSel);
extern block_dev_desc_t* UMSGetBlockDev(void);
extern gpt_header* UMSGetGPTHeader(void);

#define GPT_SIGNATURE (0x5452415020494645) /* 'EFI PART'*/
#define UMS_GPT_PARAMETER_LBA  (1024) /* when use emmc, parameter is at LBA 0, GPT must reserve 0, so I put it at LBA 1024 */
#endif

#endif /* _UMS_BOOT_H */
