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
		vector< vector<int> > board;
		//array<array<int, across>, down> board;
		int deadIdentifier;

	public:
		Board();
		Board( vector<vector<int>> );
		Board( int, int );
		void ConstructBoard( vector<vector<int>> );
		void DrawBoard();
		void UpdateBoard();
		vector< vector<int> > Board::CheckBounds( int, int, vector< vector<int> > );
		int CheckDirections( int, int, vector< vector<int> > );
		int NeighborBehavior( int, int );
		void SetBoard( vector<vector<int>> );
		void SetHeight( int );
		void SetWidth( int );
		vector< vector<int> > GetBoard();
		int GetHeight();
		int GetWidth();

		void DBG_PrintVector( vector<Species> );
		void DBG_Print2DVector( vector< vector<int> > );
	};
}

#endif
