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
 * File: RMain.cpp
 * Created on: Aug 5, 2011
 */

#include "RMain.h"

RMain::RMain() {
	phy = new RPhysics(this);
	phy->setGravity(9.8);
}

RMain::~RMain() {
	delete phy;
}

int RMain::run() {
	sdl.init();
	sdl.timer_init();
	sdl.timer_start();
	init();
	while (!sdl.finished()) {
		sdl.input();
		logic();
		phy->updatePhysics();
		sdl.render_begin();
		render();
		sdl.render_end();
		sdl.timer_delay();
	}
	SDL_Quit();
	return (0);
}

RSDLMouseStruct RMain::mouse() {
	return (sdl.mouse());
}

RSDLKeyStruct RMain::key(int id) {
	return (sdl.key(id));
}

#include <RGLText.h>

void RMain::render() {
}
