#update bootloader uboot.img 
#Note, currently rkdeveloptool need to find GPT partition table, but uboot is on EMMC which doesn't have partition table
#so for now, use old tool to upload bootloader
sudo '/home/julian/geekbox/rkdeveloptool/rkdeveloptool' wlx uboot ./uboot.img
sudo '/home/julian/geekbox/rkdeveloptool/rkdeveloptool' rd

