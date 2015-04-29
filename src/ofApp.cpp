//
//  ofApp.cpp
//  NoiseThresholdExample
//
//  Created by Andreas Müller.
//  Commented by Travis Powell.
//

#include <stdio.h>
#include "ofApp.h"

void ofApp::setup()
{
    //Adds the listener to determine the resolution of the image and whether or not it has been changed with a slider.
    resolution.addListener(this, &ofApp::resolutionChanged );
    
    //Builds the gui and sets the fonts and positions of each slider and button on the gui interface.
    gui.setup( "Main", "Main.xml") ;
    
    gui.add( resolution.set( "Resolution", 512, 2, 1024 ) );
    gui.add( noiseFrequency.set( "Noise Frequency", 80.0f, 0.00001f, 4096.0f ) );
    gui.add( animate.set( "Animate", false ) );
    
    gui.add( doThreshold.set( "Threshold", false ) );
    gui.add( thresholdLow.set( "Treshold Low", 0, 0, 255 ) );
    gui.add( thresholdHigh.set( "Treshold High", 127, 0, 255 ) );
    gui.add( invert.set( "Invert Threshold", false ) );
    
    noiseStartX = 0;
    noiseStartY = 0;
    
    drawGui = true;
    
    //Sets the size of the grayscale image based on resolution.
    noiseImage.allocate( resolution, resolution, OF_IMAGE_GRAYSCALE );
}

//-------------------------------------------------------------------
void ofApp::update()
{
    //Increases and decreases the amount of noise based on the arrow keys.
    if( ofGetKeyPressed(OF_KEY_LEFT)  )  { noiseStartX += 5; }
    if( ofGetKeyPressed(OF_KEY_RIGHT ) ) { noiseStartX -= 5; }
    if( ofGetKeyPressed(OF_KEY_UP)  )    { noiseStartY += 5; }
    if( ofGetKeyPressed(OF_KEY_DOWN ) )  { noiseStartY -= 5; }
    
    //Animates the threshold based on elapsed time.
    float time = 0.0f;
    if( animate ) time = ofGetElapsedTimef();
    
    ofPixelsRef pixels = noiseImage.getPixelsRef();
    
    //Makes sure the noise is drawn across the entire image.
    int tmpIndex = 0;
    for( int y = 0; y < noiseImage.getHeight(); y++ )
    {
        for( int x = 0; x < noiseImage.getWidth(); x++ )
        {
            // We're grabbing a single reading from the noise function here, but we can also add together more
            // readings at different frequencies to make more complex patterns
            
            float tmpNoise = ofNoise( (noiseStartX + x) / noiseFrequency, (noiseStartY + y) / noiseFrequency, time );
            
            pixels[tmpIndex] = tmpNoise * 255.0f;
            tmpIndex++;
        }
    }
    
    //Creates the threshold if the threshold is not already being drawn.
    if( doThreshold)
    {
        threshold( false );
    }
    
    noiseImage.update(); // uploads the new pixels to the gfx card
}

//---------------------------------------------------------------
void ofApp::threshold( bool _upload )
{
    //Returns the current noise threshold to be used in the threshold changed functions.
    ofPixelsRef pixels = noiseImage.getPixelsRef();
    
    //Generates the pixels that are seen with the image is animated.
    int tmpIndex = 0;
    for( int y = 0; y < noiseImage.getHeight(); y++ )
    {
        for( int x = 0; x < noiseImage.getWidth(); x++ )
        {
            if( pixels[tmpIndex] >= thresholdLow && pixels[tmpIndex] <= thresholdHigh )
            {
                pixels[tmpIndex] = 255;
            }
            else
            {
                pixels[tmpIndex] = 0;
            }
            
            if( invert )
            {
                pixels[tmpIndex] = 255 - pixels[tmpIndex];
            }
            
            tmpIndex++;
        }
    }
    
    
    //Resets the noise to accmodate for new images.
    if( _upload )
    {
        noiseImage.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackgroundGradient( ofColor(0), ofColor(40), OF_GRADIENT_CIRCULAR );
    
    //Applies the image to a rectangle that is manipulated by the changes by the noise threshold.
    ofRectangle imageRect(0,0,noiseImage.getWidth(), noiseImage.getHeight() );
    imageRect.scaleTo( ofRectangle(0,0,ofGetWidth(),ofGetHeight()) );
    noiseImage.draw( imageRect );
    
    if( drawGui )
    {
        gui.draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::resolutionChanged( int& _res )
{
    //Repostions the image to match the resolution changes made to the noise.
    noiseImage.allocate( _res, _res, OF_IMAGE_GRAYSCALE );
}


//--------------------------------------------------------------
void ofApp::keyPressed( int _key )
{
    if( _key == 'f' )
    {
        ofToggleFullscreen();
    }
}



