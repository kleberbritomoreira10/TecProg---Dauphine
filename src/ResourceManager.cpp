#include "ResourceManager.h"

ResourceManager::ResourceManager() :
	resources()
{

}

ResourceManager::~ResourceManager(){

}

SpritePtr ResourceManager::get(const std::string& name_){
	std::map<std::string,SpritePtr>::iterator it;
	it = this->resources.find(name_);

	if (it != this->resources.end()){
		return it->second;
	}

	return nullptr;
}

void ResourceManager::registerResource(const std::string& name_, SpritePtr resource_){
	this->resources.insert( std::make_pair(name_, resource_) );
}

void ResourceManager::unregisterResource(const std::string& name_){
	std::map<std::string,SpritePtr>::iterator it;
	it = this->resources.find(name_);

	if (it != this->resources.end()){
		this->resources.erase(it);
	}
}

SpritePtr ResourceManager::load(const std::string& path_){
	SpritePtr sprite = std::make_shared<Sprite>(path_);
	registerResource(path_, sprite);
	return sprite;
}

void ResourceManager::free(const std::string& name_){
	this->unregisterResource(name_);
}
