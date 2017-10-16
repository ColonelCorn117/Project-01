#include <iostream>
#include <vector>
#include <algorithm>
#include "Board.h"

using namespace std;
using namespace SpeciesNS;

namespace BoardNS
{
	int across = 10;
	int down = 10;
	const int defaultSize = 10;			//Size of the board if no custom values are entered
	vector< vector<int> > board;		//Acts like a 2D array (like int[][] in Java)
	int deadIdentifier = 0;				//Squares with this identifier value are considered "dead"


	//************************************************

	//Blank Constructor
	Board::Board()
	{
		vector<vector<int>> layout =
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
		ConstructBoard( layout );
		//SetHeight( board.size() );
		//SetWidth( board[0].size() );
		//board.resize(defaultSize, vector<int>(defaultSize, deadIdentifier));
	}

	//************************************************

	Board::Board( vector<vector<int>> board )
	{
		ConstructBoard( board );
	}

	//************************************************

	Board::Board( int down, int across )
	{
		SetHeight( down );
		SetWidth( across );
		GetBoard().resize( down, vector<int>( across, deadIdentifier ) );

	}

	//************************************************

	void Board::ConstructBoard( vector<vector<int>> board )
	{
		SetBoard( board );
		SetHeight( GetBoard().size() );
		SetWidth( GetBoard()[0].size() );
		//cout << "Down = " << GetHeight() << "     Across = " << GetWidth() << endl;
	}

	//************************************************

	void Board::DrawBoard()
	{
		//cout << "Down = " << down << "     Across = " << across << endl;
		for ( unsigned int x = 0; x < GetBoard().size(); x++ )
		{
			for ( unsigned int y = 0; y < GetBoard()[x].size(); y++ )
			{
				if ( GetBoard()[x][y] != 0 )
					//cout << "O ";
					cout << GetBoard()[x][y] << " ";
				else
					cout << ". ";
			}
			cout << endl;
		}
	}

	//************************************************

	void Board::UpdateBoard()
	{
		int neighbors = 0;
		vector< vector<int> > newBoard( GetBoard() );		//Makes copy of old board. Old values will be overwritten in the copy, so no need to make an empty copy.
		vector< vector<int> > checkLayout =			//3x3 Square centered on the current board square. 1 = check in this direction. 0 = dont check in this direction
		{ {				//Extra brackets needed
			{ 1, 1, 1 },
			{ 1, 0, 1 },
			{ 1, 1, 1 }
		} };

		vector< vector<int> > dirCheck = checkLayout;		//Copy checkLayout so we can make changes to the copy
		//DBG_Print2DVector( newBoard );

		for ( unsigned int x = 0; x < GetBoard().size(); x++ )
		{
			for ( unsigned int y = 0; y < GetBoard()[x].size(); y++ )
			{

				dirCheck = CheckBounds( x, y, checkLayout );	//Check bounds to make sure we don't attempt to check out of bounds of an array
				//cout << "DirCheck for row " << x << ", column " << y << endl;		//CheckDirections will print dirCheck
				newBoard[x][y] = CheckDirections( x, y, dirCheck );
				
			}
		}
		//DBG_Print2DVector( newBoard );
		SetBoard( newBoard );
	}

	//************************************************

	vector< vector<int> > Board::CheckBounds( int x, int y, vector< vector<int> > checkLayout )
	{
		//Check bounds
		if ( x == 0 )
		{
			checkLayout[0][0] = 0;
			checkLayout[0][1] = 0;
			checkLayout[0][2] = 0;
		}
		else if ( x == down - 1 )
		{
			checkLayout[2][0] = 0;
			checkLayout[2][1] = 0;
			checkLayout[2][2] = 0;
		}

		if ( y == 0 )
		{
			checkLayout[0][0] = 0;
			checkLayout[1][0] = 0;
			checkLayout[2][0] = 0;
		}
		else if ( y == across - 1 )
		{
			checkLayout[0][2] = 0;
			checkLayout[1][2] = 0;
			checkLayout[2][2] = 0;
		}

		//DBG_Print2DVector( checkLayout );

		return checkLayout;
	}

	//************************************************

