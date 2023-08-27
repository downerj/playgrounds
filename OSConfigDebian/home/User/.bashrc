#!/usr/bin/env bash

##########
# This file is intended for Bourne-again Shells (bash).
# This file by default is sourced in non-login mode, though it can be
# sourced in login mode as well from .bash_profile.
##########

# Set file creation mask.
# Each set bit is an unset flag for each new file.
# Example: umask 022 means chmod go-w.
umask 022

# Set $PATH so that it includes the user's privates binaries, if the
# direcroty exists.
if [[ -d "$HOME/.local/bin" ]]
then
  export PATH="$HOME/.local/bin:$PATH"
fi

# Test for an interactive shell. 
if [[ $- != *i* ]]
then
	# Shell is non-interactive. Be done now!
	return
fi

if [[ -f "$HOME/.bash_aliases" ]]
then
  source $HOME/.bash_aliases
fi

# List directories in color, directories first.
if [[ -f "$HOME/.dircolors" ]]
then
  eval $(dircolors $HOME/.dircolors)
fi

if [[ -f "$HOME/.bash_prompt" ]]
then
  source $HOME/.bash_prompt
fi

# Message of the day.
if [[ -f "$HOME/.bash_motd" ]]
then
  source $HOME/.bash_motd
fi

# History size settings.
export HISTSIZE=1000
export HISTFILESIZE=2000

# Don't put duplicate lines or lines starting with spaces in the 
# history.
export HISTCONTROL=ignoreboth

# Append to the history file; don't overwrite it.
shopt -s histappend

# Store multi-line commands as a single command.
shopt -s cmdhist

# Check the window size after each command, and, if necessary, 
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# The pattern "**" use in a pathname expansion context will match
# all files and zero or more directories and subdirectories.
shopt -s globstar

# Expand aliases.
shopt -s expand_aliases

