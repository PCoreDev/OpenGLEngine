@echo off 
Cls
DEL /S /F /Q ..\build
DEL /S /F /Q ..\bin
echo "">..\bin\.ignore.me
echo "">..\build\.ignore.me
premake5.exe vs2022
copy ..\deps\openal-soft\OpenAL\bin\Win64\soft_oal.dll ..\bin\example\example1\
start ..\build\solution\Engine.sln