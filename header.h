#ifndef head
#define head
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#define white 0
#define black 1
#define ENGINE_DEPTH 3	

using namespace std;

enum types {pawn, rook, knight, bishop, queen, king};
struct a_move {
	int rank;
	int file;
	int x;
	int y;
	int score;
	bool capture;
};

//Prototypes
void draw_board();
string get_rank(int rank);
int parse(string input);
bool parse_arguments(string arguments);
void initialise();
bool coordinate_switch(string a, int start_pos);
int score_board(int colour);
bool checkcheck(int colour);
bool checkcheck(int colour, int rank, int file, int x, int y);
bool checkcheck(int colour, a_move target_move);
bool checkcheckmate(int colour);
bool checkstalemate(int colour);
//engine functions
bool engine_move(int colour);
vector<a_move> get_all_moves(int colour);
int evaluate(int colour);
int minimax(a_move node, int depth, int colour);

//Variables
bool turn = white; //use turn = !turn to switch //white == 0; black == 1;
int turn_counter; 
bool check_flag = false;
string command;
int final_args[4];
int chess_board_score;


#include "piecetables.cpp"
#include "pieces.cpp"

bool Pawn::promote(int new_type){		//defined here because uses classes defined in pieces.cpp (included above this line)
	//create new object
	//insert address of new object into array
	switch(new_type){
		case 1 :
		{
			board[rank][file] = new Rook(rank, file, colour);
			break;
		}
		case 2 :
		{
			board[rank][file] = new Knight(rank, file, colour);
			break;
		}
		case 3 :
		{
			board[rank][file] = new Bishop(rank, file, colour);	
			break;
		}
		case 4 :
		{
			board[rank][file] = new Queen(rank, file, colour);
			break;
		}
		default :
			cout<<"Not a valid selection: try again."<<endl;
			return false;
	}
	return true;
}

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
		if(x != 0){		//check not on rank 8
			i = x - 1;
			j = y + 1; //on the right
			if(board[i][j] != NULL && board[i][j]->colour != colour && board[i][j]->type == pawn) return true;	//found enemy pawn in valid location
			j = y - 1; //on the left
			if(board[i][j] != NULL && board[i][j]->colour != colour && board[i][j]->type == pawn) return true;	//found enemy pawn in valid location
		}
	}
	else{		//check down the board for white pawns
		if(x != 7){		//check not on rank 1
			i = x + 1;
			j = y + 1;	//on the right 
			if(board[i][j] != NULL && board[i][j]->colour != colour && board[i][j]->type == pawn) return true;	//found enemy pawn in valid location
			j = y - 1; //on the left
			if(board[i][j] != NULL && board[i][j]->colour != colour && board[i][j]->type == pawn) return true;	//found enemy pawn in valid location
		}
	}
	//cout<<"checked pawns"<<endl;
	return false; //all tests passed without returning true
}

bool checkcheck(int colour, int rank, int file, int x, int y){	//ONLY GIVE THIS FUNCTION LEGAL COORDINATES
	piece* piece_buffer = board[x][y];
	board[x][y] = board[rank][file];
	board[x][y]->rank = x;
	board[x][y]->file = y;
	board[rank][file] = NULL;
	//cout<<"Moved pieces"<<endl;
	if(checkcheck(board[x][y]->colour)){ //if the proposed move would result in check
		//reset pieces to how they were
		board[rank][file] = board[x][y];
		board[x][y] = piece_buffer;
		board[rank][file]->rank = rank;
		board[rank][file]->file = file;
		return true;
	}
	else{	//reset pieces to how they were
		board[rank][file] = board[x][y];
		board[x][y] = piece_buffer;
		board[rank][file]->rank = rank;
		board[rank][file]->file = file;
		return false;
	}
}

bool checkcheck(int colour, a_move target_move){
	return checkcheck(colour, target_move.rank, target_move.file, target_move.x, target_move.y);
}

bool checkcheckmate(int colour){	//only call this function if the specified colour is in check! otherwise might be stalemate!
	vector<a_move> piece_moves;
	for(int rank = 0; rank < 8; rank++){
		for(int file = 0; file < 8; file++){
			//cout<<"Checking "<<rank<<" "<<file<<endl;
			if(board[rank][file] != NULL && board[rank][file]->colour == colour){	//If there is a piece on this square and it is of the same colour
				//if there is a legal move which results in you not being in check => not checkmate
				piece_moves = board[rank][file]->getmoves(false);
				if(piece_moves.size() != 0) return false;
			}
		}
	}
	//have scanned entire board for possible moves, not yet returned from the function therefore checkmate
	return true;
}

bool checkstalemate(int colour){	//only call this if NOT in check! otherwise might be checkmate!
	vector<a_move> piece_moves;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j] != NULL && board[i][j]->colour == colour){	//found a piece of the correct colour
				//check to see if this piece has any legal moves
				piece_moves = board[i][j]->getmoves(false);
				if(piece_moves.size() != 0) return false;
			}
		}
	}
	//check all pieces of given colour, none had any legal moves.
	return true;
}	

