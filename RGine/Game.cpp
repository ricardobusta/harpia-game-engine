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

	phy->setGravity(9.8);

	objList.push_back(REntity());
	objList.push_back(REntity());
	objList.push_back(REntity());
	objList.push_back(REntity());
	objList.push_back(REntity());
	objList.push_back(REntity());
	objList.push_back(REntity());
	objList.push_back(REntity());
	objList.push_back(REntity());
	objList.push_back(REntity());
	objList.push_back(REntity());
	objList.push_back(REntity());

	//Floor
	objList[0].triMesh = rglGenBox(5000, 100, 500, RColor(0, 255, 0));
	objList[0].setPosition(RVector3f(-2500, -400, 0));
	objList[0].physicalObject = phy->applyPhysics(&objList[0], RSHAPE_BOX, 0);

	//Wheel 1
	objList[1].triMesh = rglGenCylinder(100, 100, 500, RColor(255, 0, 0));
	objList[1].setPosition(RVector3f(0, 0, 0));
	objList[1].setRotation(RVector3f(90, 0, 0));
	objList[1].physicalObject = phy->applyPhysics(&objList[1], RSHAPE_CYLINDER,
			1);

	//Wheel 2
	objList[5].triMesh = rglGenCylinder(100, 100, 500, RColor(255, 0, 0));
	objList[5].setPosition(RVector3f(-250, 0, 0));
	objList[5].setRotation(RVector3f(90, 0, 0));
	objList[5].physicalObject = phy->applyPhysics(&objList[5], RSHAPE_CYLINDER,
			1);

//	phy->createJoint(objList[1].physicalObject,objList[2].physicalObject,RVector3f(0,0,0),RVector3f(0,0,1));
//	phy->jointList.push_back(btHingeConstraint(objList[1].physicalObject, btTransform(btQuaternion(0,0,0,1),btVector3(0,0,1)),true));

	//Obstacle 1
	objList[2].triMesh = rglGenCylinder(30, 200, 500, RColor(255, 0, 0));
	objList[2].setPosition(RVector3f(-650, 0, 0));
	objList[2].setRotation(RVector3f(90, 0, 0));
	objList[2].physicalObject = phy->applyPhysics(&objList[2], RSHAPE_CYLINDER,
			5);

	//Obstacle 2
	objList[3].triMesh = rglGenBox(400, 10, 300, RColor(0, 0, 255));
	objList[3].setPosition(RVector3f(-600, 100, 0));
	objList[3].physicalObject = phy->applyPhysics(&objList[3], RSHAPE_BOX, 1);

	//Obstacle 3
	objList[4].triMesh = rglGenCone(200, 600, 300, RColor(0, 0, 255));
	objList[4].setPosition(RVector3f(-3000, 100, 0));
	objList[4].setRotation(RVector3f(180, 0, 0));
	objList[4].physicalObject = phy->applyPhysics(&objList[4], RSHAPE_CONE, 5);

	//boxes
	for (int i = 6; i < 12; i++) {
		objList[i].triMesh = rglGenBox(50, 50, 300,
				RColor(0, 255 - (80 * (i - 5)), 80 * (i - 5)));
		objList[i].setPosition(RVector3f(-2500, i * 200, 0));
		objList[i].physicalObject = phy->applyPhysics(&objList[i], RSHAPE_BOX,
				1);
	}
}

#include "RString.h"

void Game::logic() {
	if (mouse().left.isDown) {
		objList[1].physicalObject->getRigidBody()->setActivationState(true);
		//objList[1].physicalObject->getRigidBody()->applyCentralImpulse(
		//btVector3(0, 10, 0));
		objList[1].physicalObject->getRigidBody()->applyCentralImpulse(
				btVector3(-10, 0, 0));
		objList[1].physicalObject->getRigidBody()->applyTorqueImpulse(
				btVector3(0, 0, 500));
	}
	if (mouse().right.down) {
		//objList[0].physicalObject->getRigidBody()->setActivationState(true);
		//objList[0].physicalObject->getRigidBody()->setMassProps(1,btVector3(0,0,0));
	}
	if (key(SDLK_EQUALS).isDown) {
	}
	if (key(SDLK_MINUS).isDown) {
	}
}

void Game::render() {
	camera.setPosition(-objList[1].getPosition().x(), 0, -300);
	rglSetMatrix(camera.getMatrix());
	RGLText txt("|cFF0000t|c00FF00este\n|rGravidade: 9.8", 25,
			objList[1].getPosition().x() - 300,
			objList[1].getPosition().y() + 300, objList[1].getPosition().z(),
			1);
	txt.setColor(1, 1, 1);
	txt.draw();
	for (unsigned int i = 0; i < objList.size(); i++) {
		rglSetMatrix(camera.getMatrix());
		//glMultMatrixf(objList[i].getAbsoluteTransformation().gl());
		objList[i].render();
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
