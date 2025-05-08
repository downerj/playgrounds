#!/usr/bin/env bash

function do-auto-open {
  nohup xdg-open "${1}" >/dev/null 2>&1 &
}

function do-open {
  nohup "${1}" "${2}" >/dev/null 2>&1 &
}

function do-auto-open-download {
  echo "Please visit ${1} to download and run the installer."
  nohup xdg-open "${1}" >/dev/null 2>&1 &
}

function setup-terminal {
  local backups_dir="${HOME}/System Backups/home/${USER}/"
  mkdir -p "${backups_dir}"
  if [[ ! -f "${backups_dir}/.bashrc" ]]
  then
    mv "${HOME}/.bashrc" "${backups_dir}/"
  fi
  if [[ ! -f "${backups_dir}/.profile" ]]
  then
    mv "${HOME}/.profile" "${backups_dir}/"
  fi

  if [[ ! -f "${HOME}/.bash_aliases" ]]
  then
    cp "bash_aliases.sh" "${HOME}/.bash_aliases"
  fi

  if [[ ! -f "${HOME}/.bash_profile" ]]
  then
    cp "bash_profile.sh" "${HOME}/.bash_profile"
  fi

  if [[ ! -f "${HOME}/.bash_prompts" ]]
  then
    cp "bash_prompts.sh" "${HOME}/.bash_prompts"
  fi

  if [[ ! -f "${HOME}/.bashrc" ]]
  then
    cp "bashrc.sh" "${HOME}/.bashrc"
  fi

  if [[ ! -f "${HOME}/.dircolors" ]]
  then
    cp "dircolors" "${HOME}/.dircolors"
  fi

  if [[ ! -f "${HOME}/.emacs" ]]
  then
    cp "emacs.el" "${HOME}/.emacs"
  fi

  if [[ ! -f "${HOME}/.gitconfig" ]]
  then
    cp "gitconfig" "${HOME}/.gitconfig"
  fi

  if [[ ! -f "${HOME}/.nanorc" ]]
  then
    cp "nanorc" "${HOME}/.nanorc"
  fi

  if [[ ! -f "${HOME}/.profile" ]]
  then
    cp "profile.sh" "${HOME}/.profile"
  fi

  mkdir -p "${HOME}/.vim/swapfiles"
  if [[ ! -f "${HOME}/.vimrc" ]]
  then
    cp "vimrc.vim" "${HOME}/.vimrc"
  fi
}

function setup-edit-grub {
  local backups_dir="${HOME}/System Backups"
  # Add a backups folder.
  mkdir "${backups_dir}"

  # Back up GRUB file.
  mkdir -p "${backups_dir}/etc/default"
  cp "/etc/default/grub" "${backups_dir}/etc/default/"
  sudo chown ${USER} "${backups_dir}/etc/default/grub"
  # Edit the GRUB file.
  # Sets the following values:
  #
  # GRUB_DEFAULT=saved
  # GRUB_SAVEDEFAULT=true
  sudo cp -f "grub" "/etc/default/grub"
  # Regenerate GRUB.
  # This should automatically add a GRUB entry to boot into UEFI settings.
  sudo update-grub
  echo "Please remember to reboot."
}

function setup-apt-apps {
  # Install apps.
  local app_list_multimedia=( \
    audacity \
    brasero \
    f3d \
    gimp \
    inkscape \
    leocad \
    milkytracker \
    tiled \
    vlc \
  )
  local lua_version=5.4
  local app_list_programming=( \
    adb \
    ant \
    autoconf \
    automake \
    basex \
    binutils \
    clang \
    clang-tidy \
    cmake \
    default-jdk \
    elixir \
    emacs \
    erlang \
    freeglut3-dev \
    g++ \
    gcc \
    gdb \
    git \
    glslang-dev \
    glslang-tools \
    golang \
    kotlin \
    libgles-dev \
    libglew-dev \
    libglfw3-dev \
    libglm-dev \
    libglm-doc \
    libncurses-dev \
    libsdl2-dev \
    libsdl2-mixer-dev \
    libsfml-dev \
    libsfml-doc \
    libvulkan-dev \
    lua${lua_version} \
    manpages \
    manpages-dev \
    maven \
    mesa-utils \
    mesa-vulkan-drivers \
    nodejs \
    npm \
    ocaml \
    patchelf \
    perl \
    php \
    php-fpm \
    python3 \
    python3-pip \
    ruby \
    scala \
    spirv-tools \
    swift \
    texlive \
    tcl \
    vim-gtk \
    vulkan-tools \
    vulkan-validationlayers-dev \
    xsltproc \
  )
  local app_list_utils=( \
    assimp-utils \
    bchunk \
    bsdutils \
    curl \
    dnsutils \
    fdisk \
    ffmpeg \
    fonts-terminus \
    fuse \
    gnome-control-center \
    gnome-tweaks \
    gparted \
    ibus \
    lshw \
    lynx \
    net-tools \
    openssh-client \
    openssh-server \
    pandoc \
    qpdf \
    tigervnc-viewer \
    tmux \
    tree \
    wakeonlan \
    wit \
    xfonts-terminus \
    zenity \
  )
  sudo apt install -y ${app_list_multimedia[@]} ${app_list_programming[@]} ${app_list_utils[@]}
}