bool engine_move(int colour){
	vector<a_move> turn_moves = get_all_moves(colour);
	int num_moves = turn_moves.size();
	int best_move;
	int best_value_white = std::numeric_limits<int>::min();
	int best_value_black = std::numeric_limits<int>::max();
	for(int i = 0; i < num_moves; i++){
		turn_moves[i].score = minimax(turn_moves[i], ENGINE_DEPTH, colour);
		cout<<"Move "<<i<<" out of "<<num_moves<<" has score "<<turn_moves[i].score<<endl;
		if(colour == white){	//maximise
			if(turn_moves[i].score > best_value_white){
				best_value_white = turn_moves[i].score;
				best_move = i;
			}
		}
		if(colour == black){	//minimise
			if(turn_moves[i].score < best_value_black){
				best_value_black = turn_moves[i].score;
				best_move = i;
			}
		}
	}	
	//cout<<"All possible moves for your team:"<<endl;
	/*int sizzzze = turn_moves.size();
	for(int i = 0; i < sizzzze; i++){
		cout<<turn_moves[i].rank<<" "<<turn_moves[i].file<<" to "<<turn_moves[i].x<<" "<<turn_moves[i].y<<". Score = "<<turn_moves[i].score<<endl;
	}*/
	cout<<"Best move is "<<turn_moves[best_move].rank<<" "<<turn_moves[best_move].file<<" to "<<turn_moves[best_move].x<<" "<<turn_moves[best_move].y<<". Score = "<<turn_moves[best_move].score<<endl;
	board[turn_moves[best_move].rank][turn_moves[best_move].file]->do_move(turn_moves[best_move].x, turn_moves[best_move].y);
}

int minimax(a_move node, int depth, int colour){
	int best_value;
	int i;
	//make the move
	piece* piece_buffer = board[node.x][node.y];
	board[node.x][node.y] = board[node.rank][node.file];
	board[node.x][node.y]->rank = node.x;
	board[node.x][node.y]->file = node.y;
	board[node.rank][node.file] = NULL;
	//draw_board();
	//get new moves
	if(depth == 0){
		//undo the move
		//cout<<"Reached the bottom of the tree"<<endl;
		int score = evaluate(colour);
		board[node.rank][node.file] = board[node.x][node.y];
		board[node.x][node.y] = piece_buffer;
		board[node.rank][node.file]->rank = node.rank;
		board[node.rank][node.file]->file = node.file;
		return score;
	}
	//cout<<"Getting Level "<<depth<<" moves..."<<endl;
	vector<a_move> turn_moves = get_all_moves(!colour);	//get moves for next player's turn
	int num_moves = turn_moves.size();
	if(num_moves == 0){
		//undo the move
		//cout<<"This is a terminal node"<<endl;
		int score = evaluate(colour);
		board[node.rank][node.file] = board[node.x][node.y];
		board[node.x][node.y] = piece_buffer;
		board[node.rank][node.file]->rank = node.rank;
		board[node.rank][node.file]->file = node.file;
		return score;
	}
	if(colour == white){
		best_value = std::numeric_limits<int>::max();
		for(i = 0; i<num_moves; i++){
			//cout<<"Calling minimax at depth "<<depth<<" move "<<i+1<<" of "<<num_moves<<" for white"<<endl;
			int val = minimax(turn_moves[i], depth-1, black);
			if(val < best_value){
				best_value = val;
			}
		}
		//undo the move
		board[node.rank][node.file] = board[node.x][node.y];
		board[node.x][node.y] = piece_buffer;
		board[node.rank][node.file]->rank = node.rank;
		board[node.rank][node.file]->file = node.file;
		return best_value;
	}
	else{
		best_value = std::numeric_limits<int>::min();
		for(i = 0; i<num_moves; i++){
			//cout<<"Calling minimax at depth "<<depth<<" move "<<i+1<<" of "<<num_moves<<" for black"<<endl;
			int val = minimax(turn_moves[i], depth-1, white);
			if(val > best_value){
				best_value = val;
			}
		}
		//undo the move
		board[node.rank][node.file] = board[node.x][node.y];
		board[node.x][node.y] = piece_buffer;
		board[node.rank][node.file]->rank = node.rank;
		board[node.rank][node.file]->file = node.file;
		return best_value;
	}
}

vector<a_move> get_all_moves(int colour){
	vector<a_move> turn_moves;
	//get list of moves we could make
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j] != NULL && board[i][j]->colour == colour){
				//cout<<"checking square "<<i<<" "<<j<<" for possible moves"<<endl;
				vector<a_move> current_square_moves = board[i][j]->getmoves(false);
				turn_moves.insert(turn_moves.end(), current_square_moves.begin(), current_square_moves.end());
			}			
		}
	}
	return turn_moves;
}

int evaluate(int colour){
	int score = 0;
	int r, f;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j] != NULL){
				//Caclulate material value
				score += board[i][j]->value;
				//cout<<"Piece worth "<<board[i][j]->value<<endl;
				//calculate position value
				if(board[i][j]->colour == black){
					//switch coordinates for position value lookup
					r = 7-i;
					f = j;
				}
				else{
					r = i;
					f = j;
				}
				int position = 0;
				switch(board[i][j]->type){
					case pawn :
						position = pawn_table[r][f];
						break;
					case knight :
						position = knight_table[r][f];
						break;
					case bishop :
						position = bishop_table[r][f];
						break;
					case king :
						position = king_table[r][f];
						break;
					default:
						break;
				}
				//cout<<"Piece position = "<<position<<endl;
				if(board[i][j]->colour == black) score -= position;
				else score += position;
				//mobility

				//bonuses

			}
		}			
	}
	return score;

}


#endif