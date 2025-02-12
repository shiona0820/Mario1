#pragma once

#include "../Utility/Vector2D.h"
#include "../RectCollision.h"  // RectCollisionを使う

#define D_OBJECT_SIZE (24.0f)  // オブジェクトのデフォルトサイズ

// 可動性の種類
enum eMobilityType
{
    Stationary,  // 固定オブジェクト
    Movable,     // 可動オブジェクト
};

<<<<<<< HEAD
enum eType{
	MARIO,
	KURIBO,
};
 
=======
>>>>>>> main
// ゲームオブジェクト基底クラス
class GameObjectBase
{
protected:
<<<<<<< HEAD
	class SceneBase* owner_scene;	// 所有するシーン情報
	Vector2D			location;		// 位置座標
	CapsuleCollision	collision;		// 当たり判定情報
	int					image;			// 画像情報
	int					z_layer;		// レイヤー情報
	eMobilityType		mobility;		// 可動性

	Vector2D velocity;
	Vector2D box_size;   //矩形の大きさ

	double scale;   //大きさ
	double radian;  //向き
	bool flip_flag;   //反転処理
	
	int type;   //オブジェクトのタイプ
	int coniUi;
=======
    class SceneBase* owner_scene;  // 所有するシーン情報
    Vector2D location;             // 位置座標
    Vector2D box_size;             // 仮当たり判定用box
    RectCollision collision;       // 当たり判定情報
    int image;                     // 画像情報
    int z_layer;                   // レイヤー情報
    eMobilityType mobility;        // 可動性情報
    Vector2D velocity;             // 移動速度
    double scale;                  // 大きさ
    double radian;                 // 回転角度
    bool flip_flag;                // 画像反転フラグ
>>>>>>> main

public:
    GameObjectBase();
    virtual ~GameObjectBase();

    // 初期化処理
    virtual void Initialize();

    // 更新処理（時間差分を受け取る）
    virtual void Update(float delta_second);

<<<<<<< HEAD
	//当たり判定の大きさを取得する
	Vector2D GetBoxSize() const;

public:
	// <summary>
	// 所有シーン情報の設定
	// </summary>
	// <param name="scene">所有シーン情報</param>
	void SetOwnerScene(class SceneBase* scene);
=======
    // 描画処理（スクリーンオフセットに基づいて描画）
    virtual void Draw(const Vector2D& screen_offset) const;
>>>>>>> main

    // 終了時処理
    virtual void Finalize();

    // 当たり判定通知処理
    virtual void OnHitCollision(GameObjectBase* hit_object);

    // 所有シーン情報の設定
    void SetOwnerScene(class SceneBase* scene);

    // 位置座標取得
    const Vector2D& GetLocation() const;

    // 位置座標変更
    void SetLocation(const Vector2D& location);

<<<<<<< HEAD
	int GetType();   //自身のタイプの取得

=======
    // 当たり判定情報の取得
    RectCollision GetCollision() const;

    // 矩形当たり判定情報の設定
    void SetCollisionRect(float width, float height);

    // Zレイヤー情報取得
    const int GetZLayer() const;

    // 可動性情報の取得
    const eMobilityType GetMobility() const;
>>>>>>> main
};
