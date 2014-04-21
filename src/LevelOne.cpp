#include "LevelOne.h"
#include "LuaScript.h"
#include "Logger.h"

LevelOne::LevelOne() :
	Level()
{

}

LevelOne::~LevelOne(){

}

void LevelOne::update(double dt_){
	this->player->setCameraXY(this->camera->getClip().x, this->camera->getClip().y);
	this->camera->setPlayerXY(this->player->x, this->player->y);
	this->camera->setPlayerWH(this->player->getWidth(), this->player->getHeight());

	// Update all the entities in the list.
	for(Entity *entity : entities){
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

	// Render all the entities in the list.
	for(Entity *entity : entities){
        entity->render();
	}

}

void LevelOne::load(){
	Logger::verbose("Loading level 1...");

	// Getting information from lua script
	LuaScript luaLevel1("lua/Level1.lua");
	const string scriptPlayerSpritePath = luaLevel1.unlua_get<string>("level.player.spritePath");
	const string scriptBackgroundSpritePath = luaLevel1.unlua_get<string>("level.background.spritePath");
	const double scriptX = luaLevel1.unlua_get<double>("level.player.position.x");
	const double scriptY = luaLevel1.unlua_get<double>("level.player.position.y");
	const unsigned int levelW = luaLevel1.unlua_get<int>("level.boundaries.width");
	const unsigned int levelH = luaLevel1.unlua_get<int>("level.boundaries.height");

	// Just an example of Sprite loading, delete this later.
	Sprite *spriteLevelBackground = nullptr;
	spriteLevelBackground = new Sprite(scriptBackgroundSpritePath);

	Sprite *spritePlayer = nullptr;
	spritePlayer = new Sprite(scriptPlayerSpritePath);
	
	Camera *lCamera = new Camera();
	Player *lPlayer = new Player(scriptX, scriptY, spritePlayer);

	this->background = spriteLevelBackground;
	if(this->background == nullptr){
		Logger::warning("Level background is null! No background will be set.");
	}

	this->width = levelW;
	this->height = levelH;

	setPlayer(lPlayer);
	setCamera(lCamera);
}

void LevelOne::unload(){
	Logger::verbose("Unloading level 1...");

	delete this->camera;
	this->camera = nullptr;

	delete this->player;
	this->player = nullptr;

	this->background->free();
	delete this->background;
	this->background = nullptr;

}

void LevelOne::setPlayer(Player *player_){
	this->player = player_;

	if(this->player != nullptr){
		this->player->setLevelWH(this->width, this->height);
		addEntity(this->player);
	}
	else{
		Logger::warning("Setting a null player!");
	}
	
}

void LevelOne::setCamera(Camera *camera_){
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
