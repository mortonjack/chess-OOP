#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Chessboard : public sf::Drawable, public sf::Transformable
{
public:
    // Define color constants
    sf::Color white = sf::Color{ 0xF3F3F3FF };
    sf::Color black = sf::Color{ 0x4D4C4AFF };
    sf::Color light = sf::Color{ 0xF2DBB4FF };
    sf::Color dark = sf::Color{ 0xB48C64FF };
    sf::Color red = sf::Color{ 0xCC0000FF };


    bool sourceSelected = false;
    sf::Vector2i sourceCoords;
    sf::Vector2i targetCoords;

    sf::CircleShape* sourcePiece;

    sf::CircleShape* pieces[32] = {nullptr};

    // Define board vertices
    sf::VertexArray vertices;

    bool loadBoard(sf::Vector2u tileSize)  {  
  
        // resize the vertex array to fit the level size
        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(8 * 8 * 4);

        // populate the vertex array, with one tile per tile
        for (unsigned int file = 0; file < 8; ++file)
            for (unsigned int rank = 0; rank < 8; ++rank)
            {
                // get a pointer to the current tile's tile
                sf::Vertex* tile = coords2TopLeftVertex(file, rank);

                // define its 4 corners
                tile[0].position = sf::Vector2f(file * tileSize.x, rank * tileSize.y);
                tile[1].position = sf::Vector2f((file + 1) * tileSize.x, rank * tileSize.y);
                tile[2].position = sf::Vector2f((file + 1) * tileSize.x, (rank + 1) * tileSize.y);
                tile[3].position = sf::Vector2f(file * tileSize.x, (rank + 1) * tileSize.y);

                // Determine whether the square is light or dark
                colorTile(file, rank, coords2TileColor(file,rank));
            }

        return true;
    }

    bool loadPieces(int radius) {
        for (int f = 0; f < 8; f++) {
            sf::CircleShape *Piece = new sf::CircleShape;

            Piece->setRadius(radius);
            Piece->setOrigin(radius,radius);
            Piece->setPosition(coords2Position(f, 0));

            Piece->setFillColor(white);
            Piece->setOutlineThickness(3);
            Piece->setOutlineColor(black);

            pieces[f] = Piece;
        }

        return true;
    }

    sf::Vector2i position2coords(int x, int y) {  
        int file = 0;
        int rank = 0;

        sf::Vertex* farQuad = coords2TopLeftVertex(7, 7);

        int minXDiff = getTileX(farQuad);
        int minYDiff = getTileY(farQuad);

        // Calculate the file the user is clicking
        for (int f = 0; f < 8; f++) {
            // Find the x-position of the current tile
            int tileX = getTileX(coords2TopLeftVertex(f, 0));

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
            int tileY = getTileY(coords2TopLeftVertex(0, r));

            // Calculate the vertical distance between the mouse and the tile
            int yDiff = abs(y - tileY);

            // If this distance is the smallest so far, store this value and target the current rank
            if (yDiff < minYDiff) {
                minYDiff = yDiff;
                rank = r;
            }
        }

        return sf::Vector2i(file,rank);
    }

    sf::CircleShape* coords2Piece(int file, int rank) {
        for (int i = 0; i < 32; i++) {
            if (pieces[i] == nullptr) return nullptr;
            if (pieces[i]->getPosition() == coords2Position(file,rank)) return pieces[i];
        }
        cout << "Failed...";
        return nullptr;
    }

    sf::Vector2f coords2Position(int file, int rank) {
        sf::Vertex* tile = coords2TopLeftVertex(file, rank);

        float vectorX = getTileX(tile);
        float vectorY = getTileY(tile);

        return sf::Vector2f(vectorX, vectorY);
    }

    void tileClick(int x, int y) {
        sf::Vector2i coords = position2coords(x,y);

        if (!sourceSelected) {
            setSourceCoords(coords);
        } else {
            movePiece(coords);
        }

    }

    void setSourceCoords(sf::Vector2i coords) {
        // Indicate that a source tile has been selected
        sourceSelected = true;

        // Store the clicked socation as the source coordiantes
        sourceCoords = coords;

        // Select the Piece on this tile
        sourcePiece = coords2Piece(sourceCoords.x, sourceCoords.y);

        // Color the tile red
        colorTile(sourceCoords.x, sourceCoords.y, red);
    }

    void movePiece(sf::Vector2i coords) {
        // Indicate that a source tile is no longer selected
        sourceSelected = false;

        // Store the licked location as the target coordinates
        targetCoords = coords;

        // Remove the color of the previously selected tile
        colorTile(sourceCoords.x, sourceCoords.y, coords2TileColor(sourceCoords.x, sourceCoords.y));

        // If our source Piece is empty, we are moving nothing.
        if (sourcePiece == nullptr) return;

        // Move the Piece where the player has clicked
        sourcePiece->setPosition(coords2Position(coords.x, coords.y));
    }

private:
    sf::Color coords2TileColor(int file, int rank)  { return (file + rank) % 2 == 0 ? light : dark; }
    void colorTile(int file, int rank, sf::Color color)  {
        sf::Vertex* tile = coords2TopLeftVertex(file, rank);
        tile[0].color = tile[1].color = tile[2].color = tile[3].color = color;
    }

    float getTileX(sf::Vertex* tile) { return (tile[0].position.x + tile[2].position.x) / 2; }
    float getTileY(sf::Vertex* tile) { return (tile[0].position.y + tile[2].position.y) / 2; }

    sf::Vertex* coords2TopLeftVertex(int file, int rank) { return &vertices[(file + rank * 8) * 4]; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
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