	int Board::CheckDirections( int x, int y, vector< vector<int> > dirCheck )
	{
		int identifier = GetBoard()[x][y];
		int neighbors = 0;
		int newValue = 0;

		if ( identifier != 0 )		//Checking neighbors of living square
		{
			Species currSpec = Species::GetSpecList()[identifier - 1];
			vector<Species> helpers = currSpec.GetHelpers();
			vector<Species> killers = currSpec.GetKillers();

			for ( unsigned int a = 0; a < dirCheck.size(); a++ )
			{
				for ( unsigned int b = 0; b < dirCheck[a].size(); b++ )
				{
					if ( dirCheck[a][b] != 0 )	//Check in this direction
					{
						int neighborID = GetBoard()[x + a - 1][y + b - 1];
						if ( neighborID != 0 )	//Living neighbor...
						{
							if ( neighborID == GetBoard()[x][y] )	//... of same species.
							{
								neighbors++;
							}
							else	//... of different species.
							{
								//Check if helpful
								for ( unsigned int i = 0; i < helpers.size(); i++ )
								{
									if ( dirCheck[a][b] == helpers[i].GetIdentifier() )
									{
										neighbors++;
									}
								}

								//Check if harmful
								for ( unsigned int i = 0; i < killers.size(); i++ )
								{
									if ( dirCheck[a][b] == killers[i].GetIdentifier() )
									{
										neighbors--;
									}
								}
							}
						}
						
						

						
					}
					//cout << dirCheck[a][b] << ' ';
				}
				//cout << endl;
			}
			newValue = NeighborBehavior( GetBoard()[x][y], neighbors );
		}
		else	//Checking neighbors of dead square
		{
			//DBG_PrintVector( Species::GetSpecList() );
			//DBG_Print2DVector( dirCheck );

			vector<int> possNeighbors( Species::GetSpecList().size(), 0 );	//The number of possible neighbor identifiers will be at most, the number of Species created. Vector initialized to all 0.
			
			for ( unsigned int a = 0; a < dirCheck.size(); a++ )
			{
				for ( unsigned int b = 0; b < dirCheck[a].size(); b++ )
				{
					if ( dirCheck[a][b] != 0 )
					{
						//cout << "here1\n";
						//cout << "Checked X = " << x << endl;
						//cout << "Checked Y = " << y << endl;
						//cout << "board[x][y] = " << GetBoard()[x + ( a - 1 )][y + ( b - 1 )] << endl;
						int neighborID = GetBoard()[x + a - 1][y + b - 1];
						//cout << "Neighbor X = " << x + a << endl;
						//cout << "Neighbor Y = " << y + b << endl;
						//cout << "Neighbor ID = " << neighborID << endl;
						if ( neighborID != 0 )
						{
							possNeighbors[neighborID - 1]++;	//+1 living neighbor found with specific identifier.	//Breaks here
						}
						//cout << "here2 \n\n";
					}
					//cout << dirCheck[a][b] << ' ';
				}
				//cout << endl;
			}
			
			auto maxIterator = max_element( possNeighbors.begin(), possNeighbors.end() );		//maxIterator returns the iterator (pointer) with the highest value (not the value itself). Dereferencing gives the value AT the iterator.
			int max = *maxIterator;		//Number of neighbors with the iterator: std::distance(possNeighbors.begin(), maxIterator) (std::distance() gives the value OF the iterator.)
			//cout << "Max iter = " << distance( possNeighbors.begin(), maxIterator ) << "     Max = " << max << endl;
			if ( max > 0 )
			{
				
				bool conflict = false;
				for ( unsigned int i = 1; i < possNeighbors.size(); i++ )	//There may be a value equal to max, since max_element returns the iterator of the first value equal to the max
				{
					if ( i != distance( possNeighbors.begin(), maxIterator ) && possNeighbors[i] == max )		//Two species are able to reproduce onto this square, so no one gets it.
					{
						max = possNeighbors[i];
						conflict = true;
						break;
					}
				}

				if ( conflict )
				{
					cout << "No sharing\n";
					newValue = 0;
				}
				else if ( max == 3 )
				{
					//identifier = distance( possNeighbors.begin(), maxIterator ) + 1;
					//neighbors = max;
					//newValue = NeighborBehavior( identifier, neighbors );
					newValue = distance( possNeighbors.begin(), maxIterator ) + 1;
				}
			}
		}

		//cout << "board[" << x << "][" <<y << "] has " << neighbors << " living neighbors. New value = " << newValue << endl;
		return newValue;
	}

	//************************************************

	int Board::NeighborBehavior(int identifier, int neighbors)
	{
		Species currSpec ( Species::GetSpecList()[identifier - 1] );
		//cout << "Identfier = " << currSpec.GetIdentifier() << "     Neighbors = " << neighbors << endl;
		int newValue = 0;
		if ( identifier != 0 )
		{
			//cout << "MinAdj = " << currSpec.GetMinAdj() << "     MaxAdj = " << currSpec.GetMaxAdj() << endl;
			if ( neighbors < currSpec.GetMinAdj() || neighbors > currSpec.GetMaxAdj() )	//Underpopulation or overpopulation
			{
				newValue = 0;
			}
				
			else
			{
				newValue = identifier;
			}
				
		}
		else //Reproduction
		{
			if ( neighbors == 3 )
			{
				newValue = identifier;
			}
				
			else
			{
				newValue = 0;
			}
				
		}

		return newValue;
	}

	//************************************************

	void Board::SetBoard( vector<vector<int>> board )
	{
		this->board = board;
	}

	//************************************************

	void Board::SetHeight( int down )
	{
		this->down = down;		//"this" is a pointer, so we can't use dot notation (such as "this.length")
	}

	//************************************************

	void Board::SetWidth( int across )
	{
		this->across = across;
	}

	//************************************************

	vector< vector<int> > Board::GetBoard()
	{
		return this->board;
	}

	//************************************************

	int Board::GetHeight()
	{
		return this->down;
	}

	//************************************************

	int Board::GetWidth()
	{
		return this->across;
	}

	//================================================
	// Debug Functions
	//================================================

	void Board::DBG_PrintVector( vector<Species> v )
	{
		cout << "DEBUG - Print vector:\n";
		for ( unsigned int x = 0; x < v.size(); x++ )
		{
			cout << v[x].GetIdentifier() << " ";
		}
		cout << endl;
	}

	//************************************************

	void Board::DBG_Print2DVector( vector< vector<int> > v )
	{
		cout << "DEBUG - Print 2D vector:\n";
		for ( unsigned int x = 0; x < v.size(); x++ )
		{
			for ( unsigned int y = 0; y < v[x].size(); y++ )
			{
				cout << v[x][y] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