function setup-cpp-docs {
  # https://en.cppreference.com/w/Cppreference:Archives
  pushd "/tmp"
  local apps_dir="${HOME}/.local/share/applications"
  local cpp_docs_zip="html_book_20190607.zip"
  local cpp_docs_url="https://upload.cppreference.com/mwiki/images/b/b2/${cpp_docs_zip}"
  local cpp_docs_dir="${HOME}/Source/docs/cppreference"
  curl -LR "${cpp_docs_url}" --limit-rate 1000K -o "${cpp_docs_zip}"
  mkdir -p "${cpp_docs_dir}"
  unzip -d "${cpp_docs_dir}" "${cpp_docs_zip}"
  rm -f "${cpp_docs_zip}"
  local cpp_icon_png="683px-ISO_C%2B%2B_Logo.svg.png"
  local cpp_icon_url="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/${cpp_icon_png}"
  curl -LR "${cpp_icon_url}" -o "${cpp_icon_png}"
  mv "${cpp_icon_png}" "${cpp_docs_dir}/"
  tee "${apps_dir}/cppreference.desktop" <<EOF
#!/usr/bin/env xdg-open
[Desktop Entry]
Version=1.0
Terminal=false
Type=Application
Name=C++ Reference
Exec=xdg-open "${cpp_docs_dir}/reference/en/index.html"
Icon=${cpp_docs_dir}/${cpp_icon_png}
NoDisplay=false
Categories=Development;
EOF
  popd
}

#function setup-mdn-docs {
#  # https://mdn-downloads.s3-us-west-2.amazonaws.com/developer.mozilla.org.tar.gz
#  pushd /tmp
#  local apps_dir="${HOME}/.local/share/applications"
#  local mdn_docs_zip="developer.mozilla.org.tar.gz"
#  local mdn_docs_url="https://mdn-downloads.s3-us-west-2.amazonaws.com/${mdn_docs_zip}"
#  local mdn_docs_dir="${HOME}/Source/docs/mdn"
#  curl -LR --limit-rate 1000K "${mdn_docs_url}" -o "${mdn_docs_zip}"
#  mkdir -p "${mdn_docs_dir}"
#  unzip -d "${mdn_docs_dir}" "${mdn_docs_zip}"
#  rm -f "${mdn_docs_zip}"
#  local mdn_icon_png="mdn_icon.png"
#  local mdn_icon_url="https://avatars.githubusercontent.com/u/7565578"
#  curl -LR "${mdn_icon_url}" -o "${mdn_icon_png}"
#  mv "${mdn_icon_png}" "${mdn_docs_dir}/"
#  tee "${apps_dir}/mdn.desktop" <<EOF
##!/usr/bin/env xdg-open
#[Desktop Entry]
#Version=1.0
#Terminal=false
#Type=Application
#Name=MDN Docs
#Exec=xdg-open "${mdn_docs_dir}/developer.mozilla.org/en-US/index.html"
#Icon=${mdn_docs_dir}/${mdn_icon_png}
#NoDisplay=false
#Categories=Development;
#EOF
#  popd
#}

