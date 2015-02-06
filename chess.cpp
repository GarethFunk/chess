/*Chess
Gareth Funk - 2015
*/

#include "header.h"
#include "drawing.cpp"
#include "parser.cpp"


 main(){
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
				if(stalemate(white)){
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
				if(stalemate(black)){
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
	//White Pawns
	board[6][0] = &a2;
	board[6][1] = &b2;
	board[6][2] = &c2;
	board[6][3] = &d2;
	board[6][4] = &e2;
	board[6][5] = &f2;
	board[6][6] = &g2;
	board[6][7] = &h2;
	//Black Pawns
	board[1][0] = &a7;
	board[1][1] = &b7;
	board[1][2] = &c7;
	board[1][3] = &d7;
	board[1][4] = &e7;
	board[1][5] = &f7;
	board[1][6] = &g7;
	board[1][7] = &h7;
	//White back row
	board[7][0] = &a1;	//rook
	board[7][1] = &b1;	//knight
	board[7][2] = &c1;	//bishop
	board[7][3] = &d1;	//queen
	board[7][4] = &e1;	//king
	board[7][5] = &f1;	//bishop
	board[7][6] = &g1;	//knight
	board[7][7] = &h1;	//rook
	//Black back row
	board[0][0] = &a8;	//rook
	board[0][1] = &b8;	//knight
	board[0][2] = &c8;	//bishop
	board[0][3] = &d8;	//queen
	board[0][4] = &e8;	//king
	board[0][5] = &f8;	//bishop
	board[0][6] = &g8;	//knight
	board[0][7] = &h8;	//rook
	draw_board();
}
