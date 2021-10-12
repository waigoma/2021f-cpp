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


TARGET	=	ex04 utf8_test2 \
		genngram mycount mynsort

WEXECS	=	ex04.exe utf8_test2.exe \
		genngram.exe mysort.exe mycount.exe mynsort.exe

OBJS	=	ex04.o utf8_test2.o utf8.o \
		genngram.o mysort.o mycount.o mynsort.o

WORKDIR =       class04

ARCHIVE =       $(WORKDIR).zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-(cd ..; $(ZIPCMD) $(ARCHIVE) $(WORKDIR)/*.cc $(WORKDIR)/*.h $(WORKDIR)/makefile)

clean:	
	-$(RM) $(TARGET) $(WEXECS) $(OBJS)

ex04:		ex04.o
utf8_test2:	utf8_test2.o utf8.o
genngram:	genngram.o utf8.o
mysort:		utf8.o
mycount:	mycount.o utf8.o
mynsort:	mynsort.o utf8.o

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

