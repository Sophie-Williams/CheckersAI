//
//  GameBoard.cpp
//  Checkers
//
//  Created by Bhavish Bhattar on 6/21/18.
//  Copyright © 2018 Bhavish Bhattar. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "MiniMax.hpp"
#include "GameBoard.h"
#include "Graphics.h"
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <thread>



using namespace std;
using namespace checkers;
namespace{
  //  const int FPS = 50;
   // const int MAX_FRAME_TIME = 5*1000 / FPS;
}
GameBoard::GameBoard() {
    SDL_Init(SDL_INIT_EVERYTHING);
    
    initializeLocs();
    this->gameLoop();
}
GameBoard::~GameBoard(){
    //free(_pieces);
    //free(_master);
}

void GameBoard::gameLoop(){
    
    SDL_Event event;
    Graphics graphics;
    
    _master = checkers::Checkers();
    
    
   // this->drawBoard(graphics);
    
    int LAST_UPDATE_TIME = SDL_GetTicks();
    this->drawBoard(graphics);
    vector<int> no_move = cantMove(_master);
    
    //this->drawGame(graphics);
   // graphics.flip();
    
    while(true){
        //implement call to MiniMax
        if( endGame()){
            _master.ResetBoard();
            this->drawBoard(graphics);
            vector<int> no_move = cantMove(_master);
        }
        if(_master._turn == 1){
            //problem arising in that minimax doesnt enter if statment.
            //also Minimax isnt passing moves correctly, look over that.
           vector<int> _move =  Minimax::Minimax(_master)._move;
            if(_move.size() > 2){
                for(int i = 1; i < _move.size();i++){
                    
                    int source = _move[i-1];
                    int dest = _move[i];
                    int cutTile = findCutPiece(source, dest);
                    _pieces[_master.getPiece(cutTile)].isDead = true;
                    _pieces[_master.getPiece(cutTile)].tileNum = -1;
                    _master.killPiece(cutTile);
                    
                    move(_move[i-1], _move[i], graphics);
                    sleep(1);
                    this->drawCurrBoard(graphics);
                    
                }
                /*
                if (*it == newDestTile){
                    
                    
                    int cutTile = findCutPiece(newTile, newDestTile);
                    //cout<<"tile cut: "<< cutTile<< "\n";
                    _pieces[_master.getPiece(cutTile)].isDead = true;
                    _pieces[_master.getPiece(cutTile)].tileNum = -1;
                    _master.killPiece(cutTile);
                    
                    
                    
                    move(newTile, newDestTile, graphics);
                    this->drawCurrBoard(graphics);
                    newLand = 1;
                    canCutAgain = _master.canCut(newDestTile).first;
                    //cout<<"canCutAgain:"<<canCutAgain<<"\n";
                    secondCuts =  _master.canCut(newDestTile).second;
                    lastDest = newDestTile;
                    found_tile = 1;
                    break;
                }
                */
            }
            else{
                int source = _move[0];
                int dest = _move[1];
                if(abs(source - dest)>= 7){
                int cutTile = findCutPiece(source, dest);
                _pieces[_master.getPiece(cutTile)].isDead = true;
                _pieces[_master.getPiece(cutTile)].tileNum = -1;
                _master.killPiece(cutTile);
                }
                move(_move[0], _move[1], graphics);
                sleep(1);
                this->drawCurrBoard(graphics);
            }
            _master.nextTurn();
             no_move = cantMove(_master);
        }
        else{
        if(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                return;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                int release = 0;
                int x, y;
                int tileMoves = 1;
                
                SDL_GetMouseState(&x, &y);
                //find if click occured over a tile
                int tileNum = checkTile(x, y);
                
               /* for(vector<int>::iterator it = no_move.begin(); it != no_move.end(); ++it){
                    if(tileNum == *it)
                        tileMoves = 0;
                }*/
                for(int i = 0; i < no_move.size(); i++){
                    if(tileNum == no_move[i])
                        tileMoves = 0;
                }
                if(tileNum == -1 || tileMoves == 0){
                    
                    continue;}
                else{
                    if(_master.getType(tileNum) != _master._turn){
                     
                        continue;
                    }
                    vector<int> moves = _master.possibleMoves(tileNum, _master.canCut(tileNum)).second;
                    //cout<<"got moves";
                    //draw circles for possible moves here
                    
                 
                    while (release == 0){
                        //cout<<"we inside";
                        SDL_GetMouseState(&x, &y);
                        _pieces[_master.getPiece(tileNum)].PieceX = x-20;
                        _pieces[_master.getPiece(tileNum)].PieceY = y-20;
                      
                        this->drawCurrBoard(graphics);
                        if(SDL_PollEvent(&event) && event.type == SDL_MOUSEBUTTONUP)
                        {release = 1;
                            SDL_GetMouseState(&x, &y);
                            int destTile = checkTile(x, y);
                            
                           // cout<<"destTile: "<< destTile<< " destTile2: "<< destTile2<< "\n";
                            int land = 0;
                            int didCut = 0;
                            for(vector<int>::iterator it = moves.begin(); it != moves.end(); ++it){
                               // cout<<*it<<"\n";
                                if (*it == destTile){
                                    
                                    //cout<<_master.possibleMoves(tileNum, _master.canCut(tileNum)).first<<"\n";
                                    if(_master.possibleMoves(tileNum, _master.canCut(tileNum)).first){
                                        //need to be able to provide a function that can find the tile that needs to be cut and then cut it.
                                        int cutTile = findCutPiece(tileNum, destTile);
                                        //cout<<"tile cut: "<< cutTile<< "\n";
                                        _pieces[_master.getPiece(cutTile)].isDead = true;
                                        _pieces[_master.getPiece(cutTile)].tileNum = -1;
                                        _master.killPiece(cutTile);
                                        didCut = 1;
                                    }
                                    
                                    move(tileNum, destTile, graphics);
                                    this->drawCurrBoard(graphics);
                                    land = 1;
                                    bool canCutAgain = _master.canCut(destTile).first;
                                    vector<int> secondCuts =  _master.canCut(destTile).second;
                                    int lastDest = destTile;
                                    
                                    //START OF NEW CODE
                                    while(didCut && canCutAgain){
                                        int found_tile = 0;
                                        
                                        while(found_tile == 0){
                                            if (SDL_PollEvent(&event) && event.type == SDL_MOUSEBUTTONDOWN){
                                                int newRelease = 0;
                                                int newX, newY;
                                                
                                                
                                                SDL_GetMouseState(&newX, &newY);
                                                //find if click occured over a tile
                                                int newTile = checkTile(newX, newY);
                                                if(newTile != lastDest){
                                                    
                                                    continue;}
                                                while( newRelease == 0){
                                                    SDL_GetMouseState(&newX, &newY);
                                                    _pieces[_master.getPiece(newTile)].PieceX = newX-20;
                                                    _pieces[_master.getPiece(newTile)].PieceY = newY-20;
                                                    
                                                    this->drawCurrBoard(graphics);
                                                    if(SDL_PollEvent(&event) && event.type == SDL_MOUSEBUTTONUP)
                                                    {newRelease = 1;
                                                        SDL_GetMouseState(&newX, &newY);
                                                        int newDestTile = checkTile(newX, newY);
                                                        
                                                        int newLand = 0;
                                                        //int didCut = 0;
                                                        for(vector<int>::iterator it = secondCuts.begin(); it != secondCuts.end(); ++it){
                                                            //cout<<*it<<"\n";
                                                            if (*it == newDestTile){
                                                                
                                                                
                                                                    int cutTile = findCutPiece(newTile, newDestTile);
                                                                    //cout<<"tile cut: "<< cutTile<< "\n";
                                                                    _pieces[_master.getPiece(cutTile)].isDead = true;
                                                                    _pieces[_master.getPiece(cutTile)].tileNum = -1;
                                                                    _master.killPiece(cutTile);
                                    
                                                                
                                                                
                                                                move(newTile, newDestTile, graphics);
                                                                this->drawCurrBoard(graphics);
                                                                newLand = 1;
                                                                canCutAgain = _master.canCut(newDestTile).first;
                                                                //cout<<"canCutAgain:"<<canCutAgain<<"\n";
                                                                secondCuts =  _master.canCut(newDestTile).second;
                                                                lastDest = newDestTile;
                                                                found_tile = 1;
                                                                break;
                                                            }
                                                }
                                                        if(newLand == 0){
                                                            _pieces[_master.getPiece(newTile)].PieceX = tileLocations[newTile].first;
                                                            _pieces[_master.getPiece(newTile)].PieceY = tileLocations[newTile].second;
                                                            this->drawCurrBoard(graphics);
                                                        }
                                            }
                                        }
                                            }}
                                        
                                    }
                                    //END OF NEW CODE
                                    
                                    
                                    
                                    
                                    _master.nextTurn();
                                    no_move = cantMove(_master);
                                    break;
                                }
                                }
                            if(land == 0){
                                _pieces[_master.getPiece(tileNum)].PieceX = tileLocations[tileNum].first;
                                _pieces[_master.getPiece(tileNum)].PieceY = tileLocations[tileNum].second;
                                this->drawCurrBoard(graphics);
                            }
                            
                            
                        }
                           // cout<<"you released";
                        }
               
                }
   
            }
          /*  if (event.type == SDL_MOUSEMOTION){
                //edit here
                _mouseX = event.motion.x;
                cout<<_mouseX;
                cout<<"\n";
                _mouseY = event.motion.y;
               // cout<< _mouseY;
            }
            */
            
            if (event.type == SDL_MOUSEBUTTONUP){
                //edit here
                //cout<<"release\n";
            }
        }
        const int CURRENT_UPDATE_TIME = SDL_GetTicks();
        //int DIFF = CURRENT_UPDATE_TIME- LAST_UPDATE_TIME;
        //this->update(min(DIFF,MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_UPDATE_TIME;
        
        
        } }
}

