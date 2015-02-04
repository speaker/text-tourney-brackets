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

/*******************************************************************************
*                                                                              *
* Class team                                                                   *
*                                                                              *
* Description:      Class that defines a team and it's components              *
*                                                                              *
* Requirements:     none                                                       *
*                                                                              *
*******************************************************************************/
class team
{
public:
	team(std::string, std::string, std::string, std::string, int);
	team(const char *, const char *, const char *, const char *, int);
	team();

	const std::string id() const		{ return _id; }
	const std::string last() const		{ return _last; }
	const std::string first() const		{ return _first; }
	const std::string residence() const	{ return _nationality; }
	const int seed() const				{ return _seed; }

	ttb_error_t id(std::string str)		{ _id = str; return ttb_OK; }
	ttb_error_t last(std::string str)	{ _last = str; return ttb_OK; }
	ttb_error_t first(std::string str)	{ _first = str; return ttb_OK; }
	ttb_error_t nation(std::string str)	{ _nationality = str; return ttb_OK; }
	ttb_error_t seed(int i)				{ _seed = i; return ttb_OK;}

	const std::string to_str() const;

	bool operator==(const team& A);

	bool defined() { if(_id == "!NDEF") return false; return true; }

	bool a_bye() { if(_id == "!BYE") return true; return false; }

private:
	std::string _id;
	std::string _last;
	std::string _first;
	std::string _nationality;
	int _seed;
};
