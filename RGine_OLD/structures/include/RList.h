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
 * File: RList.h
 * Created on: Aug 5, 2011
 */

#include <list>
using namespace std;

#define RList list

/*
#ifndef RLIST_H_
#define RLIST_H_

//TODO make this class to replace c++ default list (maybe)

template<class T>
/**
 * This class is a list of objects.
 *
class RList {
public:
	RList();
	virtual ~RList();

	/**
	 * This operator is used to obtain an element in the list given an index.
	 *
	 * @param index Index of the wanted element.
	 * @return The element of that index.
	 *
	T operator[](const int index);
private:
};

#endif /* RLIST_H_ */
