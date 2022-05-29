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
 * File: RPhysicalTerrain.cpp
 * Created on: Aug 5, 2011
 */

//#include "RPhysicalTerrain.h"
//
//Terrain::Terrain(ISceneNode* irrterrain, IImage* heightfield, vector3df scale)
//    :vlPhysicalObject(irrterrain, 0) {
//    //*
//    float xScale = scale.X, yScale = scale.Y, zScale = scale.Z;
//
//    int img_width = heightfield->getDimension().Width;
//    int img_height = heightfield->getDimension().Height;
//
//    f32* rawhf = new f32[img_width*img_height];
//
//    int i = 0;
//    f32 maxHeight, minHeight;
//    for(int y = img_height - 1; y >= 0 ; y--) {
//        for(int x = 0; x < img_width; x++) {
//            rawhf[i] = (f32) (((heightfield->getPixel(x, y).color) << 24) >> 24);
//
//            if(i == 0) {
//                minHeight = maxHeight = rawhf[0];
//            } else {
//                maxHeight = (rawhf[i] > maxHeight) ? rawhf[i] : maxHeight;
//                minHeight = (rawhf[i] < minHeight) ? rawhf[i] : minHeight;
//            }
//
//            i++;
//        }
//    }
//
//    btHeightfieldTerrainShape *pTerrain = new btHeightfieldTerrainShape ( img_width,
//            img_height,
//            rawhf,
//            1,         //height scale
//            minHeight, //min height
//            maxHeight, //max height
//            1,         //y-axis up
//            PHY_FLOAT, //32-bit float heightfield
//            false);
//
//    // scale the shape (x and z)
//    btVector3 localScaling = btVector3(xScale, yScale, zScale);
//    pTerrain->setLocalScaling(localScaling);
//
//    btTransform tr = btTransform();
//    btQuaternion rot;
//    rot.setRotation(btVector3(0,1,0), PI);
//    tr.setIdentity();
//    tr.setRotation(rot);
//    tr.setOrigin(btVector3(0.0, (maxHeight - minHeight)*yScale/2.0, 0.0));
//
//    // create ground object
//    btDefaultMotionState* motionState = new btDefaultMotionState(tr);
//    initializeTerrain(pTerrain, motionState);
//    //*/
//}
