#pragma once


/*����
* �����n���^�[�Ɖߋ��̎����̍쐬�����}���I�̃v���W�F�N�g�̌�����������
* �����n���^�[�Ŕ͈͂��w�ԁA�ߋ��̎����̍쐬�����}���I�̃v���W�F�N�g�Ńv���C���[�̓������l����
* ���ꂼ��̃N���X�ɓ����蔻�肪�ݒ肳��Ă��Ȃ��̂́A�����炭�T�C�Y���Ȃ����炩������Ȃ��B�T�C�Y�̂��Ƃ͒��ׂ�B
*/
#include "GameObjectBase.h"
#include "../Scene/SceneBase.h"
#include "../Utility/Vector2D.h"

// �Q�[���I�u�W�F�N�g�N���X
class GameObject : public GameObjectBase
{
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    /// <summary>
    /// �Q�[���I�u�W�F�N�g��������
    /// </summary>
    /// <typeparam name="OBJECT">��������Q�[���I�u�W�F�N�g�N���X</typeparam>
    /// <param name="generate_location">�����ʒu</param>
    /// <returns>���������Q�[���I�u�W�F�N�g�̃|�C���^</returns>
    template <class OBJECT>
    OBJECT* CreateObject(const Vector2D& generate_location)
    {
        if (owner_scene)
        {
            return owner_scene->CreateObject<OBJECT>(generate_location);
        }
        return nullptr;
    }

    /// <summary>
    /// �I�u�W�F�N�g�j������
    /// </summary>
    /// <param name="target">�j�����s���Q�[���I�u�W�F�N�g�̃|�C���^</param>
    void DestroyObject(GameObjectBase* target)
    {
        if (owner_scene)
        {
            owner_scene->DestroyObject(target);
        }
    }

    /// <summary>
    /// �X�N���[���I�t�Z�b�g���擾����
    /// </summary>
    /// <returns>�X�N���[���I�t�Z�b�g�l</returns>
    const Vector2D GetScreenOffset() const
    {
        if (owner_scene)
        {
            return owner_scene->GetScreenOffset();
        }
        return Vector2D(0.0f, 0.0f);
    }
};
