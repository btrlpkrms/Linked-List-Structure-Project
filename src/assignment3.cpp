#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include<algorithm>
#include<set>
#include<stdio.h>
using namespace std;
vector < vector<string> > allFile;
vector <string> oplines;
vector<vector<string>> operations;

struct doubleNode
{
	int matchId;
	int minute;
	string away_team;
	doubleNode *next;
	doubleNode *prev;
};
struct doubleNode *head = NULL;
struct doubleNode *tail = NULL; 

struct singleNode {
	string footballer_name;
	string footballer_team;
	singleNode *next;
	doubleNode *doubleNext;
};
singleNode *singleHead = NULL;

void singleInitNode(struct singleNode *head, string n,string n2, string awayTeam,int minute,int matchID) {
	head->footballer_name = n;
	head->footballer_team = n2;
	head->next = NULL;

	doubleNode *new_double_node = new doubleNode;
	head->doubleNext = new_double_node;
	new_double_node->away_team = awayTeam;
	new_double_node->matchId = matchID;
	new_double_node->minute = minute;


}

void singleAddNode(string n,string n2, string awayTeam,int minute,int matchID) {

	if (singleHead == NULL)
	{
		singleNode *new_single_node = new singleNode;
		new_single_node->footballer_name = n;
		new_single_node->footballer_team = n2;
		new_single_node->next = NULL;
		singleHead = new_single_node;

		doubleNode *new_double_node = new doubleNode;
		new_single_node->doubleNext = new_double_node;
		new_double_node->next = NULL;

		new_double_node->away_team = awayTeam;
		new_double_node->matchId = matchID;
		new_double_node->minute = minute;

	}

	else
	{

		singleNode *new_single_node2 = new singleNode;
		new_single_node2->footballer_name = n;
		new_single_node2->footballer_team = n2;
		new_single_node2->next = NULL;
		singleNode *cur = singleHead;

		while (cur) {
			if (cur->next == NULL) {
				cur->next = new_single_node2;
				doubleNode *new_double_node = new doubleNode;
				new_double_node->next = NULL;
				new_double_node->away_team = awayTeam;
				new_double_node->matchId = matchID;
				new_double_node->minute = minute;
				cur->next->doubleNext = new_double_node;
				break;
			}
			if (cur->footballer_name.compare(new_single_node2->footballer_name) == 0) {

				doubleNode *temp_double = new doubleNode;
				temp_double = cur->doubleNext;
				while (temp_double->next != NULL)
				{
					temp_double = temp_double->next;
				}
				doubleNode *new_double_node = new doubleNode;
				temp_double->next = new_double_node;
				new_double_node->next = NULL;
				new_double_node->away_team = awayTeam;
				new_double_node->matchId = matchID;
				new_double_node->minute = minute;
				break;
			}
			cur = cur->next;
		}
	}
	
}
void singleDisplay(ofstream &outpt) {
	int count=0;
	singleNode *temp_node = singleHead;
	while (temp_node != NULL) {
		outpt << temp_node->footballer_name << " "<<endl;
		outpt << temp_node->footballer_team << " " << endl;
		doubleNode	*cur = temp_node->doubleNext;
		while (cur != NULL) {
			outpt << cur->away_team << " " << endl;
			outpt << cur->minute << " " << endl;
			outpt << cur->matchId << " " << endl;
			cur = cur->next;
		}
		temp_node = temp_node->next;

	}
	outpt << endl;
	outpt << endl;
}

void insertFile(vector < vector<string> > allFile) {

	for (int i = 0; i < allFile.size(); i++) {
		singleAddNode(allFile[i][0], allFile[i][1],allFile[i][2],stoi(allFile[i][3]),stoi(allFile[i][4]));

	}

}

void SortLinkedList(ofstream &outpt)
{
	singleNode *node = NULL, *temp = NULL , *node2 = NULL, *temp2 = NULL;
	node = singleHead;
	while (node->next != NULL)
	{
		temp = node;
		while (temp->next != NULL)
		{
			temp2 = temp->next;
			if (temp->footballer_name > temp2->footballer_name)
			{
				outpt << "girdi" << endl;
				node2 = temp;
				temp = temp2;
				temp2 = node2;
			}
			temp = temp->next;
		}
		node = node->next; 
	}
}

vector<string> hatTrick;
int most = 0;
int lesss = 0;

