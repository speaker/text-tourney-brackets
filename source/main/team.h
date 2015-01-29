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
* Filename:      team.h
* Description:   team.h contains the definitions for team.cpp
* Notations:
*
* Author:        Adam Potolsky
*
* Revision History:  Under Revision Control
*
* Public Routines:
*  int  load_teams(std::string filename);
*
* Private routines:
*
*******************************************************************************/ 
#include <vector>
#include <iostream>
#include <fstream>
#include "error.h"


class team
{
public:
	team(std::string, std::string, std::string, std::string, int);
	team(const char *, const char *, const char *, const char *, int);
	team();

		std::string id() const				{ return team_id; }
		const std::string last() const		{ return team_last; }
		const std::string first() const		{ return team_first; }
		const std::string residence() const	{ return team_residence; }
		const int seed() const				{ return team_seed; }

		ttb_error_t id(std::string str) { team_id = str; return ttb_OK; }
		ttb_error_t last(std::string str) { team_last = str; return ttb_OK; }
		ttb_error_t first(std::string str) { team_first = str; return ttb_OK; }
		ttb_error_t residence(std::string str) { team_residence = str; return ttb_OK; }
		ttb_error_t seed(int i) { team_seed = i; return ttb_OK;}

		bool operator==(const team& A);

		bool defined() { if(team_id == "!NDEF") return false; return true; }

		bool a_bye() { if(team_id == "!BYE") return true; return false; }

private:
	std::string team_id;
	std::string team_last;
	std::string team_first;
	std::string team_residence;
	int team_seed;
};
