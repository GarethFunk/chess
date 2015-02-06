#ifndef head
#define head
#include <iostream>
#include <string>
#include <cmath>
#define white 0
#define black 1


using namespace std;

enum types {pawn, rook, knight, bishop, queen, king};

//Prototypes
void draw_board();
string get_rank(int rank);
int parse(string input);
void initialise();
bool coordinate_switch(string a, string b);
int score_board(int colour);
bool do_move(int rank, int file, int x, int y);
bool do_move(int rank, int file, int x, int y, bool sumo);
bool checkcheck(int colour);
bool checkcheck(int colout, int rank, int file, int x, int y);
bool checkcheckmate(int colour);

//Variables
string command;
int final_args[4];
bool turn = white; //use turn = !turn to switch //white == 0; black == 1;
int turn_counter; 
bool check_flag = false;

#include "pieces.cpp"

//Piece Declaration
Pawn a2 (6, 0, white);
Pawn b2 (6, 1, white);
Pawn c2 (6, 2, white);
Pawn d2 (6, 3, white);
Pawn e2 (6, 4, white);
Pawn f2 (6, 5, white);
Pawn g2 (6, 6, white);
Pawn h2 (6, 7, white);
Pawn a7 (1, 0, black);
Pawn b7 (1, 1, black);
Pawn c7 (1, 2, black);
Pawn d7 (1, 3, black);
Pawn e7 (1, 4, black);
Pawn f7 (1, 5, black);
Pawn g7 (1, 6, black);
Pawn h7 (1, 7, black);
Rook a1 (7, 0, white);
Knight b1 (7, 1, white);
Bishop c1 (7, 2, white);
Queen d1 (7, 3, white);
King e1 (7, 4, white);
Bishop f1 (7, 5, white);
Knight g1 (7, 6, white);
Rook h1 (7, 7, white);
Rook a8 (0, 0, black);
Knight b8 (0, 1, black);
Bishop c8 (0, 2, black);
Queen d8 (0, 3, black);
King e8 (0, 4, black);
Bishop f8 (0, 5, black);
Knight g8 (0, 6, black);
Rook h8 (0, 7, black);

//Other Functions
int score_board(int colour){
	int total_value = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j] != NULL){
				if(board[i][j]->colour == colour){
					total_value += board[i][j]->value;
				}
			}
		}
	}
	return total_value;
}

bool do_move(int rank, int file, int x, int y){
	piece* piece_buffer = board[x][y];
	board[x][y] = board[rank][file];
	board[rank][file] = NULL;
	if(checkcheck(board[x][y]->colour)){ //if the proposed move puts you in check
		cout<<"Move would result with you in check"<<endl;
		//reset pieces to how they were
		board[rank][file] = board[x][y];
		board[x][y] = piece_buffer;
		return false;
	}
	else{		//move does not put you in check
		//update piece properties
		board[x][y]->rank = x;
		board[x][y]->file = y;
		board[x][y]->move_count++;
		draw_board();
		turn = !turn;
		turn_counter++;
		check_flag = checkcheck(!(board[x][y]->colour)); //check if other team is now in check
		return true;
	}
}

bool do_move(int rank, int file, int x, int y, bool sumo){
	if(sumo == true){
	board[x][y] = board[rank][file];
	board[rank][file] = NULL;
	board[x][y]->rank = x;
	board[x][y]->file = y;
	board[x][y]->move_count++;
	draw_board();
	return 1;
	}
	else{
		return do_move(rank, file, x, y);
	}
}

