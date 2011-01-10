#makefile
  # IPB- 2009-..
  # Autor: Jaroslav Sendler, FIT
  # Prelozeno gcc 4.5.5
  #

# -v, -H, --version

PROGRAM=db
PROJECT=db

OBJ=db.o
SRC=db.cc
#HEAD=

CCM=g++
CCMFLAGS=-std=c++98 -Wall -pedantic -lmysqlclient

all:  ${PROGRAM} clean

run:
	./${PROGRAM} 

${PROGRAM}: ${OBJ}
	$(CCM) ${OBJ} -o ${PROGRAM} $(CCMFLAGS)

${OBJ}:${HEAD}

clean: 
	rm -f *.o

delete:
	rm -f *.o ${PROGRAM} ${PROGRAM}.tar.gz ${PROGRAM}.zip

tar:
	tar -c ${SRC} ${HEAD} makefile dokumentace.pdf > ${PROJECT}.tar; \
	gzip ${PROJECT}.tar
