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
	Species deadSpec(0, 0);
	deadSpec.AddSpecToList();
	Species instSpec;
	instSpec.AddSpecToList();
	Species instSpec2;
	instSpec2.AddSpecToList();

	instSpec.AddSpecToList( &instSpec2, Species::listType::HELP );
	instSpec2.AddSpecToList( &instSpec, Species::listType::HELP );

	Board instBoard;	//Board instance	

	do
	{
		instBoard.DrawBoard();
		cin.get( repeat );
		instBoard.UpdateBoard();
	} while ( repeat == '\n' );

	return 0;
}