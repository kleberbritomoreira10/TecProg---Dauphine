#include "LevelOne.h"
#include "AudioHandler.h"
#include "LuaScript.h"
#include "Logger.h"

#include "TileMap.h"

#include <fstream>

LevelOne::LevelOne() :
	Level()
{

}

LevelOne::~LevelOne(){

}

void LevelOne::load(){
	Logger::verbose("Loading level 1...");

	// Changing the music.
	AudioHandler* audioHandler = AudioHandler::getInstance();
	audioHandler->changeMusic("res/idk.ogg");

	// Getting information from lua script.
	LuaScript luaLevel1("lua/Level1.lua");
	const std::string scriptPlayerSpritePath = luaLevel1.unlua_get<std::string>(
		"level.player.spritePath");
	const std::string scriptBackgroundSpritePath = luaLevel1.unlua_get<std::string>(
		"level.background.spritePath");
	const double scriptX = luaLevel1.unlua_get<double>("level.player.position.x");
	const double scriptY = luaLevel1.unlua_get<double>("level.player.position.y");
	const unsigned int levelW = luaLevel1.unlua_get<int>("level.boundaries.width");
	const unsigned int levelH = luaLevel1.unlua_get<int>("level.boundaries.height");

	// Loading the sprites.
	Sprite* spriteLevelBackground = nullptr;
	spriteLevelBackground = new Sprite(scriptBackgroundSpritePath);

	Sprite* spritePlayer = nullptr;
	spritePlayer = new Sprite(scriptPlayerSpritePath);

	// Loading the player and the camera.
	Player* lPlayer = new Player(scriptX, scriptY, spritePlayer);

	Camera* lCamera = new Camera(lPlayer);

	this->background = spriteLevelBackground;
	if(this->background == nullptr){
		Logger::warning("Level background is null! No background will be set.");
	}

	this->width = levelW;
	this->height = levelH;

	// Loading the tile/tilemap.
	std::ifstream mapFile("res/maps/level1.map");

	int numberOfTiles = 0;
	mapFile >> numberOfTiles;
	std::vector<int> tileData;
	for(int i = 0; i < numberOfTiles; i++){
		int tileType = 0;
		mapFile >> tileType;
		tileData.push_back(tileType);
	}

	TileMap* tileMap = new TileMap(tileData);

	addEntity(tileMap);
	lPlayer->setTiles(tileMap->tiles);

	setPlayer(lPlayer);
	setCamera(lCamera);
	Logger::verbose("Done loading level 1...");
}

void LevelOne::unload(){
	Logger::verbose("Unloading level 1...");
	cleanEntities();
}

void LevelOne::update(double dt_){
	// Update all the entities in the list.
	for(Entity* entity : entities){
        entity->update(dt_);
	}

	this->camera->update();
}

void LevelOne::render(){
	if(this->background != nullptr){
		this->background->render(0, 0, &this->camera->getClip());
	}
	else{
		Logger::warning("No background set for this Level!");
	}

	const int cameraX = this->camera->getClip().x;
	const int cameraY = this->camera->getClip().y;

	// Render all the entities in the list.
	for(Entity* entity : entities){
        entity->render(cameraX, cameraY);
	}
}

void LevelOne::setPlayer(Player* player_){
	this->player = player_;

	if(this->player != nullptr){
		this->player->setLevelWH(this->width, this->height);
		addEntity(this->player);
	}
	else{
		Logger::warning("Setting a null player!");
	}
	
}

void LevelOne::setCamera(Camera* camera_){
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
