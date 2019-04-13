
mkdir Build32

cd Build32

cmake ../CMakeMFC1

MSBuild.exe CMakeMFCDemo1.sln -property:Configuration=Debug
MSBuild.exe CMakeMFCDemo1.sln -property:Configuration=Release
cd ..
cd bin
cd Debug32
MFCDemo1.exe