void traverse(ofstream &outpt) {

	singleNode *temp_node = singleHead;
	while (temp_node != NULL) {
		doubleNode	*cur = temp_node->doubleNext;
		int count = 0;
		while (cur->next != NULL) {
			
			int abc = cur->matchId;
			cur = cur->next;
			if (cur->matchId == abc) {
				count++;
			}
			if (count ==2) {
				hatTrick.push_back(temp_node->footballer_name);
			}
		}
		temp_node = temp_node->next;
	}
	outpt << "3)THE NAMES OF FOOTBALLERS WHO SCORED HAT-TRICK" << endl;
	sort(hatTrick.begin(), hatTrick.end());
	for (int i = 0; i < hatTrick.size(); i++) {
		outpt << hatTrick[i] << endl;
	}

}

void findRatio(ofstream &outpt) {
	singleNode *temp_node = singleHead;
	while (temp_node != NULL) {
		doubleNode	*cur = temp_node->doubleNext;
		while (cur != NULL) {
			if (cur->minute < 46) {
				lesss++;
			}
			if (cur->minute > 45) {
				most++;
			}

			cur = cur->next;
		}
		temp_node = temp_node->next;
	}
	if (lesss > most) {
		outpt << "1)THE MOST SCORED HALF" << endl;
		outpt << "0" << endl;
	}
	if (most > lesss) {
		outpt << "1)THE MOST SCORED HALF" << endl;
		outpt << "1" << endl;
	}

}

vector<int> goalScore;
vector<string> goalScorers;
vector<int> goalScorerIndex;
vector<string> sortedScorers;
void goalScorer(ofstream &outpt) {
	int abc = 0;
	singleNode *temp_node = singleHead;
	while (temp_node != NULL) {
		doubleNode	*cur = temp_node->doubleNext;
		int count=0;
		while (cur != NULL) {
			count++;
			cur = cur->next;
		}
		goalScore.push_back(count);
		goalScorers.push_back(temp_node->footballer_name);
		temp_node = temp_node->next;
	}
	int max = *max_element(goalScore.begin(), goalScore.end());
	for (int i = 0; i < goalScore.size(); i++) {
		if (goalScore[i] == max) {
			goalScorerIndex.push_back(i);
		}
	}
	outpt << "2)GOAL SCORER" << endl;
	for (int k = 0; k < goalScorerIndex.size(); k++) {
		sortedScorers.push_back(goalScorers[goalScorerIndex[k]]);
	}
	sort(sortedScorers.begin(), sortedScorers.end());
	for (int j = 0; j < sortedScorers.size(); j++) {
		outpt << sortedScorers[j]<< endl;
	}
}
set<string> teamss;
vector<string> teams;
void listOfTeams(ofstream &outpt) {
	singleNode *temp_node = singleHead;
	while (temp_node != NULL) {
		doubleNode	*cur = temp_node->doubleNext;
		teams.push_back(temp_node->footballer_team);
		temp_node = temp_node->next;
	}
	sort(teams.begin(), teams.end());
	for (int i = 0; i < teams.size(); i++) {
		teamss.insert(teams[i]);
	}

	teams.assign(teamss.begin(), teamss.end());
	outpt << "4)LIST OF TEAMS" << endl;
	for (int k = 0; k < teams.size(); k++) {
		outpt << teams[k] << endl;
	}
}

