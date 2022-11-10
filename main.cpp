#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<player.h>

const char kWindowTitle[] = "学籍番号";
struct Vector2
{
	float x;;
	float y;
};

struct HitBox
{
	Vector2 LeTo;
	Vector2 RiTo;
	Vector2 LeBo;
	Vector2 RiBo;

};

struct SHOOT
{
	Vector2 position;
	Vector2 centerpos;
	float speed;
	int isShoot;
	HitBox hitbox;
	
};
struct MACHINE
{
	Vector2 position;
	float speed;
	int SpawnFlag;

	int ShootFlag;
	
	const int Num;
	SHOOT shoot[100];
	
};

struct BARRIER
{
	Vector2 position;
	float speed;
	int Flag;
	Vector2 move;
	float theta;
	int radius;
	const float kRotaAngle;
};
struct ENEMY
{
	Vector2 position;
	Vector2 centerpos;
	float speed;
	float theta;
	int radius;

	int SpawnFlag;
	HitBox hitbox;
	int hitFlag;

};

struct PLAYER
{
	Vector2 position;
	Vector2 PosCenter;
	float speed;
	int radius;
	unsigned int tex;
	Vector2 move;

	float theta;


	HitBox hitbox;

	MACHINE RightMachine;
	MACHINE LeftMachine;



	BARRIER barrier1;
	BARRIER barrier2;
	BARRIER barrier3;
	BARRIER barrier4;


	const int Num ;
	SHOOT shoot[100];
	int ShootMainFlag;
	int timer;
	int LEtimer;
	int RItimer;
};


struct Sound
{
	unsigned int shoot;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	Novice::Initialize(kWindowTitle, 1280, 720);

	PLAYER Player
	{
		{0,0},
		{0,0},
		5,
		16,
		WHITE,
		{0,0},

		0.0f,

		{{0,0},{0,0},{0,0}, {0,0}},

		{{0,0},7,0 ,0,100},
		{{0,0},7,0 ,0,100},

		{ {0,0},4,0,{0,0}, 0.0f,32, 1.0f / 64.0f * float(M_PI) },
		{ {0,0},4,0,{0,0}, 1.5875f,32, 1.0f / 64.0f * float(M_PI) },
		{ {0,0},4,0,{0,0}, 3.175f,32, 1.0f / 64.0f * float(M_PI) },
		{ {0,0},4,0,{0,0}, 4.7625f,32, 1.0f / 64.0f * float(M_PI) },
		100,
		
		{{0,0},{0,0},5,0},
		0,
		10,
		10
	};
	Sound sound
	{

		Novice::LoadAudio("./Resouce/sound/shot.wav")
	};


	ENEMY mine
	{
		{400,0},
		{0,0},
		5,
		0.0f,
		32,
		0,
		//当たり判定
		{
		{0,0},
		{0,0},
		{0,0},
		{0,0}
	     }
		
	};







	// ライブラリの初期化
	

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		//中心
		Player.PosCenter.x = Player.position.x + Player.radius;
		Player.PosCenter.y = Player.position.y + Player.radius;// Player.radius;
		


		Novice::ScreenPrintf(700, 0, "center %f  %f", Player.PosCenter.x, Player.PosCenter.y);
		
		
		//四隅position
		HitBoxFanction(
			Player.radius, Player.PosCenter.x, Player.PosCenter.y,
			Player.hitbox.LeTo.x, Player.hitbox.LeTo.y,
			Player.hitbox.RiTo.x, Player.hitbox.RiTo.y,
			Player.hitbox.LeBo.x, Player.hitbox.LeBo.y,
			Player.hitbox.RiBo.x, Player.hitbox.RiBo.y
		);

		Novice::ScreenPrintf(300, 0, "%f    %f", Player.hitbox.LeTo.x, Player.hitbox.LeTo.y);
		Novice::ScreenPrintf(300, 20, "%f    %f", Player.hitbox.RiTo.x, Player.hitbox.RiTo.y);
		Novice::ScreenPrintf(300, 40, "%f    %f", Player.hitbox.LeBo.x, Player.hitbox.LeBo.y);
		Novice::ScreenPrintf(300, 60, "%f    %f", Player.hitbox.RiBo.x, Player.hitbox.RiBo.y);






		//移動処理
		Player.move = { 0,0 };



