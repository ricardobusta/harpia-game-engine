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
 * File: RMatrix4f.h
 * Created on: Aug 5, 2011
 */

#ifndef RMATRIX4F_H_
#define RMATRIX4F_H_

/**
 * A 4x4 matrix structure used mostly for linear transformations.
 */
class RMatrix4f {
public:
	RMatrix4f();
	virtual ~RMatrix4f();

	float data[16];

	const float* gl();

	RMatrix4f operator=(RMatrix4f);
	RMatrix4f operator*(RMatrix4f);
};

#endif /* RMATRIX4F_H_ */

