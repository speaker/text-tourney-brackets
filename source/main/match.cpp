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


// A match is comprised of 2 teams, one of which becomes a winner.
Match::Match(team t1, team t2)
{
	left_or_right = 0;
	// winner is constructed as "not defined"
	team_1 = t1;
	team_2 = t2;

	match_1 = NULL;
	match_2 = NULL;
}

// A match is comprised of 2 teams, one of which becomes a winner.
Match::Match()
{
	left_or_right = 0;

	// winner is constructed as "not defined"

	match_1 = NULL;
	match_2 = NULL;
}

Match::Match(Match * m1, Match * m2)
{
	left_or_right = 0;

	// winner is constructed as "not defined"
	match_1 = m1;
	match_2 = m2;
}

bool Match::go_left()
{
	if( left_or_right[0] == left_or_right[1] ) return true;
	return false;
}

// Bracket trees are complete. They always have a full set of matches even if
// every competitor has a bye except 2. For this reason, it is safe to assume
// If there is one match there are 2.
// If there are no matches, populate myself
// If there are subordinate matches, pass the team to the correct one of them.
// Once the subordinate matches are full, this one shoudl populate itself.
// When full, it should return ttb_match_full

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

team Match::get_winner()
{
	if(winner.defined()) return winner;

	play_match();

	return winner;
}

ttb_error_t	Match::match_one(Match * m)
{
	match_1 = m;
	return ttb_OK;
}

ttb_error_t	Match::match_two(Match * m)
{
	match_2 = m;
	return ttb_OK;
}


// TODO: This is presently a bogus play. it is only intended to return something.
ttb_error_t Match::play_match()
{
	if(false == team_1.defined())
	{
		match_1->play_match();
		team_1 = match_1->winner;
	}

	if(false == team_2.defined())
	{
		match_2->play_match();
		team_2 = match_2->winner;
	}

	if(team_2.a_bye() == true) // This is ok, bye always looses
	{
		winner = team_1;
	}
	else if(team_1.seed() <= team_2.seed()) //TODO: Some way to solve a match
	{
		winner = team_1;
	}
	else
	{
		winner = team_2;
	}

	return ttb_OK;
}
