#include "stdafx.h"
#include <iostream>
using namespace std;

const int width = 10;
const int height = 10;
void drawBoard(int board[width][height]); //draw original board
void newBoard(int board[width][height]); //determines what new board looks like
void copy(int board1[width][height], int board2[width][height]); //copies new generation to original generation

int main()
{
	char repeat;

	int board[width][height] =
	{

		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,1,0,0,0 },
		{ 1,0,1,0,0,0,1,0,0,0 },
		{ 0,1,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 }
	};
	do
	{
		drawBoard(board);
		cin.get(repeat);
		newBoard(board);
	} while (repeat == '\n');

	return 0;

}

void copy(int board1[width][height], int board2[width][height])
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			board2[x][y] = board1[x][y];
		}
	}
}

void newBoard(int board[width][height])
{
	int neighbors = 0;
	int board3[width][height];

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (x == 0 || y == 0 )
				board3[x][y] = 0;
			else
			{
				neighbors = board[x - 1][y - 1] + board[x - 1][y] + board[x - 1][y + 1] + board[x][y - 1] + board[x][y + 1] + board[x + 1][y - 1] + board[x + 1][y] + board[x + 1][y + 1];
				if (board[x][y] == 1)
				{
					if (neighbors < 2 || neighbors>3)
						board3[x][y] = 0;
					else
						board3[x][y] = 1;
				}
				else
				{
					if (neighbors == 3)
						board3[x][y] = 1;
					else
						board3[x][y] = 0;
				}
			}
		}
	}
	copy(board3, board);
}

void drawBoard(int board[width][height])
{

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (board[x][y] == 1)
				cout << "1";
			else
				cout << "0";
		}
		cout << endl;
	}
}

