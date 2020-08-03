#include <bits/stdc++.h>
using namespace std;

#define NUM_SCORE 13
#define MAX_ROUND 12
#define NUM_DICE 5

int player[2][NUM_SCORE];
const string scoreType[NUM_SCORE] = {
	"Aces          ", "Deuces        ", "Threes        ", "Fours         ", "Fives         ", "Sixes         ", "Bonus(>=65)   ",
	"Choice        ", "4 of a Kind   ", "Full House    ", "Small Straight", "Large Straight", "Yacht         "
};

void startingYacht();
void printScore(int round);
void playingYacht();
void turn(int player);
void victory();

int main(){
	ios_base::sync_with_stdio(false);
	
	while(-1){
		startingYacht();
		playingYacht();
		victory();
	}
}

void startingYacht(){
	for(int i = 0; i < NUM_SCORE; i++){
		player[0][i] = 0;
		player[1][i] = 0;
	}
	int menu;
	cout << "==================" << endl
		 << "    YACHT DICE    " << endl
		 << "==================" << endl;
	while(-1){
		cout << "1. �����ϱ�" << endl
			 << "2. �����ϱ�" << endl
			 << "���� ��� : ";
		cin >> menu;
		if(menu == 1)		break;
		else if(menu == 2)	exit(0);
		else	cout << endl << "!!! �ùٸ��� ���� �����Դϴ�. �ٽ� ����ּ���. !!!" << endl << endl;
	}
}

void playingYacht(){
	for(int round = 1; round <= MAX_ROUND; round++){
		printScore(round);
		turn(1);
		printScore(-1);
		turn(2);
	}
}

void printScore(int round){
	if(round != -1){
		cout << endl
			 << "==================" << endl
			 << "    " << round << "   ROUND    " << endl
			 << "==================" << endl;
	}
	cout << "******************   ******************" << endl
		 << "**** PLAYER 1 ****   **** PLAYER 2 ****" << endl
		 << "******************   ******************" << endl;
	
	int p1 = 0, p2 = 0;
	for(int i = 0; i < NUM_SCORE; i++){
		if(i == 6){
			if(p1 >= 63) player[0][i] = 35;
			if(p2 >= 63) player[1][i] = 35;
			
			if(p1 >= 10)	cout << "SumOfCategorie" << " :" << p1 << "   ";
			else			cout << "SumOfCategorie" << " : " << p1 << "   ";
			if(p2 >= 10)	cout << "SumOfCategorie" << " :" << p2 << endl;
			else			cout << "SumOfCategorie" << " : " << p2 << endl;
		}
		
		p1 += player[0][i];
		p2 += player[1][i];
		
		if(player[0][i] >= 10)	cout << scoreType[i] << " :" << player[0][i] << "   ";
		else					cout << scoreType[i] << " : " << player[0][i] << "   ";
		if(player[1][i] >= 10)	cout << scoreType[i] << " :" << player[1][i] << endl;
		else					cout << scoreType[i] << " : " << player[1][i] << endl;
	}
	
	cout << "�÷��̾� 1 ���� : " << p1 << " �÷��̾� 2 ���� : " << p2 << endl; 
}

