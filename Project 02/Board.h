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
		int deadIdentifier;

	public:
		Board();
		Board( int, int );
		Board( vector<vector<Species>> );
	private:
		vector<vector<Species>> ParseIntBoard( vector<vector<int>> );
		void ConstructBoard( vector<vector<Species>> );
	public:
		void DrawBoard();
		void UpdateBoard();
	private:
		vector< vector<int> > Board::CheckVertBounds( int, vector< vector<int> > );
		vector< vector<int> > Board::CheckHorizBounds( int, vector< vector<int> > );
		Species CheckDirections( int, int, vector< vector<int> > );
		Species NeighborBehavior( Species, int );
		Species NeighborConflict( vector<int> );
		void SetBoard( vector<vector<Species>> );
		void SetHeight( int );
		void SetWidth( int );
	public:
		vector< vector<Species> > GetBoard();
		int GetHeight();
		int GetWidth();

		void DBG_PrintVector( vector<Species> );
		void DBG_Print2DVector( vector< vector<int> > );
	};
}

#endif
