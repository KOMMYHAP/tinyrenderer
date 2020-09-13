call "commands/build.cmd" "dev"
if %errorlevel% neq 0 goto :eof

pushd .
cd %build_path%
ctest --output-on-failure -C Release
popd
