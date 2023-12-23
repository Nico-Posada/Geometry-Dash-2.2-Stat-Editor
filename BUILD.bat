@echo off
setlocal enabledelayedexpansion

set "BasePath=C:\Program Files\Microsoft Visual Studio\2022"
set "Editions=Community Enterprise Professional"
set "MSBUILD_PATH="

for %%e in (%Editions%) do (
    set "CheckPath=%BasePath%\%%e"
    if exist "!CheckPath!\" (
        set "MSBUILD_PATH=!CheckPath!\Msbuild\Current\Bin\MSBuild.exe"
        goto :compile
    )
)

echo Failed to find Visual Studio 2022 on your system. Make sure to have it installed!
exit

:compile
set "SOLUTION_PATH=GD Hax.sln"
set "CONFIGURATION=Release"
set "PLATFORM=x86"

"!MSBUILD_PATH!" "!SOLUTION_PATH!" /p:Configuration="!CONFIGURATION!" /p:Platform=!PLATFORM!
pause
endlocal
