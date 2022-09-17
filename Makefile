skeleton-driver:
	@g++ include/piece.cpp include/gameboard.cpp drivers/skeleton-gameboard.cpp -o drivers/moveTest.out

first-movement-driver:
	@g++ include/piece.cpp include/rook.cpp include/gameboard.cpp drivers/first-piece-movement.cpp -o drivers/moveTest.out

rook-bishop-driver:
	@g++ include/piece.cpp include/rook.cpp include/bishop.cpp include/gameboard.cpp drivers/rook-bishop-movement.cpp -o drivers/rookBishopTest.out

queen-driver:
	@g++ include/piece.cpp include/queen.cpp include/gameboard.cpp drivers/queen-movement.cpp -o drivers/queenTest.out

knight-driver:
	@g++ include/piece.cpp include/knight.cpp include/gameboard.cpp drivers/knight-movement.cpp -o drivers/knightTest.out

king-driver:
	@g++ include/piece.cpp include/king.cpp include/gameboard.cpp drivers/king-movement.cpp -o drivers/kingTest.out

pawn-driver:
	@g++ include/piece.cpp include/pawn.cpp include/gameboard.cpp drivers/pawn-movement.cpp -o drivers/pawnTest.out