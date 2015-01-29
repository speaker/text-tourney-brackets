#pragma once

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
* Filename:      roster.h
* Description:   roster.h contains the definitions for roster.cpp
* Notations:
*
* Author:        Adam Potolsky
*
* Revision History:  Under Revision Control
*
* Public Routines:
*  int  load_teams(std::string filename);
*
* Private routines:
*
*******************************************************************************/ 
#include <vector>
#include <iostream>
#include <fstream>
#include "error.h"
#include "team.h"


class Roster
{
public:
	Roster();

	Roster(std::string filename);

	// NOTE: team_list contains the real teams in the bracket. It must not include bye-teams.
	// The bye-teams are added when the brackets are built.

	std::vector<team> team_list;

	ttb_error_t display_team_list();
	ttb_error_t add_team(team t);
	ttb_error_t read_next_team();
	ttb_error_t setup_brackets();
	ttb_error_t load_roster(std::string filename);

	int size() { return team_list.size(); }

protected:
		ttb_error_t load_teams(std::string filename); // TODO: necessary with constructor?

private:
	std::ifstream file;


};
