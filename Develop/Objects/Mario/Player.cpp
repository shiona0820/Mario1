#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

#define D_PLAYER_SPEED	(50.0f)
#define D_GRAVITY (9.807f)   // �d�͉����x


Player* Player::instance = nullptr;

Player::Player() :
	move_animation(),
	jump_animation(),
	dying_animation(),
	velocity(0.0f),
	player_state(ePlayerState::IDLE),
	now_direction_state(eDirectionState::LEFT),
	next_direction_state(eDirectionState::LEFT),
	food_count(0),
	animation_time(0.0f),
	//old_panel(ePanelID::NONE),
	is_power_up(false),
	is_destroy(false),
	player(nullptr),
	scroll_end(false),
	jump_location(Vector2D(0.0f)),
	jump_velocity(Vector2D(0.0f)),
	is_on_ground(true),
	ground_y(0.0f)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	
	ResourceManager* rm = ResourceManager::GetInstance();
	// �A�j���[�V�����摜�̓ǂݍ���
	move_animation = rm->GetImages("Resource/images/Mario/mario.png", 9, 9, 1, 32, 32);
	jump_animation = rm->GetImages("Resource/images/Mario/mario.png", 9, 9, 1, 32, 32);
	//�W�����v��SE
	jump_SE = rm->GetSounds("Resource/Sounds/SE_SuperJump.wav");
	

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::player;
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::food);
	collision.hit_object_type.push_back(eObjectType::power_food);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;
	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

	image = move_animation[0];
	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("�}���I�̉摜������܂���\n");
	}

	ground_y = 500.0f;    // �n�ʂ�Y���W

	////�W�����v�͂̏�����
	//this->player->jump_velocity.y -= 15.0f;
	//jump_location = 0.0f;

}

void Player::Update(float delta_second)
{	
	//�d�͑��x�̌v�Z
	if (!is_on_ground) {
    velocity.y += D_GRAVITY * delta_second;
    }

	if (location.y + velocity.y * delta_second >= ground_y) // �n�ʈʒu�ɒB�����ꍇ
	{
		location.y = ground_y;
		velocity.y = 0.0f;
		g_velocity = 0.0f;
		is_on_ground = true;
		player_state = ePlayerState::IDLE;
	}

	InputManager* Input = InputManager::GetInstance();

	

	// �v���C���[��Ԃɂ���āA�����ς���
	switch (player_state)
	{

	case ePlayerState::IDLE:
		// �摜�̐ݒ�
		image = move_animation[0];
		velocity.x = 0;
		if (Input->GetKey(KEY_INPUT_A) || Input->GetKey(KEY_INPUT_D))
		{
			player_state = ePlayerState::MOVE;
			
		}
		else if(Input->GetKey(KEY_INPUT_SPACE))
		{
			player_state = ePlayerState::Jump;
		}
		break;
	case ePlayerState::MOVE:
		// �ړ�����
		Movement(delta_second);
		// �A�j���[�V��������
		WalkAnimationControl(delta_second);
		break;
	case ePlayerState::DIE:
		// ���S���̃A�j���[�V����
		animation_time += delta_second;
		if (animation_time >= 0.07f)
		{
			animation_time = 0.0f;
			animation_count++;
			// ����������
			if (animation_count >= dying_animation.size())
			{
				player_state = ePlayerState::IDLE;
				animation_count = 0;
				is_destroy = true;
			}
		}
		image = dying_animation[animation_count];
		break;

		case ePlayerState::Damage:
			//�_���[�W���󂯂����̃A�j���[�V����
			animation_time += delta_second;

		case ePlayerState::Jump:
			JumpMoment(delta_second);
			JumpAnimationControl(delta_second);
			// �ړ�����
			Movement(delta_second);

			break;

	default:
		break;
	}
	location += velocity;
}

