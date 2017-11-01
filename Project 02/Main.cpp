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
	deadSpec.AddSpecToList( deadSpec, Species::GetSpecList(), Species::listType::SPEC );
	Species instSpec;	//Species instance. Class keyword needed or constructor isn't found
	instSpec.AddSpecToList( instSpec, Species::GetSpecList(), Species::listType::SPEC );
	Board instBoard;	//Board instance	

	do
	{
		instBoard.DrawBoard();
		cin.get( repeat );
		instBoard.UpdateBoard();
	} while ( repeat == '\n' );

	return 0;
}