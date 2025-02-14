#include "GameObjectBase.h"
#include "../Scene/SceneBase.h"
#include "DxLib.h"

GameObjectBase::GameObjectBase() :
    owner_scene(nullptr),
    location(0.0f),
    image(-1),
    z_layer(0),
    mobility(eMobilityType::Stationary),
    velocity(0.0f),
    scale(1.0),
    radian(0.0),
    flip_flag(false)
{
    // デフォルトのコリジョンサイズを設定
    SetCollisionRect(D_OBJECT_SIZE, D_OBJECT_SIZE);
}

GameObjectBase::~GameObjectBase()
{
}

void GameObjectBase::Initialize()
{
}

void GameObjectBase::Update(float delta_second)
{
    // 位置更新
    location += velocity * delta_second;

    // 当たり判定の位置をオブジェクトの中央に補正
    float half_width = collision.GetWidth() / 2.0f;
    float half_height = collision.GetHeight() / 2.0f;

    collision.SetPosition(
        Vector2D(location.x - half_width, location.y - half_height),
        collision.GetWidth(),
        collision.GetHeight()
    );

}

void GameObjectBase::Draw(const Vector2D& screen_offset) const
{
    Vector2D graph_location = location + screen_offset;
    DrawRotaGraphF(graph_location.x, graph_location.y, scale, radian, image, TRUE, flip_flag);

    // コリジョンボックスを描画（赤色で表示）
    DrawBox(
        collision.top_left.x + screen_offset.x,
        collision.top_left.y + screen_offset.y,
        collision.bottom_right.x + screen_offset.x,
        collision.bottom_right.y + screen_offset.y,
        GetColor(255, 0, 0), FALSE
    );
}


void GameObjectBase::Finalize()
{
}

void GameObjectBase::OnHitCollision(GameObjectBase* hit_object)
{
}

void GameObjectBase::SetOwnerScene(SceneBase* scene)
{
    owner_scene = scene;
}

const Vector2D& GameObjectBase::GetLocation() const
{
    return location;
}

void GameObjectBase::SetLocation(const Vector2D& new_location)
{
    location = new_location;
    collision.SetPosition(location, collision.GetWidth(), collision.GetHeight());
}

RectCollision GameObjectBase::GetCollision() const
{
    return collision;
}

void GameObjectBase::SetCollisionRect(float width, float height)
{
    box_size.x = width;
    box_size.y = height;

    // location を中心ではなく左上基準に調整
    Vector2D collision_pos = Vector2D(location.x - width / 2.0f, location.y - height / 2.0f);

    collision.SetPosition(collision_pos, width, height);
}


int GameObjectBase::GetZLayer() const
{
    return z_layer;
}

eMobilityType GameObjectBase::GetMobility() const
{
    return mobility;
}
