#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Piece.h"
using namespace sf;

class UIBoard : public Drawable, public Transformable
{
    private:
        // Board size constants
        int _length;
        int _width;

        // Color constants
        const Color _whiteColor = Color{ 0xF5F5F5FF };
        const Color _blackColor = Color{ 0x454545FF };
        const Color _lightColor = Color{ 0xF5D5B5FF };
        const Color _darkColor = Color{ 0xB58565FF };
        const Color _redColor = Color{ 0xD50000FF };

        // Piece moving variables
        bool _sourceSelected = false;
        Vector2i _sourceCoords;
        Vector2i _targetCoords;

        Sprite* pieces[32] = {nullptr};
        int pieceCount = 0;

        // Define board vertices
        VertexArray vertices;

    public:
        UIBoard(int length, int width, Vector2i offset) {
            _length = length;
            _width = width;

            int _tileLength = length/8;
            int _tileWidth = width/8;

            int offsetX = offset.x;
            int offsetY = offset.y;

            // resize the vertex array to fit the level size
            vertices.setPrimitiveType(Quads);
            vertices.resize(8 * 8 * 4);

            // populate the vertex array, with one tile per tile
            for (unsigned int file = 0; file < 8; ++file) {
                for (unsigned int rank = 0; rank < 8; ++rank)
                {
                    // Vectorise the rank and file
                    Vector2i coords = Vector2i(file,rank);

                    // get a pointer to the current tile's tile
                    Vertex* tile = coords2TilePointer(coords);

                    // define its 4 corners
                    tile[0].position = Vector2f(file * _tileLength + offsetX, (7 - rank) * _tileWidth + offsetY);
                    tile[1].position = Vector2f((file + 1) * _tileLength + offsetX, (7 - rank) * _tileWidth + offsetY);
                    tile[2].position = Vector2f((file + 1) * _tileLength + offsetX, ((7 -rank) + 1) * _tileWidth + offsetY);
                    tile[3].position = Vector2f(file * _tileLength + offsetX, ((7 - rank) + 1) * _tileWidth + offsetY);

                    // Determine whether the square is light or dark
                    colorTile(coords, coords2TileColor(coords));
                }
            }
        }

        bool loadPieces(Gameboard* gameboard) {
            pieceCount = 0;

            for (int file = 0; file < 8; file++) {
                for (int rank = 0; rank < 8; rank++) {
                    if (gameboard->getPiece(file,rank) != nullptr) {
                        Sprite* sprite = piece2Sprite(gameboard->getPiece(file,rank));
                        sprite->setPosition(coords2Position(Vector2i(file,rank)));

                        pieces[pieceCount] = sprite;
                        pieceCount++;
                    }
                }
            }

            return true;
        }

        bool tileClick(int x, int y) {
            Vector2i coords = position2coords(x,y);

            if (!_sourceSelected) {
                setSourceCoords(coords);
                return false;
            } else {
                setTargetCoords(coords);
                return true;
            }

        }

        Vector2i getSourceCoords() { return _sourceCoords; }
        Vector2i getTargetCoords() { return _targetCoords; }

        void setSourceCoords(Vector2i coords) {
            // Indicate that a source tile has been selected
            _sourceSelected = true;

            // Store the clicked socation as the source coordiantes
            _sourceCoords = coords;

            // Color the tile red
            colorTile(_sourceCoords, _redColor);
        }
        void setTargetCoords(Vector2i coords) {
            // Indicate that a source tile is no longer selected
            _sourceSelected = false;

            _targetCoords = coords;

            // Remove the color of the previously selected tile
            colorTile(_sourceCoords, coords2TileColor(_sourceCoords));
        }

    private:
        Sprite* piece2Sprite(Piece* Piece) {
            Sprite* sprite = new Sprite;
            sprite->setTexture(*pieceName2Texture(Piece->getName()));
            sprite->setOrigin(32,32);
            return sprite;
        }

        // POSITION-COORDS CONVERTERS
        Vector2i position2coords(int x, int y) {  
            int file = 0;
            int rank = 0;

            Vertex* farQuad = coords2TilePointer(Vector2i(7,7));

            int minXDiff = getTileX(farQuad);
            int minYDiff = getTileY(farQuad);

            // Calculate the file the user is clicking
            for (int f = 0; f < 8; f++) {
                // Find the x-position of the current tile
                int tileX = getTileX(coords2TilePointer(Vector2i(f,0)));

                // Calculate the horizontal distance between the mouse and the tile
                int xDiff = abs(x - tileX);

                // If this distance is the smallest so far, store this value and target the current file
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

                // If this distance is the smallest so far, store this value and target the current rank
                if (yDiff < minYDiff) {
                    minYDiff = yDiff;
                    rank = r;
                }
            }

            return Vector2i(file,rank);
        }
        Vector2f coords2Position(Vector2i coords) {
            Vertex* tile = coords2TilePointer(coords);

            float vectorX = getTileX(tile);
            float vectorY = getTileY(tile);

            return Vector2f(vectorX, vectorY);
        }


        // Piece STYLE MANAGEMENT

        Texture* pieceName2Texture(char name) {

            Texture* texture = new Texture;

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

            return texture;
        }
        
        // TILE STYLE MANAGEMENT

        // Calculates the natural color of a tile, based on its rank and file
        Color coords2TileColor(Vector2i coords)  { return (coords.x + coords.y) % 2 == 0 ? _lightColor : _darkColor; }

        // Colors a tile a passed color
        void colorTile(Vector2i coords, Color color)  {
            Vertex* tile = coords2TilePointer(coords);
            tile[0].color = tile[1].color = tile[2].color = tile[3].color = color;
        }


        // TILE POSITION FUNCTIONS
        float getTileX(Vertex* tile) { return (tile[0].position.x + tile[2].position.x) / 2; }
        float getTileY(Vertex* tile) { return (tile[0].position.y + tile[2].position.y) / 2; }

        // Converts rank and file into a tile pointer
        Vertex* coords2TilePointer(Vector2i coords) { return &vertices[(coords.x + coords.y * 8) * 4]; }


    // DRAW FUNCTION
    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(vertices, states);

        for (int i = 0; i < pieceCount; i++) {
            if (pieces[i] != nullptr) target.draw(*pieces[i]);
        }
    }
};