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
* Filename:      main.cpp
* Description:   main.cpp contains the execuation entry routine
* Notations:
*
* Author:        Adam  Potolsky
*
* Revision History:  Under Revision Control
*
* Public Routines:
*  int  main(int argc , char *argv[] );
*
* Private routines:
*
*******************************************************************************/ 
#include "error.h"
#include "team.h"
#include "roster.h"
#include "brackets.h"
#include <iostream>
#include <string>

// TODO: fill in usage
void usage()
{
	std::cout << "USAGE:" << std::endl;
	std::cout << "  Eventually this will be filled in" << std::endl;

}

int main( int argc , char *argv[])
{
	int cnt = 1; // Start at 1, 0 is the name of the executable

	std::string sTeamFilename;

	while(NULL != argv[cnt])
	{
		std::cout << "DEBUG: cnt:" << cnt << " arg::" << argv[cnt] << std::endl;
		if(argv[cnt][0] == '-')	{
			if(argv[cnt][1] == 'h') {
				usage();
				return 0;
			}
		} else {
			sTeamFilename.assign(argv[cnt]);
		}
		cnt++;
	}

	std::cout << "DEBUG: sTeamFilename:" << sTeamFilename << std::endl;

	Brackets bracket(sTeamFilename);

	std::cout << "DEBUG: number of teams:" << bracket.team_count() << std::endl;

	std::cout << "DEBUG: bracket size:" << bracket.size() << std::endl;

	std::cout << "DEBUG: bracket depth:" << bracket.get_depth() << std::endl;


	return 0;
}
