@echo off

Cls
DEL /S /F /Q .\bin
DEL /S /F /Q .\build
echo "">.\bin\.deleteme
echo "">.\build\.deleteme
copy .\deps\openAL\bin\Win64\soft_oal.dll .\bin\example\example1\

cd tools
Cls
premake5 vs2022
REM Close the terminal
exit
