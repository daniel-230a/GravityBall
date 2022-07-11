#include "gravityBall.h"

gravityBall::gravityBall(float x, float y, float z, dWorldID w, dSpaceID s){
    /* Set our x,y,z variables */
    this->x=x; this->y=y; this->z=z;

    /* Set up physics objects */
    gBall = dBodyCreate(w);
    dBodySetPosition(gBall, x, y, z);
    dMassSetSphere(&mass,1,gBall_radius);
    dMassAdjust(&mass,1);
    dBodySetMass(gBall,&mass);
    gBallGeom = dCreateSphere(s,gBall_radius);
    dGeomSetBody(gBallGeom, gBall);

}

void gravityBall::setPosition(float x, float y, float z)
{
    //set ball postion
    this->x=x; this->y=y; this->z=z;
    dBodySetPosition(gBall, x, y, z);

}


void gravityBall::setSpeed(float speed){
    ///set ball speed and angle 0.0174532925 = 1 degrees
    x += sin(angle*0.0174532925) * -speed;
    y += cos(angle*0.0174532925) * speed;

    dBodySetPosition(gBall, x, y, z);

    const dReal* thePos = dBodyGetPosition(gBall);

    setPosition(thePos[0],thePos[1], thePos[2]);
}

void gravityBall::setX (float x){

    this->x += x;
}

void gravityBall::setZ(float up){

    //jump if ball is below jump height
    if(jump == true && z < jump_height){

        z+=up;

        dBodySetPosition(gBall, x, y, z);

        const dReal* thePos = dBodyGetPosition(gBall);

        setPosition(thePos[0],thePos[1], thePos[2]);
    }
}

void gravityBall::setRotX (float angle){
    /* Update angle */
    this->angle = angle;
}

float gravityBall::getRotX (){
    return angle;
}

/* Getter and Setters */
float gravityBall::getX(){
    return x;
}

float gravityBall::getY(){
    return y;
}

float gravityBall::getZ(){
    return z;
}

void gravityBall::draw()
{
    //set ball geom position
    const dReal* thePos = dBodyGetPosition(gBall);
    setPosition(thePos[0],thePos[1], thePos[2]);

    //draw ball
    ofPushMatrix();

    ofSetColor(ofColor(250, 152, 58, 255));
    ofTranslate(x,y,z);
    ofDrawSphere(gBall_radius);
    ofSetColor(ofColor::white);

    ofPopMatrix();

}


