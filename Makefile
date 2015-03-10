LIBMODS		:=
MODULES		:=
SRCDIR		:= src $(addprefix src/,$(MODULES))
INCDIR		:= include
BINDIR		:= bin
BUILDDIR	:= build
BINMODS		:= $(addprefix bin/,$(MODULES))
TARGET		:= $(BINDIR)/sonic-verify
SRCS		:= $(shell find $(SRCDIR) -name '*.cpp')
HEADERS		:= $(shell find $(INCDIR) -name '*.h')
OBJECTS 	:= $(subst src,$(BUILDDIR),$(SRCS:%.cpp=%.o))


vpath $(SRCDIR)

arch		= i686-linux
CC		= clang-3.5
CXX		= clang++-3.5
LD		= clang++-3.5
CFLAGS		= -Wall -Werror -Wextra -std=c++11 -g -Wno-deprecated
LDFLAGS		= -L/build/buildd/ruby1.9.1-1.9.3.484/debian/lib -L/var/lib/gems/1.9.1/gems/rice-1.7.0/ruby/lib/lib -lrice -lruby-1.9.1-static -lcrypt -ldl -pthread
DEFS		= 
INCFLAGS	= $(addprefix -I,$(INCDIR)) -I/usr/include/ruby-1.9.1/$(arch) -I/var/lib/gems/1.9.1/gems/rice-1.7.0/ruby/lib/include -I/usr/include/ruby-1.9.1/ruby/backward -I/usr/include/ruby-1.9.1

DIRGUARD	= @mkdir -p $(@D)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(DIRGUARD)
	$(LD) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: src/%.cpp
	$(DIRGUARD)
	$(CXX) $(DEFS) $(INCFLAGS) $(CFLAGS) -c $< -o $@

$(SRCS): $(HEADERS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(DEFS) $(CFLAGS) $(INCFLAGS) -MM $^ -MF  ./.depend;

include .depend

clean:
	-rm -rf $(BINDIR) $(BUILDDIR)

distclean:: clean
