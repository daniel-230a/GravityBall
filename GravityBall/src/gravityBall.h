#include "ode/ode.h"
#include "ofApp.h"
#include "ofMain.h"

#ifndef GRAVITYBALL_H
#define GRAVITYBALL_H

class gravityBall {
    public:
        gravityBall(float x, float y, float z, dWorldID w, dSpaceID s);

    /* Methods */
    void setPosition(float x, float y, float z);
    void setX (float x);
    void setRotX(float pAngle);
    void setSpeed(float speed);
    void setRadius(float radius);
    void setZ(float z);
    void draw();

    float getRotX();
    float getX();
    float getY();
    float getZ();


    dReal angle = 0;
    dBodyID gBall;
    dMass   mass;
    dGeomID gBallGeom;

    bool jump = false;

    const float jump_height= 10;
    float gBall_radius= 1;
    float x, y, z;
    float speed;
};


#endif // GRAVITYBALL_H
