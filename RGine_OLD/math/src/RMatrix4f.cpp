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
 * File: RMatrix4f.cpp
 * Created on: Aug 5, 2011
 */

#include "RMatrix4f.h"

RMatrix4f::RMatrix4f() {
	for(int i=0;i<16;i++){
		data[i]=0;
	}
}

RMatrix4f::~RMatrix4f() {
}

const float* RMatrix4f::gl(){
	return (data);
}

RMatrix4f RMatrix4f::operator =(RMatrix4f m) {
	for (int i = 0; i < 16; i++) {
		data[i] = m.data[i];
	}
	return (*this);
}

RMatrix4f RMatrix4f::operator *(RMatrix4f m) {
	RMatrix4f r;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			r.data[i + j * 4] = 0;
			for (int k = 0; k < 4; k++) {
				r.data[i + j * 4] += data[i + k * 4] * m.data[k + j * 4];
			}
		}
	}
	return (r);
}

