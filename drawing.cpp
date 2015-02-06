#include "header.h"


void draw_board(){
	cout<<"\n    a   b   c   d   e   f   g   h  "<<endl;
	int n = 8;
	for(int i=0; i<17; i++){
		if(i%2 == 0){
			cout<<"  ---------------------------------"<<endl;
		}
		else {
			cout<<n<<get_rank((i+1)/2)<<n<<endl;
			n--;
		}
	}
	cout<<"    a   b   c   d   e   f   g   h  \n"<<endl;
}

string get_rank(int rank){
	rank--;
	string spacer = " | ";
	string line = spacer;
	for(int i = 0; i<8; i++){
		if(board[rank][i] != 0){
			if((*board[rank][i]).colour == black){
				switch ((*board[rank][i]).type){
					case pawn :
						line = line + "♟";
						break;
					case rook :
						line = line + "♜";
						break;
					case knight :
						line = line + "♞";
						break;
					case bishop :
						line = line + "♝";
						break;
					case queen :
						line = line + "♛";
						break;
					case king :
						line = line + "♚";
						break;
					default :
						line = line + "!";
						break;
					}
				}
			else if((*board[rank][i]).colour == white){
				switch ((*board[rank][i]).type){
					case pawn :
						line = line + "♙";
						break;
					case rook :
						line = line + "♖";
						break;
					case knight :
						line = line + "♘";
						break;
					case bishop :
						line = line + "♗";
						break;
					case queen :
						line = line + "♕";
						break;
					case king :
						line = line + "♔";
						break;
					default :
						line = line + "!";
						break;
				}
			}
		}
		else{
			line = line + " ";
		}
		line = line + spacer;
	}
	return line;
}