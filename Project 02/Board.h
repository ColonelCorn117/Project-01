#pragma once

#include <array>
#include "Species.h"

using namespace std;
using namespace SpeciesNS;

namespace BoardNS
{
	class Board
	{
	private:
		int across = 10;
		int down = 10;
		const int defaultSize = 10;
		vector< vector<Species*> > board;
		int deadIdentifier = 0;

	public:
		Board();
		Board( int, int );
		Board( vector<vector<Species*>> );
	private:
		vector<vector<Species*>> ParseIntBoard( vector<vector<int>> );
		void ConstructBoard( vector<vector<Species*>> );
	public:
		void DrawBoard();
		void UpdateBoard();
	private:
		vector< vector<int> > Board::CheckVertBounds( int, vector< vector<int> > );
		vector< vector<int> > Board::CheckHorizBounds( int, vector< vector<int> > );
		Species* CheckDirections( int, int, vector< vector<int> > );
		Species* LivingBehavior( Species*, int );
		Species* DeadBehavior( Species*, vector<int> );
		void SetBoard( vector<vector<Species*>> );
		void SetHeight( int );
		void SetWidth( int );
	public:
		vector< vector<Species*> > GetBoard() const;
		int GetHeight() const;
		int GetWidth() const;

		void DBG_PrintVector( vector<Species*> );
		void DBG_Print2DVector( vector< vector<int> > );
	};
}
