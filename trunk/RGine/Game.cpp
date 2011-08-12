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

	//Floor
	objList.push_back(REntity());
	objList.back().triMesh = rglGenBox(10000, 100, 50, RColor(0, 255, 0));
	objList.back().setPosition(RVector3f(0, -200, 0));
	objList.back().physicalObject = phy->applyPhysics(&objList.back(),
			RSHAPE_BOX, 0);

	//wall1
	objList.push_back(REntity());
	objList.back().triMesh = rglGenBox(50, 5000, 50, RColor(0, 255, 0));
	objList.back().setPosition(RVector3f(5000, 0, 0));
	objList.back().physicalObject = phy->applyPhysics(&objList.back(),
			RSHAPE_BOX, 0);

	//wall2
	objList.push_back(REntity());
	objList.back().triMesh = rglGenBox(50, 5000, 50, RColor(0, 255, 0));
	objList.back().setPosition(RVector3f(-5000, 2000, 0));
	objList.back().physicalObject = phy->applyPhysics(&objList.back(),
			RSHAPE_BOX, 0);

	//Wheel 1
	objList.push_back(REntity());
	objList.back().triMesh = rglGenCylinder(100, 50, 500,
			RColor(255, 255, 255));
	objList.back().setPosition(RVector3f(10, 0, 0));
	objList.back().setRotation(RVector3f(90, 0, 0));
	objList.back().physicalObject = phy->applyPhysics(&objList.back(),
			RSHAPE_CYLINDER, 1);
	wheel = &objList.back();
	wheel->physicalObject->getRigidBody()->setAngularFactor(btVector3(0, 0, 1));
	wheel->physicalObject->getRigidBody()->setLinearFactor(btVector3(1, 1, 0));

	//Wheel 2
	objList.push_back(REntity());
	objList.back().triMesh = rglGenCylinder(100, 50, 500, RColor(200, 200, 200));
	objList.back().setPosition(RVector3f(-250, 0, 0));
	objList.back().setRotation(RVector3f(90, 0, 0));
	objList.back().physicalObject = phy->applyPhysics(&objList.back(),
			RSHAPE_CYLINDER, 1);
	objList.back().physicalObject->getRigidBody()->setAngularFactor(
			btVector3(0, 0, 1));
	objList.back().physicalObject->getRigidBody()->setLinearFactor(
			btVector3(1, 1, 0));
	object = &objList.back();

	//vehicle center
	objList.push_back(REntity());
	objList.back().triMesh = rglGenBox(300, 50, 60, RColor(255, 255, 255));
	objList.back().setPosition(RVector3f(0, 0, 0));
	objList.back().setRotation(RVector3f(180, 0, 0));
	objList.back().physicalObject = phy->applyPhysics(&objList.back(),
			RSHAPE_BOX, 1);
	objList.back().physicalObject->getRigidBody()->setAngularFactor(
			btVector3(0, 0, 1));
	objList.back().physicalObject->getRigidBody()->setLinearFactor(
			btVector3(1, 1, 0));
	center = &objList.back();

	//	phy->createJoint(objList[1].physicalObject,objList[2].physicalObject,RVector3f(0,0,0),RVector3f(0,0,1));
	//	phy->jointList.push_back(btHingeConstraint(objList[1].physicalObject, btTransform(btQuaternion(0,0,0,1),btVector3(0,0,1)),true));

	//Obstacle 1
	objList.push_back(REntity());
	objList.back().triMesh = rglGenCylinder(30, 50, 50, RColor(255, 0, 0));
	objList.back().setPosition(RVector3f(-650, 0, 0));
	objList.back().setRotation(RVector3f(90, 0, 0));
	objList.back().physicalObject = phy->applyPhysics(&objList.back(),
			RSHAPE_CYLINDER, 5);
	objList.back().physicalObject->getRigidBody()->setAngularFactor(
			btVector3(0, 0, 1));
	objList.back().physicalObject->getRigidBody()->setLinearFactor(
			btVector3(1, 1, 0));

	//Obstacle 2
	objList.push_back(REntity());
	objList.back().triMesh = rglGenBox(400, 10, 50, RColor(0, 0, 255));
	objList.back().setPosition(RVector3f(-600, 100, 0));
	objList.back().physicalObject = phy->applyPhysics(&objList.back(),
			RSHAPE_BOX, 1);
	objList.back().physicalObject->getRigidBody()->setAngularFactor(
			btVector3(0, 0, 1));
	objList.back().physicalObject->getRigidBody()->setLinearFactor(
			btVector3(1, 1, 0));

	//	phy->createJoint(wheel->physicalObject, object->physicalObject,
	//			RVector3f(0, 0, 0), RVector3f(0, 0, 1));

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
		//		for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 10; i++) {
			objList.push_back(REntity());
			objList.back().triMesh = rglGenBox(50, 50, 50,
					RColor(255 * k / 4, 255 * 4 / 4, (255 * i / 9)));
			objList.back().setPosition(
					//						RVector3f(-1000+k*-100, i * 100, (j - 2) * 100));
					RVector3f(-1000 + k * -100, i * 100, 0));
			objList.back().physicalObject = phy->applyPhysics(&objList.back(),
					RSHAPE_BOX, 1);
			objList.back().physicalObject->getRigidBody()->setActivationState(
					false);

			objList.back().physicalObject->getRigidBody()->setAngularFactor(
					btVector3(0, 0, 1));
			objList.back().physicalObject->getRigidBody()->setLinearFactor(
					btVector3(1, 1, 0));
		}
		//		}
	}

	/*	btPoint2PointConstraint* jt = new btPoint2PointConstraint(
	 *(wheel->physicalObject->getRigidBody())
	 ,btVector3(0,0,0));*/
	btPoint2PointConstraint* jt = new btPoint2PointConstraint(
			*(wheel->physicalObject->getRigidBody()),
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

	jt = new btPoint2PointConstraint(
				*(object->physicalObject->getRigidBody()),
				*(center->physicalObject->getRigidBody()),
				btVector3(0,0,0),
				btVector3(-150,0,0));

	phy	->dynamicsWorld->addConstraint(jt, true);
	//phy->jointList.push_back(jt);

}

