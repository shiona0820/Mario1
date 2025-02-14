#pragma once

#include "SceneBase.h"

class InGameScene : public SceneBase
{
private:
	class Player* player;		// プレイヤー情報
	class kuribo* Kuribo;


	//int back_ground_image;		// 背景画像
	int back_ground_BGM;		// BGM
	//bool pause_flag;			// 一時停止フラグ
	//float scroll;   //背景画面位置替え
	float velocity;

	//タイトル画面UIの設定
	int mario_ui;
	int mario_world;
	int mario_time;

	int fream_time;   //フレームの時間設定

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

};

