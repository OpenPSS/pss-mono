
if HOST_WIN32
export HOST_CC
endif


if JIT_SUPPORTED
if SUPPORT_SGEN
if STATIC_MONO
runtime_lib=../mini/libmonosgen-static.la        
else
runtime_lib=../mini/libmonosgen-$(API_VER).la
endif
else
if STATIC_MONO
runtime_lib=../mini/libmono-static.la        
else
runtime_lib=../mini/libmono-$(API_VER).la
endif
endif
else
runtime_lib=../interpreter/libmint.la
endif

if !ENABLE_PSS_CRYPTO
bin_PROGRAMS = monograph
endif

INCLUDES = 				\
	-I$(top_srcdir)			\
	$(GLIB_CFLAGS)

monograph_LDADD = \
	$(runtime_lib)			\
	$(GLIB_LIBS)			\
	$(LLVM_LIBS)			\
	$(LIBICONV)			\
	-lm

GRAPHS=System.Object System.Enum System.Attribute System.ValueType System.Reflection.MemberInfo
OUT=$(GRAPHS:=.jpeg)

graphs: $(OUT)

%.jpeg: monograph
	./monograph -n -o $*.png corlib.dll $*
	convert -geometry '480x360>' $*.png $*.jpeg

EXTRA_DIST = ChangeLog

