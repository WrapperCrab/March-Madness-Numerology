//2024 alg.cpp
//input 2 team names and get the winning team

#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include "2024 alg.h"

//function prototypes
void compare_teams();

int get_winning_team_number(std::string,std::string);
int do_tie_breaker(std::string,std::string,int);
int get_name_score(std::string);
int get_num_of_char_type(std::string,int);
int get_team_number_best_score(int,int);

int get_char_type(char);
std::string get_char_type_name(int);

std::string simplify(std::string,int);
std::string make_lowercase(std::string);
int get_rand_in_range(int,int);

std::string get_user_team(int);

int main_2024() {
	srand(2024);
	bool keepgoing = true;
	while (keepgoing){
		std::cout << "Would you like to compare 2 teams?\n";
		std::cout << "1) yes\n";
		std::cout << "0) no\n";
		std::string response;
		std::cin >> response;
		if (response.compare("0")==0){
			std::cout << "goodbye\n\n";
			keepgoing = false;
		}else if (response.compare("1")==0){
			compare_teams();
		}else{
			std::cout << "Error: You must type the number for one of the options.\n\n";
		}
	}
	return 0;
}

void compare_teams(){//continues indefinitely for quick input until user inputs 0 for team 1
	bool keepgoing = true;
	while (keepgoing){
		//take user input
		std::string team1 = get_user_team(1);
		if (team1=="0"){return;}
		std::string team2 = get_user_team(2);
		//decide which team wins
		int winningTeamNumber = get_winning_team_number(team1,team2);
		//print results
		std::string winningTeam;
		std::string losingTeam;
		if (winningTeamNumber==1){
			winningTeam = team1;
			losingTeam = team2;
		}else{
			winningTeam = team2;
			losingTeam = team1;
		}
		std::cout << winningTeam << " (team "<<winningTeamNumber<<") won!\n\n";
	}
}

//funcs for deciding winner and tiebreakers
int get_winning_team_number(std::string team1,std::string team2){
	//truncate longer team name to length of shorter team name
	//also make both team names lowercase
	int len1 = team1.length();
	int len2 = team2.length();
	int truncLength = std::min(len1,len2);
	std::string team1Trunc = simplify(team1,truncLength);
	std::string team2Trunc = simplify(team2,truncLength);
	//calculate the scores of each team
	int score1 = get_name_score(team1Trunc);
	int score2 = get_name_score(team2Trunc);
	if (score1!=score2){
		std::cout << team1 << " got " << score1 << " points!\n";
		std::cout << team2 << " got " << score2 << " points!\n";
	}else{
		std::cout << team1 << " and " << team2 << " got " << score1 << " points!\n";
	}
	//decide winner
	int winningTeamNumber = get_team_number_best_score(score1,score2);
	if (winningTeamNumber!=0){
		return winningTeamNumber;
	}
	//do tie breakers
	winningTeamNumber = do_tie_breaker(team1Trunc,team2Trunc,4);//most crazy chars
	if (winningTeamNumber!=0){return winningTeamNumber;}
	winningTeamNumber = do_tie_breaker(team1Trunc,team2Trunc,3);//most wild chars
	if (winningTeamNumber!=0){return winningTeamNumber;}
	winningTeamNumber = do_tie_breaker(team1Trunc,team2Trunc,1);//most good chars
	if (winningTeamNumber!=0){return winningTeamNumber;}
	//coin flip for winner
	winningTeamNumber = get_rand_in_range(1,2);
	std::cout << "A coin flip chose the winner!\n";
	return winningTeamNumber;
}
int do_tie_breaker(std::string team1,std::string team2,int charType){
	int charScore1 = get_num_of_char_type(team1,charType);
	int charScore2 = get_num_of_char_type(team2,charType);
	std::string charTypeName = get_char_type_name(charType);
	if (charScore1!=charScore2){
		std::cout << team1 << " had " << charScore1 <<" "<< charTypeName<<" characters!\n";
		std::cout << team2 << " had " << charScore2 <<" "<< charTypeName<<" characters!\n";
	}else{
		std::cout << team1 << " and " << team2 << " had " << charScore1 << " "<< charTypeName <<" characters!\n";
	}
	return get_team_number_best_score(charScore1,charScore2);
}
int get_name_score(std::string team){
	//cycle through characters of team name and add character score
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
int get_num_of_char_type(std::string team, int charType){
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
int get_team_number_best_score(int score1,int score2){
	if (score1>score2){
		return 1;
	}else if (score1<score2){
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
	0: else*/
int get_char_type(char thisChar){
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
std::string get_char_type_name(int charType){
	std::string charTypeName = "";
	switch (charType){
		case 1:
			charTypeName = "good";
			break;
		case 2:
			charTypeName = "bad";
			break;
		case 3:
			charTypeName = "wild";
			break;
		case 4:
			charTypeName = "crazy";
			break;
	}
	return charTypeName;
}

//helper funcs
std::string simplify(std::string str, int length){
	//truncates and makes the strings lowercase
	std::string newStr = str;
	if (newStr.length() > length){
		newStr = newStr.substr(0,length);
	}
	newStr = make_lowercase(newStr);//
	return newStr;
}
std::string make_lowercase(std::string str){
	std::string newStr = "";
	for (int i=0;i<str.length();i++){
		char thisChar = str[i];
		char newChar = tolower(thisChar);
		newStr+=newChar;
	}
	return newStr;
}
int get_rand_in_range(int lowerBound,int upperBound){
	//returns random value in range (inclusive)
	return (rand()%(upperBound-lowerBound+1)) + lowerBound;
}

//user input funcs
std::string get_user_team(int teamNumber){
	//ask user for name of team
	std::string team;
	if (teamNumber==1){
		std::cout << "type the name of team "<<teamNumber<<", or type 0 to exit: ";
	}else{
		std::cout << "type the name of team "<<teamNumber<<": ";
	}
	std::cin >> team;
	return team;
}
