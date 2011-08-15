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
 * File: game.cpp
 * Created on: Aug 2, 2011
 */
#include "Game.h"

#include <RGLPrimitives.h>
#include <RGLShapes.h>
#include <RGLText.h>
#include <REntity.h>
#include <RGLCommands.h>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <RPhysicalJoint.h>

Game::Game() {
}

Game::~Game() {
}

void Game::init() {
	camx = 0;
	camy = 0;
	phy->setGravity(9.8);

	REntity *ent;

	//Floor
	ent = newObject();
	ent->setPosition(0, -200, 0);
	ent->setBoxMesh(10000, 100, 50, RColor(0, 255, 0));
	ent->setBoxPhysics(0);

	//wall1
	//Floor
	ent = newObject();
	ent->setPosition(5000, 0, 0);
	ent->setBoxMesh(50, 5000, 50, RColor(0, 255, 0));
	ent->setBoxPhysics(0);

	//wall2
	ent = newObject();
	ent->setPosition(-5000, 2000, 0);
	ent->setBoxMesh(50, 5000, 50, RColor(0, 255, 0));
	ent->setBoxPhysics(0);

	//Wheel 1
	wheel1 = newObject();
	wheel1->setPosition(10, 0, 0);
	wheel1->setRotation(90, 0, 0);
	wheel1->setCylinderMesh(100, 50, 20, RColor(255, 255, 255));
	wheel1->setCylinderPhysics(1);
	wheel1->physicalObject->getRigidBody()->setAngularFactor(
			btVector3(0, 0, 1));
	wheel1->physicalObject->getRigidBody()->setLinearFactor(btVector3(1, 1, 0));

	//Wheel 2
	wheel2 = newObject();
	wheel2->setPosition(-250, 0, 0);
	wheel2->setRotation(90, 0, 0);
	wheel2->setCylinderMesh(100, 50, 20, RColor(200, 200, 200));
	wheel2->setCylinderPhysics(1);
	wheel2->physicalObject->getRigidBody()->setAngularFactor(
			btVector3(0, 0, 1));
	wheel2->physicalObject->getRigidBody()->setLinearFactor(btVector3(1, 1, 0));

	//vehicle center
	center = newObject();
	center->setPosition(0, 0, 0);
	center->setRotation(180, 0, 0);
	center->setBoxMesh(300, 50, 60, RColor(255, 255, 255));
	center->setBoxPhysics(1);
	center->physicalObject->getRigidBody()->setAngularFactor(
			btVector3(0, 0, 1));
	center->physicalObject->getRigidBody()->setLinearFactor(btVector3(1, 1, 0));

	//	phy->createJoint(objList[1].physicalObject,objList[2].physicalObject,RVector3f(0,0,0),RVector3f(0,0,1));
	//	phy->jointList.push_back(btHingeConstraint(objList[1].physicalObject, btTransform(btQuaternion(0,0,0,1),btVector3(0,0,1)),true));

		//Obstacle 1
		ent = newObject();
		ent->setPosition(-650, 0, 0);
		ent->setRotation(90, 0, 0);
		ent->setCylinderMesh(30, 50, 50, RColor(255, 0, 0));
		ent->setCylinderPhysics(5);
		ent->physicalObject->getRigidBody()->setAngularFactor(
				btVector3(0, 0, 1));
		ent->physicalObject->getRigidBody()->setLinearFactor(
				btVector3(1, 1, 0));
	//
//		//Obstacle 2
//		ent = newObject();
//		ent->setPosition();
//		ent->setBoxMesh();
//		ent->setBoxPhysics();
//		objList.push_back(REntity());
//		objList.back().triMesh = rglGenBox(400, 10, 50, RColor(0, 0, 255));
//		objList.back().setPosition(RVector3f(-600, 100, 0));
//		objList.back().physicalObject = phy->applyPhysics(&objList.back(),
//				RSHAPE_BOX, 1);
//		objList.back().physicalObject->getRigidBody()->setAngularFactor(
//				btVector3(0, 0, 1));
//		objList.back().physicalObject->getRigidBody()->setLinearFactor(
//				btVector3(1, 1, 0));
//
//		phy->createJoint(wheel->physicalObject, object->physicalObject,
//				RVector3f(0, 0, 0), RVector3f(0, 0, 1));

	//Obstacle 3
	//	objList.push_back(REntity());
	//	objList.back().triMesh = rglGenCone(200, 600, 50, RColor(0, 0, 255));
	//	objList.back().setPosition(RVector3f(-3000, 100, 0));
	//	objList.back().setRotation(RVector3f(180, 0, 0));
	//	objList.back().physicalObject = phy->applyPhysics(&objList.back(),
	//			RSHAPE_CONE, 5);
	//	objList.back().physicalObject->getRigidBody()->setAngularFactor(
	//			btVector3(0, 0, 1));
	//	objList.back().physicalObject->getRigidBody()->setLinearFactor(
	//			btVector3(1, 1, 0));

	//boxes

	for (int k = 0; k < 10; k++) {
		for (int i = 0; i < 10; i++) {
			ent = newObject();
			ent->setPosition(-1000 + k * -100, i * 100, 0);
			ent->setBoxMesh(50, 50, 50,
					RColor(255 * k / 4, 255 * 4 / 4, (255 * i / 9)));
			ent->setBoxPhysics(1);
			ent->physicalObject->getRigidBody()->setActivationState(false);
		}
	}

	/*	btPoint2PointConstraint* jt = new btPoint2PointConstraint(
	 *(wheel->physicalObject->getRigidBody())
	 ,btVector3(0,0,0));*/
	btPoint2PointConstraint* jt = new btPoint2PointConstraint(
			*(wheel1->physicalObject->getRigidBody()),
			*(center->physicalObject->getRigidBody()),
			btVector3(0,0,0),
			btVector3(150,0,0));
	/*new btHingeConstraint(wheel->physicalObject,object->physicalObject,
			 btVector3(),btVector3(),btVector3(),btVector3());
			 RPhysicalJoint(wheel->physicalObject, object->physicalObject,
			 btVector3(),
			 btVector3());
	 */

	phy	->dynamicsWorld->addConstraint(jt, true);

	jt = new btPoint2PointConstraint(*(wheel2->physicalObject->getRigidBody()),
			*(center->physicalObject->getRigidBody()),
			btVector3(0,0,0),
			btVector3(-150,0,0));

	phy	->dynamicsWorld->addConstraint(jt, true);
	//phy->jointList.push_back(jt);

}

