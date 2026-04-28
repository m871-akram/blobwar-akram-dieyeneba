CXX = /usr/bin/clang++
SDL_CONFIG ?= sdl-config
SDL_CORE_CFLAGS := $(shell $(SDL_CONFIG) --cflags)
SDL_CORE_LIBS := $(shell $(SDL_CONFIG) --libs)

# Local SDL1 net lib built for this project.
LOCAL_SDL_PREFIX ?= ../deps/sdl1
LOCAL_SDL_CFLAGS := -I$(LOCAL_SDL_PREFIX)/include/SDL
LOCAL_SDL_NET_LIBS := -L$(LOCAL_SDL_PREFIX)/lib -lSDL_net
LOCAL_SDL_RPATH := -Wl,-rpath,$(abspath $(LOCAL_SDL_PREFIX)/lib)

CXXFLAGS ?= -Wall -Werror -g -DDEBUG
CPPFLAGS += $(SDL_CORE_CFLAGS) $(LOCAL_SDL_CFLAGS)
LDFLAGS += $(LOCAL_SDL_RPATH)
LDLIBS += $(LOCAL_SDL_NET_LIBS) $(SDL_CORE_LIBS)

blobwar_server: server.o rules.o
	$(CXX) $^ $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(LDLIBS)

server.o: server.cc
	$(CXX) -c $< $(CXXFLAGS) $(CPPFLAGS) -o $@

rules.o: rules.cc
	$(CXX) -c $< $(CXXFLAGS) $(CPPFLAGS) -o $@

clean:
	rm -f *.o *~ core blobwar_server
