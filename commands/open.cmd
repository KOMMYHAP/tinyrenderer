call "%~dp0/get_cmake_flags.cmd" %1
if %errorlevel% neq 0 goto :eof

call "%~dp0/generate.cmd" "%cmake_flags%"
if %errorlevel% neq 0 goto :eof

cmake.exe --open %build_path%
