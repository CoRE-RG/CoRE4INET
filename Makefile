all: checkmakefiles src/core4inet/features.h 
	cd src && $(MAKE)

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile src/features.h

INET_PROJ=../../inet
MAKEMAKE_OPTIONS := -f --deep --no-deep-includes -I. -I$(INET_PROJ)/src/ -DINET_IMPORT -L$(INET_PROJ)/inet/out/$$\(CONFIGNAME\)/src -lINET -KINET_PROJ=$(INET_PROJ)

makefiles: src/core4inet/features.h makefiles-so

makefiles-so:
	@FEATURE_OPTIONS=$$(./core4inet_featuretool options -f -l) && cd src && opp_makemake --make-so $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

makefiles-lib:
	@FEATURE_OPTIONS=$$(./core4inet_featuretool options -f -l) && cd src && opp_makemake --make-lib $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

makefiles-exe:
	@FEATURE_OPTIONS=$$(./core4inet_featuretool options -f -l) && cd src && opp_makemake $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '======================================================================='; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '======================================================================='; \
	echo; \
	exit 1; \
	fi

# generate an include file that contains all the WITH_FEATURE macros according to the current enablement of features
src/core4inet/features.h: $(wildcard .oppfeaturestate) .oppfeatures
	@./core4inet_featuretool defines >src/core4inet/features.h

doxy:
	doxygen doxy.cfg