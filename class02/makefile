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


TARGET	=  ai01 countchar gen1gram gen2gram gen3gram

WEXECS	=	ex01.exe ex02.exe \
		ai01.exe countchar.exe gen1gram.exe gen2gram.exe gen3gram.exe

OBJS	=	ex01.o ex02.o \
		ai01.o countchar.o gen1gram.o gen2gram.o gen3gram.o

WORKDIR =	class02

ARCHIVE =	$(WORKDIR).zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-(cd ..; $(ZIPCMD) $(ARCHIVE) $(WORKDIR)/*.cc $(WORKDIR)/makefile)

clean:	
	-$(RM) $(TARGET) $(WEXECS) $(OBJS) $(ARCHIVE)

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

