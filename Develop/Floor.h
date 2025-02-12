#pragma once

#include "../Develop/Objects/GameObject.h"

class Floor : public GameObject
{
public:
	Floor();
	~Floor();
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject* hit_object);
};