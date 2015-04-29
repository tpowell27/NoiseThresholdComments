//Created by Andreas MŸller.

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp

{
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void resolutionChanged(int& _res);
    void threshold(bool _upload);
    
    ofParameter<int> resolution;
    ofParameter<float> noiseFrequency;
    ofParameter<bool> animate;
    
    ofParameter<bool> doThreshold;
    ofParameter<int> thresholdLow;
    ofParameter<int> thresholdHigh;
    ofParameter<bool> invert;
    
    bool drawGui;
    
    int noiseStartX;
    int noiseStartY;
    
    ofImage noiseImage;
    
    ofxPanel gui;
};


