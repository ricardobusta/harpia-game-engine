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
 * File: RPhysics.h
 * Created on: Aug 7, 2011
 */

#ifndef RPHYSICS_H_
#define RPHYSICS_H_

#include <BulletCollision/Gimpact/btGImpactShape.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <btBulletDynamicsCommon.h>

#include "RPhysicalBox.h"
#include "RPhysicalCapsule.h"
#include "RPhysicalCone.h"
#include "RPhysicalConvexHull.h"
#include "RPhysicalCylinder.h"
#include "RPhysicalJoint.h"
#include "RPhysicalSphere.h"
#include "RPhysicalTerrain.h"
#include "RPhysicalTriMesh.h"

#include <RVector.h>
#include <RMain.h>

class RPhysics
{
    public:
        RPhysics();
        virtual ~RPhysics();
    public:
        RMain *main;

        int lastTick;

        //Bullet vars
        btBroadphaseInterface* broadphase;
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;
        btSequentialImpulseConstraintSolver* solver;
        btContinuousDynamicsWorld* dynamicsWorld;
        btClock clock;

        vector<RPhysicalObject*> objectList;
        vector<RPhysicalJoint*> jointList;
        RPhysicalObject *terrain;

        void setGravity(double gravity);

        void UpdatePhysics();

        void step();

        RPhysicalObject* applyPhysics(REntity* entity, RShape shape, float mass);

        void removeObject(RPhysicalObject* object);

        RPhysicalJoint* createJoint(RPhysicalObject* obj1, RPhysicalObject* obj2, RVector3f anchor, RVector3f axis);
        void removeJoint(RPhysicalJoint* joint);
    private:
};

#endif /* RPHYSICS_H_ */
