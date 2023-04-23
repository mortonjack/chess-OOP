CXX := g++
CXXFLAGS := -std=c++11 -O3
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

# Default compilation
default: main.cpp main.cpp include/Piece.o include/Rook.o include/Bishop.o include/Knight.o include/Pawn.o include/Queen.o include/King.o include/MoveNode.o include/State.o include/Gameboard.o
	@$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o chess.out
	@./chess.out

# Compile & run test file
driver: include/Piece.o include/Rook.o include/Bishop.o include/Knight.o include/Pawn.o include/Queen.o include/King.o include/MoveNode.o include/State.o include/Gameboard.o drivers/TestCase.o drivers/PieceTest.o drivers/Driver.o drivers/BishopTest.o drivers/RookTest.o drivers/KnightTest.o drivers/PawnTest.o drivers/KingTest.o drivers/QueenTest.o drivers/CaptureTest.o drivers/CollisionTest.o drivers/CheckTest.o drivers/CheckmateTest.o drivers/MoveNodeTest.o drivers/DrawTest.o drivers/SaveTest.o drivers/DriverTest.cpp
	@$(CXX) $(CXXFLAGS) -Wall -Werror $^ -o drivers/test.out
	@./drivers/test.out

# Compilation rule for *.o
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove compiled files
clean:
	@rm -f chess.out drivers/*.out drivers/*.o

.PHONY: default driver clean