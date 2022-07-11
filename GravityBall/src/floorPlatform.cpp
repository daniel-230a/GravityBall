#include "floorPlatform.h"

floorPlatform::floorPlatform(float x, float y, float z, dWorldID w, dSpaceID s){
    /* Set our x,y,z variables */
    this->x=x; this->y=y; this->z=z;

    //load platform texture
    if(!ofLoadImage(pTexture, "floorTexture.jpg")) {
        std::cerr << "unable to load platform texture" << std::endl;
    }

    //repeat texture
    pTexture.setTextureWrap(GL_REPEAT, GL_REPEAT);

    //platform
    platformGeom = dCreateBox(s,p_width,p_len,p_height);
    dGeomSetPosition(platformGeom, x, y*p_len, z);

    platform.set(p_width, p_len, p_height);
    platform.setPosition(x, y * p_len, z);
    //apply texture to platform size
    platform.mapTexCoords(0,0,p_width/10,p_len/10);
    platform.setResolution(5, 5, 5);

    //remove platform trigger
    rmvPlatformTrigGeom = dCreateBox(s, p_width, rmv_p_len, rmv_p_height);
    dGeomSetPosition(rmvPlatformTrigGeom, x, y*p_len, z);

    //visualising platform trigger if needed
    rmvPlatformTrig.set(p_width,rmv_p_len,rmv_p_height/3);
    rmvPlatformTrig.setPosition(x, y*p_len, z);


    //--- 3 column of obstacles that generate in random orders ---
    vector<float> obsX = { x+(p_width/3), x, x-(p_width/3)};
    random_shuffle(obsX.begin(), obsX.end());

    vector<float> obsZ = { z+7, z+1};
    random_shuffle(obsZ.begin(), obsZ.end());

    //Obstacle 1
    obstactle1Geom = dCreateBox(s, obs_width, obs_len, obs_height);
    dGeomSetPosition(obstactle1Geom, obsX.at(0), y*p_len, z);

    obstactle1.set(obs_width, obs_len, obs_height);
    obstactle1.setPosition(obsX.at(0), y*p_len, z);

    //Obstacle 2
    obstactle2Geom = dCreateBox(s, obs_width, obs_len, 1);
    dGeomSetPosition(obstactle2Geom, obsX.at(1), y*p_len, obsZ.at(0));

    obstactle2.set(obs_width, obs_len, 1);
    obstactle2.setPosition(obsX.at(1), y*p_len, obsZ.at(0));

    //Obstacle 3
    obstactle3Geom = dCreateBox(s, obs_width, obs_len, obs_height);
    dGeomSetPosition(obstactle3Geom, obsX.at(2), y*p_len, z);

    obstactle3.set(obs_width, obs_len, obs_height);
    obstactle3.setPosition(obsX.at(2), y*p_len, z);
}

void floorPlatform::setPosition(float x, float y, float z)
{
    /* Setter method for position */
    this->x=x; this->y=y; this->z=z;
    dGeomSetPosition(platformGeom, x, y, z);
}

void floorPlatform::draw()
{

    ofPushMatrix();

    //--- show platform trigger Geom positions ---
    //ofSetColor(ofColor(250, 152, 58, 255));
    //rmvPlatformTrig.draw();
    //ofSetColor(ofColor::white);

    //--- Obstacle graphics ---
    ofSetColor(ofColor(200, 152, 58, 255));
    obstactle1.draw();
    obstactle2.draw();
    obstactle3.draw();
    ofSetColor(ofColor::white);

    //--- Platform graphics ---
    pTexture.bind();
    platform.draw();
    pTexture.unbind();

    ofPopMatrix();
}

float floorPlatform::getX(){
    return x;
}

float floorPlatform::getY(){
    return y;
}

float floorPlatform::getZ(){
    return z;
}

void floorPlatform::disableTrigger(){
    dGeomDisable(rmvPlatformTrigGeom);
    rmvPformTriggered = false;
}

bool floorPlatform::getRmvPformTriggered(){
    return rmvPformTriggered;
}


void floorPlatform::setRmvPformTriggered(bool state){

    rmvPformTriggered = state;
}
