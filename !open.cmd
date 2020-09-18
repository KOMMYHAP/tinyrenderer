@echo off

set cmake_generate_flags=-DBUILDING_TESTING:BOOL=ON
set project_path=%~dp0
set build_path=%project_path%\\build\\

mkdir %build_path%
cmake.exe -G "Visual Studio 15 2017 Win64" -T host=x64 -B"%build_path%" %cmake_generate_flags% -H"%project_path%" || goto eof
cmake.exe --open %build_path%
