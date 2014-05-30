#include "LevelOne.h"
#include "Game.h"
#include "LuaScript.h"
#include "Logger.h"
#include "Enemy.h"
#include "Crosshair.h"
#include "TileMap.h"

LevelOne::LevelOne() :
	Level()
{

}

LevelOne::~LevelOne(){

}

void LevelOne::load(){
	Log(DEBUG) << "Loading level 1...";

	// Loading the tile/tilemap.
	this->tileMap = new TileMap("res/maps/level1.tmx");

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
	const double initialPlayerX = luaLevel1.unlua_get<double>("level.player.position.x");
	const double initialPlayerY = luaLevel1.unlua_get<double>("level.player.position.y");
	const std::string pathBackgroundAudio = luaLevel1.unlua_get<std::string>(
		"level.audio.background");
	const std::string pathTileSheet = luaLevel1.unlua_get<std::string>("level.tileSheet");
	const std::string pathTempEnemy = luaLevel1.unlua_get<std::string>("level.dummyEnemy");

	// Changing the music.
	Game::instance().getAudioHandler().changeMusic(pathBackgroundAudio);

	// Loading the sprites.
	Sprite* spritePlayer = Game::instance().getResources().get(pathPlayerSpriteSheet);

	// Loading the player and the camera.
	Player* lPlayer = new Player(initialPlayerX, initialPlayerY, spritePlayer);
	Camera* lCamera = new Camera(lPlayer);

	Sprite* spriteCrosshair = Game::instance().getResources().get("res/images/alvo.png");
	Crosshair* crosshair = new Crosshair(500, 600, spriteCrosshair);

	Sprite* spriteBombPotion = Game::instance().getResources().get("res/images/potion.png");
	BombPotion* bombPotion = new BombPotion(300, 600, spriteBombPotion);

	addEntity(crosshair);
	addEntity(bombPotion);

	lPlayer->setCrosshair(crosshair);
	lPlayer->setBombPotion(bombPotion);

	Sprite* spriteEnemy = Game::instance().getResources().get(pathTempEnemy);
	Enemy* enemy = new Enemy(704.0, 0.0, spriteEnemy, true, 200.0);
	enemy->setLevelWH(this->width, this->height);
	addEntity(enemy);
	
	// Test text.
	// Text* text = new Text(200.0, 900.0, "res/fonts/KGFeeling22.ttf", 50, "dauphine");
	// addEntity(text);

	// Finally, setting the player and the camera.
	setPlayer(lPlayer);
	setCamera(lCamera);
}

void LevelOne::unload(){
	Log(DEBUG) << "\tUnloading level 1...";
	cleanEntities();
}

void LevelOne::update(const double dt_){
	// Populating the QuadTree.
	this->quadTree->setObjects(this->tileMap->getCollisionRects());

	// // Updating the entities, using the QuadTree.
	std::vector<SDL_Rect> returnObjects;
	for (auto entity : this->entities) {
		returnObjects.clear();
		this->quadTree->retrieve(returnObjects, entity->getBoundingBox());
		entity->setCollisionRects(returnObjects);
		entity->update(dt_);
	}

	/// @todo Refactor this static Enemy::px, Enemy::py.
	Enemy::px = this->player->x;
	Enemy::py = this->player->y;

	this->camera->update();
}

void LevelOne::render(){
	const int cameraX = this->camera->getClip().x;
	const int cameraY = this->camera->getClip().y;

	this->background->render(0, 0);

	// Render the tiles in the TileMap.
	this->tileMap->render(cameraX, cameraY);

	// Render all the entities in the list.
	for(auto entity : entities){
        entity->render(cameraX, cameraY);
	}
}

