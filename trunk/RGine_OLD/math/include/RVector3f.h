/*
 * RVector3f.h
 *
 *  Created on: Jul 14, 2011
 *      Author: Ricardo Bustamante de Queiroz
 *      e-mail: ricardobqueiroz@gmail.com
 */

#ifndef RVECTOR3F_H_
#define RVECTOR3F_H_

//TODO finish this class

#include <vector>
using namespace std;

/**
 * 3D float coordinate vector.
 */
class RVector3f {
public:
	/**
	 * Constructor.
	 */
	RVector3f();

	/**
	 * Destructor.
	 */
	virtual ~RVector3f();

	/**
	 * Constructor. Will create a vector with 3 given coordinates.
	 *
	 * @param x X Coordinate.
	 * @param y Y Coordinate.
	 * @param z Z coordinate.
	 */
	RVector3f(float x, float y, float z);

	float x() const;
	float y() const;
	float z() const;

	void setX(float x); //TODO
	void setY(float y); //TODO
	void setZ(float z); //TODO
	void set(float x, float y, float z);

	vector<float> getVector(); //todo replace x,y,z w/ vector

	float norm();
	RVector3f unit();

	//Operators
	bool operator==(RVector3f); //TODO
	RVector3f operator=(RVector3f); //TODO
	RVector3f operator+(RVector3f); //TODO
	RVector3f operator-(RVector3f); //TODO
	float operator*(RVector3f); //TODO
	RVector3f operator^(RVector3f); //TODO
	RVector3f operator*(float); //TODO
	RVector3f operator/(float); //TODO

	//Operators methods
	bool compare(RVector3f);
	RVector3f set(RVector3f);
	RVector3f add(RVector3f);
	RVector3f subtract(RVector3f);
	RVector3f dotProduct(RVector3f);
	RVector3f crossProduct(RVector3f);
	RVector3f multiply(float);
	RVector3f divide(float);
private:
	float x_;
	float y_;
	float z_;
};

#endif /* RVECTOR3F_H_ */
