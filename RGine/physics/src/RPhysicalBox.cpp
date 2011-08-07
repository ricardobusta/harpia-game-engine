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
 * File: RPhysicalBox.cpp
 * Created on: Aug 5, 2011
 */

#include "RPhysicalBox.h"

RPhysicalBox::RPhysicalBox(REntity* entity, double mass) :
RPhysicalObject(entity, mass) {
	btVector3 size;
	RVector3f scale = entity->scale;
	RVector3f minVertex = entity->getBoundingBox().getMinVertex();
	RVector3f maxVertex = entity->getBoundingBox().getMaxVertex();

	size.setX(scale.x()*((maxVertex.x() - minVertex.x())/2.0 ));
	size.setY(scale.y()*((maxVertex.y() - minVertex.y())/2.0 ));
	size.setZ(scale.z()*((maxVertex.z() - minVertex.z())/2.0 ));

	initialize(new btBoxShape(size));
}
