# Flash the image onto a USB stick.
# - Replace `/path/to/xubuntu.iso` with the appropriate ISO image.
# - Replace `sdX` with the appropriate device node.
sudo dd if=/path/to/xubuntu.iso of=/dev/sdX conv=fdatasync status=progress bs=1M

# Boot into the USB stick and run the installer.
# You might need to boot into the PC's UEFI settings to do so.
# Make sure the install medium is botted in UEFI mode!

# On the new installation, run the following installers.

# Terminus font. `xfonts-terminus` for Xorg; `fonts-terminus` for Wayland.
# The Xorg version is needed for the TTY console (for dpkg-reconfigure console-setup).
sudo apt install xfonts-terminus fonts-terminus

# GVim.
sudo apt install vim-gtk3

# Install the OpenSSH server.
# Don't forget to add it to startup:
# - Settings > Session and Startup > Application Autostart
sudo apt install openssh-server

# Generate SSH key.
ssh-keygen

# Start the server.
sudo systemctl start sshd

# Install the Arc theme.
# When setting the theme, set it in the following locations:
# - Settings > Appearance > Style
# - Settings > Window Manager > Style
sudo apt install arc-theme

# Set the TTY font (for Ctrl+Alt+F1, Ctrl+Alt+F2, etc.).
# Set to "Terminus 10x20".
sudo dpkg-reconfigure console-setup

# In Settings > Session and Startup:
# - Check "Automatically save session on logout".

# Go through all of the Xfce settings and disable mouse wheel scroll options.

# Update GRUB on the previous/existing Linux partition, if applicable.
# Edit /etc/default/grub. (Make sure to back it up first.)
# - GRUB_DEFAULT=saved
# - GRUB_TIMEOUT=15
# - GRUB_SAVEDEFAULT=true
# Update Grub.
# Make sure to restart afterwards.
sudo update-grub

# Add Ctrl+Shift+K to Xfce4 Terminal as reset-and-clear.
gvim ~/.config/xfce4/terminal/accels.scm
# Uncomment/add the following line:
# (gtk_accel_path "<Actions>/terminal-window/reset-and-clear" "<Primary><Shift>k")

# Git SCM.
sudo apt install git

# Clone the setup repo.
# For GitHub, first generate your local SSH key (see above), then add it to your GitHub account.
cat ~/.ssh/id_rsa.pub
cd ~/Downloads
git clone git@github.com:ascenderx/osconfig-linux-debian.git OSConfig-Linux-Debian.git

# Java Development Kit.
sudo apt install default-jdk

# GCC for C/C++ (etc.).
sudo apt install gcc g++

# Lisp dialects.
sudo apt install clisp scm

# Manual pages.
sudo apt install manpages manpages-dev

# cURL.
sudo apt install curl

# OpenGL libraries.
sudo apt install libglew-dev libglfw3-dev freeglut3-dev

# Python IDLE REPL.
sudo apt install idle3

# MilkyTracker.
sudo apt install milkytracker

# OCaml.
sudo apt install ocaml

# QPDF.
sudo apt install qpdf

# SQLite.
sudo apt install sqlite3

# Timidity.
sudo apt install timidity timidity-interfaces-extra

# XCalib.
# After install, use `xcalib -i -a` to invert screen colors.
sudo apt install xcalib

# Golang.
sudo apt install golang

# Rust.
sudo apt install rustc

# Lua.
sudo apt install lua5.4

# VSCode.
sudo snap install --classic code

# Icon themes.
sudo apt install faenza-icon-theme gnome-icon-theme

# Ruby.
sudo apt install ruby

# Scala.
sudo apt install scala

# Lynx web browser in console.
sudo apt install lynx

# Swift, from:
# https://swift.org/download/#releases

# PEP 8 style checker for Python 3.
# Alternatively, use `pip install pycodestyle` and run it with:
# `python3 -m pycodestyle <filename>.py`
sudo apt install pycodestyle

