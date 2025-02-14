#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

enum eNokonokoState
{
	N_WALK,   //�����E�ʏ���
	N_STEP,   //���܂ꂽ���
};

class nokonoko : public GameObject
{
private:
	std::vector<int> move_animation;   //�ړ��̃A�j���[�V����

	//�A�j���[�V�����p
	const int animation_num[2] = { 0,1 };
	int animation_count;
	float animation_time;

	static nokonoko* instance;

	//����
	Vector2D direction;

	nokonoko* Kuribo;

public:

	//�N���{�[�̏��
	eNokonokoState nokonoko_state;

	nokonoko();
	~nokonoko();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/*virtual void OnHitCollision(GameObject* hit_object) ;*/

	void SetVelocity(float velo);

	static nokonoko* GetInstance();

private:

	void Movement(float delta_second);
	void AnimeCount(float delta_second);
};

