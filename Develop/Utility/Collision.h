#pragma once

#include"Vector2D.h"
#include <vector>

// オブジェクトタイプ
enum class eObjectType : unsigned char
{
	none,
	player,
	enemy,
	ground,
	block,
	item,
	floor,
	hatena,
	flag
	
};

//当たり判定のクラス
class Collision
{
public:
	bool is_blocking;	//オブジェクトの動きが止められているか確認する変数
	Vector2D box_size;	//当たり判定の大きさ
	Vector2D pivot;		//当たり判定とオブジェクトのオフセット
	eObjectType object_type;	//オブジェクトのタイプ
	std::vector<eObjectType> hit_object_type;	//当たる資格を持つオブジェクト

private:
	Vector2D position;

public:
	Collision();
	~Collision();

	//当たり判定の位置設置
	void SetPosition(const Vector2D& pos);

	//当たり判定の位置の取得
	const Vector2D& GetPosition() const;

	//当たり判定の大きさ設定
	void SetSize(const float& width, const float& height);

	//当たり判定の大きさ取得
	Vector2D GetSize();

	//オブジェクトタイプの設定
	void SetObjectType(const eObjectType& FUNC_objecttype);

	//当たるオブジェクトタイプの設定
	void SetHitObjectType(const std::vector<eObjectType>& FUNC_hitobjecttype);

	//当たったオブジェクトのタイプ確認
	bool IsCheckHitTarget(eObjectType FUNC_hitobject) const;

	//当たり判定同士が当たっているか確認
	bool CheckCollision(const Collision& other) const;
};
