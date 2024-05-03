#!/bin/sh

configure="./autogen.sh"
if [ -e 'configure' ]; then
    configure="./configure"
fi
"$configure" --with-sgen=yes --disable-mcs-build --enable-shared=no --with-mobile=yes

# "mono/mini/.libs/libmonosgen-static.a" is the file you're after
build() {
    make CFLAGS='-DTARGET_PSS -DPSS_USE_CRYPTO -DHAVE_ISINF=1' -j"$(nproc)" "$@"
} &&
build -C libgc &&
build -C mono/io-layer &&
build -C mono/metadata &&
build -C eglib &&
build -C mono/utils libmonoutils.la &&
build -C mono/mini distdir="mono/mini" distdir &&
build -C mono/mini libmonosgen-static.la

[ -e builddir ] || mkdir builddir
cp -a -t builddir \
  mono/mini/.libs/libmonosgen-static.a \
  eglib/src/.libs/libeglib-static.a
