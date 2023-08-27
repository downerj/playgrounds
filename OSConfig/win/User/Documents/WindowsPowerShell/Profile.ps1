$Global:Admin=''
$CurrentUser = [System.Security.Principal.WindowsIdentity]::GetCurrent()
$Principal = New-Object System.Security.Principal.WindowsPrincipal($CurrentUser)
if ($Principal.IsInRole("Administrators")) { $Admin='ADMIN ' }

function Prompt {
  $Admin + 'PS ' + ($pwd -split '\\')[0]+' '+$(($pwd -split '\\')[-1] -join '\') + '> '
}