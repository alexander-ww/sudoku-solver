all: sudoku_solve

sudoku_solve: main.o sudoku_solver.o sudoku_table.o
	g++ main.o sudoku_solver.o sudoku_table.o -o sudoku_solve

main.o: main.cpp sudoku_solver.h sudoku_table.h
	g++ -c main.cpp

sudoku_solver.o: sudoku_solver.cpp sudoku_solver.h
	g++ -c sudoku_solver.cpp

sudoku_table.o: sudoku_table.cpp sudoku_table.h
	g++ -c sudoku_table.cpp

clean:
	rm -f *.o
	rm -f sudoku_solve
