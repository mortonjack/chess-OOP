driver:
	@g++ -Wall -std=c++11 include/piece.cpp include/rook.cpp include/bishop.cpp include/knight.cpp include/pawn.cpp include/queen.cpp include/king.cpp include/movenode.cpp include/gameboard.cpp drivers/testcase.cpp drivers/piecetest.cpp drivers/driver.cpp drivers/bishoptest.cpp drivers/rooktest.cpp drivers/knighttest.cpp drivers/pawntest.cpp drivers/kingtest.cpp drivers/queentest.cpp drivers/capturetest.cpp drivers/collisiontest.cpp drivers/checktest.cpp drivers/checkmatetest.cpp drivers/movenodetest.cpp drivers/drawtest.cpp drivers/driver-test.cpp -o drivers/test.out

clear-drivers:
	@rm drivers/*.out