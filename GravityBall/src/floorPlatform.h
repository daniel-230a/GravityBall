#include "ode/ode.h"
#include "ofApp.h"
#include "ofMain.h"

#ifndef FLOORPLATFORM_H
#define FLOORPLATFORM_H


class floorPlatform {
public:
    floorPlatform(float x, float y, float z, dWorldID w, dSpaceID s);

    void setPosition(float x, float y, float z);
    void setBallPosition(float bX, float bY, float bZ);
    void setSpeed(float speed);
    void draw();
    void drawBall();
    void ballSetup(float x, float y, float z, dWorldID w, dSpaceID s);
    void disableTrigger();
    bool getRmvPformTriggered();
    void setRmvPformTriggered(bool state);

    float getX();
    float getY();
    float getZ();

    dBodyID platformBody;
    dGeomID platformGeom;
    dGeomID rmvPlatformTrigGeom;

    dGeomID obstactle1Geom;
    dGeomID obstactle2Geom;
    dGeomID obstactle3Geom;

    ofBoxPrimitive platform;

    ofTexture pTexture;

    ofBoxPrimitive rmvPlatformTrig;

    ofBoxPrimitive obstactle1;
    ofBoxPrimitive obstactle2;
    ofBoxPrimitive obstactle3;


    bool debugDraw = true;
    bool hit = false;
    bool ball = false;
    bool rmvPformTriggered = false;

    const float p_width=20,p_len=60,p_height=1;

    const float rmv_p_len=2,rmv_p_height=60;

    const float obs_width=p_width/3,obs_len=rmv_p_len,obs_height=15;


    float x, y, z;
    float speed;
};

#endif // FLOORPLATFORM_H
