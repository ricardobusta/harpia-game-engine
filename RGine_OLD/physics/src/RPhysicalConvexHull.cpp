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
 * File: RPhysicalConvexHull.cpp
 * Created on: Aug 5, 2011
 */

#include "RPhysicalConvexHull.h"

//ConvexHull::ConvexHull(ISceneNode *irrobject, double mass)
//    :vlPhysicalObject(irrobject, mass) {
//    IMeshBuffer* mbuffer = ((IAnimatedMeshSceneNode*)irrobject)->getMesh()->getMeshBuffer(0);
//
//    int numVertices = mbuffer->getVertexCount();
//
//    btVector3 vertexBase[numVertices];
//
//    S3DVertex* vertices = (S3DVertex*)(mbuffer->getVertices());
//    vector3df scale = irrobject->getScale();
//
//    btConvexHullShape* chshape = new btConvexHullShape();
//
//    for(int i = 0; i < numVertices; i++) {
//        vertexBase[i].setX((float)(vertices[i].Pos.X * scale.X));
//        vertexBase[i].setY((float)(vertices[i].Pos.Y * scale.Y));
//        vertexBase[i].setZ((float)(vertices[i].Pos.Z * scale.Z));
//        chshape->addPoint(vertexBase[i]);
//    }
//
//    initialize(chshape);
//
//}
