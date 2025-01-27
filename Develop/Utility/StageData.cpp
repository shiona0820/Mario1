#include "StageData.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputManager.h"
#include "DxLib.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

//#include "../Objects/GameObjectBase.h"

//#define D_OBJECT_SIZE	(24.0f)			// 壁のサイズ

StageData* StageData::instance = nullptr;

/// <summary>
/// ステージデータを読み込む
/// </summary>
void StageData::Load()
{
	//ファイルを開く(.csv)
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/StageMap.csv";
	//指定したファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	//横１行全部入るように
	char buffer[435];

	
	int y = 0;
	ResourceManager* rm = ResourceManager::GetInstance();

	//fgetsでファイルから１行抜き出す
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{

		int x = 0;   //x座標(列番号)

		//1行のデータを1文字ずつ処理したい
		for(char* p = buffer; *p != '\0'; ++p)
		{
			const float block_size = 32.0f;
			if (*p == ',')
			{
				continue;
			}
			if (*p == '\n')
			{
				break;
			}

			Vector2D generate_location = Vector2D((float)x, (float)y) * block_size;
			//対象の文字があるか確認
			//空
			if (*p == 's')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/sora.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//山１
			if (*p == 'm')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/mountain_left.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//山２
			if (*p == '1')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/mountain_right.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//山３
			if (*p == '2')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/mountain_surface.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//山4
			if (*p == '3')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/mountain_surface1.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//山5
			if (*p == '4')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/mountain_surface2.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//山６
			if (*p == '5')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/mountain_up.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//雲
			if (*p == 'c')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/cloud1.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//雲１
			if (*p == '6')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/cloud2.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//雲２
			if (*p == '7')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/cloud3.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//雲３
			if (*p == '8')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/cloud4.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//雲４
			if (*p == '9')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/cloud5.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//雲５
			if (*p == 'a')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/cloud6.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//はっぱ１
			if (*p == 'h')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/ha0.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//はっぱ２
			if (*p == 'b')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/ha1.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//はっぱ３
			if (*p == 'd')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/ha2.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//床
			if (*p == 'f')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/Block/floor.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}


			//ブロック
			if (*p == 'B')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/Block/Block.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//ハテナブロック
			if (*p == 'H')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/Block/hatena.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//クリボー
			if (*p == 'C')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/配置素材/クリボー.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//キノコ
			if (*p == 'K')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/配置素材/キノコ配置.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//緑ノコ
			if (*p == 'M')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/配置素材/緑ノコ.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//スター
			if (*p == 'S')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/配置素材/スター配置.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//1up
			if (*p == 'U')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/配置素材/1up配置.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//コイン
			if (*p == 'A')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/配置素材/コイン配置.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//フラグ１
			if (*p == 'F')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/flag.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//フラグ２
			if (*p == 'G')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/flag_siro.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//ポール
			if (*p == 'P')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/pole.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			if (*p == 'p')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/pole_down.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//城
			if (*p == 'I')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/siro1.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//階段
			if (*p == 'v')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/Block/kai_block.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//から？
			if (*p == 'w')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/Block/kara_block.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//横土管
			if (*p == 'Y')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/yokodokan_left_down.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			if (*p == 'j')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/yokodokan_left_up.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			if (*p == 'n')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/yokodokan_middle_down.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			if (*p == 'o')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/yokodokan_middle_up.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			if (*p == 'q')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/yokodokan_right_down.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			if (*p == 'r')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/yokodokan_right_up.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//縦土管
			if (*p == 'D')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/dokan_left_down.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			if (*p == 'e')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/dokan_left_up.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			if (*p == 'g')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/dokan_right_down.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			if (*p == 'i')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/dokan_right_up.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}


			//地下壁
			if (*p == 'T')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/Block/blackblock.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//地下床
			if (*p == 't')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/Block/tika_floor.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}
			//ちっちゃいやつ
			if (*p == 'V')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/Block/bloak_1.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//ちっちゃいやつ
			if (*p == 'z')
			{
				//対象の文字があれば「２次元座標」と「画像情報」を覚える
				int image_sora = rm->GetImages("Resource/images/Item/star.png").at(0);
				DrawGraph((int)generate_location.x + velocity.x, (int)generate_location.y, image_sora, TRUE);
			}

			//次の列
			x++;

		}

		//次の行
		y++;
		
	}
	
	
	//ファイルを閉じる
	fclose(fp);
}

void StageData::Draw()
{
	
}


StageData* StageData::GetInstance()
{
	if (instance ==nullptr)
	{
		instance = new StageData();
	}
	return instance;
}

void StageData::Update(float delta_second)
{
	if (velocity.x <= -6100)
	{
		velocity.x = -6100;
	}
}

Vector2D StageData::GetVelocity()
{
	return velocity;
}

void StageData::SetVelocity(float velo)
{
	velocity.x -= velo;
}