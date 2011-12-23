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
 * File: Vehicle.cpp
 * Created on: Aug 15, 2011
 */

#include "Vehicle.h"

#include <cmath>
#include <RColor.h>

Vehicle::Vehicle(RMain* p) {
	parent = p;
	// TODO Auto-generated constructor stub

}

Vehicle::~Vehicle() {
	// TODO Auto-generated destructor stub
}

void Vehicle::buildVehicle(float angle0, float magnitude0, float angle1,
		float magnitude1, float angle2, float magnitude2, float angle3,
		float magnitude3, float angle4, float magnitude4, float angle5,
		float magnitude5, float angle6, float magnitude6, float angle7,
		float magnitude7, unsigned int wheel0axis, float wheel0radius,
		float wheel0angle, unsigned int wheel1axis, float wheel1radius,
		float wheel1angle) {

	float angletot = angle0 + angle1 + angle2 + angle3 + angle4 + angle5
			+ angle6 + angle7;

	//	float a0 = (2 * M_PI) * (angle0 / angletot);
	float a0 = M_PI / 4;
	float a1 = 2 * a0;
	float a2 = 3 * a0;
	float a3 = 4 * a0;
	float a4 = 5 * a0;
	float a5 = 6 * a0;
	float a6 = 7 * a0;
	float a7 = 8 * a0;
	vector[0].set(magnitude0 * cos(a0), magnitude0 * sin(a0), 0);
	//	float a1 = (2 * M_PI) * (angle1 / angletot);

	vector[1].set(magnitude1 * cos(a1), magnitude1 * sin(a1), 0);
	//	float a2 = (2 * M_PI) * (angle2 / angletot);

	vector[2].set(magnitude2 * cos(a2), magnitude2 * sin(a2), 0);
	//	float a3 = (2 * M_PI) * (angle3 / angletot);

	vector[3].set(magnitude3 * cos(a3), magnitude3 * sin(a3), 0);
	//	float a4 = (2 * M_PI) * (angle4 / angletot);
	vector[4].set(magnitude4 * cos(a4), magnitude4 * sin(a4), 0);
	//	float a5 = (2 * M_PI) * (angle5 / angletot);
	vector[5].set(magnitude5 * cos(a5), magnitude5 * sin(a5), 0);
	//	float a6 = (2 * M_PI) * (angle6 / angletot);
	vector[6].set(magnitude6 * cos(a6), magnitude6 * sin(a6), 0);
	//	float a7 = (2 * M_PI) * (angle7 / angletot);
	vector[7].set(magnitude7 * cos(a7), magnitude7 * sin(a7), 0);
	RVector3f o(0, 0, 0);

	RTriMesh mesh;
	for (int i = 0; i < 7; i++) {
		mesh.addTriangle(o, vector[i], vector[i + 1], o, RColor(255, 255, 255));
		//		mesh.addTriangle(o, vector[i + 1], vector[i], o, RColor(255, 255, 255));

	}
	mesh.addTriangle(o, vector[7], vector[0], o, RColor(255, 255, 255));
	//	mesh.addTriangle(o, vector[0], vector[7], o, RColor(255, 255, 255));
	//mesh.addTriangle(RVector3f(0,0,0),RVector3f(500,500,0),RVector3f(0,500,0));

	body = parent->newEntity();
	body->setPosition(0, 1000, 0);
	body->setTriMesh(mesh);
	//body->setTriMesh(mesh);
	body->setTriMeshPhysics(1);
	body->set2DXYPhysics();

	wheel0 = parent->newEntity();
	wheel0->setPosition(0, 1000, 0);
	wheel0->setRotation(90, 0, 0);
	wheel0->setCylinderMesh(wheel0radius, 50, 10, RColor(255, 0, 255));
	wheel0->setCylinderPhysics(1);
	wheel0->addPointConstraint(o, body, vector[wheel0axis]);
	wheel0->set2DXYPhysics();
	wheel0->physicalObject->getRigidBody()->setActivationState(false);

	wheel1 = parent->newEntity();
	wheel1->setPosition(0, 1000, 0);
	wheel1->setRotation(90, 0, 0);
	wheel1->setCylinderMesh(wheel1radius, 50, 10, RColor(0, 255, 255));
	wheel1->setCylinderPhysics(1);
	wheel1->addPointConstraint(o, body, vector[wheel1axis]);
	wheel1->set2DXYPhysics();
	wheel1->physicalObject->getRigidBody()->setActivationState(false);
	//	REntity* wheel2 = parent->newEntity();
	//	wheel2->setCylinderMesh(100, 50 ,10,RColor(255,0,255));
	//	wheel2->setCylinderPhysics(1);

	//mesh.add
}

