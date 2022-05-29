/*
 * RColor.cpp
 *
 *  Created on: Jul 15, 2011
 *      Author: ricardo
 */

#include "RColor.h"

RColor::RColor() {
	r_ = 255;
	g_ = 255;
	b_ = 255;
}

RColor::~RColor() {

}

RColor::RColor(int r, int g, int b) {
	r_ = r;
	g_ = g;
	b_ = b;
}

RColor::RColor(float r, float g, float b) {
	r_ = (int) (r * 255.0);
	g_ = (int) (g * 255.0);
	b_ = (int) (b * 255.0);
}

int RColor::r() {
	return (r_);
}

int RColor::g() {
	return (g_);
}

int RColor::b() {
	return (b_);
}

void RColor::setR(int r) {
	r_ = r;
}

void RColor::setG(int g) {
	g_ = g;
}

void RColor::setB(int b) {
	b_ = b;
}

void RColor::setR(float r) {
	r_ = (r * 255);
}

void RColor::setG(float g) {
	g_ = (g * 255);
}

void RColor::setB(float b) {
	b_ = (b * 255);
}

float RColor::rF() {
	return (r_ / 255.0f);
}

float RColor::gF() {
	return (g_ / 255.0f);
}

float RColor::bF() {
	return (b_ / 255.0f);
}

