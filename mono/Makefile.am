if CROSS_COMPILING
SUBDIRS = arch utils io-layer cil metadata $(interpreter_dir) dis profiler mini
else
if MOONLIGHT
SUBDIRS = arch utils io-layer metadata mini

moon-do-build:
	@list='$(SUBDIRS)'; for subdir in $$list; do \
	  case "x$$subdir" in \
		xmetadata ) target="moon-do-build" ;; \
		xmini ) target="moon-do-build" ;; \
		* ) target="all" ;; \
	  esac; \
	  echo "Making $$target in $$subdir"; \
	  (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$target); \
    done;

moon-do-clean:
	@list='$(SUBDIRS)'; for subdir in $$list; do \
	  case "x$$subdir" in \
		xmetadata ) target="moon-do-clean" ;; \
		xmini ) target="moon-do-clean" ;; \
		* ) target="clean" ;; \
	  esac; \
	  echo "Making $$target in $$subdir"; \
	  (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$target); \
    done;

else
SUBDIRS = arch utils io-layer cil metadata $(interpreter_dir) dis monograph tests benchmark profiler mini
endif
endif
DIST_SUBDIRS = arch utils io-layer cil metadata interpreter dis monograph tests benchmark profiler mini
