(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(ansi-color-faces-vector
   [default default default italic underline success warning error])
 '(ansi-color-names-vector
   ["#212526" "#ff4b4b" "#b4fa70" "#fce94f" "#729fcf" "#e090d7" "#8cc4ff" "#eeeeec"])
 '(c-electric-pound-behavior nil)
 '(css-indent-offset 2)
 '(custom-enabled-themes '(manoj-dark))
 '(global-display-line-numbers-mode t)
 '(global-linum-mode f)
 '(inhibit-startup-screen t)
 '(ispell-dictionary nil)
 '(js-indent-level 2)
 '(tab-always-indent nil)
 '(tab-width 2)
 '(truncate-lines t))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(default ((t (:family "Terminus" :foundry "PfEd" :slant normal :weight normal :height 120 :width normal)))))

(setq c-default-style "k&r"
      c-basic-offset 2)
(set-frame-font "Fantasque Sans Mono 14" nil t)
(global-set-key "\C-j" 'newline)
(setq backup-directory-alist `(("." . "~/.emacs-saves")))

