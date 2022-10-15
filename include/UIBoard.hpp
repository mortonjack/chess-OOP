#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Piece.h"
using namespace sf;

class UIBoard : public Drawable, public Transformable
{
    private:
        int _length;    // Board length
        int _width;     // Board width

        int _x;   // Board position (x)
        int _y;   // Board position (y)

        const Color _lightColor = Color{ 0xF5D5B5FF }; // Dark square color
        const Color _darkColor = Color{ 0xB58565FF };  // Light square color
        const Color _redColor = Color{ 0xD50000FF };   // Selected square color

        bool _sourceSelected = false;   // Whether or not a piece is seleted to move
        Vector2i _sourceCoords;         // The file and rank of the piece to move
        Vector2i _targetCoords;         // The file and rank of where the piece will move

        Sprite* _pieceSprites[32] = {nullptr}; // The piece sprites
        int _pieceCount = 0;             // The number of piece sprites to render

        VertexArray _vertices;           // The verticies of the game board

        // Converts a screen position into rank and file coordinates
        Vector2i position2coords(int x, int y) { 
            // The rank and file of the coordinates are 0 by default (to highlight any errors) 
            int file = -1;
            int rank = -1;

            // Calculate the furthest possible x and y distance between the screen position and a tile, and set these
            int minXDiff = _length;
            int minYDiff = _width;

            // Calculate the file the user is clicking
            for (int f = 0; f < 8; f++) {
                // Find the x-position of the current tile
                int tileX = getTileX(coords2TilePointer(Vector2i(f,0)));

                // Calculate the horizontal distance between the mouse and the tile
                int xDiff = abs(x - tileX);

                // If this distance is the smallest so far, store this value and the current file
                // This is the file that will be selected
                if (xDiff < minXDiff) {
                    minXDiff = xDiff;
                    file = f;
                }
            }

            // Calculate the rank the user is clicking
            for (int r = 0; r < 8; r++) {
                // Find the y-position of the current tile
                int tileY = getTileY(coords2TilePointer(Vector2i(0,r)));

                // Calculate the vertical distance between the mouse and the tile
                int yDiff = abs(y - tileY);

                // If this distance is the smallest so far, store this value and the current rank
                // This is the rank that will be selected
                if (yDiff < minYDiff) {
                    minYDiff = yDiff;
                    rank = r;
                }
            }

            // Return the file and rank closest to the passed screen position
            return Vector2i(file,rank);
        }

        // Converts file and rank coordinates into a screen positon
        Vector2f coords2Position(Vector2i coords) {
            // Get the pointer of the tile with the passed coordinates
            Vertex* tile = coords2TilePointer(coords);

            // Return the tile's screen position
            float vectorX = getTileX(tile);
            float vectorY = getTileY(tile);

            return Vector2f(vectorX, vectorY);
        }

        // Converts a piece object into its appropriate sprite
        Sprite* piece2Sprite(Piece* Piece) {
            Sprite* sprite = new Sprite;
            sprite->setTexture(*pieceName2Texture(Piece->getName()));
            sprite->setOrigin(32,32);
            return sprite;
        }

        // Returns a piece's image texture from its name
        Texture* pieceName2Texture(char name) {
            // Create a new texture to store the image data in
            Texture* texture = new Texture;

            // Select the appropriate piece and colour texture, based on the its name
            switch (name) {
                case 'P':
                    texture->loadFromFile("./assets/whitePawn.png");
                    break;

                case 'N':
                    texture->loadFromFile("./assets/whiteKnight.png");
                    break;

                case 'B':
                    texture->loadFromFile("./assets/whiteBishop.png");
                    break;

                case 'R':
                    texture->loadFromFile("./assets/whiteRook.png");
                    break;

                case 'Q':
                    texture->loadFromFile("./assets/whiteQueen.png");
                    break;

                case 'K':
                    texture->loadFromFile("./assets/whiteKing.png");
                    break;


                case 'p':
                    texture->loadFromFile("./assets/blackPawn.png");
                    break;

                case 'n':
                    texture->loadFromFile("./assets/blackKnight.png");
                    break;

                case 'b':
                    texture->loadFromFile("./assets/blackBishop.png");
                    break;

                case 'r':
                    texture->loadFromFile("./assets/blackRook.png");
                    break;

                case 'q':
                    texture->loadFromFile("./assets/blackQueen.png");
                    break;

                case 'k':
                    texture->loadFromFile("./assets/blackKing.png");
                    break;

            }

            // Return the texture, with the loaded image data
            return texture;
        }

        // Calculates the natural color of a tile, based on its rank and file
        Color coords2TileColor(Vector2i coords)  { return (coords.x + coords.y) % 2 == 0 ? _lightColor : _darkColor; }

        // Colors a tile a passed color
        void colorTile(Vector2i coords, Color color)  {
            Vertex* tile = coords2TilePointer(coords);
            tile[0].color = tile[1].color = tile[2].color = tile[3].color = color;
        }

