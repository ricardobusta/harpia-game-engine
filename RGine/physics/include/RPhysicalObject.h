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
 * File: RPhysicalObject.h
 * Created on: Aug 5, 2011
 */

#ifndef RPHYSICALOBJECT_H_
#define RPHYSICALOBJECT_H_

#include <cmath>
#include <btBulletDynamicsCommon.h>
#include <REntity.h>
//#include "RPhysicalJoint.h"

enum RShape {
	RSHAPE_SPHERE,
	RSHAPE_BOX,
	RSHAPE_CAPSULE,
	RSHAPE_CYLINDER,
	RSHAPE_CONE,
	RSHAPE_CONVEXHULL,
	RSHAPE_TRIMESH
};

class RPhysicalJoint;

/**
 * Generic Physical Object Representation.
 * This class will be used by the physics engine to represent an object with
 * physical behavior.
 */
class RPhysicalObject {
	friend class RPhysicalJoint;
	friend class RPhysics;

private:
	btRigidBody* rigidBody;
	btCollisionShape* shape;
	btDefaultMotionState* motionState;
	double mass;

	REntity* entity;
	//ISceneNode* irrnode;

protected:
	void initializeTerrain(btCollisionShape* shape,
			btDefaultMotionState* motionState);
	void initialize(btCollisionShape* shape);

	void update();
public:

	btRigidBody* getRigidBody();
	btVector3 getJointReferenceAxis();
	REntity* getEntity();

	//public:

	RPhysicalObject(REntity* entity, double mass);
	~RPhysicalObject();

//	void setPosition(RVector3f);

	RVector3f getScale();
	RVector3f getPosition();
	RVector3f getRotation();
	RMatrix4f getAbsoluteTransformation();

	float getAngularVel();
	float getLinearVel();

	void setRestitution(float c);
	void setFriction(float c);

	void setLinearDamping(float damp);
	void setAngularDamping(float damp);

	bool isColliding(RPhysicalObject* obj);
};

#endif /* RPHYSICALOBJECT_H_ */
