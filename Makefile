CC = g++

# Folders
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin

# Targets
EXECUTABLE := libcomm
TARGET := $(TARGETDIR)/$(EXECUTABLE)

# Final Paths
INSTALLBINDIR := /usr/local/bin

# Code Lists
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Folder Lists
INCDIRS := $(shell find src/**/* -name '*.h' -exec dirname {} \; | sort | uniq)
INCLIST := $(patsubst src/%,-I src/%,$(INCDIRS))
BUILDLIST := $(patsubst src/%,$(BUILDDIR)/%,$(INCDIRS))

# Shared Compiler Flags
CFLAGS := -std=c++14 -O3 -Wall -Wextra
INC := -I include $(INCLIST) -I /usr/local/include
LIB := -lm -lrt

ifeq ($(debug), 1)
CFLAGS += -g
else
CFLAGS += -DNDEBUG
endif

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo  "${P}Linking all targets...${N}"
	@$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDLIST)
	@echo "${Y}Compiling${N} ${B}$< ${N}"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "${R}Cleaning $(TARGET)${N}"; $(RM) -r $(BUILDDIR) $(TARGETDIR)

install:
	@echo "${R}Installing ${N} ${B} $(EXECUTABLE) ${N}"; cp $(TARGET) $(INSTALLBINDIR)

distclean:
	@echo "${R}Removing ${N} ${B} $(EXECUTABLE) ${N}"; rm $(INSTALLBINDIR)/$(EXECUTABLE)

run:
	${TARGET}

.PHONY: clean
