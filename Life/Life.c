// Life.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <Windows.h>/*used to make game sleep*/
#include <stdlib.h>

#define SIZE (10)
#define TURNCOUNT (100)

/* fills array with random numbers */
void fillArray(int arr[][SIZE]);
/* do a turn in the game */
int doTurn(int arr[][SIZE]);
/* checks cell next turn value */
int getCellNextValue(int arr[][SIZE], int i, int j);
/* prints current turn */
void printTurn(int arr[][SIZE], int turn);

/* gets new values
if main cell changes values, it isnt the original
board again so the wrong cells will live and die*/
static int temp[SIZE][SIZE];

int main(int argc, char * argv[])
{
	int x = 1;
	int arr[SIZE][SIZE];
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; j++)
			arr[i][j] = 0;

	fillArray(arr);
	int turns;
	if (argc > 1)
		turns = atoi(argv[1]);
	else
		turns = TURNCOUNT;
	for (int i = 0; i < turns; i++)
	{
		printTurn(arr, i);
		int remainingCells = doTurn(arr);
		if (remainingCells == 0)
			break;
	}
	return 0;
}
void fillArray(int arr[][SIZE])
{
	srand(time(NULL));
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; j++)
		{
			arr[i][j] = rand() % 2;
		}
	}
}
int doTurn(int arr[][SIZE])
{
	int numOfLives = 0;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; j++)
		{
			int cellNextValue = getCellNextValue(arr, i, j);
			numOfLives += cellNextValue;
			temp[i][j] = cellNextValue;
		}
	}
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; j++)
		{
			arr[i][j] = temp[i][j];
		}
	}
	return numOfLives;
}

int getCellNextValue(int arr[][SIZE], int i, int j)
{
	int v;
	if (i == 5 && j == 6)
		v = 1;
	int counter = 0;
	for (int x = i - 1; x < i + 2; ++x)
	{
		for (int y = j - 1; y < j + 2; ++y)
		{
			if (x >= 0 && x < SIZE && y >= 0 && y < SIZE)
				counter += arr[x][y];
		}
	}
	/* its faster removing cell value then checking every time if it isnt current cell */
	counter -= arr[i][j];
	/* check if cell has exactly 3 neighbors, if so create new life */
	if (arr[i][j] == 0 && counter == 3)
		return 1;
	/* if cell has 2 or 3 neighbors keep cell at current state*/
	if (counter == 3 || counter == 2)
		return arr[i][j];
	/* kill cell in case of overcrowding or loneliness*/
	return 0;
}

void printTurn(int arr[][SIZE], int turn)
{
	system("cls");
	printf("\rTurn %d\n\n", turn + 1);
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (arr[i][j] == 1)
				printf("O");
			else
				printf("_");
		}
		printf("\n");
	}
	printf("\n");
	Sleep(1000);

}