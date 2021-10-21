#
#	makefile
#

CXX		=	g++
CXXFLAGS	=	$(CXXINCLUDE) $(DEBUG)
CXXINCLUDE	=
LINK.o		=	$(LINK.cc)
LDLIBS		=
## LDLIBS		=	-lncurses
LOADLIBS	=
DEBUG		=
DEBUG		=	-g
ZIPCMD		=	zip


TARGET		=	genngram sentence_gen ai02

WEXECS		=	genngram.exe sentence_gen.exe ai02.exe

OBJS		=	utf8.o genngram.o sentence_gen.o ai02.o

WORKDIR		=       class05

ARCHIVE		=       $(WORKDIR).zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-(cd ..; $(ZIPCMD) $(ARCHIVE) $(WORKDIR)/*.cc $(WORKDIR)/*.h $(WORKDIR)/*.txt $(WORKDIR)/makefile)

clean:	
	-$(RM) $(TARGET) $(WEXECS) $(OBJS) $(ARCHIVE)

genngram:	genngram.o utf8.o
sentence_gen:	sentence_gen.o utf8.o
ai02:		ai02.o utf8.o

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

