#pragma once
#ifndef ITEMOBJECT_HPP
#define ITEMOBJECT_HPP

#include "sdlgameobject.hpp"
#include "item.hpp"

class ItemObject : public SDLGameObject {
public:
	ItemObject();
	ItemObject(Item& item);
protected:
	Item* _item;
};

#endif