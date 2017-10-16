#include <iostream>
#include <vector>
#include "Species.h"

namespace SpeciesNS
{
	vector<Species> Species::specList;	//List of every Species
	vector<Species> killedBy;		//List of Species that this Species is killed by
	vector<Species> helpedBy;		//List of Species that this Species is helped survive by
	int identifier = 1;			//Number used to idenify this species on any square of the any Board
	int minAdj = 2;				//Minimum number of adjacent "living" squares of same or helpful species needed for any square of this species to stay alive (less than this = underpopulation)
	int maxAdj = 3;				//Maximum number of adjacent "living" squares of same or helpful species needed for any square of this species to stay alive (more than this = overpopulation)

	//************************************************

	Species::Species() : Species( 2, 3 )	//Calls other constructor using default values
	{
		//nothing
	}

	//************************************************

	Species::Species( int minAdj, int maxAdj )
	{
		//cout << specList.size();
		int newSpec = GetSpecList().size() + 1;
		SetIdentifier( newSpec );
		SetMinAdj( minAdj );
		SetMaxAdj( maxAdj );
		//specList.resize( newSpec );
		//specList.push_back( *this );		
	}

	//************************************************

	void Species::AddSpecToList( Species spec, vector<Species> list )
	{
		//list.resize( list.size() + 1 );
		list.push_back( spec );			//Increase temp Species list size and adds this Species to the temp Species list
		SetSpecList( list );			//Overwrite the Species lists with the temp
	}

	//************************************************

	vector<Species> Species::GetSpecList()
	{
		return Species::specList;
	}

	//************************************************

	vector<Species> Species::GetHelpers()
	{
		return helpedBy;
	}

	//************************************************

	vector<Species> Species::GetKillers()
	{
		return killedBy;
	}

	//************************************************

	int Species::GetIdentifier()
	{
		return identifier;
	}

	//************************************************

	int Species::GetMinAdj()
	{
		return this->minAdj;
	}

	//************************************************

	int Species::GetMaxAdj()
	{
		return this->maxAdj;
	}

	//************************************************

	void Species::SetSpecList( vector<Species> specList )
	{
		Species::specList = specList;
	}

	//************************************************

	void Species::SetIdentifier(int identifier)
	{
		this->identifier = identifier;;
	}

	//************************************************

	void Species::SetMinAdj(int minAdj)
	{
		this->minAdj = minAdj;
	}

	//************************************************

	void Species::SetMaxAdj( int maxAdj )
	{
		this->maxAdj = maxAdj;
	}
	
}