		//上
		if (keys[DIK_W])
		{
			Player.theta = 1.0f / 2.0f * M_PI;
			WASDPush(Player.theta, Player.move.x, Player.move.y, Player.speed);

		}
		//下
		if (keys[DIK_S])
		{
			Player.theta = 3.0 / 2.0f * M_PI;
			WASDPush(Player.theta, Player.move.x, Player.move.y, Player.speed);

		}
		//右
		if (keys[DIK_D])
		{
			Player.theta = 0.0f * M_PI;
			WASDPush(Player.theta, Player.move.x, Player.move.y, Player.speed);
		}
		//左
		if (keys[DIK_A])
		{
			Player.theta = 1.0f * M_PI;
			WASDPush(Player.theta, Player.move.x, Player.move.y, Player.speed);
		}
		//右上
		if (keys[DIK_W] && keys[DIK_D])
		{
			Player.theta = 1.0f / 4.0f * M_PI;
			WASDPush(Player.theta, Player.move.x, Player.move.y, Player.speed);
		}
		//左上
		if (keys[DIK_W] && keys[DIK_A])
		{
			Player.theta = 3.0f / 4.0f * M_PI;


			WASDPush(Player.theta, Player.move.x, Player.move.y, Player.speed);
		}
		//右下
		if (keys[DIK_D] && keys[DIK_S])
		{
			Player.theta = 7.0f / 4.0f * M_PI;
			WASDPush(Player.theta, Player.move.x, Player.move.y, Player.speed);
		}
		//左下
		if (keys[DIK_A] && keys[DIK_S])
		{
			Player.theta = 5.0f / 4.0f * M_PI;
			WASDPush(Player.theta, Player.move.x, Player.move.y, Player.speed);
		}

		Player.position.x += Player.move.x;
		Player.position.y -= Player.move.y;

		//移動処理終了


		//射撃


		Player.timer--;
		
		Player.ShootMainFlag = 0;

		if (Player.timer < 0)
		{
			if (keys[DIK_SPACE])
			{
				Player.timer = 10;

				Player.ShootMainFlag = 1;

			}
		};

		if (Player.ShootMainFlag == 1)
		{
			for (int i = 0; i < Player.Num; i++)
			{
				if (Player.shoot[i].isShoot == 0)
				{
					Player.shoot[i].position.x = Player.PosCenter.x-8;
					Player.shoot[i].position.y = Player.PosCenter.y;
					
					if (!Novice::IsPlayingAudio(sound.shoot))
					{
						Novice::PlayAudio(sound.shoot, false, 1.0);
					}

					Player.shoot[i].speed = 8;

					Player.shoot[i].isShoot = 1;
					break;
				}
			}
		}

		for (int i = 0; i < Player.Num; i++)
		{
			Player.shoot[i].centerpos.x = Player.shoot[i].position.x + 16;
			Player.shoot[i].centerpos.x = Player.shoot->position.x + 16;

			
			HitBoxFanction
			(
				16,
				Player.shoot[i].centerpos.x,
				Player.shoot[i].centerpos.y,
				Player.shoot[i].hitbox.LeTo.x,
				Player.shoot[i].hitbox.LeTo.y,
				Player.shoot[i].hitbox.RiTo.x,
			    Player.shoot[i].hitbox.RiTo.y,

				Player.shoot[i].hitbox.LeBo.x,
				Player.shoot[i].hitbox.LeBo.y,
				Player.shoot[i].hitbox.RiBo.x,
				Player.shoot[i].hitbox.RiBo.y
			);
			




		}




		Player.RItimer--;
		Player.LEtimer--;




		//右子機射撃
		for (int i = 0; i < Player.Num; i++)
		{
			if (Player.shoot[i].isShoot == 0)
			{
				continue;
			}

			if (Player.shoot[i].isShoot == 1)
			{
				Player.shoot[i].position.y -= Player.shoot[i].speed;
			}

			if (Player.shoot[i].position.y <= -40)
			{
				Player.shoot[i].isShoot = 0;
			}

		}

		if (Player.RightMachine.SpawnFlag == 1)
		{

			Novice::ScreenPrintf(0, 0, "a");

			Player.RightMachine.ShootFlag = 0;

			if (Player.RItimer < 0)
			{
				Player.RItimer = 25;

				Player.RightMachine.ShootFlag = 1;

			};

			if (Player.RightMachine.ShootFlag == 1)
			{
				for (int i = 0; i < 100; i++)
				{
					if (Player.RightMachine.shoot[i].isShoot == 0)
					{
						Player.RightMachine.shoot[i].position.x = Player.RightMachine.position.x + 4;
						Player.RightMachine.shoot[i].position.y = Player.RightMachine.position.y;

						Player.RightMachine.shoot[i].speed = 8;

						Player.RightMachine.shoot[i].isShoot = 1;
						break;
					}
				}
			}


			for (int i = 0; i < 100; i++)
			{
				if (Player.RightMachine.shoot[i].isShoot == 0)
				{
					continue;
				}

				if (Player.RightMachine.shoot[i].isShoot == 1)
				{
					Player.RightMachine.shoot[i].position.y -= Player.RightMachine.shoot[i].speed;
				}

				if (Player.RightMachine.shoot[i].position.y <= -40)
				{
					Player.RightMachine.shoot[i].isShoot = 0;
				}

			}
			

		}

