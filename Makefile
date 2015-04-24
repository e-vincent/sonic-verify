# V=0 quiet, V=1 verbose.  other values don't work.
V  	  = 0
Q1	  = $(V:1=)
Q  	  = $(Q1:0=@)
n 	  = $(NULLCMD)
ECHO1 = $(V:1=@$n)
ECHO  = $(ECHO1:0=@echo)

LIBMODS		:=
MODULES		:=
SRCDIR		:= src $(addprefix src/,$(MODULES))
RUBYINC		:= $(shell ruby -rrbconfig -e 'print RbConfig::CONFIG["rubyhdrdir"]')
RUBYARCHINC	:= $(shell ruby -rrbconfig -e 'print RbConfig::CONFIG["rubyarchhdrdir"]')
RICEINC		:= $(shell ruby -e "print File.join(Gem::Specification.find_by_name('rice').gem_dir, 'ruby/lib/include')")
INCDIR		:= include $(RUBYINC) $(RUBYINC)/ruby/backward $(RUBYARCHINC) $(RICEINC)
BINDIR		:= bin
BUILDDIR	:= build
BINMODS		:= $(addprefix bin/,$(MODULES))
TARGET		:= $(BINDIR)/verify
SRCS		:= $(shell find $(SRCDIR) -name '*.cpp')
HEADERS		:= $(shell find $(INCDIR) -name '*.h')
OBJECTS 	:= $(subst src,$(BUILDDIR),$(SRCS:%.cpp=%.o))
RUBYLIBDIR	:= $(shell ruby -rrbconfig -e 'print RbConfig::CONFIG["rubylibdir"]')
RUBYLIB		:= $(shell ruby -rrbconfig -e 'print RbConfig::CONFIG["LIBRUBYARG_STATIC"]')
RICELIBDIR	:= $(shell ruby -e "print File.join(Gem::Specification.find_by_name('rice').gem_dir, 'ruby/lib/lib')")

vpath $(SRCDIR)

arch		= i686-linux
CC		= clang-3.5
CXX		= clang++-3.5
LD		= clang++-3.5 
LDSO		= clang++-3.5 -shared
CFLAGS		= -fPIC -Wall -Werror -Wextra -std=c++11 -g -g -Wno-deprecated
LDFLAGS		= -L$(RUBYLIBDIR) -L$(RICELIBDIR) -lrice $(RUBYLIB) -lcrypt -ldl -pthread
DEFS		= 
INCFLAGS	= $(addprefix -I,$(INCDIR))

DLLIB		= $(TARGET).so

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
