#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

class Dokan : public GameObject
{
public:
	Dokan();
	~Dokan();

	virtual void Initialize() override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject* hit_object) ;
};

