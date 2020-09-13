pushd .

set source_path=%~dp0
set build_path=C:/cmake-build/tinyrenderer/

mkdir "%build_path%"
cd "%build_path%"

cmake.exe -G"Visual Studio 15 2017" -A"x64" -T"host=x64" -B"%build_path%" -H"%source_path%" && cmake.exe --open "%build_path%"

popd