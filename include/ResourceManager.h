#ifndef INCLUDE_RESOURCEMANAGER_H
#define INCLUDE_RESOURCEMANAGER_H

#include <map>
#include <memory>
#include <string>

#include "Sprite.h"

typedef std::shared_ptr<Sprite> SpritePtr;

class ResourceManager {

	public:
		ResourceManager();
		~ResourceManager();

		SpritePtr load(const std::string& path_);
		void free(const std::string& name_);
		SpritePtr get(const std::string& name_);

	private:
		void registerResource(const std::string& name_, SpritePtr resource_);
		void unregisterResource(const std::string& name_);

		std::map <std::string, SpritePtr> resources;

};



#endif // INCLUDE_RESOURCEMANAGER_H
