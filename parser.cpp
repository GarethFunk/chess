#include "header.h"

int parse(string input){	//return states: -1 = quit game; 0 = failed to parse anything; 1 = parsed successfully;
	//extract command
	int open, close;
	string arguments;
	open = input.find_first_of("(");
	close = input.find_last_of(")");
	if(open != -1 && close != -1){	//found an open and close bracket
		command = input;
		command = command.erase(open, (command.length()-open));	//strip arguments off command
		arguments = input;
		arguments = arguments.erase(0, command.length()+1);	//remove command and first bracket
		arguments = arguments.erase(arguments.length()-1, 1);//remove last bracket
		//remove whitespace from arguments
		std::string::iterator end_pos = std::remove(arguments.begin(), arguments.end(), ' ');
		arguments.erase(end_pos, arguments.end());
	}
	else if(open == -1 && close == -1){	//no arguments
		command = input;
	}
	else{
		cout<<"Confused by brackets..."<<endl;
		return 0;
	}

	//do command
	if(command == "move"){
		if(parse_arguments(arguments)) board[final_args[0]][final_args[1]]->do_move(final_args[2], final_args[3]);
	}
	else if(command == "sumo"){
		if(parse_arguments(arguments)) board[final_args[0]][final_args[1]]->do_move(final_args[2], final_args[3], true);
	}
	else if(command == "lsmv"){
		if(parse_arguments(arguments)) board[final_args[0]][final_args[1]]->getmoves(true);
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

bool coordinate_switch(string a, int start_pos){	//only give string of length 2
	char *arg11 = &a[0];
	char *arg12 = &a[1];
	char args[2];
	args[0] = *arg11;
	args[1] = *arg12;
	final_args[start_pos] = 7 - (args[1] - '0' -1);	//convert rank
	final_args[start_pos + 1] = args[0] - 97;		//convert file
	//check arguments are refer to locations on the board.
	if(final_args[start_pos] < 0 || final_args[start_pos] > 7 || final_args[start_pos+1] < 0 || final_args[start_pos+1] > 7){
		cout<<"Coordinates specified do not lie on the board"<<endl;
		return false;
	}
	return true;
}

bool parse_arguments(string arguments){	//give this function a comma separated list of arguments with no whitespace
	int comma = 0;
	int length = arguments.length();
	for(int i = 0; i<length; i++){
		if(arguments[i]==',') comma ++;
	}
	switch(comma){
		case 0 :
			if(coordinate_switch(arguments, 0) && board[final_args[0]][final_args[1]] != NULL) return true;
			else if(board[final_args[0]][final_args[1]] == NULL) cout<<"Error: There is nothing at the specified coordinate"<<endl;
			return false;
			break;
		case 1 :
			if(coordinate_switch(arguments.substr(0,2), 0) && coordinate_switch(arguments.substr(3,2), 2) && board[final_args[0]][final_args[1]] != NULL) return true;
			else if(board[final_args[0]][final_args[1]] == NULL) cout<<"Error: There is nothing at the specified target coordinate"<<endl;
			return false;
			break;
		default :
			cout<<"Too many commas in input arguments."<<endl;
			return false;
	}
}