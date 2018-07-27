cd cpp
cmake -DARROW_PLASMA=on -DARROW_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local .
make -j8 install
cd ..
