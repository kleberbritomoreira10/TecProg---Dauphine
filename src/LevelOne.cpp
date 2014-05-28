#include "LevelOne.h"
#include "Game.h"
#include "LuaScript.h"
#include "Logger.h"
#include "Enemy.h"
#include "TmxWrapper.h"
#include "TileMap.h"

#include "Text.h"

LevelOne::LevelOne() :
	Level()
{

}

LevelOne::~LevelOne(){

}

void LevelOne::load(){
	Logger::verbose("Loading level 1...");

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
	Sprite* spritePlayer = nullptr;
	spritePlayer = Game::instance().getResources().get(pathPlayerSpriteSheet);

	// Loading the player and the camera.
	Player* lPlayer = new Player(initialPlayerX, initialPlayerY, spritePlayer);
	Camera* lCamera = new Camera(lPlayer);

	// Loading the tile/tilemap.
	this->tileMap = new TileMap("res/maps/level1.tmx");
	//lPlayer->setTiles(tileMap->tiles);

	// Setting the level width/height.
	this->width = this->tileMap->getMapWidth();
	this->height = this->tileMap->getMapHeight();

	// Test enemy.
	Sprite* spriteEnemy;
	spriteEnemy = Game::instance().getResources().get(pathTempEnemy);
	Enemy* enemy = new Enemy(704.0, 0.0, spriteEnemy, true, 200.0);
	enemy->setLevelWH(this->width, this->height);
	//enemy->setTiles(tileMap->tiles);
	addEntity(enemy);

	// Test text.
	// Text* text = new Text(200.0, 900.0, "res/fonts/KGFeeling22.ttf", 50, "dauphine");
	// addEntity(text);

	// Finally, setting the player and the camera.
	setPlayer(lPlayer);
	setCamera(lCamera);
}

void LevelOne::unload(){
	Logger::verbose("\tUnloading level 1...");
	cleanEntities();
}

void LevelOne::update(const double dt_){
	Logger::verbose("Updating level 1...");

	// Update all the entities in the list.
	for(auto entity : entities){
        entity->update(dt_);
	}

	/// @todo Refactor this static Enemy::px, Enemy::py.
	Enemy::px = this->player->x;
	Enemy::py = this->player->y;

	this->camera->update();
}

void LevelOne::render(){
	Logger::verbose("Rendering level 1...");

	const int cameraX = this->camera->getClip().x;
	const int cameraY = this->camera->getClip().y;

	Logger::verbose("Rendering level 1 TileMap...");
	// Render the tiles in the TileMap, by layers.
	for(unsigned int i = 0; i < this->tileMap->getLayers(); i++){
		Logger::verbose("number: " + std::to_string(i));
		this->tileMap->renderLayer(cameraX, cameraY, i);
	}

	Logger::verbose("Rendering level 1 entities...");
	// Render all the entities in the list.
	for(auto entity : entities){
        entity->render(cameraX, cameraY);
	}
}

void LevelOne::setPlayer(Player* const player_){
	this->player = player_;

	if(this->player != nullptr){
		this->player->setLevelWH(this->width, this->height);
		addEntity(this->player);
	}
	else{
		Logger::warning("Setting a null player!");
	}
	
}

void LevelOne::setCamera(Camera* const camera_){
	this->camera = camera_;

	if(this->camera != nullptr){
		if(this->player != nullptr){
			this->camera->setLevelWH(this->width, this->height);
		}
		else{
			Logger::warning("Shouldn't set the camera before the player, in Level!");
		}
	}
	else{
		Logger::warning("Setting a null camera!");
	}

}
