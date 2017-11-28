#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Board.h"

using namespace std;
using namespace SpeciesNS;

namespace BoardNS
{
	//Used to resolve reproduction conflicts
	static std::random_device rd;
	static std::mt19937 gen( rd() );

	//************************************************

	//Blank Constructor
	Board::Board()
	{
		//vector<vector<int>> layout =
		//{ {			//Extra brackets needed
		//	{ 0,0,0,0,0,0,0,2,0,0 },
		//	{ 0,0,1,0,0,0,0,2,0,0 },
		//	{ 1,0,1,0,0,0,0,2,0,0 },
		//	{ 0,1,1,0,0,0,0,0,0,0 },
		//	{ 0,0,0,0,0,0,0,0,0,0 },
		//	{ 0,0,0,0,0,0,0,0,0,0 },
		//	{ 0,0,0,0,0,0,0,0,0,0 },
		//	{ 0,0,0,0,0,0,0,0,0,0 },
		//	{ 0,0,0,0,0,0,0,0,0,0 },
		//	{ 0,0,0,0,0,0,0,0,0,0 }
		//} };

		vector<vector<int>> layout =
		{ {			//Extra brackets needed
			{ 0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,1,1,0,0,0,1,2,0 },
			{ 0,1,0,0,0,0,1,0,0,0 },
			{ 0,1,0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,1,2,0,0,0,2,1,0 },
			{ 0,1,0,0,0,0,1,0,0,0 },
			{ 0,2,0,0,0,0,2,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 }
			} };

		ConstructBoard( ParseIntBoard( layout ) );
	}

	//************************************************

	Board::Board( int down, int across ) : Board::Board( vector<vector<Species*>>( down, vector<Species*>( across, Species::GetSpeciesFromID( 0 ) ) ) )
	{
		//This constuctor delegates (calls) to the constructor that accepts a 2D vector of Species
	}

	//************************************************

	Board::Board( vector<vector<Species*>> board )
	{
		ConstructBoard( board );
	}

	//************************************************

