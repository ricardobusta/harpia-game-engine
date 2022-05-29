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
 * File: RGLShapes.cpp
 * Created on: Aug 5, 2011
 */

#include "RGLShapes.h"

#include <SDL/SDL_opengl.h>
#include <cmath>
#include <RVector3f.h>

void rglDrawTriMesh(RTriMesh mesh) {
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < mesh.points.size(); i++) {
		float col = ((float) (i + 1) / (float) mesh.points.size()); //TODO remove after debugging is complete
//		float col = 1;
		glColor3f(mesh.colors[i].rF() * col, mesh.colors[i].gF() * col,
				mesh.colors[i].bF() * col);
		glNormal3fv(mesh.normals[i].getVector().data());
		glVertex3fv(mesh.points[i].getVector().data());
	}
	glEnd();
}

void rglDrawTriMeshWired(RTriMesh mesh){
	glBegin(GL_LINES);
	for (unsigned int i = 0; i < mesh.points.size()-1; i++) {
		glColor3f(mesh.colors[i].rF(), mesh.colors[i].gF(),
				mesh.colors[i].bF());
		glNormal3fv(mesh.normals[i].getVector().data());
		glVertex3fv(mesh.points[i].getVector().data());
		glNormal3fv(mesh.normals[i+1].getVector().data());
		glVertex3fv(mesh.points[i+1].getVector().data());
	}
	glEnd();
}

void rglDrawCylinder(float radius, float height, unsigned int div,
		RColor color) {
	float ang = (2.0 / div) * (M_PI);
	float h = height / 2;
	float x, y, z;
	float c, s, c1, s1;
	glBegin(GL_TRIANGLES);
	glColor3ub(color.r(), color.g(), color.b());
	for (unsigned int i = 0; i < div; i++) {
		float ca = (i / (float) div);
		glColor3f(color.rF() * ca, color.gF() * ca, color.bF() * ca);
		c = radius * cos(ang * i);
		c1 = radius * cos(ang * (i + 1));
		s = -radius * sin(ang * i);
		s1 = -radius * sin(ang * (i + 1));
		//top
		x = z = 0;
		y = h;
		glVertex3f(x, y, z);
		x = c;
		z = s;
		glVertex3f(x, y, z);
		x = c1;
		z = s1;
		glVertex3f(x, y, z);

		//bot
		x = z = 0;
		y = -h;
		glVertex3f(x, y, z);
		x = c1;
		z = s1;
		glVertex3f(x, y, z);
		x = c;
		z = s;
		glVertex3f(x, y, z);

		//side top
		y = h;
		x = c1;
		z = s1;
		glVertex3f(x, y, z);
		x = c;
		z = s;
		glVertex3f(x, y, z);
		y = -h;
		glVertex3f(x, y, z);

		//side bot
		glVertex3f(x, y, z);
		x = c1;
		z = s1;
		glVertex3f(x, y, z);
		y = h;
		x = c1;
		z = s1;
		glVertex3f(x, y, z);

	}
	glEnd();
}

void rglDrawCone(float radius, float height, unsigned int div, RColor color) {
	float ang = (2.0 / div) * (M_PI);
	float h = height / 2;
	float x, y, z;
	float c, s, c1, s1;
	glBegin(GL_TRIANGLES);
	glColor3ub(color.r(), color.g(), color.b());
	for (unsigned int i = 0; i < div; i++) {
		float ca = (i / (float) div);
		glColor3f(color.rF() * ca, color.gF() * ca, color.bF() * ca);
		c = radius * cos(ang * i);
		c1 = radius * cos(ang * (i + 1));
		s = -radius * sin(ang * i);
		s1 = -radius * sin(ang * (i + 1));

		//bot
		x = z = 0;
		y = -h;
		glVertex3f(x, y, z);
		x = c1;
		z = s1;
		glVertex3f(x, y, z);
		x = c;
		z = s;
		glVertex3f(x, y, z);

		//side bot
		glVertex3f(x, y, z);
		x = c1;
		z = s1;
		glVertex3f(x, y, z);
		y = h;
		x = 0;
		z = 0;
		glVertex3f(x, y, z);

	}
	glEnd();
}

