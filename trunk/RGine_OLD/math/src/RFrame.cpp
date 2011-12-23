/*
 * RFrame.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: ricardo
 */

#include "RFrame.h"

#include <RCommon.h>

#include <cmath>
#include <math.h>

RFrame::RFrame() {
	setIdentity();
}

RFrame::~RFrame() {
	// TODO Auto-generated destructor stub
}

float* RFrame::getTransformation() {
	return (matrix.data);
}

RMatrix4f RFrame::getMatrix(){
	return (matrix);
}

void RFrame::setIdentity() {
	for (int i = 0; i < 16; i++) {
		if (i % 5 == 0)
			matrix.data[i] = 1;
		else
			matrix.data[i] = 0;
	}
}

void RFrame::setPosition(float x, float y, float z) {
	matrix.data[12] = x;
	matrix.data[13] = y;
	matrix.data[14] = z;
}

void RFrame::rotate(float angle, float x, float y, float z) {
	float radangle = ((M_PI * angle) / 180);
	float c = cos(radangle);
	float s = sin(radangle);

	RMatrix4f opmatrix;
	opmatrix.data[0] = (x * x * (1 - c)) + c;
	opmatrix.data[1] = (y * x * (1 - c)) + (z * s);
	opmatrix.data[2] = (z * x * (1 - c)) - (y * s);
	opmatrix.data[3] = 0;

	opmatrix.data[4] = (x * y * (1 - c)) - (z * s);
	opmatrix.data[5] = (y * y * (1 - c)) + c;
	opmatrix.data[6] = (z * y * (1 - c)) + (x * s);
	opmatrix.data[7] = 0;

	opmatrix.data[8] = (x * z * (1 - c)) + (y * s);
	opmatrix.data[9] = (y * z * (1 - c)) - (x * s);
	opmatrix.data[10] = z * z * (1 - c) + c;
	opmatrix.data[11] = 0;

	opmatrix.data[12] = 0;
	opmatrix.data[13] = 0;
	opmatrix.data[14] = 0;
	opmatrix.data[15] = 1;

	matrix = matrix*opmatrix;
}

void RFrame::scale(float x, float y, float z) {
	RMatrix4f opmatrix;
	opmatrix.data[0] = x;

	opmatrix.data[5] = y;

	opmatrix.data[10] = z;

	opmatrix.data[15] = 1;

	matrix = matrix*opmatrix;
}

void RFrame::move(float x, float y, float z) {
	matrix.data[12] += x;
	matrix.data[13] += y;
	matrix.data[14] += z;
}
