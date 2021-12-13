#
#	makefile
#

CXX		=	g++ -std=c++14
CXXFLAGS	=	$(CXXINCLUDE) $(DEBUG)
CXXINCLUDE	=
LINK.o		=	$(LINK.cc)
LDLIBS		=	-lncurses
LOADLIBS	=
DEBUG		=
DEBUG		=	-g
ZIPCMD		=	zip


TARGET	=	hanoi06-1s hanoi06-1c

WEXECS	=	hanoi06-1s.exe hanoi06-1c.exe

OBJS	=	hanoi06-1s.o hanoi06-1c.o STerminal.o CTerminal.o \
		Plate.o Pole.o Board.o

WORKDIR	=	class13

ARCHIVE =	$(WORKDIR).zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-(cd ..; $(ZIPCMD) $(ARCHIVE) $(WORKDIR)/*.cc $(WORKDIR)/*.h $(WORKDIR)/makefile)

clean:	
	-$(RM) $(TARGET) $(WEXECS) $(OBJS) $(ARCHIVE)

hanoi06-1c:	hanoi06-1c.o CTerminal.o Plate.o Pole.o Board.o
hanoi06-1s:	hanoi06-1s.o CTerminal.o Plate.o Pole.o Board.o

CTerminal.o:	CTerminal.cc CTerminal.h
STerminal.o:	STerminal.cc STerminal.h
Plate.o:	Plate.cc Plate.h
Pole.o:		Pole.cc Pole.h
Board.o:	Board.cc Board.h

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

