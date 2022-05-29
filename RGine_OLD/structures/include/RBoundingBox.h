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
 * File: RBoundingBox.h
 * Created on: Aug 6, 2011
 */

#ifndef RBOUNDINGBOX_H_
#define RBOUNDINGBOX_H_

#include <RVector3f.h>
#include "RTriMesh.h"

/**
 *
 */
class RBoundingBox {
public:
	RBoundingBox();
	virtual ~RBoundingBox();

    void setMaxVertex(RVector3f maxVertex);
    void setMinVertex(RVector3f minVertex);
	RVector3f getMaxVertex() const;
    RVector3f getMinVertex() const;

    void set(RTriMesh mesh);
private:
    RVector3f minVertex;
    RVector3f maxVertex;
};

#endif /* RBOUNDINGBOX_H_ */
