@echo off 
Cls
DEL /S /F /Q ..\bin
DEL /S /F /Q ..\build
echo "">..\bin\.deleteme
echo "">..\build\.deleteme
::premake5.exe vs2022
copy ..\deps\openAL\bin\Win64\soft_oal.dll ..\bin\example\example1\
::start ..\..\build\solution\Sirius.sln