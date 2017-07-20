FILES = $(wildcard *.cpp)
OBJECTS = $(subst .cpp,.o,$(FILES))

CPP = g++
AR = ar
ARFLAGS = cr
LIBRARY = libonepokerutil.a

DEBUGOPTION = -DONEPOKER_DEBUG
all:
	$(CPP) -c $(FILES) $(CPPFLAGS)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJECTS)
debug:
	$(CPP) -c $(FILES) $(CPPFLAGS) $(DEBUGOPTION)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJECTS)

clean:
	rm -rf $(OBJECTS) $(LIBRARY)
