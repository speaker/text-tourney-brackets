/*******************************************************************************
* 
*    text-tourney-brackets
*
*    Simple text driven tournament bracketing tool
*    
*    Copyright (C) 2015  Adam Potolsky
*
*    This program is free software; you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation; either version 2 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License along
*    with this program; if not, write to the Free Software Foundation, Inc.,
*    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
* Filename:      roster.cpp
* Description:   roster.cpp contains the execuation entry routine
* Notations:
*
* Author:        Adam  Potolsky
*
* Revision History:  Under Revision Control
*
* Public Routines:
*  int  load_teams(std::string filename);
*
* Private routines:
*
*******************************************************************************/ 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "roster.h"
#include "team.h"


Roster::Roster(std::string filename)
{
	load_teams(filename);
}

//
// This routine will read in the next line with valid data for the roster
//
ttb_error_t Roster::read_next_team()
{
	std::string sOneLine("#");

	while ('#' == sOneLine[0] || 0 == sOneLine.size()) // Skip comments
	{
		// If it's the end of file, we;re done.
		if(file.eof()) return ttb_EOF;

		std::getline(file, sOneLine);
		//std::cout << "DEBUG: sOneLine:" << sOneLine << std::endl;
	}

	std::stringstream sstream(sOneLine);


	std::string seed_str = "";

	std::string tmp_id = "";
	std::string tmp_last = "";
	std::string tmp_first = "";
	std::string tmp_residence = "";

	getline(sstream, tmp_id, ',' );
	getline(sstream, tmp_last, ',' );
	getline(sstream, tmp_first, ',' );
	getline(sstream, tmp_residence, ',' );

	getline(sstream, seed_str, ',' );

	//std::cout << "DEBUG: seed_str:" << seed_str << std::endl;

	int tmp_seed = -1;

	if( "" == seed_str ) {
		tmp_seed = 0;
	} else {
		std::stringstream( seed_str ) >> tmp_seed;
	}

	//std::cout << "DEBUG: t.seed:" << seed_str << std::endl;

	team t(tmp_id, tmp_last, tmp_first,tmp_residence, tmp_seed);

	add_team(t);

	return ttb_OK;
}


ttb_error_t Roster::display_team_list()
{
	std::cout << "\n\t\tTeam List Dump:" << std::endl;


	std::vector<team>::const_iterator i = team_list.begin();

	for( ; i != team_list.end() ; i++)
	{
		std::cout << i->id() << ": ";
		std::cout << i->last() << ", ";
		std::cout << i->first() << ", From: ";
		std::cout << i->residence() << ", Seed:";
		std::cout << i->seed() << std::endl;
	}

	std::cout << "\t\tEnd of List" << std::endl;

	return ttb_OK;
}

ttb_error_t Roster::add_team(team t)
{
	// nothing for now
	team_list.push_back(t);
	return ttb_OK;
}

ttb_error_t Roster::setup_brackets()
{
	// nothing for now
	return ttb_OK;
}

ttb_error_t Roster::load_roster(std::string filename)
{
	return load_teams(filename);
}

ttb_error_t Roster::load_teams(std::string filename)
{
	file.open(filename.c_str(),std::ios::in);

	if( ! file.is_open()) {
		std::cerr << "There was an error opening file:" << filename << std::endl;
		return ttb_unknown;
	}

	std::cout << "Filename:" << filename << std::endl;

	while(ttb_OK == read_next_team())
	{
			//
	}

	display_team_list();

	return ttb_OK;
}
