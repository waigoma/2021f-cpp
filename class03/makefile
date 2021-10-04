#
#	makefile
#

CXX		=	g++
CXXFLAGS	=	$(CXXINCLUDE) $(DEBUG)
CXXINCLUDE	=
LINK.o		=	$(LINK.cc)
LDLIBS		=
LDLIBS		=
LOADLIBS	=
DEBUG		=
DEBUG		=	-g
ZIPCMD		=	zip


TARGET	=	countchar2 gen1gram2 gen2gram2 genngram

WEXECS	=	utf8_test.exe \
		countchar2.exe gen1gram2.exe gen2gram2.exe genngram.exe

OBJS	=	utf8.o \
		utf8_test.o \
		countchar2.o gen1gram2.o gen2gram2.o genngram.o

WORKDIR =	class03

ARCHIVE =	$(WORKDIR).zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-(cd ..; $(ZIPCMD) $(ARCHIVE) $(WORKDIR)/*.cc $(WORKDIR)/*.h $(WORKDIR)/makefile)

clean:	
	-$(RM) $(TARGET) $(WEXECS) $(OBJS) $(ARCHIVE)

utf8_test:	utf8_test.o utf8.o
gen1gram2:	gen1gram2.o utf8.o
gen2gram2:	gen2gram2.o utf8.o
genngram:	genngram.o utf8.o

countchar2.o:	countchar2.cc
gen1gram2.o:	gen1gram2.cc utf8.h
gen2gram2.o:	gen2gram2.cc utf8.h
genngram.o:	genngram.cc utf8.h
utf8.o:		utf8.cc utf8.h

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

