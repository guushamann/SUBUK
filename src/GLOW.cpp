#include "GLOW.h"
//--------------------------------------------------------------

GLOW::PixelGrid::PixelGrid(int PGRowCount,int PGColumnCount){
	RowCount=PGRowCount;
	ColumnCount=PGColumnCount;
}

void GLOW::setup(){
	creatureCount=50;
	CanvasOffsetY=-600;
	CanvasOffsetX=0;
	AttractTo=2;

	ofSetVerticalSync(true);
	glEnable(GL_DEPTH_TEST);
	ofSetLineWidth(10);
	PG = new PixelGrid(20,180);
	PG->CreateGrid();
	Creatures.resize(creatureCount);

	for(int i=0;i<Creatures.size();i++){
		Creatures[i].InitCreature(PG);
	}
	for(int i=0;i<PG->RowCount;i++){
		for(int j=0;j<PG->ColumnCount;j++){
			ofVec3f cur;
			cur.x=(j*10)+CanvasOffsetY;
			cur.y=(i*10)+CanvasOffsetX;
			cur.z=0;
			mesh.addVertex(cur);
			PG->PixelrowColection[i].PixelColumnColection[j].Vertex=cur;
		}
	}
}
void GLOW::PixelGrid::CreateGrid(){
	
	int rowNR;
	int ColumnNR;
	int test;
	for(int i=0;i<this->RowCount;i++){
		rowNR= PixelrowColection.Add();	
		PixelrowColection[i].rowNR=rowNR;
		for(int j=0;j<this->ColumnCount;j++){
			ColumnNR=PixelrowColection[rowNR].PixelColumnColection.Add();
			PixelrowColection[rowNR].PixelColumnColection[ColumnNR].ColumnNR=ColumnNR;			
		}
	}	
}
void GLOW::Creature::InitCreature(GLOW::PixelGrid* PG){
	direction=2;
	speed=(int)ofRandom(1,8);
	x=(int)ofRandom(1,179);
	y=(int)ofRandom(1,19);
	Kleur=ofColor(255,255,255);

}
void GLOW::Creature::FindCreatures(GLOW::PixelGrid* PG,vector<Creature> & Creatures){
	this->Kleur=ofColor(255,255,255);
	this->NearCreatures.clear();
	for(int i=0;i<Creatures.size();i++){	
		if(ofDistSquared(this->x,this->y,Creatures[i].x,Creatures[i].y)<3 && ofDistSquared(this->x,this->y,Creatures[i].x,Creatures[i].y)>-3){
			this->NearCreatures.push_back(i);			
		}
	}
	if(this->NearCreatures.size()>1){
		this->Kleur=ofColor::green;
	}
	if(this->NearCreatures.size()>2){
		this->Kleur=ofColor::yellow;
	}
	if(this->NearCreatures.size()>3){
		this->Kleur=ofColor(255,0,0);		
	}
	
}
void GLOW::Creature::MoveCreature(GLOW::PixelGrid* PG,int AttractTo){
	if(1==(int)ofRandom(1,speed)){
		if(x > PG->ColumnCount-1){
			direction=4;
		}
		if(x <= 0){
			direction=2;
		}
		if(y > PG->RowCount-1){
			direction=3;
		}
		if(y <= 0){
			direction=1;
		}
		if(1==(int)ofRandom(50)){
			if(direction<4){
				direction=direction+1;
			}else{
				direction=1;
			}
		}
		if(1==(int)ofRandom(8)){
			direction=AttractTo;
		}

		if(direction==1 && y < PG->RowCount){
			y=y+1;
		}

		if(direction==2 && x < PG->ColumnCount){
			x=x+1;
			//y=1;
		}
		if(direction==3 && y>0){
			y=y-1;
		}
		if(direction==4 && x>0){
			x=x-1;
			//y=1;
		}
	}
};
//--------------------------------------------------------------
void GLOW::update(){
	for(int i=0;i<Creatures.size();i++){
		Creatures[i].FindCreatures(PG,Creatures);
		Creatures[i].MoveCreature(PG, AttractTo);
	}
}

//--------------------------------------------------------------
void GLOW::draw(){
	ofBackgroundGradient(ofColor(50), ofColor(0));
	
	cam.begin();

	glPointSize(1);
	ofSetColor(100, 100, 100);	
	mesh.drawVertices();

	cam.end();
	
	for(int i=0;i<Creatures.size();i++){
			ofVec3f cur;			
			if(Creatures[i].x < PG->ColumnCount && Creatures[i].y < PG->RowCount){
				cur = cam.worldToScreen(PG->PixelrowColection[Creatures[i].y].PixelColumnColection[Creatures[i].x].Vertex);
			}
			ofSetColor(Creatures[i].Kleur);
			//ofSetLineWidth(2);
			ofCircle(cur, 2);
	}

/*
	int n = mesh.getNumVertices();
	float nearestDistance = 0;
	ofVec2f nearestVertex;
	int nearestIndex;
	ofVec2f mouse(mouseX, mouseY);
	for(int i = 0; i < n; i++) {
		ofVec3f cur = cam.worldToScreen(mesh.getVertex(i));
		if(i<80){
			ofSetColor(ofColor::yellow);
			ofSetLineWidth(2);
			ofCircle(cur, 4);
		}
		float distance = cur.distance(mouse);
		if(i == 0 || distance < nearestDistance) {
			nearestDistance = distance;
			nearestVertex = cur;
			nearestIndex = i;
		}
	}
	
	ofSetColor(ofColor::gray);
	ofLine(nearestVertex, mouse);
	
	ofNoFill();
	ofSetColor(ofColor::yellow);
	ofSetLineWidth(2);
	ofCircle(nearestVertex, 4);
	ofSetLineWidth(1);
	
	ofVec2f offset(10, -10);
	ofDrawBitmapStringHighlight(ofToString(nearestIndex), mouse + offset);*/
}

//--------------------------------------------------------------
void GLOW::keyPressed(int key){

}

//--------------------------------------------------------------
void GLOW::keyReleased(int key){
	if(key>48 && key <53){
		AttractTo=key-48;
	}
}

//--------------------------------------------------------------
void GLOW::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void GLOW::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void GLOW::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void GLOW::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void GLOW::windowResized(int w, int h){

}

//--------------------------------------------------------------
void GLOW::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void GLOW::dragEvent(ofDragInfo dragInfo){ 

}