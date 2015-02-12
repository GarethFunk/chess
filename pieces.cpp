class piece {
public:
	int colour;
	int rank;
	int file;
	types type;
	int move_count = 0;
	int value;
	bool do_move(int x, int y);
	bool do_move(int x, int y, bool sumo);	
	virtual bool islegal(int x, int y){
		cout<<"Error: method for checking legality not found"<<endl;
		return false;
	}
	vector<a_move> getmoves(){
		vector<a_move> all_moves;
		for(int i = rank -1; i <=rank + 1; i++){
			for(int j = file -1; j <= file + 1; j++){
				if(i >= 0 && i <=7 && j>=0 && j<=7 && islegal(i, j) && checkcheck(colour, rank, file, i, j) == false){	
				//If the move is a valid coordinate and is legal and does not result in check. 
					all_moves.push_back({rank, file, i, j});
				}
			}
		}
		
		/*cout<<"piece at "<<rank<<" "<<file<<" can move: "<<endl;
		for(int i = 0; i < all_moves.size(); i++){
			cout<<all_moves[i].x<<" "<<all_moves[i].y<<endl;
		}*/
		return all_moves;
	}
};

//board[rank, rows][file, columns]
piece* board[8][8]{
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}};

const int squares[8][8]{
	{white, black, white, black, white, black, white, black},
	{black, white, black, white, black, white, black, white},
	{white, black, white, black, white, black, white, black},
	{black, white, black, white, black, white, black, white},
	{white, black, white, black, white, black, white, black},
	{black, white, black, white, black, white, black, white},
	{white, black, white, black, white, black, white, black},
	{black, white, black, white, black, white, black, white}};

bool piece::do_move(int x, int y){
	if(colour == turn){		//Check piece is allowed to move on this turn
		if(islegal(x, y)){		//Check move is legal
			if(checkcheck(colour, rank, file, x, y)){ //if the proposed move puts you in check
				cout<<"Move would result with you in check"<<endl;
				return false;
			}
			else{		//move does not put you in check
			//update piece properties and make the move
			board[x][y] = board[rank][file];
			board[rank][file] = NULL;
			rank = x;
			file = y;
			move_count++;
			draw_board();
			turn = !turn;
			turn_counter++;
			check_flag = checkcheck(!colour); //check if other team is now in check
			return true;
			}
		}
		else{
			cout<<"Move not legal"<<endl;
			return false;
		}
	}	
	else{
		cout<<"It is not your turn!"<<endl;
		return false;
	}
}

bool piece::do_move(int x, int y, bool sumo){
	if(sumo){
		//cout<<"sumoved"<<endl;
		//update piece properties and make the move
		board[x][y] = board[rank][file];
		board[rank][file] = NULL;
		board[x][y]->rank = x;
		board[x][y]->file = y;
		board[x][y]->move_count++;
		draw_board();
		return true;
	}
	else{
		return do_move(x, y);
	}
}

class Pawn: public piece {
private:
	bool promotion(int x, int y);

public: 
	virtual bool islegal(int x, int y){
		piece* target_piece = board[x][y];
		if(target_piece == NULL || target_piece->colour != colour){ //Check target square is either empty or has enemy piece on it
			if(colour == white){		//white rules i.e. can only move up the board
				if(rank - x == 1 && y == file && target_piece == NULL){ //moving one space forwards
					return true;
				}
				else if(rank - x == 2 && move_count == 0 && target_piece == NULL){ //moving two spaces forwards
					return true;
				}
				else if(rank - x == 1 && abs(y - file) == 1 && target_piece != NULL){ //taking an enemy piece 
					return true;
				}
				else{
					return false;
				}
			}
			else{		//black rules i.e. can only move down the board. 
				if(x - rank == 1 && y == file && target_piece == NULL){ //moving one space forwards
					return true;
				}
				else if(x - rank == 2 && move_count == 0 && target_piece == NULL){ //moving two spaces forwards
					return true;
				}
				else if(x - rank == 1 && abs(y - file) == 1 && target_piece != NULL){ //taking an enemy piece 
					return true;
				}
				else{
					return false;
				}
			}	
		}
		else{
			return false;
		}
	}

	Pawn (int a, int b, int y){
		rank = a;
		file = b;
		colour = y;
		type = pawn;
		value = 1;
	};
};

class Rook: public piece {
public: 
	virtual bool islegal(int x, int y){
		piece* target_piece = board[x][y];
		if(target_piece == NULL || target_piece->colour != colour){ //Check target square is either empty or has enemy piece on it
			if(rank == x && y != file){ 		//moving along a row
				if(y > file){		//moving right
					//check path is clear
					int i = file +1;
					for(i; i<y; i++){
						if(board[rank][i] != NULL) break;
					}
					if(i == y) return true;
					else return false; //something in the way
				}
				else{		//moving left
					int i = file -1;
					for(i; i>y; i--){
						if(board[rank][i] != NULL) break;
					}
					if(i == y) return true;
					else return false; //something in the way
				}
			}
			else if(rank != x && file ==y){	//moving along a column
				if(x < rank){		//moving up
					//check path is clear
					int i = rank -1;
					for(i; i>x; i--){
						if(board[i][file] != NULL) break;
					}
					if(i == x) return true;
					else return false; //something in the way
				}
				else{		//moving down
					int i = rank +1;
					for(i; i<x; i++){
						if(board[i][file] != NULL) break;
					}
					if(i == x) return true;
					else return false; //something in the way
				}
			}
			else return false; //move not along rank or file
		}
		else{
			return false; //target square has friendly piece on it
		}
	}

	Rook (int a, int b, int y){
		rank = a;
		file = b;
		colour = y;
		type = rook;
		value = 5;
	};
};

