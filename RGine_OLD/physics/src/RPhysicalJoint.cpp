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
 * File: RPhysicalJoint.cpp
 * Created on: Aug 5, 2011
 */

#include "RPhysicalJoint.h"

RPhysicalJoint::RPhysicalJoint(RPhysicalObject* obj1, RPhysicalObject* obj2,
		btVector3 anchor, btVector3 axis = btVector3(0, 0, 1)) {
	jointType = RJ_HINGE;
	constraint = createHinge(obj1, obj2,
			btVector3(anchor.x(), anchor.y(), anchor.z()),
			btVector3(axis.x(), axis.y(), axis.z()));
}

RPhysicalJoint::~RPhysicalJoint() {
	delete constraint;
}

Joints RPhysicalJoint::getType() {
	return (jointType);
}

btTypedConstraint* RPhysicalJoint::getConstraint() {
	return (constraint);
}

btHingeConstraint* RPhysicalJoint::createHinge(RPhysicalObject* obj1,
		RPhysicalObject* obj2, btVector3 anchor, btVector3 axis) {
	btVector3 anchorInA, anchorInB;

//	anchorInA = anchor;

//	anchorInB = obj2->getRigidBody()->getCenterOfMassTransform().inverse()
//			* (obj1->getRigidBody()->getCenterOfMassTransform() * anchor);

	return (new btHingeConstraint(
			*(obj1->getRigidBody()), *(obj2->getRigidBody()), anchorInA, anchorInB, axis, axis, true)
			);

		}

void RPhysicalJoint::setLimits(float min, float max) {
	if (jointType == RJ_HINGE) {
		btScalar radMin = min * M_PI / 180.0, radMax = max * M_PI / 180.0;

		((btHingeConstraint*) constraint)->setLimit(radMin, radMax);
	}
}

void RPhysicalJoint::move(float force) {
	if (jointType == RJ_HINGE) {
		if (force == 0) {
			((btHingeConstraint*) constraint)->enableMotor(false);
			return;
		}
		((btHingeConstraint*) constraint)->enableAngularMotor(true, force,
				100.0);
	}
}
