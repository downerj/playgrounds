#!/usr/bin/env bash -f
echo "Updating the Crouton installer..."
curl -RO https://raw.githubusercontent.com/dnschneid/crouton/master/installer/crouton
if [[ ! $? == 0 ]]
then
  exit 1
fi 
chmod u+x ./crouton

echo "Installing the Chroot shortcuts..."
sudo install -Dt /usr/local/bin -m 755 ./UpdateCrouton
sudo install -Dt /usr/local/bin -m 755 ./crouton
sudo install -Dt /usr/local/bin -m 755 ./Chroot
sudo install -Dt /usr/local/bin -m 755 ./Chroot-Xfce4
sudo install -Dt /usr/local/bin -m 755 ./Chroot-Xiwi

