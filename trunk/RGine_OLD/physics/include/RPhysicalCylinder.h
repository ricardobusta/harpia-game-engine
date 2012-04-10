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
 * File: RPhysicalCylinder.h
 * Created on: Aug 5, 2011
 */

#ifndef RPHYSICALCYLINDER_H_
#define RPHYSICALCYLINDER_H_

#include "RPhysicalObject.h"

/**
 * Cylinder shaped physical object.
 */
class RPhysicalCylinder : public RPhysicalObject {
public:
    RPhysicalCylinder(REntity *entity, double mass);
    ~RPhysicalCylinder() {};
};

#endif /* RPHYSICALCYLINDER_H_ */