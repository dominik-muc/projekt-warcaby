rmdir /S /Q %cd%\build
mkdir build
cd build
cmake ..
cmake --build .
cd ..