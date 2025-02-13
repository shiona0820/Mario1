#pragma once

#include "../Utility/Vector2D.h"
#include "../RectCollision.h"  // ��`�R���W�������g�p

#define D_OBJECT_SIZE (36.0f)  // �I�u�W�F�N�g�̃f�t�H���g�T�C�Y

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
    class SceneBase* owner_scene;  // ��������V�[��
    Vector2D location;             // �ʒu���W
    RectCollision collision;       // �����蔻����
    int image;                     // �摜ID
    int z_layer;                   // �`�惌�C���[
    eMobilityType mobility;        // �������
    Vector2D velocity;             // �ړ����x
    double scale;                  // �X�P�[��
    double radian;                 // ��]�p�x
    bool flip_flag;                 // �摜�̔��]�t���O

public:
    GameObjectBase();
    virtual ~GameObjectBase();

    virtual void Initialize();
    virtual void Update(float delta_second);
    virtual void Draw(const Vector2D& screen_offset) const;
    virtual void Finalize();
    virtual void OnHitCollision(GameObjectBase* hit_object);

    void SetOwnerScene(class SceneBase* scene);
    const Vector2D& GetLocation() const;
    void SetLocation(const Vector2D& location);

    RectCollision GetCollision() const;
    void SetCollisionRect(float width, float height);

    int GetZLayer() const;
    eMobilityType GetMobility() const;
};
