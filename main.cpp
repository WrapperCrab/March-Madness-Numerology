//main.cpp
//input 2 team names and get the winning team

#include <iostream>
#include <cstdlib>
using namespace std;

// #include <algorithm>

//function prototypes
void input_teams();
int get_winning_team(string,string);
int get_team_number_best_score(int,int);
int get_team_number_most_char_type(string,string,int);
int get_char_type(char);
int get_name_score(string);
int get_num_of_char_type(string,int);
string simplify(string,int);
int get_rand_in_range(int,int);

using namespace std;

int main() {
	srand(2024);
	bool keepgoing = true;
	while (keepgoing){
		cout << "Would you like to compare 2 teams?\n";
		cout << "1) yes\n";
		cout << "0) no\n";
		string response;
		cin >> response;
		if (response.compare("0")==0){
			cout << "goodbye";
			keepgoing = false;
		}else if (response.compare("1")==0){
			input_teams();
		}
	}
	return 0;
}

void input_teams(){
	string team1;
	string team2;
	bool keepgoing = true;
	while (keepgoing){
		cout << "type the name of the first team, or type 0 to exit: ";
		cin >> team1;
		if (team1.compare("0")==0){
			return;
		}
		cout << "type the name of the second team: ";
		cin >> team2;

		//decide which team won
		int winningTeamNumber = get_winning_team(team1,team2);
		//print the results
		string winningTeam;
		string losingTeam;
		if (winningTeamNumber==1){
			winningTeam = team1;
			losingTeam = team2;
		}else{
			winningTeam = team2;
			losingTeam = team1;
		}
		cout << winningTeam << " won!\n\n";
	}
}

int get_winning_team(string team1,string team2){
	//simplify the team names to the shorter one
	int len1 = team1.length();
	int len2 = team2.length();
	int truncLength = min(len1,len2);
	string team1Trunc = simplify(team1,truncLength);
	string team2Trunc = simplify(team2,truncLength);

	//calculate the scores of each team
	int score1 = get_name_score(team1Trunc);
	int score2 = get_name_score(team2Trunc);
	cout << team1 << " got " << score1 << " points!\n";
	cout << team2 << " got " << score2 << " points!\n";
	//decide winner
	int winningTeamNumber = get_team_number_best_score(score1,score2);
	if (winningTeamNumber!=0){
		return winningTeamNumber;
	}
	//do tie breakers//!!Likely a better way to organize this
	winningTeamNumber = get_team_number_most_char_type(team1Trunc,team2Trunc,4);
	if (winningTeamNumber!=0){
		return winningTeamNumber;
	}
	winningTeamNumber = get_team_number_most_char_type(team1Trunc,team2Trunc,3);
	if (winningTeamNumber!=0){
		return winningTeamNumber;
	}
	winningTeamNumber = get_team_number_most_char_type(team1Trunc,team2Trunc,1);
	if (winningTeamNumber!=0){
		return winningTeamNumber;
	}
	//coin flip for winner
	int coinFlip = get_rand_in_range(1,2);
	return coinFlip;
}
//funcs for tiebreakers and deciding winner
int get_team_number_best_score(int score1,int score2){
	if (score1>score2){
		return 1;
	}else if (score1<score2){
		return 2;
	}else{
		return 0;
	}
}
int get_team_number_most_char_type(string team1,string team2,int charType){
	int numLetters1 = get_num_of_char_type(team1,charType);
	int numLetters2 = get_num_of_char_type(team2,charType);
	if (numLetters1>numLetters2){
		return 1;
	}else if (numLetters1<numLetters2){
		return 2;
	}else{
		return 0;
	}
}

//char types
/*	1: good
	2: bad
	3: wild
	4: crazy
	0: else
*/
int get_char_type(char thisChar){//!!Likely a better way of organizing this
	int charType = 0;
	switch (thisChar){
		case 'b':
		case 'c':
		case 'l':
		case 'o':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'x':
		case 'z':
			charType = 1;
			break;
		case 'a':
		case 'd':
		case 'e':
		case 'g':
		case 'j':
		case 'k':
		case 'm':
		case 'p':
		case 'v':
		case 'y':
			charType = 2;
			break;
		case 'f':
		case 'h':
		case 'i':
		case 'n':
		case 'w':
			charType = 3;
			break;
		case 'q':
			charType = 4;
			break;
	}
	return charType;
}

//funcs cycle through team name
int get_name_score(string team){
	int score = 0;
	int multiplier = 1;
	for (int index=0;index<team.length();index++){
		char character = team[index];
		int charType = get_char_type(character);
		switch (charType){
			case 1://good
				score+=3;
				break;
			case 2://bad
				score-=3;
				break;
			case 3://wild
				{
					int addScore = get_rand_in_range(-6,6);
					score+=addScore;
					break;
				}
			case 4://crazy
				{
					int multScore = get_rand_in_range(1,2);
					multiplier*=multScore;
					break;
				}
		}
	}
	int finalHopeUpperRange = 6*team.length();
	int totalScore = score*multiplier + get_rand_in_range(-finalHopeUpperRange,finalHopeUpperRange);
	return totalScore;
}
int get_num_of_char_type(string team, int charType){
	int numLetters = 0;
	for (int index=0;index<team.length();index++){
		char character = team[index];
		int thisCharType = get_char_type(character);
		if (charType==thisCharType){
			numLetters++;
		}
	}
	return numLetters;
}

//helper funcs
string simplify(string str, int length){
	//truncates and makes the strings lowercase
	if (str.length() > length){
		return str.substr(0, length);
	}
	return str;
}
int get_rand_in_range(int lowerBound,int upperBound){
	//returns random value in range (inclusive)
	return (rand()%(upperBound-lowerBound+1)) + lowerBound;
}
