#include "RectCollision.h"
#include <algorithm>  // std::max, std::min

/// <summary>
/// �����蔻��Ώۂ��m�F���鏈��
/// </summary>
/// <param name="hit_object">����̃I�u�W�F�N�g�^�C�v</param>
/// <returns>�K�p����I�u�W�F�N�g�Ȃ� true</returns>
bool RectCollision::IsCheckHitTarget(eObjectType hit_object) const
{
    for (eObjectType type : hit_object_type)
    {
        if (type == hit_object)
        {
            return true;
        }
    }
    return false;
}

/// <summary>
/// ��`���m�̓����蔻��m�F����
/// </summary>
/// <param name="rect1">��`1</param>
/// <param name="rect2">��`2</param>
/// <returns>�������Ă���Ȃ� true</returns>
bool IsCheckCollision(const RectCollision& rect1, const RectCollision& rect2)
{
    // �������@�ɂ�锻��iAxis-Aligned Bounding Box ����j
    return !(rect1.bottom_right.x <= rect2.top_left.x || // rect1 �� rect2 �̍����ɂ���
        rect1.top_left.x >= rect2.bottom_right.x ||  // rect1 �� rect2 �̉E���ɂ���
        rect1.bottom_right.y <= rect2.top_left.y ||  // rect1 �� rect2 �̏㑤�ɂ���
        rect1.top_left.y >= rect2.bottom_right.y);   // rect1 �� rect2 �̉����ɂ���
}
