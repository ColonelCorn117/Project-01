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

	Species::Species( int minAdj, int maxAdj )
	{
		//cout << specList.size();
		int id = GetSpecList().size();
		SetIdentifier( id );
		SetMinAdj( minAdj );
		SetMaxAdj( maxAdj );	
	}

	//************************************************

	void Species::AddSpecToList( Species spec, vector<Species> list, listType type)
	{
		list.push_back( spec );			//Increase temp list size and add this Species to it
		switch ( type )
		{
			case( SPEC ):
				SetSpecList( list );			//Overwrite the desired list with the updated temp list
				break;
			case( HELP ):
				SetHelpers( list );
				break;
			case ( KILL ):
				SetKillers( list );
				break;
			default:
				cout << "\n\nError in Species.cpp - Invalid listType\n\n";
		}
		
		
	}

	//************************************************

	vector<Species> Species::GetSpecList()
	{
		return Species::specList;
	}

	//************************************************

	Species Species::GetSpeciesFromID(int id)
	{
		return GetSpecList()[id];
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

	void Species::SetSpecList( vector<Species> list )
	{
		Species::specList = list;
	}

	//************************************************

	void Species::SetHelpers( vector<Species> list )
	{
		this->helpedBy = list;
	}

	//************************************************

	void Species::SetKillers( vector<Species> list )
	{
		this->killedBy = list;
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