void GameBoard::draw(Graphics &graphics){
    graphics.clear();
    
    this->_player[1].draw(graphics,100,100);
    graphics.flip();
}

void update(float time){}
void GameBoard::drawBoard(Graphics &graphics){
    graphics.clear();
    this->_board = Sprite(graphics,boardSprite,0,0,448,464,0,0);
    this->_board.draw(graphics,0,0);
    this->drawGame(graphics);
    graphics.flip();
}
void GameBoard::drawCurrBoard(Graphics &graphics){
    graphics.clear();
    this->_board = Sprite(graphics,boardSprite,0,0,448,464,0,0);
    this->_board.draw(graphics,0,0);
    this->drawCurrGame(graphics);
    graphics.flip();
}
void GameBoard::drawCurrGame(Graphics &graphics){
    
    for(int i = 0;i <24; i++ )
    {
        if (_pieces[i].isDead != true)
        _pieces[i].sprite.draw(graphics,_pieces[i].PieceX , _pieces[i].PieceY);
        
        //graphics.flip();
    }
}
//need to edit this
void GameBoard::drawGame(Graphics &graphics){
    
    for(int i = 0;i <24; i++ )
    {   int j;
        if( i > 11)
            j = i + 8;
        else
            j = i;
        _pieces[i].tileNum = j;
        _pieces[i].isDead = false;
        this->setSpriteType(i, graphics);
        _pieces[i].PieceX = tileLocations[j].first;
        _pieces[i].PieceY = tileLocations[j].second;
        _pieces[i].sprite.draw(graphics, _pieces[i].PieceX, _pieces[i].PieceY);
        
        //graphics.flip();
    }
    //graphics.flip();
}

