#pragma once

#include "ofMain.h"
#include "ode/ode.h"
#include "gravityBall.h"
#include "floorPlatform.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void collide (dGeomID o1, dGeomID o2);
    void resetBall();

    //Start screen objects
    ofImage menuScrnBG;
    ofImage menuScrnTitle;
    ofImage menuScrnStartBTN;
    ofImage menuScrnEndBTN;
    ofColor hoverColorStartBTN = ofColor::white;
    ofColor hoverColorEndBTN = ofColor::white;

    //Game screen objects
    ofImage gameScrnBG;

    //gameStart
    void gameStartSetup();
    void gameStartDraw();

    //Game
    void gameSetup();
    void gameUpdate();
    void gameDraw();

    //Game End
    void gameEndDraw();
    void gameExit();

    //Game states
    int gameScreen = 0; //0: start screen, 1: level 1, -1: end screen
    bool startScreen = true;
    bool endScreen = true;
    bool hoverStartBTN = false;
    bool hoverEndBTN = false;

    int numPlatforms=0;
    int maxPlatforms=15;
    bool addPlatform = true;

    bool resetBallOnDeath = false;

    int lives = 5;
    int score = 0;

    ofTrueTypeFont infoText;

    dJointGroupID contactgroup;
    dWorldID world;
    dSpaceID space;
    dGeomID ground;

    vector<floorPlatform*> platformList;

    ofPlanePrimitive mGround;
    ofPlanePrimitive platform;

    ofEasyCam cam;

    gravityBall* gBall;

    ofLight light;
    ofLight light2;

    float playerSpeed = 0.4; //0.1 = 10MPH


};

static void nearCallback (void *, dGeomID o1, dGeomID o2);
extern ofApp *myApp;
