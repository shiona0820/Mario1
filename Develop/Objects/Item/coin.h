#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

class coin : public GameObject
{
private:
	std::vector<GameObject*>objects;

	std::vector<int> coin_animation;   //������̃A�j���[�V����

	//�A�j���[�V�����p
	const int animation_num[2] = { 0,1 };
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

	/*virtual void OnHitCollision(GameObject* hit_object) ;*/

	void SetVelocity(float velo);

	static coin* GetInstance();

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

private:

	void Movement(float delta_second);
	void AnimeCount(float delta_second);

	//�I�u�W�F�N�g��������
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

		//����������
		new_object->Initialize();
		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};

