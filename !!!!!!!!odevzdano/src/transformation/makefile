#makefile
  # IPB- 2009-..
  # Autor: Jaroslav Sendler, FIT
  # Prelozeno gcc 4.5.5
  #

# -v, -H, --version

PROGRAM=transformation
PROJECT=TRANSFORMATION
sfx	= cc

SRC=transformation.cc

#CCM=g++
CXX=g++
#CCMFLAGS= -Wall -Wextra -pedantic -D_REENTRANT -Wconversion
CXXFLAGS +=  -Wextra -Wconversion -Wwrite-strings
CXXFLAGS += -W -Wall -ansi -pedantic -Wcast-align
CXXFLAGS += -Wcast-qual -Wchar-subscripts -Winline
CXXFLAGS += -Wpointer-arith -Wredundant-decls -Wshadow

all:  ${PROGRAM} clean

run:
	./${PROGRAM} 

${PROGRAM}: ${PROGRAM}.${sfx}
#	$(CCM) ${OBJ} -o ${PROGRAM} $(CCMFLAGS)
	$(CXX) ${CXXFLAGS} -o  ${PROGRAM} ${PROGRAM}.${sfx}

clean:
	rm -f *.o

clean-all:
	rm -f *.o ${PROGRAM}

delete:
	rm -f *.o ${PROGRAM} ${PROGRAM}.tar.gz ${PROGRAM}.zip

tar:
	tar -c ${SRC} ${HEAD} makefile > ${PROJECT}.tar; \
	gzip ${PROJECT}.tar
zip:
	zip ${PROJECT} ${SRC} ${HEAD} makefile

help:
	@echo ""
