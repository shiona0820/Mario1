#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

class coin : public GameObject
{
private:
	std::vector<GameObject*>objects;

	std::vector<int> coin_animation;   //������̃A�j���[�V����

	//�A�j���[�V�����p
	const int animation_num[4] = {1,2,3,4};
	int animation_count;
	float animation_time;

	int coin_sound;

	static coin* instance;
	coin* Coin;

public:

	coin();
	~coin();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	void SetVelocity(float velo);

	static coin* GetInstance();

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

private:

	void Movement(float delta_second);
	void AnimeCount(float delta_second);
};