        // Returns the central x-position of a tile, from its pointer
        float getTileX(Vertex* tile) { return (tile[0].position.x + tile[2].position.x) / 2; }

        // Returns the central y-position of a tile, from its pointer
        float getTileY(Vertex* tile) { return (tile[0].position.y + tile[2].position.y) / 2; }

        // Converts rank and file into a tile pointer
        Vertex* coords2TilePointer(Vector2i coords) { return &_vertices[(coords.x + coords.y * 8) * 4]; }
        
    public:
        // Constructor
        UIBoard(int length, int width, Vector2i offset) {
            // Store the dimensions of the board
            _length = length;
            _width = width;

            // Store the dimensions of each tile on the board
            int tileLength = length/8;
            int tileWidth = width/8;

            // Store the position of the board
            _x = offset.x;
            _y = offset.y;

            // Create an array of _vertices to store the board's points
            _vertices.setPrimitiveType(Quads);
            _vertices.resize(8 * 8 * 4);

            // Populate the vertex array, with four vertifies to a tile
            for (unsigned int file = 0; file < 8; ++file) {
                for (unsigned int rank = 0; rank < 8; ++rank)
                {
                    // Vectorise the rank and file
                    Vector2i coords = Vector2i(file,rank);

                    // Get a pointer to the current tile
                    Vertex* tile = coords2TilePointer(coords);

                    // Define the tile's four corners
                    tile[0].position = Vector2f(file * tileLength + _x, (7 - rank) * tileWidth + _y);
                    tile[1].position = Vector2f((file + 1) * tileLength + _x, (7 - rank) * tileWidth + _y);
                    tile[2].position = Vector2f((file + 1) * tileLength + _x, ((7 -rank) + 1) * tileWidth + _y);
                    tile[3].position = Vector2f(file * tileLength + _x, ((7 - rank) + 1) * tileWidth + _y);

                    // Color the tile light/dark depending on its positon
                    colorTile(coords, coords2TileColor(coords));
                }
            }
        }

        // Load the pieces on the gameboards as sprites on the UI
        void loadPieces(Gameboard* gameboard) {
            // Reset the piece counter
            _pieceCount = 0;

            // For every rank and file on the game board...
            for (int file = 0; file < 8; file++) {
                for (int rank = 0; rank < 8; rank++) {
                    // If the piece at the current position is not empty...
                    if (gameboard->getPiece(file,rank) != nullptr) {
                        // Load a sprite to represent the piece
                        Sprite* sprite = piece2Sprite(gameboard->getPiece(file,rank));
                        sprite->setPosition(coords2Position(Vector2i(file,rank)));

                        // Add the sprite to the array of piece sprites
                        _pieceSprites[_pieceCount] = sprite;
                        _pieceCount++;
                    }
                }
            }
        }

        // If a tile is clicked, select the piece on it. If it is clicked again, move the selected piece.
        bool tileClick(int x, int y) {
            // Convert the clicked position into file and rank
            Vector2i coords = position2coords(x,y);

            // If a piece is not selected, select it
            if (!_sourceSelected) {
                setSourceCoords(coords);
                return false;
            // Otherwise, select where the piece is to be move, and return that a move should be made
            } else {
                setTargetCoords(coords);
                return true;
            }

        }

        // Returns whether the board is hovered over
        bool isHovered(int x, int y) {
            return ((x > _x && x < _x + _length) && 
                    (y > _y && y < _y + _width));
        }

        // Returns the coordinates of the piece to be moved
        Vector2i getSourceCoords() { return _sourceCoords; }

        // Returns the coordinates of where the piece will be moved
        Vector2i getTargetCoords() { return _targetCoords; }

        // Sets the coordinates of the piece to be moved, handling the UI style appropriately
        void setSourceCoords(Vector2i coords) {
            // Indicate that a source tile has been selected
            _sourceSelected = true;

            // Store the clicked socation as the source coordiantes
            _sourceCoords = coords;

            // Color the tile red
            colorTile(_sourceCoords, _redColor);
        }

        // Sets the coordinates of where the piece will be moved, handling the UI style appropriatley
        void setTargetCoords(Vector2i coords) {
            // Indicate that a source tile is no longer selected
            _sourceSelected = false;

            _targetCoords = coords;

            // Remove the color of the previously selected tile
            colorTile(_sourceCoords, coords2TileColor(_sourceCoords));
        }

        // Draws the control
        virtual void draw(RenderTarget& target, RenderStates states) const {
            // Apply any transfoirmation
            states.transform *= getTransform();

            // Draw the board
            target.draw(_vertices, states);

            // Draw the piece sprites
            for (int i = 0; i < _pieceCount; i++) {
                if (_pieceSprites[i] != nullptr) target.draw(*_pieceSprites[i]);
            }
        }

        // Destroys the control and all its dynamically-allocated sprites
        ~UIBoard() {
            for (int i = 0; i < 32; i++) {
                if (_pieceSprites[i] != nullptr) delete _pieceSprites[i];
            }
        }

private:

};