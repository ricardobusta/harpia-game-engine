/*
 * RPoint3f.cpp
 *
 *  Created on: Jul 14, 2011
 *      Author: Ricardo Bustamante de Queiroz
 *      e-mail: ricardobqueiroz@gmail.com
 */

#include "RPoint3f.h"

RPoint3f::RPoint3f() {
	// TODO Auto-generated constructor stub
	x_ = 0;
	y_ = 0;
	z_ = 0;
}

RPoint3f::RPoint3f(float x, float y, float z) {
	x_ = x;
	y_ = y;
	z_ = z;
}

RPoint3f::~RPoint3f() {
	// TODO Auto-generated destructor stub
}

float RPoint3f::x() {
	return (x_);
}

float RPoint3f::y() {
	return (y_);
}

float RPoint3f::z() {
	return (z_);
}

void RPoint3f::set(float x, float y, float z) {
	x_ = x;
	y_ = y;
	z_ = z;
}

void RPoint3f::setX(float x) {
	x_ = x;
}

void RPoint3f::setY(float y) {
	y_ = y;
}

void RPoint3f::setZ(float z) {
	z_ = z;
}

float RPoint3f::norm(){
	return ((*this)*(*this));
}

RPoint3f RPoint3f::unit()
{
	return ((*this)/norm());
}

vector<float> RPoint3f::getVector() {
	vector<float> v;
	v.push_back(x_);
	v.push_back(y_);
	v.push_back(z_);
	return (v);
}

bool RPoint3f::operator ==(RPoint3f p) {
	if (x_ == p.x_ and y_ == p.y_ and z_ == p.z_)
		return (true);
	return (false);
}

RPoint3f RPoint3f::operator =(RPoint3f p) {
	x_ = p.x_;
	y_ = p.y_;
	z_ = p.z_;

	return (*this);
}

RPoint3f RPoint3f::operator +(RPoint3f rPoint3f) {
	RPoint3f r;
	//TODO
	return r;
}

RPoint3f RPoint3f::operator -(RPoint3f rPoint3f) {
	RPoint3f r;
	//TODO
	return r;
}

float RPoint3f::operator *(RPoint3f p) {
	return ((x_*p.x_) + (y_*p.y_) + (z_*p.z_));
}

RPoint3f RPoint3f::operator ^(RPoint3f rPoint3f) {
	RPoint3f r;
	//TODO
	return r;
}

RPoint3f RPoint3f::operator *(float float1) {
	RPoint3f r;
	//TODO
	return r;
}

RPoint3f RPoint3f::operator /(float float1) {
	RPoint3f r;
	//TODO
	return r;
}

bool RPoint3f::compare(RPoint3f rPoint3f) {
	RPoint3f r;
	//TODO
	return true;
}

RPoint3f RPoint3f::set(RPoint3f rPoint3f) {
	RPoint3f r;
	//TODO
	return r;
}

RPoint3f RPoint3f::add(RPoint3f rPoint3f) {
	RPoint3f r;
	//TODO
	return r;
}

RPoint3f RPoint3f::subtract(RPoint3f rPoint3f) {
	RPoint3f r;
	//TODO
	return r;
}

RPoint3f RPoint3f::dotProduct(RPoint3f rPoint3f) {
	RPoint3f r;
	//TODO
	return r;
}

RPoint3f RPoint3f::crossProduct(RPoint3f rPoint3f) {
	RPoint3f r;
	//TODO
	return r;
}

RPoint3f RPoint3f::multiply(float float1) {
	RPoint3f r;
	//TODO
	return r;
}

RPoint3f RPoint3f::divide(float float1) {
	RPoint3f r;
	//TODO
	return r;
}

