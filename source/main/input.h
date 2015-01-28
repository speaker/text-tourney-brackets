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
* Filename:      input.h
* Description:   input.h contains the definitions for input.cpp
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


typedef struct one_team_entry {
	std::string id;
	std::string last;
	std::string first;
	std::string residence;
	int seed;
} team;


class ttb_Roster
{
public:
	std::vector<team> team_list;

	ttb_error_t display_team_list();
	ttb_error_t add_team(team t);
	ttb_error_t read_next_team();
	ttb_error_t setup_brackets();
	ttb_error_t load_teams(std::string filename);

private:
	std::ifstream file;
};
