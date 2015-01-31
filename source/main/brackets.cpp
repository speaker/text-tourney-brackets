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
* Filename:      brackets.cpp
* Description:   brackets.cpp contains the bracketing source
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

#include "brackets.h"
#include "match.h"
#include <math.h>
#include <cmath>

ttb_error_t Brackets::display_heats()
{
	// TODO: nothing yet
	return ttb_OK;
}

int Brackets::get_depth()
{
	return depth;
}

ttb_error_t Brackets::setup_brackets()
{

	// This is a temp list to hold the teams and the byes used to fill the 1st round
	std::vector<team> bracket_list; // this is a copy of the team_list with byes added

	bracket_list = team_list;

	// Add a number of byes to fill the list
	int add_byes = pow(2,depth) - bracket_list.size();

	for( ; 0 < add_byes ; add_byes-- )
	{
		bracket_list.push_back(make_a_bye());
	}



	// TODO: nothing yet
	return ttb_OK;

}

// This does not populate the brackets, only creates he tree structure

ttb_error_t Brackets::start_bracket_tree()
{

	// There must be a competitor
	if(team_list.size() == 0)
	{
		return ttb_no_roster;
	}

	// The winner is the only team in the bracket
	if(team_list.size() == 1)
	{
		return ttb_OK;
	}

	finals.match_one( build_bracket_node(0) );

	finals.match_two( build_bracket_node(0) );

	return ttb_OK;
}


Match * Brackets::build_bracket_node(int cur_depth)
{
	if(cur_depth == depth) return NULL;

	Match * m1 = build_bracket_node(cur_depth+1);
	Match * m2 = build_bracket_node(cur_depth+1);

	return (new Match(m1,m2));
}


