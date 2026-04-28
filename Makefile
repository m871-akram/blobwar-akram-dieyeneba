OBJS = strategy.o blobwar.o main.o font.o mouse.o image.o widget.o rollover.o button.o label.o board.o rules.o blob.o network.o bidiarray.o shmem.o
OBJS_launchComputation = launchStrategy.o strategy.o bidiarray.o shmem.o
OBJS_launchComputation_op = launchStrategy.o strategy_op.o bidiarray.o shmem.o

CXX = /usr/bin/clang++
SDL_CONFIG ?= sdl-config
SDL_CORE_CFLAGS := $(shell $(SDL_CONFIG) --cflags)
SDL_CORE_LIBS := $(shell $(SDL_CONFIG) --libs)

# Local SDL1 companion libs (SDL_image/SDL_ttf/SDL_net) built for this project.
LOCAL_SDL_PREFIX ?= $(CURDIR)/deps/sdl1
LOCAL_SDL_CFLAGS := -I$(LOCAL_SDL_PREFIX)/include/SDL
LOCAL_SDL_LIBS := -L$(LOCAL_SDL_PREFIX)/lib -lSDL_image -lSDL_ttf -lSDL_net
LOCAL_SDL_RPATH := -Wl,-rpath,$(LOCAL_SDL_PREFIX)/lib

CXXFLAGS ?= -Wall -Werror -O3 -g -Wno-strict-aliasing -DDEBUG
CPPFLAGS += $(SDL_CORE_CFLAGS) $(LOCAL_SDL_CFLAGS)
LDFLAGS += $(LOCAL_SDL_RPATH)
LDLIBS += $(LOCAL_SDL_LIBS) $(SDL_CORE_LIBS) -lm -lpthread

# $(sort) removes duplicate objects.
OBJS_ALL = $(sort $(OBJS) $(OBJS_launchComputation) $(OBJS_launchComputation_op) strategy_op.o)

blobwar: $(OBJS) launchStrategy launchStrategy_op
	$(CXX) $(OBJS) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(LDLIBS)

$(OBJS_ALL): %.o: %.cc common.h
	$(CXX) -c $< $(CXXFLAGS) $(CPPFLAGS) -o $@

launchStrategy: $(OBJS_launchComputation)
	$(CXX) $(OBJS_launchComputation) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(LDLIBS)

launchStrategy_op: $(OBJS_launchComputation_op)
	$(CXX) $(OBJS_launchComputation_op) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(LDLIBS)

clean:
	rm -f *.o core blobwar launchStrategy launchStrategy_op *~
