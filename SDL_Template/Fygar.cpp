#include "Fygar.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "InputManager.h"
bool Fygar::IgnoreCollisions() {
	return HarpoonStriked || Dead || mAnimating;
}

Fygar::Fygar() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	mInput = InputManager::Instance();
	mMoveSpeed = 100.0f;
	mAnimFrame = 1;
    LeaveTunnel = false;
	GhostForm = false;
    Ghost = (std::rand() % 25) + 5;
	FireTimer = (std::rand() % 10) + 5;
	mTimerGhost = 0;
	mMoveBounds = Vector2(27.0f, 652.0f);
	mWalking = new AnimatedGLTexture("Fygars.png", 0, 0, 44, 42, 2, 0.25f, Animation::Layouts::Horizontal);
	mWalking->Parent(this);
	mWalking->Position(Vec2_Zero);
	mGhostForm = new AnimatedGLTexture("Fygars.png", 141, 9, 45, 33, 2, 0.25f, Animation::Layouts::Horizontal);
	mGhostForm->Parent(this);
	mGhostForm->Position(Vec2_Zero);
	mPreFire = new AnimatedGLTexture("Fygars.png",45, 0, 44, 42, 2, 0.1f, Animation::Layouts::Horizontal);
	mPreFire->Parent(this);
	mPreFire->Position(Vec2_Zero);
	mDeath2 = new GLTexture("Death2.png", 0, 0, 39, 22);
	mDeath2->Parent(this);
	mDeath2->Position(Vector2(0.0f, 10.0f));
	mFDeath1 = new GLTexture("FDeath1.png", 0, 0, 42, 42);
	mFDeath2 = new GLTexture("FDeath2.png", 0, 0, 60, 56);
	mFDeath3 = new GLTexture("FDeath3.png", 0, 0, 60, 64);
	mFDeath4 = new GLTexture("FDeath4.png", 0, 0, 72, 69);
	mFDeath1->Parent(this);
	mFDeath1->Position(Vector2(0.0f, 0.0f));
	mFDeath2->Parent(this);
	mFDeath2->Position(Vector2(0.0f, 0.0f));
	mFDeath3->Parent(this);
	mFDeath3->Position(Vector2(0.0f, 0.0f));
	mFDeath4->Parent(this);
	mFDeath4->Position(Vector2(0.0f, 0.0f));
	mFire = new GLTexture("Fygars.png", 6, 57, 45, 39);
	mFire1 = new GLTexture("Fygars.png", 60, 48, 96, 48);
	mFire2 = new GLTexture("Fygars.png", 162, 51, 144, 48);
	mFire->Parent(this);
	mFire->Position(Vector2(22.5f, 0.0f));
	mFire1->Parent(this);
	mFire1->Position(Vector2(48.0f, 0.0f));
	mFire2->Parent(this);
	mFire2->Position(Vector2(72.0f, 0.0f));
	GoingTowards = "Right";
	Dead = false;
	AddCollider(new BoxCollider(Vector2(35.0f, 30.0f)));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
}

Fygar::~Fygar() {
	delete mWalking;
	mWalking = nullptr;
	delete mGhostForm;
	mGhostForm = nullptr;
	delete mDeath2;
	mDeath2 = nullptr;
	delete mFDeath1;
	mFDeath1 = nullptr;
	delete mFDeath2;
	mFDeath2 = nullptr;
	delete mFDeath3;
	mFDeath3 = nullptr;
	delete mFDeath4;
	mFDeath4 = nullptr;
	delete mPreFire;
	mPreFire = nullptr;
	delete mFire;
	mFire = nullptr;
	delete mFire1;
	mFire1 = nullptr;
	delete mFire2;
	mFire2 = nullptr;
}

