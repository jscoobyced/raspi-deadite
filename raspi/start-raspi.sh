#!/bin/bash

if [ $(id -u) -ne 0 ];
then
	echo "Must be run as root."
	exit -1
fi

mkdir -p chroot-dir/usr/local/src/servo
mount -o bind ../servo chroot-dir/usr/local/src/servo
mount -o bind /dev chroot-dir/dev
mount -t devpts none chroot-dir/dev/pts
mount -t proc none chroot-dir/proc
mount -t sysfs none chroot-dir/sys

chroot chroot-dir

umount chroot-dir/dev/pts
umount chroot-dir/dev
umount chroot-dir/proc
umount chroot-dir/sys