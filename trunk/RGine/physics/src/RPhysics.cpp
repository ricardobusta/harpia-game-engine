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
 * File: RPhysics.cpp
 * Created on: Aug 7, 2011
 */

#include "RPhysics.h"

#include <RMain.h>

RPhysics::RPhysics(RMain *main) {
	this->main = main;

	broadphase = new btDbvtBroadphase();

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);

	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btContinuousDynamicsWorld(dispatcher, broadphase,
			solver, collisionConfiguration);
}

RPhysics::~RPhysics() {
	while (!jointList.empty()) {
		dynamicsWorld->removeConstraint(jointList.back()->getConstraint());
		delete jointList.back();
		jointList.pop_back();
	}

	while (!objectList.empty()) {
		dynamicsWorld->removeRigidBody(objectList.back()->getRigidBody());
		delete objectList.back();
		objectList.pop_back();
	}

	delete broadphase;
	delete collisionConfiguration;
	delete dispatcher;
	delete solver;
	delete dynamicsWorld;
}

void RPhysics::updatePhysics() {
	unsigned int tick = main->sdl.timer_getCurrentTick();
	unsigned int TDeltaTime = lastTick - tick;
	lastTick = tick;

	dynamicsWorld->stepSimulation(TDeltaTime * 0.001f, 60);

	list<RPhysicalObject*>::iterator it;
	for (it = objectList.begin(); it != objectList.end(); it++)
		(*it)->update();

}

void RPhysics::step() {
	btScalar dt = (btScalar) clock.getTimeMicroseconds();
	clock.reset();

	dynamicsWorld->stepSimulation(dt / 1000000.f);
}

RPhysicalObject* RPhysics::applyPhysics(REntity* object, RShape shape,
		float mass) {
	RPhysicalObject* phyObject;
	switch (shape) {

	case RSHAPE_BOX:
		phyObject = new RPhysicalBox(object, mass);
		break;
	case RSHAPE_CAPSULE:
		phyObject = new RPhysicalCapsule(object, mass);
		break;
	case RSHAPE_CONE:
		phyObject = new RPhysicalCone(object, mass);
		break;
	case RSHAPE_CONVEXHULL:
		//phyObject = new RPhysicalConvexHull(object, mass);
		break;
	case RSHAPE_CYLINDER:
		phyObject = new RPhysicalCylinder(object, mass);
		break;
	case RSHAPE_SPHERE:
		phyObject = new RPhysicalSphere(object, mass);
		break;
	case RSHAPE_TRIMESH:
		phyObject = new RPhysicalTriMesh(object, mass);
		break;
	default:
		phyObject = new RPhysicalSphere(object, mass);
		break;
	}

	objectList.push_back(phyObject);
	dynamicsWorld->addRigidBody(phyObject->getRigidBody());

	return (phyObject);
}

RPhysicalJoint* RPhysics::createJoint(RPhysicalObject* obj1,
		RPhysicalObject* obj2, RVector3f anchor, RVector3f axis) {
	RPhysicalJoint* jt = new RPhysicalJoint(obj1, obj2,
			btVector3(anchor.x(), anchor.y(), anchor.z()),
			btVector3(axis.x(), axis.y(), axis.z()));
	dynamicsWorld->addConstraint(jt->getConstraint(), true);

	jointList.push_back(jt);

	return (jt);
}

void RPhysics::removeJoint(RPhysicalJoint* joint) {
	list<RPhysicalJoint*>::iterator it;
	for (it = jointList.begin(); it != jointList.end(); it++) {
		if ((*it) == joint) {
			dynamicsWorld->removeConstraint((*it)->getConstraint());
			delete (*it);
			jointList.erase(it);
			return;
		}
	}
}

void RPhysics::setGravity(double gravity) {
	dynamicsWorld->setGravity(btVector3(0, -gravity, 0));
}
