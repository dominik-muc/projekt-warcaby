EXE?=test_main
TARGET=$(BUILDDIR)/$(EXE)

SRCDIR=src
BUILDDIR=_build
$(shell mkdir -p $(BUILDDIR))

SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
DEP=$(SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.d)

NCURSES_LIB?=ncurses
NCURSES_CFLAGS?=`pkg-config --cflags $(NCURSES_LIB)`
NCURSES_LDLIBS?=`pkg-config --libs $(NCURSES_LIB)`

CFLAGS?=-Wall -Wextra -pedantic -std=c++20 -O2 -march=native -D_GNU_SOURCE $(NCURSES_CFLAGS)
LDLIBS?=$(NCURSES_LDLIBS)

PREFIX?=/usr/local
BINDIR?=$(PREFIX)/bin


.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDLIBS)

%.o : %.cpp

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(BUILDDIR)/%.d
	$(CC) -MM $< -MQ $(BUILDDIR)/$*.o -MF $(BUILDDIR)/$*.d
	$(CC) -c $(CFLAGS) $< -o $@

%.d: ;

-include $(DEP)


clean:
	@-rm -r $(BUILDDIR)

install: $(TARGET)
	install -m 755 $(TARGET) $(BINDIR)

uninstall:
	rm $(BINDIR)/$(EXE)
