@set /p build=<settings\build_number.txt
@set add=1
@set /a "output=%build%+%add%"


@echo %output% > "settings/build_number.txt"

@set output=0
