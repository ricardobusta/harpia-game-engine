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
	objList.back().triMesh = rglGenBox(5000, 100, 500, RColor(0, 255, 0));
	objList.back().setPosition(RVector3f(-2500, -400, 0));
	objList.back().physicalObject = phy->applyPhysics(&objList.back(),
			RSHAPE_BOX, 0);

	//Wheel 1
	objList.push_back(REntity());
	objList.back().triMesh = rglGenCylinder(100, 300, 500, RColor(255, 0, 0));
	objList.back().setPosition(RVector3f(0, 0, 0));
	objList.back().setRotation(RVector3f(90, 0, 0));
	objList.back().physicalObject = phy->applyPhysics(&objList.back(),
			RSHAPE_CYLINDER, 1);
	wheel = &objList.back();
	/*
	 //Wheel 2
	 objList.push_back(REntity());
	 objList.back().triMesh = rglGenCylinder(100, 100, 500, RColor(255, 0, 0));
	 objList.back().setPosition(RVector3f(-250, 0, 0));
	 objList.back().setRotation(RVector3f(90, 0, 0));
	 objList.back().physicalObject = phy->applyPhysics(&objList.back(), RSHAPE_CYLINDER,
	 1);

	 //	phy->createJoint(objList[1].physicalObject,objList[2].physicalObject,RVector3f(0,0,0),RVector3f(0,0,1));
	 //	phy->jointList.push_back(btHingeConstraint(objList[1].physicalObject, btTransform(btQuaternion(0,0,0,1),btVector3(0,0,1)),true));

	 //Obstacle 1
	 objList.push_back(REntity());
	 objList.back().triMesh = rglGenCylinder(30, 200, 500, RColor(255, 0, 0));
	 objList.back().setPosition(RVector3f(-650, 0, 0));
	 objList.back().setRotation(RVector3f(90, 0, 0));
	 objList.back().physicalObject = phy->applyPhysics(&objList.back(), RSHAPE_CYLINDER,
	 5);

	 //Obstacle 2
	 objList.push_back(REntity());
	 objList.back().triMesh = rglGenBox(400, 10, 300, RColor(0, 0, 255));
	 objList.back().setPosition(RVector3f(-600, 100, 0));
	 objList.back().physicalObject = phy->applyPhysics(&objList.back(), RSHAPE_BOX, 1);

	 //Obstacle 3
	 objList.push_back(REntity());
	 objList.back().triMesh = rglGenCone(200, 600, 300, RColor(0, 0, 255));
	 objList.back().setPosition(RVector3f(-3000, 100, 0));
	 objList.back().setRotation(RVector3f(180, 0, 0));
	 objList.back().physicalObject = phy->applyPhysics(&objList.back(), RSHAPE_CONE, 5);
	 */
	//boxes
	for (int k = 0; k < 5; k++) {
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < 10aa; i++) {
				objList.push_back(REntity());
				objList.back().triMesh = rglGenBox(50, 50, 50,
						RColor(255*k/9, 255*j/9, (255 * i / 9)));
				objList.back().setPosition(
						RVector3f(-1000+k*-100, i * 200, (j - 2) * 100));
				objList.back().physicalObject = phy->applyPhysics(
						&objList.back(), RSHAPE_BOX, 1);
			}
		}
	}

}

#include "RString.h"

void Game::logic() {
	if (mouse().left.isDown) {
		wheel->physicalObject->getRigidBody()->setActivationState(true);
		//objList[1].physicalObject->getRigidBody()->applyCentralImpulse(
		//btVector3(0, 10, 0));
		wheel->physicalObject->getRigidBody()->applyCentralImpulse(
				btVector3(-10, 0, 0));
		wheel->physicalObject->getRigidBody()->applyTorqueImpulse(
				btVector3(0, 0, 500));
	}
	if (mouse().right.down) {
		objList.push_back(REntity());
		objList.back().triMesh = rglGenSphere(50, 10, RColor(0, 0, 255));
		objList.back().setPosition(
				RVector3f(wheel->getPosition().x() - camx, camy, 1000));
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
		camx += 10;
	}
	if (key(SDLK_d).isDown) {
		camx -= 10;
	}
	if (key(SDLK_s).isDown) {
		camy -= 10;
	}
	if (key(SDLK_w).isDown) {
		camy += 10;
	}
}

void Game::render() {
	camera.setPosition(
			RVector3f(-wheel->getPosition().x() + camx, -camy, -400));
	rglSetMatrix(camera.getAbsoluteTransformation());
	RGLText txt("|cFF0000t|c00FF00este\n|rGravidade: 9.8", 25,
			wheel->getPosition().x() - 300, wheel->getPosition().y() + 300,
			wheel->getPosition().z(), 1);
	txt.setColor(1, 1, 1);
	txt.draw();
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
