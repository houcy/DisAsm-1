rmdir /s/q windows32-msvc2013
mkdir windows32-msvc2013
cd windows32-msvc2013
cmake -G "Visual Studio 12" -T "v120_xp" -DCMAKE_C_FLAGS="/W4" ..
"%VS120COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
Release\DisAsmTest.exe
Release\DisAsmBenchmark.exe %IPP_HOME%\ipp.bin
cd ..
