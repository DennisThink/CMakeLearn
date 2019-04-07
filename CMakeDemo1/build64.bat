mkdir Build64Bat
cd Build64Bat
cmake .. -G "Visual Studio 15 2017 Win64"
MSBuild.exe Demo1.vcxproj -property:Configuration=Debug

pause
MSBuild.exe Demo1.vcxproj -property:Configuration=Release

cd ..
cd bin
cd Debug64
Demo1.exe
pause

cd ..
cd Release64
Demo1.exe
pause