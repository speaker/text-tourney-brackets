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

/*******************************************************************************
*                                                                              *
* Brackets::Brackets(std::string f ) : Roster(f)                               *
*                                                                              *
* Description:      Constructor for a Brackets                                 *
*                                                                              *
* Inputs:           f		filename given to Roster                           *
*                                                                              *
* Requirements:     f must be a valid filename                                 *
*                                                                              *
* Outputs:          Constructor...                                             *
*                                                                              *
* Effects:          Constructor...                                             *
*                                                                              *
* Notes:				                                                       *
*                                                                              *
********************************************************************************/
Brackets::Brackets(std::string f ) : Roster(f)
{
	depth = (int)std::ceil( log2(team_list.size()));

	start_bracket_tree();
}

/*******************************************************************************
*                                                                              *
* ttb_error_t Brackets::show_bracket()                                         *
*                                                                              *
* Description:      initial routine to output the human readable bracket tree  *
*                                                                              *
* Inputs:           none                                                       *
*                                                                              *
* Requirements:     none                                                       *
*                                                                              *
* Outputs:          none			                                           *
*                                                                              *
* Effects:          standard output is generated                               *
*                                                                              *
* Notes:				                                                       *
* 	Each match will display:                                                   *
*	1) It's left-subordinate match _XOR_ it's left-team if there are none      *
*	2) It's winner or --------- if it's not determined                         *
*	3) It's right-subordinate match _XOR_ it's right-team if there are none    *
*                                                                              *
* The Any match with subordinate matches will have it's team displayed as the  *
* winner of that subordinate match.                                            *
*                                                                              *
********************************************************************************/
ttb_error_t Brackets::show_bracket()
{
	std::cout << std::endl;
	std::cout << "show_bracket" << std::endl;

	_show_bracket(finals,1);

	std::cout << std::endl;
	std::cout << std::endl;
	return ttb_OK;
}

/*******************************************************************************
*                                                                              *
* void tab_out(int cnt)                                                        *
*                                                                              *
* Description:      prints to standard out 2 x cnt tabs                        *
*                                                                              *
* Inputs:           cnt		count used to determine the bumber of two-tabs     *
*                                                                              *
* Requirements:     none                                                       *
*                                                                              *
* Outputs:          none			                                           *
*                                                                              *
* Effects:          standard output is generated                               *
*                                                                              *
* Notes:				                                                       *
*                                                                              *
********************************************************************************/
void tab_out(int cnt)
{
	for(int i = 0 ; i < cnt ; i++) std::cout << "\t\t";
}

/*******************************************************************************
*                                                                              *
* ttb_error_t Brackets::_show_bracket(Match m, int curr_depth)                 *
*                                                                              *
* Description:      Routine to recursively display matches. (See Notes.)       *
*                                                                              *
* Inputs:           m		    Match from which display begins (recursive)    *
* 					curr_depth	Current depth of this Match                    *
*                                                                              *
* Requirements:     The tree must be defined                                   *
*                                                                              *
* Outputs:          ttb_OK			normal completion                          *
*                                                                              *
* Effects:          standard output is generated                               *
*                                                                              *
* Notes:				                                                       *
* 	This method displayed output in a human readable text format. It can be    *
* 	to generate a bracket with only the leaf nodes populated, or one with some *
* 	or all matches complete.                                                   *
*                                                                              *
*TODO: Explain this better.....                                                *
*TODO: Strings should be defined in an external system that allows for L10N &  *
*      I18N as well as sports specific terms                                   *
********************************************************************************/
ttb_error_t Brackets::_show_bracket(Match m, int curr_depth)
{
	// Display all matches to the left, or else the team to the left.
	if(m.match_one_defined())
	{
		_show_bracket(m.match_one(),curr_depth+1);
	}
	else
	{
		tab_out(depth-curr_depth);
		std::cout << m.team_one().last() << std::endl;
	}

	// Display the winner of the finals if there is one
	tab_out(depth-curr_depth+1);

	if(m.get_winner().defined())
	{
		std::cout << m.get_winner().last() << std::endl;
	}
	else
	{
		std::cout << "--------" << std::endl;
	}

	// Display all matches to the right, or else the team to the right.
	if(m.match_two_defined())
	{
		_show_bracket(m.match_two(),curr_depth+1);
	}
	else
	{
		tab_out(depth-curr_depth);
		std::cout << m.team_two().last() << std::endl;
	}

	return ttb_OK;

}

