#ifndef INCLUDE_QUADTREE_H
#define INCLUDE_QUADTREE_H

#include "SDLWrapper.h"
#include <vector>

class QuadTree {

	public:
		QuadTree(int level_, SDL_Rect bounds_);
		~QuadTree();

		/**
		* Clears the QuadTree.
		*/
		void clear();

		/**
		* Splits the node into four subnodes.
		*/
		void split();

		/**
		* Determine which node the object belongs to.
		* -1 means object cannot completely fit within a child node and is part of the parent node.
		*/
		int getIndex(SDL_Rect rect_);

		/**
		* Insert the object into the quadtree.
		* If the node exceeds the capacity, it will split and add all objects to their corresponding nodes.
		*/
		void insert(SDL_Rect rect_);

		/**
		* Return all objects that could collide with the given object.
		*/
		std::vector<SDL_Rect> retrieve(std::vector<SDL_Rect>& returnObjects_, SDL_Rect rect_);

		void setObjects(std::vector<SDL_Rect>& objects_);

	private:
		const int maxObjects;
		const int maxLevels;

		int level;
		std::vector <SDL_Rect> objects;
		SDL_Rect bounds;
		QuadTree* nodes[4];

};

#endif //INCLUDE_QUADTREE_H
