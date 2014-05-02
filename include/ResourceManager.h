#ifndef INCLUDE_RESOURCEMANAGER_H
#define INCLUDE_RESOURCEMANAGER_H

#include <map>

#include <string>

#include "Sprite.h"


class ResourceManager {

	public:
		ResourceManager();
		~ResourceManager();
		
		Sprite::SpritePtr get(const std::string& name_);

	private:
		Sprite::SpritePtr load(const std::string& path_);
		void free(const std::string& name_);
		void registerResource(const std::string& name_, Sprite::SpritePtr resource_);
		void unregisterResource(const std::string& name_);

		std::map <std::string, Sprite::SpritePtr> resources;

};



#endif // INCLUDE_RESOURCEMANAGER_H
