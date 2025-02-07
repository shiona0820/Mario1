#include "GameObjectBase.h"
#include "../Scene/SceneBase.h"
#include "DxLib.h"

GameObjectBase::GameObjectBase() :
    owner_scene(nullptr),
    location(0.0f),
    image(NULL),
    z_layer(0),
    mobility(eMobilityType::Stationary),
    velocity(0.0f),
    scale(1.0),
    radian(0.0),
    flip_flag(false)
{
    // �f�t�H���g�̃R���W�����T�C�Y��ݒ�
    collision.SetPosition(location, D_OBJECT_SIZE, D_OBJECT_SIZE);
}

GameObjectBase::~GameObjectBase()
{
}

/// ����������
void GameObjectBase::Initialize()
{
}

/// �X�V����
void GameObjectBase::Update(float delta_second)
{
    // �ʒu�X�V (���x���l��)
    location += velocity * delta_second;
    collision.SetPosition(location, collision.GetWidth(), collision.GetHeight());
}

/// �`�揈��
void GameObjectBase::Draw(const Vector2D& screen_offset) const
{
    Vector2D graph_location = location + screen_offset;
    DrawRotaGraphF(graph_location.x, graph_location.y, scale, radian, image, TRUE, flip_flag);
}

/// �I��������
void GameObjectBase::Finalize()
{
}

/// �����蔻��ʒm����
void GameObjectBase::OnHitCollision(GameObjectBase* hit_object)
{
    // �Փˎ��̏����i�h���N���X�ŃI�[�o�[���C�h�j
}

/// ���L�V�[�����̐ݒ�
void GameObjectBase::SetOwnerScene(SceneBase* scene)
{
    owner_scene = scene;
}

/// �ʒu���W�擾����
const Vector2D& GameObjectBase::GetLocation() const
{
    return location;
}

/// �ʒu���ύX����
void GameObjectBase::SetLocation(const Vector2D& new_location)
{
    location = new_location;
    collision.SetPosition(location, collision.GetWidth(), collision.GetHeight());
}

/// �����蔻��擾����
RectCollision GameObjectBase::GetCollision() const
{
    return collision;
}

/// ��`�����蔻����̐ݒ�
void GameObjectBase::SetCollisionRect(float width, float height)
{
    collision.SetPosition(location, width, height);
}

/// Z���C���[���擾����
const int GameObjectBase::GetZLayer() const
{
    return z_layer;
}

/// �������擾����
const eMobilityType GameObjectBase::GetMobility() const
{
    return mobility;
}
