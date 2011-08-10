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
 * File: game.h
 * Created on: Aug 2, 2011
 */

#ifndef GAME_H_
#define GAME_H_

#include "RMain.h"

#include <RFrame.h>
#include <REntity.h>
#include <RList.h>

/**
 * This class inherits the main engine class. It's where the game should be programmed.
 */
class Game: public RMain {
public:
	Game();
	virtual ~Game();

	/**
	 * This method initializes the variables and environment. Run once before the game loop.
	 */
	void init();
	/**
	 * This method comes before the rendering phase, where the game logic is made.
	 */
	void logic();
	/**
	 * This method defines how the game graphics should be rendered.
	 */
	void render();
private:
	/**
	 * Camera frame (transformations: rotation, scale etc)
	 */
	REntity camera;

	float camx;
	float camy;

	list<REntity> objList;

	REntity *wheel;
};

#endif /* GAME_H_ */
