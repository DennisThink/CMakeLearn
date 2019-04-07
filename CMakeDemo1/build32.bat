mkdir Build32Bat
cd Build32Bat
cmake ..
MSBuild.exe Demo1.vcxproj -property:Configuration=Debug
pause

MSBuild.exe Demo1.vcxproj -property:Configuration=Release
pause


cd ..
cd bin
cd Debug32
echo '-----------------------------------------------------'
Demo1.exe
pause
echo '-----------------------------------------------------'



cd ..
cd Release32
echo '-----------------------------------------------------'
Demo1.exe
echo '-----------------------------------------------------'
pause