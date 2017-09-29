/*
==============================================================================
Reversi!

Copyright (C) 2017  BMP4

Developer: Vincent Berthiaume

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
==============================================================================
*/

#pragma once
#include <utility>

struct Square
{
	enum SquareState
	{
		empty,
		black, 
		white
	};

	SquareState state;
	int x;
	int y;

	Square()
	{
		state = empty;
		x = 0;
		y = 0;
	}

	Square(int p_x, int p_y, SquareState p_state)
	{
		x = p_x;
		y = p_y;
		state = p_state;
	}
};
