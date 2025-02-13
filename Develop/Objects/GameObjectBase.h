#pragma once

#include "../Utility/Vector2D.h"
#include "../RectCollision.h"  // 矩形コリジョンを使用

#define D_OBJECT_SIZE (36.0f)  // オブジェクトのデフォルトサイズ

// 可動性の種類
enum eMobilityType
{
    Stationary,  // 固定オブジェクト
    Movable,     // 可動オブジェクト
};

// ゲームオブジェクト基底クラス
class GameObjectBase
{
protected:
    class SceneBase* owner_scene;  // 所属するシーン
    Vector2D location;             // 位置座標
    RectCollision collision;       // 当たり判定情報
    int image;                     // 画像ID
    int z_layer;                   // 描画レイヤー
    eMobilityType mobility;        // 可動性情報
    Vector2D velocity;             // 移動速度
    double scale;                  // スケール
    double radian;                 // 回転角度
    bool flip_flag;                 // 画像の反転フラグ

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
