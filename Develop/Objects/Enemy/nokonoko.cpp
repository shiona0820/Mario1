#include "nokonoko.h"

#include "../../Utility/ResourceManager.h"

#include "DxLib.h"

nokonoko* nokonoko::instance = nullptr;

nokonoko::nokonoko() :
	move_animation(),
	nokonoko_state(eNokonokoState::N_WALK)
{

}

nokonoko::~nokonoko()
{

}

void nokonoko::Initialize()
{
    //�A�j���[�V�����摜�̓ǂݍ���
    ResourceManager* rm = ResourceManager::GetInstance();
    move_animation = rm->GetImages("Resource/images/Enemy/nokonoko.png", 2, 2, 1, 32, 64);

    image = move_animation[0];

    //�G���[�`�F�b�N
    if (image == -1)
    {
        throw("nokonoko�̉摜������܂���\n");
    }

    velocity.x = -0.1;
}


void nokonoko::Update(float delta_second)
{
	velocity.x = -0.1;
    location += velocity;

	switch (nokonoko_state)
	{
	case N_WALK:
		// �A�j���[�V��������
		AnimeCount(delta_second);
		break;
	case N_STEP:
		break;
	default:
		break;
	}
}

void nokonoko::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void nokonoko::Finalize()
{

}

void nokonoko::AnimeCount(float delta_second)
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

void nokonoko::Movement(float delta_second)
{

}

nokonoko* nokonoko::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new nokonoko();
	}
	return instance;
}

void nokonoko::SetVelocity(float velo)
{
	location.x -= velo;
}