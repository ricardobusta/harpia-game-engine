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
 * File: RPhysicalCapsule.h
 * Created on: Aug 5, 2011
 */

#ifndef RPHYSICALCAPSULE_H_
#define RPHYSICALCAPSULE_H_

#include "RPhysicalObject.h"

/**
 * Capsule shaped physical object.
 */
class RPhysicalCapsule : public RPhysicalObject {
public:
	/**
	 * Creates a physical capsule attached to that entity.
	 *
	 * @param entity Entity that will have this physical property.
	 * @param mass Mass of that entity.
	 */
    RPhysicalCapsule(REntity *entity, double mass);
    ~RPhysicalCapsule() {};
};

#endif /* RPHYSICALCAPSULE_H_ */
