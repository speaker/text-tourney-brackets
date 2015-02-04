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
* Filename:      match.cpp
* Description:   match.cpp contains the match source
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

/*******************************************************************************
*                                                                              *
* Match::Match(team t1, team t2)                                               *
*                                                                              *
* Description:      Constructor that builds a Match given 2 teams              *
*                                                                              *
* Inputs:           t1	"left" team of new match                               *
* 					t2	"right" team of new match                              *
*                                                                              *
* Requirements:     N/A                                                        *
*                                                                              *
* Outputs:          a Match is created                                         *
*                                                                              *
* Effects:          N/A                                                        *
*                                                                              *
*******************************************************************************/
Match::Match(team t1, team t2)
{
	winner = team();
	loser = team();
	left_or_right = 0;
	team_1 = t1;
	team_2 = t2;
	match_1 = NULL;
	match_2 = NULL;
}

/*******************************************************************************
*                                                                              *
* Match::Match()                                                               *
*                                                                              *
* Description:      Constructor default                                        *
*                                                                              *
* Inputs:           t1	"left" team of new match                               *
* 					t2	"right" team of new match                              *
*                                                                              *
* Requirements:     N/A                                                        *
*                                                                              *
* Outputs:          a Match is created with not defined teams                  *
*                                                                              *
* Effects:          N/A                                                        *
*                                                                              *
*******************************************************************************/
Match::Match()
{
	winner = team();
	loser = team();
	left_or_right = 0;
	match_1 = NULL;
	match_2 = NULL;
}

/*******************************************************************************
*                                                                              *
* Match::Match(Match * m1, Match * m2)                                         *
*                                                                              *
* Description:      Constructor that builds a Match given 2 matches            *
*                                                                              *
* Inputs:           m1	"left" match                                           *
* 					m2	"right" match                                          *
*                                                                              *
* Requirements:     Matches must be valid or NULL                              *
*                                                                              *
* Outputs:          a Match is created                                         *
*                                                                              *
* Effects:          N/A                                                        *
*                                                                              *
*******************************************************************************/
Match::Match(Match * m1, Match * m2)
{
	winner = team();
	loser = team();
	left_or_right = 0;
	match_1 = m1;
	match_2 = m2;
}

/*******************************************************************************
*                                                                              *
* bool Match::go_left()                                                        *
*                                                                              *
* Description:      method that determines whether the next object should go   *
*                   down the left branch or right. The Pattern is LRRLLRRL     *
*                                                                              *
* Inputs:           N/A                                                        *
*                                                                              *
* Requirements:     N/A                                                        *
*                                                                              *
* Outputs:          bool	true on left                                       *
*                                                                              *
* Effects:          N/A                                                        *
*                                                                              *
*******************************************************************************/
bool Match::go_left()
{
	if( left_or_right[0] == left_or_right[1] ) return true;
	return false;
}

/*******************************************************************************
*                                                                              *
* ttb_error_t Match::add_team(team t)                                          *
*                                                                              *
* Description:      method to add a team to this bracket reference. Recursion  *
* is used to climb down the branches as appropriate. If all sub-matches are    *
* full, then add the team to this match.                                       *
*                                                                              *
* Inputs:           t  team to add to this structure                           *
*                                                                              *
* Requirements:     t must be a valid team                                     *
*                                                                              *
* Outputs:          ttb_OK	        normal completion                          *
*                   ttb_match_full  this and all bub-matches are full          *
*                                                                              *
* Effects:          contents of the match tree is modified                     *
*                                                                              *
* Notes:                                                                       *
*                                                                              *
* Bracket trees are complete. They always have a full set of matches even if   *
* every competitor has a bye except 2. For this reason, it is safe to assume   *
* If there is one match there are 2.                                           *
* If there are no matches, populate myself                                     *
* If there are subordinate matches, pass the team to the correct one of them.  *
* Once the subordinate matches are full, this one shoudl populate itself.      *
* When full, it should return ttb_match_full                                   *
*                                                                              *
*******************************************************************************/
ttb_error_t Match::add_team(team t)
{
	// If both teams are defined, the match is full.
	if(team_1.defined() && team_2.defined()) return ttb_match_full;

	// No match means populate this match.
	if(NULL == match_1)
	{
		if( true == go_left())
		{
			team_1 = t;
		}
		else
		{
			team_2 = t;
		}
		left_or_right = left_or_right.to_ulong() + 1; // TODO: This is a kludge

		return ttb_OK;
	}

	// Need to load the match beneath us

	if( true == go_left())
	{
		match_1->add_team(t);
	}
	else
	{
		match_2->add_team(t);
	}
	left_or_right = left_or_right.to_ulong() + 1;

	return ttb_OK;

}

