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
 * File: REntity.cpp
 * Created on: Aug 5, 2011
 */

#include "REntity.h"

#include <RFrame.h>
#include <RGLShapes.h>
#include <RGLCommands.h>
#include <RMain.h>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <RPhysicalJoint.h>

REntity::REntity() {
	hasMesh = false;
	hasPhysics = false;

	scale.set(1, 1, 1);
}

REntity::~REntity() {
}

void REntity::handle() {
}

void REntity::render() {
//		if(hasMesh){
	rglMultMatrix(getAbsoluteTransformation());
//	rglDrawTriMeshWired(triMesh);
//	rglDrawTriMesh(triMesh);
	rglDrawTriMeshWired(triMesh);
//		}
}

/*TODO if physics bug the issue might be here*/
RMatrix4f REntity::getAbsoluteTransformation() {
	RFrame f;
	f.rotate(rotation.z(), 0, 0, 1);
	f.rotate(rotation.y(), 0, 1, 0);
	f.rotate(rotation.x(), 1, 0, 0);

	f.move(position.x(), position.y(), position.z());
	f.scale(scale.x(), scale.y(), scale.z());
	return (f.getMatrix());
}

RVector3f REntity::getPosition() const {
	return (position);
}

RVector3f REntity::getRotation() const {
	return (rotation);
}

RVector3f REntity::getScale() const {
	return (scale);
}

void REntity::setPosition(RVector3f position) {
	this->position = position;
}

void REntity::setPosition(float x, float y, float z) {
	this->position = RVector3f(x, y, z);
}

void REntity::setRotation(RVector3f rotation) {
	this->rotation = rotation;
}

void REntity::setRotation(float x, float y, float z) {
	this->rotation = RVector3f(x, y, z);
}

void REntity::setScale(RVector3f scale) {
	this->scale = scale;
}

void REntity::setScale(float x, float y, float z) {
	this->scale = RVector3f(x, y, z);
}

RBoundingBox REntity::getBoundingBox() {
	RBoundingBox bbox;
	bbox.set(triMesh);
	return (bbox);
}

void REntity::setBoxMesh(float width, float height, float depth, RColor color) {
	//Make Mesh
	triMesh = rglGenBox(width, height, depth, color);
}

void REntity::setBoxPhysics(float mass) {
	//Make Physics
	physicalObject = parent->phy->applyPhysics(this, RSHAPE_BOX, mass);
}

void REntity::setCylinderMesh(float radius, float height, unsigned int div,
		RColor color) {
	//Make Mesh
	triMesh = rglGenCylinder(radius, height, div, color);
}

void REntity::setCylinderPhysics(float mass) {
	//Make Physics
	physicalObject = parent->phy->applyPhysics(this, RSHAPE_CYLINDER, mass);
}

void REntity::setSphereMesh(float radius, unsigned int div, RColor color) {
	//Make Mesh
	triMesh = rglGenSphere(radius, div, color);
}

void REntity::setSpherePhysics(float mass) {
	//Make Physics
	physicalObject = parent->phy->applyPhysics(this, RSHAPE_SPHERE, mass);
}

void REntity::setTriMesh(RTriMesh mesh) {
	triMesh = mesh;
}

void REntity::setTriMeshPhysics(float mass) {
	physicalObject = parent->phy->applyPhysics(this, RSHAPE_TRIMESH, mass);
}

void REntity::set2DXYPhysics() {
	physicalObject->getRigidBody()->setAngularFactor(btVector3(0, 0, 1));
	physicalObject->getRigidBody()->setLinearFactor(btVector3(1, 1, 0));
}

void REntity::set2DXZPhysics() {
	physicalObject->getRigidBody()->setAngularFactor(btVector3(0, 1, 0));
	physicalObject->getRigidBody()->setLinearFactor(btVector3(1, 0, 1));
}

void REntity::set2DYZPhysics() {
	physicalObject->getRigidBody()->setAngularFactor(btVector3(1, 0, 0));
	physicalObject->getRigidBody()->setLinearFactor(btVector3(0, 1, 1));
}

void REntity::set3DPhysics() {
	physicalObject->getRigidBody()->setAngularFactor(btVector3(1, 1, 1));
	physicalObject->getRigidBody()->setLinearFactor(btVector3(1, 1, 1));
}

void REntity::addPointConstraint(RVector3f v) {
	btPoint2PointConstraint* jt = new btPoint2PointConstraint(
			*physicalObject->getRigidBody(), btVector3(v.x(), v.y(), v.z()));
	parent->phy->dynamicsWorld->addConstraint(jt, true);
}

void REntity::addPointConstraint(RVector3f v, REntity *pair, RVector3f pv) {
	btPoint2PointConstraint* jt = new btPoint2PointConstraint(
			*physicalObject->getRigidBody(),
			*pair->physicalObject->getRigidBody(),
			btVector3(v.x(), v.y(), v.z()), btVector3(pv.x(), pv.y(), pv.z()));
	parent->phy->dynamicsWorld->addConstraint(jt, true);
}

