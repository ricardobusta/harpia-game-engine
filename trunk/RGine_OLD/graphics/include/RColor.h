/*
 * RColor.h
 *
 *  Created on: Jul 15, 2011
 *      Author: ricardo
 */

/*
 * Color data structure.
 */

#ifndef RCOLOR_H_
#define RCOLOR_H_

/**
 * Color data structure. Will store red, green and blue values and will convert
 * if necessary.
 */
class RColor {
public:
	/**
	 * Constructor.
	 */
	RColor();

	/**
	 * Constuctor. Build a color object with the given colors.
	 *
	 * @param r
	 * @param g
	 * @param b
	 */
	RColor(int r, int g, int b);

	/**
	 * Constuctor. Build a color object with the given colors.
	 *
	 * @param r
	 * @param g
	 * @param b
	 */
	RColor(float r, float g, float b);

	/**
	 * Destructor
	 */
	virtual ~RColor();

	/**
	 * Get the integer value of the red component of the color.
	 *
	 * @return A value [0,255].
	 */
	int r();

	/**
	 * Get the integer value of the green component of the color.
	 *
	 * @return A value [0,255].
	 */
	int g();

	/**
	 * Get the integer value of the blue component of the color.
	 *
	 * @return A value [0,255].
	 */

	int b();

	/**
	 * Set the value of the red component of the color.
	 *
	 * @return A value [0,255].
	 */
	void setR(int r);

	/**
	 * Set the value of the green component of the color.
	 *
	 * @return A value [0,255].
	 */
	void setG(int g);

	/**
	 * Set the value of the blue component of the color.
	 *
	 * @return A value [0,255].
	 */
	void setB(int b);

	/**
	 * Get the float value of the red component of the color.
	 *
	 * @return A value [0.0f,1.0f].
	 */
	float rF();

	/**
	 * Get the float value of the green component of the color.
	 *
	 * @return A value [0.0f,1.0f].
	 */
	float gF();
	/**
	 * Get the float value of the blue component of the color.
	 *
	 * @return A value [0.0f,1.0f].
	 */
	float bF();

	/**
	 * Set the value of the red component of the color.
	 *
	 * @return A value [0.0f,1.0f].
	 */
	void setR(float r);
	/**
	 * Set the value of the green component of the color.
	 *
	 * @return A value [0.0f,1.0f].
	 */
	void setG(float g);
	/**
	 * Set the value of the blue component of the color.
	 *
	 * @return A value [0.0f,1.0f].
	 */
	void setB(float b);

private:

	/**
	 * Data containing the red component of color.
	 */
	int r_;
	/**
	 * Data containing the green component of color.
	 */
	int g_;
	/**
	 * Data containing the blue component of color.
	 */
	int b_;
};

#endif /* RCOLOR_H_ */
