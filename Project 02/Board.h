#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Species.h"

using namespace std;
using namespace SpeciesNS;

namespace BoardNS
{
	class Board
	{
	private:
		int across;
		int down;
		const int defaultSize = 10;
		vector< vector<Species> > board;
		//array<array<int, across>, down> board;
		int deadIdentifier;

	public:
		Board();
		Board( vector<vector<Species>> );
		Board( int, int );
		vector<vector<Species>> ParseIntBoard( vector<vector<int>> );
		void ConstructBoard( vector<vector<Species>> );
		void DrawBoard();
		void UpdateBoard();
		vector< vector<int> > Board::CheckBounds( int, int, vector< vector<int> > );
		Species CheckDirections( int, int, vector< vector<int> > );
		Species NeighborBehavior( Species, int );
		Species NeighborConflict( vector<int> );
		void SetBoard( vector<vector<Species>> );
		void SetHeight( int );
		void SetWidth( int );
		vector< vector<Species> > GetBoard();
		int GetHeight();
		int GetWidth();

		void DBG_PrintVector( vector<Species> );
		void DBG_Print2DVector( vector< vector<int> > );
	};
}

#endif
