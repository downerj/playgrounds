$version = "1.18"
$mc = "$env:APPDATA\.minecraft"
$jsonFile = "$mc\assets\indexes\$version.json"

$json = (Get-Content $jsonFile) -Join " "
$data = ConvertFrom-Json $json

$data.objects | Get-Member -MemberType NoteProperty | ForEach-Object {
  $path = $_.Name
  $hash = $data.objects."$path".hash
  $srcFolder = $hash.Substring(0, 2)
  $dirParts = $path -Split "/"
  $dir = $dirParts[0..($dirParts.Count - 2)] -Join "\"
  
  New-Item $dir -ItemType Directory -ErrorAction SilentlyContinue
  Copy-Item "$mc\assets\objects\$srcFolder\$hash" ".\$path" -ErrorAction SilentlyContinue
}
