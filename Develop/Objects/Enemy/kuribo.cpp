#include "kuribo.h"

#include "../../Utility/ResourceManager.h"
#include "../Mario/Player.h"

#include "DxLib.h"

kuribo* kuribo::instance = nullptr;

kuribo::kuribo():
	move_animation(),
	kuribo_state(eKuriboState::WALK)
{

}

kuribo::~kuribo()
{

}

void kuribo::Initialize()
{
	//�A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/images/Enemy/kuribo.png", 3, 3, 1, 32, 32);

	image = move_animation[0];

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("�N���{�[�̉摜������܂���\n");
	}

	velocity.x = -0.1;

	//�����蔻���ݒ�
	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);

	//�I�u�W�F�N�g�^�C�v��ݒ�
	collision.SetObjectType(eObjectType::eEnemy);

	//������I�u�W�F�N�g�^�C�v��ݒ�
	collision.SetHitObjectType({ eObjectType::ePlayer, eObjectType::eGround });

	//�����蔻��̕`��t���O
	SetDrawCollisionBox(false);

}


void kuribo::Update(float delta_second)
{
	velocity.x = -0.1;
	location += velocity;

	//�����蔻��̈ʒu���擾����
	Vector2D collisionPosition = collision.GetPosition();
	//�����蔻��̈ʒu���X�V����
	collision.SetPosition(location);

	switch (kuribo_state)
	{
	case WALK:
		// �A�j���[�V��������
		AnimeCount(delta_second);
		break;
	case STEP:
		
		break;
	default:
		break;
	}

}

void kuribo::Draw(const Vector2D& screen_offset) const 
{
	__super::Draw(screen_offset);
}

void kuribo::Finalize()
{

}

void kuribo::OnHitCollision(GameObject* hit_object)
{

	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		//kuribo�����ł���
		owner_scene->DestroyObject(this);
	}
}


void kuribo::AnimeCount(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		// �摜�̐ݒ�
		image = move_animation[animation_num[animation_count]];
	}
}

void kuribo::Movement(float delta_second)
{

}

kuribo* kuribo::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new kuribo();
	}
	return instance;
}

void kuribo::SetVelocity(float velo)
{
	location.x -= velo;
}