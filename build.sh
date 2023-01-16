cd mbedtls
mkdir -p build
cd build
cmake ..
make

cd ../..
cd libwebsockets
cd custom
./build.sh

cd ../..
mkdir -p build
cd build
cmake ..
make