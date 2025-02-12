@echo off 
Cls
DEL /S /F /Q ..\build
DEL /S /F /Q ..\bin
echo "">..\bin\.ignore.me
echo "">..\build\.ignore.me
premake5.exe vs2022
premake5.exe export-compile-commands
copy ..\build\solution\compile_commands\debug_win64.json ..\compile_commands.json
copy ..\deps\openal-soft\OpenAL\bin\Win64\soft_oal.dll ..\bin\example\example1\
copy ..\deps\glew-2.1.0\bin\Release\x64\glew32.dll ..\bin\example\example1\


start ..\build\solution\Engine.sln
