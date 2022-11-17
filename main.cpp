#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdlib.h>
#include<time.h>

#include<player.h>
#include<KuroSprite.h>


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
	Vector2 move;
	float speed;
	float theta;
	int radius;

	int SpawnFlag;
	HitBox hitbox;
	int hitFlag;
	const int Num;
	SHOOT bullet[50];
	int timer;


	
	float MineTheta[16];
	Vector2 MineMove[16];
	int Minetimer;
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

struct Boss
{
	Vector2 position;
	Vector2 center;
	float speed;
	int radius;
	Vector2 move;
	float theta;





};


struct Sound
{
	unsigned int shoot;
	unsigned int Explosion;
};

struct tex
{
	unsigned int PlayerBullet;
	unsigned int RightBullet;
	unsigned int LeftBullet;
	unsigned int Explosion;
	unsigned int starback;
};


struct scroll
{
	Vector2 FrontPosition;
	Vector2 BackPosition;
	float speed;

};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	Novice::Initialize(kWindowTitle, 960 ,780);

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

		Novice::LoadAudio("./Resouce/sound/shot.wav"),
		Novice::LoadAudio("./Resouce/sound/hit.wav")
	};

	tex tex
	{
		Novice::LoadTexture("./Resouce/tex/game/PlayerBullet.png"),
		Novice::LoadTexture("./Resouce/tex/game/RightBullet.png"),
		Novice::LoadTexture("./Resouce/tex/game/LeftBullet.png"),
		Novice::LoadTexture("./Resouce/tex/enemy/Explosion.png"),
		Novice::LoadTexture("./Resouce/tex/game/ShootingBack.png")




	};
	Boss boss
	{
		{336,60},
		{0,0},
		5,
		64,
		{0,0},
		0.0f



	};

	ENEMY zako
	{
		{900,50},
		{50,50},
		5,
		5,
		0.0f,
		32,

	};

	scroll scroll
	{
		{0,0},
		{0,-1500},
		5



	};

	ENEMY mine
	{
		{400,0},
		{0,0},
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
	     },
		0,
		{50},
		3

		
	};


	for (int i = 0; i < 100; i++)
	{
		Player.shoot[i].position = { -100,0 };

	}

	for (int i = 0; i < 16; i++)
	{
		mine.bullet[i].speed = 2;
	}

	

		mine.MineTheta[0] = 0.0f * M_PI;
		mine.MineTheta[1] = 1.0f /2.0* M_PI;

		mine.MineTheta[2] = 3.0f / 2.0f * M_PI;
		mine.MineTheta[3] = 1.0f* M_PI;
		
		mine.MineTheta[4] = 1.0f / 4.0f * M_PI;
		mine.MineTheta[5] = 3.0f / 4.0f * M_PI;

		mine.MineTheta[6] = 5.0f / 4.0f * M_PI;
		mine.MineTheta[7] = 7.0f / 4.0f * M_PI;

		mine.MineTheta[8] = 1.0f/8.0 * M_PI;
		mine.MineTheta[9] = 3.0f / 8.0 * M_PI;

		mine.MineTheta[10] = 5.0f / 8.0f * M_PI;
		mine.MineTheta[11] = 7.0f/8.0 * M_PI;

		mine.MineTheta[12] = 9.0f / 8.0f * M_PI;
		mine.MineTheta[13] = 11.0f / 8.0f * M_PI;

		mine.MineTheta[14] = 13.0f / 8.0f * M_PI;
		mine.MineTheta[15] = 15.0f / 8.0f * M_PI;

	// ライブラリの初期化

		//
		
		int isenemyAlive = 0;
		int zakoriactiontimer = 0;
		int zakoriactionFrame = 0;
		int framcaunt = 0;
		int caunt = 0;
		int speedx = 5;
		int speedy = 1;
		///

		int zako1 = Novice::LoadTexture("./Resouce/tex/enemy/zako1.png");
		int zako2 = Novice::LoadTexture("./Resouce/tex/enemy/zako2.png");
		int zako3 = Novice::LoadTexture("./Resouce/tex/enemy/zako3.png");
		int zako4 = Novice::LoadTexture("./Resouce/tex/enemy/zako4.png");
		//int tama = Novice::LoadTexture("./TDtama.png");

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
			Player.shoot[i].centerpos.x = Player.shoot[i].position.x + 16;

			
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




		
		for (int i = 0; i < Player.Num; i++)
		{
			if (Player.shoot[i].isShoot == 0)
			{
				Player.shoot[i].position = { -100,0 };
				continue;
			}

			if (Player.shoot[i].isShoot == 1)
			{
				Player.shoot[i].position.y -= Player.shoot[i].speed;
			}

			if (Player.shoot[i].position.y <= 0)
			{
				Player.shoot[i].isShoot = 0;
				//Player.shoot[i].position = { -100,0 };

			}

		}//右子機射撃
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
					Player.RightMachine.shoot[i].position = { -100,0 };
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
					Player.LeftMachine.shoot[i].position = { -100,0 };
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
		if (keys[DIK_4])//zako1出現
		{
			isenemyAlive = 1;
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


        

		//プレイヤー主機*地雷当たり判定
			for (int i = 0; i < Player.Num; i++)
			{

				
				if (mine.position.x-32<=Player.shoot[i].position.x-16
					&&
				    Player.shoot[i].position.x <= mine.position.x+32
					)
				{
				
					Novice::ScreenPrintf(500, 500, "aaaaa");
					if (mine.position.y - 32 <= Player.shoot[i].position.y-16
						&&
						Player.shoot[i].position.y <= mine.position.y+32
						)
					{
						Novice::ScreenPrintf(500, 520, "fbebubfuobew");

						Player.shoot[i].isShoot = 0;


						mine.SpawnFlag = 3;
						for (int i = 0; i < 16; i++)
						{
							mine.bullet[i].position.x = mine.position.x;
							mine.bullet[i].position.y = mine.position.y;

						}

					}
				}


				if (mine.position.x - 32 <= Player.RightMachine.shoot[i].position.x - 16
					&&
					Player.RightMachine.shoot[i].position.x <= mine.position.x + 32
					)
				{

					Novice::ScreenPrintf(500, 500, "aaaaa");
					if (mine.position.y - 32 <= Player.RightMachine.shoot[i].position.y - 16
						&&
						Player.RightMachine.shoot[i].position.y <= mine.position.y + 32
						)
					{
						Novice::ScreenPrintf(500, 520, "fbebubfuobew");

						Player.RightMachine.shoot[i].isShoot = 0;


						mine.SpawnFlag = 3;
						for (int i = 0; i < 16; i++)
						{
							mine.bullet[i].position.x = mine.position.x;
							mine.bullet[i].position.y = mine.position.y;

						}

					}


				}
				

				if (mine.position.x - 32 <= Player.LeftMachine.shoot[i].position.x - 16
					&&
					Player.LeftMachine.shoot[i].position.x <= mine.position.x + 32
					)
				{

					Novice::ScreenPrintf(500, 500, "aaaaa");
					if (mine.position.y - 32 <= Player.LeftMachine.shoot[i].position.y - 16
						&&
						Player.LeftMachine.shoot[i].position.y <= mine.position.y + 32
						)
					{
						Novice::ScreenPrintf(500, 520, "fbebubfuobew");

						Player.LeftMachine.shoot[i].isShoot = 0;


						mine.SpawnFlag = 3;
						for (int i = 0; i < 16; i++)
						{
							mine.bullet[i].position.x = mine.position.x;
							mine.bullet[i].position.y = mine.position.y;

						}

					}


				}
			}
			
		}



		if (mine.SpawnFlag==3)
		{
			Novice::ScreenPrintf(600, 600, "%d", mine.SpawnFlag);
			Novice::ScreenPrintf(600, 620, "%d", mine.Num);
			mine.Minetimer++;
			if (mine.Minetimer<=40)
			{


				for (int i = 0; i < 8; i++)
				{
					WASDPush(mine.MineTheta[i], mine.MineMove[i].x, mine.MineMove[i].y, mine.bullet[i].speed);

					mine.bullet[i].position.x += mine.MineMove[i].x;
					mine.bullet[i].position.y += mine.MineMove[i].y;


				}
			}
			if (mine.Minetimer>=40&& mine.Minetimer <= 80)
			{
				for (int i = 8; i < 16; i++)
				{
					WASDPush(mine.MineTheta[i], mine.MineMove[i].x, mine.MineMove[i].y, mine.bullet[i].speed);

					mine.bullet[i].position.x += mine.MineMove[i].x;
					mine.bullet[i].position.y += mine.MineMove[i].y;


				}
			}
			if (mine.Minetimer>=80)
			{
				mine.SpawnFlag = 4;
			}
		}
		if (mine.SpawnFlag==4)
		{
			mine.Minetimer = 0;

		}
		//地雷処理終了
		// 
		// 
		// 
		 
		
		
		//雑魚１動き
		if (isenemyAlive==0)
		{
			zako.position.y = -50;
		}
		if (isenemyAlive == 1)
		{
			zako.position.x += speedx;

			zako.position.y += speedy;


			if (zako.position.x >= 960)
			{
				speedx = -10;
			}
			if (zako.position.x <= 0)
			{
				speedx = 10;
			}

			framcaunt++;
			Novice::ScreenPrintf(200, 0, "%d", framcaunt);
			if (framcaunt >= 0)
			{
				caunt = 1;

			}
			if (framcaunt >= 10)
			{
				caunt = 2;
			}
			if (framcaunt >= 20)
			{
				caunt = 3;
			}
			if (framcaunt >= 30)
			{
				caunt = 0;
				framcaunt = 0;
			}

			for (int i = 0; i < Player.Num; i++)
			{


				if (zako.position.x - 32 <= Player.shoot[i].position.x - 16
					&&
					Player.shoot[i].position.x <= zako.position.x + 32
					)
				{

					Novice::ScreenPrintf(500, 500, "kkkkkkkkk");
					if (zako.position.y - 32 <= Player.shoot[i].position.y - 16
						&&
						Player.shoot[i].position.y <= zako.position.y + 32
						)
					{
						Novice::ScreenPrintf(500, 520, "zzzzzzzz");

						isenemyAlive=2;
						if (!Novice::IsPlayingAudio(sound.Explosion))
						{
							Novice::PlayAudio(sound.Explosion, false, 1.0);
						}

					}


				}

				if (zako.position.x - 32 <= Player.RightMachine.shoot[i].position.x-16
					&&
					Player.RightMachine.shoot[i].position.x  <= zako.position.x + 32
					)
				{

					Novice::ScreenPrintf(500, 500, "kkkkkkkkk");
					if (zako.position.y - 32 <= Player.RightMachine.shoot[i].position.y-16
						&&
						Player.RightMachine.shoot[i].position.y  <= zako.position.y + 32
						)
					{
						Novice::ScreenPrintf(500, 520, "zzzzzzzz");

						isenemyAlive = 2;

						if (!Novice::IsPlayingAudio(sound.Explosion))
						{
							Novice::PlayAudio(sound.Explosion, false, 1.0);
						}

					}
				}

				if (zako.position.x - 32 <= Player.LeftMachine.shoot[i].position.x - 16
					&&
					Player.LeftMachine.shoot[i].position.x <= zako.position.x + 32
					)
				{

					Novice::ScreenPrintf(500, 500, "kkkkkkkkk");
					if (zako.position.y - 32 <= Player.LeftMachine.shoot[i].position.y - 16
						&&
						Player.LeftMachine.shoot[i].position.y <= zako.position.y + 32
						)
					{
						Novice::ScreenPrintf(500, 520, "zzzzzzzz");

						isenemyAlive = 2;

						if (!Novice::IsPlayingAudio(sound.Explosion))
						{
							Novice::PlayAudio(sound.Explosion, false, 1.0);
						}

					}
				}
			}

		}
		if (isenemyAlive==2)
		{
			Sprite4Fanction(zakoriactiontimer, 60, zakoriactionFrame, 0, 15, 30, 45);
			
			
			if (zakoriactiontimer>=59)
			{
				isenemyAlive = 0;
			}
		}



		//ぼす処理開始

		



		///
		/// ↑更新処理ここまで
		///
		scroll.FrontPosition.y += scroll.speed;
		scroll.BackPosition.y += scroll.speed;
		if (scroll.BackPosition.y>=1500)
		{
			scroll.BackPosition.y = -1500;
		}
		if (scroll.FrontPosition.y>=1500)
		{
			scroll.FrontPosition.y = -1500;
		}
		///
		/// ↓描画処理ここから
		///
		/// 
		Novice::DrawSprite(scroll.FrontPosition.x, scroll.FrontPosition.y , tex.starback, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(scroll.BackPosition.x, scroll.BackPosition.y, tex.starback, 1, 1, 0.0f, WHITE);


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
			if (Player.shoot[i].isShoot==1)
			{


				Novice::DrawSprite
				(
					Player.shoot[i].position.x, Player.shoot[i].position.y,
					tex.PlayerBullet, 1, 1, 0.0f, WHITE
				);
			}
		}

		for (int i = 0; i < Player.RightMachine.Num; i++)
		{
			Novice::DrawSprite
			(
				Player.RightMachine.shoot[i].position.x, Player.RightMachine.shoot[i].position.y,
				tex.RightBullet, 1, 1, 0.0f, WHITE
			);
		}
		for (int i = 0; i < Player.LeftMachine.Num; i++)
		{ 
			Novice::DrawSprite
			(
				Player.LeftMachine.shoot[i].position.x, Player.LeftMachine.shoot[i].position.y,
				tex.LeftBullet, 1, 1, 0.0f, WHITE
			);
		}
		if (Player.barrier1.Flag == 1)
		{
			Novice::DrawEllipse(
				Player.barrier1.position.x, Player.barrier1.position.y
				, 16, 16, 0.0f, RED,
				kFillModeSolid);
		}


		if (Player.barrier2.Flag == 1)
		{
			Novice::DrawEllipse(
				Player.barrier2.position.x, Player.barrier2.position.y
				, 16, 16, 0.0f, RED,
				kFillModeSolid);
		}

		if (Player.barrier4.Flag == 1)
		{

			Novice::DrawEllipse(
				Player.barrier4.position.x,
				Player.barrier4.position.y,
				16, 16, 0.0f, RED,
				kFillModeSolid);
		}

		if (Player.barrier3.Flag == 1)
		{

			Novice::DrawEllipse(
				Player.barrier3.position.x, Player.barrier3.position.y
				, 16, 16, 0.0f, RED,
				kFillModeSolid);
		}
		if (mine.SpawnFlag == 3)
		{


			for (int i = 0; i < 16; i++)
			{

				Novice::DrawEllipse(
					mine.bullet[i].position.x,
					mine.bullet[i].position.y,
					16, 16, 0.0f, GREEN, kFillModeSolid
				);

			}
		}

		//雑魚１描画
	

		if (isenemyAlive == 1)
		{
			Novice::ScreenPrintf(0, 100, "tekiON");
			Novice::ScreenPrintf(0, 200, "%d", caunt);
			if (caunt == 0)
			{
				Novice::DrawSprite(zako.position.x, zako.position.y, zako1, 1, 1, 0.0f, WHITE);
			}
			if (caunt == 1)
			{
				Novice::DrawSprite(zako.position.x, zako.position.y, zako2, 1, 1, 0.0f, WHITE);
			}
			if (caunt == 2)
			{
				Novice::DrawSprite(zako.position.x, zako.position.y, zako3, 1, 1, 0.0f, WHITE);
			}
			if (caunt == 3)
			{
				Novice::DrawSprite(zako.position.x, zako.position.y, zako4, 1, 1, 0.0f, WHITE);
			}
			//Novice::DrawBox(enemy.center.X, enemy.center.Y, 10, 10, 0.0f, WHITE, kFillModeSolid);
		}
		if (isenemyAlive == 2)
		{
			Tex4Sprite(zakoriactionFrame, zako.position.x, zako.position.y, 0, 0, 65, 0, 130, 0, 195, 0,
				tex.Explosion, 64, 0.25, 1, 0.0f
			);
		}

		Novice::DrawBox(boss.position.x, boss.position.y, 96, 96, 0.0f, WHITE, kFillModeSolid);


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
