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

Game::Game() {
}

Game::~Game() {
}

void Game::init() {
	cam.setZ(1);

//	REntity* e;
//
//	e = newEntity();
//	//e->triMesh = rglGenBox(200, 200, 200, RColor(0.1f, 0.1f, 0.9f));
//	e->triMesh = rglGenCapsule(10,20,10,RColor(255,255,0));
//	e->setPosition(RVector3f(0,0,0));
//
////	e->physicalObject = phy->applyPhysics(e,RSHAPE_BOX,0.1);
//
//	e = newEntity();
//	e->triMesh = rglGenCapsule(50,100,10,RColor(255,0,255));
//	e->setPosition(RVector3f(0,200,0));
//
////	e->physicalObject = phy->applyPhysics(e,RSHAPE_BOX,0.1);
//
//	e = newEntity();
//	e->triMesh = rglGenCapsule(50,100,10,RColor(0,255,255));
//	e->setPosition(RVector3f(0,-200,0));
//
//	e->physicalObject = phy->applyPhysics(e,RSHAPE_BOX,0.1);


	objList.push_back(REntity());
	objList.push_back(REntity());
	objList.push_back(REntity());

	objList[0].triMesh = rglGenBox(200, 20, 200, RColor(0.1f, 0.1f, 0.9f));
	objList[0].setPosition(RVector3f(0,0,0));
	objList[1].physicalObject = phy->applyPhysics(&objList[0],RSHAPE_BOX,1);
	objList[1].physicalObject->getRigidBody()->applyCentralForce(btVector3(0,50,0));
	objList[1].triMesh = rglGenCapsule(50,100,10,RColor(255,255,255));
	objList[1].setPosition(RVector3f(0,200,0));
	objList[1].physicalObject = phy->applyPhysics(&objList[1],RSHAPE_BOX,1);
	objList[2].triMesh = rglGenCapsule(50,100,10,RColor(255,255,255));
	objList[2].setPosition(RVector3f(0,-200,0));
	objList[2].physicalObject = phy->applyPhysics(&objList[2],RSHAPE_BOX,1);
}

#include "RString.h"

void Game::logic() {
	if (mouse().left.isDown) {
//		objList[0].rotation.setY(objList[0].rotation.y()+mouse().speed.x());
//		objList[0].rotation.setX(objList[0].rotation.x()+mouse().speed.y());

	}
	if(mouse().right.isDown){
//		objList[1].rotation.setY(objList[1].rotation.y()+mouse().speed.x());
//		objList[1].rotation.setX(objList[1].rotation.x()+mouse().speed.y());
	}
	if (key(SDLK_EQUALS).isDown) {
//	if(mouse().wheelup.isDown){
//		objList[0].scale*1.01;
	}
	if (key(SDLK_MINUS).isDown) {
//	if(mouse().wheeldown.isDown){
//		objList[0].scale*0.99;
	}

//	obj.frame.setIdentity();
	//objList[0].position = RVector3f(200, 0, 0);
	//objList[1].position = RVector3f(-200, 0, 0);
//	obj.frame.rotate(cam.x(), 1, 0, 0);
//	obj.frame.rotate(cam.y(), 0, 1, 0);
//	obj.frame.scale(cam.z(), cam.z(), cam.z());
}

void Game::render() {
	glLoadIdentity();
	RGLText txt("|cFF0000t|c00FF00este\n|rteste",50,0,300,200,1);
	txt.setColor(1,1,1);
	txt.draw();
	for(unsigned int i=0;i<objList.size();i++){
		glLoadMatrixf(objList[i].getAbsoluteTransformation().gl());
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