/*******************************************************************************
*                                                                              *
* ttb_error_t Brackets::_display_heats()                                       *
*                                                                              *
* Description:      Routine to recursively display matches. (See Notes.)       *
*                                                                              *
* Inputs:           none                                                       *
*                                                                              *
* Requirements:     The tree must be defined                                   *
*                                                                              *
* Outputs:          ttb_OK			normal completion                          *
*                                                                              *
* Effects:          standard output is generated                               *
*                                                                              *
* Notes:				                                                       *
*                                                                              *
*TODO: Explain this better.....                                                *
*TODO: Strings should be defined in an external system that allows for L10N &  *
*      I18N as well as sports specific terms
********************************************************************************/
ttb_error_t Brackets::display_heats()
{
	int curr_depth = 0;
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

	if(finals.match_one_defined())	_display_heat(finals.match_one(), size()-3 , 1, 0);

	if(finals.match_two_defined())	_display_heat(finals.match_two(), size()-2 , 1, 1);


	return ttb_OK;
}

/*******************************************************************************
*                                                                              *
* int Brackets::calc_left_match_start(int depth_start_count, int curr_depth)   *
*                                                                              *
* Description:      Calculates the value of the first match at this depth      *
*                                                                              *
* Inputs:           depth_start_count	*See Notes                             *
* 					curr_depth          depth in the tree of this match        *
*                                                                              *
* Requirements:     none                                                       *
*                                                                              *
* Outputs:          int			value of the first match at this depth         *
*                                                                              *
* Effects:          none                                                       *
*                                                                              *
* Notes:			The caller is reporting the start point for it's depth.    *
*                   From this 2^(depth of caller-1) is subtracted.             *
*                                                                              *
********************************************************************************/
int Brackets::calc_left_match_start(int depth_start_count, int curr_depth)
{
	int num = depth_start_count-pow(2,curr_depth);

	return num;
}

/*******************************************************************************
*                                                                              *
* ttb_error_t Brackets::_display_heat(	Match m,                               *
* 										int depth_start_count,                 *
* 										int curr_depth,                        *
* 										int bit_mask)                          *
*                                                                              *
* Description:      Routine to recursively display matches. (See Notes.)       *
*                                                                              *
* Inputs:           m                   Match to display                       *
* 					depth_start_count	*See Notes                             *
* 					curr_depth          depth in the tree of this match        *
* 					bit_mask            *See notes                             *
*                                                                              *
* Requirements:     m					must be a valid match                  *
* 					depth_start_count	range 1-depth                          *
* 					curr_depth          range 1-depth                          *
* 					bit_mask            *See notes                             *
*                                                                              *
* Outputs:          ttb_OK			normal completion                          *
*                                                                              *
* Effects:          standard output is generated                               *
*                                                                              *
* Notes:				                                                       *
* 	The output of this routine is one match per line. Each depth level of the  *
* tree can be represented by an equal number of bits. Finals needs 0 bits,     *
* semi-finals needs 1 bit (2 Matches), quarter finals needs 2 bits (4 teams),  *
* and so forth. The position of that match in a tier is the sum of the first   *
* match in the tier and the bit value represented by it's position. (bit_mask) *
* When a subordinate Match is being calculated, the bit_mask is left shifted   *
* with either a 0 (left) or a 1 (right) pushed in. The depth_start_count is    *
* constant for a given tier, so when added to the bit_mask that specific match *
* number is calculated.                                                        *
*                                                                              *
*TODO: Explain this better.....                                                *
*TODO: bit_mask is not a very good name                                        *
********************************************************************************/
ttb_error_t Brackets::_display_heat(Match m, int depth_start_count, int curr_depth, int bit_mask)
{
	int match_number = depth_start_count + bit_mask;

	int left_sub_match_number = calc_left_match_start(depth_start_count,curr_depth+1);

	std::cout << "Match " << match_number << "("<< bit_mask <<"):";

	if(m.team_one().defined())
	{
		std::cout << m.team_one().last() << " vs. ";
	}
	else
	{
		std::cout << "Winner of match " << left_sub_match_number <<" vs. ";
	}

	if(m.team_two().defined())
	{
		std::cout << m.team_two().last() << std::endl;
	}
	else
	{
		std::cout << "Winner of match " << left_sub_match_number+1 << std::endl;
	}

	if(m.match_one_defined()) _display_heat(m.match_one(),left_sub_match_number,curr_depth+1, (0 + (bit_mask <<= 1)) );

	if(m.match_two_defined()) _display_heat(m.match_two(),left_sub_match_number,curr_depth+1, (1 + (bit_mask <<= 1)) );

	return ttb_OK;
}

