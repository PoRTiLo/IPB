#makefile
  # IPB- 2009-..
  # Autor: Jaroslav Sendler, FIT
  # Prelozeno gcc 4.5.5
  #

# -v, -H, --version

PROJECT=DOC

HTML = ./html/*.* ./html/search/*.* ./html/installdox
LATEX = ./latex/*.* ./latex/Makefile

all:  run

run:
	doxygen Doxyfile

clean: clean-di


clean-di: clean-file
	rmdir ./html/search/

clean-file:
	rm -f ${HTML} ${LATEX}

clean-all: clean
	rm -f ${PROJECT}.zip ${PROJECT}.tar.gz

tar:
	tar -c ${HTML} ${LATEX} makefile Doxyfile > ${PROJECT}.tar; \
	gzip ${PROJECT}.tar
zip:
	zip ${PROJECT} ${HTML} ${LATEX} makefile Doxyfile

help:
	@echo ":)"
