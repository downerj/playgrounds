#$HOME\Documents\WindowsPowerShell\

$esc = [char]27
$red = "$esc[1;31m"
$green = "$esc[1;32m"
$yellow = "$esc[1;33m"
$blue = "$esc[1;34m"
$magenta = "$esc[1;35m"
$cyan = "$esc[1;36m"
$default = "$esc[1;39m"
$reset = "$esc[0m"

function Prompt {
  "$yellow" + "PS " + "$cyan$($executionContext.SessionState.Path.CurrentLocation | Split-Path -Leaf) " + "$green$('>' * ($nestedPromptLevel + 1))" + "$reset "
}
