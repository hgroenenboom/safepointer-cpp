$testLocation = Resolve-Path "$PSScriptRoot/../test"

g++ "$testLocation/test.cpp" -o "$testLocation/test.exe"
& "$testLocation/test.exe"
