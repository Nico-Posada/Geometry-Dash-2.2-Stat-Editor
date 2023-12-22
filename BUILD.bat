@echo off

set MSBUILD_PATH="C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MSBuild.exe"
set SOLUTION_PATH=GD Hax.sln
set CONFIGURATION=Release
set PLATFORM=x86

%MSBUILD_PATH% "%SOLUTION_PATH%" /p:Configuration="%CONFIGURATION%" /p:Platform=%PLATFORM%
pause
