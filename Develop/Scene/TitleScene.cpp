#include "TitleScene.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

TitleScene::TitleScene()
{
	back_ground_image = NULL;
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	// �w�i�摜�̓ǂݍ���
	back_ground_image = rm->GetImages("Resource/images/title.png")[0];

	//UI�̓ǂݍ���
	mario_ui = rm->GetImages("Resource/images/UI/name_mario.png")[0];
	mario_time = rm->GetImages("Resource/images/UI/time.png")[0];
	mario_world = rm->GetImages("Resource/images/UI/world.png")[0];
	mario_coin = rm->GetImages("Resource/images/UI/uicoin.png")[0];

}

eSceneType TitleScene::Update(const float& delta_second)
{

	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	// �C���Q�[���V�[���ɑJ�ڂ���
  	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::in_game;
	}
	/*if (input->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::in_game;
	}*/

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{

	DrawExtendGraph(0, 0, 640, 480, back_ground_image,FALSE);   //�w�i�̕`��

	//�^�C�g��UI�̕`��
	DrawGraph(340, 10, mario_world,TRUE);
	DrawGraph(480, 10, mario_time,TRUE);
	DrawGraph(100, 10, mario_ui, TRUE);
	DrawGraph(150, 25, mario_coin, TRUE);
}

void TitleScene::Finalize()
{

	 //�e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}
