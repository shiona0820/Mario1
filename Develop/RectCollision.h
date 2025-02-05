#pragma once

#include "../Develop/Utility/Vector2D.h"
#include <vector>

// �I�u�W�F�N�g�^�C�v�̒�`
enum class eObjectType : unsigned char
{
    none,
    player,
    enemy,
    wall,
    item,
};

// ��`�R���W�����\����
class RectCollision
{
public:
    bool is_blocking;                             // ���蔲������t���O
    eObjectType object_type;                      // ���g�̃I�u�W�F�N�g�^�C�v
    std::vector<eObjectType> hit_object_type;     // �K�p����I�u�W�F�N�g�^�C�v
    Vector2D top_left;                            // ��`�̍���̍��W
    Vector2D bottom_right;                        // ��`�̉E���̍��W

    RectCollision() :
        is_blocking(false),
        object_type(eObjectType::none),
        top_left(0.0f, 0.0f),
        bottom_right(0.0f, 0.0f) {
    }

    ~RectCollision() = default;

    // �����蔻��Ώۊm�F����
    bool IsCheckHitTarget(eObjectType hit_object) const;

    // ��`�̕��ƍ������擾
    float GetWidth() const { return bottom_right.x - top_left.x; }
    float GetHeight() const { return bottom_right.y - top_left.y; }

    // ��`�̈ʒu���X�V����
    void SetPosition(const Vector2D& position, float width, float height)
    {
        top_left = position;
        bottom_right = Vector2D(position.x + width, position.y + height);
    }
};

// ��`���m�̓����蔻��m�F�֐�
bool IsCheckCollision(const RectCollision& rect1, const RectCollision& rect2);
