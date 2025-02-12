#include "InGameScene.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputManager.h"
#include "../Utility/StageData.h"


#include "../Objects/Mario/Player.h"
#include "../Objects/Enemy/kuribo.h"

#include "../Objects/Item/coin.h"

#include "DxLib.h"
#include <fstream>



InGameScene::InGameScene() :
	mario_coin_ui(),
	kakeru_ui(),
	coin_num_min(),
	coin_num_sec()
{
	back_ground_BGM = NULL;
}

InGameScene::~InGameScene()
{
	screen_offset.y = D_OBJECT_SIZE * 3.0f;
}

void InGameScene::Initialize()
{

	ResourceManager* rm = ResourceManager::GetInstance();
	//���C��BGM�̓ǂݍ���
	back_ground_BGM = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	StageData* Stage = StageData::GetInstance();
	Stage->Load();
	
	//�}���I�̕\��
	player = CreateObject<Player>(Vector2D(100, 403));
	//�N���{�[�̕\��
	Kuribo = CreateObject<kuribo>(Vector2D(750, 403));

	Coin = CreateObject<coin>(Vector2D(200, 403));


	//UI�̓ǂݍ���
	mario_ui = rm->GetImages("Resource/images/UI/name_mario.png")[0];
	mario_time = rm->GetImages("Resource/images/UI/time.png")[0];
	mario_world = rm->GetImages("Resource/images/UI/world.png")[0];

	mario_coin_ui = rm->GetImages("Resource/images/Item/coin.png", 4, 4, 1, 32, 32);
	kakeru_ui = rm->GetImages("Resource/images/Ui/num.png", 14, 14, 1, 16, 16);

	//�����ꖇ�̉摜������
	//�R�C���擾��
	coin_num_min = kakeru_ui;
	coin_num_sec = kakeru_ui;
}

eSceneType InGameScene::Update(const float& delta_second)
{
	StageData* Stage = StageData::GetInstance();
	Stage->Update(delta_second);

	//BGM������Ă��Ȃ��Ƃ��ɍĐ�
	if (CheckSoundMem(back_ground_BGM) != TRUE)
	{
		//���C��BGM�̍Đ�
		PlaySoundMem(back_ground_BGM, DX_PLAYTYPE_LOOP, TRUE);
	}

	//��ʉE�[�������Ă�Ƃ��ɉ�ʓ���������
	if (player->GetLocation().x >= 640 / 2 && player->GetPlayerState() == ePlayerState::MOVE)
	{
		//-45100
		Stage->SetVelocity(player->GetVelocity().x);
		if (Stage->GetVelocity().x <= -5100)
		{
			player->SetScrollEnd();
		}

		//�N���{�[�p
		Kuribo->SetVelocity(player->GetVelocity().x);
	}

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

void InGameScene::Draw() const 
{
	StageData* Stage = StageData::GetInstance();
	Stage->Load();

	

	//�^�C�g��UI�̕`��
	DrawGraph(340, 10, mario_world, TRUE);
	DrawGraph(480, 10, mario_time, TRUE);
	DrawGraph(100, 10, mario_ui, TRUE);

	//�R�C���̉摜
	DrawGraph(160, 25, mario_coin_ui[0], TRUE);  //�R�C���̉摜
	DrawGraph(190, 33, kakeru_ui[11], TRUE);     //�R�C�����́~
	DrawGraph(210, 34, coin_num_min[0], TRUE);   //�R�C��10�̈ʂ̐���
	DrawGraph(230, 34, coin_num_sec[0], TRUE);   //�R�C���P�̈ʂ̐���

	__super::Draw();

}

//�I������
void InGameScene::Finalize()
{
	//�e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType ::in_game;
}


#ifdef D_PIVOT_CENTER


//�����蔻��`�F�b�N�����i��`�̒��S�œ����蔻����Ƃ�j
void InGameScene::HitCheckObject(GameObjectBase* a, GameObjectBase* b)
{
	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabs(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		if (a->GetType() == b->GetType())
		{
			return;
		}
		else
		{
			//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
			a->OnHitCollision(b);
			b->OnHitCollision(a);
		}
	}
}

#else

//�����蔻��`�F�b�N�����i���㒸�_�̍��W���瓖���蔻��v�Z���s��)
void Scene::HitCheckObject(GameObjectBase* a, GameObjectBase* b)
{
	//�E�����_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɂ�������Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif // D_PIVOT_CNETER
