#pragma once

#include "ofMain.h"
#include "TCollection.h"

class GLOW : public ofBaseApp{
	public:
		class PixelGrid;
		class Creature;
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		PixelGrid *PG;
		ofEasyCam cam;
		ofMesh mesh;
		vector<Creature> Creatures;
		int creatureCount;
		int CanvasOffsetX;
		int CanvasOffsetY;
		int AttractTo;//1 up	2 right		3 down		4 left;
};
class GLOW::PixelGrid{
public:
	PixelGrid(int RowCount,int ColumnCount);
	void CreateGrid();
	class PixelRow;	
	TCollection<PixelRow> PixelrowColection;
	int RowCount;
	int ColumnCount;
};

class GLOW::PixelGrid::PixelRow{
	public:
	int rowNR;
	class PixelColumn;
	TCollection<PixelColumn> PixelColumnColection;

};
class GLOW::PixelGrid::PixelRow::PixelColumn{
	public:
	int ColumnNR;
	bool CreatureSpot;
	ofVec3f Vertex;
};

class GLOW::Creature{
	public:
		int ID;
		int x;
		int y;
		int direction; //1 up	2 right		3 down		4 left;
		void MoveCreature(GLOW::PixelGrid* PG,int AttractTo);
		void InitCreature(GLOW::PixelGrid* PG);
		int speed;
		
};
