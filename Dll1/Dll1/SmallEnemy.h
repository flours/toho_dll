#pragma once

#include "AbstractEnemy.h"

class Player;


class SmallEnemy final : public AbstractEnemy
{
public:
	SmallEnemy(float x, float y,std::shared_ptr<Player> player);
	~SmallEnemy() = default;
	void draw() const override;

protected:
	void setSize() override;
};