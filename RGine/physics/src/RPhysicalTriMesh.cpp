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
 * File: RPhysicalTriMesh.cpp
 * Created on: Aug 5, 2011
 */

#include "RPhysicalTriMesh.h"

//TriMesh::TriMesh(ISceneNode *irrobject, double mass)
//    :vlPhysicalObject(irrobject, mass) {
//    trimesh = new btTriangleMesh();
//
//    IMeshBuffer* mbuffer = ((IAnimatedMeshSceneNode*)irrobject)->getMesh()->getMeshBuffer(0);
//
//    int numIndices = mbuffer->getIndexCount();
//
//    int indexBase[numIndices];
//
//    u16* irrIndexBase = mbuffer->getIndices();
//
//    for(int i = 0; i < numIndices; i++)
//        indexBase[i] = (int)irrIndexBase[i];
//
//    int numVertices = mbuffer->getVertexCount();
//
//    btVector3 vertexBase[numVertices];
//
//    S3DVertex* vertices = (S3DVertex*)(mbuffer->getVertices());
//    vector3df scale = irrobject->getScale();
//
//    for(int i = 0; i < numVertices; i++) {
//        vertexBase[i].setX((float)(vertices[i].Pos.X * scale.X));
//        vertexBase[i].setY((float)(vertices[i].Pos.Y * scale.Y));
//        vertexBase[i].setZ((float)(vertices[i].Pos.Z * scale.Z));
//    }
//
//    for(int i = 0; i < numIndices; i += 3) {
//        trimesh->addTriangle( vertexBase[indexBase[i]], vertexBase[indexBase[i+1]], vertexBase[indexBase[i+2]]);
//    }
//
//    btGImpactMeshShape* trimesh_sh = new btGImpactMeshShape(trimesh);
//    trimesh_sh->updateBound();
//
//    initialize(trimesh_sh);
//
//}
//
//TriMesh::~TriMesh() {
//    delete trimesh;
//}
