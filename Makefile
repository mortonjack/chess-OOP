driver:
	@g++ -Wall -std=c++11 include/piece.cpp include/rook.cpp include/bishop.cpp include/knight.cpp include/pawn.cpp include/queen.cpp include/king.cpp include/boardnode.cpp include/gameboard.cpp drivers/testcase.cpp drivers/driver.cpp drivers/bishoptest.cpp drivers/rooktest.cpp drivers/knighttest.cpp drivers/pawntest.cpp drivers/kingtest.cpp drivers/queentest.cpp drivers/capturetest.cpp drivers/collisiontest.cpp drivers/checktest.cpp drivers/checkmatetest.cpp drivers/boardnodetest.cpp drivers/drawtest.cpp drivers/driver-test.cpp -o drivers/test.out

rank-and-file-driver:
	@g++ -Wall -std=c++11 include/piece.cpp include/pawn.cpp include/knight.cpp include/bishop.cpp include/rook.cpp include/queen.cpp include/king.cpp include/gameboard.cpp drivers/example-board-setup.cpp -o drivers/rankFileTest.out

ui-driver:
	@g++ -Wall -std=c++11 UI-versions/uitest.cpp -lsfml-graphics -lsfml-window -lsfml-system -o drivers/test.out

clear-drivers:
	@rm drivers/*.out