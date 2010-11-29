#makefile
  # IPB- 2009-..
  # Autor: Jaroslav Sendler, FIT
  # Prelozeno gcc 4.5.5
  #

# -v, -H, --version

PROGRAM=ipb
PROJECT=IPB

OBJ=main.o bot.o param.o errors.o database.o 
SRC=main.cc bot.cc param.cc errors.cc database.cc
HEAD=bot.h param.h errors.h database.h

CCM=g++
CCMFLAGS=-std=c++98 -Wall -pedantic -lncurses -lgloox -lpthread -lpcre -L/usr/lib/postgresql/8.4/lib/ -lpq#-dumpspecs
CPPFLAGS = -I/usr/include/postgresql/

all:  ${PROGRAM} clean

run:
	./${PROGRAM} 

${PROGRAM}: ${OBJ}
	$(CCM) ${OBJ} -o ${PROGRAM} $(CCMFLAGS) $(CPPFLAGS)

${OBJ}:${HEAD}

clean: 
	rm -f *.o

delete:
	rm -f *.o ${PROGRAM} ${PROGRAM}.tar.gz ${PROGRAM}.zip

tar:
	tar -c ${SRC} ${HEAD} makefile dokumentace.pdf > ${PROJECT}.tar; \
	gzip ${PROJECT}.tar
