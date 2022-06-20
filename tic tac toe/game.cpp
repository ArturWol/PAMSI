
#include<bits/stdc++.h> 
using namespace std; 

#define COMPUTER 1 
#define HUMAN 2 

#define SIDE 3 // Szerokość planszy

// Komputer jest 'O' 
// Gracz jest 'X' 
#define COMPUTERMOVE 'O' 
#define HUMANMOVE 'X' 

// Funkcja przedstawiająca status tablicy
void showBoard(char board[][SIDE]) 
{ 
	printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);  
} 

/*void showBoard(char board[][SIDE]) 
{ 
	
	printf("\t\t\t %c | %c | %c | %c \n", board[0][0], board[0][1], board[0][2], board[0][3]); 
	printf("\t\t\t----------------\n"); 
	printf("\t\t\t %c | %c | %c | %c \n", board[1][0], board[1][1], board[1][2], board[1][3]);
	printf("\t\t\t----------------\n"); 
	printf("\t\t\t %c | %c | %c | %c \n", board[2][0], board[2][1], board[2][2], board[2][3]);
	printf("\t\t\t----------------\n"); 
	printf("\t\t\t %c | %c | %c | %c \n", board[3][0], board[3][1], board[3][2], board[3][3]);
} */

// Funkcja pokazujące numery ID danych pól
void showInstructions() 
{ 
	printf("\nWybierz numer pola\n\n"); 
	
	printf("\t\t\t 1 | 2 | 3 \n"); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t 4 | 5 | 6 \n"); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t 7 | 8 | 9 \n\n"); 
} 


// Funkcja inicjalizująca grę 
void initialise(char board[][SIDE]) 
{	
	// Inicjalizacja pustej tablicy
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
			board[i][j] = ' '; 
	} 
} 

// Funkcja określająca zwyciezcę 
void declareWinner(int whoseTurn) 
{ 
	if (whoseTurn == COMPUTER) 
		printf("KOMPUTER wygral\n"); 
	else
		printf("Brawo, Wygrales!\n"); 
} 

// Funckja zwraca true kiedy wszystkie wiersze są zajęte przez jednego gracza
bool rowCrossed(char board[][SIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] != ' ') 
			return (true); 
	} 
	return(false); 
} 

// Funckja zwraca true kiedy wszystkie kolumny są zajęte przez jednego gracza
bool columnCrossed(char board[][SIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != ' ') 
			return (true); 
	} 
	return(false); 
} 

// Funckja zwraca true kiedy przekątne są zajęte przez jednego gracza 
bool diagonalCrossed(char board[][SIDE]) 
{ 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] != ' ') 
		return(true); 
		
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] != ' ') 
		return(true); 

	return(false); 
} 

// Funkcja zwraca true jeśli gra dobiegnie końca
bool gameOver(char board[][SIDE]) 
{ 
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) ); 
}

// Funkcja przeliczająca najlepszy wynik
int minimax(char board[][SIDE], int depth, bool isAI)
{
	int score = 0;
	int bestScore = 0;
	if (gameOver(board) == true)
	{
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1;
	}
	else
	{
		if(depth < 9)
		{
			if(isAI == true)
			{
				bestScore = -999;
				for(int i=0; i<SIDE; i++)
				{
					for(int j=0; j<SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = COMPUTERMOVE;
							score = minimax(board, depth + 1, false);
							board[i][j] = ' ';
							if(score > bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore = 999;
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = HUMANMOVE;
							score = minimax(board, depth + 1, true);
							board[i][j] = ' ';
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

// Funckja obliczająca najlepszy ruch
int bestMove(char board[][SIDE], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE;
				score = minimax(board, moveIndex+1, false);
				board[i][j] = ' ';
				if(score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

// Funkcja zaczynająca grę 
void playTicTacToe(int whoseTurn) 
{ 
	char board[SIDE][SIDE]; 
	int moveIndex = 0, x = 0, y = 0;

	initialise(board);
	showInstructions(); 
	
	while (gameOver(board) == false && moveIndex != SIDE*SIDE) 
	{ 
		int n;
		if (whoseTurn == COMPUTER) 
		{
			n = bestMove(board, moveIndex);
			x = n / SIDE;
			y = n % SIDE;
			board[x][y] = COMPUTERMOVE; 
			printf("KOMPUTER postawil %c na polu %d\n\n", COMPUTERMOVE, n+1);
			showBoard(board);
			moveIndex ++; 
			whoseTurn = HUMAN;
		} 
		
		else if (whoseTurn == HUMAN) 
		{
			printf("Wolne pola : ");
			for(int i=0; i<SIDE; i++)
				for (int j = 0; j < SIDE; j++)
					if (board[i][j] == ' ')
						printf("%d ", (i * 3 + j) + 1);
			printf("\n\nWybierz pole = ");
			scanf("%d",&n);
			n--;
			x = n / SIDE;
			y = n % SIDE; 
			if(board[x][y] == ' ' && n<9 && n>=0) 
			{
				board[x][y] = HUMANMOVE; 
				printf ("\npostawiles %c na polu %d\n\n", HUMANMOVE, n+1); 
				showBoard(board); 
				moveIndex ++; 
				whoseTurn = COMPUTER;
			}
			else if(board[x][y] != ' ' && n<9 && n>=0) 
			{
				printf("\nPozycja jest zajeta, wybierz inne pole!\n\n");
			}
			else if(n<0 || n>8) 
			{
				printf("bledne pole\n");
			}
		} 
	} 

	// FUnkjca wskazująca, czy jest remis
	if (gameOver(board) == false && moveIndex == SIDE * SIDE) 
		printf("Remis, nikomu nie udalo sie wygrac\n"); 
	else
	{ 
		if (whoseTurn == COMPUTER) 
			whoseTurn = HUMAN; 
		else if (whoseTurn == HUMAN) 
			whoseTurn = COMPUTER; 
		
		declareWinner(whoseTurn); 
	} 
} 

int main() 
{ 
	printf("\n-------------------------------------------------------------------\n\n");
	printf("\t\t\t Kolko krzyzyk\n"); 
	printf("\n-------------------------------------------------------------------\n\n");
	char cont='y';
	do {
		char choice;
	 	printf("Czy chcesz zaczac? (t/n) : ");
	 	scanf(" %c", &choice);

		if(choice=='n')
			playTicTacToe(COMPUTER);
		else if(choice=='t')
			playTicTacToe(HUMAN);
		else
			printf("Zly wybor\n"); 
        
		printf("\nCzy chcesz  wyjsc?(t/n) : ");
       		scanf(" %c", &cont);
	} while(cont=='n');
	return (0); 
} 
