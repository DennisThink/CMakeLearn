pause
mkdir Build32
cd Build32
cmake ../SRC
MSBuild.exe CMakeDemo2.sln -property:Configuration=Debug
MSBuild.exe CMakeDemo2.sln -property:Configuration=Release

cd ../bin/Debug32/
Main.exe
pause

cd ../Release32/
Main.exe
pause