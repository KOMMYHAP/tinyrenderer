set errorlevel=0
set project_path=%~dp0..\\
set build_path=%project_path%build\\
mkdir %build_path%

echo build_path=%build_path%
echo project_path=%project_path%

cmake.exe -G "Visual Studio 15 2017 Win64" -T host=x64 -B %build_path% %1 -S "%project_path%" || set "errorlevel=1"
