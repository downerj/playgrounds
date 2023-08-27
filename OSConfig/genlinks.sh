#!/bin/bash

# You can comment out any lines below to force this script to always skip them.
# Otherwise, as long as -f is not passed when run, the user will need to confirm each file.
FILES=( \
  "bashfmt" \
  "bash_profile" \
  "bashrc" \
  "bashutils" \
  "dircolors" \
  "lscolors-bsd" \
  "profile" \
  "vimrc" \
  "Xdefaults" \
  "Xresources" \
)

# Display usage.
function display_usage {
  echo "Usage: bash genlinks.sh [-h|--help] [OPTIONS]"
  echo "Create links to project files in user's HOME folder."
  echo ""
  echo "OPTIONS:"
  echo -e "\t-B  Do not create .bak files before linking"
  echo -e "\t-c  Make copies instead of linking"
  echo -e "\t-f  Link all files and replace existing files"
}

# Check command-line flags.
BACKUPS="y"
COPY=
FORCED=

while getopts ":Bcf" ARG
do
  case $ARG in
    B) BACKUPS= ;;
    c) COPY="y" ;;
    f) FORCED="y" ;;
    h)
      display_usage
      exit 0
    ;;
    ?)
      echo "Unknown argument \"$ARG\""
      display_usage
      exit 2
    ;;
  esac
done
shift $(($OPTIND - 1))

for F in ${FILES[@]}
do
  LINK="$HOME/.$F"
  TARGET="$PWD/home/user/$F"
  SKIP=
  
  # $FORCED is unset...
  if [[ -z $FORCED ]]
  then
    echo -n "Link $F [y/N]? "
    read DO_LINK
    case $DO_LINK in
      y) ;;
      Y) ;;
      *)
        SKIP="y"
      ;;
    esac
    
    # $SKIP is unset...
    if [[ -z $SKIP ]]
    then
      # link or file exists...
      if [[ -L $LINK ]] || [[ -f $LINK ]]
      then
        echo -n "$LINK already exists. Replace anyway [y/N]? "
        read DO_REPLACE
        
        case $DO_REPLACE in
          y) ;;
          Y) ;;
          *)
            SKIP="y"
          ;;
        esac
      fi
    fi
  # $FORCED is set...
  else
    SKIP=
  fi
  
  # $SKIP is unset...
  if [[ -z $SKIP ]]
  then
    # link exists...
    if [[ -L $LINK ]]
    then
      rm -f $LINK
    # file exists but isn't a link...
    elif [[ -f $LINK ]]
    then
      mv -f $LINK $LINK.bak
    fi
    
    # $COPY is unset...
    if [[ -z $COPY ]]
    then
      echo "Linking $F -> $LINK"
      ln -s $TARGET $LINK
    # $COPY is set...
    else
      echo "Copying $F -> $LINK"
      cp -f $TARGET $LINK
    fi
  # $SKIP is set...
  else
    echo "Skipping $F"
  fi
  
  # $FORCED is unset…
  if [[ -z $FORCED ]]
  then
    echo ""
  fi
done
