/**
 * @file
 * @author Ricardo Bustamante de Queiroz <ricardobqueiroz@gmail.com>
 * @version
 *
 * @section LICENSE
 *
 * This file is part of RGine.
 *
 * RGine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RGine.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * Created on: Jul 14, 2011
 * File: main.cpp
 *
 * Copyright 2009,2010,2011 Ricardo Bustamante de Queiroz
 */

#include "Game.h"

#include <iostream>
using namespace std;

/**
 *
 * Program's main function. Will create a Game Object and run it and return it's result.
 */
int main(int argc, char *argv[]) {
	Game a;
	return (a.run());
}
