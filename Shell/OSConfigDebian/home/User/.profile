##########
# This is intended for POSIX/Bourne shells (sh).
##########

# Set file mode creation mask.
# Each set bit is an unset flag for each new file.
# Example: umask 022 means chmod go-w.
umask 022

# Set $PATH so that it includes the user's private binaries if the
# directory exists.
if [ -d "$HOME/bin" ]
then
  export PATH="$PATH:$HOME/bin"
fi

# Uncomment this to ensure security programs are accessible to root.
#export PATH="$PATH:/usr/sbin:/usr/local/sbin"

