#include "Collision.h"
#include <math.h>

Collision::Collision() :
	is_blocking(false),
	object_type(eObjectType::none),
	hit_object_type(),
	position(0)
{
}

Collision::~Collision()
{

}

//当たり判定の位置を設置する
void Collision::SetPosition(const Vector2D& pos)
{
	position = pos;
}

//当たり判定の位置を取得する
const Vector2D& Collision::GetPosition() const
{
	return position;
}

//当たり判定の大きさ設置する
void Collision::SetSize(const float& width, const float& height)
{
	box_size.x = width;
	box_size.y = height;
}

// 当たり判定の大きさ設置する
Vector2D Collision::GetSize()
{
	return box_size;
}

//オブジェクトタイプを設置
void Collision::SetObjectType(const eObjectType& FUNC_objecttype)
{
	object_type = FUNC_objecttype;
}

//当たるオブジェクトタイプの設定
void Collision::SetHitObjectType(const std::vector<eObjectType>& FUNC_hitobjecttype)
{
	hit_object_type = FUNC_hitobjecttype;
}

//当たったオブジェクトのタイプ確認する
bool Collision::IsCheckHitTarget(eObjectType FUNC_hitobject) const
{
	//適用するオブジェクトタイプ分ループする
	for (eObjectType type : hit_object_type)
	{
		//適応するタイプならTRUE
		if (type == FUNC_hitobject)
		{
			return true;
		}
	}

	return false;
}

//当たり判定同士が当たっているか確認
bool Collision::CheckCollision(const Collision& other) const
{
	//オブジェクトの当たり判定の位置の変数宣言
	Vector2D A_min = position - (box_size / 2) + pivot;
	Vector2D A_max = position + (box_size / 2) + pivot;

	//当たったオブジェクトの当たり判定の位置の変数宣言
	Vector2D B_min = other.position - (other.box_size / 2) + other.pivot;
	Vector2D B_max = other.position + (other.box_size / 2) + other.pivot;

	//もしオブジェクト同士が当たっていれば true を返す
	if (A_min.x < B_max.x &&
		A_max.x > B_min.x &&
		A_min.y < B_max.y &&
		A_max.y > B_min.y)
	{
		return true;
	}

	return false;
}