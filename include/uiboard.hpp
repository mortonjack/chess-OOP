#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
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

    bool sourceSelected = false;
    Vector2i sourceCoords;
    Vector2i targetCoords;

    CircleShape* sourcePiece;

    CircleShape* pieces[32] = {nullptr};

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

    bool loadPieces(int radius) {
        for (int f = 0; f < 8; f++) {
            CircleShape *piece = new CircleShape;

            piece->setRadius(radius);
            piece->setOrigin(radius,radius);
            piece->setPosition(coords2Position(Vector2i(f,0)));

            piece->setFillColor(_whiteColor);
            piece->setOutlineThickness(3);
            piece->setOutlineColor(_blackColor);

            pieces[f] = piece;
        }

        return true;
    }

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

    CircleShape* coords2Piece(Vector2i coords) {
        for (int i = 0; i < 32; i++) {
            if (pieces[i] == nullptr) return nullptr;
            if (pieces[i]->getPosition() == coords2Position(coords)) return pieces[i];
        }
        return nullptr;
    }

    Vector2f coords2Position(Vector2i coords) {
        Vertex* tile = coords2TilePointer(coords);

        float vectorX = getTileX(tile);
        float vectorY = getTileY(tile);

        return Vector2f(vectorX, vectorY);
    }

    void tileClick(int x, int y) {
        Vector2i coords = position2coords(x,y);

        if (!sourceSelected) {
            setSourceCoords(coords);
        } else {
            movePiece(coords);
        }

    }

    void setSourceCoords(Vector2i coords) {
        // Indicate that a source tile has been selected
        sourceSelected = true;

        // Store the clicked socation as the source coordiantes
        sourceCoords = coords;

        // Select the piece on this tile
        sourcePiece = coords2Piece(sourceCoords);

        // Color the tile red
        colorTile(sourceCoords, _redColor);
    }

    void movePiece(Vector2i coords) {
        // Indicate that a source tile is no longer selected
        sourceSelected = false;

        // Store the licked location as the target coordinates
        targetCoords = coords;

        // Remove the color of the previously selected tile
        colorTile(sourceCoords, coords2TileColor(sourceCoords));

        // If our source piece is empty, we are moving nothing.
        if (sourcePiece == nullptr) return;

        // Move the piece where the player has clicked
        sourcePiece->setPosition(coords2Position(targetCoords));
    }

private:
    // TILE COLOR MANAGEMENT

    // Calculates the natural color of a tile, based on its rank and file
    Color coords2TileColor(Vector2i coords)  { return (coords.x + coords.y) % 2 == 0 ? _lightColor : _darkColor; }

    // Colors a tile a passed color
    void colorTile(Vector2i coords, Color color)  {
        Vertex* tile = coords2TilePointer(coords);
        tile[0].color = tile[1].color = tile[2].color = tile[3].color = color;
    }

    // TILE POSITION FUNCTIONS

    // Returns the X and Y positions of a file, from its pointer
    float getTileX(Vertex* tile) { return (tile[0].position.x + tile[2].position.x) / 2; }
    float getTileY(Vertex* tile) { return (tile[0].position.y + tile[2].position.y) / 2; }

    // Converts rank and file into a tile pointer
    Vertex* coords2TilePointer(Vector2i coords) { return &vertices[(coords.x + coords.y * 8) * 4]; }

    // MAIN FUNCTION
    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(vertices, states);

        for (int i = 0; i < 8; i++) {
            target.draw(*pieces[i]);
        }
    }
};