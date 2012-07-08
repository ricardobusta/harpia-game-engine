#include "RGScene.h"

RGScene::RGScene()
{
    entID = 0;
}

RGScene::~RGScene()
{
    //dtor
}

void RGScene::render(){
    for(map<int,RGEntity*>::iterator it = entities.begin(); it != entities.end(); it++){
        (*it).second->render();
    }
}

void RGScene::addEntity(RGEntity *entity){
    entities[entID++] = entity;
}
