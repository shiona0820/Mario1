#include "RectCollision.h"
#include <algorithm>

// �R���X�g���N�^
RectCollision::RectCollision()
    : is_blocking(false),
    object_type(eObjectType::none),
    top_left(0.0f, 0.0f),
    bottom_right(0.0f, 0.0f) {
}

RectCollision::~RectCollision() = default;

// �����蔻��Ώۂ̃I�u�W�F�N�g�^�C�v���m�F
bool RectCollision::IsCheckHitTarget(eObjectType hit_object) const
{
    for (eObjectType type : hit_object_type)
    {
        if (type == hit_object)
        {
            return true;  // ��v����ꍇ�A����Ώ�
        }
    }
    return false;  // ��v���Ȃ��ꍇ�A����Ώۂł͂Ȃ�
}

// ��`�̕����v�Z����
float RectCollision::GetWidth() const
{
    return bottom_right.x - top_left.x;
}

// ��`�̍������v�Z����
float RectCollision::GetHeight() const
{
    return bottom_right.y - top_left.y;
}

// ��`�̈ʒu��ݒ肷��
void RectCollision::SetPosition(const Vector2D& position, float width, float height)
{
    top_left = position;  // ����̍��W
    bottom_right = Vector2D(position.x + width, position.y + height);  // ���ƍ�������E�����W���v�Z
}

// ��`���m�̓����蔻�菈��
bool IsCheckCollision(const RectCollision& rect1, const RectCollision& rect2)
{
    // ��`���d�Ȃ��Ă��邩���m�F�������
    return !(rect1.bottom_right.x < rect2.top_left.x ||   // rect1��rect2�̍���
        rect1.top_left.x > rect2.bottom_right.x ||   // rect1��rect2�̉E��
        rect1.bottom_right.y < rect2.top_left.y ||   // rect1��rect2�̏㑤
        rect1.top_left.y > rect2.bottom_right.y);    // rect1��rect2�̉���
}
