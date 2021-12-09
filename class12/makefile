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


TARGET	=	hanoi05-1 hanoi05-2 hanoi05-3 hanoi05-4

WEXECS	=	hanoi05-1.exe hanoi05-2.exe hanoi05-3.exe hanoi05-4.exe

OBJS	=	hanoi05-1.o hanoi05-2.o hanoi05-3.o hanoi05-4.o \
		Plate.o Pole.o Board.o

WORKDIR	=	class12

ARCHIVE =	$(WORKDIR).zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-(cd ..; $(ZIPCMD) $(ARCHIVE) $(WORKDIR)/*.cc $(WORKDIR)/*.h $(WORKDIR)/makefile)

clean:	
	-$(RM) $(TARGET) $(WEXECS) $(OBJS) $(ARCHIVE)

hanoi05-1:	hanoi05-1.o Plate.o Pole.o Board.o
hanoi05-2:	hanoi05-2.o Plate.o Pole.o Board.o
hanoi05-3:	hanoi05-3.o Plate.o Pole.o Board.o
hanoi05-4:	hanoi05-4.o Plate.o Pole.o Board.o
Board.o:	Board.cc Board.h
Pole.o:		Pole.cc Pole.h
Plate.o:	Plate.cc Plate.h

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

