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
 * File: RGLCommands.cpp
 * Created on: Aug 5, 2011
 */

#include "RGLCommands.h"

#include <SDL/SDL_opengl.h>

void rglSetMatrix(RMatrix4f rMatrix4f)
{
	glLoadMatrixf(rMatrix4f.data);
}



void rglMultMatrix(RMatrix4f rMatrix4f)
{
	glMultMatrixf(rMatrix4f.data);
}

RMatrix4f rglGetMatrix()
{
	RMatrix4f m;
	glGetFloatv(GL_MODELVIEW,m.data);
	return (m);
}

