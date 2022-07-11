#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);

    //starting screen
    if(gameScreen == 0) {
        gameStartSetup();
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    /* Making sure the setup is called once */
    if(gameScreen == 1){
        if(startScreen == true){
            startScreen = false;
            gameSetup();
        }
        gameUpdate();
    }
}
//--------------------------------------------------------------
void ofApp::draw(){

    //Game Screens
    if(gameScreen == 0) gameStartDraw();
    if(gameScreen == 1) gameDraw();
    if(gameScreen == -1) gameEndDraw();

}
//--------------------------------------------------------------
void ofApp::exit() {
    gameExit();
}
//--------------------------------------------------------------
static void nearCallback (void *, dGeomID o1, dGeomID o2) {

    myApp->collide(o1,o2);
}
//--------------------------------------------------------------
void ofApp::collide(dGeomID o1, dGeomID o2) {

    //check each platform in list for collision with the ball and platform removal trigger
    for(auto pform : platformList){

        //check for colision with platform removal trigger and ball
        if(pform->rmvPlatformTrigGeom == o1 || pform->rmvPlatformTrigGeom == o2){
            if((gBall->gBallGeom == o1 || gBall->gBallGeom == o2) && !pform->getRmvPformTriggered()){

                //if collided remove first platform in list
                pform->setRmvPformTriggered(true);
                platformList.erase(platformList.begin());
                pform->disableTrigger();
                numPlatforms++;
                score+=1;
                pform->setRmvPformTriggered(false);
                //trigger addition of a platform
                addPlatform=true;
                return;
            }

        }

        //on colision of any of the 3 obstacles reduce score and players lives
        int obs1 = (o1 == pform->obstactle1Geom || o2 == pform->obstactle1Geom);
        int obs2 = (o1 == pform->obstactle2Geom || o2 == pform->obstactle2Geom);
        int obs3 = (o1 == pform->obstactle3Geom || o2 == pform->obstactle3Geom);
        if(obs1 || obs2|| obs3){
            if(gBall->gBallGeom == o1 || gBall->gBallGeom == o2){

                if(score > 0) {
                    score-=1;
                }

                //triggers loss of a life
                resetBallOnDeath = true;
                return;

            }

        }

    }

    //if ball falls off platform let it fall past ground level
    if (o1 == ground || o2 == ground){
        return;
    }

    //collision surface response parameters
    int i,n;

    const int N = 10;
    dContact contact[N];
    n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
    if (n > 0) {
        for (i=0; i<n; i++) {
          contact[i].surface.mode = dContactSlip1 | dContactSlip2 |
            dContactSoftERP | dContactSoftCFM | dContactApprox1;
          contact[i].surface.mu = dInfinity;
          contact[i].surface.slip1 = 0.1;
          contact[i].surface.slip2 = 0.1;
          contact[i].surface.soft_erp = 0.3;
          contact[i].surface.soft_cfm = 0.1;
          dJointID c = dJointCreateContact (world,contactgroup,&contact[i]);
          dJointAttach (c,
                        dGeomGetBody(contact[i].geom.g1),
                        dGeomGetBody(contact[i].geom.g2));
        }
    }

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //user key controls press action
    switch(key) {
    case 'a': case 'A': case OF_KEY_LEFT:
        if(gBall->getRotX() == 0) {
            gBall->setSpeed(0);
            gBall->setRotX(45);
        }
      break;
    case 'd': case 'D': case OF_KEY_RIGHT:
        if(gBall->getRotX() == 0) {
            gBall->setSpeed(0);
            gBall->setRotX(-45);
        }
      break;
    case ' ':
        if(gBall->z < 1.5) {
            if(gBall->jump == false) {
                gBall->jump = true;
                for (int i = 0; i < gBall->jump_height; i++) {
                    gBall->setZ(i);
                }
            }
        }
        break;
    case 'q':
        ofExit();
        break;
    }

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //user key controls release action
    switch(key) {
    case 'a': case 'A': case OF_KEY_LEFT:
      gBall->setRotX(0);
      break;
    case 'd': case 'D': case OF_KEY_RIGHT:
      gBall->setRotX(0);
      break;
    case ' ':
        gBall->jump = false;
        break;
    }

}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //shade menu screen buttons on hover
    if(gameScreen == 0 || gameScreen == -1){
        //start button area
        if(x > (ofGetWindowWidth()/2)-300 && x < 770 && y > ((ofGetWindowHeight()/2)-100) && y < (ofGetWindowHeight()/2)+50){
            if(hoverStartBTN == false){
                hoverColorStartBTN = ofColor::gray;
                hoverStartBTN = true;
            }
        }else{
            hoverStartBTN = false;
            hoverColorStartBTN = ofColor::white;
        }
        //exit button area
        if(x > (ofGetWindowWidth()/2)-300 && x < 770 && y > ((ofGetWindowHeight()/2)+100) && y < (ofGetWindowHeight()/2)+250){
            if(hoverEndBTN == false){
                hoverColorEndBTN = ofColor::gray;
                hoverEndBTN = true;
            }
        }else{
            hoverEndBTN = false;
            hoverColorEndBTN = ofColor::white;
        }
    }

}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //menu button click events
    if(gameScreen == 0 || gameScreen == -1){
        if(button == 0){
            if(mouseX > (ofGetWindowWidth()/2)-300 && mouseX < 770 && mouseY > ((ofGetWindowHeight()/2)-100) && mouseY < (ofGetWindowHeight()/2)+50){
                gameScreen = 1;
            }if(mouseX > (ofGetWindowWidth()/2)-300 && mouseX < 770 && mouseY > ((ofGetWindowHeight()/2)+100) && mouseY < (ofGetWindowHeight()/2)+250){
                ofExit();
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
//--------------------------------------------------------------
void ofApp::gameStartSetup(){
    //starting screen
    menuScrnBG.load("menuBackground.jpg");
    menuScrnTitle.load("gameTitle.png");
    menuScrnStartBTN.load("startBTN.png");
    menuScrnEndBTN.load("endBTN.png");
}

void ofApp::gameStartDraw(){
    //start menu screen
    menuScrnBG.draw(0,0);
    menuScrnTitle.draw((ofGetWindowWidth()/2)-380,ofGetWindowHeight()/2 - 320);

    ofSetColor(hoverColorStartBTN);
    menuScrnStartBTN.draw((ofGetWindowWidth()/2)-300,ofGetWindowHeight()/2 -100);

    ofSetColor(hoverColorEndBTN);
    menuScrnEndBTN.draw((ofGetWindowWidth()/2)-300,(ofGetWindowHeight()/2 +100));

    ofSetColor(ofColor::white);
}
//--------------------------------------------------------------
void ofApp::gameSetup(){
    ofResetElapsedTimeCounter();
    ofDisableArbTex();

    gameScrnBG.load("menuBackground.jpg");

    // create world
    dInitODE2(0);
    world = dWorldCreate();
    space = dHashSpaceCreate(0);
    contactgroup = dJointGroupCreate(0);
    dWorldSetGravity (world,0,0,-7);
    ground = dCreatePlane(space,0,0,1,0);

    dAllocateODEDataForThread(dAllocateMaskAll);

    //spawn ball ahead of first platform length to hide despawning of previous platform
    gBall = new gravityBall(0,62,10, world, space);

    //ball lighting
    light.setPointLight();
    light.enable();

    //global lighting
    light2.setDirectional();
    light2.setOrientation(glm::vec3(gBall->getX(),gBall->getY()-200,gBall->getZ()-30));
    light2.enable();

    //font for ingame onscreen text
    infoText.load("gameFont.ttf",20);

    //camera
    ofVec3f upVector;
    upVector.set(0, 0, 1);
    cam.setAutoDistance(false);
    cam.setNearClip(0.01);
    cam.setPosition(gBall->getX(),gBall->getY()-5,gBall->getZ()+3);
    cam.lookAt({gBall->getX(),gBall->getY(),gBall->getZ()},upVector);
    cam.setUpAxis(upVector);
    cam.disableMouseInput();
    cam.disableMouseMiddleButton();

    //Generate and Push the max number of platforms into the List of platforms
    for(unsigned int p=0; p<maxPlatforms; p++) {
        platformList.push_back(new floorPlatform(0, p, 0, world, space));
        numPlatforms = platformList.size();
    }

}

void ofApp::gameUpdate(){

    //increment speed and apply to ball on every frame
    playerSpeed+=0.0001;
    gBall->setSpeed(playerSpeed);

    //light to follow ball
    light.setPosition(0,gBall->getY()-20,gBall->getZ()+5);

    //camera to follow ball
    cam.setPosition(gBall->getX(),gBall->getY()-10,gBall->getZ()+8);

    //Add new platform to the end of the endlessly generating Vector of platforms
    if(addPlatform) {
        addPlatform = false;
        platformList.push_back(new floorPlatform(0, numPlatforms, 0, world, space));
    }

    //if ball falls off the platform
    if(gBall->getZ() < -15){
        resetBall();
    }

    //if ball lost a life and needs reseting
    if(resetBallOnDeath && score > 0){
        resetBall();
    }

    //when player has no more lives left
    if(lives <= 0){
        gameScreen = -1;
        startScreen = true;
    }


    dSpaceCollide (space,0,&nearCallback);
    dWorldStep (world,0.05);

    // remove all contact joints
    dJointGroupEmpty (contactgroup);

}

void ofApp::gameDraw(){
    //draw background
    gameScrnBG.draw(0,0);

    //show information text and game stats
    ofSetColor(ofColor::white);
    infoText.drawString("Speed: " + ofToString(floor(playerSpeed * 100)) + "MPH",5,30);

    ofSetColor(ofColor::black);
    ofFill();
    ofDrawRectangle(5,50, 200, 15);
    ofSetColor(ofColor::gold);
    ofFill();
    ofDrawRectangle(5,50, floor(lives*40), 15);

    infoText.drawString("Lives: " + ofToString(lives),5,100);

    ofSetColor(ofColor::white);

    infoText.drawString("Score: " + ofToString(score),5,130);
    infoText.drawString("A - Left ",5,170);
    infoText.drawString("D - Right ",5,200);
    infoText.drawString("Space - Jump ",5,230);

    cam.begin();

    ofEnableDepthTest();
    ofPushMatrix();

    ofSetColor(ofColor::blanchedAlmond);

    //draw ball
    gBall->draw();

    //draw platforms
    for(auto pform : platformList){
        pform->draw();
    }

    ofSetColor(ofColor::white);
    ofDisableDepthTest();
    cam.end();

    ofPopMatrix();

}
//--------------------------------------------------------------
void ofApp::gameEndDraw(){
    //end screen menu and information
    menuScrnBG.draw(0,0);
    menuScrnTitle.draw((ofGetWindowWidth()/2)-380,ofGetWindowHeight()/2 - 320);

    infoText.drawString("Game Over, you have lost all ur lives!", (ofGetWindowWidth()/2)-250,(ofGetWindowHeight()/2)-100);

    infoText.drawString("Score: " + ofToString(score), (ofGetWindowWidth()/2)-250,(ofGetWindowHeight()/2)-50);

    ofSetColor(hoverColorEndBTN);
    menuScrnEndBTN.draw((ofGetWindowWidth()/2)-300,(ofGetWindowHeight()/2 +100));

    ofSetColor(ofColor::white);
}
//--------------------------------------------------------------

void ofApp::resetBall() {
    //reset ball position when player looses life
    gBall->setPosition(0, (numPlatforms-maxPlatforms+1)*61,2);
    lives-=1;
    resetBallOnDeath = false;

}


void ofApp::gameExit(){

    //on game exit
    for(auto pform : platformList){
        dGeomDestroy(pform->platformGeom);
    }

    platformList.clear();
    dGeomDestroy(gBall->gBallGeom);
    dJointGroupDestroy (contactgroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);
    dCloseODE();
}
