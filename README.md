# chess-OOP
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![Visual Studio Code](https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white)

Two-player chess.

# Installation instructions
1. Install [SFML](https://www.sfml-dev.org/index.php).
2. Run `make` to compile and run the program.
3. Afterwards, run chess.out to play.

# How to play
Click on a tile to select a piece, then click elsewhere to select a destination. If you click on an
invalid tile, you will be able to select a different piece. White goes first, then players take it
in turns. The game ends when either:
 - The current player has no legal moves (checkmate/stalemate)
 - Fifty moves have passed without any pieces being taken or pawns being moved up (draw, fifty move rule)
 - The same board position has appeared three different times (draw, threefold repetition)
 - One player resigns
 - Both players agree to draw

If you close the program before finishing the game, you can continue where you left off by clicking "load". 
You can also click "save" before you close the program. If you don't do this, the game will attempt to
automatically save your game.

If you've never played chess before, check out [this article](https://www.chess.com/learn-how-to-play-chess).
