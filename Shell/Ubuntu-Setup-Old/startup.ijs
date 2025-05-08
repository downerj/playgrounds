NB. Simple dec-to-hex converter (8-bit: 0-255).
hex =: 1 : 0
a =: <.u%16
b =: 16|u
h =: '0123456789abcdef'
;/(a,.b){h
)

NB. ANSI escape codes.
ansi_esc =: 4&u:27
ansi_csi =: ansi_esc,'['
ansi_clear =: ansi_esc,'c'
ansi_ed =: ansi_csi,'3J'
ansi_red =: ansi_csi,'1;31m'
ansi_green =: ansi_csi,'1;32m'
ansi_yellow =: ansi_csi,'1;33m'
ansi_blue =: ansi_csi,'1;34m'
ansi_magenta =: ansi_csi,'1;35m'
ansi_cyan =: ansi_csi,'1;36m'
ansi_white =: ansi_csi,'1;37m'
ansi_default =: ansi_csi,'1;39m'
ansi_reset =: ansi_csi,'0m'

