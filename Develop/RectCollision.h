#pragma once

#include "../Develop/Utility/Vector2D.h"
#include <vector>
#include <algorithm>  // for std::max, std::min

// �I�u�W�F�N�g�^�C�v�̒�`
enum class eObjectType : unsigned char
{
    none,
    player,
    enemy,
    block,
    item,
    flag,
    dokan,
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

    RectCollision();
    ~RectCollision();

    // �����蔻��Ώۊm�F����
    bool IsCheckHitTarget(eObjectType hit_object) const;

    // ��`�̕��ƍ������擾
    float GetWidth() const;
    float GetHeight() const;

    // ��`�̈ʒu���X�V����
    void SetPosition(const Vector2D& position, float width, float height);
};

// ��`���m�̓����蔻��m�F�֐�
bool IsCheckCollision(const RectCollision& rect1, const RectCollision& rect2);
