#include<stdio.h>
#include<Novice.h>

void Sprite4Fanction
(
	int& Count, int CountReset, int& Flame,
	//合計カウント数//カウントリセットするフレーム//キャラフレーム
	int Count1, int Count2, int Count3, int Count4//何フレーム目で画像を切り替えるか
)

{
	Count++;//カウント開始
	if (Count >= Count1)//１キャラフレーム
	{
		Flame = 1;
	}
	if (Count >= Count2)
	{
		Flame = 2;
	}
	if (Count >= Count3)
	{
		Flame = 3;
	}
	if (Count >= Count4)
	{
		Flame = 4;
	}



	if (Count >= CountReset)//カウントリセット
	{
		Count = 0;
	}


};

void Tex4Sprite
(
	int& ObjFlameCount, //計フレーム数
	float ObjPosX, float ObjPosY,
	float ScrSizeX1, float ScrSizeY1,
	float ScrSizeX2, float ScrSizeY2,
	float ScrSizeX3, float ScrSizeY3,
	float ScrSizeX4, float ScrSizeY4,
	//Scr表示したい画像のｘｙ入力
	unsigned int ObjTexname,
	int ObjTexSize,
	float srcX, float srcY, float angle//元画像の大きさ

)
{
	//連番の左から表示される
	if (ObjFlameCount == 1)
	{
		Novice::DrawSpriteRect(ObjPosX, ObjPosY, ScrSizeX1, ScrSizeY1, ObjTexSize, ObjTexSize, ObjTexname, srcX, srcY, angle, WHITE);
	}
	if (ObjFlameCount == 2)
	{
		Novice::DrawSpriteRect(ObjPosX, ObjPosY, ScrSizeX2, ScrSizeY2, ObjTexSize, ObjTexSize, ObjTexname, srcX, srcY, angle, WHITE);
	}

	if (ObjFlameCount == 3)
	{
		Novice::DrawSpriteRect(ObjPosX, ObjPosY, ScrSizeX3, ScrSizeY3, ObjTexSize, ObjTexSize, ObjTexname, srcX, srcY, angle, WHITE);
	}
	if (ObjFlameCount == 4)
	{
		Novice::DrawSpriteRect(ObjPosX, ObjPosY, ScrSizeX4, ScrSizeY4, ObjTexSize, ObjTexSize, ObjTexname, srcX, srcY, angle, WHITE);
	}





}


