#!/usr/bin/env bash

myDir="/media/removable/DebianChroot"
if [[ ! -d "$myDir" ]]
then
  echo "Please insert your DebianChroot SD Card."
  return
fi

debianMount=$(mount | grep "DebianChroot")
if [[ "$debianMount" == *"noexec"* ]]
then
  echo "Remounting the SD Card as exec partition."
  sudo mount -o rw,remount,exec,symfollow $myDir
fi

cd $myDir/bin
sudo ./startxfce4 -X xorg
