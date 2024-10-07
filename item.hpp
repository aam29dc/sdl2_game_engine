#pragma once
#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>

/*	Each item gets an ID, that uniquely identifies it, and this ID helps id the texture, etc
	For textures we could use a large texture map that contains all our items */

class Item {
public:
	Item(const unsigned int id = 0, const unsigned int maxStack = 0, const std::string type = "null", const int effect = 0, const int cooldown = 0);
	virtual ~Item();

	const unsigned int& getID() const;
	size_t& getTextureID();

	const unsigned int& getAmount() const;
	const unsigned int& getMaxStack() const;
	const int& getEffect() const;
	const std::string& getType() const;
	const unsigned int& getCooldown() const;
	const std::string& getName() const;

	void setAmount(const unsigned int& amount);
protected:
	unsigned int _ID;	//item ID
	size_t _textureID;

	unsigned int _amount;
	unsigned int _maxStack;
	int _effect;
	std::string _type;
	unsigned int _cooldown;
	std::string _name;
};

#endif