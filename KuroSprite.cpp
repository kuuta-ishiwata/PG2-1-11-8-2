#include<stdio.h>
#include<Novice.h>

void Sprite4Fanction
(
	int& Count, int CountReset, int& Flame,
	//���v�J�E���g��//�J�E���g���Z�b�g����t���[��//�L�����t���[��
	int Count1, int Count2, int Count3, int Count4//���t���[���ڂŉ摜��؂�ւ��邩
)

{
	Count++;//�J�E���g�J�n
	if (Count >= Count1)//�P�L�����t���[��
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



	if (Count >= CountReset)//�J�E���g���Z�b�g
	{
		Count = 0;
	}


};

void Tex4Sprite
(
	int& ObjFlameCount, //�v�t���[����
	float ObjPosX, float ObjPosY,
	float ScrSizeX1, float ScrSizeY1,
	float ScrSizeX2, float ScrSizeY2,
	float ScrSizeX3, float ScrSizeY3,
	float ScrSizeX4, float ScrSizeY4,
	//Scr�\���������摜�̂�������
	unsigned int ObjTexname,
	int ObjTexSize,
	float srcX, float srcY, float angle//���摜�̑傫��

)
{
	//�A�Ԃ̍�����\�������
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


