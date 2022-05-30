$libPath = [String]$(Resolve-Path("$PSScriptRoot"))
$libPath = $libPath.replace("\", "/")

return "include_directories($libPath/lib/json/include)"
