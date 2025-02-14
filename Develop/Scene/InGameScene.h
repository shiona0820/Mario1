#pragma once
#define D_PIVOT_CENTER

#include "SceneBase.h"

class InGameScene : public SceneBase
{
private:
	class Player* player;		// �v���C���[���
	class kuribo* Kuribo;      //�N���{�[�̏��

	class coin* Coin;          //�R�C���̏��
	std::vector<int> coin_animation;   //������̃A�j���[�V����
	//�A�j���[�V�����p
	const int animation_num[4] = { 1,2,3,4 };
	int animation_count;
	float animation_time;

	std::vector<kuribo> enemies;      //�����`��p


	int back_ground_BGM;		// BGM
	
	float velocity;

	//�^�C�g�����UI�̐ݒ�
	int mario_ui;
	int mario_world;
	int mario_time;

	int fream_time;   //�t���[���̎��Ԑݒ�

	std::vector<int> kakeru_ui;       //�R�C�����́~�̉摜
	std::vector<int>coin_num_min;         //�R�C���擾���̉摜�\�̈�
	std::vector<int>coin_num_sec;         //�R�C���擾���̉摜��̈�

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;

private:
	void AnimeCount(float delta_secound);


//private:
//
//	//�����蔻��`�F�b�N����
//	void HitCheckObject(GameObjectBase* a, GameObjectBase* b);
//
//	//�I�u�W�F�N�g��������
//	template <class T>
//	T* CreateObject(const Vector2D& location)
//	{
//		//�w�肵���N���X�𐶐�����
//		T* new_instance = new T();
//		//GameObject�N���X���p�����Ă��邩�m�F
//		GameObjectBase* new_object = dynamic_cast<GameObjectBase*>(new_instance);
//
//		//�G���[�`�F�b�N
//		if (new_object == nullptr)
//		{
//			delete new_instance;
//			throw ("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
//		}
//
//		//����������
//		new_object->Initialize();
//		//�ʒu���̐ݒ�
//		new_object->SetLocation(location);
//
//		////�I�u�W�F�N�g���X�g�ɒǉ�
//		//objects.push_back(new_object);
//
//		//�C���X�^���X�̃|�C���^��ԋp
//		return new_instance;
//	}

};

