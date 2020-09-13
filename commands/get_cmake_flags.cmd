if %1 == "prod" goto production
if %1 == "dev" goto dev
goto error

:production
set "cmake_flags=-DBUILDING_TESTING=OFF"
goto return

:dev
set "cmake_flags=-DBUILDING_TESTING=ON"
goto return

:error
echo "Error: expected get_cmake_flags (dev|prod), but obtained %1"
set "errorlevel=1"
goto :eof

:return
echo cmake_flags are %cmake_flags%
