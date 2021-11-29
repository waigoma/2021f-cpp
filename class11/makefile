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

WORKDIR	=	class11

ARCHIVE =	$(WORKDIR).zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-(cd ..; $(ZIPCMD) $(ARCHIVE) $(WORKDIR)/*.cc $(WORKDIR)/*.h $(WORKDIR)/makefile)


clean:	
	-$(RM) $(TARGET) $(WEXECS) $(OBJS) $(ARCHIVE)

hanoi04-1:	hanoi04-1.o
hanoi04-2:	hanoi04-2.o Plate.o Pole.o Board.o
hanoi04-3:	hanoi04-3.o Plate.o Pole.o Board.o

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

