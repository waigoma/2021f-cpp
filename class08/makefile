#
#	makefile : week 08
#

CXX		=	g++
CXXFLAGS	=	$(CXXINCLUDE) $(DEBUG)
CXXINCLUDE	=
## DEBUG		=
DEBUG		=	-g
ZIPCMD		=	zip


TARGET		=	hanoi01-1 hanoi01-2 hanoi01-3 \
			hanoi01-4 hanoi01-5 hanoi01-6

WEXECS		=	hanoi01-1.exe hanoi01-2.exe hanoi01-3.exe \
			hanoi01-4.exe hanoi01-5.exe hanoi01-6.exe

OBJS		=	hanoi01-1.o hanoi01-2.o hanoi01-3.o \
			hanoi01-4.o hanoi01-5.o hanoi01-6.o

WORKDIR		=	class08

ARCHIVE		=	$(WORKDIR).zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-(cd ..; $(ZIPCMD) $(ARCHIVE) $(WORKDIR)/*.cc $(WORKDIR)/*.h $(WORKDIR)/makefile)

clean:	
	-$(RM) $(TARGET) $(WEXECS) $(OBJS)

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

