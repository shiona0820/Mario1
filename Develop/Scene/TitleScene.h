#pragma once

#include "SceneBase.h"

// �^�C�g���V�[��
class TitleScene : public SceneBase
{
private:

	int back_ground_image;   //�w�i�摜

	//�^�C�g�����UI�̐ݒ�
	int mario_ui;
	int mario_world;
	int mario_time;
	std::vector<int> mario_coin_ui;   //�R�C���摜
	std::vector<int> kakeru_ui;       //�R�C�����́~�̉摜
	std::vector<int>coin_num_min;         //�R�C���擾���̉摜�\�̈�
	std::vector<int>coin_num_sec;         //�R�C���擾���̉摜��̈�

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;

	
};

