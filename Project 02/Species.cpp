#include <iostream>
#include <vector>
#include "Species.h"

namespace SpeciesNS
{
	vector<Species*> Species::specList;	//List of every Species
	//vector<Species> killedBy;		//List of Species that this Species is killed by
	//vector<Species> helpedBy;		//List of Species that this Species is helped survive by
	//int identifier = 1;			//Number used to idenify this species on any square of the any Board
	//int minAdj = 2;				//Minimum number of adjacent "living" squares of same or helpful species needed for any square of this species to stay alive (less than this = underpopulation)
	//int maxAdj = 3;				//Maximum number of adjacent "living" squares of same or helpful species needed for any square of this species to stay alive (more than this = overpopulation)
	
	//************************************************

	Species::Species( int minAdj, int maxAdj )
	{
		//cout << specList.size();
		int id = GetSpecList().size();
		this->SetIdentifier( id );
		this->SetMinAdj( minAdj );
		this->SetMaxAdj( maxAdj );
	}

	//************************************************

	void Species::AddSpecToList()
	{
		Species::specList.push_back( this );
	}

	//************************************************

	void Species::AddSpecToList( Species* spec, listType type )
	{
		//list.push_back( spec );			//Increase temp list size and add this Species to it
		switch ( type )
		{
			case( HELP ):
				this->AddHelper( spec );
				break;
			case ( KILL ):
				this->AddKiller( spec );
				break;
			default:
				cout << "\n\nError in Species.cpp - Invalid listType (Add)\n\n";
		}
	}

	//************************************************

	void Species::RemoveSpecFromList( Species* spec, listType type )
	{		
		switch ( type )
		{
			case( HELP ):
				this->RemoveHelper( spec );
				break;
			case ( KILL ):
				this->RemoveKiller( spec );
				break;
			default:
				cout << "\n\nError in Species.cpp - Invalid listType (Remove)\n\n";
		}
	}

	//************************************************

	Species* Species::GetSpeciesFromID(int id)
	{
		/*cout << "ID = " << id << endl;*/
		return GetSpecList()[id];
	}

	//************************************************

	vector<Species*> Species::GetSpecList()
	{
		return Species::specList;
	}

	//************************************************

	vector<Species*> Species::GetHelpers() const
	{
		return helpedBy;
	}

	//************************************************

	vector<Species*> Species::GetKillers() const
	{
		return killedBy;
	}

	//************************************************

	int Species::GetIdentifier() const
	{
		return identifier;
	}

	//************************************************

	int Species::GetMinAdj() const
	{
		return this->minAdj;
	}

	//************************************************

	int Species::GetMaxAdj() const
	{
		return this->maxAdj;
	}

	//************************************************

	void Species::SetIdentifier( int identifier )
	{
		this->identifier = identifier;
	}

	//************************************************

	void Species::SetMinAdj( int minAdj )
	{
		this->minAdj = minAdj;
	}

	//************************************************

	void Species::SetMaxAdj( int maxAdj )
	{
		this->maxAdj = maxAdj;
	}

	//************************************************

	void Species::AddHelper( Species* spec )
	{
		bool addHelper = true;
		if ( GetHelpers().size() > 0 )
		{
			for each ( Species* helper in this->GetHelpers() )
			{
				if ( helper->GetIdentifier() == spec->GetIdentifier() )
				{
					addHelper = false;
					break;
				}
			}
		}

		if ( addHelper )
		{
			this->helpedBy.push_back( spec );
		}
		else
		{
			cout << "Species is already a Helper.\n";
		}
		
	}

	//************************************************

	void Species::AddKiller( Species* spec )
	{
		bool addKiller = true;
		if ( GetKillers().size() > 0 )
		{
			for each ( Species* killer in this->GetKillers() )
			{
				if ( killer->GetIdentifier() == spec->GetIdentifier() )
				{
					addKiller = false;
					break;
				}
			}
		}

		if ( addKiller )
		{
			this->killedBy.push_back( spec );
		}
		else
		{
			cout << "Species is already a Killer.\n";
		}
	}

	//************************************************

	void Species::RemoveHelper( Species* spec )
	{

	}

	//************************************************

	void Species::RemoveKiller( Species* spec )
	{

	}

	//************************************************

	//void Species::SetSpecList( vector<Species> list )
	//{
	//	Species::specList = list;
	//}

	////************************************************

	//void Species::SetHelpers( vector<Species> list )
	//{
	//	this->helpedBy = list;
	//}

	////************************************************

	//void Species::SetKillers( vector<Species> list )
	//{
	//	this->killedBy = list;
	//}

	
	
}