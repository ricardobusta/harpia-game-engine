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
 * File: Vehicle.h
 * Created on: Aug 15, 2011
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <RTriMesh.h>
#include <RVector3f.h>
#include <RMain.h>

/**
 *
 */
class Vehicle {
public:
	Vehicle(RMain* parent);
	virtual ~Vehicle();

	RMain *parent;

	REntity* wheel0;
	REntity* wheel1;
	REntity* body;

	void buildVehicle(float angle0, float magnitude0, float angle1,
			float magnitude1, float angle2, float magnitude2, float angle3,
			float magnitude3, float angle4, float magnitude4, float angle5,
			float magnitude5, float angle6, float magnitude6, float angle7,
			float magnitude7, unsigned int wheel0axis, float wheel0radius,
			float wheel0angle, unsigned int wheel1axis, float wheel1radius,
			float wheel1angle);

	RVector3f vector[8];
};

#endif /* VEHICLE_H_ */
