/* Bhavish Bhattar Summer Project 2018*/

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <array>
#include "Checkers.h"

using namespace checkers;

//creates game
Checkers::Checkers(){
    
 
 // REDS_ = new Piece[12];
//  BLACKS_ = new Piece[12];
    this->ResetBoard();
}
Checkers::Checkers(const Checkers &other){
    for(int i = 0; i < 32; i++){
        Board_[i].tile_num = other.Board_[i].tile_num;
        Board_[i].has_Bking = other.Board_[i]. has_Bking;
        Board_[i].has_Rking = other.Board_[i].has_Rking;
        Board_[i].up_tiles = other.Board_[i].up_tiles;
        Board_[i].down_tiles = other.Board_[i].down_tiles;
        Board_[i].has_Bpiece = other.Board_[i].has_Bpiece;
        Board_[i].has_Rpiece = other.Board_[i].has_Rpiece;
        Board_[i].curr_piece = other.Board_[i].curr_piece;
    }
    _turn = other._turn;
}
const Checkers & Checkers::operator= (const Checkers &other){
    for(int i = 0; i < 32; i++){
        Board_[i].tile_num = other.Board_[i].tile_num;
        Board_[i].has_Bking = other.Board_[i]. has_Bking;
        Board_[i].has_Rking = other.Board_[i].has_Rking;
        Board_[i].up_tiles = other.Board_[i].up_tiles;
        Board_[i].down_tiles = other.Board_[i].down_tiles;
        Board_[i].has_Bpiece = other.Board_[i].has_Bpiece;
        Board_[i].has_Rpiece = other.Board_[i].has_Rpiece;
        Board_[i].curr_piece = other.Board_[i].curr_piece;
    }
    _turn = other._turn;
    return *this;
}

// initializes board and pieces
void Checkers::ResetBoard(){
  //unsigned red = 0;
  //unsigned black = 0;
  //Declares location for all pieces on board and initializes all pieces
    int j = 0;
    for(int i = 0; i < 32; i++){
        
        Board_[i].tile_num = i;
        Board_[i].has_Bking = false;
        Board_[i].has_Rking = false;
     /* Board_[i].has_Rpiece = false;
        Board_[i].has_Bpiece = false;*/
        if(i - 4 >= 0 && i+4 <32 &&(i%8 != 0 && i%8 != 7)){ // 4-6, 9-11, 12-14, 17-19, 20-22, 25-27
            if(i%8 > 3){
                Board_[i].up_tiles = (make_pair(i-4,i-3));
                Board_[i].down_tiles= make_pair(i+4,i+5);}
            else{
                Board_[i].up_tiles= (make_pair(i-5,i-4));
                Board_[i].down_tiles = (make_pair(i+3,i+4));}
            
        }
        else if (i - 4 >= 0  &&(i%8 != 0 && i%8 != 7)){ //28-30
            Board_[i].up_tiles = (make_pair(i-4,i-3));
            Board_[i].down_tiles = (make_pair(-1,-1));
        }
        else if (i+4 <32 &&(i%8 != 0 && i%8 != 7)){ //1-3
            Board_[i].down_tiles = (make_pair(i+3,i+4));
            Board_[i].up_tiles = (make_pair(-1,-1));
        }
        else if(i - 4 >= 0 && i+4 <32 &&(i%8 != 7)){ //8,16,24
            Board_[i].up_tiles = (make_pair(-1,i-4));
            Board_[i].down_tiles = (make_pair(-1,i+4));
        }
        else if(i - 4 >= 0 && i+4 <32 &&(i%8 != 0)){//7,15,23
            Board_[i].up_tiles = (make_pair(i-4,-1));
            Board_[i].down_tiles = (make_pair(i+4,-1));
        }
        else if( i == 0){//0
            Board_[i].up_tiles = (make_pair(-1,-1));
            Board_[i].down_tiles = (make_pair(-1,i+4));
        }
        else if( i == 31){ //31
            Board_[i].up_tiles = (make_pair(i-4,-1));
            Board_[i].down_tiles = (make_pair(-1,-1));
        }
        
        if(i < 12){
            Board_[i].has_Bpiece = true;
            Board_[i].has_Rpiece = false;
            Board_[i].curr_piece = j;
            j++;
           // cout<< "tile"<< i << Board_[i].has_Bpiece<< "\n";
        }
        else if(i > 19){
            
            Board_[i].has_Bpiece = false;
            Board_[i].has_Rpiece = true;
            Board_[i].curr_piece = j;
            j++;
            
            //cout<< "tile"<< i << Board_[i].has_Rpiece << "\n";
            
        }
        else{
            Board_[i].curr_piece = -1;
            Board_[i].has_Bpiece = false;
            Board_[i].has_Rpiece = false;
        }
        
    }
     _turn = 0;
}
bool Checkers::isOccupied(int tile){
    bool piece;
    if(tile != -1)
     piece = (Board_[tile].has_Bpiece || Board_[tile].has_Rpiece);
    else
        return true;
    
    //cout<<"\n isOccupied say tile:"<< tile<< "has black is " << Board_[tile].has_Bpiece;
    return piece;
}
Checkers::Tile * Checkers::getTile(int tile){
    if(tile != -1)
        return &Board_[tile];
    else
        return NULL;
}


int Checkers::getType(int tile){ //EVEN IF KING MARK THE COLOR OF THE PIECE
    if (isOccupied(tile)){
        if (Board_[tile].has_Rpiece){
            return 0; //red
        }
        if (Board_[tile].has_Bpiece){
            return 1; //black
        }
    }
    return -1;
}

