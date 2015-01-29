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
#include "input.h"

class Match
{
public:
	Match(team t1, team t2);
	Match(team t1);

	team get_winner();

	ttb_error_t play_match();

private:
	team winner; // Winner of the match

	team team_one;
	team team_two;

};

class Brackets : public Roster
{
public:
	Brackets(std::string f ) : Roster(f)
	{
		//load_roster(filename);
		// this is a little ugly.
		depth = (int)std::ceil( log2(team_list.size()));

		// TODO: setup_brackets here? Make setup_brackets private?
	};

	ttb_error_t display_heats();

	int get_depth();

	ttb_error_t setup_brackets();

	//static const team bye() { return the_bye; }
	//static const team not_defined() { return team_not_defined; }


private:
	int depth; // The number of levels of the bracket ceiling(log2(num_of_teams))

	team the_bye();

	team team_not_defined();



};


