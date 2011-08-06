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
 * File: RGLPrimitives.cpp
 * Created on: Aug 5, 2011
 */

#include "RGLPrimitives.h"

#include <SDL/SDL_opengl.h>

void rglDrawTriangle(RVector3f p1, RVector3f p2, RVector3f p3, RColor color) {
	glBegin(GL_TRIANGLES);
	glColor3ub(color.r(), color.g(), color.b());
	glVertex3f(p1.x(), p1.y(), p1.z());
	glVertex3f(p2.x(), p2.y(), p2.z());
	glVertex3f(p3.x(), p3.y(), p3.z());
	glEnd();
}

void rglDrawQuad(RVector3f p1, RVector3f p2, RVector3f p3, RVector3f p4,
		RColor color) {
	glBegin(GL_QUADS);
	glColor3ub(color.r(), color.g(), color.b());
	glVertex3f(p1.x(), p1.y(), p1.z());
	glVertex3f(p2.x(), p2.y(), p2.z());
	glVertex3f(p3.x(), p3.y(), p3.z());
	glVertex3f(p4.x(), p4.y(), p4.z());
	glEnd();
}

void rglDrawLineStrip(vector<RVector3f> points, RColor color) {
	glBegin(GL_LINE_STRIP);
	glColor3ub(color.r(), color.g(), color.b());
	for (unsigned int i = 0; i < points.size(); i++) {
		glVertex3f(points[i].x(), points[i].y(), points[i].z());
	}
	glEnd();
}
