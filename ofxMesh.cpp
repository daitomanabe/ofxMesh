//
//  ofxMesh.cpp
//
//  Created by Rick Companje on 10/20/11.
//  Copyright (c) 2011 Globe4D. All rights reserved.
//

#include "ofxMesh.h"

void ofxMesh::fromMesh(const ofMesh & mesh){
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

void ofxMesh::toMesh(ofMesh & mesh){
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

void ofxMesh::addFace(ofVec3f a, ofVec3f b, ofVec3f c) {
    ofVec3f normal = ((c - a).cross(b - a)).normalize();
    
	addNormal(normal);
	addVertex(a);
	addNormal(normal);
	addVertex(b);
	addNormal(normal);
	addVertex(c);
    
    addIndex(getNumIndices());
    addIndex(getNumIndices());
    addIndex(getNumIndices());    
}

void ofxMesh::addFace(ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
    addFace(a, b, d);
	addFace(b, c, d);
}

void ofxMesh::addFace(ofRectangle r) {
    ofVec2f lt(r.x,r.y);
    ofVec2f rt(r.x+r.width,r.y);
    ofVec2f rb(r.x+r.width,r.y+r.height);
    ofVec2f lb(r.x,r.y+r.height);
    addFace(lt,lb,rb,rt);
}

void ofxMesh::addBox(ofRectangle r, float height) {
    
    ofVec3f a(r.x,r.y);
    ofVec3f b(r.x,r.y+r.height);
    ofVec3f c(r.x+r.width,r.y+r.height);
    ofVec3f d(r.x+r.width,r.y);

    ofVec3f e = a+ofVec3f(0,0,height);
    ofVec3f f = b+ofVec3f(0,0,height);
    ofVec3f g = c+ofVec3f(0,0,height);
    ofVec3f h = d+ofVec3f(0,0,height);
    
    ofxMesh mesh;
        
    mesh.addFace(a,b,c,d); //top
    mesh.addFace(h,g,f,e); //bottom
    mesh.addFace(b,f,g,c); //front
    mesh.addFace(c,g,h,d); //right
    mesh.addFace(d,h,e,a); //back
    mesh.addFace(a,e,f,b); //left
     
    addMesh(mesh);
}

ofxMesh &ofxMesh::addMesh(ofMesh b) {

    int numVertices = getNumVertices();
    int numIndices = getNumIndices();

    //add b
    addVertices(b.getVertices());
    addNormals(b.getNormals());
    addIndices(b.getIndices());

    //shift indices for b
    for (int i=0; i<b.getNumIndices(); i++) {
        getIndices()[numIndices+i] += numVertices;
    }

    return *this;
}

void ofxMesh::addMeshes(const vector<ofxMesh> & input)
{
    for (int i=0; i<input.size(); i++) {
        addMesh(input[i]);
    }
}

void ofxMesh::translate(const ofVec3f & pos) {
    for (int i=0; i<getNumVertices(); i++) {
        getVertices()[i] += pos;
    }
}

void ofxMesh::translate(float x, float y, float z) {
    for (int i=0; i<getNumVertices(); i++) {
        ofVec3f tmp = getVertices()[i] + ofVec3f(x,y,z);
		getVertices()[i].set(tmp);
    }
}

void ofxMesh::rotate(float angle, ofVec3f axis) {
    for (int i=0; i<getNumVertices(); i++) {
        getVertices()[i].rotate(angle, axis);
    }
}

void ofxMesh::scale(float x, float y, float z) {
    for (int i=0; i<getNumVertices(); i++) {
        getVertices()[i].x *= x;
        getVertices()[i].y *= y;
        getVertices()[i].z *= z;
    }
}

void ofxMesh::transform(const ofMatrix4x4 trans) {
    for (int i=0; i<getNumVertices(); i++) {
		getVertices()[i] = trans.preMult(getVertices()[i]);
    }
}

void ofxMesh::invertNormals() {
    for (int i=0; i<getNumNormals(); i++) {
        getNormals()[i] *= -1;
    }
}

ofVec3f ofxMesh::getNormal(const ofVec3f& v1, const ofVec3f& v2, const ofVec3f& v3) {
	ofVec3f a = v1 - v2;
	ofVec3f b = v3 - v2;
	ofVec3f normal = b.cross(a);
	normal.normalize();
	return normal;
}

void ofxMesh::buildNormals() {
	vector<ofVec3f>& vertices = getVertices();
	for(int i = 0; i < getNumVertices(); i += 3) {
		ofVec3f normal = getNormal(
                                   getVertices()[i+0],
                                   getVertices()[i+1],
                                   getVertices()[i+2]);
		for(int j = 0; j < 3; j++) {
			addNormal(normal);
		}
	}
}




//ofMesh ofxMesh::dodecahedron(float r )
//{
//    ofMesh mesh;
//    vector<ofVec3f> vertices;
//    float phi = (float) (sqrt(5) - 1) / 2; // The golden rati
//    float R = (float) (r / sqrt(3));
//
//    float a = (R * 1);
//    float b = R / phi;
//    float c = R * phi;
//
//    for (int i = -1; i < 2; i += 2)
//    {
//        for (int j = -1; j < 2; j += 2)
//        {
//            mesh.addVertex(ofVec3f(
//                                   0,
//                                   i * c * R,
//                                   j * b * R));
//            mesh.addVertex(ofVec3f(
//                                   i * c * R,
//                                   j * b * R,
//                                   0));
//            mesh.addVertex(ofVec3f(
//                                   i * b * R,
//                                   0,
//                                   j * c * R));
//
//            for (int k = -1; k < 2; k += 2){
//
//                mesh.addVertex(ofVec3f(
//                                       i * a * R,
//                                       j * a * R,
//                                       k * a * R));
//            }
//        }
//    }
//    return mesh;
//}

