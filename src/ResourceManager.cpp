#include "ResourceManager.h"
#include "Logger.h"

ResourceManager::ResourceManager() :
	resources()
{

}

ResourceManager::~ResourceManager(){
	std::map<std::string,Sprite::SpritePtr>::iterator it;
	for(it = this->resources.begin(); it != this->resources.end(); it++){
		if(it->second.use_count() != 1){
			Logger::warning("Resource deleted with use count different than 1 (" + it->first + ").");
		}
		// else{
		// 	Logger::verbose("Resource deleted successfully (" + it->first + ").");
		// }
	}
}

Sprite* ResourceManager::get(const std::string& name_){
	std::map<std::string,Sprite::SpritePtr>::iterator it;
	it = this->resources.find(name_);

	if (it != this->resources.end()){
		return it->second.get();
	}

	return load(name_).get();
}

void ResourceManager::registerResource(const std::string& name_, Sprite::SpritePtr resource_){
	this->resources.insert( std::make_pair(name_, resource_) );
}

void ResourceManager::unregisterResource(const std::string& name_){
	std::map<std::string,Sprite::SpritePtr>::iterator it;
	it = this->resources.find(name_);

	if (it != this->resources.end()){
		this->resources.erase(it);
	}
}

Sprite::SpritePtr ResourceManager::load(const std::string& path_){
	Sprite::SpritePtr sprite = std::make_shared<Sprite>(path_);
	registerResource(path_, sprite);
	return sprite;
}

void ResourceManager::free(const std::string& name_){
	this->unregisterResource(name_);
}
