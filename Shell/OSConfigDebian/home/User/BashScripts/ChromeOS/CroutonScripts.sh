#!/bin/false

##########
# Shell settings.
##########

# Update the hostname from "localhost".
#sudo hostname Chromebook

##########
# Installing/updating Crouton.
##########

# Download the crouton installer.
curl -RO https://raw.githubusercontent.com/dnschneid/crouton/master/installer/crouton
if [[ ! $? == 0 ]]
then
  exit 1
fi

# Make it executable.
chmod u+x "./crouton"

# Install it.
sudo install -Dt /usr/local/bin -m 755 ./crouton

##########
# Installing a chroot onto an SD card.
# https://github.com/dnschneid/crouton/wiki/How-To-Install-To-External-Drive
# https://github.com/dnschneid/crouton/wiki/Format-external-storage
##########

# Make sure you know which device the SD card is.
fdisk -l
lsblk | grep mmcblk1

# Unmount the SD Card and prep it (assuming /dev/mmcblk1).
sudo umount /dev/mmcblk1*

# Wipe the SD card and format it as ext4.
sudo dd if=/dev/zero of=/dev/mmcblk1 bs=1M
sudo mkfs.ext4 -L "DebianChroot" /dev/mmcblk1
sudo sync

# Physically eject and reinsert the SD card.

# Create directories and change permissions.
cd /media/removable/DebianChroot
sudo mkdir Downloads downerj
sudo chmod a+rwx Downloads
sudo chown downerj downerj
sudo chgrp downerj downerj

##########
# Install the chroot.
##########
sudo crouton -t audio,cli-extra,core,extension,keyboard,x11,xfce,xiwi,xorg -r buster -n "DebianChroot" -p "/media/removable/DebianChroot"

##########
# Change root.
##########
if [[ ! -d "/media/removable/DebianChroot" ]]
then
  echo "Please insert your DebianChroot SD Card."
  return
fi

##########
# Remount the SD card as executable.
##########
debianMount=$(mount | grep "DebianChroot")
if [[ "$debianMount" == *noexec* ]]
then
  echo "Remounting the SD Card as an exec partition."
  sudo mount -o rw,remount,exec,symfollow /media/removable/DebianChroot
fi

cd /media/removable/DebianChroot

# Start as Xorg.
sudo ./startxfce4 -X xorg

# Start in xiwi window.
sudo ./startxfce4 -X xiwi

# xiwi: Open a window and send it to the xiwi extension on ChromeOS.
xiwi $commandplusargs &> /dev/null &

# Enter chroot w/o GUI.
sudo ./enter-chroot

# Xorg: Disable the keyboard (e.g. for touchscreen).
xinput float 11

# Xorg: Reenable the keyboard.
xinput reattach 11 3

