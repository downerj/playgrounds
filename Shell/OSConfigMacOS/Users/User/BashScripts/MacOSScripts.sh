#!/usr/bin/env bash

# NTFS-3G / OSXFuse: Mount, ensuring files appear in Finder.
alias MountNTFS="sudo ntfs-3g -oauto_xattr"

# SSHFS into other Linux distros.
# Examples:
#   SSHFS pi ascender-pi
#   SSHFS downerj acepc-xubuntu
#   SSHFS downerj Jamess-Macbook-Pro 
function SSHFS {
  local OPTIONS="allow_other,default_permissions,IdentityFile=$HOME/.ssh/id_rsa"
  local HOST_USER="$1"
  local HOST="$2"
  local HOST_DIR="/home/$HOST_USER"
  local LOCAL_DIR="/Users/downerj/$HOST_USER"

  if [[ ! -d $LOCAL_DIR ]]
  then
    mkdir -p $LOCAL_DIR
  fi

  sshfs -o $OPTIONS $HOST_USER@$HOST:$HOST_DIR $LOCAL_DIR
}
