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

//NOTE: I could have gone with std::pair, but I find its usage pretty awkward.
struct SquareCoordinates
{
    SquareCoordinates(int p_r = 0, int p_c = 0)
        : r(p_r)
        , c(p_c)
    {}

    int r;
    int c;
};

struct Square
{
	enum SquareState
	{
		empty,
		black, 
		white
	};

	SquareState state;
    SquareCoordinates coordinates;

	Square()
        :state(empty)
	{
	}

	Square(SquareCoordinates p_coordinates, SquareState p_state)
	{
        coordinates.r = p_coordinates.r;
        coordinates.c = p_coordinates.c;
		state = p_state;
	}

    Square(int r, int c, SquareState p_state)
    {
        coordinates.r = r;
        coordinates.c = c;
        state = p_state;
    }

    SquareState getState() { return state; }

    void setState(SquareState p_state) { state = p_state; }
};
