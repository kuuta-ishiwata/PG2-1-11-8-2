#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdlib.h>
#include<time.h>

#include<player.h>
#include<KuroSprite.h>
#include<boss.h>

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
	int Hp;


};

struct Boss
{
	Vector2 position;
	Vector2 center;
	float speed;
	int radius;
	Vector2 move;
   Vector2 theta;

	int SpawnFlag;
	int moveFlag;

	int ShootFlag;
	SHOOT MainShoot[100];
	SHOOT RightShoot[100];
	SHOOT LeftShoot[100];
	float MainTheta;
	float RightTheta;
	float LeftTheta;
	int bullettimer;

	Vector2 MainMove[100];
	Vector2 RightMove[100];
	Vector2 LeftMove[100];

	SHOOT RightLaser[200];
	SHOOT LeftLaser[200];
	int RightLaserFlag;
	int LeftLaserFlag;
	int LazerPosY;

	Vector2 PastPlayerPosition;
	int LaserCount;
	int HP; 
	int SpawnCount;
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
	unsigned int Mine;
	unsigned int MineBullet;

};


struct Scroll
{
	Vector2 FrontPosition;
	Vector2 BackPosition;
	float speed;

};

struct Enemy2 {
	Vector2 pos;
	Vector2 speed;
	float radius;
	int isShot;
	int isAlive;
	unsigned int color;
};
typedef struct EnemyBullet {
	Vector2 pos;
	Vector2 speed;
	float radius;
	int isBullet;
};

