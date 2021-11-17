#
#	makefile : week 09
#

CXX		=	g++
CXXFLAGS	=	$(CXXINCLUDE) $(DEBUG)
CXXINCLUDE	=
## DEBUG		=
DEBUG		=	-g
ZIPCMD		=	zip


TARGET		=	hanoi02-1 hanoi02-2 hanoi02-2e \
			hanoi02-3c hanoi02-3n

WEXECS		=	hanoi02-1.exe hanoi02-2.exe hanoi02-2e.exe \
			hanoi02-3c.exe hanoi02-3n.exe

OBJS		=	hanoi02-1.o hanoi02-2.o hanoi02-2e.o \
			hanoi02-3c.o hanoi02-3n.o

WORKDIR		=	class09

ARCHIVE		=	class09.zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-(cd ..; $(ZIPCMD) $(ARCHIVE) $(WORKDIR)/*.cc $(WORKDIR)/*.h $(WORKDIR)/makefile)

clean:	
	-$(RM) $(TARGET) $(WEXECS) $(ARCHIVE)

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