vector<string> footballers;
set<string> footballerSet;
void listOfFootballer(ofstream &outpt) {
	singleNode *temp_node = singleHead;
	while (temp_node != NULL) {
		doubleNode	*cur = temp_node->doubleNext;
		footballers.push_back(temp_node->footballer_name);
		temp_node = temp_node->next;
	}
	sort(teams.begin(), teams.end());
	for (int i = 0; i < footballers.size(); i++) {
		footballerSet.insert(footballers[i]);
	}

	footballers.assign(footballerSet.begin(), footballerSet.end());
	outpt << "5)LIST OF FOOTBALLERS" << endl;
	for (int k = 0; k < footballers.size(); k++) {
		outpt << footballers[k] << endl;
	}
}
void matchesOfFootballer(ofstream &outpt) {
	outpt << "6)MATCHES OF GIVEN FOOTBALLER" << endl;
	sort(operations[0].begin(), operations[0].end());
	for (int i = 0; i < operations[0].size(); i++) {
		outpt << "Matches of " << operations[0][i] << endl;
		singleNode *temp_node = singleHead;
		while (temp_node != NULL) {
			doubleNode	*cur = temp_node->doubleNext;
			if (temp_node->footballer_name.compare(operations[0][i]) == 0) {
				while (cur != NULL) {
					outpt << "Footballer Name: " << operations[0][i] << "Away Team: " << cur->away_team << ",Min of Goal: " << cur->minute << ",Match ID: " << cur->matchId << endl;
					cur = cur->next;
				}
			}
			temp_node = temp_node->next;
		}
	}

}
vector <int> matches;
set <int> removeDubmatch;
void matchesOfAscending(ofstream &outpt) {
	outpt << "7)ASCENDING ORDER ACCORDING TO MATCH ID" << endl;
	sort(operations[1].begin(), operations[1].end());
	for (int i = 0; i < operations[1].size(); i++) {
		singleNode *temp_node = singleHead;
		while (temp_node != NULL) {
			doubleNode	*cur = temp_node->doubleNext;
			if (temp_node->footballer_name.compare(operations[1][i]) == 0) {
				while (cur != NULL) {
					matches.push_back(cur->matchId);
					cur = cur->next;
				}

				sort(matches.begin(), matches.end());

				for (int i = 0; i < matches.size(); i++) {
					removeDubmatch.insert(matches[i]);
				}

				matches.assign(removeDubmatch.begin(), removeDubmatch.end());
				for (int l = 0; l < matches.size(); l++) {
					outpt << "Footballer Name: " << operations[1][i] << ",Match ID: " << matches[l] << endl;
				}

				matches.erase(matches.begin(), matches.end());
				removeDubmatch.erase(removeDubmatch.begin(), removeDubmatch.end());
			}
			temp_node = temp_node->next;
		}
	}
}
vector <int> matches2;
set <int> removeDubmatch2;
void matchesOfDescending(ofstream &outpt) {
	outpt << "8)DESCENDING ORDER ACCORDING TO MATCH ID" << endl;
	sort(operations[2].rbegin(), operations[2].rend());
	for (int i = 0; i < operations[2].size(); i++) {
		singleNode *temp_node = singleHead;
		while (temp_node != NULL) {
			doubleNode	*cur = temp_node->doubleNext;
			if (temp_node->footballer_name.compare(operations[2][i]) == 0) {
				while (cur != NULL) {
					matches2.push_back(cur->matchId);
					cur = cur->next;
				}
				sort(matches2.begin(), matches2.end());
				for (int i = 0; i < matches2.size(); i++) {
					removeDubmatch2.insert(matches2[i]);
				}
				matches2.assign(removeDubmatch2.begin(), removeDubmatch2.end());
				for (int l = matches2.size()-1; l >= 0 ;l--) {
					outpt << "Footballer Name: " << operations[2][i] << ",Match ID: " << matches2[l] << endl;
				}

				matches2.erase(matches2.begin(), matches2.end());
				removeDubmatch2.erase(removeDubmatch2.begin(), removeDubmatch2.end());
			}

			temp_node = temp_node->next;
		}
	}
}



int main(int argc,const char *argv[]) {
	ofstream outpt;
	outpt.open(argv[3], ios::out);
	ifstream infile;
	int i = 0;
	vector <string> temp;
	char cNum[250];
	infile.open(argv[1], ifstream::in);
	if (infile.is_open())
	{
		while (infile.good())
		{
			infile.getline(cNum, 256, ',');
			temp.push_back(cNum);
			if (i == 3) {
				infile.getline(cNum, 256, '\n');
				temp.push_back(cNum);
				allFile.push_back(temp);
				temp.erase(temp.begin(), temp.end());
				i = -1;
			}
			i++;
		}
		infile.close();
	}
	ifstream opfile;
	int k = 0;
	char cNum2[250];
	opfile.open(argv[2], ifstream::in);
	if (opfile.is_open())
	{
		while (opfile.good())
		{
			opfile.getline(cNum2, 256, ',');
			oplines.push_back(cNum2);
			opfile.getline(cNum2, 256, '\n');
			oplines.push_back(cNum2);
			operations.push_back(oplines);
			oplines.erase(oplines.begin(),oplines.end());
		}
		infile.close();
	}

	insertFile(allFile);
	findRatio(outpt);
	goalScorer(outpt);
	traverse(outpt);
	listOfTeams(outpt);
	listOfFootballer(outpt);
	matchesOfFootballer(outpt);
	matchesOfAscending(outpt);
	matchesOfDescending(outpt);
}
