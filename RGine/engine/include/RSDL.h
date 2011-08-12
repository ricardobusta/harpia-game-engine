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
 * File: RSDL.h
 * Created on: Aug 5, 2011
 *
 * The timer functions were based on Lazy Foo' tutorials, where I learned
 * most of what I know about SDL.
 * http://lazyfoo.net/SDL_tutorials/index.php
 */

#ifndef RSDL_H_
#define RSDL_H_

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include <list>
using namespace std;

#include <RPoint2i.h>

/**
 * This structure will keep track of every key or button state.
 */
struct RSDLKeyStruct {
	/**
	 * If the key was lifted during that frame this will be true.
	 */
	bool up;
	/**
	 * If the key was pressed during that frame this will be true.
	 */
	bool down; //Key was pressed during that frame
	/**
	 * If the key is down this will be true (pressed)
	 */
	bool isDown; //Key is down
	/**
	 * this struct will keep track on the key states.
	 */
	RSDLKeyStruct() {
		up = false;
		down = false;
		isDown = false;
	}
};

/**
 * This structure will keep track of the mouse state. Including buttons states
 * and speed, position etc.
 */
struct RSDLMouseStruct {
	/**
	 * Left mouse button state.
	 */
	RSDLKeyStruct left;
	/**
	 * Right mouse button state.
	 */
	RSDLKeyStruct right;
	/**
	 * Middle mouse button state.
	 */
	RSDLKeyStruct middle;
	/**
	 * Mousewheel UP button state.
	 */
	RSDLKeyStruct wheelup;
	/**
	 * Mousewheel DOWN button state.
	 */
	RSDLKeyStruct wheeldown;
	/**
	 * Mouse current position on screen. Being (0,0) left top corner.
	 */
	RPoint2i position;
	/**
	 * Mouse current speed on move.
	 */
	RPoint2i speed;
	/**
	 * Mousewheel speed.
	 */
	RPoint2i wheelspeed;
};

/**
 * Class that will make direct access to the sdl commands and make it available
 * to the rest of the application.
 */
class RSDL {
private:
	friend class RMain;
	//Screen
	int width;
	int height;
	int bpp;

	//Control
	SDL_Event event;
	bool quit;

	//OpenGL
	bool opengl_init();
	void opengl_resize();

	//Keyboard
	RSDLKeyStruct key_[SDLK_LAST];
	list<int> key_mod;
	void key_reset();

	//Mouse
	RSDLMouseStruct mouse_;
	void mouse_reset();

	//Timer
	bool timer_started;
	int timer_startTicks;
	bool timer_paused;
	int timer_pausedTicks;
	int timer_currentTick;
	int fps;


	//Timer
	void timer_init();
	void timer_start();
	void timer_stop();
	void timer_pause();
	void timer_unpause();
	void timer_delay();
	int timer_getTicks();

public:
	RSDL();
	virtual ~RSDL();

	/**
	 * Will init SDL subsystems.
	 *
	 * @return True if everything went ok.
	 */
	bool init();

	/**
	 * Will end SDL subsystems.
	 *
	 * @return True if everything went ok.
	 */
	bool end();

	/**
	 * Will warn if the main loop was finished by the application.
	 *
	 * @return True if the main loop is finished.
	 */
	bool finished();

	/**
	 * Will track all key and mouse input.
	 */
	void input();

	/**
	 * Prepare the main loop for render.
	 */
	void render_begin();

	/**
	 * Complete the render phase by finishing it.
	 */
	void render_end();

	/**
	 * Mouse structure.
	 *
	 * @return will return the mouse structure.
	 */
	RSDLMouseStruct mouse();

	/**
	 * Key structure. Will return a specific key given it's ID (SDLK_*id*).
	 * @param id Key ID. (SDLK_*id*).
	 * @return The wanted key structure.
	 */
	RSDLKeyStruct key(int id);

	/**
	 * Get the SDL screen width.
	 * @return Screen width.
	 */
	int getWidth();

	/**
	 * Get the SDL screen height.
	 * @return Screen height.
	 */
	int getHeight();

	int timer_getCurrentTick(); //TODO put on private somehow?
};

#endif /* RSDL_H_ */
