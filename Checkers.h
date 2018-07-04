#ifndef CHECKERS_H
#define CHECKERS_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <vector>



using namespace std;
namespace checkers {
    

class Checkers{
  private:
    
   /* struct Piece{
      bool is_dead;
      bool is_king;
      int curr_X;
      int curr_Y;
      //probably dont need this
      bool must_move;
    };
    */
    
   // Piece * REDS_;
   // Piece * BLACKS_;
    
  public:
    struct Tile{
        pair <int , int > up_tiles;
        pair <int , int > down_tiles;
        
        bool has_Rpiece;
        bool has_Bpiece;
        bool has_Rking;
        bool has_Bking;
        
        int tile_num;
        int curr_piece = -1;
    };
    Tile Board_[32];
    Checkers();
    Checkers(const Checkers &other);
    const Checkers & operator= (const Checkers &other);
    void ResetBoard();
    pair <bool, vector<int>> canCut(int tile);
    int _turn; //turn = 0 for red and turn = 1 for black
    bool isOccupied(int tile);
    int getType(int tile);
    
    void nextTurn();
    void killPiece(int tile);
    void move(int tile, int dest);
    bool isKing(int tile);
    int getPiece(int tile);
    void makeKing(int tile);
    int findCutPiece(int tile, int dest);
    pair<bool,vector<int>> possibleMoves(int tile,pair<bool,vector<int>> cuts);
    Tile * getTile(int tile);
    

};
}
#endif