class Knight: public piece {
public: 
	virtual bool islegal(int x, int y){
		piece* target_piece = board[x][y];
		if(target_piece == NULL || target_piece->colour != colour){ //Check target square is either empty or has enemy piece on it
			if(abs(rank - x) == 2 && abs(file - y) == 1){ //move in vertical L
				return true;
			}
			else if(abs(rank - x) == 1 && abs(file - y) == 2){ //move in horizontal L
				return true;
			}
			else return false; // move not in L shape
		}
		else{
			return false; //target square already has friendly piece on it
		}
	}

	Knight (int a, int b, int y){
		rank = a;
		file = b;
		colour = y;
		type = knight;
		value = 3;
	};
};

class Bishop: public piece {
public: 
	virtual bool islegal(int x, int y){
		piece* target_piece = board[x][y];
		if(target_piece == NULL || target_piece->colour != colour){ //Check target square is either empty or has enemy piece on it
			//Piece specific moves
			if(abs(rank - x) == abs(file - y )){		//check move is diagonal
				if(x > rank){ 		//moving down
					if(y > file){		//moving down & right
						int i = rank + 1;
						int j = file + 1;
						while(i < x && j < y){
							if(board[i][j] == NULL){
								i++;
								j++;
							}
							else break;
						}
						if(i == x && j == y) return true;
						else return false; //something in the way
					}
					else{	//moving down & left
						int i = rank + 1;
						int j = file - 1;
						while(i < x && j > y){
							if(board[i][j] == NULL){
								i++;
								j--;
							}
							else break;
						}
						if(i == x && j == y) return true;
						else return false; //something in the way
					}
				}
				else{ 		//moving up
					if(y > file){	//moving up & right
						int i = rank - 1;
						int j = file + 1;
						while(i > x && j < y){
							if(board[i][j] == NULL){
								i--;
								j++;
							}
							else break;
						}
						if(i == x && j == y) return true;
						else return false; //something in the way
					}
					else{	//moving up & left
						int i = rank - 1;
						int j = file - 1;
						while(i > x && j > y){
							if(board[i][j] == NULL){
								i--;
								j--;
							}
							else break;
						}
						if(i == x && j == y) return true;
						else return false; //something in the way
					}
				}
			}
			else return false; //move not file or diagonal
		}
		else{
			return false; //target square has friendly piece on it
		}
	}

	Bishop (int a, int b, int y){
		rank = a;
		file = b;
		colour = y;
		type = bishop;
		int square_colour = squares[a][b];
		value = 3;
	};
};

class Queen: public piece {
public: 
	virtual bool islegal(int x, int y){
		piece* target_piece = board[x][y];
		if(target_piece == NULL || target_piece->colour != colour){ //Check target square is either empty or has enemy piece on it
				//Piece specific moves
				if(rank == x && y != file){ 		//moving along a row
					if(y > file){		//moving right
						//check path is clear
						int i = file +1;
						for(i; i<y; i++){
							if(board[rank][i] != NULL) break;
						}
						if(i == y) return true;
						else return false; //something in the way
					}
					else{		//moving left
						int i = file -1;
						for(i; i>y; i--){
							if(board[rank][i] != NULL) break;
						}
						if(i == y) return true;
						else return false; //something in the way
					}
				}
				else if(rank != x && file ==y){	//moving along a column
					if(x < rank){		//moving up
						//check path is clear
						int i = rank -1;
						for(i; i>x; i--){
							if(board[i][file] != NULL) break;
						}
						if(i == x) return true;
						else return false; //something in the way
					}
					else{		//moving down
						int i = rank +1;
						for(i; i<x; i++){
							if(board[i][file] != NULL) break;
						}
						if(i == x) return true;
						else return false; //something in the way
					}
				}
				else if(abs(rank - x) == abs(file - y )){		//check move is diagonal
					if(x > rank){ 		//moving down
						if(y > file){		//moving down & right
							int i = rank + 1;
							int j = file + 1;
							while(i < x && j < y){
								if(board[i][j] == NULL){
									i++;
									j++;
								}
								else break;
							}
							if(i == x && j == y) return true;
							else return false; //something in the way
						}
						else{	//moving down & left
							int i = rank + 1;
							int j = file - 1;
							while(i < x && j > y){
								if(board[i][j] == NULL){
									i++;
									j--;
								}
								else break;
							}
							if(i == x && j == y) return true;
							else return false; //something in the way
						}
					}
					else{ 		//moving up
						if(y > file){	//moving up & right
							int i = rank - 1;
							int j = file + 1;
							while(i > x && j < y){
								if(board[i][j] == NULL){
									i--;
									j++;
								}
								else break;
							}
							if(i == x && j == y) return true;
							else return false; //something in the way
						}
						else{	//moving up & left
							int i = rank - 1;
							int j = file - 1;
							while(i > x && j > y){
								if(board[i][j] == NULL){
									i--;
									j--;
								}
								else break;
							}
							if(i == x && j == y) return true;
							else return false; //something in the way
						}
					}
				}
				else return false; //move not along rank, file or diagonal
			}
		else return false; //target square already has friednly piece on it
	}

	Queen (int a, int b, int y){
		rank = a;
		file = b;
		colour = y;
		type = queen;
		value = 9;
	};
};

class King: public piece {
public: 
	virtual bool islegal(int x, int y){
		piece* target_piece = board[x][y];
		//Piece specific moves
		if(target_piece == NULL || target_piece->colour != colour){ //Check target square is either empty or has enemy piece on it
			if(abs(rank - x) <= 1 && abs(file - y) <= 1){
				return true;
			}
			else return false; //move not of radius 1	
		}
		else return false; //target square already has frienly piece on it
	}
	King (int a, int b, int y){
		rank = a;
		file = b;
		colour = y;
		type = king;
		value = 0;
	};	
};