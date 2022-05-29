/*
 * RPoint2i.h
 *
 *  Created on: Jul 14, 2011
 *      Author: Ricardo Bustamante de Queiroz
 *      e-mail: ricardobqueiroz@gmail.com
 */

#ifndef RPOINT2I_H_
#define RPOINT2I_H_

/**
 * 2D integer coordinate point.
 */
class RPoint2i {
public:
	RPoint2i();
	RPoint2i(int x, int y);
	virtual ~RPoint2i();

	int x();
	int y();

	void setX(int);
	void setY(int);
	void set(int x, int y);

	//Operators
	bool operator==(RPoint2i); //TODO
	RPoint2i operator=(RPoint2i); //TODO
	RPoint2i operator+(RPoint2i); //TODO
	RPoint2i operator-(RPoint2i); //TODO
	RPoint2i operator*(RPoint2i); //TODO
	RPoint2i operator^(RPoint2i); //TODO
	RPoint2i operator*(int); //TODO
	RPoint2i operator/(int); //TODO
private:
	int x_;
	int y_;
};

#endif /* RPOINT2I_H_ */
