all:
	(cd timerLib; make install)
	(cd lcdLib; make install)
	(cd shapeLib; make install)
	(cd p2swLib; make install)


clean:
	(cd timerLib; make clean)
	(cd src; make clean)
	(cd shapeLib; make clean)
	(cd p2swLib; make clean)

	rm -rf lib h
