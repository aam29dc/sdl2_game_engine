#include "itemobject.hpp"

ItemObject::ItemObject() {
	_item = nullptr;
}

ItemObject::ItemObject(Item& item) {
	_item = &item;
}