void rglDrawBox(float width, float height, float depth, RColor color) {
	float w = width / 2;
	float h = height / 2;
	float d = depth / 2;

	RVector3f p[8];
	p[0].set(w, h, d);
	p[1].set(w, h, -d);
	p[2].set(-w, h, -d);
	p[3].set(-w, h, d);
	p[4].set(w, -h, d);
	p[5].set(w, -h, -d);
	p[6].set(-w, -h, -d);
	p[7].set(-w, -h, d);

	glBegin(GL_TRIANGLES);

	glColor3f(color.rF(), color.gF(), color.bF());

	glVertex3fv(p[0].getVector().data());
	glVertex3fv(p[3].getVector().data());
	glVertex3fv(p[7].getVector().data());

	glVertex3fv(p[0].getVector().data());
	glVertex3fv(p[7].getVector().data());
	glVertex3fv(p[4].getVector().data());

	glVertex3fv(p[1].getVector().data());
	glVertex3fv(p[5].getVector().data());
	glVertex3fv(p[6].getVector().data());

	glVertex3fv(p[1].getVector().data());
	glVertex3fv(p[6].getVector().data());
	glVertex3fv(p[2].getVector().data());

	glVertex3fv(p[0].getVector().data());
	glVertex3fv(p[1].getVector().data());
	glVertex3fv(p[2].getVector().data());

	glVertex3fv(p[0].getVector().data());
	glVertex3fv(p[2].getVector().data());
	glVertex3fv(p[3].getVector().data());

	glVertex3fv(p[7].getVector().data());
	glVertex3fv(p[6].getVector().data());
	glVertex3fv(p[5].getVector().data());

	glVertex3fv(p[7].getVector().data());
	glVertex3fv(p[5].getVector().data());
	glVertex3fv(p[4].getVector().data());

	glVertex3fv(p[0].getVector().data());
	glVertex3fv(p[4].getVector().data());
	glVertex3fv(p[5].getVector().data());

	glVertex3fv(p[0].getVector().data());
	glVertex3fv(p[5].getVector().data());
	glVertex3fv(p[1].getVector().data());

	glVertex3fv(p[2].getVector().data());
	glVertex3fv(p[6].getVector().data());
	glVertex3fv(p[7].getVector().data());

	glVertex3fv(p[2].getVector().data());
	glVertex3fv(p[7].getVector().data());
	glVertex3fv(p[3].getVector().data());

	glEnd();
}

void rglDrawCapsule(float radius, float height, unsigned int div,
		RColor color) {
	float h = height / 2;
	float x, y, z;
	float s, c, s1, c1, o;
	float sb, cb, sb1, cb1;
	float ang = (1.0 / div) * (M_PI);
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < 2 * div; i++) {
		float col = (i / (float) (2 * div));
		glColor3f(color.rF() * col, color.gF() * col, color.bF() * col);

		c = radius * cos(ang * i);
		c1 = radius * cos(ang * (i + 1));
		s = -radius * sin(ang * i);
		s1 = -radius * sin(ang * (i + 1));

		//side top
		y = h;
		x = c1;
		z = s1;
		glVertex3f(x, y, z);
		x = c;
		z = s;
		glVertex3f(x, y, z);
		y = -h;
		glVertex3f(x, y, z);

		//side bot
		glVertex3f(x, y, z);
		x = c1;
		z = s1;
		glVertex3f(x, y, z);
		y = h;
		x = c1;
		z = s1;
		glVertex3f(x, y, z);

		for (unsigned int j = 0; j < div; j++) {
			if (j < div / 2)
				o = h;
			else
				o = -h;
			//longitude
			s = -sin(ang * i);
			s1 = -sin(ang * (i + 1));
			c = cos(ang * i);
			c1 = cos(ang * (i + 1));
			//latitude
			sb = radius * sin(ang * j);
			sb1 = radius * sin(ang * (j + 1));
			cb = radius * cos(ang * j);
			cb1 = radius * cos(ang * (j + 1));
			if (j != div - 1) {
				x = sb * c;
				y = cb + o;
				z = sb * s;
				glVertex3f(x, y, z);
				x = sb1 * c;
				y = cb1 + o;
				z = sb1 * s;
				glVertex3f(x, y, z);
				x = sb1 * c1;
				y = cb1 + o;
				z = sb1 * s1;
				glVertex3f(x, y, z);
			}
			if (j != 0) {
				x = sb * c;
				y = cb + o;
				z = sb * s;
				glVertex3f(x, y, z);
				x = sb1 * c1;
				y = cb1 + o;
				z = sb1 * s1;
				glVertex3f(x, y, z);
				x = sb * c1;
				y = cb + o;
				z = sb * s1;
				glVertex3f(x, y, z);
			}
		}
	}
	glEnd();
}

