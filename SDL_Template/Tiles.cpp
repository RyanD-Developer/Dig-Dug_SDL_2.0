#include "Tiles.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
void Tiles::Visible(bool visible) {
	mVisible = visible;
}
bool Tiles::ReturnVisible() {
	return mVisible;
}
bool Tiles::IgnoreCollisions(){
	return true;
}
Tiles::Tiles() {
	mTile = new GLTexture("DigPiece.png", 0, 0, 48, 48);
	mTile->Position(Vector2(0.0f, 0.0f));
	mTile->Parent(this);

	Visible(false);
}

Tiles::~Tiles() {
	delete mTile;
	mTile = nullptr;
}
void Tiles::Update() {
	
}

void Tiles::Render() {
	if (!mVisible) {

	}
	else if (mVisible) {
	    mTile->Render();
	}

	PhysEntity::Render();
}