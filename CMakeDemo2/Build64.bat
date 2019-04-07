pause
mkdir Build64
cd Build64
cmake ../SRC -G "Visual Studio 15 2017 Win64"
MSBuild.exe CMakeDemo2.sln -property:Configuration=Debug
MSBuild.exe CMakeDemo2.sln -property:Configuration=Release

cd ../bin/Debug64/
Main.exe
pause

cd ../Release64/
Main.exe
pause