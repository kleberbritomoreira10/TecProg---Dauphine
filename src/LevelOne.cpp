#include "LevelOne.h"
#include "Game.h"
#include "LuaScript.h"
#include "Logger.h"
#include "Enemy.h"
#include "TmxWrapper.h"
#include "TileMap.h"

LevelOne::LevelOne() :
	Level()
{

}

LevelOne::~LevelOne(){

}

void LevelOne::load(){
	Logger::verbose("Loading level 1...");

	// Changing the music.
	Game::instance().getAudioHandler().changeMusic("res/idk.ogg");

	// Getting information from lua script.
	LuaScript luaLevel1("lua/Level1.lua");
	const std::string scriptPlayerSpritePath = luaLevel1.unlua_get<std::string>(
		"level.player.spritePath");
	const double scriptX = luaLevel1.unlua_get<double>("level.player.position.x");
	const double scriptY = luaLevel1.unlua_get<double>("level.player.position.y");

	// Loading the sprites.
	Sprite* spritePlayer = nullptr;
	spritePlayer = Game::instance().getResources().get(scriptPlayerSpritePath);

	// Loading the player and the camera.
	Player* lPlayer = new Player(scriptX, scriptY, spritePlayer);
	Camera* lCamera = new Camera(lPlayer);

	// Loading the tile/tilemap.
	TmxWrapper tmxw("res/maps/level1.tmx");
	TileMap* tileMap = new TileMap(tmxw.getTileData(), "res/tilesheet.png");
	addEntity(tileMap);
	lPlayer->setTiles(tileMap->tiles);

	this->width = tmxw.getMapWidth();
	this->height = tmxw.getMapHeight();

	Sprite* spriteEnemy;
	spriteEnemy = Game::instance().getResources().get("res/InimigoVigilia.png");
	Enemy* enemy = new Enemy(1100.0, 400.0, spriteEnemy, true, 200.0);
	enemy->setLevelWH(this->width, this->height);
	addEntity(enemy);

	setPlayer(lPlayer);
	setCamera(lCamera);
}

void LevelOne::unload(){
	Logger::verbose("\tUnloading level 1...");
	cleanEntities();
}

void LevelOne::update(const double dt_){
	// Update all the entities in the list.
	for(auto entity : entities){
        entity->update(dt_);
	}

	Enemy::px = this->player->x;
	Enemy::py = this->player->y;

	this->camera->update();
}

void LevelOne::render(){
	const int cameraX = this->camera->getClip().x;
	const int cameraY = this->camera->getClip().y;

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
