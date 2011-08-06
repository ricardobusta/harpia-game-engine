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
 * File: RGLShapes.h
 * Created on: Aug 5, 2011
 */

#ifndef RGLSHAPES_H_
#define RGLSHAPES_H_

#include "RColor.h"

#include <RTriMesh.h>

/**
 * Draw a box using OpenGL commands.
 *
 * @param width Box width.
 * @param height Box height.
 * @param depth Box depth.
 * @param color Box color.
 */
void rglDrawBox(float width, float height, float depth, RColor color);

/**
 * Draw a capsule using OpenGL commands.
 *
 * @param radius Capsule corners radius.
 * @param height Capsule body height.
 * @param div Capsule level of detail.
 * @param color Capsule color.
 */
void rglDrawCapsule(float radius, float height, unsigned int div, RColor color);

/**
 * Draw a cone using OpenGL commands.
 *
 * @param radius Cone bottom radius.
 * @param height Cone height.
 * @param div Cone level of detail.
 * @param color Cone color.
 */
void rglDrawCone(float radius, float height, unsigned int div, RColor color);

/**
 * Draw a convex hull using OpenGL commands. TODO
 */
void rglDrawConvexHull();

/**
 * Draw a cylinder using OpenGL commands.
 *
 * @param radius Cylinder radius.
 * @param height Cylinder height.
 * @param div Cylinder level of detail.
 * @param color Cylinder color.
 */
void rglDrawCylinder(float radius, float height, unsigned int div, RColor color);

/**
 * Draw a sphere using OpenGL commands.
 *
 * @param radius Sphere radius.
 * @param div Sphere level of detail.
 * @param color Sphere color.
 */
void rglDrawSphere(float radius, unsigned int div, RColor color);

/**
 * Draw a triangle mesh using OpenGL commands. TODO
 *
 * @param mesh Triangular mesh containing a vector of vertexes.
 */
void rglDrawTriMesh(RTriMesh mesh);

/**
 * Generate a box and returns a tringle mesh.
 *
 * @param width Box width.
 * @param height Box height.
 * @param depth Box depth.
 * @param color Box color.
 *
 * @return A triangle mesh representing this object.
 */
RTriMesh rglGenBox(float width, float height, float depth, RColor color);
RTriMesh rglGenCapsule(float radius, float height, unsigned int div, RColor color);
RTriMesh rglGenCone(float radius, float height, unsigned int div, RColor color);
RTriMesh rglGenConvexHull();
RTriMesh rglGenCylinder(float radius, float height, unsigned int div, RColor color);
RTriMesh rglGenSphere(float radius, unsigned int div, RColor color);;


#endif /* RGLSHAPES_H_ */
