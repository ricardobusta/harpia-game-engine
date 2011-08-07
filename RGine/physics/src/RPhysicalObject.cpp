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
 * File: RPhysicalObject.cpp
 * Created on: Aug 5, 2011
 */

#include "RPhysicalObject.h"

#include <RVector3f.h>
#include <cmath>

RPhysicalObject::RPhysicalObject(REntity* entity, double mass) {
    this->mass = mass;
    this->entity = entity;
}

void RPhysicalObject::initializeTerrain(btCollisionShape* shape, btDefaultMotionState* motionState) {
    this->shape = shape;
    this->motionState = motionState;

    btVector3 inertia = btVector3(0,0,0);
    this->shape->calculateLocalInertia(0.0, inertia);
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0.0, motionState, this->shape, inertia);
    this->rigidBody = new btRigidBody(rigidBodyCI);
}

void RPhysicalObject::initialize(btCollisionShape* shape) {
    RVector3f pos, rotation;
    pos = entity->position;//irrnode->getPosition();
    rotation = entity->rotation;//irrnode->getRotation();
    btQuaternion rot;
    rot.setEuler(rotation.y()*M_PI/180.0, rotation.x()*M_PI/180.0, rotation.z()*M_PI/180.0);

    this->shape = shape;

    btTransform trans;
    trans.setIdentity();

    trans.setRotation(rot);
    trans.setOrigin(btVector3(pos.x(), pos.y(), pos.z()));

    this->motionState = new btDefaultMotionState(trans);
    btScalar m = this->mass;
    btVector3 inertia(0,0,0);
    this->shape->calculateLocalInertia(m, inertia);
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(m, this->motionState, this->shape, inertia);
    this->rigidBody = new btRigidBody(rigidBodyCI);

    this->rigidBody->setCenterOfMassTransform(trans);
}

RPhysicalObject::~RPhysicalObject() {
    //entity->remove();
    delete rigidBody->getMotionState();
    delete rigidBody;
    delete shape;
}

void RPhysicalObject::update() {
    btVector3 pos = rigidBody->getCenterOfMassPosition();
    btQuaternion rot = rigidBody->getOrientation();
    btVector3 eulerRot;

    btScalar W = rot.getW();
    btScalar X = rot.getX();
    btScalar Y = rot.getY();
    btScalar Z = rot.getZ();
    float WSquared = W * W;
    float XSquared = X * X;
    float YSquared = Y * Y;
    float ZSquared = Z * Z;

    eulerRot.setX(atan2(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
    eulerRot.setY(asin(-2.0f * (X * Z - Y * W)));
    eulerRot.setZ(atan2(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));

    eulerRot.setX( eulerRot.x()*180.0/M_PI );
    eulerRot.setY( eulerRot.y()*180.0/M_PI );
    eulerRot.setZ( eulerRot.z()*180.0/M_PI );

    if(entity != NULL) {
        entity->position = RVector3f(pos.x(), pos.y(), pos.z());
        entity->rotation = RVector3f(eulerRot.x(), eulerRot.y(), eulerRot.z());
    }
}

btRigidBody* RPhysicalObject::getRigidBody() {
    return (rigidBody);
}

REntity* RPhysicalObject::getEntity() {
    return (entity);
}

RVector3f RPhysicalObject::getScale() {
    return (entity->scale);
}

RVector3f RPhysicalObject::getPosition() {
    return (entity->position);
}

RVector3f RPhysicalObject::getRotation() {
    return (entity->rotation);
}

RMatrix4f RPhysicalObject::getAbsoluteTransformation() {
    return (entity->getAbsoluteTransformation());
}

float RPhysicalObject::getAngularVel() {
    btVector3 vel =	rigidBody->getAngularVelocity();

    return (vel.length());
}

float RPhysicalObject::getLinearVel() {
    btVector3 vel =	rigidBody->getLinearVelocity();

    return (vel.length());
}

void RPhysicalObject::setRestitution(float c) {
    rigidBody->setRestitution(c);
}

void RPhysicalObject::setFriction(float c) {
    rigidBody->setFriction(c);
}

void RPhysicalObject::setAngularDamping(float damp) {
    btScalar lin = rigidBody->getLinearDamping();
    rigidBody->setDamping(lin, damp);
}

void RPhysicalObject::setLinearDamping(float damp) {
    btScalar ang = rigidBody->getAngularDamping();
    rigidBody->setDamping(damp, ang);
}

bool RPhysicalObject::isColliding(RPhysicalObject* obj) {
    return (rigidBody->checkCollideWith(obj->getRigidBody()));
}
