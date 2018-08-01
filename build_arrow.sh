set -x

cd cpp
cmake -DARROW_PLASMA=on -DARROW_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local .
make -j16 
make install
cd ..
