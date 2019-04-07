mkdir Build64

cd Build64

cmake ../CMakeMFC1 -G "Visual Studio 15 2017 Win64"

MSBuild.exe CMakeMFCDemo1.sln -property:Configuration=Debug
MSBuild.exe CMakeMFCDemo1.sln -property:Configuration=Release
cd ..
cd bin
MFCDemo1.exe