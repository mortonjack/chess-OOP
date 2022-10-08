#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/piece.h"
using namespace sf;

class uiboard : public Drawable, public Transformable
{
    protected:
        // Board size constants
        int _length;
        int _width;

        // Color constants
        const Color _whiteColor = Color{ 0xF3F3F3FF };
        const Color _blackColor = Color{ 0x4D4C4AFF };
        const Color _lightColor = Color{ 0xF2DBB4FF };
        const Color _darkColor = Color{ 0xB48C64FF };
        const Color _redColor = Color{ 0xCC0000FF };

        // Piece moving variables
        bool _sourceSelected = false;
        Vector2i _sourceCoords;
        Vector2i _targetCoords;

        CircleShape* _sourcePiece;

    public:
        CircleShape* pieces[32] = {nullptr};
        int pieceCount = 0;

        // Define board vertices
        VertexArray vertices;

    public:
        uiboard(): uiboard(512,512) {}

        uiboard(int length, int width) {
            _length = length;
            _width = width;

            // resize the vertex array to fit the level size
            vertices.setPrimitiveType(Quads);
            vertices.resize(8 * 8 * 4);

            // populate the vertex array, with one tile per tile
            for (unsigned int file = 0; file < 8; ++file)
                for (unsigned int rank = 0; rank < 8; ++rank)
                {
                    // Vectorise the rank and file
                    Vector2i coords = Vector2i(file,rank);

                    // get a pointer to the current tile's tile
                    Vertex* tile = coords2TilePointer(coords);

                    // define its 4 corners
                    tile[0].position = Vector2f(file * _length/8, rank * _width/8);
                    tile[1].position = Vector2f((file + 1) * _length/8, rank * _width/8);
                    tile[2].position = Vector2f((file + 1) * _length/8, (rank + 1) * _width/8);
                    tile[3].position = Vector2f(file * _length/8, (rank + 1) * _width/8);

                    // Determine whether the square is light or dark
                    colorTile(coords, coords2TileColor(coords));
                }
        }

        bool loadPieces(piece* board[8][8]) {
            for (int file = 0; file < 8; file++) {
                for (int rank = 0; rank < 8; rank++) {
                    if (board[file][rank] != nullptr) {
                        CircleShape* sprite = piece2Sprite(board[file][rank]);
                        sprite->setPosition(coords2Position(Vector2i(file,rank)));

                        pieces[pieceCount] = sprite;
                        pieceCount++;
                    }
                }
            }

            return true;
        }

        /*
        void tileClick(int x, int y) {
            Vector2i coords = position2coords(x,y);

            if (!_sourceSelected) {
                setSourceCoords(coords);
            } else {
                movePiece(coords);
            }

        }

        void setSourceCoords(Vector2i coords) {
            // Indicate that a source tile has been selected
            _sourceSelected = true;

            // Store the clicked socation as the source coordiantes
            _sourceCoords = coords;

            // Select the piece on this tile
            _sourcePiece = coords2Piece(_sourceCoords);

            // Color the tile red
            colorTile(_sourceCoords, _redColor);
        }

        void movePiece(Vector2i coords) {
        // Indicate that a source tile is no longer selected
        _sourceSelected = false;

        // Remove the color of the previously selected tile
        colorTile(_sourceCoords, coords2TileColor(_sourceCoords));

        // If our source piece is empty, we are moving nothing.
        if (_sourcePiece == nullptr) return;

        // Move the piece where the player has clicked
        _sourcePiece->setPosition(coords2Position(coords));
    } */

    private:
        /*
        CircleShape* coords2Piece(Vector2i coords) {
            for (int i = 0; i < 32; i++) {
                if (pieces[i] == nullptr) return nullptr;
                if (pieces[i]->getPosition() == coords2Position(coords)) return pieces[i];
            }
            return nullptr;
        } */

        CircleShape* piece2Sprite(piece* piece) {
            CircleShape* sprite = new CircleShape;

            // Setup physical properties (size, origin)
            int size = pieceType2Size(piece->getType());
            sprite->setRadius(size);
            sprite->setOrigin(size,size);

            // Setup style properties (color, outline)            
            sprite->setFillColor(pieceColor2Color(piece->getColor()));
            sprite->setOutlineThickness(3);
            sprite->setOutlineColor(pieceColor2OutlineColor(piece->getColor()));

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


        // PIECE STYLE MANAGEMENT
        int pieceType2Size(char type) {
            switch (type) {
                case 'k':
                    return 20;

                case 'q':
                    return 15;

                case 'r':
                    return 10;

                case 'b':
                    return 8;

                case 'n':
                    return 8;

                case 'p':
                    return 5;

                default:
                    return 0;
            }
        }
        Color pieceColor2Color(char color) { return color != 'B' ? _whiteColor : _blackColor; }
        Color pieceColor2OutlineColor(char color) { return color != 'B' ? _blackColor : _whiteColor; }
        
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