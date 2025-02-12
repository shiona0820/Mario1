#pragma once

#include "../Develop/Objects/GameObject.h"

class Hatena : public GameObject
{
private:
	int animation[4];
	int animation_count;
	float animation_time;

public:
	Hatena();
	~Hatena();
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject* hit_object);

private:
	void AnimationControl(float delta_second);
};

