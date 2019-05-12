all:
	cd build ; qmake ../src/ChessApp.pro ; make ; mv ChessApp chess
clean:
	cd build ; make clean
doxygen:
	cd doc ; doxygen
run:
	cd build ; ./chess
