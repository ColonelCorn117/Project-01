#pragma once
#ifndef SPECIES_H
#define SPECIES_H

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
		//char consoleOutput = 'a';	//Representation of this Species in the console window
		vector<Species> killedBy;
		vector<Species> helpedBy;

	public:
		Species();
		Species( int, int );
		static void AddSpecToList( Species, vector<Species> );
		static vector<Species> GetSpecList();
		vector<Species> GetHelpers();
		vector<Species> GetKillers();
		int GetIdentifier();
		int GetMinAdj();
		int GetMaxAdj();
		static void SetSpecList( vector<Species> );
		void SetIdentifier( int );
		void SetMinAdj( int );
		void SetMaxAdj( int );
		
	};
}

#endif
