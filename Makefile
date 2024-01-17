#Try to detect INET if variable is not set
ifndef INET_PROJ
    ifneq ($(wildcard ../inet),)
        INET_PROJ=../../inet
    else
        $(error "Cannot find INET framework in the usual location. You have to set the PATH to INET in the INET_PROJ variable")
    endif
endif

FEATURES_H = src/core4inet/features.h

all: checkmakefiles $(FEATURES_H)
	cd src && $(MAKE)

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile $(FEATURES_H)
	
ifeq ($(MODE), debug)
    DBG_SUFFIX=_dbg
else
    DBG_SUFFIX=
endif

EXTRA_INCLUDES= -Icore4inet/api/AS6802/tte_api
MAKEMAKE_OPTIONS := -f --deep --no-deep-includes -O out -KINET_PROJ=$(INET_PROJ) -I. $(EXTRA_INCLUDES) -I$(INET_PROJ)/src/ -L$$\(INET_PROJ\)/out/$$\(CONFIGNAME\)/src -lINET$(DBG_SUFFIX) 

makefiles: makefiles-so 

makefiles-so: $(FEATURES_H)
	@FEATURE_OPTIONS=$$(opp_featuretool options -f -l -c | tr '\\' '/') && cd src && opp_makemake --make-so $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

makefiles-lib: $(FEATURES_H)
	@FEATURE_OPTIONS=$$(opp_featuretool options -f -l -c | tr '\\' '/') && cd src && opp_makemake --make-lib $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

makefiles-exe: $(FEATURES_H)
	@FEATURE_OPTIONS=$$(opp_featuretool options -f -l -c | tr '\\' '/') && cd src && opp_makemake $(MAKEMAKE_OPTIONS) $$FEATURE_OPTIONS

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
$(FEATURES_H): $(wildcard .oppfeaturestate) .oppfeatures
	@opp_featuretool defines >$(FEATURES_H)

doc:
	doxygen doxy.cfg