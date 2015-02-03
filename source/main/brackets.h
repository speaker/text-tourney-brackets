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
	Brackets(std::string);

	ttb_error_t setup_brackets();	// Builds empty bracket tree

	ttb_error_t show_bracket();		// displays "pretty" match tree
	ttb_error_t display_heats();	// dumps the matches
	int get_depth();				// returns the # of bracket levels

	// number of matches in complete tree
	int size() { return pow(2,depth); }

	// returns the number of real teams in the bracket (no byes)
	int team_count() { return team_list.size(); }


private:
	int depth;					// The number of levels of the bracket
	Match finals;				// Head of the tree

	team the_bye();				// returns true is this is a bye
	team team_not_defined();	// returns frue if the team isn't defined

	// See function Header
	int calc_left_match_start(int , int );

	// workhorse routine to display the matches in the tree
	ttb_error_t _display_heat( Match , int, int, int);

	// workhorse routine to disply the bracket in a pretty way
	ttb_error_t _show_bracket(Match,int);

	// Routine that kicks off the building of the bracket tree
	ttb_error_t start_bracket_tree();

	// workhorse routine to build the bracket tree
	Match * build_bracket_node(int cur_depth);

};


