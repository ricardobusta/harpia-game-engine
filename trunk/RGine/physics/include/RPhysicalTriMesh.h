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
 * File: RPhysicalTriMesh.h
 * Created on: Aug 5, 2011
 */

#ifndef RPHYSICALTRIMESH_H_
#define RPHYSICALTRIMESH_H_

#include "RPhysicalObject.h"

#include <BulletCollision/Gimpact/btGImpactShape.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

/**
 * Triangular mesh physical object.
 */
class TriMesh : public RPhysicalObject {
private:
    btTriangleMesh* trimesh;

public:
    TriMesh(REntity *entity, double mass);
    ~TriMesh();
};

#endif /* RPHYSICALTRIMESH_H_ */
