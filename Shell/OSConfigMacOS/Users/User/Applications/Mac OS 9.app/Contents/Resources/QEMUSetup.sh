#!/usr/bin/env bash

##########
# Install QEMU
##########

brew install qemu

##########
# Download and extract a Mac OS 9 image.
##########

# https://macintoshgarden.org/apps/macintosh-system-922-1021-power-macintosh-g4-mirrored-drive-doors-mdd

##########
# Set up QEMU for Mac OS 9
##########

# Create the shared disk image.
D="$HOME/Applications/MacOS 9 (QEMU).app/Contents/Resources"
qemu-img create -f raw -o size=256M "$D/Shared.img"
# Run the setup/installer.
/usr/local/bin/qemu-system-ppc \
  -bios openbios-ppc \
  -M mac99,via=pmu \
  -m 512 \
  -boot d \
  -hda "$D/disk.qcow2" \
  -cdrom "$WHATEVER_THE_ISO_PATH_IS" \
  -prom-env "auto-boot?=true" \
  -prom-env "boot-args=-v" \
  -prom-env "vga-ndrv?=true" \
  -vga std \
  -g 800x600x32 \
  -drive file="$D/Shared.img",format=raw,media=disk
