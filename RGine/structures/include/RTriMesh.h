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
 * File: RTriMesh.h
 * Created on: Aug 5, 2011
 */

#ifndef RTRIMESH_H_
#define RTRIMESH_H_

#include "RVector3f.h"
#include "RColor.h"
#include <vector>
using namespace std;
//TODO replace with RVector

/**
 * This class stores a triangular mesh. Used to represent a tridimentional object.
 */
class RTriMesh {
public:
	RTriMesh();
	virtual ~RTriMesh();

	/**
	 * Add a point to the triangular mesh.
	 *
	 * @param point The position of the vertex that will be added.
	 * @param normal Normal of that vertex. Default is (0,0,1).
	 * @param color Color of that vertex. Default is white.
	 */
	void addPoint(RVector3f point, RVector3f normal, RColor color=RColor(255,255,255));
	void addTriangle(RVector3f p1, RVector3f p2, RVector3f p3, RColor color=RColor(255,255,255));
	void addTriangle(RVector3f p1, RVector3f p2, RVector3f p3, RVector3f normal, RColor color=RColor(255,255,255));
	/**
	 * Get a point at the given position.
	 *
	 * @param at Index of the wanted vertex.
	 * @return The point of that vertex.
	 */
	RVector3f getPoint(int at);
	/**
	 * Remove the vertex from the triangular mesh.
	 *
	 * @param at Vertex index.
	 */
	void removePoint(int at);

public: //make private
	vector<RVector3f> points;
	vector<RVector3f> normals;
	vector<RColor> colors;
};

#endif /* RTRIMESH_H_ */
