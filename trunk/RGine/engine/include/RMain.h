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
 * File: RMain.h
 * Created on: Aug 5, 2011
 */

#ifndef RMAIN_H_
#define RMAIN_H_

#include "RSDL.h"

#include <RVector.h>
#include <REntity.h>
#include <RPhysics.h>


/**
 * Main engine class. This will handle events, the main loop, logic and
 * rendering. This class should be inherited to build the main application
 * class.
 */
class RMain {
public:
	RMain();
	virtual ~RMain();

	/**
	 * Run the main application loop.
	 *
	 * @return Will return 0 if no error is found during execution.
	 */
	int run();

	vector<REntity> entityList;
protected:
	/**
	 * Gets the mouse structure.
	 *
	 * @return The mouse structure.
	 */
	RSDLMouseStruct mouse();
	/**
	 * Gets a specific key (by SDLK_(key) id).
	 *
	 * @param id The identifier of the key.
	 * @return The key structure.
	 */
	RSDLKeyStruct key(int id);

	REntity* newEntity();
public:
	/**
	 * SDL object.
	 */
	RSDL sdl;

	RPhysics *phy;

private:

	virtual void render();
	virtual void init()=0;
	virtual void logic()=0;
};

#endif /* RMAIN_H_ */