void Fygar::Update() {
	if (GoingTowards == "Right") {
		mFire->Scale(Vector2(1.0f, 1.0f));
		mFire1->Scale(Vector2(1.0f, 1.0f));
		mFire2->Scale(Vector2(1.0f, 1.0f));
		mFire->Position(Vector2(27.5f, 0.0f));
		mFire1->Position(Vector2(53.0f, 0.0f));
		mFire2->Position(Vector2(77.0f, 0.0f));
	}
	else if (GoingTowards == "Left" || GoingTowards == "Up" || GoingTowards == "Down") {
		mFire->Scale(Vector2(-1.0f, 1.0f));
		mFire1->Scale(Vector2(-1.0f, 1.0f));
		mFire2->Scale(Vector2(-1.0f, 1.0f));
		mFire->Position(Vector2(-27.5f, 0.0f));
		mFire1->Position(Vector2(-53.0f, 0.0f));
		mFire2->Position(Vector2(-77.0f, 0.0f));
	}
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
	else if (Active() && FireBreath() == false) {
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
	else {
		mPreFire->Update();
	}
}
void Fygar::SetLO(bool LO) {
	LastOne = LO;
}
bool Fygar::GetDone() {
	return Done;
}
void Fygar::Render() {
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
				mFDeath1->Render();
			}
			else if (mAnimFrame <= 4) {
 				mFDeath2->Render();
			}
			else if (mAnimFrame <= 6) {
				mFDeath3->Render();
			}
			else if (mAnimFrame <= 7) {
				mFDeath4->Render();
			}
			else if (mAnimFrame > 7) {
                mAudio->PlaySFX("MonsterBlow.mp3");
			    Dead = true;
			}
		}
		else if (!mWasHit) {
		mAudio->PlaySFX("MonsterBlow.mp3");
		mDeath2->Render();
		}
	}
	else {
		if (Active()) {
			mWasHit = false;
			mAnimFrame = 1;
			if (!GhostForm && FireBreath() == false) {
				mWalking->Render();
			}
			else if (FireBreath() == false) {
				mGhostForm->Render();
			}
			if (FireBreath() == false && !GhostForm) {
				mFireTimer += 0.026;
			} if (mFireTimer > FireTimer) {
				mFireTimer = 0;
				mFireBreath = true;
			}
			if (FireBreath() == true){
			    mAnimFrame2 += 0.026;
			}
			if (FireBreath() == true && mAnimFrame2 <= 3) {
				mPreFire->Render();
			} else if (FireBreath() == true && mAnimFrame2 <= 5) {
				mFire->Render();
				mWalking->Render();
			}
			else if (FireBreath() == true && mAnimFrame2 <= 7) {
				mFire1->Render();
				mWalking->Render();
			}
			else if (FireBreath() == true && mAnimFrame2 <= 9) {
				mFire2->Render();
				mWalking->Render();
			}
			else if (FireBreath() == true && mAnimFrame2 > 9) {
				mAnimFrame2 = 0;
				mFireBreath = false;
			}
		}
	}
	 PhysEntity::Render();
}
void Fygar::HandleMovement() {
	if (InPlace) {
		if (mWalking->Position().x > -50.0f) {
			mWalking->Scale(Vector2(-1.0f, 1.0f));
			mPreFire->Scale(Vector2(-1.0f, 1.0f));
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
					mPreFire->Scale(Vector2(1.0f, 1.0f));
					mWalkingX = mWalking->Position().x;
				}
				else {
					if (mWalking->Position().x < TilePos.x + 3) {
						Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
					}
					else {
						Previous = "Right";
						GoingTowards = "Null";
					}
				}
			}
			else if (GoingTowards == "Left") {
				if (mTileLeft) {
					Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
					mWalking->Scale(Vector2(-1.0f, 1.0f));
					mPreFire->Scale(Vector2(-1.0f, 1.0f));
					mWalkingX = mWalking->Position().x;
				}
				else {
					if (mWalking->Position().x > TilePos.x + 3) {
						Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
					}
					else {
						Previous = "Left";
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
						mPreFire->Scale(Vector2(-1.0f, 1.0f));
						mWalkingX = mWalking->Position().y;
					}
					else {
						if (mWalking->Position().y > TilePos.y + 5) {
							Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
						}
						else {
							Previous = "Up";
							GoingTowards = "Null";
						}
					}
				}
			}
			else if (GoingTowards == "Down") {
				if (mTileBelow) {
					Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
					mWalking->Scale(Vector2(-1.0f, 1.0f));
					mPreFire->Scale(Vector2(-1.0f, 1.0f));
					mWalkingX = mWalking->Position().y;

				}
				else {
					if (Position().y < TilePos.y + 2) {
						Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
					}
					else {
						Previous = "Down";
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


	void Fygar::Hit(PhysEntity * other) {
	GoingTowards = "None";
}

bool Fygar::FireBreath() {
 return mFireBreath;
}

void Fygar::HarpoonHit() {
	mWasHit = true;
	WasHit();
}

bool Fygar::WasHit() {
	mAnimating = true;
	//mAudio->PlaySFX
	return mWasHit;
}

void Fygar::SetTile(int Tile) {
	mTile = Tile;
}

void Fygar::SurroundTiles(bool left, bool right, bool up, bool down, bool tile) {
	mTileLeft = left;
	mTileRight = right;
	mTileAbove = up;
	mTileBelow = down;
	mTileVis = tile;
}
void Fygar::AnimFrameSet() {
	mTimeSide1 = 0;
	mAnimFrame += 1;
}

void Fygar::HarpoonStrike(bool hs) {
	HarpoonStriked = hs;
}

bool Fygar::GetHPS() {
	return HarpoonStriked;
}
bool Fygar::GetDead() {
	return Dead;
}

void Fygar::SetDead(bool Dead2) {
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
void Fygar::Reset() {
	mWasHit = false;
	HarpoonStriked = false;
}
int Fygar::GetFrame() {
	return mAnimFrame;
}
void Fygar::SetDirection(std::string dir) {
	GoingTowards = dir;
}
void Fygar::SetPlayerPos(Vector2 PPos) {
	PlayerPos = PPos;
}
void Fygar::HandleDirection() {
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
		}
		else if (std::rand() % 3 == 1) {
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
		}
		else if (std::rand() % 3 == 2) {
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

		}
		else if (std::rand() % 3 == 3) {
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

void Fygar::SetTilePos(Vector2 TP) {
	TilePos = TP;
}

void Fygar::CheckIfClear(std::string dir) {
	if (dir == "Null") {
		Check = false;
		DirCheck = dir;
	}
	else {
		Check = true;
		DirCheck = dir;
	}
}

int Fygar::GetTile() {
	return mTile;
}
std::string Fygar::GetDirC() {
	return DirCheck;
}
bool Fygar::NeedCheck() {
	return Check;
}
void Fygar::SetMS(int Move) {
	mMoveSpeed = Move;
}