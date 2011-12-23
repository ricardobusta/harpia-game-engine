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
#include <Vehicle.h>

Game::Game() {
}

Game::~Game() {
}

void Game::init() {
	srand(time(0));
	camx = 0;
	camy = 0;
	phy->setGravity(9.8);

	float gamedepth = 100;

	REntity *ent;

	Vehicle veh(this);
	veh.buildVehicle(1, rand() % 400 + 100, 1, rand() % 400 + 100, 1,
			rand() % 400 + 100, 1, rand() % 400 + 100, 1, rand() % 400 + 100, 1,
			rand() % 400 + 100, 1, rand() % 400 + 100, 1, rand() % 400 + 100,/*rand()%8*/0,rand()%100+100,0,/*rand()%8*/2,rand()%100+100,0);
	wheel0 = veh.wheel0;
	wheel1 = veh.wheel1;
	body = veh.body;

	//Floor
	ent = newEntity();
	ent->setPosition(0, -200, 0);
	ent->setBoxMesh(10000, 100, gamedepth, RColor(0, 255, 0));
	ent->setBoxPhysics(0);

	//wall1
	//Floor
	ent = newEntity();
	ent->setPosition(5000, 0, 0);
	ent->setBoxMesh(50, 5000, gamedepth, RColor(0, 255, 0));
	ent->setBoxPhysics(0);

	//wall2
	ent = newEntity();
	ent->setPosition(-5000, 2000, 0);
	ent->setBoxMesh(50, 5000, gamedepth, RColor(0, 255, 0));
	ent->setBoxPhysics(0);

//	//Wheel 1
//	wheel1 = newEntity();
//	wheel1->setPosition(10, 0, 0);
//	wheel1->setRotation(90, 0, 0);
//	wheel1->setCylinderMesh(100, gamedepth, 20, RColor(255, 255, 255));
//	wheel1->setCylinderPhysics(1);
//	wheel1->set2DXYPhysics();
//
//	//Wheel 2
//	wheel2 = newEntity();
//	wheel2->setPosition(-250, 0, 0);
//	wheel2->setRotation(90, 0, 0);
//	wheel2->setCylinderMesh(100, gamedepth, 20, RColor(200, 200, 200));
//	wheel2->setCylinderPhysics(1);
//	wheel2->set2DXYPhysic//s();
//
//	//vehicle center
//	center = newEntity();
//	center->setPosition(0, 0, 0);
//	center->setRotation(180, 0, 0);
//	center->setBoxMesh(300, 50, gamedepth + 2, RColor(255, 255, 255));
//	center->setBoxPhysics(1);
//	center->set2DXYPhysics();

	//	phy->createJoint(objList[1].physicalObject,objList[2].physicalObject,RVector3f(0,0,0),RVector3f(0,0,1));
	//	phy->jointList.push_back(btHingeConstraint(objList[1].physicalObject, btTransform(btQuaternion(0,0,0,1),btVector3(0,0,1)),true));

	//Obstacle 1
	ent = newEntity();
	ent->setPosition(-650, 0, 0);
	ent->setRotation(90, 0, 0);
	ent->setCylinderMesh(30, gamedepth, 50, RColor(255, 0, 0));
	ent->setCylinderPhysics(5);
	ent->set2DXYPhysics();
	//
	//Obstacle 2
	ent = newEntity();
	ent->setPosition(-600, 100, 0);
	ent->setBoxMesh(400, 10, gamedepth, RColor(0, 0, 255));
	ent->setBoxPhysics(1);
	ent->set2DXYPhysics();

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
			ent = newEntity();
			ent->setPosition(-1000 + k * -100, i * 100, 0);
			ent->setBoxMesh(50, 50, gamedepth,
					RColor(255 * k / 4, 255 * 4 / 4, (255 * i / 9)));
			ent->setBoxPhysics(1);
			//			ent->set2DXYPhysics();
			ent->physicalObject->getRigidBody()->setActivationState(false);
		}
	}

//	wheel1->addPointConstraint(RVector3f(0, 0, 0), center,
//			RVector3f(150, 0, 0));
//	wheel2->addPointConstraint(RVector3f(0, 0, 0), center,
//			RVector3f(-150, 0, 0));
}

#include "RString.h"

void Game::logic() {
	REntity* ent;

	if (key(SDLK_LEFT).isDown) {
		wheel0->physicalObject->getRigidBody()->setActivationState(true);
		wheel1->physicalObject->getRigidBody()->setActivationState(true);
		wheel0->physicalObject->getRigidBody()->applyTorqueImpulse(
				btVector3(0, 0, 500));
		wheel1->physicalObject->getRigidBody()->applyTorqueImpulse(
				btVector3(0, 0, 500));
		body->physicalObject->getRigidBody()->applyCentralForce(
				btVector3(-1, 0, 0));
	}
	if (key(SDLK_RIGHT).isDown) {
		wheel0->physicalObject->getRigidBody()->setActivationState(true);
		wheel1->physicalObject->getRigidBody()->setActivationState(true);
		wheel0->physicalObject->getRigidBody()->applyTorqueImpulse(
				btVector3(0, 0, -500));
		wheel1->physicalObject->getRigidBody()->applyTorqueImpulse(
				btVector3(0, 0, -500));
		body->physicalObject->getRigidBody()->applyCentralForce(
				btVector3(1, 0, 0));
	}
	if (key(SDLK_UP).isDown) {
		body->physicalObject->getRigidBody()->setActivationState(true);
		body->physicalObject->getRigidBody()->applyCentralImpulse(
				btVector3(0, 100, 0));

	}
	if (key(SDLK_DOWN).isDown) {
		body->physicalObject->getRigidBody()->setActivationState(true);
		body->physicalObject->getRigidBody()->applyCentralImpulse(
				btVector3(0, -100, 0));

	}
	if (mouse().left.down) {
		ent = newEntity();
		ent->setPosition(
				-camera.getPosition().x()
				+ (mouse().position.x() - sdl.getWidth() / 2),
				-camera.getPosition().y() - mouse().position.y()
				+ sdl.getHeight() / 2, -camera.getPosition().z() + 500);
		ent->setSphereMesh(50, 4, RColor(255, 255, 0));
		ent->setSpherePhysics(1);
		ent->physicalObject->getRigidBody()->applyCentralImpulse(
				btVector3(0, 10, -500));
		//objList[0].physicalObject->getRigidBody()->setActivationState(true);
		//objList[0].physicalObject->getRigidBody()->setMassProps(1,btVector3(0,0,0));
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
			RVector3f(-body->getPosition().x() + camx,
					-body->getPosition().y() - camy, -1000));
	rglSetMatrix(camera.getAbsoluteTransformation());
}