void Player::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Player::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	dying_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Player::OnHitCollision(GameObjectBase* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Player����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;
	}

	// ���������A�I�u�W�F�N�g���ʏ�a��������
	if (hit_object->GetCollision().object_type == eObjectType::food)
	{
		food_count++;

	}

	// ���������A�I�u�W�F�N�g���p���[�a��������
	if (hit_object->GetCollision().object_type == eObjectType::power_food)
	{
		food_count++;
		is_power_up = true;
	}

	// ���������I�u�W�F�N�g���G��������
	if (hit_object->GetCollision().object_type == eObjectType::enemy)
	{
		player_state = ePlayerState::DIE;
	}

}

/// <summary>
/// �v���C���[�̏�Ԃ��擾����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
ePlayerState Player::GetPlayerState() const
{
	return player_state;
}

/// <summary>
/// �v���C���[���p���[�A�b�v���Ă邩�m�F����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
bool Player::GetPowerUp() const
{
	return is_power_up;
}

/// <summary>
/// �p���[�_�E��������
/// </summary>
void Player::SetPowerDown()
{
	is_power_up = false;
}

bool Player::GetDestroy() const
{
	return is_destroy;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::Movement(float delta_second)
{

	InputManager* Input = InputManager::GetInstance();

	//A�{�^�����������獶�ɐi��
	if (Input->GetKey(KEY_INPUT_A))
	{
		velocity.x = -0.8f;
		flip_flag = true;

		//SPACE����������W�����v��������
		//SE�炷
		if (Input->GetKey(KEY_INPUT_SPACE) && is_on_ground)
		{
			velocity.y = -5.0f;
			JumpAnimationControl(delta_second);
			player_state = ePlayerState::Jump;
			is_on_ground = false;
			PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
		}

		player_state = ePlayerState::MOVE;
	}

	//D�{�^������������E�ɐi��
	else if (Input->GetKey(KEY_INPUT_D))
	{
		velocity.x = 0.8f;
		flip_flag = false;

		//SPACE����������W�����v��������
		//SE�炷
		if (Input->GetKey(KEY_INPUT_SPACE) && is_on_ground)
		{
			velocity.y = -5.0f;
			JumpAnimationControl(delta_second);
			player_state = ePlayerState::Jump;
			is_on_ground = false;
			PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
		}

		player_state = ePlayerState::MOVE;
	}

	else
	{
		velocity.x = 0;
		player_state = ePlayerState::IDLE;
	}

	//��ʊO�ɍs���Ȃ��悤�ɂ��鏈��
	if (location.x < 16.0f)
	{
		location.x = 16.0f;
	}

	//��ʒ�������ɐi�܂Ȃ�
	if (scroll_end == false)
	{
		if (location.x >= 640.0f / 2)
		{
			location.x = 640.0f / 2;
		}
	}
	else
	{
		//��ʊO�ɍs���Ȃ��悤�ɂ��鏈��
		if (location.x > 600.0f)
		{
			location.x = 600.0f;
		}
	}

	/**�쐬�i�K�̉�ʊO����(y��)if (location.y >= 500.0f && is_on_ground == true)
	{
		location.y = 500.0f;
		velocity.y = 0.0f;
		g_velocity = 0.0f;
	}*/
}

/// <summary>
/// �W�����v����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::JumpMoment(float delta_second)
{
	InputManager* Input = InputManager::GetInstance();

		if (Input->GetKey(KEY_INPUT_SPACE) && is_on_ground == true)
		{
			velocity.y = -4.0f;
			JumpAnimationControl(delta_second);
			player_state = ePlayerState::Jump;
			is_on_ground = false;
			PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
		}
}

/// <summary>
/// ���E�ړ��A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::WalkAnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// �摜�̐ݒ�
			image = move_animation[animation_num[animation_count]];
	}


}

/// <summary>
/// �W�����v����A�j���[�V��������
/// </summary>
// <param name="delta_second">1�t���[��������̎���</param>
void Player::JumpAnimationControl(float delta_second)
{
	// �W�����v���̃A�j���[�V����
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
		image = jump_animation[jump_animation_num[animation_count]];
	}

	PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
}

Player* Player::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Player();
	}
	return instance;
}

const Vector2D& Player::GetVelocity() const
{
	return velocity;
}

void Player::SetScrollEnd()
{
	scroll_end = true;
}

ePlayerState Player::PlayerState()
{
	return player_state;
}