/*******************************************************************************
*                                                                              *
* bool Match::defined()                                                        *
*                                                                              *
* Description:      method to play out the matches using the seed as the       *
*                   victory condition                                          *
*                                                                              *
* Inputs:           N/A                                                        *
*                                                                              *
* Requirements:     Bracket Tree must be set up                                *
*                                                                              *
* Outputs:          ttb_OK	        normal completion                          *
*                   ttb_match_full  this and all bub-matches are full          *
*                                                                              *
* Effects:          contents of the match tree is modified                     *
*                                                                              *
* Notes:                                                                       *
*                                                                              *
* If a seed cannot resolve the match, the "right" team wins                    *
*                                                                              *
*******************************************************************************/
ttb_error_t Match::play_match_by_seed()
{
	if(false == team_1.defined())
	{
		match_1->play_match_by_seed();
		team_1 = match_1->winner;
	}

	if(false == team_2.defined())
	{
		match_2->play_match_by_seed();
		team_2 = match_2->winner;
	}

	if(team_2.a_bye() == true) // This is ok, bye always looses
	{
		winner = team_1;
	}
	else if(team_1.seed() <= team_2.seed()) //TODO: Some way to solve a match
	{
		winner = team_1;
		loser = team_2;
	}
	else
	{
		winner = team_2;
		loser = team_1;
	}

	return ttb_OK;
}


/*******************************************************************************
*                                                                              *
* bool Match::defined()                                                        *
*                                                                              *
* Description:      method to determine if this match has been defined         *
*                                                                              *
* Inputs:           t  team to add to this structure                           *
*                                                                              *
* Requirements:     t must be a valid team                                     *
*                                                                              *
* Outputs:          true	        team is defined                            *
*                   false           team is not defined                        *
*                                                                              *
* Effects:          contents of the match tree is modified                     *
*                                                                              *
* Notes:                                                                       *
*                                                                              *
* if there is a team or match in _1_ and a team or match in _2_ than it's      *
* defined otherwise it's not defined or partially defined. This routine treats *
* either as not defined                                                        *
*                                                                              *
*******************************************************************************/
bool Match::defined()
{
	// if there is a team or match in _1_ and a team or match in _2_ than it's defined otherwise it's not defined or partially defined. This routine treats either as not defined

	if( (team_1.defined() || (NULL != match_1) ) && (team_2.defined() || (NULL != match_2) ) )
	{
		return true;
	}
	return false;
}

/*******************************************************************************
*                                                                              *
* bool Match::match_one_defined()                                              *
*                                                                              *
* Description:      Returns whether or not match_1 has been defined            *
*                                                                              *
* Inputs:           N/A                                                        *
*                                                                              *
* Requirements:     N/A                                                        *
*                                                                              *
* Outputs:          true	        Match_1 is defined                         *
*                   false           Match_1 is not defined                     *
*                                                                              *
* Effects:          none                                                       *
*                                                                              *
* Notes:                                                                       *
*                                                                              *
* Does not test validity of the match                                          *
*                                                                              *
*******************************************************************************/
bool Match::match_one_defined()
{
	if(NULL == match_1)
	{
		return false;
	}
	return true;
}

/*******************************************************************************
*                                                                              *
* bool Match::match_two_defined()                                              *
*                                                                              *
* Description:      Returns whether or not match_2 has been defined            *
*                                                                              *
* Inputs:           N/A                                                        *
*                                                                              *
* Requirements:     N/A                                                        *
*                                                                              *
* Outputs:          true	        Match_2 is defined                         *
*                   false           Match_2 is not defined                     *
*                                                                              *
* Effects:          none                                                       *
*                                                                              *
* Notes:                                                                       *
*                                                                              *
* Does not test validity of the match                                          *
*                                                                              *
*******************************************************************************/
bool Match::match_two_defined()
{
	if(NULL == match_2)
	{
		return false;
	}
	return true;
}