		//左子機射撃
	
		if (Player.LeftMachine.SpawnFlag == 1)
		{

			

			Player.LeftMachine.ShootFlag = 0;

			if (Player.LEtimer < 0)
			{
				Player.LEtimer = 25;

				Player.LeftMachine.ShootFlag = 1;

			};

			if (Player.LeftMachine.ShootFlag == 1)
			{
				for (int i = 0; i < 100; i++)
				{
					if (Player.LeftMachine.shoot[i].isShoot == 0)
					{
						Player.LeftMachine.shoot[i].position.x = Player.LeftMachine.position.x + 4;
						Player.LeftMachine.shoot[i].position.y = Player.LeftMachine.position.y;

						Player.LeftMachine.shoot[i].speed = 8;

						Player.LeftMachine.shoot[i].isShoot = 1;
						break;
					}
				}
			}


			for (int i = 0; i < 100; i++)
			{
				if (Player.LeftMachine.shoot[i].isShoot == 0)
				{
					continue;
				}

				if (Player.LeftMachine.shoot[i].isShoot == 1)
				{
					Player.LeftMachine.shoot[i].position.y -= Player.LeftMachine.shoot[i].speed;
				}

				if (Player.LeftMachine.shoot[i].position.y <= -40)
				{
					Player.LeftMachine.shoot[i].isShoot = 0;
				}

			}


		}
		//射撃終了
		
		//テスト
		if (keys[DIK_1])//子機出現
		{
			Player.RightMachine.SpawnFlag = 1;
			Player.LeftMachine.SpawnFlag = 1;
		}

		if (keys[DIK_2])//バリア出現
		{
			Player.barrier1.Flag = 1;
			Player.barrier2.Flag = 1;
			Player.barrier3.Flag = 1;
			Player.barrier4.Flag = 1;
		}
		if (keys[DIK_3])//地雷出現
		{
			mine.SpawnFlag = 1;
			mine.position.y = 0;
		}



		if (Player.RightMachine.SpawnFlag == 1)
		{

			Player.RightMachine.position.x = Player.position.x+64;
			Player.RightMachine.position.y = Player.PosCenter.y - 8;
		}

		if (Player.LeftMachine.SpawnFlag == 1)
		{

			Player.LeftMachine.position.x = Player.position.x-48;
			Player.LeftMachine.position.y = Player.PosCenter.y - 8;



		}

		Novice::ScreenPrintf(0, 40, "%f      %f", Player.position.x, Player.position.y);
		Novice::ScreenPrintf(0, 60, "%f      %f", Player.LeftMachine.position.x, Player.LeftMachine.position.y);
		Novice::ScreenPrintf(0, 80, "%f      %f", Player.RightMachine.position.x, Player.RightMachine.position.y);
		


		if (Player.barrier1.Flag == 1)
		{

			BarrierPosfanction
			(
				Player.barrier1.theta,
				Player.position.x, Player.position.y,
				Player.barrier1.position.x,
				Player.barrier1.position.y

			);

			Novice::DrawEllipse(
				Player.barrier1.position.x, Player.barrier1.position.y
				, 16, 16, 0.0f, RED,
				kFillModeSolid);
		}


		if (Player.barrier2.Flag == 1)
		{

			BarrierPosfanction
			(
				Player.barrier2.theta,
				Player.position.x, Player.position.y,
				Player.barrier2.position.x,
				Player.barrier2.position.y

			);
			Novice::DrawEllipse(
				Player.barrier2.position.x, Player.barrier2.position.y
				, 16, 16, 0.0f, RED,
				kFillModeSolid);
		}

		if (Player.barrier4.Flag == 1)
		{

			BarrierPosfanction
			(
				Player.barrier4.theta,
				Player.position.x, Player.position.y,
				Player.barrier4.position.x,
				Player.barrier4.position.y

			);
			Novice::DrawEllipse(
				Player.barrier4.position.x,
				Player.barrier4.position.y,
				16, 16, 0.0f, RED,
				kFillModeSolid);
		}

		if (Player.barrier3.Flag == 1)
		{

			BarrierPosfanction
			(
				Player.barrier3.theta,
				Player.position.x, Player.position.y,
				Player.barrier3.position.x,
				Player.barrier3.position.y

			);

			Novice::DrawEllipse(
				Player.barrier3.position.x, Player.barrier3.position.y
				, 16, 16, 0.0f, RED,
				kFillModeSolid);
		}



		//プレイヤー処理終了

