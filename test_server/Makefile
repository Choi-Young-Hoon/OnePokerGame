FILES = $(wildcard *.cpp)
OBJECTS = $(subst .cpp,.o,$(FILES))
TARGETS = $(subst .cpp,,$(FILES))

CPP = g++
LIBRARY = -lonepokergamedata -lonepokerserver -lonepokerutil -lonepokerdb

all:$(TARGETS)
debug: $(TARGETS)


$(TARGETS):
	$(CPP) -o $@ $@.cpp -g -ggdb $(CPPFLAGS) $(LIBPATH) $(LIBRARY) $(shell mysql_config --libs)


clean:
	rm -rf $(OBJECTS) $(TARGETS)
