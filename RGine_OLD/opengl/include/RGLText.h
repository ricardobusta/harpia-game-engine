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
 * File: RGLText.h
 * Created on: Aug 5, 2011
 */

#ifndef RGLTEXT_H_
#define RGLTEXT_H_

#include <RString.h>

/**
 * Class used to write texts with opengl commands.
 */
class RGLText {
private:
	void drawCharacter(char c);RString text; //text
	float spacingx, spacingy; //spacing between characters
	float size; //character size (square)
	float aspectx, aspecty; //text aspect x:y
	float x, y, z;
	float r, g, b; //text color
	float bgr, bgg, bgb; //background color
	int detail; //angle increment for circular characters
	float lineWidth; //character line width
	int tabsize; //size of tab in characters
	bool lowercase;
	bool uppercase;
	bool underline;
	bool bg; //background

	RGLText *next;

	//auxiliar
	void drawCircular(float angle1, float angle2, float cx, float cy,
			float scalex, float scaley); //draw circular sections of characters
public:
	void draw();
	void setText(RString text);
	void appendText(RString text);
	void setSize(float size);
	void setColor(float r, float g, float b);
	void setColor(RString color);
	void setBGColor(float r, float g, float b);
	void setBGColor(RString color);
	void setSpacing(float x, float y);
	void setAspect(float x, float y);
	void setDetail(int detail);
	void setLineWidth(float width);
	void setNext(RGLText *next);
	void setLowerCase();
	void setUpperCase();
	void setNoCase();

	RGLText(RString text, float size, float x, float y, float z, float width);
	virtual ~RGLText();
};

#endif /* RGLTEXT_H_ */
