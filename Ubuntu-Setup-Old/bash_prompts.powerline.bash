#!/usr/bin/env bash

black="8;2;0;0;0"
red="8;2;255;0;0"
yellow="8;2;255;255;0"
green="8;2;0;255;0"
cyan="8;2;0;255;255"
blue="8;2;0;0;255"
magenta="8;2;255;0;255"
white="8;2;255;255;255"

arrow=$(echo -e "\ue0b0")
chevron=$(echo -e "\u276f")

segments=(
  "\[\e[3${black}m\]"
  "\[\e[4${red}m\]${arrow}\[\e[3${white}m\] bash \[\e[3${red}m\]"
  "\[\e[4${yellow}m\]${arrow}\[\e[3${black}m\] \u \[\e[3${yellow}m\]"
  "\[\e[4${blue}m\]${arrow}\[\e[3${white}m\] \H \[\e[3${blue}m\]"
  "\[\e[4${cyan}m\]${arrow}\[\e[3${black}m\] \w \[\e[3${cyan}m\]"
  "\[\e[4${green}m\]${arrow}\[\e[3${black}m\]"' `git branch 2>/dev/null | grep -e ^* | sed -E s/\\\\\*\ \(.+\)$/\(\\\\\1\)\ /` '"\[\e[3${green}m\]"
  "\[\e[49m\]${arrow}"
)
firstline=""
for segment in "${segments[@]}"
do
  firstline="${firstline}${segment}"
done

chevron_colors=("$magenta" "$red" "$yellow" "$green" "$cyan" "$blue")
chevron_str=""
for color in ${chevron_colors[@]}
do
  chevron_str="${chevron_str}\[\e[3${color}m\]${chevron}"
done

PS1="${firstline}\[\e[0m\]\n${chevron_str}\[\e[0m\] "
PS2="${chevron}${chevron}${chevron}${chevron}${chevron}${chevron} "

unset black red yellow green cyan blue magenta white arrow chevron
unset segments firstline chevron_colors chevron_str

PROMPT_COMMAND='if [[ -z ${TABNAME+x} ]]
then
  thisdir=$(basename "$PWD")
  echo -ne "\e]0;$thisdir\x07"
  unset thisdir
else
  echo -ne "\e]0;$TABNAME\x07"
fi'