enum Game
{
	title,
	home,
	tutorial,
	play,
	clear,
	over


};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	Novice::Initialize(kWindowTitle, 960 ,780);

	PLAYER Player
	{
		{440,550},
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
		Novice::LoadTexture("./Resouce/tex/game/player/PlayerBullet.png"),
		Novice::LoadTexture("./Resouce/tex/game/player/RightBullet.png"),
		Novice::LoadTexture("./Resouce/tex/game/player/LeftBullet.png"),
		Novice::LoadTexture("./Resouce/tex/game/Explosion.png"),
		Novice::LoadTexture("./Resouce/tex/game/ShootingBack.png"),
		Novice::LoadTexture("./Resouce/tex/game/enemy/Mine.png"),
		Novice::LoadTexture("./Resouce/tex/game/enemy/MineBullet.png")




	};

	Boss boss
	{
		{336,60},
		{0,0},
		3,
		64,
		{0,0},
		0.0f,
		0,
		0,
		0
		



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

	Scroll scroll
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
	boss.bullettimer = 0;
	const int bossbulletNum = 100;
	boss.RightLaserFlag=0;
	boss.LeftLaserFlag=0;
	boss.LazerPosY = 400;
	boss.LaserCount = 0;
	for (int i = 0; i < 100; i++)
	{


		boss.MainShoot[i].speed = 3;
		boss.LeftShoot[i].speed = 3;
		boss.RightShoot[i].speed = 3;
	}
	boss.HP = 400;

	//地雷弾初期化
	mine.SpawnFlag = 1;
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

	//ボス弾初期化
		boss.MainTheta = 3.0 / 2.0 * M_PI;
		boss.RightTheta = 3.0f / 8.0f * M_PI;
		boss.LeftTheta = 5.0f / 8.0f * M_PI;
		boss.SpawnCount = 0;
		

		Player.Hp = 5;
		int  MineBulletPlayerhit = 0;
		int MineBulletPlayerhitCount=0;

		
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

		int zako1 = Novice::LoadTexture("./Resouce/tex/game/enemy/zako1.png");
		int zako2 = Novice::LoadTexture("./Resouce/tex/game/enemy/zako2.png");
		int zako3 = Novice::LoadTexture("./Resouce/tex/game/enemy/zako3.png");
		int zako4 = Novice::LoadTexture("./Resouce/tex/game/enemy/zako4.png");
		//int tama = Novice::LoadTexture("./TDtama.png");
	
		
		//ランダム生成
		unsigned int currentTime = time(nullptr);
		srand(currentTime);

		//スイッチ
		int game= title;
		int GameCount = 0;


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
		/// 
		
		
		switch (game)
		{
		case title:

			if (keys[DIK_SPACE]&&preKeys[DIK_SPACE]==0)
			{
				game = home;

			}

			break;
		case home:

			if (keys[DIK_W]&&preKeys[DIK_W]==0)
			{
				for (int i = 0; i < 1; i++)
				{

					GameCount--;
				}

			}

			if (keys[DIK_S]&&preKeys[DIK_S]==0)
			{
				for (int i = 0; i < 1; i++)
				{
					GameCount++;
				}

			}
			if (GameCount<=0)
			{
				GameCount = 0;

			}
			if (GameCount>=1)
			{
				GameCount = 1;
			}
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{


				if (GameCount == 0)
				{
					game = tutorial;
				}

				if (GameCount == 1)
				{
					game = play;
				}
			}

		//初期化
			{
			
				 boss=
				{
					{336,60},
					{0,0},
					3,
					64,
					{0,0},
					0.0f,
					0,
					0,
					0




				};


				scroll=
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
				boss.bullettimer = 0;
				
				boss.RightLaserFlag = 0;
				boss.LeftLaserFlag = 0;
				boss.LazerPosY = 400;
				boss.LaserCount = 0;
				for (int i = 0; i < 100; i++)
				{


					boss.MainShoot[i].speed = 3;
					boss.LeftShoot[i].speed = 3;
					boss.RightShoot[i].speed = 3;
				}
				boss.HP = 400;

				//地雷弾初期化
				mine.SpawnFlag = 1;
				mine.MineTheta[0] = 0.0f * M_PI;
				mine.MineTheta[1] = 1.0f / 2.0 * M_PI;

				mine.MineTheta[2] = 3.0f / 2.0f * M_PI;
				mine.MineTheta[3] = 1.0f * M_PI;

				mine.MineTheta[4] = 1.0f / 4.0f * M_PI;
				mine.MineTheta[5] = 3.0f / 4.0f * M_PI;

				mine.MineTheta[6] = 5.0f / 4.0f * M_PI;
				mine.MineTheta[7] = 7.0f / 4.0f * M_PI;

				mine.MineTheta[8] = 1.0f / 8.0 * M_PI;
				mine.MineTheta[9] = 3.0f / 8.0 * M_PI;

				mine.MineTheta[10] = 5.0f / 8.0f * M_PI;
				mine.MineTheta[11] = 7.0f / 8.0 * M_PI;

				mine.MineTheta[12] = 9.0f / 8.0f * M_PI;
				mine.MineTheta[13] = 11.0f / 8.0f * M_PI;

				mine.MineTheta[14] = 13.0f / 8.0f * M_PI;
				mine.MineTheta[15] = 15.0f / 8.0f * M_PI;

				//ボス弾初期化
				boss.MainTheta = 3.0 / 2.0 * M_PI;
				boss.RightTheta = 3.0f / 8.0f * M_PI;
				boss.LeftTheta = 5.0f / 8.0f * M_PI;
				boss.SpawnCount = 0;


				Player.Hp = 5;
				MineBulletPlayerhit = 0;
				MineBulletPlayerhitCount = 0;
				break;
				//Player.Hp = 5;
			}

			boss.HP = 400;
			zako.position = { 400,-50 };
			mine.position = { 300,-50 };
			Player.Hp = 5;
			break;
		case tutorial:
				break;
		case play:
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
			for (int i = 0; i < Player.Num; i++)
			{


				if (Player.shoot[i].isShoot == 0)
				{
					Player.shoot[i].position = { -200,0 };
				}
				if (Player.LeftMachine.shoot[i].isShoot == 0)
				{
					Player.LeftMachine.shoot[i].position = { -200,0 };
				}
				if (Player.RightMachine.shoot[i].isShoot == 0)
				{
					Player.RightMachine.shoot[i].position = { -200,0 };
				}
			}

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
						Player.shoot[i].position.x = Player.PosCenter.x - 8;
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
							Player.RightMachine.shoot[i].position.y = Player.RightMachine.position.y - 8;

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
							Player.LeftMachine.shoot[i].position.y = Player.LeftMachine.position.y - 8;

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






			if (Player.RightMachine.SpawnFlag == 1)
			{

				Player.RightMachine.position.x = Player.position.x + 64;
				Player.RightMachine.position.y = Player.PosCenter.y - 8;
			}

			if (Player.LeftMachine.SpawnFlag == 1)
			{

				Player.LeftMachine.position.x = Player.position.x - 48;
				Player.LeftMachine.position.y = Player.PosCenter.y - 8;



			}


			Novice::ScreenPrintf(0, 0, "%d", Player.Hp);
			if (Player.Hp <= 5)
			{
				Player.barrier1.Flag = 1;
				Player.barrier2.Flag = 1;
				Player.barrier3.Flag = 1;
				Player.barrier4.Flag = 1;
			}

			if (Player.Hp <= 4)
			{
				Player.barrier1.Flag = 1;
				Player.barrier2.Flag = 1;
				Player.barrier3.Flag = 1;
				Player.barrier4.Flag = 0;

			}
			if (Player.Hp <= 3)
			{
				Player.barrier1.Flag = 1;
				Player.barrier2.Flag = 0;
				Player.barrier3.Flag = 1;
				Player.barrier4.Flag = 0;

			}
			if (Player.Hp <= 2)
			{
				Player.barrier1.Flag = 1;
				Player.barrier2.Flag = 0;
				Player.barrier3.Flag = 0;
				Player.barrier4.Flag = 0;
			}
			if (Player.Hp <= 1)
			{
				Player.barrier1.Flag = 0;
				Player.barrier2.Flag = 0;
				Player.barrier3.Flag = 0;
				Player.barrier4.Flag = 0;
			}

			if (Player.Hp <= 0)
			{
				//gameover

			}






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
			if (mine.SpawnFlag == 4)
			{
				mine.position = { 0,-50 };
				int mineRandX = rand();
				mineRandX = mineRandX % 864 + 96;
				mine.position.x = mineRandX;




				mine.SpawnFlag = 1;
			}

			if (mine.SpawnFlag == 1)
			{
				mine.centerpos.x = mine.position.x + mine.radius;
				mine.centerpos.y = mine.position.y + mine.radius;

				mine.position.y += mine.speed;
				if (mine.position.y >= 850)
				{
					mine.SpawnFlag = 1;
				}
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

				if (mine.position.x <= Player.position.x + 32
					&&
					Player.position.x <= mine.position.x + 32
					)
				{
					if (mine.position.y <= Player.position.y + 32
						&&
						Player.position.y <= mine.position.y + 32
						)
					{


						mine.SpawnFlag = 4;

						for (int i = 0; i < 1; i++)
						{
							Player.Hp -= 1;
						}
						if (!Novice::IsPlayingAudio(sound.Explosion))
						{
							Novice::PlayAudio(sound.Explosion, false, 1.0);
						}

					}
				}


				//プレイヤー主機*地雷当たり判定
				for (int i = 0; i < Player.Num; i++)
				{


					if (mine.position.x - 32 <= Player.shoot[i].position.x - 16
						&&
						Player.shoot[i].position.x <= mine.position.x + 32
						)
					{

						Novice::ScreenPrintf(500, 500, "aaaaa");
						if (mine.position.y - 32 <= Player.shoot[i].position.y - 16
							&&
							Player.shoot[i].position.y <= mine.position.y + 32
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
			if (mine.position.y >= 850)
			{

				mine.SpawnFlag = 4;
			}


			if (mine.SpawnFlag == 3)
			{

				mine.Minetimer++;
				if (mine.Minetimer <= 200)
				{


					for (int i = 0; i < 8; i++)
					{
						WASDPush(mine.MineTheta[i], mine.MineMove[i].x, mine.MineMove[i].y, mine.bullet[i].speed);

						mine.bullet[i].position.x += mine.MineMove[i].x;
						mine.bullet[i].position.y += mine.MineMove[i].y;


					}
				}
				if (mine.Minetimer >= 40 && mine.Minetimer <= 300)
				{
					for (int i = 8; i < 16; i++)
					{
						WASDPush(mine.MineTheta[i], mine.MineMove[i].x, mine.MineMove[i].y, mine.bullet[i].speed);

						mine.bullet[i].position.x += mine.MineMove[i].x;
						mine.bullet[i].position.y += mine.MineMove[i].y;


					}
				}
				if (mine.Minetimer >= 300)
				{
					mine.SpawnFlag = 4;
				}


				for (int i = 0; i < 16; i++)
				{
					if (MineBulletPlayerhit == 0)
					{


						if (mine.bullet[i].position.x - 16 <= Player.position.x + 32
							&&
							Player.position.x <= mine.bullet[i].position.x + 16
							)
						{
							if (mine.bullet[i].position.y - 16 <= Player.position.y + 32
								&&
								Player.position.y <= mine.bullet[i].position.y + 16
								)
							{
								for (int i = 0; i < 1; i++)
								{
									Player.Hp -= 1;
								}
								if (!Novice::IsPlayingAudio(sound.Explosion))
								{
									Novice::PlayAudio(sound.Explosion, false, 1.0);
								}
								MineBulletPlayerhit = 1;

							}
						}
					}



				}

				if (MineBulletPlayerhit == 1)
				{
					MineBulletPlayerhitCount++;
					if (MineBulletPlayerhitCount >= 60)
					{
						MineBulletPlayerhit = 0;
						MineBulletPlayerhitCount = 0;

					}

				}


			}
			if (mine.SpawnFlag == 4)
			{

				mine.position = { 0,-50 };
				int mineRandX = rand();
				mineRandX = mineRandX % 864 + 96;
				mine.position.x = mineRandX;




				mine.SpawnFlag = 1;

				mine.Minetimer = 0;
				mine.SpawnFlag = 1;

			}
			//地雷処理終了
			// 
			// 
			// 



			//雑魚１動き
			if (isenemyAlive == 0)
			{
				zako.position.y = -50;

				int zakoRandPosX = rand();
				zakoRandPosX = zakoRandPosX % 864 + 96;
				zako.position.x = zakoRandPosX;

				isenemyAlive = 1;

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


						if (zako.position.y - 32 <= Player.shoot[i].position.y - 16
							&&
							Player.shoot[i].position.y <= zako.position.y + 32
							)
						{


							isenemyAlive = 2;
							if (!Novice::IsPlayingAudio(sound.Explosion))
							{
								Novice::PlayAudio(sound.Explosion, false, 1.0);
							}

						}


					}

					if (zako.position.x - 32 <= Player.RightMachine.shoot[i].position.x - 16
						&&
						Player.RightMachine.shoot[i].position.x <= zako.position.x + 32
						)
					{


						if (zako.position.y - 32 <= Player.RightMachine.shoot[i].position.y - 16
							&&
							Player.RightMachine.shoot[i].position.y <= zako.position.y + 32
							)
						{

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


						if (zako.position.y - 32 <= Player.LeftMachine.shoot[i].position.y - 16
							&&
							Player.LeftMachine.shoot[i].position.y <= zako.position.y + 32
							)
						{


							isenemyAlive = 2;

							if (!Novice::IsPlayingAudio(sound.Explosion))
							{
								Novice::PlayAudio(sound.Explosion, false, 1.0);
							}

						}
					}


				}
				if (zako.position.x <= Player.position.x
					&&
					Player.position.x <= zako.position.x + 32
					)
				{
					if (zako.position.y <= Player.position.y + 32
						&&
						Player.position.y <= zako.position.y + 32
						)
					{


						isenemyAlive = 2;

						for (int i = 0; i < 1; i++)
						{
							Player.Hp -= 1;
						}
						if (!Novice::IsPlayingAudio(sound.Explosion))
						{
							Novice::PlayAudio(sound.Explosion, false, 1.0);
						}

					}
				}
				if (zako.position.y >= 800)
				{
					isenemyAlive = 0;
				}

			}
			if (isenemyAlive == 2)
			{
				Sprite4Fanction(zakoriactiontimer, 60, zakoriactionFrame, 0, 15, 30, 45);


				if (zakoriactiontimer >= 59)
				{
					isenemyAlive = 0;

				}
			}




			//ぼす処理開始

			//テストボス沸きkey０

			if (keys[DIK_0])
			{
				boss.SpawnFlag = 1;

			}

			if (keys[DIK_9])
			{
				boss.SpawnFlag = 2;

			}


			//boss弾/playermain
			for (int i = 0; i < 100; i++)
			{
				if (boss.MainShoot[i].position.x - 32 <= Player.shoot[i].position.x - 16
					&&
					Player.shoot[i].position.x <= boss.MainShoot[i].position.x + 32
					)
				{


					if (boss.MainShoot[i].position.y - 32 <= Player.shoot[i].position.y - 16
						&&
						Player.shoot[i].position.y <= boss.MainShoot[i].position.y + 32
						)
					{


						boss.MainShoot[i].isShoot = 0;
						Player.shoot[i].isShoot = 0;

					}
				}
			}

			//
			for (int i = 0; i < 100; i++)
			{
				if (boss.RightShoot[i].position.x <= Player.shoot[i].position.x + 32
					&&
					Player.shoot[i].position.x <= boss.RightShoot[i].position.x + 32
					)
				{

					if (boss.RightShoot[i].position.y <= Player.shoot[i].position.y + 32
						&&
						Player.shoot[i].position.y <= boss.RightShoot[i].position.y + 32
						)
					{


						boss.RightShoot[i].isShoot = 0;
						Player.shoot[i].isShoot = 0;

					}
				}
			}

			//右
			for (int i = 0; i < 100; i++)
			{


				if (boss.LeftShoot[i].position.x <= Player.shoot[i].position.x + 32
					&&
					Player.shoot[i].position.x <= boss.LeftShoot[i].position.x + 64
					)
				{
					\
						if (boss.LeftShoot[i].position.y <= Player.shoot[i].position.y + 32
							&&
							Player.shoot[i].position.y <= boss.LeftShoot[i].position.y + 32
							)
						{


							boss.LeftShoot[i].isShoot = 0;
							Player.shoot[i].isShoot = 0;

						}
				}
			}
			//左
			for (int i = 0; i < 100; i++)
			{
				if (boss.MainShoot[i].position.x <= Player.RightMachine.shoot[i].position.x + 32
					&&
					Player.RightMachine.shoot[i].position.x <= boss.MainShoot[i].position.x + 64
					)
				{


					if (boss.MainShoot[i].position.y <= Player.RightMachine.shoot[i].position.y + 32
						&&
						Player.RightMachine.shoot[i].position.y <= boss.MainShoot[i].position.y + 32
						)
					{


						boss.MainShoot[i].isShoot = 0;
						Player.RightMachine.shoot[i].isShoot = 0;

					}
				}
			}


			for (int i = 0; i < 100; i++)
			{
				if (boss.RightShoot[i].position.x <= Player.RightMachine.shoot[i].position.x + 32
					&&
					Player.RightMachine.shoot[i].position.x <= boss.RightShoot[i].position.x + 32
					)
				{


					if (boss.RightShoot[i].position.y <= Player.RightMachine.shoot[i].position.y + 32
						&&
						Player.RightMachine.shoot[i].position.y <= boss.RightShoot[i].position.y + 32
						)
					{

						boss.RightShoot[i].isShoot = 0;
						Player.RightMachine.shoot[i].isShoot = 0;

					}
				}
			}
			for (int i = 0; i < 100; i++)
			{


				if (boss.LeftShoot[i].position.x <= Player.RightMachine.shoot[i].position.x + 32
					&&
					Player.RightMachine.shoot[i].position.x <= boss.LeftShoot[i].position.x + 32
					)
				{
					if (boss.LeftShoot[i].position.y <= Player.RightMachine.shoot[i].position.y + 32
						&&
						Player.RightMachine.shoot[i].position.y <= boss.LeftShoot[i].position.y + 32
						)
					{
						boss.LeftShoot[i].isShoot = 0;
						Player.RightMachine.shoot[i].isShoot = 0;

					}
				}
			}

			for (int i = 0; i < 100; i++)
			{
				if (boss.MainShoot[i].position.x <= Player.LeftMachine.shoot[i].position.x + 32
					&&
					Player.LeftMachine.shoot[i].position.x <= boss.MainShoot[i].position.x + 64
					)
				{


					if (boss.MainShoot[i].position.y <= Player.LeftMachine.shoot[i].position.y + 32
						&&
						Player.LeftMachine.shoot[i].position.y <= boss.MainShoot[i].position.y + 32
						)
					{


						boss.MainShoot[i].isShoot = 0;
						Player.LeftMachine.shoot[i].isShoot = 0;

					}
				}
			}


			for (int i = 0; i < 100; i++)
			{
				if (boss.RightShoot[i].position.x <= Player.LeftMachine.shoot[i].position.x + 32
					&&
					Player.LeftMachine.shoot[i].position.x <= boss.RightShoot[i].position.x + 32
					)
				{


					if (boss.RightShoot[i].position.y <= Player.LeftMachine.shoot[i].position.y + 32
						&&
						Player.LeftMachine.shoot[i].position.y <= boss.RightShoot[i].position.y + 32
						)
					{


						boss.RightShoot[i].isShoot = 0;
						Player.LeftMachine.shoot[i].isShoot = 0;

					}
				}
			}
			for (int i = 0; i < 100; i++)
			{


				if (boss.LeftShoot[i].position.x <= Player.LeftMachine.shoot[i].position.x + 32
					&&
					Player.LeftMachine.shoot[i].position.x <= boss.LeftShoot[i].position.x + 32
					)
				{

					if (boss.LeftShoot[i].position.y <= Player.LeftMachine.shoot[i].position.y + 32
						&&
						Player.LeftMachine.shoot[i].position.y <= boss.LeftShoot[i].position.y + 32
						)
					{


						boss.LeftShoot[i].isShoot = 0;
						Player.LeftMachine.shoot[i].isShoot = 0;

					}
				}
			}
			boss.SpawnCount++;

			if (boss.SpawnCount >= 3500)
			{
				boss.SpawnFlag = 1;
			}

			if (boss.SpawnFlag >= 1)
			{
				Novice::ScreenPrintf(30, 0, "%d", boss.HP);
				//動き処理

				if (boss.moveFlag == 1)
				{
					boss.theta.x = 0.0f * M_PI;
					boss.theta.y = 1.0 / 2.0 * M_PI;

					BossMoveFanction(boss.theta.x, boss.move.x, boss.move.y, boss.speed);

					if (boss.position.x >= 800)
					{
						boss.moveFlag = 0;
					}




				}
				if (boss.moveFlag == 0)
				{
					boss.theta.x = 1.0f * M_PI;


					BossMoveFanction(boss.theta.x, boss.move.x, boss.move.y, boss.speed);

					if (boss.position.x <= 96)
					{
						boss.moveFlag = 1;
					}


				}


				boss.position.x += boss.move.x;
				boss.position.y -= boss.move.y;

				//動き処理終了
				boss.ShootFlag = 0;
				if (boss.ShootFlag == 0)
				{


					boss.bullettimer--;
					if (boss.bullettimer <= 0)
					{

						boss.bullettimer = 70;
						boss.ShootFlag = 1;
					}
				}


				for (int i = 0; i < 100; i++)
				{
					if (boss.MainShoot[i].position.x <= Player.position.x + 32
						&&
						Player.position.x <= boss.MainShoot[i].position.x + 64
						)
					{


						if (boss.MainShoot[i].position.y <= Player.position.y + 32
							&&
							Player.position.y <= boss.MainShoot[i].position.y + 32
							)
						{


							boss.MainShoot[i].isShoot = 0;
							for (int i = 0; i < 1; i++)
							{
								Player.Hp--;
							}

						}
					}
				}


				for (int i = 0; i < 100; i++)
				{
					if (boss.RightShoot[i].position.x <= Player.position.x + 32
						&&
						Player.position.x <= boss.RightShoot[i].position.x + 32
						)
					{


						if (boss.RightShoot[i].position.y <= Player.position.y + 32
							&&
							Player.position.y <= boss.RightShoot[i].position.y + 32
							)
						{


							boss.RightShoot[i].isShoot = 0;
							for (int i = 0; i < 1; i++)
							{
								Player.Hp--;
							}


						}
					}
				}
				for (int i = 0; i < 100; i++)
				{


					if (boss.LeftShoot[i].position.x <= Player.position.x + 32
						&&
						Player.position.x <= boss.LeftShoot[i].position.x + 32
						)
					{

						if (boss.LeftShoot[i].position.y <= Player.position.y + 32
							&&
							Player.position.y <= boss.LeftShoot[i].position.y + 32
							)
						{


							boss.LeftShoot[i].isShoot = 0;
							for (int i = 0; i < 1; i++)
							{
								Player.Hp--;
							}


						}
					}
				}



				for (int i = 0; i < 100; i++)
				{
					if (boss.position.x <= Player.shoot[i].position.x + 16
						&&
						Player.shoot[i].position.x <= boss.position.x + 96
						)
					{


						if (boss.position.y <= Player.shoot[i].position.y + 16
							&&
							Player.shoot[i].position.y <= boss.position.y + 96
							)
						{

							for (int j = 0; j < 1; j++)
							{
								boss.HP--;
							}
							Player.shoot[i].isShoot = 0;

						}
					}
				}
				for (int i = 0; i < 100; i++)
				{


					if (boss.position.x <= Player.RightMachine.shoot[i].position.x + 16
						&&
						Player.RightMachine.shoot[i].position.x <= boss.position.x + 96
						)
					{

						if (boss.position.y <= Player.RightMachine.shoot[i].position.y + 16
							&&
							Player.RightMachine.shoot[i].position.y <= boss.position.y + 96
							)
						{


							for (int j = 0; j < 1; j++)
							{
								boss.HP--;
							}
							Player.RightMachine.shoot[i].isShoot = 0;

						}
					}
				}
				for (int i = 0; i < 100; i++)
				{
					if (boss.position.x <= Player.LeftMachine.shoot[i].position.x + 16
						&&
						Player.LeftMachine.shoot[i].position.x <= boss.position.x + 96
						)
					{

						if (boss.position.y <= Player.LeftMachine.shoot[i].position.y + 16
							&&
							Player.LeftMachine.shoot[i].position.y <= boss.position.y + 96
							)
						{


							for (int j = 0; j < 1; j++)
							{
								boss.HP--;
							}
							Player.LeftMachine.shoot[i].isShoot = 0;

						}
					}
				}
				//


				//弾処理
				// 
				// 
				// 






				if (boss.ShootFlag == 1)
				{
					for (int i = 0; i < 100; i++)
					{
						if (boss.MainShoot[i].isShoot == 0)
						{
							boss.MainShoot[i].position.x = boss.position.x + 32;
							boss.MainShoot[i].position.y = boss.position.y + 48;

							boss.MainShoot[i].speed = 3.7;
							WASDPush(boss.MainTheta, boss.MainMove[i].x, boss.MainMove[i].y, boss.MainShoot[i].speed);
							boss.MainShoot[i].isShoot = 1;
							break;
						}
					}

					for (int i = 0; i < 100; i++)
					{
						if (boss.RightShoot[i].isShoot == 0)
						{
							boss.RightShoot[i].position.x = boss.position.x + 32;
							boss.RightShoot[i].position.y = boss.position.y + 48;

							boss.RightShoot[i].speed = 3.5;
							WASDPush(boss.RightTheta, boss.RightMove[i].x, boss.RightMove[i].y, boss.RightShoot[i].speed);

							boss.RightShoot[i].isShoot = 1;
							break;
						}
					}
					for (int i = 0; i < 100; i++)
					{
						if (boss.LeftShoot[i].isShoot == 0)
						{
							boss.LeftShoot[i].position.x = boss.position.x + 32;
							boss.LeftShoot[i].position.y = boss.position.y + 48;

							boss.LeftShoot[i].speed = 3.5;
							WASDPush(boss.LeftTheta, boss.LeftMove[i].x, boss.LeftMove[i].y, boss.LeftShoot[i].speed);

							boss.LeftShoot[i].isShoot = 1;
							break;
						}
					}

				}


				//弾後処理
				for (int i = 0; i < 100; i++)
				{
					if (boss.MainShoot[i].isShoot == 0)
					{
						boss.MainShoot[i].position = { -200,0 };
						continue;
					}

					if (boss.MainShoot[i].isShoot == 1)
					{
						boss.MainShoot[i].position.x += boss.MainMove[i].x;
						boss.MainShoot[i].position.y -= boss.MainMove[i].y;
					}

					if (boss.MainShoot[i].position.y >= 900)
					{
						boss.MainShoot[i].isShoot = 0;

					}
				}

				for (int i = 0; i < 100; i++)
				{
					if (boss.RightShoot[i].isShoot == 0)
					{
						boss.RightShoot[i].position = { -200,0 };
						continue;
					}

					if (boss.RightShoot[i].isShoot == 1)
					{

						boss.RightShoot[i].position.x += boss.RightMove[i].x;
						boss.RightShoot[i].position.y += boss.RightMove[i].y;
					}

					if (boss.RightShoot[i].position.y >= 900)
					{
						boss.RightShoot[i].isShoot = 0;

					}
				}

				for (int i = 0; i < 100; i++)
				{
					if (boss.LeftShoot[i].isShoot == 0)
					{
						boss.LeftShoot[i].position = { -200,0 };
						continue;
					}

					if (boss.LeftShoot[i].isShoot == 1)
					{

						boss.LeftShoot[i].position.x += boss.LeftMove[i].x;
						boss.LeftShoot[i].position.y += boss.LeftMove[i].y;
					}

					if (boss.LeftShoot[i].position.y >= 900)
					{
						boss.LeftShoot[i].isShoot = 0;

					}
				}

			}
			//レーザー処理

			if (boss.HP <= 200)
			{
				boss.RightLaserFlag = 1;
				boss.LeftLaserFlag = 1;
			}



			if (boss.RightLaserFlag == 1)
			{
				for (int i = 0; i < 100; i++)
				{
					if (boss.RightLaser[i].isShoot == 0)
					{
						boss.RightLaser[i].position.x = 960;
						boss.RightLaser[i].position.y = boss.LazerPosY - 30;

						boss.RightLaser[i].speed = 8;

						boss.RightLaser[i].isShoot = 1;
						break;
					}
				}



				for (int i = 0; i < 100; i++)
				{
					if (boss.RightLaser[i].isShoot == 0)
					{
						boss.RightLaser[i].position = { -100,0 };

						continue;
					}

					if (boss.RightLaser[i].isShoot == 1)
					{
						boss.RightLaser[i].position.x -= boss.RightLaser[i].speed;
					}


				}
				if (boss.RightLaser[99].isShoot == 1)
				{
					if (boss.RightLaser[99].position.x <= 0)
					{

						boss.RightLaserFlag = 2;

					}


				}

			}




			if (boss.LeftLaserFlag == 1)
			{
				for (int i = 0; i < 100; i++)
				{
					if (boss.LeftLaser[i].isShoot == 0)
					{
						boss.LeftLaser[i].position.x = -50;
						boss.LeftLaser[i].position.y = boss.LazerPosY + 92;

						boss.LeftLaser[i].speed = 8;

						boss.LeftLaser[i].isShoot = 1;
						break;
					}
				}



				for (int i = 0; i < 100; i++)
				{
					if (boss.LeftLaser[i].isShoot == 0)
					{
						boss.LeftLaser[i].position = { -100,0 };

						continue;
					}

					if (boss.LeftLaser[i].isShoot == 1)
					{
						boss.LeftLaser[i].position.x += boss.LeftLaser[i].speed;
					}


				}
				if (boss.LeftLaser[99].isShoot == 1)
				{
					if (boss.LeftLaser[99].position.x >= 980)
					{

						boss.LeftLaserFlag = 2;

					}


				}

			}
			if (boss.LeftLaserFlag == 2 && boss.LeftLaserFlag == 2)
			{



				for (int i = 0; i < 100; i++)
				{
					boss.LeftLaser[i].isShoot = 0;

				}



				for (int i = 0; i < 100; i++)
				{
					boss.RightLaser[i].isShoot = 0;

				}
				boss.LazerPosY = Player.position.y;
				boss.RightLaserFlag = 1;

				boss.LeftLaserFlag = 1;

			}



			///
			/// ↑更新処理ここまで
			///
			scroll.FrontPosition.y += scroll.speed;
			scroll.BackPosition.y += scroll.speed;
			if (scroll.BackPosition.y >= 1500)
			{
				scroll.BackPosition.y = -1500;
			}
			if (scroll.FrontPosition.y >= 1500)
			{
				scroll.FrontPosition.y = -1500;
			}

			if (Player.Hp<=0)
			{
				game = over;


			}
			if (boss.HP<=0)
			{
				game = clear;
			}
			break;
		case clear:

			if (keys[DIK_SPACE]&&preKeys[DIK_SPACE]==0)
			{
				game = title;
			}
			break;
		case over:	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
		{
			game = title;
		}
			break;
		default:
			break;
		}
		
		
		
		///
		/// ↓描画処理ここから
		///
		/// 
		/// 
		/// 

switch (game)
{
case title:

	Novice::ScreenPrintf(0, 0, "fjaihfh" );
	break;

case home:
	break;

case tutorial:
	break;

case play:

	Novice::DrawSprite(scroll.FrontPosition.x, scroll.FrontPosition.y, tex.starback, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(scroll.BackPosition.x, scroll.BackPosition.y, tex.starback, 1, 1, 0.0f, WHITE);
	Novice::ScreenPrintf(0, 40, "%d", boss.SpawnCount);

	Novice::DrawBox(
		Player.position.x,
		Player.position.y,
		32, 32, 0.0f, WHITE, kFillModeSolid
	);
	if (Player.RightMachine.SpawnFlag == 1)
	{


		Novice::DrawBox(
			Player.RightMachine.position.x,
			Player.RightMachine.position.y,
			24, 24, 0.0f, WHITE, kFillModeSolid
		);
	}
	if (Player.LeftMachine.SpawnFlag == 1)
	{


		Novice::DrawBox(
			Player.LeftMachine.position.x,
			Player.LeftMachine.position.y,
			24, 24, 0.0f, WHITE, kFillModeSolid
		);
	}
	//地雷　
	if (mine.SpawnFlag == 1)
	{
		Novice::DrawSprite(mine.position.x, mine.position.y, tex.Mine, 1, 1, 0.0f, WHITE);

	}





	for (int i = 0; i < Player.Num; i++)
	{
		if (Player.shoot[i].isShoot == 1)
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
		if (Player.RightMachine.shoot[i].isShoot == 1)
		{


			Novice::DrawSprite
			(
				Player.RightMachine.shoot[i].position.x, Player.RightMachine.shoot[i].position.y,
				tex.RightBullet, 1, 1, 0.0f, WHITE
			);
		}
	}
	for (int i = 0; i < Player.LeftMachine.Num; i++)
	{
		if (Player.LeftMachine.shoot[i].isShoot == 1)
		{


			Novice::DrawSprite
			(
				Player.LeftMachine.shoot[i].position.x, Player.LeftMachine.shoot[i].position.y,
				tex.LeftBullet, 1, 1, 0.0f, WHITE
			);
		}
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
			Novice::DrawSprite(
				mine.bullet[i].position.x - 16,
				mine.bullet[i].position.y - 16,
				tex.MineBullet,
				1, 1, 0.0f, WHITE


			);
		}
	}

	//雑魚１描画


	if (isenemyAlive == 1)
	{

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



	if (boss.SpawnFlag >= 1)
	{


		Novice::DrawBox(boss.position.x, boss.position.y, 96, 96, 0.0f, WHITE, kFillModeSolid);




		for (int i = 0; i < 100; i++)
		{
			if (boss.MainShoot[i].isShoot == 1)
			{

				Novice::DrawBox(boss.MainShoot[i].position.x, boss.MainShoot[i].position.y, 32, 32, 0.0f, RED, kFillModeSolid);

			}
			if (boss.RightShoot[i].isShoot == 1)
			{

				Novice::DrawBox(boss.RightShoot[i].position.x, boss.RightShoot[i].position.y, 32, 32, 0.0f, RED, kFillModeSolid);

			}
			if (boss.LeftShoot[i].isShoot == 1)
			{

				Novice::DrawBox(boss.LeftShoot[i].position.x, boss.LeftShoot[i].position.y, 32, 32, 0.0f, RED, kFillModeSolid);

			}
		}
	}
	if (boss.RightLaserFlag == 1)
	{

		for (int i = 0; i < 100; i++)
		{
			if (boss.RightLaser[i].isShoot == 1)
			{

				Novice::DrawBox(boss.RightLaser[i].position.x, boss.RightLaser[i].position.y, 32, 32, 0.0f, GREEN, kFillModeSolid);

			}
		}
	}
	if (boss.LeftLaserFlag == 1)
	{

		for (int i = 0; i < 100; i++)
		{
			if (boss.LeftLaser[i].isShoot == 1)
			{

				Novice::DrawBox(boss.LeftLaser[i].position.x, boss.LeftLaser[i].position.y, 32, 32, 0.0f, GREEN, kFillModeSolid);

			}
		}
	}
	break;


default:
	break;

}


Novice::ScreenPrintf(50, 50, "%d", GameCount);

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