//matches x y ranges to certain tiles
int GameBoard::checkTile(int x, int y){
    int x_size = 56;
    int y_size = 58;
    //working here to map locations to appropriate tiles.
    if(x < x_size){
        if(y < y_size)
            return 0;
        if(y < y_size*3 && y > y_size*2)
            return 8;
        if(y < y_size*5 && y > y_size*4)
            return 16;
        if(y < y_size*7 && y > y_size*6)
            return 24;
    }
    if(x > x_size && x < x_size * 2){
        if(y > y_size && y < y_size *2)
            return 4;
        if(y > y_size*3 && y < y_size*4)
            return 12;
        if(y > y_size*5 && y < y_size*6)
            return 20;
        if(y > y_size*7 && y < y_size*8)
            return 28;
    }
    if(x > x_size*2 && x < x_size*3){
        if(y < y_size)
            return 1;
        if(y < y_size*3 && y > y_size*2)
            return 9;
        if(y < y_size*5 && y > y_size*4)
            return 17;
        if(y < y_size*7 && y > y_size*6)
            return 25;
    }
    if(x > x_size*3 && x < x_size * 4){
        if(y > y_size && y < y_size *2)
            return 5;
        if(y > y_size*3 && y < y_size*4)
            return 13;
        if(y > y_size*5 && y < y_size*6)
            return 21;
        if(y > y_size*7 && y < y_size*8)
            return 29;
    }
    if(x > x_size*4 && x < x_size*5){
        if(y < y_size)
            return 2;
        if(y < y_size*3 && y > y_size*2)
            return 10;
        if(y < y_size*5 && y > y_size*4)
            return 18;
        if(y < y_size*7 && y > y_size*6)
            return 26;
    }
    if(x > x_size*5 && x < x_size * 6){
        if(y > y_size && y < y_size *2)
            return 6;
        if(y > y_size*3 && y < y_size*4)
            return 14;
        if(y > y_size*5 && y < y_size*6)
            return 22;
        if(y > y_size*7 && y < y_size*8)
            return 30;
    }
    if(x > x_size*6 && x < x_size*7){
        if(y < y_size)
            return 3;
        if(y < y_size*3 && y > y_size*2)
            return 11;
        if(y < y_size*5 && y > y_size*4)
            return 19;
        if(y < y_size*7 && y > y_size*6)
            return 27;
    }
    if(x > x_size*7 && x < x_size * 8){
        if(y > y_size && y < y_size *2)
            return 7;
        if(y > y_size*3 && y < y_size*4)
            return 15;
        if(y > y_size*5 && y < y_size*6)
            return 23;
        if(y > y_size*7 && y < y_size*8)
            return 31;
    }
    return -1;
}

