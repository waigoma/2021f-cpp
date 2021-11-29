#
#	makefile
#

CXX		=	g++
CXXFLAGS	=	$(CXXINCLUDE) $(DEBUG)
CXXINCLUDE	=
LINK.o		=	$(LINK.cc)
LDLIBS		=	-lncurses
LOADLIBS	=
DEBUG		=
DEBUG		=	-g
ZIPCMD	=	zip


TARGET	=	hanoi04-1 hanoi04-2 hanoi04-3

WEXECS	=	hanoi04-1.exe hanoi04-2.exe hanoi04-3.exe

OBJS	=	hanoi04-1.o hanoi04-2.o hanoi04-3.o Plate.o Pole.o Board.o

ZIP_SRC =	hanoi04-1.cc hanoi04-2.cc hanoi04-3.cc \
		Plate.h Plate.cc Pole.h Pole.cc Board.h Board.cc makefile

ARCHIVE =	class11.zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-$(ZIPCMD) $(ARCHIVE) $(ZIP_SRC)

clean:	
	-$(RM) $(TARGET) $(WEXECS) $(OBJS) $(ARCHIVE)

05-hanoi01:	05-hanoi01.o
05-hanoi02:	05-hanoi02.o Plate.o Pole.o Board.o
05-hanoi03:	05-hanoi03.o Plate.o Pole.o Board.o

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

