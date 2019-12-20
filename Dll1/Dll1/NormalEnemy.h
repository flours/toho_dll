#pragma once
#include "AbstractEnemy.h"

class Player;


class NormalEnemy final : public AbstractEnemy
{
public:
	NormalEnemy(float x, float y,std::shared_ptr<Player> player);
	~NormalEnemy() = default;
	void draw() const override;

protected:
	void setSize() override;

};