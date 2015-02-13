#include "header.h"

int parse(string input){
	int open, close, comma;
	if(input.find("(") != -1 && input.find(")") != -1){
		open = input.find_first_of("(");
		close = input.find_last_of(")");
		command = input;
		command = command.erase(open, (command.length()-open));
	}
	else{
		command = input;
	}
	if(command == "move"){
		//parse arguments
		string arguments = input;
		arguments = arguments.erase(0,open+1); //LENGTH TO ERASE DEPENDS ON LENGTH OF KEYWORD!
		arguments = arguments.erase(arguments.length()-1, 1);
		if(arguments.find_first_of(",") != -1){		//if comma found
			comma = arguments.find_first_of(",");
			string argument1 = arguments;
			string argument2 = arguments;
			argument1 = argument1.erase(2, argument1.length()-2);
			switch(arguments.length()){
				case 5: 	//no spaces
					argument2 = argument2.erase(0, comma+1);
					break;
				case 6:		//assume one space after the comma.
					argument2 = argument2.erase(0, comma +2);
					break;
				default:
					cout<<"Please use the input format specified. Type 'help' for more information."<<endl;
			}
			//change from chess coords to array coords
			if(coordinate_switch(argument1, argument2)){
				//make the move
				board[final_args[0]][final_args[1]]->do_move(final_args[2], final_args[3]);
			}
			else{
				cout<<"Error: Invalid coordinates"<<endl;
			}
		}
		else cout<<"Please use the input format specified. Type 'help' for more information."<<endl;
		
		
	}
	else if(command == "sumo"){
		//parse arguments
		string arguments = input;
		arguments = arguments.erase(0, 5); //LENGTH TO ERASE DEPENDS ON LENGTH OF KEYWORD!
		arguments = arguments.erase(arguments.length()-1, 1);
		comma = arguments.find_first_of(",");
		string argument1 = arguments;
		string argument2 = arguments;
		argument1 = argument1.erase(2, argument1.length()-2);
		argument2 = argument2.erase(0, comma+1);
		//change from chess coords to array coords
		if(coordinate_switch(argument1, argument2)){
			board[final_args[0]][final_args[1]]->do_move(final_args[2], final_args[3], true);
		}
		else{
			cout<<"Error: Invalid coordinates (refers to an invalid location)"<<endl;
		}
	}

	else if(command == "help"){
		cout<<	"move(x1,y2)\tMoves the piece at x1 to y2\n"<<
				"stalemate\tDeclares a stalemate to which both players must agree\n"<<
				"resign\t\tResign from the game. The other player will win\n"<<
				"exit\t\tQuits the program and returns to the terminal\n"<<endl;
	}
	else if(command == "exit"){
		return -1;
	}
	else if(command == "scrw"){
		cout<<"White board is valued at: "<<score_board(white)<<endl;
	}
	else if(command == "scrb"){
		cout<<"Black board is valued at: "<<score_board(black)<<endl;
	}
	else if(command == "chkw"){
		cout<<"White king check status = "<<checkcheck(white)<<endl;
	}
	else if(command == "chkb"){
		cout<<"Black king check status = "<<checkcheck(black)<<endl;
	}
	else if(command == "turn"){
		turn = !turn;
	}
	else if(command == "stalemate"){
		char ans;
		turn = !turn;
		if(turn == white){
			cout<<"White, do you agree to a stalemate? (y/n)"<<endl;
		}
		else{
			cout<<"Black, do you agree to a stalemate? (y/n)"<<endl;
		}
		cin>>ans;
		if(ans == 'y'){
			cout<<"Stalemate reached"<<endl;
			return -1; //tell main() the game has ended
		}
		else if(ans == 'n'){
			turn = !turn;
			if(turn == white)cout<<"White to move"<<endl;
			else cout<<"Black to move"<<endl;
			return 1; //tell main() the game has ended
		}
	}
	else if(command == "resign"){
		if(turn == white) cout<<"White resigns. Black wins."<<endl;
		else cout<<"Black resigns. White wins."<<endl;
		return -1;
	}
	else{
		cout<<"Command not found. Enter 'help' for a list of commands."<<endl;
	}
	return 1;
}

bool coordinate_switch(string a, string b){
	if(a.length() == 2 && b.length() == 2){
		char *arg11 = &a[0];
		char *arg12 = &a[1];
		char *arg21 = &b[0];
		char *arg22 = &b[1];
		char args[4];
		args[0] = *arg11;
		args[1] = *arg12;
		args[2] = *arg21;
		args[3] = *arg22;
		final_args[0] = 7 - (args[1] - '0' -1);
		final_args[1] = args[0] - 97;
		final_args[2] = 7 - (args[3] - '0' -1);
		final_args[3] = args[2] - 97;
		int j = 0;			//counter to check all arguments are valid.
		for(int i = 0; i<4; i++){
			if(final_args[i] >= 0 && final_args[i] <= 7){
				j++;
			}
			else{
				return false;
			}
		}
		if(j == 4 && board[final_args[0]][final_args[1]] != NULL){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		cout<<"Error: Invalid coordinates"<<endl;
	}
}


