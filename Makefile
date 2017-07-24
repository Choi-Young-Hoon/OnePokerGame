BUILDDIR = ./db ./util ./game ./server ./test ./test_server ./test_client

INCLUDEPATH = $(shell pwd)
export INCLUDEPATH
CPPFLAGS = -O2 -W -Wall -std=c++11 -I$(INCLUDEPATH) $(shell mysql_config --include)
export CPPFLAGS
LIBPATH = $(subst ./,-L$(INCLUDEPATH)/,$(BUILDDIR)) $(shell mysql_config --libs)
export LIBPATH

all:
	@echo "Build Start ============================"
	@echo "Library path : $(LIBPATH)"	
	@for dir in $(BUILDDIR); do \
		$(MAKE) -C $$dir all; \
	done	
	@echo "Build Finish =========================="
debug:
	@for dir in $(BUILDDIR); do\
		$(MAKE) -C $$dir debug; \
	done
clean:
	@for dir in $(BUILDDIR); do \
		$(MAKE) -C $$dir clean; \
	done