int Checkers::getPiece(int tile){
    return Board_[tile].curr_piece;
}
pair <bool, vector<int>> Checkers::canCut(int tile){
    bool canCut = false;
    vector<int> cuts;
    //NEED TO CHANGE THIS TO WORK WITH SEGFAULTS (checking up of a -1)
    //cout<<tile<< " ,type: "<< getType(tile) <<"\n";
    if (isOccupied(tile)){
        //cout<<tile<<"\n";
        bool up_left_left, up_right_right, down_left_left, down_right_right;
        
        Tile* currTile = getTile(tile); //will always be an actual tile
        Tile* up_leftTile = getTile(currTile->up_tiles.first);
        
        if(up_leftTile != NULL)
            up_left_left = !isOccupied(up_leftTile->up_tiles.first);
        else
            up_left_left = false;
        
        Tile* up_rightTile = getTile(currTile->up_tiles.second);
        
        if(up_rightTile != NULL)
            up_right_right = !isOccupied(up_rightTile->up_tiles.second);
        else
            up_right_right = false;
        
        Tile* down_rightTile = getTile(currTile->down_tiles.second);
        
        if(down_rightTile != NULL)
            down_right_right = !isOccupied(down_rightTile->down_tiles.second);
        else
            down_right_right = false;
        
        Tile* down_leftTile = getTile(currTile->down_tiles.first);
        
        if(down_leftTile != NULL)
            down_left_left = !isOccupied(down_leftTile->down_tiles.first);
        else
            down_left_left = false;
        
        //need to come up with a way to differentiate between which cuts need to happen as a king
        //red goes up, black goes down ie. black is smaller numbers/ red is larger
        if(up_leftTile != NULL){
        if(getType(tile) != getType(up_leftTile->tile_num) && up_left_left && isOccupied(up_leftTile->tile_num)&&(getType(tile) == 0 || currTile->has_Bking)){
            canCut = true;
            cuts.push_back(up_leftTile->up_tiles.first);
        }
        }
        if(up_rightTile != NULL){
        if(getType(tile) != getType(up_rightTile->tile_num) && up_right_right && isOccupied(up_rightTile->tile_num)&&(getType(tile) == 0 || currTile->has_Bking)){
            canCut = true;
            cuts.push_back(up_rightTile->up_tiles.second);
        }}
        if(down_leftTile != NULL){
        if(getType(tile) != getType(down_leftTile->tile_num) && down_left_left && isOccupied(down_leftTile->tile_num)&&(getType(tile) == 1 || currTile->has_Rking)){
            canCut = true;
            cuts.push_back(down_leftTile->down_tiles.first);
        }}
        if(down_rightTile != NULL){
        if(getType(tile) != getType(down_rightTile->tile_num) && down_right_right && isOccupied(down_rightTile->tile_num)&&(getType(tile) == 1 || currTile->has_Rking)){
            canCut = true;
            cuts.push_back(down_rightTile->down_tiles.second);
        }
        }
    }
    if (!canCut)
        cuts.push_back(-1);
    return make_pair(canCut,cuts);
}

void Checkers::nextTurn(){
    if(_turn)
        _turn = 0;
    else
        _turn = 1;
}
void Checkers::killPiece(int tile){
    Board_[tile].has_Bking = false;
    Board_[tile].has_Rking = false;
    Board_[tile].has_Rpiece = false;
    Board_[tile].has_Bpiece = false;
    Board_[tile].curr_piece = -1;
}
void Checkers::move(int tile, int dest){
    if(isOccupied(dest)){
        cout<<"there is a piece here, dumbfuck";
        return;
    }
    Board_[dest].has_Bking = Board_[tile].has_Bking;
    Board_[dest].has_Rking = Board_[tile].has_Rking;
    Board_[dest].has_Rpiece = Board_[tile].has_Rpiece;
    Board_[dest].has_Bpiece = Board_[tile].has_Bpiece;
    Board_[dest].curr_piece = Board_[tile].curr_piece;
    //include function to promote if applicable
    if(Board_[dest].has_Rpiece && !Board_[dest].has_Rking && dest < 4 && dest >= 0)
        Board_[dest].has_Rking = true;
    if(Board_[dest].has_Bpiece && !Board_[dest].has_Bking && dest > 27)
        Board_[dest].has_Bking = true;
    
    killPiece(tile);
    
}
bool Checkers::isKing(int tile){
    return (Board_[tile].has_Bking || Board_[tile].has_Rking);
}
void Checkers::makeKing(int tile){
    
}
pair<bool,vector<int>> Checkers::possibleMoves(int tile, pair<bool, vector<int> > cuts){
    //need to consider how to scan for moves based on the type of piece it is
    //
    bool isCutting;
    vector<int> moves;
    int type = getType(tile);
    bool king = isKing(tile);
    if(cuts.first){
        //cout<<"we got here";
        isCutting = cuts.first;
        moves = cuts.second;
    }
    else{
        isCutting = false;
        if(!isOccupied(Board_[tile].up_tiles.first) && (type == 0 ||king))
            moves.push_back(Board_[tile].up_tiles.first);
        if(!isOccupied(Board_[tile].up_tiles.second) && (type == 0 ||king))
            moves.push_back(Board_[tile].up_tiles.second);
        if(!isOccupied(Board_[tile].down_tiles.second) && (type == 1 ||king))
            moves.push_back(Board_[tile].down_tiles.second);
        if(!isOccupied(Board_[tile].down_tiles.first) && (type == 1 ||king))
            moves.push_back(Board_[tile].down_tiles.first);
    }
    return make_pair(isCutting,moves);
}
int Checkers::findCutPiece(int tile, int dest){
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
