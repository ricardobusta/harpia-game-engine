/*
 * RPoint2i.cpp
 *
 *  Created on: Jul 14, 2011
 *      Author: Ricardo Bustamante de Queiroz
 *      e-mail: ricardobqueiroz@gmail.com
 */

#include "RPoint2i.h"

RPoint2i::RPoint2i() :
x_(0), y_(0) {

}

RPoint2i::RPoint2i(int x, int y) :
				x_(x), y_(y) {
}

RPoint2i::~RPoint2i() {
}

int RPoint2i::x() {
	return (x_);
}

int RPoint2i::y() {
	return (y_);
}

void RPoint2i::setX(int x) {
	x_ = x;
}

void RPoint2i::setY(int y) {
	y_ = y;
}

void RPoint2i::set(int x, int y) {
	x_ = x;
	y_ = y;
}
