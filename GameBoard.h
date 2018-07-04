//
//  GameBoard.h
//  Checkers
//
//  Created by Bhavish Bhattar on 6/21/18.
//  Copyright © 2018 Bhavish Bhattar. All rights reserved.
//

#ifndef GameBoard_h
#define GameBoard_h

#include "Sprite.hpp"
#include "Checkers.h"

class Graphics;

class GameBoard{
public:
    GameBoard();
    ~GameBoard();
    
    struct Piece{
        int tileNum;
        string type;
        Sprite sprite;
        bool isDead;
        int PieceX;
        int PieceY;
    };
    Piece * getPieces();
private:
    
    Piece _pieces[24];
    int pieceX = 56;
    int pieceY = 58;
    //Piece * _blacks;
    string boardSprite = "/Users/bhavishbhattar/Desktop/Checkers_Summer_Proj/checkers_board.png";
    string Rking = "/Users/bhavishbhattar/Desktop/Checkers_Summer_Proj/red_piece_king.png";
    string Bking = "/Users/bhavishbhattar/Desktop/Checkers_Summer_Proj/black_piece_king.png";
    string Bpiece = "/Users/bhavishbhattar/Desktop/Checkers_Summer_Proj/black_piece.png";
    string Rpiece = "/Users/bhavishbhattar/Desktop/Checkers_Summer_Proj/red_piece.png";
    void gameLoop();
    void draw(Graphics &graphics);
    void drawBoard(Graphics &graphics);
    void drawCurrBoard(Graphics &graphics);
    void drawGame(Graphics &graphics);
    void drawCurrGame(Graphics &graphics);
    void update(float time);
    void setSpriteType(int piece, Graphics & graphics);
    void setSprites(Graphics & graphics);
    float _mouseX;
    float _mouseY;
    Sprite * _player;
    Sprite _board;
    checkers::Checkers _master;
    void click(int mouseX,int mouseY, Graphics & graphics);
    int checkTile(int x, int y);
    pair<int , int > tileLocations[32];
    void initializeLocs();
    void move(int tile, int dest,  Graphics &graphics);
    void killPiece(int tile,int dest);
    int findCutPiece(int tile, int dest);
    vector<int> cantMove(checkers::Checkers & game);
    bool endGame();
};

#endif /* GameBoard_h */
