#include <SFML/Graphics.hpp>
#include "chess.hpp"
#include <iostream>
#include <unordered_map>
#include <string>
#include <map>

using namespace std;

struct PieceSprite {
    sf::Sprite sprite;
    sf::Vector2f currentPos;
    sf::Vector2f targetPos;
    bool moving = false;
};

int main() {
    chess_board board;  // initialized in constructor

    const int TILE_SIZE = 80;
    const int BOARD_SIZE_PX = TILE_SIZE * 8;

    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE_PX, BOARD_SIZE_PX), "ChessGUI");
    window.setFramerateLimit(60);

    // Load textures
    unordered_map<string, sf::Texture> textures;
    string pieces[] = {
        "white-pawn","white-bishop","white-knight","white-rook","white-queen","white-king",
        "black-pawn","black-bishop","black-knight","black-rook","black-queen","black-king"
    };

    for(auto &name : pieces){
        sf::Texture tex;
        if(!tex.loadFromFile("/home/user/Masaüstü/chess/images/" + name + ".png")){
            cout << "Failed to load " << name << ".png" << endl;
        }
        textures[name] = tex;
    }

    // Helper: piece number -> name
    auto pieceName = [&](int num){
        switch(num){
            case 1: return "white-pawn";
            case 2: return "white-bishop";
            case 3: return "white-knight";
            case 4: return "white-rook";
            case 5: return "white-queen";
            case 6: return "white-king";
            case -1: return "black-pawn";
            case -2: return "black-bishop";
            case -3: return "black-knight";
            case -4: return "black-rook";
            case -5: return "black-queen";
            case -6: return "black-king";
        }
        return "";
    };

    // Keep sprites for moving pieces
    map<pair<int,int>, PieceSprite> activePieces;

    auto refreshBoardSprites = [&](){
        activePieces.clear();
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                int piece_num = board.board[i][j];
                if(piece_num != 0){
                    string name = pieceName(piece_num);
                    PieceSprite ps;
                    ps.sprite.setTexture(textures[name]);

                    // scale to fit square
                    sf::Vector2u texSize = textures[name].getSize();
                    float scaleX = static_cast<float>(TILE_SIZE) / texSize.x;
                    float scaleY = static_cast<float>(TILE_SIZE) / texSize.y;
                    ps.sprite.setScale(scaleX, scaleY);

                    ps.currentPos = sf::Vector2f(j*TILE_SIZE, i*TILE_SIZE);
                    ps.targetPos = ps.currentPos;
                    ps.sprite.setPosition(ps.currentPos);
                    activePieces[{i,j}] = ps;
                }
            }
        }
    };

    refreshBoardSprites();

    bool dragging = false;
    sf::Vector2i drag_start, drag_end;
    string old_pos, new_pos;
    int turn = 1;          // 1 = white, 0 = black
    int termination = 0;

    srand(time(0));
    if(rand()%2) turn = 0;

    while(window.isOpen() && termination == 0){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed){
                drag_start = sf::Vector2i(event.mouseButton.x / TILE_SIZE, event.mouseButton.y / TILE_SIZE);
                old_pos = string(1,'a'+drag_start.x) + to_string(8-drag_start.y);
                dragging = true;
            }

            if(event.type == sf::Event::MouseButtonReleased && dragging){
                drag_end = sf::Vector2i(event.mouseButton.x / TILE_SIZE, event.mouseButton.y / TILE_SIZE);
                new_pos = string(1,'a'+drag_end.x) + to_string(8-drag_end.y);

                bool move_ok = board.move(old_pos, new_pos, turn, termination);
                if(move_ok) {
                    turn = 1-turn;
                    refreshBoardSprites(); // refresh positions after logic update
                }
                dragging = false;
            }
        }

        // Animate pieces
        for(auto &kv : activePieces){
            auto &ps = kv.second;
            if(ps.currentPos != ps.targetPos){
                sf::Vector2f dir = ps.targetPos - ps.currentPos;
                float dist = sqrt(dir.x*dir.x + dir.y*dir.y);
                float speed = 10.0f; // pixels per frame
                if(dist < speed){
                    ps.currentPos = ps.targetPos;
                } else {
                    dir /= dist;
                    ps.currentPos += dir * speed;
                }
                ps.sprite.setPosition(ps.currentPos);
            }
        }

        // Draw board
        window.clear();
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                sf::RectangleShape square(sf::Vector2f(TILE_SIZE,TILE_SIZE));
                if((i+j)%2==0) square.setFillColor(sf::Color(240,217,181));
                else square.setFillColor(sf::Color(181,136,99));
                square.setPosition(j*TILE_SIZE, i*TILE_SIZE);
                window.draw(square);
            }
        }

        // Draw pieces
        for(auto &kv : activePieces){
            window.draw(kv.second.sprite);
        }

        window.display();
    }

    return 0;
}
