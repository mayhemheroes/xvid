#!/bin/bash -eu

cd $SRC/xvidcore/build/generic/
./bootstrap.sh
mkdir -p $SRC/xvidcore-install/
if [[ $CFLAGS = *sanitize=memory* ]]; then
    ./configure --prefix=$SRC/xvidcore-install/ --disable-assembly
elif [[ $CFLAGS = *-m32* ]]; then
    LDFLAGS="-m32" ./configure --prefix=$SRC/xvidcore-install/ --disable-assembly
else
    ./configure --prefix=$SRC/xvidcore-install/
fi
make -j $(nproc)
make install

$CXX $CXXFLAGS -I $SRC/xvidcore/src $SRC/fuzzer/fuzzer-decoder.cpp $SRC/xvidcore-install/lib/libxvidcore.a $LIB_FUZZING_ENGINE -o $OUT/fuzzer-decoder
