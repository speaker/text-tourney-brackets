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
/*******************************************************************************
*                                                                              *
* Constructor team::team(	std::string id                                     *
* 							std::string last,                                  *
* 							std::string first,                                 *
* 							std::string res,                                   *
* 							int seed)                                          *
*                                                                              *
* Description:      constructs a team with the given data                      *
*                                                                              *
* Inputs:           string	id		The ID to use for this team                *
* 					string	last	Last name of team                          *
* 					string	first	First name of team                         *
* 					string	res		Country of residency                       *
* 					int		seed	the seed or ranking of this team           *
*                                                                              *
* Requirements:     Inputs must be valid                                       *
*                                                                              *
* Outputs:          New instance of a team is allocated                        *
*                                                                              *
* Effects:          Constructor...                                             *
*                                                                              *
*******************************************************************************/
team::team(std::string id, std::string last, std::string first, std::string res, int seed)
{
	_id				= id;
	_last			= last;
	_first			= first;
	_nationality	= res;
	_seed			= seed;
}

/*******************************************************************************
*                                                                              *
* Constructor team::team(	char *  id                                         *
* 							char * last,                                       *
* 							char * first,                                      *
* 							char * res,                                        *
* 							int seed)                                          *
*                                                                              *
* Description:      constructs a team with the given data                      *
*                                                                              *
* Inputs:           char *	id		The ID to use for this team                *
* 					char *	last	Last name of team                          *
* 					char *	first	First name of team                         *
* 					char *	res		Country of residency                       *
* 					int		seed	the seed or ranking of this team           *
*                                                                              *
* Requirements:     Inputs must be valid                                       *
*                                                                              *
* Outputs:          New instance of a team is allocated                        *
*                                                                              *
* Effects:          Constructor...                                             *
*                                                                              *
*******************************************************************************/
team::team(const char * id, const char * last, const char * first, const char * res, int seed)
{
	_id				= id;
	_last			= last;
	_first			= first;
	_nationality	= res;
	_seed 			= seed;
}

/*******************************************************************************
*                                                                              *
* Constructor team::team()                                                     *
*                                                                              *
* Description:      constructs a team that is "not defined"                    *
*                                                                              *
* Inputs:           none                                                       *
*                                                                              *
* Requirements:     none                                                       *
*                                                                              *
* Outputs:          New instance of a team is allocated                        *
*                                                                              *
* Effects:          Constructor...                                             *
*                                                                              *
*******************************************************************************/
team::team()
{
	_id				= "!NDEF";
	_last			= "!NDEF";
	_first			= "!NDEF";
	_nationality	= "!NDEF";
	_seed			= -2;
}

/*******************************************************************************
*                                                                              *
* const std::string team::to_str() const                                       *
*                                                                              *
* Description:      builds a string to represent the team data                 *
*                                                                              *
* Inputs:           none                                                       *
*                                                                              *
* Requirements:     none                                                       *
*                                                                              *
* Outputs:          string const                                               *
*                                                                              *
* Effects:          none                                                       *
*                                                                              *
*******************************************************************************/
const std::string team::to_str() const
{
	std::string str("ID:");
	str.append(id());
	str.append(" Last:");
	str.append(last());
	str.append(" First:");
	str.append(first());
	str.append(" Res:");
	str.append(residence());

	std::ostringstream tmp;
	tmp << seed();
	std::string seed_str(tmp.str());

	str.append(" Seed:");
	str.append(seed_str);

	return str;
}
