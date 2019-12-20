#pragma once

#include "AbstractEnemy.h"

class Player;

class BigEnemy final : public AbstractEnemy
{
public:
	BigEnemy(float x, float y, std::shared_ptr<Player> player);
	~BigEnemy() = default;
	void draw() const override;

protected:
	void setSize() override;

};