void rglDrawSphere(float radius, unsigned int div, RColor color) {
	float sa, sa1, ca, ca1;
	float sb, sb1, cb, cb1;
	float x, y, z;
	float ang = ((1.0 / div) * (M_PI));
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < 2 * div; i++) {
		for (unsigned int j = 0; j < div; j++) {
			float col = ((i + j) / (float) (2 * div + div));
			glColor3f(color.rF() * col, color.gF() * col, color.bF() * col);
			//longitude
			sa = -sin(ang * i);
			sa1 = -sin(ang * (i + 1));
			ca = cos(ang * i);
			ca1 = cos(ang * (i + 1));
			//latitude
			sb = radius * sin(ang * j);
			sb1 = radius * sin(ang * (j + 1));
			cb = radius * cos(ang * j);
			cb1 = radius * cos(ang * (j + 1));
			if (j != div - 1) {
				x = sb * ca;
				y = cb;
				z = sb * sa;
				glVertex3f(x, y, z);
				x = sb1 * ca;
				y = cb1;
				z = sb1 * sa;
				glVertex3f(x, y, z);
				x = sb1 * ca1;
				y = cb1;
				z = sb1 * sa1;
				glVertex3f(x, y, z);
			}
			if (j != 0) {
				x = sb * ca;
				y = cb;
				z = sb * sa;
				glVertex3f(x, y, z);
				x = sb1 * ca1;
				y = cb1;
				z = sb1 * sa1;
				glVertex3f(x, y, z);
				x = sb * ca1;
				y = cb;
				z = sb * sa1;
				glVertex3f(x, y, z);
			}
		}
	}
	glEnd();
}

void rglDrawConvexHull() {
}




RTriMesh rglGenBox(float width, float height, float depth, RColor color) {
	RTriMesh mesh;

	float w = width / 2;
	float h = height / 2;
	float d = depth / 2;

	RVector3f p[8];
	p[0].set(w, h, d);
	p[1].set(w, h, -d);
	p[2].set(-w, h, -d);
	p[3].set(-w, h, d);
	p[4].set(w, -h, d);
	p[5].set(w, -h, -d);
	p[6].set(-w, -h, -d);
	p[7].set(-w, -h, d);
	RVector3f n[6];
	n[0].set(1, 0, 0); //right
	n[1].set(0, 1, 0); //top
	n[2].set(0, 0, 1); //near
	n[3].set(-1, 0, 0); //left
	n[4].set(0, -1, 0); //bottom
	n[5].set(0, 0, -1); //far

	//near
	mesh.addTriangle(p[0], p[3], p[7], n[2], color);
	mesh.addTriangle(p[0], p[7], p[4], n[2], color);

	//far
	mesh.addTriangle(p[1], p[5], p[6], n[5], color);
	mesh.addTriangle(p[1], p[6], p[2], n[5], color);

	//top
	mesh.addTriangle(p[0], p[1], p[2], n[1], color);
	mesh.addTriangle(p[0], p[2], p[3], n[1], color);

	//bottom
	mesh.addTriangle(p[7], p[6], p[5], n[4], color);
	mesh.addTriangle(p[7], p[5], p[4], n[4], color);

	//right
	mesh.addTriangle(p[0], p[4], p[5], n[0], color);
	mesh.addTriangle(p[0], p[5], p[1], n[0], color);

	//left
	mesh.addTriangle(p[2], p[6], p[7], n[3], color);
	mesh.addTriangle(p[2], p[7], p[3], n[3], color);

	return (mesh);
}

RTriMesh rglGenCapsule(float radius, float height, unsigned int div,
		RColor color) {
	RTriMesh mesh;
	float h = height / 2;
	RVector3f p1, p2, p3;
	float s, c, s1, c1, o;
	float sb, cb, sb1, cb1;
	float ang = (1.0 / div) * (M_PI);
	for (unsigned int i = 0; i < 2 * div; i++) {
		c = radius * cos(ang * i);
		c1 = radius * cos(ang * (i + 1));
		s = -radius * sin(ang * i);
		s1 = -radius * sin(ang * (i + 1));

		//side top
		p1.set(c1, h, s1);
		p2.set(c, h, s);
		p3.set(c, -h, s);
		mesh.addTriangle(p1, p2, p3, color);

		//side bot
		p1.set(c, -h, s);
		p2.set(c1, -h, s1);
		p3.set(c1, h, s1);
		mesh.addTriangle(p1, p2, p3, color);

		for (unsigned int j = 0; j < div; j++) {
			if (j < div / 2)
				o = h;
			else
				o = -h;
			//longitude
			s = -sin(ang * i);
			s1 = -sin(ang * (i + 1));
			c = cos(ang * i);
			c1 = cos(ang * (i + 1));
			//latitude
			sb = radius * sin(ang * j);
			sb1 = radius * sin(ang * (j + 1));
			cb = radius * cos(ang * j);
			cb1 = radius * cos(ang * (j + 1));
			if (j != div - 1) {
				p1.set(sb * c, cb + o, sb * s);
				p2.set(sb1 * c, cb1 + o, sb1 * s);
				p3.set(sb1 * c1, cb1 + o, sb1 * s1);
				mesh.addTriangle(p1, p2, p3, color);
			}
			if (j != 0) {
				p1.set(sb * c, cb + o, sb * s);
				p2.set(sb1 * c1, cb1 + o, sb1 * s1);
				p3.set(sb * c1, cb + o, sb * s1);
				mesh.addTriangle(p1, p2, p3, color);
			}
		}
	}
	return (mesh);
}

