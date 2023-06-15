#include "Pooka.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
bool Pooka::IgnoreCollisions() {
	return HarpoonStriked || Dead || mAnimating;
}

Pooka::Pooka() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mMoveSpeed = 100.0f;
	mAnimFrame = 1;
	LeaveTunnel = false;
	LastOne = false;
	Ghost = (std::rand() % 25) + 5;
	GhostForm = false;
	mTimerGhost = 0;
	mMoveBounds = Vector2(27.0f, 652.0f);
	mWalking = new AnimatedGLTexture("Pooka.png", 0, 0, 44, 42, 2, 0.25f, Animation::Layouts::Horizontal);
	mWalking->Parent(this);
	mWalking->Position(Vec2_Zero);
	mGhostForm = new AnimatedGLTexture("PookaGhost.png", 0, 0, 39, 22, 2, 0.25f, Animation::Layouts::Horizontal);
	mGhostForm->Parent(this);
	mGhostForm->Position(Vec2_Zero);
	mDeath1 = new GLTexture("DeathP1.png", 0, 0, 40, 21);
	mDeath1->Parent(this);
	mDeath1->Position(Vector2(0.0f, 10.0f));
	mPDeath1 = new GLTexture("PDeath1.png", 0, 0, 42, 42);;
	mPDeath2 = new GLTexture("PDeath2.png", 0, 0, 60, 48);;
	mPDeath3 = new GLTexture("PDeath3.png", 0, 0, 63, 57);;
	mPDeath4 = new GLTexture("PDeath4.png", 0, 0, 72, 56);;
	mPDeath1->Parent(this);
	mPDeath1->Position(Vector2(0.0f, 0.0f));
	mPDeath2->Parent(this);
	mPDeath2->Position(Vector2(0.0f, 0.0f));
	mPDeath3->Parent(this);
	mPDeath3->Position(Vector2(0.0f, 0.0f));
	mPDeath4->Parent(this);
	mPDeath4->Position(Vector2(0.0f, 0.0f));
	Dead = false;
	AddCollider(new BoxCollider(Vector2(35.0f, 30.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
}

Pooka::~Pooka() {
	delete mWalking;
	mWalking = nullptr;
	delete mGhostForm;
	mGhostForm = nullptr;
	delete mDeath1;
	mDeath1 = nullptr;
	delete mPDeath1;
	mPDeath1 = nullptr;
	delete mPDeath2;
	mPDeath2 = nullptr;
	delete mPDeath3;
	mPDeath3 = nullptr;
	delete mPDeath4;
	mPDeath4 = nullptr;
}

void Pooka::Update() {
	if (mTimeSide1 >= 2 && mTimeSide1 < 2.028) {
		mAnimFrame -= 1;
	}
	else if (mTimeSide1 >= 2.028) {
		mTimeSide1 = 0;
	}
	if (mAnimating) {

		if (mWasHit) {

		}
		else if (!mWasHit) {
			mTimeSide += 0.026;
			if (mTimeSide >= 3) {
				mAnimating = false;
				Dead = true;
			}
		}
	}
	else if (Active()) {
		mTimeSide1 = 0;
		if (!GhostForm) {
			HandleDirection();
			mTimerGhost += 0.026;
			mWalking->Update();
		}
		else {
			mGhostForm->Update();
		}
		if (!GhostForm && mTimerGhost > Ghost) {
			mTimerGhost = 0;
			GhostForm = true;
		}
		if (LastOne && !InPlace) {
			GhostForm = true;
			mTimerGhost = 0;
		}
		HandleMovement();
	}
}
void Pooka::SetLO(bool LO) {
	LastOne = LO;
}
bool Pooka::GetDone() {
	return Done;
}
void Pooka::Render() {
	if (mAnimating) {

		if (mWasHit) {
			mTimeSide1 += 0.026;
			if (mAnimFrame < 0) {
				mTimeSide1 = 0;
				mWasHit = false;
				HarpoonStriked = false;
				mAnimating = false;
			}
			else if (mAnimFrame <= 2) {
				mPDeath1->Render();
			}
			else if (mAnimFrame <= 4) {
				mPDeath2->Render();
			}
			else if (mAnimFrame <= 6) {
				mPDeath3->Render();
			}
			else if (mAnimFrame <= 7) {
				mPDeath4->Render();
			}
			else if (mAnimFrame > 7) {
                mAudio->PlaySFX("MonsterBlow.mp3");
			    Dead = true;
			}
		}
		else if (!mWasHit) {
            mAudio->PlaySFX("MonsterBlow.mp3");
		    mDeath1->Render();
		}
	}
	else {
		if (Active()) {
			mAnimFrame = 1;
			mWasHit = false;
			if (!GhostForm) {
				mWalking->Render();
			}
			else {
				mGhostForm->Render();
			}
		}
	}
	PhysEntity::Render();
}
void Pooka::HandleMovement() {
	if (InPlace) {
		if (mWalking->Position().x > -50.0f) {
			mWalking->Scale(Vector2(-1.0f, 1.0f));
			Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		}
		else {
			Done = true;
		}
	}
	else {
		if (!GhostForm) {
			if (GoingTowards == "Right") {
				if (mTileRight) {
					Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
					mWalking->Scale(Vector2(1.0f, 1.0f));
					mWalkingX = mWalking->Position().x;
				}
				else {
					if (mWalking->Position().x < TilePos.x + 3) {
						Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
					}
					else {
						GoingTowards = "Null";
					}
				}
			}
			else if (GoingTowards == "Left") {
				if (mTileLeft) {
					Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
					mWalking->Scale(Vector2(-1.0f, 1.0f));
					mWalkingX = mWalking->Position().x;
				}
				else {
					if (mWalking->Position().x > TilePos.x + 3) {
						Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
					}
					else {
						GoingTowards = "Null";
					}
				}
			}
			else if (GoingTowards == "Up") {
				if (mWalking->Position().y < 257.0f) {
					GoingTowards = "Down";
				}
				else {
					if (mTileAbove) {
						Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
						mWalking->Scale(Vector2(-1.0f, 1.0f));
						mWalkingX = mWalking->Position().y;
					}
					else {
						if (mWalking->Position().y > TilePos.y + 5) {
							Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
						}
						else {
							GoingTowards = "Null";
						}
					}
				}
			}
			else if (GoingTowards == "Down") {
				if (mTileBelow) {
					Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
					mWalking->Scale(Vector2(-1.0f, 1.0f));
					mWalkingX = mWalking->Position().y;

				}
				else {
					if (Position().y < TilePos.y + 2) {
						Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
					}
					else {
						GoingTowards = "Null";
					}
				}
			}
		}
		else {
			if (!mTileVis || !LeaveTunnel) {
				if (!LastOne && !InPlace) {
					float dy = PlayerPos.y - Position().y;
					float dx = PlayerPos.x - Position().x;
					float angle = atan2(dy, dx);

					float vx = (mMoveSpeed * mTimer->DeltaTime()) * cos(angle);
					float vy = (mMoveSpeed * mTimer->DeltaTime()) * sin(angle);

					Translate(Vector2(vx, vy), World);
					if (!mTileVis && !LeaveTunnel) {
						LeaveTunnel = true;
					}
					else if (mTileVis && !LeaveTunnel) {
						mTimerGhost += 0.026;
						if (mTimerGhost > 5) {
							LeaveTunnel = false;
							GhostForm = false;
							mTimerGhost = 0;
						}
					}
				}

			}
			else if (!LastOne) {
				if (Position().x < TilePos.x) {
					Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
				}
				else if (Position().x + 44 > TilePos.x + 48) {
					Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
				}
				else if (Position().y < TilePos.y) {
					Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
				}
				else if (Position().y + 42 > TilePos.y + 48) {
					Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
				}
				else {
					LeaveTunnel = false;
					GhostForm = false;
					mTimerGhost = 0;
				}
			} if (!mTileVis || !LeaveTunnel) {
				if (!InPlace && LastOne) {
					float dy = 260.0f - Position().y;
					float dx = 123.0f - Position().x;
					float angle = atan2(dy, dx);

					float vx = (mMoveSpeed * mTimer->DeltaTime()) * cos(angle);
					float vy = (mMoveSpeed * mTimer->DeltaTime()) * sin(angle);

					Translate(Vector2(vx, vy), World);
					if (Position().y < 260.0f) {
						LeaveTunnel = true;
					}
				}

			}
			else if (LastOne) {
				if (Position().x < TilePos.x) {
					Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
				}
				else if (Position().x + 44 > TilePos.x + 48) {
					Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
				}
				else if (Position().y < TilePos.y) {
					Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
				}
				else if (Position().y + 42 > TilePos.y + 48) {
					Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
				}
				else {
					LeaveTunnel = false;
					InPlace = true;
					GhostForm = false;
					mTimerGhost = 0;
				}
			}
		}

		Vector2 pos = Position(Local);
		if (pos.x < mMoveBounds.x) {
			pos.x = mMoveBounds.x;
			GoingTowards = "Right";
		}
		else if (pos.x > mMoveBounds.y) {
			pos.x = mMoveBounds.y;
			GoingTowards = "Left";
		}
		Position(pos);
	}
}
/*
texture = new GLTexture(filename, x, y, w, h)
texture->Position(Vector2(x.0f,y.0f)
texture->Scale(Vector2(x.0f,y.0f)
-----------------------------------------------
delete texture
texture = nullptr
-----------------------------------------------
texture->Render()
*/

void Pooka::Hit(PhysEntity* other) {
	GoingTowards = "None";
}

void Pooka::HarpoonHit() {
	mWasHit = true;
	WasHit();
}

bool Pooka::WasHit() {
	mAnimating = true;
	//mAudio->PlaySFX
	return mWasHit;
}

void Pooka::SetTile(int Tile) {
	mTile = Tile;
}

void Pooka::SurroundTiles(bool left, bool right, bool up, bool down, bool tile) {
	mTileLeft = left;
	mTileRight = right;
	mTileAbove = up;
	mTileBelow = down;
	mTileVis = tile;
}

void Pooka::AnimFrameSet() {
	mTimeSide1 = 0;
	mAnimFrame += 1;
}

void Pooka::HarpoonStrike(bool hs) {
	HarpoonStriked = hs;
}

bool Pooka::GetHPS() {
	return HarpoonStriked;
}
bool Pooka::GetDead() {
	return Dead;
}
void Pooka::SetDead(bool Dead2) {
	mAnimFrame = -1;
	LeaveTunnel = false;
	mTimerGhost = 0;
	GhostForm = false;
	mTimerGhost = 0;
	Done = false;
	InPlace = false;
	LastOne = false;
	Dead = Dead2;
}
void Pooka::Reset() {
	mWasHit = false;
	HarpoonStriked = false;
}
int Pooka::GetFrame() {
	return mAnimFrame;
}
void Pooka::SetDirection(std::string dir) {
	GoingTowards = dir;
}
void Pooka::SetPlayerPos(Vector2 PPos) {
	PlayerPos = PPos;
}
void Pooka::HandleDirection() {
	if (GoingTowards == "Null") {
		if (std::rand() % 3 == 0) {
			if (mTileBelow && PlayerPos.y > std::roundf(Position().y)) {
				GoingTowards = "Down";
			}
			else if (mTileLeft && PlayerPos.x + 1 < std::roundf(Position().x)) {
				GoingTowards = "Left";
			}
			else if (mTileRight && PlayerPos.x + 1 > std::roundf(Position().x)) {
				GoingTowards = "Right";
			}
			else if (mTileLeft) {
				GoingTowards = "Left";
			}
			else if (mTileRight) {
				GoingTowards = "Right";
			}
			else {
				GoingTowards = "Up";
			}
		} else if (std::rand() % 3 == 1) {
			if (mTileAbove && PlayerPos.y < std::roundf(Position().y)) {
				GoingTowards = "Up";
			}
			else if (mTileLeft && PlayerPos.x + 1 < std::roundf(Position().x)) {
				GoingTowards = "Left";
			}
			else if (mTileRight && PlayerPos.x + 1 > std::roundf(Position().x)) {
				GoingTowards = "Right";
			}
			else if (mTileLeft) {
				GoingTowards = "Left";
			}
			else if (mTileRight) {
				GoingTowards = "Right";
			}
			else {
				GoingTowards = "Down";
			}
		} else if (std::rand() % 3 == 2) {
			if (mTileRight && PlayerPos.y + 2 && PlayerPos.x + 1 > std::roundf(Position().x)) {
				GoingTowards = "Right";
			}
			else if (mTileAbove && PlayerPos.y < std::roundf(Position().y)) {
				GoingTowards = "Up";
			}
			else if (mTileBelow && PlayerPos.y > std::roundf(Position().y)) {
				GoingTowards = "Right";
			}
			else if (mTileAbove) {
				GoingTowards = "Up";
			}
			else if (mTileBelow) {
				GoingTowards = "Down";
			}
			else {
				GoingTowards = "Left";
			}

		} else if (std::rand() % 3 == 3) {
			if (mTileLeft && PlayerPos.x + 1 < std::roundf(Position().x)) {
				GoingTowards = "Left";
			}
			else if (mTileAbove && PlayerPos.y < std::roundf(Position().y)) {
				GoingTowards = "Up";
			}
			else if (mTileBelow && PlayerPos.y > std::roundf(Position().y)) {
				GoingTowards = "Right";
			}
			else if (mTileAbove) {
				GoingTowards = "Up";
			}
			else if (mTileBelow) {
				GoingTowards = "Down";
			}
			else {
				GoingTowards = "Right";
			}

		}
	}
	if (!LastOne) {
		if (mTileRight && PlayerPos.y - 2 <= std::roundf(Position().y) && std::roundf(Position().y) <= PlayerPos.y + 2 && PlayerPos.x + 1 > std::roundf(Position().x)) {
			CheckIfClear("R");
		}
		else if (mTileLeft && PlayerPos.y - 2 <= std::roundf(Position().y) && std::roundf(Position().y) <= PlayerPos.y + 2 && PlayerPos.x + 1 < std::roundf(Position().x)) {
			CheckIfClear("L");
		}
		if (mTileAbove && PlayerPos.x - 2 <= std::roundf(Position().x) && std::roundf(Position().x) <= PlayerPos.x + 2 && PlayerPos.y < std::roundf(Position().y)) {
			CheckIfClear("U");
		}
		else if (mTileBelow && PlayerPos.x - 2 <= std::roundf(Position().x) && std::roundf(Position().x) <= PlayerPos.x + 2 && PlayerPos.y > std::roundf(Position().y)) {
			CheckIfClear("D");
		}
	}
}

void Pooka::SetTilePos(Vector2 TP) {
	TilePos = TP;
}

void Pooka::CheckIfClear(std::string dir) {
	if (dir == "Null") {
		Check = false;
		DirCheck = dir;
	}
	else {
		Check = true;
		DirCheck = dir;
	}
}

int Pooka::GetTile() {
	return mTile;
}
std::string Pooka::GetDirC() {
	return DirCheck;
}
bool Pooka::NeedCheck() {
	return Check;
}
void Pooka::SetMS(int Move) {
	mMoveSpeed = Move;
}