//sets type and sprite for a certain piece
void GameBoard::setSpriteType(int piece,Graphics & graphics){
    int type = _master.getType(_pieces[piece].tileNum); //0 red, 1 black
    bool king = _master.isKing(_pieces[piece].tileNum);
    
    if(type && king)
        _pieces[piece].type = Bking;
    if(type && !king)
        _pieces[piece].type = Bpiece;
    if(!type && king)
        _pieces[piece].type = Rking;
    if(!type && !king)
        _pieces[piece].type = Rpiece;
    
    _pieces[piece].sprite = Sprite(graphics,_pieces[piece].type,0,0,pieceX,pieceY,tileLocations[_pieces[piece].tileNum].first,tileLocations[_pieces[piece].tileNum].second);
    
   // cout<<"\n Piece:"<< piece << " tile:"<< _pieces[piece].tileNum << " type: "<< _master->getType(_pieces[piece].tileNum)<< "\n";
}

//logic executed after move event
void GameBoard::move(int tile, int dest, Graphics &graphics){
    _pieces[_master.getPiece(tile)].PieceX = tileLocations[dest].first;
    _pieces[_master.getPiece(tile)].PieceY = tileLocations[dest].second;
    _pieces[_master.getPiece(tile)].tileNum = dest;
    //remeber to include a function to promote to king if applicable
    if(dest < 4 && dest >= 0 && _pieces[_master.getPiece(tile)].type == Rpiece){
       // cout<<"make king\n";
        _pieces[_master.getPiece(tile)].type = Rking;
        _pieces[_master.getPiece(tile)].sprite = Sprite(graphics,_pieces[_master.getPiece(tile)].type,0,0,pieceX,pieceY,_pieces[_master.getPiece(tile)].PieceX,_pieces[_master.getPiece(tile)].PieceY);
    }
    else if(dest > 27 && _pieces[_master.getPiece(tile)].type == Bpiece){
        _pieces[_master.getPiece(tile)].type = Bking;
         _pieces[_master.getPiece(tile)].sprite = Sprite(graphics,_pieces[_master.getPiece(tile)].type,0,0,pieceX,pieceY,_pieces[_master.getPiece(tile)].PieceX,_pieces[_master.getPiece(tile)].PieceY);
    }
    _master.move(tile,dest);
}

