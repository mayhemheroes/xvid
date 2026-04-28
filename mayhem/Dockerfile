FROM gcr.io/oss-fuzz-base/base-builder
RUN apt-get update && apt-get install -y make autoconf automake libtool
COPY xvidcore $SRC/xvidcore
COPY mayhem/fuzzer $SRC/fuzzer
COPY mayhem/build.sh $SRC/

ENV FUZZING_LANGUAGE=c++ SANITIZER=address ARCHITECTURE=x86_64
RUN compile
RUN chmod +x /out/fuzzer-decoder
