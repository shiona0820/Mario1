#pragma once

#include "../Utility/Vector2D.h"
#include "../RectCollision.h"  // RectCollision���g��

#define D_OBJECT_SIZE (24.0f)  // �I�u�W�F�N�g�̃f�t�H���g�T�C�Y

// �����̎��
enum eMobilityType
{
    Stationary,  // �Œ�I�u�W�F�N�g
    Movable,     // ���I�u�W�F�N�g
};

// �Q�[���I�u�W�F�N�g���N���X
class GameObjectBase
{
protected:
    class SceneBase* owner_scene;  // ���L����V�[�����
    Vector2D location;             // �ʒu���W
    Vector2D box_size;             // �������蔻��pbox
    RectCollision collision;       // �����蔻����
    int image;                     // �摜���
    int z_layer;                   // ���C���[���
    eMobilityType mobility;        // �������
    Vector2D velocity;             // �ړ����x
    double scale;                  // �傫��
    double radian;                 // ��]�p�x
    bool flip_flag;                // �摜���]�t���O

public:
    GameObjectBase();
    virtual ~GameObjectBase();

    // ����������
    virtual void Initialize();

    // �X�V�����i���ԍ������󂯎��j
    virtual void Update(float delta_second);

    // �`�揈���i�X�N���[���I�t�Z�b�g�Ɋ�Â��ĕ`��j
    virtual void Draw(const Vector2D& screen_offset) const;

    // �I��������
    virtual void Finalize();

    // �����蔻��ʒm����
    virtual void OnHitCollision(GameObjectBase* hit_object);

    // ���L�V�[�����̐ݒ�
    void SetOwnerScene(class SceneBase* scene);

    // �ʒu���W�擾
    const Vector2D& GetLocation() const;

    // �ʒu���W�ύX
    void SetLocation(const Vector2D& location);

    // �����蔻����̎擾
    RectCollision GetCollision() const;

    // ��`�����蔻����̐ݒ�
    void SetCollisionRect(float width, float height);

    // Z���C���[���擾
    const int GetZLayer() const;

    // �������̎擾
    const eMobilityType GetMobility() const;
};
