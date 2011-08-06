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
 * File: REntity.cpp
 * Created on: Aug 5, 2011
 */

#include "REntity.h"

#include <RFrame.h>

REntity::REntity() {
	hasMesh = false;
	hasPhysics = false;

	scale.set(1,1,1);
}

REntity::~REntity() {
}

void REntity::handle(){
}

void REntity::render()
{
	if(hasMesh){

	}
}

/*TODO if physics bug the issue might be here*/
RMatrix4f REntity::getAbsoluteTransformation()
{
	RFrame f;
	f.rotate(rotation.y(),0,1,0);
	f.rotate(rotation.x(),1,0,0);
	f.rotate(rotation.z(),0,0,1);
	f.move(position.x(),position.y(),position.z());
	f.scale(scale.x(),scale.y(),scale.z());
	return f.getMatrix();
}




