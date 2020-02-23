set /p build=<build_number.txt
set add=1
set /a "output=%build%+%add%"
echo %output%

echo %output% > "settings/build_number.txt"

set output=0
