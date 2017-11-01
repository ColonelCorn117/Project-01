#pragma once

#include <vector>
using namespace std;

namespace SpeciesNS
{
	class Species
	{
	private:
		static vector<Species> specList;	//Class declaration (not definition) of the list of all species.

		int identifier;
		int minAdj;
		int maxAdj;
		//char consoleOutput = 'a';		//Representation of this Species in the console window
		vector<Species> helpedBy;
		vector<Species> killedBy;
	public:
		enum listType
		{
			SPEC,
			HELP,
			KILL
		};

	
		Species( int = 2, int = 3 );
		void AddSpecToList( Species, vector<Species>, listType );
		static Species GetSpeciesFromID( int );
		static vector<Species> GetSpecList();
		vector<Species> GetHelpers();
		vector<Species> GetKillers();
		int GetIdentifier();
		int GetMinAdj();
		int GetMaxAdj();
	private:
		static void SetSpecList( vector<Species> );
		void SetHelpers( vector<Species> );
		void SetKillers( vector<Species> );
		void SetIdentifier( int );
		void SetMinAdj( int );
		void SetMaxAdj( int );
	};
}
