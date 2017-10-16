//#include "stdafx.h"
#include <iostream>
#include <array>
using namespace std;

const int down = 10;
const int across = 10;
void DrawBoard( array<array<int, down>, across> board );	//draw original board
array<array<int, down>, across> NewBoard( array<array<int, down>, across> board );		//determines what new board looks like
void copy( array<array<int, down>, across> board, array<array<int, down>, across> board2 ); //copies new generation to original generation

int Notmain()
{
	char repeat;

	array<array<int, across>, down> board =
	{ {			//Extra brackets needed
		{ 0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,1,0,0,0,0,1,0,0 },
		{ 1,0,1,0,0,0,0,1,0,0 },
		{ 0,1,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 }
		} };
	do
	{
		DrawBoard( board );
		cin.get( repeat );
		board = NewBoard( board );
	} while ( repeat == '\n' );

	return 0;

}

//************************************************

void copy( array<array<int, down>, across> board1, array<array<int, down>, across> board2 )
{
	for ( int x = 0; x < down; x++ )
	{
		for ( int y = 0; y < across; y++ )
		{
			board2[x][y] = board1[x][y];
		}
	}
}

//************************************************

array<array<int, down>, across> NewBoard( array<array<int, down>, across> board )
{
	int neighbors = 0;
	array<array<int, down>, across> newBoard;
	array<array<int, 3>, 3> checkLayout =			//3x3 Square centered on the current board square. 1 = check in this direction. 0 = dont check in this direction
	{ {				//Extra brackets needed
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 }
		} };

	array<array<int, 3>, 3> dirCheck = checkLayout;


	for ( int x = 0; x < down; x++ )
	{
		for ( int y = 0; y < across; y++ )
		{
			dirCheck = checkLayout;
			neighbors = 0;

			//Check bounds
			if ( x == 0 )
			{
				dirCheck[0][0] = 0;
				dirCheck[0][1] = 0;
				dirCheck[0][2] = 0;
			}
			else if ( x == down - 1 )
			{
				dirCheck[2][0] = 0;
				dirCheck[2][1] = 0;
				dirCheck[2][2] = 0;
			}

			if ( y == 0 )
			{
				dirCheck[0][0] = 0;
				dirCheck[1][0] = 0;
				dirCheck[2][0] = 0;
			}
			else if ( y == across - 1 )
			{
				dirCheck[0][2] = 0;
				dirCheck[1][2] = 0;
				dirCheck[2][2] = 0;
			}

			//cout << "DirCheck for row " << x << ", column " << y << endl;
			for ( int a = 0; a < dirCheck.size(); a++ )
			{
				for ( int b = 0; b < dirCheck[a].size(); b++ )
				{
					//cout << dirCheck[a][b] << ' ';
					if ( dirCheck[a][b] != 0 )
					{
						neighbors += board[x + ( a - 1 )][y + ( b - 1 )];
					}
				}
				//cout << endl;
			}
			//cout << neighbors << " living neighbors." << endl;

			if ( board[x][y] == 1 )
			{
				if ( neighbors < 2 || neighbors > 3 )	//Underpopulation or overpopulation
					newBoard[x][y] = 0;
				else
					newBoard[x][y] = 1;
			}
			else
			{
				if ( neighbors == 3 )	//Reproduction
					newBoard[x][y] = 1;
				else
					newBoard[x][y] = 0;
			}
		}
	}
	return newBoard;
}

//************************************************

void DrawBoard( array<array<int, down>, across> board )
{

	for ( int x = 0; x < down; x++ )
	{
		for ( int y = 0; y < across; y++ )
		{
			if ( board[x][y] == 1 )
				cout << "O ";
			else
				cout << ". ";
		}
		cout << endl;
	}
}

//************************************************

