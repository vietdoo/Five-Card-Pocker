#include <iostream>
#include <cstring>
#include <time.h>

using namespace std;

const int SUITS = 4;
const int FACES = 13;

void shuffleCards(int deck[][FACES]) {
	int n = 52;
	int m[53];
	for (int i = 1; i <= n; i++)
		m[i] = i;
	for (int i = 0; i < SUITS; i++) {
		for (int j = 0; j < FACES; j++) {
			int k = rand() % n + 1;
			deck[i][j] = m[k];
			m[k] = m[n];
			n--;
		}
	}
}

void printCardShuffing(int deck[][FACES], char * suits[], char * faces[]) {
	int n = 1;
	int m = 1;
	while (n <= 52) {
		for (int i = 0; i < SUITS; i++) {
			for (int j = 0; j < FACES; j++) {
				if (n == deck[i][j]) {
					cout << n << ". (" << suits[i] << ", " << faces[j] << ')' << '\n';
					m++;
					goto nextStage;
				}
			} 
		}
		nextStage :
		n++;
	}
}

int** dealingForHand(int deck[SUITS][FACES]) {
	int** a = new int *[5];
	for (int i = 0; i < 5; i++) {
		a[i] = new int[2];
	};
	int n = 1;
	while (n <= 5) {
		for (int i = 0; i < SUITS; i++) {
			for (int j = 0; j < FACES; j++) {
				if (n == deck[i][j]) {
					a[n - 1][0] = j;
					a[n - 1][1] = i;
					goto nextStage;
				}
			} 
		}
		nextStage :
		n++;
	}
	return a;
}

void printHand(int** hand, char* suits[], char* faces[]) {
	for (int i = 0; i < 5; i++)
		cout << '(' << suits[hand[i][1]] << ", " << faces[hand[i][0]] << ')' << '\n';
}

int isFourOfAKind(int** hand) {
	int a[14] = {0};
		for (int i = 0; i < 5; i++) {
			a[hand[i][0]]++;
		}
	for (int i = 1; i <= 13; i++) 
		if (a[i] == 4) {
			return 1;
		}
	return 0;
}
int isFullHouse(int** hand) {
	int a[14] = {0};
		for (int i = 0; i < 5; i++) {
			a[hand[i][0]]++;
		}
	int b[6] = {0};
	for (int i = 0; i <= 12; i++) 
		b[a[i]]++;
	if (b[3] == 1 && b[2] == 1) 
		return 1;
	return 0;
}
int isFlush(int** hand) {
	int b[14] = {0};
		for (int i = 0; i < 5; i++) {
			b[hand[i][0]]++;
		}
	int res = 0;
	for (int i = 2; i <= 13; i++)  {
		if (b[i] > 0 && b[i-1] > 0) {
			res++;
		}
	}
	if (res == 4)
		return 0;
	int a[5] = {0};
		for (int i = 0; i < 5; i++) {
			a[hand[i][1]]++;
		}

	for (int i = 0; i <= 4; i++) 
		if (a[i] == 5) {
			return 1;
		}
	return 0;
}
int isStraight(int** hand) {
	int a[14] = {0};
		for (int i = 0; i < 5; i++) {
			a[hand[i][0]]++;
		}
	int res = 0;
	for (int i = 2; i <= 13; i++)  {
		if (a[i] > 0 && a[i-1] > 0) {
			res++;
		}
	}
	if (res == 4)
		return 1;
	else
		return 0;
}
int isStraightFlush(int** hand) {
	int m = -1;
	int b[5] = {0};
		for (int i = 0; i < 5; i++) {
			b[hand[i][1]]++;
		}
	for (int i = 0; i <= 3; i++) 
		m = (m < b[i] ? b[i] : m);
	if (m != 5)
		return 0;
	int a[14] = {0};
		for (int i = 0; i < 5; i++) {
			a[hand[i][0]]++;
		}
	int res = 0;
	for (int i = 2; i <= 13; i++)  {
		if (a[i] > 0 && a[i-1] > 0) {
			res++;
		}
	}
	if (res == 4)
		return 1;
	else
		return 0;

	return 0;
}
int isThreeOfAKind(int** hand) {
	int a[14] = {0};
		for (int i = 0; i < 5; i++) {
			a[hand[i][0]]++;
		}
	int b[6] = {0};
	for (int i = 0; i <= 12; i++) 
		b[a[i]]++;
	if (b[3] == 1 && b[1] == 2) 
		return 1;
	return 0;
}
int isTwoPairs(int** hand) {
	int a[14] = {0};
		for (int i = 0; i < 5; i++) {
			a[hand[i][0]]++;
		}
	int b[6] = {0};
	for (int i = 0; i <= 12; i++) 
		b[a[i]]++;
	if (b[2] == 2) 
		return 1;
	return 0;
}
int isPair(int** hand) {
	int a[14] = {0};
		for (int i = 0; i < 5; i++) {
			a[hand[i][0]]++;
		}
	int b[6] = {0};
	for (int i = 0; i <= 12; i++) 
		b[a[i]]++;
	if (b[1] == 3  && b[2] == 1) 
		return 1;
	return 0;
}
int getHighestCard(int** hand) {
	int m = -1;
	for (int i = 0; i < 5; i++) {
		m = (m < hand[i][0] ? hand[i][0] : m);
	}
	return m;
}

