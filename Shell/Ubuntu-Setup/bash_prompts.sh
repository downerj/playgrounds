#!/usr/bin/env bash

black="8;2;0;0;0"
red="8;2;255;0;0"
yellow="8;2;255;255;0"
green="8;2;0;255;0"
cyan="8;2;0;255;255"
blue="8;2;0;0;255"
magenta="8;2;255;0;255"
white="8;2;255;255;255"
reset="0"
bold="1"

chevron=">"

gitline='`git branch 2>/dev/null | grep -e ^* | sed -E s/\\\\\*\ \(.+\)$/\(\\\\\1\)\ /`'
firstline="\[\e[${reset};${bold};3${red}m\]bash \[\e[3${yellow}m\]\u \[\e[3${blue}m\]\H \[\e[3${cyan}m\]\w \[\e[3${green}m\]${gitline}"

chevron_colors=("${magenta}" "${red}" "${yellow}" "${green}" "${cyan}" "${blue}")
chevron_str=""
for color in ${chevron_colors[@]}
do
  chevron_str="${chevron_str}\[\e[3${color}m\]${chevron}"
done

chevron_str_ps2=""
for color in ${chevron_colors[@]}
do
  chevron_str_ps2="${chevron_str_ps2}${chevron}"
done

PS1="${firstline}\[\e[${reset};${bold}m\]\n${chevron_str}\[\e[${reset}m\] "
PS2="\[\e[${reset};${bold}m\]${chevron_str_ps2}\[\e[${reset}m\] "
#trap "echo -ne '\e[0m'" DEBUG

unset black red yellow green cyan blue magenta white chevron
unset firstline gitline chevron_colors chevron_str chevron_str_ps2

PROMPT_COMMAND='if [[ -z ${TABNAME+x} ]]
then
  thisdir=$(basename "$PWD")
  echo -ne "\e]0;${thisdir}\x07"
  unset thisdir
else
  echo -ne "\e]0;${TABNAME}\x07"
fi'

