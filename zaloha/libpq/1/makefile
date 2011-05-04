#makefile
  # IPB- 2009-..
  # Autor: Jaroslav Sendler, FIT
  # Prelozeno gcc 4.5.5
  #

# -v, -H, --version

PROGRAM=data
PROJECT=data

OBJ=data.o
SRC=data.cc
#HEAD=

CCM=g++
CCMFLAGS=-std=c++98 -Wall -pedantic -L/usr/lib/postgresql/8.4/lib/ -lpq
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
