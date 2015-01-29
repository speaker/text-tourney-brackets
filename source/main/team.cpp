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
* Filename:      team.cpp
* Description:   team.cpp contains the execuation entry routine
* Notations:
*
* Author:        Adam  Potolsky
*
* Revision History:  Under Revision Control
*
* Public Routines:
*  int  load_teams(std::string filename);
*
* Private routines:
*
*******************************************************************************/ 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "team.h"

bool team::operator==(const team& A)
{
	if( id() == A.id() ) return true;

	return false;
}

team::team(std::string _id, std::string _last, std::string _first, std::string _res, int _seed)
{
	team_id			= _id;
	team_last		= _last;
	team_first		= _first;
	team_residence	= _res;
	team_seed		= _seed;
}

team::team(const char * _id, const char * _last, const char * _first, const char * _res, int _seed)
{
	team_id			= _id;
	team_last		= _last;
	team_first		= _first;
	team_residence	= _res;
	team_seed 		= _seed;
}

team::team()
{
	team_id			= "!NDEF";
	team_last		= "!NDEF";
	team_first		= "!NDEF";
	team_residence	= "!NDEF";
	team_seed		= -2;
}