bool checkcheck(int colour){
	//find the correct king
	int x = 8;
	int y = 8;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j] != NULL && board[i][j]->type == king){
				if(board[i][j]->colour == colour){	//found the right king
					x = i;
					y = j;
					break;
				}
			}
		}
		if(x==i) break;
	}
	int i, j;
	//check left
	i = y -1;
	for(i; i>=0; i--){
		if(board[x][i] != NULL && (board[x][i]->type == rook || board[x][i]->type == queen) && board[x][i]->colour != colour ) return true; //found enemy piece with clear line of sight.
		if(i == y-1 && board[x][i] != NULL && board[x][i]->type == king) return true; //found king
		if(board[x][i] != NULL) break;	//found piece blocking
	}
	//cout<<"checked left"<<endl;
	//check right
	i = y +1;
	for(i; i<8; i++){
		if(board[x][i] != NULL && (board[x][i]->type == rook || board[x][i]->type == queen) && board[x][i]->colour != colour) return true; //found enemy piece with clear line of sight.
		if(i == y+1 && board[x][i] != NULL && board[x][i]->type == king) return true; //found king
		if(board[x][i] != NULL) break;	//found piece blocking
	}
	//cout<<"checked right"<<endl;
	//check down
	i = x + 1;
	for(i; i<8; i++){
		if(board[i][y] != NULL && (board[i][y]->type == rook || board[i][y]->type == queen) && board[i][y]->colour != colour) return true; //found enemy piece with clear line of sight.
		if(i == x+1 && board[i][y] != NULL && board[i][y]->type == king) return true; //found king
		if(board[i][y] != NULL) break;	//found piece blocking
	}
	//cout<<"checked down"<<endl;
	//check up
	i = x - 1;
	for(i; i>=0; i--){
		if(board[i][y] != NULL && (board[i][y]->type == rook || board[i][y]->type == queen) && board[i][y]->colour != colour) return true; //found enemy piece with clear line of sight.
		if(i == x-1 && board[i][y] != NULL && board[i][y]->type == king) return true; //found king
		if(board[i][y] != NULL) break;	//found piece blocking
	}
	//cout<<"checked up"<<endl;
	//check diagonal up right
	i = x - 1;
	j = y + 1;
	while(i>=0 && j<8){
		if(board[i][j] != NULL && (board[i][j]->type == bishop || board[i][j]->type == queen) && board[i][j]->colour != colour) return true; //found enemy piece with clear line of sight.
		if(i == x-1 && board[i][j] != NULL && board[i][j]->type == king) return true; //found king
		if(board[i][j] != NULL) break;	//found piece blocking
		i--;
		j++;
	}
	//cout<<"checked up right"<<endl;
	//check diagonal up left
	i = x - 1;
	j = y - 1;
	while(i>=0 && j>=0){
		if(board[i][j] != NULL && (board[i][j]->type == bishop || board[i][j]->type == queen) && board[i][j]->colour != colour) return true; //found enemy piece with clear line of sight.
		if(i == x-1 && board[i][j] != NULL && board[i][j]->type == king) return true; //found king
		if(board[i][j] != NULL) break;	//found piece blocking
		i--;
		j--;

	}
	//cout<<"checked up left"<<endl;
	//check diagonal down right
	i = x + 1;
	j = y + 1;
	while(i<8 && j<8){
		if(board[i][j] != NULL && (board[i][j]->type == bishop || board[i][j]->type == queen) && board[i][j]->colour != colour) return true; //found enemy piece with clear line of sight.
		if(i == x+1 && board[i][j] != NULL && board[i][j]->type == king) return true; //found king
		if(board[i][j] != NULL) break;	//found piece blocking
		i++;
		j++;
	}
	//cout<<"checked down right"<<endl;
	//check diagonal down left
	i = x + 1;
	j = y - 1;
	while(i<8 && j>=0){
		if(board[i][j] != NULL && (board[i][j]->type == bishop || board[i][j]->type == queen) && board[i][j]->colour != colour) return true; //found enemy piece with clear line of sight.
		if(i == x+1 && board[i][j] != NULL && board[i][j]->type == king) return true; //found king
		if(board[i][j] != NULL) break;	//found piece blocking
		i++;
		j--;
	}
	//cout<<"checked down left"<<endl;
	//check knights
	int knight_possible_locations[8][2]{
		{x-2, y-1},
		{x-2, y+1},
		{x-1, y-2},
		{x-1, y+2},
		{x+1, y-2},
		{x+1, y+2},
		{x+2, y-1},
		{x+2, y+1},
	};
	for(i = 0; i < 8; i++){
		int r = knight_possible_locations[i][0];
		int	f = knight_possible_locations[i][1];
		if(r>=0 && r<8 && f>=0 && f<8){	//check coordinates are valid
			if(board[r][f] != NULL && board[r][f]->colour != colour && board[r][f]->type == knight) return true;	//found enemy knight in valid location
		}
	}
	//cout<<"checked knights"<<endl;
	//check pawns
	if(colour == white){		//check up the board for black pawns
		i = x - 1;
		j = y + 1; //on the right
		if(board[i][j] != NULL && board[i][j]->colour != colour && board[i][j]->type == pawn) return true;	//found enemy pawn in valid location
		j = y - 1; //on the left
		if(board[i][j] != NULL && board[i][j]->colour != colour && board[i][j]->type == pawn) return true;	//found enemy pawn in valid location
	}
	else{		//check down the board for white pawns
		i = x + 1;
		j = y + 1;	//on the right 
		if(board[i][j] != NULL && board[i][j]->colour != colour && board[i][j]->type == pawn) return true;	//found enemy pawn in valid location
		j = y - 1; //on the left
		if(board[i][j] != NULL && board[i][j]->colour != colour && board[i][j]->type == pawn) return true;	//found enemy pawn in valid location
	}
	//cout<<"checked pawns"<<endl;
	return false; //all tests passed without returning true
}

bool checkcheck(int colout, int rank, int file, int x, int y){	//ONLY GIVE THIS FUNCTION LEGAL COORDINATES
	piece* piece_buffer = board[x][y];
	board[x][y] = board[rank][file];
	board[rank][file] = NULL;
	if(checkcheck(board[x][y]->colour)){ //if the proposed move would result in check
		//reset pieces to how they were
		board[rank][file] = board[x][y];
		board[x][y] = piece_buffer;
		return true;
	}
	else{	//reset pieces to how they were
		board[rank][file] = board[x][y];
		board[x][y] = piece_buffer;
		return false;
	}
}

bool checkcheckmate(int colour){	//only call this function if the specified colour is in check! 
	for(int rank = 0; rank < 8; rank++){
		for(int file = 0; file < 8; file++){
			//cout<<"Checking "<<rank<<" "<<file<<endl;
			if(board[rank][file] != NULL && board[rank][file]->colour == colour){	//If there is a piece on this square and it is of the same colour
				for(int x = 0; x < 8; x++){
					for(int y = 0; y < 8; y++){
						if(board[rank][file]->islegal(x, y) == true){	//if move legal
							if(checkcheck(colour, rank, file, x, y) == false){ //if move would result in you not being in check
								//cout<<"There is a move which could get you out of check, mate."<<endl;
								return false;
							}
						}
					}
				}
			}
		}
	}
	//have scanned entire board for possible moves, not yet returned from the function therefore checkmate
	return true;
}
#endif