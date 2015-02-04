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
* Filename:      match.h
* Description:   match.h contains the definitions for match.cpp
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
#include <bitset>
#include "team.h"
#include "roster.h"

/*******************************************************************************
*                                                                              *
* Class Match                                                                  *
*                                                                              *
* Description:      Class that defines a match and it's components             *
*                                                                              *
* Requirements:     Uses: Class team                                           *
*                                                                              *
*******************************************************************************/

class Match
{
public:
	Match(Match * m1, Match * m2);
	Match(team t1, team t2);
	Match(team t1);
	Match();

	ttb_error_t play_match();
	ttb_error_t play_match_by_seed();
	ttb_error_t	match_one(Match * m) { match_1=m; return ttb_OK; }
	ttb_error_t	match_two(Match * m) { match_2=m; return ttb_OK; }
	ttb_error_t add_team(team);
	Match match_one() { return *match_1; }
	Match match_two() { return *match_2; }
	bool match_one_defined();
	bool match_two_defined();
	team team_one() { return team_1; }
	team team_two() { return team_2; }
	team get_winner()	{ return winner; }
	team get_loser()	{ return loser; }
	bool defined();


private:
	// TODO: Should a match really understand the structure of the bracket other than 2 teams?
	std::bitset<2> left_or_right;
	bool go_left();
	team winner;
	team loser;
	team team_1;
	team team_2;
	Match * match_1;
	Match * match_2;
};
