@echo off
REM Open the Developer Command Prompt
call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" -startdir=none -arch=x64 -host_arch=x64

REM Navigate to the directory containing the solution file
cd /d "C:\Users\pablo\OneDrive\Documentos\Projects\OpenGL"

REM Run msbuild with the specified parameters
msbuild .\build\solution\Engine.sln /p:Configuration=Debug /p:Platform=Win64

.\bin\example\example1\Example1.exe

REM Close the terminal
exit
