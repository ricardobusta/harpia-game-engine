/*
 * RFrame.h
 *
 *  Created on: Jul 16, 2011
 *      Author: ricardo
 */

#ifndef RFRAME_H_
#define RFRAME_H_

#include "RVector3f.h"

#include "RMatrix4f.h"

/**
 * Class that stores transformation state in a 4x4 matrix, like opengl.
 * Can keep track of position, scale, rotation etc.
 */
class RFrame {
public:
	RFrame();
	virtual ~RFrame();

	/**
	 * Set the matrix to be the identity matrix.
	 */
	void setIdentity();

	/**
	 * Set the current position.
	 *
	 * @param x Position x coordinate.
	 * @param y Position y coordinate.
	 * @param z Position z coordinate.
	 */
	void setPosition(float x, float y, float z);

	/**
	 * Move the frame location.
	 *
	 * @param x Movement x magnitude.
	 * @param y Movement y magnitude.
	 * @param z Movement z magnitude.
	 */
	void move(float x, float y, float z);

	/**
	 * Scale the frame.
	 *
	 * @param x Scale x magnitude.
	 * @param y Scale y magnitude.
	 * @param z Scale z magnitude.
	 */
	void scale(float x, float y, float z);

	/**
	 * Rotate the frame around a given vector.
	 *
	 * @param angle Angle of rotation.
	 * @param x X coordinate of the rotation axis.
	 * @param y Y coordinate of the rotation axis.
	 * @param z Z coordinate of the rotation axis.
	 */
	void rotate(float angle, float x, float y, float z);

	/**
	 * Get the frame 4x4 matrix for opengl commands.
	 *
	 * @return The 4x4 matrix ready to be used with opengl commands.
	 */
	float* getTransformation();

	/**
	 * Get the frame 4x4 matrix structure.
	 * @return The RMatrix4f structure.
	 */
	RMatrix4f getMatrix();
private:
	/**
	 * Data structure where the transformations are saved.
	 */
	RMatrix4f matrix;
};

#endif /* RFRAME_H_ */
