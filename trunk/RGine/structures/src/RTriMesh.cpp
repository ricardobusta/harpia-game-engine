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
 * File: RTriMesh.cpp
 * Created on: Aug 5, 2011
 */

#include "RTriMesh.h"

RTriMesh::RTriMesh() {
	// TODO Auto-generated constructor stub

}

RTriMesh::~RTriMesh() {
	// TODO Auto-generated destructor stub
}

void RTriMesh::addPoint(RVector3f point, RVector3f normal, RColor color)
{
	points.push_back(point);
	normals.push_back(normal);
	colors.push_back(color);
}



void RTriMesh::addTriangle(RVector3f p1, RVector3f p2, RVector3f p3, RColor color)
{
	RVector3f px1 = p1-p3;
	RVector3f px2 = p2-p3;
	RVector3f n = (px1^px2).unit();
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	normals.push_back(n);
	normals.push_back(n);
	normals.push_back(n);
	colors.push_back(color);
	colors.push_back(color);
	colors.push_back(color);
}

void RTriMesh::addTriangle(RVector3f p1, RVector3f p2, RVector3f p3, RVector3f n, RColor color)
{
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	normals.push_back(n);
	normals.push_back(n);
	normals.push_back(n);
	colors.push_back(color);
	colors.push_back(color);
	colors.push_back(color);
}



RVector3f RTriMesh::getPoint(int at)
{
	return (points.at(at));
}



void RTriMesh::removePoint(int at)
{
	//points.erase(points.at(at));
}

unsigned int RTriMesh::size()
{
	return points.size();
}





