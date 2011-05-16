#makefile
  # IPB- 2009-..
  # Autor: Jaroslav Sendler, FIT
  # Prelozeno gcc 4.5.5
  #

# -v, -H, --version

PROGRAM=mining
PROJECT=MINING

OBJ=mining.o  transform.o 
SRC=mining.cc  transform.cc 
HEAD=transform.h connect.h

CCM=g++
CCMFLAGS=-std=c++98 -Wall -Wextra -pedantic -D_REENTRANT -lpthread -lgloox -lpcre -L/usr/lib/postgresql/8.4/lib/ -lpq #-dumpspecs
CPPFLAGS = -I/usr/include/postgresql/
CXXFLAGS +=  -Wextra -Wconversion -Wwrite-strings
CXXFLAGS += -W -Wall -ansi -pedantic -Wcast-align
CXXFLAGS += -Wcast-qual -Wchar-subscripts -Winline
CXXFLAGS += -Wpointer-arith -Wredundant-decls -Wshadow


all:  ${PROGRAM} clean

run:
	./${PROGRAM} 

${PROGRAM}: ${OBJ}
	$(CCM) ${OBJ} -o ${PROGRAM} $(CCMFLAGS) $(CPPFLAGS)

${OBJ}:${HEAD}

clean:
	rm -f *.o

clean-all:
	rm -f *.o ${PROGRAM}

delete:
	rm -f *.o ${PROGRAM} ${PROGRAM}.tar.gz ${PROGRAM}.zip

tar:
	tar -c ${SRC} ${HEAD} makefile dokumentace.pdf > ${PROJECT}.tar; \
	gzip ${PROJECT}.tar
zip:
	zip ${PROJECT} ${SRC} ${HEAD} makefile

help:
	@echo "dodelat"
