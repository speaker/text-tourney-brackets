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

Match::Match(team t1, team t2)
{
	// winner is constructed as "not defined"
	team_one = t1;
	team_two = t2;
}

team Match::get_winner()
{
	if(winner.defined()) return winner;

	play_match();

	return winner;
}

// TODO: This is presently a bogus play. it is only intended to return something.
ttb_error_t Match::play_match()
{
	if(team_two.a_bye() == true) // This is ok, bye always looses
	{
		winner = team_one;
	}
	else if(team_one.seed() <= team_two.seed())
	{
		winner = team_one;
	}
	else
	{
		winner = team_two;
	}

	return ttb_OK;
}

