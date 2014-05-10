//
//  ofxMesh.h
//
//  Created by Rick Companje on 10/20/11.
//  Copyright (c) 2011 Globe4D. All rights reserved.
//

#pragma once

#include "ofMain.h"

class ofxMesh : public ofMesh {
public:  
    void toMesh(ofMesh & mesh);
	void fromMesh(const ofMesh & mesh);
    
    void addFace(ofVec3f a, ofVec3f b, ofVec3f c);
    void addFace(ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d);
    void addFace(ofRectangle r);
    void addBox(ofRectangle r, float height);
    ofxMesh &addMesh(ofMesh b);
	void addMeshes(const vector<ofxMesh> & input);

    void translate(const ofVec3f & pos);
    void translate(float x, float y, float z);
    void rotate(float angle, ofVec3f axis);
	void transform(const ofMatrix4x4 trans);
    void scale(float x, float y, float z=1);

    void invertNormals();
    ofVec3f getNormal(const ofVec3f& v1, const ofVec3f& v2, const ofVec3f& v3);
    void buildNormals();



	float getWidth(){

		float minX = std::numeric_limits<int>::max();
		float maxX = std::numeric_limits<int>::min();

		for (int i=0; i<getNumVertices(); i++) {
			ofVec3f v = getVertices()[i];
			minX = MIN(minX, v.x);
			maxX = MAX(maxX, v.x);
		}
		float width = fabs(minX - maxX);
		return width;
	}
    //    P(± r/√3, ± r/√3, ± r/√3)
    //    P(0, ± r/(√3*φ), ± (r*φ)/√3)
    //    P(± r/(√3*φ), ± (r*φ)/√3, 0)
    //    P(± (r*φ)/√3, 0, ± r/(√3*φ))

//	static ofMesh dodecahedron(float r = 1.);
};
