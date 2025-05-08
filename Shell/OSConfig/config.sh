#!/usr/bin/env bash

#####
# Crouton: Fix ~/Downloads write issue.
#####
# Comment out "session optional pam_keyinit.so force revoke".
sudo vim /etc/pam.d/runuser-l
sudo vim /etc/pam.d/su-l

#####
# XOrg terminal shortcut.
#
# Terminus font:
#   - GNU/Linux: "Terminus"
#   - FreeBSD: "xos4 Terminus"
#####
xterm -title "XTerm" -fa "Terminus" -fs 12 -bg "black" -fg "white" -bc +bdc -cr "green" -ms "red" -e "/bin/bash" -l

#####
# SSH configuration.
#####
ssh-keygen
ssh-copy-id -i -p<port> <username>@<ipaddress>

#####
# Download this configuration directory.
#####
git clone https://github.com/ascenderx/termconfig.git .termconfig
~/.termconfig/genlinks.sh

#####
# Update X defaults
#####
xrdb -merge .Xdefaults