int*** dealingForHands(int deck[SUITS][FACES], int n) {

	int*** a = new int**[n];
	for (int i = 0; i < n; i++) {
		a[i] = new int*[5];
		for (int j = 0; j < 5; j++) {
			a[i][j] = new int[2];
		}
	}
	int m = 1;
	
	int count = 1;
	while (count <= 5) {

		for (int k = 0; k < n; k++) {
			for (int i = 0; i < SUITS; i++) {
				for (int j = 0; j < FACES; j++) {
					if (m == deck[i][j]) {				
						a[k][count - 1][0] = j;
						a[k][count - 1][1] = i;
						goto nextStage;
					}
				} 
			}
			nextStage :
			m++;
		}
		count++;
	}

	return a;
}

int getStatusOfHand(int** hand) {
	if (isStraightFlush(hand))
		return 8;
	else if (isFourOfAKind(hand)) 
		return 7;
	else if (isFullHouse(hand))
		return 6;
	else if (isFlush(hand)) 
		return 5;
	else if (isStraight(hand)) 
		return 4;
	else if (isThreeOfAKind(hand))
		return 3;
	else if (isTwoPairs(hand)) 
		return 2;
	else if (isPair(hand))
		return 1;
	else 
		return 0;
	cout << '\n';
}

int* rankingHands(int*** hands, int n) {
	int* rank = new int[n];
	int a[n];
	for (int i = 0; i < n; i++) 
		a[i] = getStatusOfHand(hands[i]);

	int stt = 1;
	for (int i = 8; i >= 0; i--) {
		int count = 0;
		for (int j = 0; j < n; j++)
			if (a[j] == i) {
				rank[j] = stt;
				count++;
			}
		stt += count;
	}
	return rank;
}

int* evaluateHands(int* a, int n) {
	int* rank = new int[n];
	int stt = 1;
	for (int i = 1500; i >= 0; i--) {
		int count = 0;
		for (int j = 0; j < n; j++)
			if (a[j] == i) {
				rank[j] = stt;
				count++;
			}
		stt += count;
	}
	return rank;
}

void gameFor1Player(int deck[SUITS][FACES], char* suits[], char* faces[]) {
	cout << string(50, '\n');
	char choice = '1';
	int** result = nullptr;
	while (choice != 'x') {

		cout << "\n\nChoose your choices";
		cout << "\n1. Dealing cards";
		cout << "\n2. Show cards";
		cout << "\nx. exit";
		cout << '\n';
		cin >> choice;
		cout << string(50, '\n');
		if (choice == 'x') {
			return;
		}
		else if (choice == '1') {
			shuffleCards(deck);
			result = dealingForHand(deck);
			cout << "\nDealing success\n\n";
		}
		else if (choice == '2' && result != nullptr) {
			printHand(result, suits, faces);
		}
	}
}

void gameForNPlayer(int deck[SUITS][FACES], char* suits[], char* faces[]) {
	char choice = '1';
	int n = 0;
	int*** results = nullptr;
	int* rank = nullptr;
	cout << string(50, '\n');
	cout << "Number of players : ";
	cin >> n;
	while (n > 10) {
		cout << "\nUnder 10 players! ";
		cout << "\nNumber of players : ";
		cin >> n;
	}
	int* finalRank = new int[n];
	int* winnerRank = new int[n];
	for (int i = 0; i < n; i++)
		finalRank[i] = 0;
	while (choice != 'x') {
		cout << "\n\nChoose your choices";
		cout << "\n1. Dealing cards";
		cout << "\n2. Ranking";
		cout << "\n3. Final Ranking";
		cout << "\nx. exit";
		cout << '\n';
		cin >> choice;
		cout << string(50, '\n');
		if (choice == 'x') {
			return;
		}
		else if (choice == '1') {
			shuffleCards(deck);
			results = dealingForHands(deck, n);
			for (int i = 0; i < n; i++) {
				cout << "\nPlayer " << i << ":\n";	
				printHand(results[i], suits, faces);
			}
			printCardShuffing(deck, suits, faces);
			rank = rankingHands(results, n);
			for (int i = 0; i < n; i++)
				finalRank[i] += 8 - rank[i] + 1;
		}
		else if (choice == '2'  && results != nullptr) {
			
			cout << "\n******Ranking******\n";
			for (int i = 0; i < n; i++)
				cout << '\n' << "Player " << i << ": " << rank[i];
			}
		else if (choice == '3' && results != nullptr) {
			cout << "\n******Final Ranking******\n";
			winnerRank = evaluateHands(finalRank, n);
			for (int i = 0; i < n; i++) {
				cout << "\nPlayer " << i << ": " << finalRank[i] << "  points";
			}
			cout << "\n\nThe Winner is : \n";
			for (int i = 0; i < n; i++)
				if (winnerRank[i] == 1) {
					cout << "\nPlayer " << i;
				}
		}
	}
}

int main () {
	srand(time(0));
	int deck[SUITS][FACES] = {0};
	char* suits[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
	char* faces[FACES] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	
	char choice = '1';
	int n = 0;
		while (choice != 'x') {
		cout << string(50, '\n');
		cout << "Choose your choices: ";
		cout << "\n1. Game for 1 player";
		cout << "\n2. Game for N players";
		cout << "\nx. exit";
		cout << '\n';
		cin >> choice;
		if (choice == 'x') {
			break;
		}
		else if (choice == '2') {
			gameForNPlayer(deck, suits, faces);
		}
		else if (choice == '1') {
			gameFor1Player(deck, suits, faces);
		}
	}
	
	return 0;
}
