##########
# This file is intended for Bourne-again Shells (bash).
# This file by default is sourced in login mode.
##########

# Source the non-login mode as well for consistency.
if [[ -f "$HOME/.bashrc" ]]
then
	source "$HOME/.bashrc"
fi

