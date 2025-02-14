#pragma once

#include "SceneBase.h"

// タイトルシーン
class TitleScene : public SceneBase
{
private:

	class coin* Coin;   //コインの情報
	std::vector<int> coin_animation;   //こいんのアニメーション
	//アニメーション用
	const int animation_num[4] = { 1,2,3,4 };
	int animation_count;
	float animation_time;

	int back_ground_image;   //背景画像

	//タイトル画面UIの設定
	int mario_coin;
	int mario_ui;
	int mario_world;
	int mario_time;
	
	std::vector<int> kakeru_ui;       //コイン横の×の画像
	std::vector<int>coin_num_min;         //コイン取得数の画像十の位
	std::vector<int>coin_num_sec;         //コイン取得数の画像一の位

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

	
};

