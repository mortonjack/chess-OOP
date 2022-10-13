driver:
	@g++ -Wall -std=c++11 include/Piece.cpp include/Rook.cpp include/Bishop.cpp include/Knight.cpp include/Pawn.cpp include/Queen.cpp include/King.cpp include/MoveNode.cpp include/Gameboard.cpp drivers/TestCase.cpp drivers/PieceTest.cpp drivers/Driver.cpp drivers/BishopTest.cpp drivers/RookTest.cpp drivers/KnightTest.cpp drivers/PawnTest.cpp drivers/KingTest.cpp drivers/QueenTest.cpp drivers/CaptureTest.cpp drivers/CollisionTest.cpp drivers/CheckTest.cpp drivers/CheckmateTest.cpp drivers/MoveNodeTest.cpp drivers/DrawTest.cpp drivers/DriverTest.cpp -o drivers/test.out
	@./drivers/test.out

ui-driver:
	@g++ -Wall -std=c++11 main.cpp -std=c++11 include/Piece.cpp include/Rook.cpp include/Bishop.cpp include/Knight.cpp include/Pawn.cpp include/Queen.cpp include/King.cpp include/MoveNode.cpp include/Gameboard.cpp -lsfml-graphics -lsfml-window -lsfml-system -o drivers/test.out
	@./drivers/test.out

clear-drivers:
	@rm drivers/*.out