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
 * File: RGLPrimitives.h
 * Created on: Aug 5, 2011
 */

#ifndef RGLPRIMITIVES_H_
#define RGLPRIMITIVES_H_

#include "RPoint3f.h"
#include "RColor.h"
#include "vector" //TODO replace std::vector with RVector
using namespace std;

/**
 * Draw a triangle using OpenGL commands.
 *
 * @param p1 First point.
 * @param p2 Second point.
 * @param p3 Third point.
 * @param color Color.
 */
void rglDrawTriangle(RPoint3f p1, RPoint3f p2, RPoint3f p3, RColor color);

/**
 * Draw a quad using OpenGL commands.
 *
 * @param p1 First point.
 * @param p2 Second point.
 * @param p3 Third point.
 * @param p4 Fourth point.
 * @param color Color.
 */
void rglDrawQuad(RPoint3f p1, RPoint3f p2, RPoint3f p3, RPoint3f p4,
		RColor color);

/**
 * Draw a line strip using OpenGL commands.
 *
 * @param points
 * @param color
 */
void rglDrawLineStrip(vector<RPoint3f> points, RColor color);

/*
 * TODO more primitives.
 */

#endif /* RGLPRIMITIVES_H_ */
