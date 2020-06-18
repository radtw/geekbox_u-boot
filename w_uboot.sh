#update bootloader uboot.img 
#Note, currently rkdeveloptool need to find GPT partition table, but uboot is on EMMC which doesn't have partition table
#so for now, use old tool to upload bootloader
#sudo '/home/julian/geekbox/rkdeveloptool/rkdeveloptool' wlx uboot ./uboot.img
#sudo '/home/julian/geekbox/rkdeveloptool/rkdeveloptool' rd

#'/home/julian/geekbox/rkdeveloptool/rkdeveloptool' wlx uboot ./uboot.img

#TSAI: 2020-06-18, looks like need to update both or it will not be effective??
'/home/julian/geekbox/rkdeveloptool/rkdeveloptool' WL 16384 /home/julian/geekbox/rkbin/trust.img 
'/home/julian/geekbox/rkdeveloptool/rkdeveloptool' WL 8192 uboot.img
'/home/julian/geekbox/rkdeveloptool/rkdeveloptool' rd


