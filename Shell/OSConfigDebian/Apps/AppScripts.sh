#!/bin/false

# Invert screen colors (X11).
xcalib -i -a

# Run GVim with tabs.
gvim -p
gvim -p $files

# Run Synaptic GUI as superuser.
synaptic-pkexec

# Run XTerm with custom configuration, without setting defaults file.
xterm -title "XTerm" -fa "Terminus" -fs 12 -bg "black" -fg "white" -bc +bdc -cr "green" -ms "red" -e "/bin/bash" -l

# Disable the keyboard (for touchscreens/tablet mode).
xinput float 11

# Enable the keyboard.
xinput reattach 11 3

