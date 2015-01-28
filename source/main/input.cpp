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
* Filename:      input.cpp
* Description:   input.cpp contains the execuation entry routine
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

#include "input.h"

//
// This routine will read in the next line with valid data for the roster
//
ttb_error_t ttb_Roster::read_next_team()
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

	team t;

	std::string seed_str = "";

	getline(sstream, t.id, ',' );
	getline(sstream, t.last, ',' );
	getline(sstream, t.first, ',' );
	getline(sstream, t.residence, ',' );

	getline(sstream, seed_str, ',' );

	//std::cout << "DEBUG: seed_str:" << seed_str << std::endl;

	if( "" == seed_str ) {
		t.seed = 0;
	} else {
		std::stringstream( seed_str ) >> t.seed;
	}

	//std::cout << "DEBUG: t.seed:" << seed_str << std::endl;

	add_team(t);

	return ttb_OK;
}


ttb_error_t ttb_Roster::display_team_list()
{
	std::cout << "\n\t\tTeam List Dump:" << std::endl;


	std::vector<team>::const_iterator i = team_list.begin();

	for( ; i != team_list.end() ; i++)
	{
		std::cout << i->id << ": ";
		std::cout << i->last << ", ";
		std::cout << i->first << ", From: ";
		std::cout << i->residence << ", Seed:";
		std::cout << i->seed << std::endl;
	}

	std::cout << "\t\tEnd of List" << std::endl;

	return ttb_OK;
}

ttb_error_t ttb_Roster::add_team(team t)
{
	// nothing for now
	team_list.push_back(t);
	return ttb_OK;
}

ttb_error_t ttb_Roster::setup_brackets()
{
	// nothing for now
	return ttb_OK;
}


ttb_error_t ttb_Roster::load_teams(std::string filename)
{
	file.open(filename.c_str(),std::ios::in);

	if( ! file.is_open()) {
		std::cerr << "There was an error opening file:" << filename << std::endl;
		return ttb_unknown;
	}

	std::cout << "Filename:" << filename << std::endl;

	team nt;

	while(ttb_OK == read_next_team())
	{
			//
	}

	display_team_list();

	return ttb_OK;
}
