first-movement-driver:
	@g++ -Wall -std=c++11 include/piece.cpp include/rook.cpp include/gameboard.cpp drivers/first-piece-movement.cpp -o drivers/moveTest.out

rook-bishop-driver:
	@g++ -Wall -std=c++11 include/piece.cpp include/rook.cpp include/bishop.cpp include/gameboard.cpp drivers/rook-bishop-movement.cpp -o drivers/rookBishopTest.out

queen-driver:
	@g++ -Wall -std=c++11 include/piece.cpp include/queen.cpp include/gameboard.cpp drivers/queen-movement.cpp -o drivers/queenTest.out

knight-driver:
	@g++ -Wall -std=c++11 include/piece.cpp include/knight.cpp include/gameboard.cpp drivers/knight-movement.cpp -o drivers/knightTest.out

king-driver:
	@g++ -Wall -std=c++11 include/piece.cpp include/king.cpp include/gameboard.cpp drivers/king-movement.cpp -o drivers/kingTest.out

pawn-driver:
	@g++ -Wall -std=c++11 include/piece.cpp include/pawn.cpp include/gameboard.cpp drivers/pawn-movement.cpp -o drivers/pawnTest.out

piece-drivers:
	@make rook-bishop-driver queen-driver knight-driver king-driver pawn-driver

capture-driver:
	@g++ -Wall -std=c++11 include/piece.cpp include/pawn.cpp include/rook.cpp include/knight.cpp include/bishop.cpp include/queen.cpp include/king.cpp include/gameboard.cpp drivers/capture.cpp -o drivers/captureTest.out

rank-and-file-driver:
	@g++ -Wall -std=c++11 include/gameboard.cpp include/piece.cpp include/pawn.cpp include/knight.cpp include/bishop.cpp include/rook.cpp include/queen.cpp include/king.cpp drivers/example-board-setup.cpp -o drivers/rankFileTest.out

vertical-collision-driver:
	@g++ -Wall -std=c++11 include/piece.cpp include/pawn.cpp include/rook.cpp include/gameboard.cpp drivers/vertical-collision-detection.cpp -o drivers/verticalCollisionTest.out	

collision-driver:
	@g++ -Wall -std=c++11 include/gameboard.cpp include/piece.cpp include/pawn.cpp include/knight.cpp include/bishop.cpp include/rook.cpp include/queen.cpp include/king.cpp drivers/collision-detection.cpp -o drivers/collisionTest.out

clear-drivers:
	@rm drivers/*.out