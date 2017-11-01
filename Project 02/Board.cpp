#include <iostream>
#include <vector>
#include <algorithm>
#include "Board.h"

using namespace std;
using namespace SpeciesNS;

namespace BoardNS
{
	int down = 10;
	int across = 10;
	const int defaultSize = 10;			//Size of the board if no custom values are entered
	vector< vector<Species> > board;		//Acts like a 2D array (like int[][] in Java)
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
		ConstructBoard( ParseIntBoard( layout ) );
	}

	//************************************************

	Board::Board( int down, int across ) : Board::Board( vector<vector<Species>>( down, vector<Species>( across, Species::GetSpeciesFromID( 0 ) ) ) )
	{
		//This constuctor delegates (calls) to the constructor that accepts a 2D vector of Species
	}

	//************************************************

	Board::Board( vector<vector<Species>> board )
	{
		ConstructBoard( board );
	}

	//************************************************

	//Transforms a board of Species identifiers into a board of Species
	vector<vector<Species>> Board::ParseIntBoard(vector<vector<int>> intBoard)
	{
		vector<vector<Species>> specBoard;
		specBoard.resize( intBoard.size() );
		for ( unsigned int y = 0; y < intBoard.size(); y++ )
		{
			specBoard[y].resize( intBoard[y].size() );
			for ( unsigned int x = 0; x < intBoard[y].size(); x++ )
			{
				specBoard[y][x] = Species::GetSpeciesFromID( intBoard[y][x] );
			}
		}
		
		return specBoard;
	}

	//************************************************

	void Board::ConstructBoard( vector<vector<Species>> board )
	{
		SetBoard( board );
		SetHeight( GetBoard().size() );
		SetWidth( GetBoard()[0].size() );
		//cout << "Down = " << GetHeight() << "     Across = " << GetWidth() << endl;
	}

	//************************************************

	void Board::DrawBoard()
	{
		system( "cls" );		//Clears screen
		//cout << "Down = " << down << "     Across = " << across << endl;
		for ( unsigned int y = 0; y < GetBoard().size(); y++ )
		{
			for ( unsigned int x = 0; x < GetBoard()[y].size(); x++ )
			{
				if ( GetBoard()[y][x].GetIdentifier() != 0 )
				{
					cout << GetBoard()[y][x].GetIdentifier() << " ";
				}
				else
				{
					cout << ". ";
				}
			}
			cout << endl;
		}
	}

	//************************************************

	void Board::UpdateBoard()
	{
		int neighbors = 0;
		vector< vector<Species> > newBoard( GetBoard() );		//Makes copy of old board. Old values will be overwritten in the copy, so no need to make an empty copy.
		vector< vector<int> > masterCheck =			//3x3 Square centered on the current board square. 1 = check in this direction. 0 = dont check in this direction
		{ {				//Extra brackets needed
			{ 1, 1, 1 },
			{ 1, 0, 1 },
			{ 1, 1, 1 }
		} };

		vector< vector<int> > vertCheck;	//Will hold modified masterCheck 2D vector. Will possibly have its first or last row (XOR) changed to all 0.
		vector< vector<int> > bothCheck;	//Will hold a modified vertCheck 2D vector. Will possibly have its first or last column (XOR) changed to all 0.

		for ( unsigned int y = 0; y < GetBoard().size(); y++ )
		{
			vertCheck = CheckVertBounds( y, masterCheck );
			for ( unsigned int x = 0; x < GetBoard()[y].size(); x++ )
			{
				bothCheck = CheckHorizBounds( x, vertCheck );	//Check bounds to make sure we don't attempt to check out of bounds of an array
				newBoard[y][x] = CheckDirections( y, x, bothCheck );
			}
		}
		SetBoard( newBoard );
	}

	//************************************************

	//Modifies the 3x3 checkLayout vector based on the current position on the board. Separated from horizCheck so vertical bounds aren't unnecessarily checked while moving across a row.
	vector< vector<int> > Board::CheckVertBounds( int y, vector< vector<int> > masterCheck )
	{
		//Check bounds
		if ( y == 0 )
		{
			masterCheck[0][0] = 0;
			masterCheck[0][1] = 0;
			masterCheck[0][2] = 0;
		}
		else if ( y == down - 1 )
		{
			masterCheck[2][0] = 0;
			masterCheck[2][1] = 0;
			masterCheck[2][2] = 0;
		}

		return masterCheck;
	}

	//************************************************

	vector< vector<int> > Board::CheckHorizBounds( int x, vector< vector<int> > vertCheck )
	{
		if ( x == 0 )
		{
			vertCheck[0][0] = 0;
			vertCheck[1][0] = 0;
			vertCheck[2][0] = 0;
		}
		else if ( x == across - 1 )
		{
			vertCheck[0][2] = 0;
			vertCheck[1][2] = 0;
			vertCheck[2][2] = 0;
		}

		//DBG_Print2DVector( checkLayout );

		return vertCheck;
	}

	//************************************************

	//Check the neighbors of the current board square using the 3x3 checkLayout vector as a guide and determine what the current square should change to
	Species Board::CheckDirections( int y, int x, vector< vector<int> > bothCheck )
	{
		int identifier = GetBoard()[y][x].GetIdentifier();
		Species newValue( Species::GetSpeciesFromID( 0 ) );

		//Used for checking neighbors of living cells
		int neighbors = 0;
		Species currSpec( Species::GetSpeciesFromID( 0 ) );
		vector<Species> helpers;
		vector<Species> killers;

		//Used for checking neighbors of dead cells
		vector<int> possNeighbors;

		//Refers to the Species that we are checking the neighbors of (i.e. This doesn't refer to the neighbors)
		enum checkType
		{
			DEAD,
			LIVING
		};

		checkType thisType;
		if ( identifier != 0 )		//Check neighbors of a living square
		{
			currSpec = Species::GetSpeciesFromID( identifier );
			helpers = currSpec.GetHelpers();
			killers = currSpec.GetKillers();
			thisType = LIVING;
		}
		else	//Check neighbors of a dead square
		{
			//The number of possible neighbor identifiers will be at most, the number of Species created. We're not going to count the "dead species", so subtract 1. Vector initialized to all 0.
			possNeighbors.resize( Species::GetSpecList().size(), 0 );
			thisType = DEAD;
		}

		for ( unsigned int a = 0; a < bothCheck.size(); a++ )
		{
			for ( unsigned int b = 0; b < bothCheck[a].size(); b++ )
			{
				if ( bothCheck[a][b] != 0 )	//Check in this direction
				{
					//cout << "[a][b] = [" << a << "][" << b << "]\n\n";
					int neighborID = GetBoard()[y + a - 1][x + b - 1].GetIdentifier();

					if ( neighborID != 0 )	//Living neighbor...
					{
						if ( thisType == LIVING )
						{

							if ( neighborID == GetBoard()[y][x].GetIdentifier() )	//... of same species.
							{
								neighbors++;
							}
							else	//... of different species.
							{
								//Check if helpful
								for ( unsigned int i = 0; i < helpers.size(); i++ )
								{
									if ( bothCheck[a][b] == helpers[i].GetIdentifier() )
									{
										neighbors++;
									}
								}

								//Check if harmful
								for ( unsigned int i = 0; i < killers.size(); i++ )
								{
									if ( bothCheck[a][b] == killers[i].GetIdentifier() )
									{
										neighbors--;
									}
								}
							}
						}
						else if ( thisType == DEAD )
						{
							possNeighbors[neighborID]++;	//+1 living neighbor found with specific identifier.	
						}
						else
						{
							cout << "\n\nError - checkType not properly assigned.\n\n";
						}
					}
				}
				//cout << dirCheck[a][b] << ' ';
			}
			//cout << endl;
		}
		if ( thisType == LIVING )
		{
			newValue = NeighborBehavior( GetBoard()[y][x], neighbors );
		}
		else if ( thisType == DEAD )
		{
			newValue = NeighborConflict( possNeighbors );
		}

		//cout << "board[" << x << "][" <<y << "] has " << neighbors << " living neighbors. New value = " << newValue << endl;

		return newValue;
	}

	//************************************************

	//Dictates how a living cell behaves based on its neighbor requirements
	Species Board::NeighborBehavior(Species currSpec, int neighbors)
	{
		//cout << "Identfier = " << currSpec.GetIdentifier() << "     Neighbors = " << neighbors << endl;
		Species newValue( Species::GetSpeciesFromID( 0 ) );
		if ( currSpec.GetIdentifier() != 0 )	//Living cell. Check if still alive.
		{
			//cout << "MinAdj = " << currSpec.GetMinAdj() << "     MaxAdj = " << currSpec.GetMaxAdj() << endl;
			if ( neighbors < currSpec.GetMinAdj() || neighbors > currSpec.GetMaxAdj() )	//Underpopulation or overpopulation
			{
				newValue = Species::GetSpeciesFromID(0);
			}
				
			else
			{
				newValue = currSpec;
			}
				
		}
		else //Dead Cell. Check for Reproduction
		{
			if ( neighbors == 3 )
			{
				newValue = currSpec;
			}
				
			else
			{
				newValue = newValue = Species::GetSpeciesFromID( 0 );
			}		
		}

		return newValue;
	}

	//************************************************

	//Handles conflicts where multiple species can reproduce onto one dead square
	Species Board::NeighborConflict( vector<int> possNeighbors )
	{
		Species newValue (Species::GetSpeciesFromID(0));
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
					//max = possNeighbors[i];
					conflict = true;
					break;
				}
			}

			if ( conflict )
			{
				cout << "No sharing\n";
				newValue = Species::GetSpeciesFromID( 0 );
			}
			else if ( max == 3 )	//Assumes all species require 3 to reproduce
			{
				newValue = Species::GetSpeciesFromID( distance( possNeighbors.begin(), maxIterator ));
			}
		}

		return newValue;
	}

	//************************************************

	void Board::SetBoard( vector<vector<Species>> board )
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

	vector< vector<Species> > Board::GetBoard() const
	{
		return this->board;
	}

	//************************************************

	int Board::GetHeight() const
	{
		return this->down;
	}

	//************************************************

	int Board::GetWidth() const
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
		for ( unsigned int y = 0; y < v.size(); y++ )
		{
			for ( unsigned int x = 0; x < v[y].size(); x++ )
			{
				cout << v[y][x] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