#include "RString.h"

void Game::logic() {
	REntity* ent;

	if (key(SDLK_LEFT).isDown) {
		wheel1->physicalObject->getRigidBody()->setActivationState(true);
		wheel2->physicalObject->getRigidBody()->setActivationState(true);
		wheel1->physicalObject->getRigidBody()->applyTorqueImpulse(
				btVector3(0, 0, 500));
		wheel2->physicalObject->getRigidBody()->applyTorqueImpulse(
				btVector3(0, 0, 500));
	}
	if (key(SDLK_RIGHT).isDown) {
		wheel1->physicalObject->getRigidBody()->setActivationState(true);
				wheel2->physicalObject->getRigidBody()->setActivationState(true);
				wheel1->physicalObject->getRigidBody()->applyTorqueImpulse(
						btVector3(0, 0, -500));
				wheel2->physicalObject->getRigidBody()->applyTorqueImpulse(
						btVector3(0, 0, -500));
	}
	if (mouse().left.down) {
		ent = newObject();
		ent->setPosition(-camera.getPosition().x()+(mouse().position.x()-sdl.getWidth()/2), -camera.getPosition().y()-mouse().position.y()+sdl.getHeight()/2,
				-camera.getPosition().z()+500);
		ent->setSphereMesh(50, 4, RColor(255, 255, 0));
		ent->setSpherePhysics(1);
		ent->physicalObject->getRigidBody()->applyCentralImpulse(
				btVector3(0, 10, -500));
		//objList[0].physicalObject->getRigidBody()->setActivationState(true);
		//objList[0].physicalObject->getRigidBody()->setMassProps(1,btVector3(0,0,0));
	}
	if (key(SDLK_EQUALS).isDown) {
	}
	if (key(SDLK_MINUS).isDown) {
	}
	if (key(SDLK_a).isDown) {
		camx += 30;
	}
	if (key(SDLK_d).isDown) {
		camx -= 30;
	}
	if (key(SDLK_s).isDown) {
		camy -= 30;
	}
	if (key(SDLK_w).isDown) {
		camy += 30;
	}

	camera.setPosition(
			RVector3f(-center->getPosition().x() + camx,
					-center->getPosition().y() - camy, -1000));
	rglSetMatrix(camera.getAbsoluteTransformation());
}