function setup-java-docs {
  # Download the JDK Docs (need to first accept the License Agreement).
  # Unzip the contents into ${HOME}/Source/docs/JDK.
  # https://www.oracle.com/java/technologies/javase-jdk22-doc-downloads.html
  # https://stackoverflow.com/a/6987039
  pushd /tmp
  local java_docs_dir="${HOME}/Source/docs/JDK"
  local java_icon_png="426px-Duke_%28Java_mascot%29_waving.svg.png"
  local java_icon_url="https://upload.wikimedia.org/wikipedia/commons/thumb/5/5d/Duke_%28Java_mascot%29_waving.svg/${java_icon_png}"
  curl -LR "${java_icon_url}" -o "${java_icon_png}"
  mv "${java_icon_png}" "${java_docs_dir}/"
  local apps_dir="${HOME}/.local/share/applications"
  tee "${apps_dir}/jdkdocs.desktop" <<EOF
#!/usr/bin/env xdg-open
[Desktop Entry]
Version=1.0
Terminal=false
Type=Application
Name=Java SE Docs
Exec=xdg-open "${java_docs_dir}/docs/index.html"
Icon=${java_docs_dir}/${java_icon_png}
NoDisplay=false
Categories=Development;
EOF
  popd
}

function setup-install-chrome {
  do-auto-open-download "https://www.google.com/chrome/?platform=linux"
}

function setup-install-vscode {
  do-auto-open-download "https://code.visualstudio.com/docs/?dv=linux64_deb"
}

function setup-install-discord {
  do-auto-open-download "https://discord.com/download"
}

function setup-install-discord {
  do-auto-open-download "https://www.pj64-emu.com/public-releases"
  echo "Note that Wine is required to run Windows apps on Linux."
}

