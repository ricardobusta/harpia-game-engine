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

RPhysicalTriMesh::RPhysicalTriMesh(REntity *entity, double mass)
    :RPhysicalObject(entity, mass) {
    trimesh = new btTriangleMesh();

    RTriMesh *mesh = &entity->triMesh;
    int num = mesh->points.size();

    RVector3f scale = entity->getScale();
    btVector3 vertexBase[num];
    for(int i = 0; i < num; i++) {
        vertexBase[i].setX((float)(mesh->points[i].x() * scale.x()));
        vertexBase[i].setY((float)(mesh->points[i].y() * scale.y()));
        vertexBase[i].setZ((float)(mesh->points[i].z() * scale.z()));
    }

    for(int i = 0; i < num; i += 3) {
        trimesh->addTriangle( vertexBase[i], vertexBase[i+1], vertexBase[i+2]);
    }

    btGImpactMeshShape* trimesh_sh = new btGImpactMeshShape(trimesh);
    trimesh_sh->updateBound();

    initialize(trimesh_sh);
}

RPhysicalTriMesh::~RPhysicalTriMesh() {
    delete trimesh;
}
