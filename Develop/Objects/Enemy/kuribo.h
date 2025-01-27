#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

enum eKuriboState
{
	WALK,   //歩く・通常状態
	STEP,   //踏まれた状態
};

class kuribo : public GameObject
{
private:
	std::vector<int> move_animation;   //移動のアニメーション


	//アニメーション用
	const int animation_num[2] = {0,1};
	int animation_count;
	float animation_time;

	static kuribo* instance;

	//向き
	Vector2D direction;

	kuribo* Kuribo;

public:

	//クリボーの状態
	eKuriboState kuribo_state;

	kuribo();
	~kuribo();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/*virtual void OnHitCollision(GameObject* hit_object) ;*/

	void SetVelocity(float velo);

	static kuribo* GetInstance();

private:

	void Movement(float delta_second);
	void AnimeCount(float delta_second);
};

