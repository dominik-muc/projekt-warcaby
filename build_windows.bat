rmdir /S /Q %cd%\build
mkdir build
cd build
cmake -G "MinGW Makefiles" ..  
cmake --build .
cd ..