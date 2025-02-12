#include "TitleScene.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

TitleScene::TitleScene() :
	mario_coin_ui(),
	kakeru_ui(),
	coin_num_min(),
	coin_num_sec()
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
	mario_coin_ui = rm->GetImages("Resource/images/Item/coin.png",4,4,1,32,32);
	kakeru_ui = rm->GetImages("Resource/images/Ui/num.png", 14, 14, 1, 16, 16);

	//�����ꖇ�̉摜������
	//�R�C���擾��
	coin_num_min = kakeru_ui;
	coin_num_sec = kakeru_ui;
}

eSceneType TitleScene::Update(const float& delta_second)
{

	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	// �C���Q�[���V�[���ɑJ�ڂ���
	// �V�[���J�ڗp�̃L�[���ꎞ�I�ɕύX(�ύX�O�F�X�y�[�X�L�[ �ύX��:�G���^�[�L�[)
  	if (input->GetKeyDown(KEY_INPUT_RETURN))
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
	DrawGraph(50, 10, mario_ui, TRUE);
	//�R�C���̉摜
	DrawGraph(160, 25, mario_coin_ui[0], TRUE);  //�R�C���̉摜
	DrawGraph(190, 33, kakeru_ui[11], TRUE);     //�R�C�����́~
	DrawGraph(210, 34, coin_num_min[0], TRUE);   //�R�C��10�̈ʂ̐���
	DrawGraph(230, 34, coin_num_sec[0], TRUE);   //�R�C���P�̈ʂ̐���
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