		//地雷処理開始
		if (mine.SpawnFlag==1)
		{
			mine.centerpos.x=mine.position.x+mine.radius;
			mine.centerpos.y = mine.position.y + mine.radius;

			mine.position.y += mine.speed;

			HitBoxFanction
			(
				mine.radius,
				mine.centerpos.x,
				mine.centerpos.y,
				mine.hitbox.LeTo.x,
				mine.hitbox.LeTo.y,
				mine.hitbox.RiTo.x,
				mine.hitbox.RiTo.y,

				mine.hitbox.LeBo.x,
				mine.hitbox.LeBo.y,
				mine.hitbox.RiBo.x,
				mine.hitbox.RiBo.y
			);

			
			for (int i = 0; i < Player.Num; i++)
			{


				if (mine.hitbox.LeTo.x<=Player.shoot[i].hitbox.RiTo.x
					&&
				    Player.shoot[i].hitbox.LeTo.x <= mine.hitbox.RiTo.x
					)
				{
					Novice::ScreenPrintf(500, 500, "aaaaa");
					if (mine.hitbox.LeTo.y <= Player.shoot[i].hitbox.RiTo.y
						&&
						Player.shoot[i].hitbox.LeTo.y <= mine.hitbox.RiTo.y
						)
					{
						Novice::ScreenPrintf(500, 520, "fbebubfuobew");



					}


				}
			}
			
		}
	




		

		/*
		if (isenemyAlive == true)
		{
			enemy.center.X += enemy.speed;

		}
		if (enemy.center.X + 65 >= 1280)
		{
			enemy.speed *= -1;
			//framcaunt += 8;
		}
		if (enemy.center.X - 25 <= 700)
		{
			enemy.speed *= -1;

			//framcaunt += 8;

		}
		framcaunt++;
		if (framcaunt >= 15)
		{
			framcaunt = 0;
			caunt++;
			if (caunt >= 3)
			{
				caunt = 0;
			}
		}
		*/
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		/// 

		Novice::DrawBox(
			Player.position.x,
			Player.position.y,
			32, 32, 0.0f, WHITE, kFillModeSolid
		);

		Novice::DrawBox(
			Player.RightMachine.position.x,
			Player.RightMachine.position.y,
			24, 24, 0.0f, WHITE, kFillModeSolid
		);
		Novice::DrawBox(
			Player.LeftMachine.position.x,
			Player.LeftMachine.position.y,
			24, 24, 0.0f, WHITE, kFillModeSolid
		);
		
		//地雷　
		if (mine.SpawnFlag == 1)
		{
			Novice::DrawBox(
				mine.position.x, mine.position.y,
				mine.radius, mine.radius,
				0.0f, RED, kFillModeWireFrame

			);
		}



		Novice::DrawLine(Player.barrier1.position.x, Player.barrier1.position.y,
			Player.barrier3.position.x, Player.barrier3.position.y, WHITE
		);
		Novice::DrawLine(Player.barrier2.position.x, Player.barrier2.position.y,
			Player.barrier4.position.x, Player.barrier4.position.y, WHITE
		);

		Novice::DrawEllipse(Player.position.x +16, Player.position.y + 16, 100, 100, 0.0f, WHITE, kFillModeWireFrame);

		for (int i = 0; i < Player.Num; i++)
		{
			Novice::DrawBox(
				Player.shoot[i].position.x, Player.shoot[i].position.y, 
				16, 16, 0.0f, BLACK, kFillModeSolid
			);
		}

		for (int i = 0; i < Player.RightMachine.Num; i++)
		{


			Novice::DrawBox(
				Player.RightMachine.shoot[i].position.x, Player.RightMachine.shoot[i].position.y,
				16, 16, 0.0f, GREEN, kFillModeSolid
			);
		}
		for (int i = 0; i < Player.LeftMachine.Num; i++)
		{


			Novice::DrawBox(
				Player.LeftMachine.shoot[i].position.x, Player.LeftMachine.shoot[i].position.y,
				16, 16, 0.0f, BLUE, kFillModeSolid
			);
		}




		/*
		if (isenemyAlive == true)
		{
			Novice::ScreenPrintf(0, 100, "tekiON");
			if (caunt == 0)
			{
				Novice::DrawSprite(enemy.center.X, enemy.center.Y, zako1, 1, 1, 0.0f, WHITE);
			}
			if (caunt == 1)
			{
				Novice::DrawSprite(enemy.center.X, enemy.center.Y, zako2, 1, 1, 0.0f, WHITE);
			}
			if (caunt == 2)
			{
				Novice::DrawSprite(enemy.center.X, enemy.center.Y, zako3, 1, 1, 0.0f, WHITE);
			}
			if (caunt == 3)
			{
				Novice::DrawSprite(enemy.center.X, enemy.center.Y, zako4, 1, 1, 0.0f, WHITE);
			}
			Novice::DrawBox(enemy.center.X, enemy.center.Y, 10, 10, 0.0f, WHITE, kFillModeSolid);
		}
		*/
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
