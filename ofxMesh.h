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
    void toMesh(ofMesh & mesh){
        mesh.clear();
		if (hasVertices()) {
			mesh.getVertices()=getVertices();
		}
		if (hasColors()) {
			mesh.getColors()=getColors();
		}
		if (hasNormals()) {
			mesh.getNormals()=getNormals();
		}
		if (hasTexCoords()) {
			mesh.getTexCoords()=getTexCoords();
		}
		if (hasIndices()) {
			mesh.getIndices()=getIndices();
		}
    }
	void fromMesh(const ofMesh & mesh){
		if (mesh.hasVertices()) {
			getVertices()=mesh.getVertices();
		}
		if (mesh.hasColors()) {
			getColors()=mesh.getColors();
		}
		if (mesh.hasNormals()) {
			getNormals()=mesh.getNormals();
		}
		if (mesh.hasTexCoords()) {
			getTexCoords()=mesh.getTexCoords();
		}
		if (mesh.hasIndices()) {
			getIndices()=mesh.getIndices();
		}
		
	}
    void addFace(ofVec3f a, ofVec3f b, ofVec3f c);
    void addFace(ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d);
    void addFace(ofRectangle r);
    void addBox(ofRectangle r, float height);
    void translate(const ofVec3f & pos);
    void translate(float x, float y, float z);
    void rotate(float angle, ofVec3f axis);
	void transform(const ofMatrix4x4 trans);
	
    void scale(float x, float y, float z=1);
    void invertNormals();
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
    
//    ofVec3f getSize();
//    void unifyVertices();

    ofxMesh &addMesh(ofMesh b);
	
	void addMeshes(vector<ofxMesh> & input){
		for (int i=0; i<input.size(); i++) {
			addMesh(input[i]);
		}
	}
};
