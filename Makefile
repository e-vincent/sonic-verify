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

CC		= gcc
CXX		= g++
LD		= g++
CFLAGS		= -Wall -pedantic -Werror -Wextra -std=c++11 -g -Wno-deprecated
LDFLAGS		= 
DEFS		= 
INCFLAGS	= $(addprefix -I,$(INCDIR))

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
