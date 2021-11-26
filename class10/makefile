#
#	makefile
#

CXX		=	g++
CXXFLAGS	=	$(CXXINCLUDE) $(DEBUG)
CXXINCLUDE	=
LINK.o		=	$(LINK.cc)
LDLIBS		=
LOADLIBS	=
DEBUG		=
DEBUG		=	-g
ZIPCMD	=	zip


TARGET	=	hanoi03-1c hanoi03-1n hanoi03-2c hanoi03-2n \
		hanoi03-3 hanoi03-4

WEXECS	=	hanoi03-1c.exe hanoi03-1n.exe hanoi03-2c.exe hanoi03-2n.exe \
		hanoi03-3.exe hanoi03-4.exe

OBJS	=	hanoi03-1n.o hanoi03-1c.o hanoi03-2n.o hanoi03-2c.o \
		hanoi03-3.o hanoi03-4.o

ZIP_SRC =	hanoi03-1n.h hanoi03-1n.cc hanoi03-1c.h hanoi03-1c.cc \
		hanoi03-2n.cc hanoi03-2c.cc \
		Plate.h Plate.cc Board.h Board.cc Pole.h Pole.cc \
		hanoi03-3.h hanoi03-3.cc hanoi03-4.h hanoi03-4.cc

ARCHIVE =	class04.zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-$(ZIPCMD) $(ARCHIVE) $(ZIP_SRC)

clean:	
	-$(RM) $(TARGET) $(WEXECS) $(OBJS) $(ARCHIVE)

hanoi03-1n:	hanoi03-1n.o
hanoi03-1c:	hanoi03-1c.o
hanoi03-2n:	hanoi03-2n.o Plate.o Pole.o Board.o
hanoi03-2c:	hanoi03-2c.o Plate.o Pole.o Board.o
hanoi03-3:	hanoi03-3.o
hanoi03-4:	hanoi03-4.o

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

