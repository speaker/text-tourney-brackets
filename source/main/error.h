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
* Filename:      error.h
*
* Description:   error.h contains definitions for routines that use error.cpp
*
* Notations:
*
* Author:        Adam Potolsky
*
* Revision History:  Under Revision Control
*
* Public Routines:
*
* Private routines:
*
*******************************************************************************/ 
#include <iostream>

typedef enum ttb_error_codes {
	ttb_unknown = -1,
	ttb_OK = 0,
	ttb_EOF = 10,
	ttb_no_roster = 20,
	ttb_match_full = 30,


	// Do not add error codes below this entry
	ttb_last_error_code

} ttb_error_t;