void turn(int P){
	cout << endl
		<< "------------------" << endl
		 << " PLAYER  " << P << "  TURN    " << endl
		 << "------------------" << endl;
	
	int reroll = 3;
	vector<int> dice(NUM_DICE, 0);
	vector<bool> pinned(NUM_DICE, false);

	while(-1){
		cout << endl <<
			"1. �����ϱ� (" << reroll << "ȸ ���ҽ��ϴ�.)" << endl
			<< "2. ���� �����ϱ�" << endl
			<< "�÷��̾� " << P << "�� ���� : ";
			
		int menu;
		cin >> menu;
		
		if((reroll == 0 && menu == 1) || (reroll == 3 && menu == 2) || (menu != 1 && menu != 2 )){
			cout << endl << "!!! �ùٸ��� ���� �����Դϴ�. �ٽ� ����ּ���. !!!" << endl << endl;
			continue;
		}
		
		if(menu == 1){
			reroll--;
			srand((unsigned int)time(NULL));
			
			cout << endl
				<< "++++++++++++++++++" << endl
				<< "pinned : ";
			
			for(int i = 0; i < NUM_DICE; i++){
				if(!pinned[i]){
					dice[i] = rand() % 6 + 1;
					cout << "  ";
				}
				else	cout << "V ";
			}
			cout << endl << "�ֻ��� : ";
			for(int i = 0; i < NUM_DICE; i++)
				cout << dice[i] << " ";
			cout << endl
				 << "++++++++++++++++++" << endl
				 << "�ֻ��� �����ϱ� (���� : 1 ~ 5) (�ֻ��� ������ ������ -1�� �Է��ϼ���)" << endl;
			
			int t;
			while(-1){
				cout << "�÷��̾� " << P << "�� ���� : ";
				cin >> t;
				
				if(t >= 1 && t <= 5){
					pinned[t - 1] = !pinned[t - 1];
					cout << endl << "++++++++++++++++++" << endl;
					cout << "pinned : ";
					for(int i = 0; i < NUM_DICE; i++){
						if(!pinned[i])	cout << "  ";
						else			cout << "V ";
					}
					cout << endl << "�ֻ��� : ";
					for(int i = 0; i < NUM_DICE; i++)
						cout << dice[i] << " ";
					cout << endl;
					cout << "++++++++++++++++++" << endl;
				}
				else if(t == -1)	break;
				else				cout << endl << "!!! �ùٸ��� ���� �����Դϴ�. �ٽ� ����ּ���. !!!" << endl << endl;
			}
		}
		else if(menu == 2){
			vector<bool> canAddress(NUM_SCORE, true);
			vector<int> cntArr(7, 0);
			int sum = 0;
			
			for(int i = 0; i < NUM_SCORE; i++){
				if(i == 6)	canAddress[i] = false;
				if(player[P - 1][i] != 0) canAddress[i] = false;
			}
			
			for(int i = 0; i < NUM_DICE; i++){
				cntArr[dice[i]]++;
				sum += dice[i];
			}
			
			while(-1){
				cout << endl << "������ ��� �����ұ��?" << endl;
				for(int i = 0; i < NUM_SCORE; i++){
					if(canAddress[i])	cout << i + 1 << " : " << scoreType[i] << endl;
				}
				cout << "�÷��̾� " << P << "�� ���� : ";
				int t;	cin >> t;
				
				if(t <= 0 || t >= 14 || !canAddress[t - 1])
					cout << endl << "!!! �ùٸ��� ���� �����Դϴ�. �ٽ� ����ּ���. !!!" << endl << endl;
				else{
					// score calc
					if(t >= 1 && t <= 6){
						player[P - 1][t - 1] = cntArr[t] * t;
					}
					else if(t == 8){
						player[P - 1][t - 1] = sum;
					}
					else if(t == 9){
						bool flag = false;
						for(auto c : cntArr){
							if(c >= 4) flag = true;
						}
						
						if(flag)	player[P - 1][t - 1] = sum;
						else		player[P - 1][t - 1] = 0;
					}
					else if(t == 10){
						bool flag_2 = false, flag_3 = false;
						for(auto c : cntArr){
							if(c == 3) flag_3 = true;
							if(c == 2) flag_2 = true;
						}
						
						if(flag_2 && flag_3)	player[P - 1][t - 1] = sum;
						else					player[P - 1][t - 1] = 0;
					}
					else if(t == 11){
						int cnt = 0;
						for(int i = 1; i <= 6; i++){
							if(cnt == 4) 		break; 
							if(cntArr[i] >= 1)	cnt++;
							else				cnt = 0;
						}
						
						if(cnt >= 4)	player[P - 1][t - 1] = 15;
						else			player[P - 1][t - 1] = 0;
					}
					else if(t == 12){
						int cnt = 0;
						for(int i = 1; i <= 6; i++){
							if(cnt == 5) 		break; 
							if(cntArr[i] >= 1)	cnt++;
							else				cnt = 0;
						}
						
						if(cnt >= 5)	player[P - 1][t - 1] = 30;
						else			player[P - 1][t - 1] = 0;
					}
					else if(t == 13){
						bool flag = false;
						for(auto c : cntArr){
							if(c == 5) flag = true;
						}
						
						if(flag)	player[P - 1][t - 1] = 50;
						else		player[P - 1][t - 1] = 0;
					}
					break;
				}
			}
			break;
		}
	}
}

void victory(){	
	int p1 = 0, p2 = 0;
	for(int i = 0; i < NUM_SCORE; i++){
		if(i == 6){
			if(p1 >= 63) player[0][i] = 35;
			if(p2 >= 63) player[1][i] = 35;
		}
		p1 += player[0][i];
		p2 += player[1][i];
	}
	cout << "�÷��̾� 1 ���� : " << p1 << " �÷��̾� 2 ���� : " << p2 << endl; 
	if(p1 > p2)			cout << "�÷��̾� 1 ���!" << endl << "�÷��̾� 1 ���!" << endl << "�÷��̾� 1 ���!" << endl;
	else if(p1 == p2)	cout << "���º�!" << endl << "���º�!" << endl << "���º�!" << endl;
	else				cout << "�÷��̾� 2 ���!" << endl << "�÷��̾� 2 ���!" << endl << "�÷��̾� 2 ���!" << endl;
}
