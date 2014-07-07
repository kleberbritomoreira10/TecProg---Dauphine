#include "LevelBoss.h"
#include "Game.h"
#include "LuaScript.h"
#include "Logger.h"
#include "Enemy.h"
#include "Crosshair.h"
#include "TileMap.h"
#include "Collision.h"

LevelBoss::LevelBoss() :
	Level()
{

}

LevelBoss::~LevelBoss(){

}

void LevelBoss::load(){
	Log(DEBUG) << "Loading level boss...";

	// Loading the tile/tilemap.
	this->tileMap = new TileMap("res/maps/levelBoss.tmx");

	// Setting the level width/height.
	this->width = this->tileMap->getMapWidth();
	this->height = this->tileMap->getMapHeight();
	SDL_Rect bounds = {0, 0, (int)this->width, (int)this->height};
	this->quadTree = new QuadTree(0, bounds);

	this->background = Game::instance().getResources().get("res/images/lv1_background.png");

	// Getting information from lua script.
	LuaScript luaLevel1("lua/Level1.lua");
	const std::string pathPlayerSpriteSheet = luaLevel1.unlua_get<std::string>(
		"level.player.spriteSheet");
	const std::string pathBackgroundAudio = luaLevel1.unlua_get<std::string>(
		"level.audio.background");
	const std::string pathEnemy = luaLevel1.unlua_get<std::string>("level.enemy");

	// Changing the music.
	Game::instance().getAudioHandler().changeMusic(pathBackgroundAudio);

	// Loading the player and the camera.
	Player* lPlayer = new Player(this->tileMap->getInitialX(), this->tileMap->getInitialY(), pathPlayerSpriteSheet);
	Camera* lCamera = new Camera(lPlayer); 

	this->playerHud = new PlayerHUD(lPlayer);

	Boss* lBoss = new Boss(1200, 684.0, pathEnemy, lPlayer);
	lBoss->getAnimation()->changeAnimation(0,0,1,false,0.0);
	
	// Test text.
	// Text* text = new Text(200.0, 900.0, "res/fonts/KGFeeling22.ttf", 50, "dauphine");
	// addEntity(text);

	// Finally, setting the player, the boss and the camera.
	setPlayer(lPlayer);
	setBoss(lBoss);
	setCamera(lCamera);

	Game::instance().getFade().fadeOut(0, 0.002);
}

void LevelBoss::unload(){
	Log(DEBUG) << "\tUnloading level boss...";
	cleanEntities();
	clearEnemies();
}

void LevelBoss::update(const double dt_){

	// Populating the QuadTree.
	this->quadTree->setObjects(this->tileMap->getCollisionRects());

	// Updating the entities, using the QuadTree.
	std::vector<CollisionRect> returnObjects;
	for (auto entity : this->entities) {
		returnObjects.clear();
		this->quadTree->retrieve(returnObjects, entity->getBoundingBox());
		entity->setCollisionRects(returnObjects);
		entity->update(dt_);
	}

	// Set to GameOver if the player is dead.
	if(this->player->isDead()){
		Game::instance().setState(Game::GStates::GAMEOVER);
		return;
	}

	// Updating the potions.
	for(auto potion : this->player->potions){
		returnObjects.clear();
		this->quadTree->retrieve(returnObjects, potion->getBoundingBox());
		potion->setCollisionRects(returnObjects);
	}

	if(this->boss->x < this->player->x + 10 && this->boss->x > this->player->x - 10){
		this->boss->sawPlayer = true;
	}

	// Updating the HUD.
	this->playerHud->update();

	// Updating the boss.
	this->boss->update(dt_);

	// Updating the camera.
	this->camera->update();

	// Set next level if end is reached.
	if(this->player->reachedLevelEnd){
		Game::instance().setState(Game::GStates::LEVEL_ONE);
		return;
	}

	// Updating the potion/enemy collision.
	for(auto potion : this->player->potions){
		for(auto enemy : this->enemies){
			if(Collision::rectsCollided(potion->getBoundingBox(), enemy->getBoundingBox())){
				if(potion->activated){
					enemy->changeState(Enemy::EStates::DEAD);
				}
			}
		}
	}

	// Updating the player attack/enemy collision.
	for(auto enemy : this->enemies){
		if(Collision::rectsCollided(this->player->getBoundingBox(), enemy->getBoundingBox())){
			if(this->player->isCurrentState(Player::PStates::ATTACK) || this->player->isCurrentState(Player::PStates::ATTACKMOVING)){
				enemy->changeState(Enemy::EStates::DEAD);
			}
		}
	}
	
}

void LevelBoss::render(){
	const int cameraX = this->camera->getClip().x;
	const int cameraY = this->camera->getClip().y;

	this->background->render(0, 0);

	// Render the tiles in the TileMap.
	this->tileMap->render(cameraX, cameraY);

	this->playerHud->render();

	this->boss->render(cameraX, cameraY);

	// Render all the entities in the list.
	for(auto entity : this->entities){
        entity->render(cameraX, cameraY);
	}
}

