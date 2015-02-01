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
#include <string>

// This first displays the finals then calls a recursive routine to output the rest of the bracket
ttb_error_t Brackets::display_heats()
{
	int curr_depth = 0;
	// TODO: Strings should be defined in an external system that allows for L10N and I18N as well as sports specific terms
	if(finals.get_winner().defined())
	{
		std::cout << "1st: " << finals.get_winner().last() << ", " << finals.get_winner().first() << std::endl;
		std::cout << "2nd: " << finals.get_loser().last() << ", " << finals.get_loser().first() << std::endl; //TODO: handle bye

		if(finals.match_one_defined())
		{
			std::cout << "3rd: " << finals.match_one().get_loser().last() << ", " << finals.match_one().get_loser().first() << std::endl;
		}
		if(finals.match_two_defined())
		{
			std::cout << "3rd: " << finals.match_two().get_loser().last() << ", " << finals.match_two().get_loser().first() << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Full Bracket results:" << std::endl;
	}

	// Note: The match numbers are easy for the finals. The rest of the matches, not so much

	std::cout << "Match " << ( size()-1 ) << ":";

	if(finals.match_one().get_winner().defined())
	{
		std::cout << finals.match_one().get_winner().last() << " vs. ";
	}
	else
	{
		std::cout << "Winner of match " << ( size()-3 ) <<" vs. ";
	}

	if(finals.match_two().get_winner().defined())
	{
		std::cout << finals.match_two().get_winner().last() << " vs. ";
	}
	else
	{
		std::cout << "Winner of match " << ( size()-2 ) << std::endl;
	}

	// The 3rd argument to display heat is the depth of that match. This is needed so it can predict
	// the match numbers it will call.

	if(finals.match_one_defined())	display_heat(finals.match_one(), size()-3 , 2, 0);

	if(finals.match_two_defined())	display_heat(finals.match_two(), size()-2 , 2, 1);


	return ttb_OK;
}

//TODO: bit_mask is not a very good name

ttb_error_t Brackets::display_heat(Match m, int match_number, int depth, int bit_mask)
{
	std::cout << "Match " << match_number << ":";

	if(m.team_one().defined())
	{
		std::cout << m.team_one().last() << " vs. ";
	}
	else
	{
		std::cout << "Winner of match " << ( size()-3 ) <<" vs. ";
	}

	if(m.team_two().defined())
	{
		std::cout << m.team_two().last() << std::endl;
	}
	else
	{
		std::cout << "Winner of match " << ( size()-2 ) << std::endl;
	}



	if(m.match_one().get_winner().defined())
	{
		std::cout << m.match_one().get_winner().last() << ", " << m.get_winner().first() << std::endl;
		std::cout << " vs. ";
	}
	else
	if(m.match_two().match_two().get_winner().defined())
	{
		std::cout << m.get_winner().last() << ", " << m.get_winner().first() << std::endl;
		std::cout << " vs. ";
	}

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
	int add_byes = size() - bracket_list.size();

	for( ; 0 < add_byes ; add_byes-- )
	{
		bracket_list.push_back(make_a_bye());
	}

	std::vector<team>::const_iterator i = bracket_list.begin();

	for( ; i != bracket_list.end() ; i++)
	{
		std::cout << "DEBUG ADDING: " << i->to_str() << std::endl;

		finals.add_team(*i);
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