#include "RString.h"

void Game::logic() {
	if (key(SDLK_LEFT).isDown) {
		wheel->physicalObject->getRigidBody()->setActivationState(true);
		//objList[1].physicalObject->getRigidBody()->applyCentralImpulse(
		//btVector3(0, 10, 0));
		wheel->physicalObject->getRigidBody()->applyCentralImpulse(
				btVector3(-10, 0, 0));
		wheel->physicalObject->getRigidBody()->applyTorqueImpulse(
				btVector3(0, 0, 500));
	}
	if (key(SDLK_RIGHT).isDown) {
		wheel->physicalObject->getRigidBody()->setActivationState(true);
		//objList[1].physicalObject->getRigidBody()->applyCentralImpulse(
		//btVector3(0, 10, 0));
		wheel->physicalObject->getRigidBody()->applyCentralImpulse(
				btVector3(10, 0, 0));
		wheel->physicalObject->getRigidBody()->applyTorqueImpulse(
				btVector3(0, 0, -500));
	}
	if (mouse().left.down) {
		objList.push_back(REntity());
		objList.back().triMesh = rglGenSphere(50, 4, RColor(255, 255, 0));
		objList.back().setPosition(
				RVector3f(-camera.getPosition().x(), -camera.getPosition().y(),
						-camera.getPosition().z()));
		objList.back().physicalObject = phy->applyPhysics(&objList.back(),
				RSHAPE_SPHERE, 1);
		objList.back().physicalObject->getRigidBody()->applyCentralImpulse(
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
}

void Game::render() {
	camera.setPosition(
			RVector3f(-wheel->getPosition().x() + camx, -camy, -400));
	rglSetMatrix(camera.getAbsoluteTransformation());
	/*
	RGLText txt("|cFF0000t|c00FF00este\n|rGravidade: 9.8", 25,
			wheel->getPosition().x() - 300, wheel->getPosition().y() + 300,
			wheel->getPosition().z(), 1);
	txt.setColor(1, 1, 1);
	txt.draw();*/
	list<REntity>::iterator it;
	for (it = objList.begin(); it != objList.end(); it++) {
		rglSetMatrix(camera.getAbsoluteTransformation());
		//glMultMatrixf(objList[i].getAbsoluteTransformation().gl());
		(*it).render();
		//rglDrawTriMesh(objList[i].triMesh);
	}

	//glLoadMatrixf(frame.getMatrix());

	//rglDrawCylinder(200,200,100,RColor(255,255,255));
	//rglDrawCone(200,200,100,RColor(255,255,255));
	//rglDrawSphere(100, 16, RColor(255, 255, 255));
	//rglDrawCapsule(100,200,10,RColor(255,255,255));
	//rglDrawBox(200, 20, 200, RColor(0.1f, 0.1f, 0.9f));

	//frame.setIdentity();
	//frame.setPosition(300, 300, 0);
	//glLoadMatrixf(frame.getMatrix());
	//rglDrawCone(200, 200, 100, RColor(255, 255, 255));
}
