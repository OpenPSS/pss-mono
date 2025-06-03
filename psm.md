CFLAGS="-DTARGET_PSS -DPSS_USE_CRYPTO" $PSS_MONO/configure \
	--disable-boehm --with-sgen=yes --with-gc=sgen --with-mobile=yes --with-monotouch=yes --disable-shared --enable-static