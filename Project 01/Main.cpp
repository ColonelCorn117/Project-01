#include <iostream>
#include "Board.h"
#include "Species.h"

using namespace std;
using namespace BoardNS;
using namespace SpeciesNS;


int main()
{
	char repeat = ' ';

	//Create board, populate it with species identifiers, run time ticks
	Board instBoard;	//Board instance
	Species instSpec;	//Species instance
	Species::AddSpecToList( instSpec, Species::GetSpecList() );	//GetSpecList return reference instead?

	do
	{
		instBoard.DrawBoard();
		cin.get( repeat );
		instBoard.UpdateBoard();
	} while ( repeat == '\n' );

	return 0;
}