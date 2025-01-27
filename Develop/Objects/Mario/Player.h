#pragma once

#include "../GameObject.h"
#include "../../Utility/Vector2D.h"
#include "../../Utility/StageData.h"

// プレイヤー状態
enum ePlayerState
{
	IDLE,		// 待機状態
	MOVE,		// 移動状態
	DIE,		// 死亡状態
	Damage,     //ダメージ
	Jump,       //ジャンプ
};

/// <summary>
/// プレイヤークラス（パックマン）
/// </summary>
class Player : public GameObject
{
private:
	// 進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

private:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	std::vector<int> jump_animation;        //ジャンプのアニメーション画像
	std::vector<int> dying_animation;		// 死亡のアニメーション画像

	Vector2D old_location;					// 前回のlocation(ジャンプ)
	Vector2D velocity;						// 移動量

	Vector2D jump_location;
	Vector2D jump_velocity;

	eDirectionState now_direction_state;	// 現在進行方向状態
	eDirectionState next_direction_state;	// 次回進行方向状態
	int food_count;							// 餌を食べた数
	float animation_time;					// アニメーション時間
	//int animation_count;					// アニメーション添字
	//ePanelID old_panel;						// 前回パネル情報
	bool is_power_up;						// パワー餌を食べたか？
	bool is_destroy;						// 死んだ状態になったか？

	// 移動アニメーションの順番
	const int animation_num[4] = { 1, 2, 3, 2, };
	const int jump_animation_num[2] = { 1,5 };

	//アニメーションのカウント
	int animation_count;
	
	//画面スクロール用
	bool scroll_end;
	int g_velocity;

	//ジャンプのSE
	int jump_SE;

	Player* player;
public:
	int screenoffset;   //スクロール用の原点用の変数

	



public:
	ePlayerState player_state;				// プレイヤー状態

	static Player* GetInstance();

private:
	static Player* instance;

public:
	Player();
	virtual ~Player();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

	/*void Draw(float sscreen_offsetcre);*/

	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	/// <summary>
	/// 餌を食べた数取得
	/// </summary>
	/// <returns>餌を食べた数</returns>
	int GetFoodCount() const;

	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	ePlayerState GetPlayerState() const;

	/// <summary>
	/// プレイヤーがパワーアップしてるか確認する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	bool GetPowerUp() const;

	/// <summary>
	/// パワーダウンさせる
	/// </summary>
	void SetPowerDown();

	/// <summary>
	/// プレイヤーがパワーアップしてるか確認する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	bool GetDestroy() const;

	//位置情報取得処理
	const Vector2D& GetVelocity() const;

	void SetScrollEnd();

	//プレイヤーの状態
	ePlayerState PlayerState();

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);

};
