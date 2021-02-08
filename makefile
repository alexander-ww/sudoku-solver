all: sudoku_solve

sudoku_solve: main.o SingleBox.o Pair.o NineBox.o SudokuTable.o
	g++ main.o SingleBox.o Pair.o NineBox.o SudokuTable.o -o sudoku_solve

main.o: main.cpp SingleBox.h NineBox.h SudokuTable.h
	g++ -c main.cpp

SingleBox.o: SingleBox.cpp SingleBox.h
	g++ -c SingleBox.cpp

Pair.o: Pair.cpp Pair.h
	g++ -c Pair.cpp

NineBox.o: NineBox.cpp NineBox.h
	g++ -c NineBox.cpp

SudokuTable.o: SudokuTable.cpp SudokuTable.h
	g++ -c SudokuTable.cpp

clean:
	rm -f *.o
	rm -f sudoku_solve
