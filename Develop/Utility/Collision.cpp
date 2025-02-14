#include "Collision.h"
#include <math.h>

Collision::Collision() :
	is_blocking(false),
	object_type(eObjectType::none),
	hit_object_type(),
	position(0)
{
}

Collision::~Collision()
{

}

//�����蔻��̈ʒu��ݒu����
void Collision::SetPosition(const Vector2D& pos)
{
	position = pos;
}

//�����蔻��̈ʒu���擾����
const Vector2D& Collision::GetPosition() const
{
	return position;
}

//�����蔻��̑傫���ݒu����
void Collision::SetSize(const float& width, const float& height)
{
	box_size.x = width;
	box_size.y = height;
}

// �����蔻��̑傫���ݒu����
Vector2D Collision::GetSize()
{
	return box_size;
}

//�I�u�W�F�N�g�^�C�v��ݒu
void Collision::SetObjectType(const eObjectType& FUNC_objecttype)
{
	object_type = FUNC_objecttype;
}

//������I�u�W�F�N�g�^�C�v�̐ݒ�
void Collision::SetHitObjectType(const std::vector<eObjectType>& FUNC_hitobjecttype)
{
	hit_object_type = FUNC_hitobjecttype;
}

//���������I�u�W�F�N�g�̃^�C�v�m�F����
bool Collision::IsCheckHitTarget(eObjectType FUNC_hitobject) const
{
	//�K�p����I�u�W�F�N�g�^�C�v�����[�v����
	for (eObjectType type : hit_object_type)
	{
		//�K������^�C�v�Ȃ�TRUE
		if (type == FUNC_hitobject)
		{
			return true;
		}
	}

	return false;
}

//�����蔻�蓯�m���������Ă��邩�m�F
bool Collision::CheckCollision(const Collision& other) const
{
	//�I�u�W�F�N�g�̓����蔻��̈ʒu�̕ϐ��錾
	Vector2D A_min = position - (box_size / 2) + pivot;
	Vector2D A_max = position + (box_size / 2) + pivot;

	//���������I�u�W�F�N�g�̓����蔻��̈ʒu�̕ϐ��錾
	Vector2D B_min = other.position - (other.box_size / 2) + other.pivot;
	Vector2D B_max = other.position + (other.box_size / 2) + other.pivot;

	//�����I�u�W�F�N�g���m���������Ă���� true ��Ԃ�
	if (A_min.x < B_max.x &&
		A_max.x > B_min.x &&
		A_min.y < B_max.y &&
		A_max.y > B_min.y)
	{
		return true;
	}

	return false;
}