vector<int> GameBoard::cantMove(checkers::Checkers &game){
    bool cutting = false;
    vector<int> cut;
    cut.push_back(-1);
    vector<int> cantCut;
    if(!game._turn){
        
        for(int i = 12; i < 24; i++){
        if(!_pieces[i].isDead){
            if(game.canCut(_pieces[i].tileNum).first){
                cutting = true;
                //cut.push_back(_pieces[i].tileNum);
            }
            else
                cantCut.push_back(_pieces[i].tileNum);
        }}
    }
    else{
        for(int i = 0; i < 12; i++){
            if(!_pieces[i].isDead){
            if(game.canCut(_pieces[i].tileNum).first){
                cutting = true;
                //cut.push_back(_pieces[i].tileNum);
            }
            else
                cantCut.push_back(_pieces[i].tileNum);
            }}
    }
    if(cutting)
        return cantCut;
    else
        return cut;
}
int GameBoard::findCutPiece(int tile, int dest){
    int diff = dest - tile;
    if(diff == -9){
        if(tile%8 < 4)
            return tile - 5;
        else return tile - 4;
    }
    else if(diff == -7){
        if(tile%8 < 4)
            return tile - 4;
        else return tile - 3;
        
    }
    else if(diff == 7){
        if(tile%8 < 4)
            return tile + 3;
        else return tile + 4;
        
    }
    else if (diff == 9){
        if(tile%8 < 4)
            return tile + 4;
        else return tile + 5;
    }
    return -1;
}

GameBoard::Piece * GameBoard::getPieces(){
    GameBoard::Piece * piece = new Piece[24];
    for(int i = 0; i < 24; i++){
        piece[i] = _pieces[i];
    }
    return piece;
}
bool GameBoard::endGame(){
    int deadb= 0;
    int deadr = 0;
    for(int i = 0; i< 12; i++){
        if (_pieces[i].isDead){
            deadb++;
        }
        if (_pieces[i+12].isDead){
            deadr++;
        }
    }
    if(deadb == 12 ){
        cout<<"RED WINS";
        return true;
    }
    else if(deadr == 12 ){
        cout<<"BLACK WINS";
        return true;
    }
    return false;
}

//initializes location array for tiles
void GameBoard::initializeLocs(){
    int x = 56;
    int y = 58;
    tileLocations[0]  = make_pair(0, 0);
    tileLocations[1]  = make_pair(x*2, 0);
    tileLocations[2]  = make_pair(x*4, 0);
    tileLocations[3]  = make_pair(x*6, 0);
    tileLocations[4]  = make_pair(x, y);
    tileLocations[5]  = make_pair(x*3, y);
    tileLocations[6]  = make_pair(x*5, y);
    tileLocations[7]  = make_pair(x*7, y);
    tileLocations[8]  = make_pair(0, y*2);
    tileLocations[9]  = make_pair(x*2, y*2);
    tileLocations[10]  = make_pair(x*4, y*2);
    tileLocations[11]  = make_pair(x*6, y*2);
    tileLocations[12]  = make_pair(x, y*3);
    tileLocations[13]  = make_pair(x*3, y*3);
    tileLocations[14]  = make_pair(x*5, y*3);
    tileLocations[15]  = make_pair(x*7, y*3);
    tileLocations[16]  = make_pair(0, y*4);
    tileLocations[17]  = make_pair(x*2, y*4);
    tileLocations[18]  = make_pair(x*4, y*4);
    tileLocations[19]  = make_pair(x*6, y*4);
    tileLocations[20]  = make_pair(x, y*5);
    tileLocations[21]  = make_pair(x*3, y*5);
    tileLocations[22]  = make_pair(x*5, y*5);
    tileLocations[23]  = make_pair(x*7, y*5);
    tileLocations[24]  = make_pair(0, y*6);
    tileLocations[25]  = make_pair(x*2, y*6);
    tileLocations[26]  = make_pair(x*4, y*6);
    tileLocations[27]  = make_pair(x*6, y*6);
    tileLocations[28]  = make_pair(x, y*7);
    tileLocations[29]  = make_pair(x*3, y*7);
    tileLocations[30]  = make_pair(x*5, y*7);
    tileLocations[31]  = make_pair(x*7, y*7);
    
}
