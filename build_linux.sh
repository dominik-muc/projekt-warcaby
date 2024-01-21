rm -rf ./build
mkdir build
cd build
cmake -G "MinGW Makefiles" $1 $2 ..  
cmake --build . 
cd ..
