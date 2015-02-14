/*Chess
Gareth Funk - 2015
*/

#include "header.h"
#include "drawing.cpp"
#include "parser.cpp"


int main(){
 	initialise();
	cout<<"White to move"<<endl;
	while(1==1){
		getline(cin, command);
		if(command != ""){
			if(parse(command) == -1){
				return 1;
			}
			else if(turn == white){
				if(check_flag){
					if(checkcheckmate(white)){
						cout<<"White is checkmated. Black wins."<<endl;
						return 1;
					}
					else cout<<"White is in check!"<<endl;
				}
				else if(checkstalemate(white)){		//not in check, test stalemate
					cout<<"Stalemate reached. Game Over."<<endl;
					return 1;
				}
				cout<<"White to move"<<endl;
			}
			else if(turn == black){
				if(check_flag){
					if(checkcheckmate(black)){
						cout<<"Black is checkmated. White wins."<<endl;
						return 1;
					}
					else cout<<"Black is in check!"<<endl;
				}
				else if(checkstalemate(black)){		//not in check, test stalemate
					cout<<"Stalemate reached. Game Over."<<endl;
					return 1;
				}
				cout<<"Black to move"<<endl;
			}
			
		}
	}
	return 1;
}

void initialise(){
	turn = 0;
	turn_counter = 1;
	//Pawns
	for(int i = 0; i<8; i++){
		board[6][i] = new Pawn(6, i, white);	//white pawn
		board[1][i] = new Pawn(1, i, black);	//black pawn
	}
	//White back row
	board[7][0] = new Rook(7, 0, white);	//rook
	board[7][1] = new Knight(7, 1, white);	//knight
	board[7][2] = new Bishop(7, 2, white);	//bishop
	board[7][3] = new Queen(7, 3, white);	//queen
	board[7][4] = new King(7, 4, white);	//king
	board[7][5] = new Bishop(7, 5, white);	//bishop
	board[7][6] = new Knight(7, 6, white);	//knight
	board[7][7] = new Rook(7, 7, white);	//rook
	//Black back row
	board[0][0] = new Rook(0, 0, black);	//rook
	board[0][1] = new Knight(0, 1, black);	//knight
	board[0][2] = new Bishop(0, 2, black);	//bishop
	board[0][3] = new Queen(0, 3, black);	//queen
	board[0][4] = new King(0, 4, black);	//king
	board[0][5] = new Bishop(0, 5, black);	//bishop
	board[0][6] = new Knight(0, 6, black);	//knight
	board[0][7] = new Rook(0, 7, black);	//rook
	draw_board();
}