	//Transforms a board of Species identifiers into a board of Species
	vector<vector<Species*>> Board::ParseIntBoard(vector<vector<int>> intBoard)
	{
		vector<vector<Species*>> specBoard;
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

	void Board::ConstructBoard( vector<vector<Species*>> board )
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
				if ( GetBoard()[y][x]->GetIdentifier() != 0 )
				{
					cout << GetBoard()[y][x]->GetIdentifier() << " ";
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
		vector< vector<Species*> > newBoard( GetBoard() );		//Makes copy of old board. Old values will be overwritten in the copy, so no need to make an empty copy.
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

		/*char DBG_stop;
		cin >> DBG_stop;*/

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
	Species* Board::CheckDirections( int y, int x, vector< vector<int> > bothCheck )
	{
		int identifier = GetBoard()[y][x]->GetIdentifier();
		Species* newValue = Species::GetSpeciesFromID( 0 );

		//Used for checking neighbors of living cells
		int neighbors = 0;
		//Species* currSpec = Species::GetSpeciesFromID( identifier );
		vector<Species*> helpers = Species::GetSpeciesFromID( identifier )->GetHelpers();
		vector<Species*> killers = Species::GetSpeciesFromID( identifier )->GetKillers();

		//Used for checking neighbors of dead cells
		vector<int> possNeighbors;

		//Refers to the Species that we are checking the neighbors of (In other words, this doesn't refer to the neighbors)
		enum checkType
		{
			DEAD,
			LIVING
		};

		checkType thisType;
		if ( identifier != 0 )		//Check neighbors of a living square
		{
			thisType = LIVING;
		}
		else	//Check neighbors of a dead square
		{
			//The number of possible neighbor identifiers will be at most, the number of Species created. Vector initialized to all 0.
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
					int neighborID = GetBoard()[y + a - 1][x + b - 1]->GetIdentifier();

					if ( neighborID != 0 )	//Living neighbor... (Note that because of this check, the possNeighbors vector will always say that there are 0 dead neighbor cells. This is intentional.)
					{
						if ( thisType == LIVING )
						{
							if ( neighborID == identifier )	//... of same species.
							{
								neighbors++;
							}
							else	//... of different species.
							{
								//Check if helpful
								for ( unsigned int i = 0; i < helpers.size(); i++ )
								{					
									if ( neighborID == helpers[i]->GetIdentifier() )
									{
										neighbors++;
									}
								}

								//Check if harmful
								for ( unsigned int i = 0; i < killers.size(); i++ )
								{
									if ( neighborID == killers[i]->GetIdentifier() )
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
							cout << "\n\nError (Board) - checkType not properly assigned.\n\n";
						}
					}
				}
				//cout << dirCheck[a][b] << ' ';
			}
			//cout << endl;
		}
		if ( thisType == LIVING )
		{
			newValue = LivingBehavior( GetBoard()[y][x], neighbors );
		}
		else if ( thisType == DEAD )
		{
			newValue = DeadBehavior( GetBoard()[y][x], possNeighbors );
		}

		return newValue;
	}

	//************************************************

	//Dictates how a living cell behaves based on its neighbors.
	Species* Board::LivingBehavior(Species* currSpec, int neighbors)
	{
		//cout << "Identfier = " << currSpec.GetIdentifier() << "     Neighbors = " << neighbors << endl;
		Species* newValue( Species::GetSpeciesFromID( 0 ) );
		if ( currSpec->GetIdentifier() != 0 )	//Safety. Ensure this is a living cell.
		{
			//cout << "MinAdj = " << currSpec.GetMinAdj() << "     MaxAdj = " << currSpec.GetMaxAdj() << endl;
			if ( neighbors < currSpec->GetMinAdj() || neighbors > currSpec->GetMaxAdj() )	//Underpopulation or overpopulation
			{
				newValue = Species::GetSpeciesFromID(0);
			}
			else
			{
				newValue = currSpec;
			}
				
		}
		else
		{
			cout << "Error (Board) - Trying to use LivingBehavior on a dead cell.\n";
		}

		return newValue;
	}

	//************************************************

	//Handles possible reproduction onto this dead cell
	Species* Board::DeadBehavior( Species* currSpec, vector<int> possNeighbors )
	{
		Species* newValue( Species::GetSpeciesFromID( 0 ) );
		if ( currSpec->GetIdentifier() == 0 )		//Safety. Ensure this is a dead cell.
		{	
			vector<int> neighborCount = possNeighbors;	//Need a copy so we can do arithmetic operations without changing the values in the original
			vector<Species*> contenders;
			for ( int i = 1; i < possNeighbors.size(); i++ )
			{
				vector<Species*> helpers = Species::GetSpeciesFromID( i )->GetHelpers();
				vector<Species*> killers = Species::GetSpeciesFromID( i )->GetKillers();

				//Add helpers of current species ID to the count of neighboring cells with that ID
				//(i.e. Consider the scenario: Species 2 helps Species 1 (but not vice-versa). There is 1 neighbor of Species 1 and 1 neighbor of Species 2.
				//Therefore, we'll say that there are 2 neighbors of Species 1, but not 2 neighbors of Species 2 since Species 1 doesn't help Species 2.)
				for ( Species* helper : helpers )
				{
					for ( int j = 1; j < possNeighbors.size(); j++ )
					{
						if ( helper->GetIdentifier() == j )
						{
							//possNeighbor contains the identifier of every species created, in order (even if they aren't a recorded neighbor),
							//so this shouldn't ever overflow if we're using the IDs of already created Species as the index.
							neighborCount[i] += possNeighbors[helper->GetIdentifier()];
							//cout << "Added " << possNeighbors[helper->GetIdentifier()] << " to the neighbor count of Species " << i << endl;
						}
					}
				}

				//Same as above, except subtracting from the neighbor count for every killer
				for ( Species* killer : killers )
				{
					for ( int j = 1; j < possNeighbors.size(); j++ )
					{
						if ( killer->GetIdentifier() == j )
						{
							neighborCount[i] -= possNeighbors[killer->GetIdentifier()];
						}
					}
				}

				if ( neighborCount[i] == 3 )
				{
					contenders.push_back( Species::GetSpeciesFromID( i ) );
				}
			}

			int numContenders = contenders.size();

			if ( numContenders > 0 )
			{
				uniform_int_distribution<int> udistr( 0, numContenders - 1 );
				newValue = contenders[udistr( gen )];			//Randomly chosen contender is newValue
			}
		}
		else
		{
			cout << "Error (Board) - Trying to use DeadBehavior on a living cell.\n";
		}
		

		return newValue;
	}

	//************************************************

	void Board::SetBoard( vector<vector<Species*>> board )
	{
		this->board = board;		//"this" is a pointer, so we can't use dot notation (such as "this.length")
	}

	//************************************************

	void Board::SetHeight( int down )
	{
		this->down = down;
	}

	//************************************************

	void Board::SetWidth( int across )
	{
		this->across = across;
	}

	//************************************************

	vector< vector<Species*> > Board::GetBoard() const
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

	void Board::DBG_PrintVector( vector<Species*> v )
	{
		cout << "DEBUG - Print vector:\n";
		for ( unsigned int x = 0; x < v.size(); x++ )
		{
			cout << v[x]->GetIdentifier() << " ";
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

