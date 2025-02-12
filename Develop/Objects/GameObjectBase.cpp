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
    // デフォルトのコリジョンサイズを設定
    collision.SetPosition(location, D_OBJECT_SIZE, D_OBJECT_SIZE);
}

GameObjectBase::~GameObjectBase()
{
}

/// 初期化処理
void GameObjectBase::Initialize()
{
}

/// 更新処理
void GameObjectBase::Update(float delta_second)
{
    // 位置更新 (速度を考慮)
    location += velocity * delta_second;
    collision.SetPosition(location, collision.GetWidth(), collision.GetHeight());
}

/// 描画処理
void GameObjectBase::Draw(const Vector2D& screen_offset) const
{
    Vector2D graph_location = location + screen_offset;
    DrawRotaGraphF(graph_location.x, graph_location.y, scale, radian, image, TRUE, flip_flag);
}

/// 終了時処理
void GameObjectBase::Finalize()
{
}

/// 当たり判定通知処理
void GameObjectBase::OnHitCollision(GameObjectBase* hit_object)
{
    // 衝突時の処理（派生クラスでオーバーライド）
}

/// 所有シーン情報の設定
void GameObjectBase::SetOwnerScene(SceneBase* scene)
{
    owner_scene = scene;
}

/// 位置座標取得処理
const Vector2D& GameObjectBase::GetLocation() const
{
    return location;
}

/// 位置情報変更処理
void GameObjectBase::SetLocation(const Vector2D& new_location)
{
    location = new_location;
    collision.SetPosition(location, collision.GetWidth(), collision.GetHeight());
}

/// 当たり判定取得処理
RectCollision GameObjectBase::GetCollision() const
{
    return collision;
}

/// 矩形当たり判定情報の設定
void GameObjectBase::SetCollisionRect(float width, float height)
{
    collision.SetPosition(location, width, height);
}

/// Zレイヤー情報取得処理
const int GameObjectBase::GetZLayer() const
{
    return z_layer;
}

/// 可動性情報取得処理
const eMobilityType GameObjectBase::GetMobility() const
{
    return mobility;
}