function setup-install-texmacs {
  pushd /tmp
  local apps_dir="${HOME}/.local/share/applications"
  local install_dir="${HOME}/.local/share/texmacs"
  mkdir -p "${install_dir}"
  # https://texmacs.org/tmweb/download/linux.en.html
  local version="2.1.4"
  local tarball="TeXmacs-${version}-C.tar.gz"
  curl -L -O -R "https://www.texmacs.org/Download/ftp/tmftp/generic/${tarball}"
  tar -x -v -z -f "${tarball}"
  local out_dir="TeXmacs-${version}-x86_64-pc-linux-gnu"
  rm -f "${tarball}"
  mv "${out_dir}/TeXmacs"/* "${install_dir}/"
  rm -rf "${out_dir}"
  local icon_path="${install_dir}/misc/images/texmacs-512.png"
  local script_file="${install_dir}/bin/texmacs.sh"
  tee "${script_file}" <<EOF
#!/usr/bin/env bash
export TEXMACS_PATH="${install_dir}"
export PATH="\$TEXMACS_PATH/bin:\$PATH"
${install_dir}/bin/texmacs &
EOF
  chmod +x ${script_file}
  tee "${apps_dir}/texmacs.desktop" <<EOF
#!/usr/bin/env xdg-open
[Desktop Entry]
Version=1.0
Terminal=false
Type=Application
Name=TeXmacs
Exec=${install_dir}/bin/texmacs.sh
Icon=${icon_path}
NoDisplay=false
Categories=Education;
EOF
  popd
}

function setup-install-musescore {
  pushd /tmp
  local apps_dir="${HOME}/.local/share/applications"
  local install_dir="${HOME}/.local/share/musescore"
  mkdir -p "${install_dir}"
  local icons_dir="${HOME}/.local/share/icons"
  mkdir -p "${icons_dir}"
  # https://musescore.org/en
  local version="4.2.1"
  local hash="240230938"
  local url="https://cdn.jsdelivr.net/musescore/v${version}/MuseScore-${version}.${hash}-x86_64.AppImage"
  local app_file="MuseScore.AppImage"
  curl -L -R -o "${app_file}" "${url}"
  chmod +x "${app_file}"
  ./${app_file} --appimage-extract
  local icon_file="mscore4portable.png"
  cp "squashfs-root/share/icons/hicolor/512x512/apps/${icon_file}" "${icons_dir}/"
  rm -rf "squashfs-root"
  mv "${app_file}" "${install_dir}/"
  tee "${apps_dir}/musescore.desktop" <<EOF
#!/usr/bin/env xdg-open
[Desktop Entry]
Version=1.0
Terminal=false
Type=Application
Name=MuseScore
Exec=${install_dir}/${app_file}
Icon=${icons_dir}/${icon_file}
NoDisplay=false
Categories=Audio;Education;
EOF
  popd
}

function setup-install-j {
  pushd /tmp
  local apps_dir="${HOME}/.local/share/applications"
  local icons_dir="${HOME}/.local/share/icons"
  mkdir -p "${icons_dir}"
  # https://code.jsoftware.com/wiki/System/Installation
  local j_version="9.5"
  local j_zip="j${j_version}_linux64.tar.gz"
  local j_url="https://www.jsoftware.com/download/j${j_version}/install/${j_zip}"
  curl -LOR "${j_url}"
  tar -x -v -z -f "${j_zip}"
  pushd "j${j_version}/bin"
  sudo sh install-usr.sh
  popd
  rm -rf "j${j_version}"
  rm -f "${j_zip}"
  local j_icon_png="Jblue.png"
  local j_icon_url="https://code.jsoftware.com/mediawiki/images/d/d2/${j_icon_png}"
  curl -LOR "${j_icon_url}"
  mv "${j_icon_png}" "${icons_dir}/"
  tee "${apps_dir}/ijconsole.desktop" <<EOF
#!/usr/bin/env xdg-open
[Desktop Entry]
Version=1.0
Terminal=true
Type=Application
Name=J Console
Exec=ijconsole
Icon=${icons_dir}/${j_icon_png}
NoDisplay=false
Categories=Development;
EOF
  popd
}

function setup-install-fonts {
  # Download fonts.
  # Place them in ~/.fonts (you may need to create the folder first).
  # https://fonts.google.com/specimen/Anonymous+Pro
  # https://cm-unicode.sourceforge.io/download.html
  # https://github.com/belluzj/fantasque-sans/releases
  # https://fonts.google.com/specimen/Fira+Code
  # https://fonts.google.com/specimen/JetBrains+Mono
  # https://fonts.google.com/specimen/Source+Code+Pro
  mkdir ~/.fonts
}

function clone-sources {
  ssh-keygen
  # Add SSH keys to GitHub, local devices, etc.
  cat ${HOME}/.ssh/id_rsa.pub

  git config --global user.email "jamesdanieldowner@gmail.com"
  git config --global user.name "Jimmy Downer"

  local sources_dir="${HOME}/Source"
  mkdir "${sources_dir}"
  cd "${sources_dir}"
  mkdir -p "ascenderx/gist"
  mkdir -p "ascenderx/git"
  mkdir -p "downerj/gist"
  mkdir -p "downerj/git"
  mkdir -p "user0x4a35/git"
  # https://github.com/Hopson97/MineCraft-One-Week-Challenge
  # https://github.com/PacktPublishing/Real-Time-3D-Graphics-with-WebGL-2
  # https://github.com/phoboslab/q1k3
  # https://github.com/Plombo/vcromclaim
  # https://github.com/Wiimm/wiimms-iso-tools
}

function setup-install-games {
  # Install QEMU.
  # Add any qemu-system-* targets.
  # You can see the available list by running:
  # sudo apt update && sudo apt search qemu-system
  sudo apt install qemu qemu-system-ppc

  # Install Wine.
  sudo apt install wine

  # Install DOSBox.
  sudo apt install dosbox

  # Install ScummVM.
  sudo apt install scummvm

  # Install Mupen64Plus.
  sudo apt install mupen64plus-qt mupen64plus-data

  # Install FCEUX.
  sudo apt install fceux

  # Install ZSNES.
  sudo apt install zsnes

  # Install mGBA.
  sudo apt install mgba-qt mgba-sdl

  # Install SGT Puzzles.
  sudo apt install sgt-launcher sgt-puzzles
}

function setup-wallpapers {
  echo "Stub"
}

function setup-appgrid {
  gsettings set org.gnome.shell app-picker-layout "[]"
}

function get-app-sizes {
  dpkg-query -Wf '${Installed-Size}\t${Package}\n' | sort -r -n
}

# TODO: add .face
# TODO: Install Godot.
# TODO: Install LMMS.
# TODO: Set passwd for root.
# TODO: Copy dotfiles to root.

function disable-dock {
  cd /usr/share/gnome-shell/extensions/
  sudo mv ubuntu-dock\@ubuntu.com{,.bak}
  # To undo:
  #sudo mv ubuntu-dock\@ubuntu.com{.bak,}
}

function setup-postinstall {
  echo "Open Firefox and navigate to about:preferences#sync to sign in and enable sync."
  echo "Open Chrome and navigate to chrome://settings/people to sign in and enable sync."
  echo "Enable the Compose Key and bind it to Right Alt."
}

function setup-cleanup {
  sudo apt autoremove
  sudo apt autoclean
}

