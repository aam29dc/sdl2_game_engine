#include "item.hpp"

Item::Item(const unsigned int id, const unsigned int maxStack, const std::string type, const int effect, const int cooldown) {
	_ID = id;
	_textureID = 0;
	_maxStack = maxStack;
	_effect = effect;
	_cooldown = cooldown;
	_type = type;
	_amount = 1;
}

Item::~Item() {

}

void Item::setAmount(const unsigned int& amount) {
	_amount = amount;
}

const unsigned int& Item::getID() const {
	return _ID;
}

const std::string& Item::getName() const {
	return _name;
}

size_t& Item::getTextureID() {
	return _textureID;
}

const unsigned int& Item::getAmount() const {
	return _amount;
}

const unsigned int& Item::getMaxStack() const {
	return _maxStack;
}

const int& Item::getEffect() const {
	return _effect;
}

const std::string& Item::getType() const {
	return _type;
}

const unsigned int& Item::getCooldown() const {
	return _cooldown;
}

void spawn(const float x, const float y) {

}