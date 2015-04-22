# V=0 quiet, V=1 verbose.  other values don't work.
V	= 0
Q1	= $(V:1=)
Q	= $(Q1:0=@)
n 	= $(NULLCMD)
ECHO1	= $(V:1=@$n)
ECHO	= $(ECHO1:0=@echo)

LIBMODS		:=
MODULES		:=
SRCDIR		:= src $(addprefix src/,$(MODULES))
INCDIR		:= include
BINDIR		:= bin
BUILDDIR	:= build
BINMODS		:= $(addprefix bin/,$(MODULES))
TARGET		:= $(BINDIR)/verify
SRCS		:= $(shell find $(SRCDIR) -name '*.cpp')
HEADERS		:= $(shell find $(INCDIR) -name '*.h')
OBJECTS 	:= $(subst src,$(BUILDDIR),$(SRCS:%.cpp=%.o))

vpath $(SRCDIR)

arch		= i686-linux
CC		= clang-3.5
CXX		= clang++-3.5
LD		= clang++-3.5 
LDSO		= clang++-3.5 -shared
CFLAGS		= -std=c++11 -stdlib=libc++ -fPIC -Wall -Werror -Wextra -std=c++11 -g -g -Wno-deprecated
LDFLAGS		= -L/build/buildd/ruby1.9.1-1.9.3.484/debian/lib -L/var/lib/gems/1.9.1/gems/rice-1.7.0/ruby/lib/lib -lrice -lruby-1.9.1-static -lcrypt -ldl -pthread
DEFS		= 
INCFLAGS	= $(addprefix -I,$(INCDIR)) -I/usr/include/ruby-1.9.1/$(arch) -I/var/lib/gems/1.9.1/gems/rice-1.7.0/ruby/lib/include -I/usr/include/ruby-1.9.1/ruby/backward -I/usr/include/ruby-1.9.1

hdrdir 		= /usr/include/ruby-1.9.1
arch_hdrdir = /usr/include/ruby-1.9.1/$(arch)

DLLIB		 = $(TARGET).so

DIRGUARD	= @mkdir -p $(@D)

.PHONY: all clean

all: $(DLLIB)

$(BUILDDIR)/%.o: src/%.cpp
	$(DIRGUARD)
	$(CXX) $(DEFS) $(INCFLAGS) $(CFLAGS) -c $< -o $@

$(SRCS): $(HEADERS)

$(DLLIB): $(OBJECTS) Makefile
	$(ECHO) linking shared-object $(DLLIB)
	-$(Q)rm -f $(@)
	$(DIRGUARD)
	$(Q) $(LDSO) -o $@ $(OBJECTS) $(LDFLAGS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(DEFS) $(CFLAGS) $(INCFLAGS) -MM $^ -MF  ./.depend;

include .depend

clean:
	-rm -rf $(BINDIR) $(BUILDDIR)

distclean:: clean
