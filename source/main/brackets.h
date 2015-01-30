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
* Filename:      brackets.h
* Description:   brackets.h contains the definitions for brackets.cpp
* Notations:
*
* Author:        Adam  Potolsky
*
* Revision History:  Under Revision Control
*
* Public Routines:
*
* Private routines:
*
*******************************************************************************/ 

#include <math.h>
#include <cmath>
#include "team.h"
#include "roster.h"
#include "match.h"

class Brackets : public Roster
{
public:
	Brackets(std::string f ) : Roster(f)
	{
		depth = (int)std::ceil( log2(team_list.size()));

		start_bracket_tree();
	};

	ttb_error_t display_heats();

	int get_depth();

	ttb_error_t setup_brackets();

	int team_count() { return team_list.size(); }


private:
	int depth; // The number of levels of the bracket ceiling(log2(num_of_teams))

	team the_bye();

	team team_not_defined();

	Match finals;

	Match * build_bracket_node(int cur_depth);

	ttb_error_t start_bracket_tree();

};


