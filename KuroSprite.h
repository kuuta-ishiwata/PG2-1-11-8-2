#pragma once
void Sprite4Fanction(
	int& Count, int CountReset, int& Flame,
	//合計カウント数//カウントリセットするフレーム//キャラフレーム
	int Count1, int Count2, int Count3, int Count4//何フレーム目で画像を切り替えるか
);
void Tex4Sprite
(
	int& ObjFlameCount,
	float ObjPosX, float ObjPosY,
	float ScrSizeX1, float ScrSizeY1,
	float ScrSizeX2, float ScrSizeY2,
	float ScrSizeX3, float ScrSizeY3,
	float ScrSizeX4, float ScrSizeY4,

	unsigned int ObjTexname,
	int ObjTexSize,
	float srcX, float srcY, float angle
);