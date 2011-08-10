/*
 * RPoint3f.cpp
 *
 *  Created on: Jul 14, 2011
 *      Author: Ricardo Bustamante de Queiroz
 *      e-mail: ricardobqueiroz@gmail.com
 */

#include "RVector3f.h"

RVector3f::RVector3f() {
	// TODO Auto-generated constructor stub
	x_ = 0;
	y_ = 0;
	z_ = 0;
}

RVector3f::RVector3f(float x, float y, float z) {
	x_ = x;
	y_ = y;
	z_ = z;
}

RVector3f::~RVector3f() {
	// TODO Auto-generated destructor stub
}

float RVector3f::x() const {
	return (x_);
}

float RVector3f::y() const {
	return (y_);
}

float RVector3f::z() const {
	return (z_);
}

void RVector3f::set(float x, float y, float z) {
	x_ = x;
	y_ = y;
	z_ = z;
}

void RVector3f::setX(float x) {
	x_ = x;
}

void RVector3f::setY(float y) {
	y_ = y;
}

void RVector3f::setZ(float z) {
	z_ = z;
}

float RVector3f::norm(){
	return ((*this)*(*this));
}

RVector3f RVector3f::unit()
{
	return ((*this)/norm());
}

vector<float> RVector3f::getVector() {
	vector<float> v;
	v.push_back(x_);
	v.push_back(y_);
	v.push_back(z_);
	return (v);
}

bool RVector3f::operator ==(RVector3f p) {
	if (x_ == p.x_ and y_ == p.y_ and z_ == p.z_)
		return (true);
	return (false);
}

RVector3f RVector3f::operator =(RVector3f p) {
	x_ = p.x_;
	y_ = p.y_;
	z_ = p.z_;

	return (*this);
}

RVector3f RVector3f::operator +(RVector3f p) {
	RVector3f r;
	r.x_ = x_ + p.x_;
	r.x_ = y_ + p.y_;
	r.x_ = z_ + p.z_;
	return (r);
}

RVector3f RVector3f::operator -(RVector3f p) {
	RVector3f r;
	r.x_ = x_ - p.x_;
	r.x_ = y_ - p.y_;
	r.x_ = z_ - p.z_;
	return (r);
}

float RVector3f::operator *(RVector3f p) {
	return ((x_*p.x_) + (y_*p.y_) + (z_*p.z_));
}

RVector3f RVector3f::operator ^(RVector3f rPoint3f) {
	RVector3f r;
	//r.x_ = x_ + rPoint3f.x_;
	//r.x_ = y_ + rPoint3f.y_;
	//r.x_ = z_ + rPoint3f.z_;
	return (r);
}

RVector3f RVector3f::operator *(float f) {
	RVector3f r;
	r.x_ = x_ * f;
	r.x_ = y_ * f;
	r.x_ = z_ * f;
	return (r);
}

RVector3f RVector3f::operator /(float f) {
	RVector3f r;
	r.x_ = x_ / f;
	r.x_ = y_ / f;
	r.x_ = z_ / f;
	return (r);
}

bool RVector3f::compare(RVector3f p) {
	if(x_ == p.x_ and y_ == p.y_ and z_ == p.z_)
		return (true);
	else
		return (false);
}

RVector3f RVector3f::set(RVector3f p) {
	RVector3f r;
	//TODO
	return (r);
}

RVector3f RVector3f::add(RVector3f p) {
	RVector3f r;
	//TODO
	return (r);
}

RVector3f RVector3f::subtract(RVector3f rPoint3f) {
	RVector3f r;
	//TODO
	return (r);
}

RVector3f RVector3f::dotProduct(RVector3f rPoint3f) {
	RVector3f r;
	//TODO
	return (r);
}

RVector3f RVector3f::crossProduct(RVector3f rPoint3f) {
	RVector3f r;
	//TODO
	return (r);
}

RVector3f RVector3f::multiply(float float1) {
	RVector3f r;
	//TODO
	return (r);
}

RVector3f RVector3f::divide(float float1) {
	RVector3f r;
	//TODO
	return (r);
}

