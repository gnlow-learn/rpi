sudo insmod gpio_drv.ko
sudo su
cd /sys/class/sysprog_gpio
echo 17 > export
echo in > gpio17/direction
echo 26 > export
echo out > gpio26/direction
echo 0 > gpio26/value