RTriMesh rglGenCone(float radius, float height, unsigned int div,
		RColor color) {
	RTriMesh mesh;

	float ang = (2.0 / div) * (M_PI);
	float h = height / 2;
	RVector3f p1,p2,p3;
	float c, s, c1, s1;

	for (unsigned int i = 0; i < div; i++) {
		float ca = (i / (float) div);
		glColor3f(color.rF() * ca, color.gF() * ca, color.bF() * ca);
		c = radius * cos(ang * i);
		c1 = radius * cos(ang * (i + 1));
		s = -radius * sin(ang * i);
		s1 = -radius * sin(ang * (i + 1));

		//bot
		p1.set(0,-h,0);
		p2.set(c1,-h,s1);
		p3.set(c,-h,s);
		mesh.addTriangle(p1, p2, p3, color);

		//side bot
		p1.set(c,-h,s);
		p2.set(c1,-h,s1);
		p3.set(0,h,0);
		mesh.addTriangle(p1, p2, p3, color);
	}

	return (mesh);
}

RTriMesh rglGenConvexHull() {
	RTriMesh mesh;
	return (mesh);
}

RTriMesh rglGenCylinder(float radius, float height, unsigned int div,
		RColor color) {
	RTriMesh mesh;

	float ang = (2.0 / div) * (M_PI);
	float h = height / 2;
	RVector3f p1,p2,p3;
	float c, s, c1, s1;

	for (unsigned int i = 0; i < div; i++) {
		float ca = (i / (float) div);
		glColor3f(color.rF() * ca, color.gF() * ca, color.bF() * ca);
		c = radius * cos(ang * i);
		c1 = radius * cos(ang * (i + 1));
		s = -radius * sin(ang * i);
		s1 = -radius * sin(ang * (i + 1));
		//top
		p1.set(0,h,0);
		p2.set(c,h,s);
		p3.set(c1,h,s1);
		mesh.addTriangle(p1, p2, p3, color);

		//bot
		p1.set(0,-h,0);
		p2.set(c1,-h,s1);
		p3.set(c,-h,s);
		mesh.addTriangle(p1, p2, p3, color);


		//side top
		p1.set(c1,h,s1);
		p2.set(c,h,s);
		p3.set(c,-h,s);
		mesh.addTriangle(p1, p2, p3, color);

		//side bot
		p1.set(c,-h,s);
		p2.set(c1,-h,s1);
		p3.set(c1,h,s1);
		mesh.addTriangle(p1, p2, p3, color);
	}

	return (mesh);
}

RTriMesh rglGenSphere(float radius, unsigned int div, RColor color) {
	RTriMesh mesh;
	float sa, sa1, ca, ca1;
	float sb, sb1, cb, cb1;
	RVector3f p1, p2, p3;
	float ang = ((1.0 / div) * (M_PI));
	for (unsigned int i = 0; i < 2 * div; i++) {
		for (unsigned int j = 0; j < div; j++) {
			//longitude
			sa = -sin(ang * i);
			sa1 = -sin(ang * (i + 1));
			ca = cos(ang * i);
			ca1 = cos(ang * (i + 1));
			//latitude
			sb = radius * sin(ang * j);
			sb1 = radius * sin(ang * (j + 1));
			cb = radius * cos(ang * j);
			cb1 = radius * cos(ang * (j + 1));
			if (j != div - 1) {
				p1.set(sb * ca, cb, sb * sa);
				p2.set(sb1 * ca, cb1, sb1 * sa);
				p3.set(sb1 * ca1, cb1, sb1 * sa1);
				mesh.addTriangle(p1, p2, p3, color);
			}
			if (j != 0) {
				p1.set(sb * ca, cb, sb * sa);
				p2.set(sb1 * ca1, cb1, sb1 * sa1);
				p3.set(sb * ca1, cb, sb * sa1);
				mesh.addTriangle(p1, p2, p3, color);
			}
		}
	}
	return (mesh);
}

