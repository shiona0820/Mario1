#pragma once
#define D_PIVOT_CENTER

#include "SceneBase.h"

class InGameScene : public SceneBase
{
private:
	class Player* player;		// プレイヤー情報
	class kuribo* Kuribo;      //クリボーの情報
	class nokonoko* Nokonoko;  //のこのこの情報
	class coin* Coin;          //コインの情報

	std::vector<int> coin_animation;   //こいんのアニメーション
	//アニメーション用
	const int animation_num[4] = { 1,2,3,4 };
	int animation_count;
	float animation_time;

	std::vector<kuribo> enemies;      //複数描画用


	int back_ground_BGM;		// BGM
	
	float velocity;

	//タイトル画面UIの設定
	int mario_ui;
	int mario_world;
	int mario_time;

	int fream_time;   //フレームの時間設定

	std::vector<int> kakeru_ui;       //コイン横の×の画像
	std::vector<int>coin_num_min;         //コイン取得数の画像十の位
	std::vector<int>coin_num_sec;         //コイン取得数の画像一の位

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

private:
	void AnimeCount(float delta_secound);

};

