skeleton-driver:
	@g++ include/piece.cpp include/gameboard.cpp drivers/skeleton-gameboard.cpp -o drivers/moveTest.out

first-movement-driver:
	@g++ include/piece.cpp include/rook.cpp include/gameboard.cpp drivers/first-piece-movement.cpp -o drivers/moveTest.out