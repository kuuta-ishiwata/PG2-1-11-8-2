#pragma once
void Sprite4Fanction(
	int& Count, int CountReset, int& Flame,
	//���v�J�E���g��//�J�E���g���Z�b�g����t���[��//�L�����t���[��
	int Count1, int Count2, int Count3, int Count4//���t���[���ڂŉ摜��؂�ւ��邩
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