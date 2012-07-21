#pragma once

#include "ofMain.h"
#include "TCollection.h"
//declaraties van classes en functies

//Hoofd class
class GLOW : public ofBaseApp{
	public:
		class PixelGrid;
		class Creature;
		class NearCreatureInfo;
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

		PixelGrid *PG;	//Pixelgrid, soort array maar dan in object vorm
		ofEasyCam cam;	//3D camera
		ofMesh mesh;	//3D omgeving
		vector<Creature> Creatures;		//verzameling beestjes
		int creatureCount;	//aantal beestjes

		//bepalen waar het grid getekend word
		int CanvasOffsetX;
		int CanvasOffsetY;

		//richtingen waar het beestje naar toe kan
		int AttractTo;//1 up	2 right		3 down		4 left;
		int GridXcount;
		int GridYcount;

};
class GLOW::PixelGrid{
public:
	PixelGrid(int RowCount,int ColumnCount);
	void CreateGrid(); //functie die het grid vult
	class PixelRow;	//declaratie van 1 pixelrij
	TCollection<PixelRow> PixelrowColection; //declaratie rij collectie
	int RowCount; //aantal rijen in het grid
	int ColumnCount; // aantal kolommen in het grid
};

class GLOW::PixelGrid::PixelRow{
	public:
	int rowNR;
	class PixelColumn; //declaratie van 1 pixelkolom
	TCollection<PixelColumn> PixelColumnColection; //declaratie kolom collectie

};
class GLOW::PixelGrid::PixelRow::PixelColumn{
	public:
	int ColumnNR;
	bool CreatureSpot;	//geeft aan of er een beestje op deze locatie staat
	ofVec3f Vertex;	//3d coordinaat voor het 3Dgrid
};


//beestje
class GLOW::Creature{
	public:
		int ID;	//uniek ID van het Beestje
		float x;	//x positie op het grid
		float y;	//y positie op het grid
		int direction; //1 up	2 right		3 down		4 left;
		void MoveCreature(GLOW::PixelGrid* PG,int AttractTo);	//functie om beestje te verplaatsen (60 x per seconde)
		void FindCreatures(GLOW::PixelGrid* PG,vector<Creature> & Creatures);
		void InitCreature(GLOW::PixelGrid* PG);		//initialisatie van het beestje, bepaald de beginwaardes
		int speed; // snelheid van het beestje
		int speedCounter;
		vector<GLOW::NearCreatureInfo*> NearCreatures;
		ofColor Kleur; //kleur van het beestje
};
class GLOW::NearCreatureInfo{
	public:
	int ID;
	float DistanceToCreature;

};