int Brackets::get_depth()
{
	return depth;
}

/*******************************************************************************
*                                                                              *
* ttb_error_t Brackets::setup_brackets()                                       *
*                                                                              *
* Description:      populates the bracket tree with matches.                   *
*                                                                              *
* Inputs:           none	                                                   *
*                                                                              *
* Requirements:     cur_depth	must be a valid depth of this bracket tree     *
*                                                                              *
* Outputs:          ttb_OK			normal completion                          *
*                                                                              *
* Effects:          tree structure is allocated                                *
*                                                                              *
* Note:				This routines expects the team list is in seed order.      *
* 					Bye teams are expected to be lowest seed and thus placed   *
*                   at the end of the list. The algorithm that populates the   *
*                   tree uses seed order placement, so if there needs to be    *
*                   randomness in the list, it had to be done prior.           *
*                                                                              *
*******************************************************************************/
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

/*******************************************************************************
*                                                                              *
* ttb_error_t Brackets::start_bracket_tree()                                   *
*                                                                              *
* Description:      Creates an empty tree structure.                           *
*                                                                              *
* Inputs:           none	                                                   *
*                                                                              *
* Requirements:     cur_depth	must be a valid depth of this bracket tree     *
*                                                                              *
* Outputs:          ttb_no_roster	No roster exists                           *
*                   ttb_OK			normal completion                          *
*                                                                              *
* Effects:          tree structure is allocated                                *
*                                                                              *
*******************************************************************************/
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

	finals.match_one( build_bracket_node(1) );

	finals.match_two( build_bracket_node(1) );

	return ttb_OK;
}

/*******************************************************************************
*                                                                              *
* Match * Brackets::build_bracket_node(int cur_depth)                          *
*                                                                              *
* Description:      Creates a new instance of a match. When a match is created *
* 					It is created with the subordinate matches attached. When  *
* 					a leaf match would be created, the teams of the requesting *
* 					match are already that match, so none is actually built.   *
*                                                                              *
* Inputs:           cur_depth	the depth the match is being created at        *
*                                                                              *
* Requirements:     cur_depth	must be a valid depth of this bracket tree     *
*                                                                              *
* Outputs:          Match *		new created instance of a Match                *
*                                                                              *
* Effects:          new instance...                                            *
*                                                                              *
*******************************************************************************/
Match * Brackets::build_bracket_node(int cur_depth)
{
	if(cur_depth == depth) return NULL;

	Match * m1 = build_bracket_node(cur_depth+1);
	Match * m2 = build_bracket_node(cur_depth+1);

	return (new Match(m1,m2));
}

// TODO: Need to make this really work
/*******************************************************************************
*                                                                              *
* ttb_error_t Brackets::resolve_by_seed()                                      *
*                                                                              *
* Description:      Plays out the matches                                      *
*                                                                              *
* Inputs:           none                                                       *
*                                                                              *
* Requirements:     Roster should be complete                                  *
*                                                                              *
* Outputs:          ttb_OK	Normal completion                                  *
*                                                                              *
* Effects:          bracket tree is modified                                   *
*                                                                              *
*******************************************************************************/

ttb_error_t Brackets::resolve()
{
	return finals.play_match_by_seed();
}

/*******************************************************************************
*                                                                              *
* ttb_error_t Brackets::resolve_by_seed()                                      *
*                                                                              *
* Description:      Plays out the matches using the seed as the 1st victory    *
* 					condition. "Right wins" if seed doesn't decide.            *
*                                                                              *
* Inputs:           none                                                       *
*                                                                              *
* Requirements:     Roster should be complete                                  *
*                                                                              *
* Outputs:          ttb_OK	Normal completion                                  *
*                                                                              *
* Effects:          bracket tree is modified                                   *
*                                                                              *
*******************************************************************************/
ttb_error_t Brackets::resolve_by_seed()
{
	return finals.play_match_by_seed();
}


