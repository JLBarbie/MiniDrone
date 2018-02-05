FROM dolcetriade/qt5-linux-static-openssl:5.9.0

RUN apt-get update && apt-get install -y wget autopoint autoconf gettext libcppunit-dev libtool libgcrypt11-dev pkgconf git

COPY . /airborne

RUN wget https://warehouse.leapmotion.com/apps/4186/download
RUN apt install -y libdbus-1-3
RUN tar xf download && ls Leap* && dpkg -i Leap*/*x64.deb

WORKDIR /airborne
RUN qmake -config release && make clean && make -j`nproc`

CMD cp Minidrone /build-docker
