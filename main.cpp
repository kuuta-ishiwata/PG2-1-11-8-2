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

	int Flame;
	int FlameCount;
};
struct Circle
{
	SHOOT attack[32];
	float theta[32];
	Vector2 move[32];
	Vector2 move2[32];
	Vector2 speed;
	Vector2 center;
	int Flag;
	int timer;
	int ModeChange;
	float  thetaMove1;
	float thetaMove2;
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

	int Flame;
	int Flamecount;
	Circle circle;
};


struct Sound
{
	unsigned int shoot;
	unsigned int Explosion;
	unsigned int Select;
	unsigned int clear;
	unsigned int over;
	unsigned int playerhit;
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
	unsigned int title;
	unsigned int tutorial;
	unsigned int tutorialSelect;
	unsigned int Play;
	unsigned int PlaySelect;
	unsigned int selectMark;
	unsigned int SelectBack;
	unsigned int TutorialSelectPlay;
	unsigned int gameover;
	unsigned int gameclear;
	unsigned int lazerBullet;
	unsigned int PlayerRiLe;
	unsigned int Player;
	unsigned int Boss;
	unsigned int BossBullet;
	unsigned int playerHP;
	unsigned int BossHP; 
	unsigned int titlename;
};




struct Scroll
{
	Vector2 FrontPosition;
	Vector2 BackPosition;
	float speed;

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
		Novice::LoadAudio("./Resouce/sound/hit.wav"),
		Novice::LoadAudio("./Resouce/sound/Select.wav"),
		Novice::LoadAudio("./Resouce/sound/clear.wav"),
		Novice::LoadAudio("./Resouce/sound/over.wav"),
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
		Novice::LoadTexture("./Resouce/tex/game/enemy/MineBullet.png"),
		Novice::LoadTexture("./Resouce/tex/mode/title.png"),
		Novice::LoadTexture("./Resouce/tex/mode/Tutorial.png"),
		Novice::LoadTexture("./Resouce/tex/mode/tutorialSelect.png"),
		Novice::LoadTexture("./Resouce/tex/mode/Play.png"),
		Novice::LoadTexture("./Resouce/tex/mode/PlaySelect.png"),
		Novice::LoadTexture("./Resouce/tex/mode/SelectMark.png"),
		Novice::LoadTexture("./Resouce/tex/mode/select.png"),
		Novice::LoadTexture("./Resouce/tex/mode/TutoRial2.png"),
        Novice::LoadTexture("./Resouce/tex/mode/gameover.png"),
        Novice::LoadTexture("./Resouce/tex/mode/gameclear.png"),
		Novice::LoadTexture("./Resouce/tex/game/enemy/Lazer.png"),
		Novice::LoadTexture("./Resouce/tex/game/player/koki.png"),
		Novice::LoadTexture("./Resouce/tex/game/player/Player.png"),
		Novice::LoadTexture("./Resouce/tex/game/enemy/Boss.png"),
		Novice::LoadTexture("./Resouce/tex/game/enemy/BossBullet.png"),
		Novice::LoadTexture("./Resouce/tex/game/player/HP.png"),
		Novice::LoadTexture("./Resouce/tex/game/enemy/HP.png"),
		Novice::LoadTexture("./Resouce/tex/mode/titlename.png")
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

		for (int i = 1; i < 16; i++)
		{

			boss.circle.theta[i] += 1.0f / 8.0f *M_PI;
			boss.circle.speed = { 5,5 };
			boss.circle.attack[i].position = { 240,195 };
		}
		for (int i = 17; i < 32; i++)
		{
			boss.circle.theta[i] += 1.0f / 8.0f * M_PI;
			boss.circle.attack[i].position = { 720,585 };
		}
	

	//ボス弾初期化
		boss.MainTheta = 3.0 / 2.0 * M_PI;
		boss.RightTheta = 3.0f / 8.0f * M_PI;
		boss.LeftTheta = 5.0f / 8.0f * M_PI;
		boss.SpawnCount = 0;
		

		Player.Hp = 5;
		int  MineBulletPlayerhit = 0;
		int MineBulletPlayerhitCount=0;
		int LazerhitCLT = 0;
		int LazerhitCLTflag = 0;


		Player.Flame = 0;
		Player.FlameCount = 0;
		boss.Flamecount = 0;
		boss.Flamecount=0; 


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
				if (!Novice::IsPlayingAudio(sound.Select))
				{
					Novice::PlayAudio(sound.Select, false, 1.0);
				}

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

				if (!Novice::IsPlayingAudio(sound.Select))
				{
					Novice::PlayAudio(sound.Select, false, 1.0);
				}
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
				Player.barrier1.theta = 0.0f;
				Player.barrier2.theta= 1.5875f;
				Player.barrier3.theta= 3.175f;
				Player.barrier4.theta= 4.7625f;


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
				mine.SpawnFlag = 4;
				mine.Minetimer = 0;
				mine.position = { 0,-50 };
				zako.position = { 0,-50 };
			


 				boss.HP = 400;
				zako.position = { 400,-50 };
				mine.position = { 300,-50 };

		
				for (int i = 0; i < 16; i++)
				{
					
					boss.circle.move[i] = {0,0};
					boss.circle.speed = { 2,2 };
					boss.circle.attack[i].position = { 240,195 };
				}

			boss.circle.theta[0] = 0.0f * M_PI;
			boss.circle.theta[1] = 1.0f / 2.0 * M_PI;
			
			boss.circle.theta[2] = 3.0f / 2.0f * M_PI;
			boss.circle.theta[3] = 1.0f * M_PI;
		
			boss.circle.theta[4] = 1.0f / 4.0f * M_PI;
			boss.circle.theta[5] = 3.0f / 4.0f * M_PI;
		
			boss.circle.theta[6] = 5.0f / 4.0f * M_PI;
			boss.circle.theta[7] = 7.0f / 4.0f * M_PI;
			
			boss.circle.theta[8] = 1.0f / 8.0 * M_PI;
			boss.circle.theta[9] = 3.0f / 8.0 * M_PI;
		
			boss.circle.theta[10] = 5.0f / 8.0f * M_PI;
			boss.circle.theta[11] = 7.0f / 8.0 * M_PI;
			
			boss.circle.theta[12] = 9.0f / 8.0f * M_PI;
			boss.circle.theta[13] = 11.0f / 8.0f * M_PI;
		
			boss.circle.theta[14] = 13.0f / 8.0f * M_PI;
			boss.circle.theta[15] = 15.0f / 8.0f * M_PI;
			

				for (int i = 16; i < 32; i++)
				{
				
					boss.circle.move[i] = { 0,0 };
					boss.circle.theta[i] += 1.0f / 8.0f * M_PI;
					boss.circle.attack[i].position = { 670,585 };
				}
				boss.circle.theta[16] = 0.0f * M_PI;
				boss.circle.theta[17] = 1.0f / 2.0 * M_PI;

				boss.circle.theta[18] = 3.0f / 2.0f * M_PI;
				boss.circle.theta[19] = 1.0f * M_PI;

				boss.circle.theta[20] = 1.0f / 4.0f * M_PI;
				boss.circle.theta[21] = 3.0f / 4.0f * M_PI;

				boss.circle.theta[22] = 5.0f / 4.0f * M_PI;
				boss.circle.theta[23] = 7.0f / 4.0f * M_PI;

				boss.circle.theta[24] = 1.0f / 8.0 * M_PI;
				boss.circle.theta[25] = 3.0f / 8.0 * M_PI;

				boss.circle.theta[26] = 5.0f / 8.0f * M_PI;
				boss.circle.theta[27] = 7.0f / 8.0 * M_PI;

				boss.circle.theta[28] = 9.0f / 8.0f * M_PI;
				boss.circle.theta[29] = 11.0f / 8.0f * M_PI;

				boss.circle.theta[30] = 13.0f / 8.0f * M_PI;
				boss.circle.theta[31] = 15.0f / 8.0f * M_PI;
				boss.circle.thetaMove1 = 1.0f/2.0f*M_PI;
				boss.circle.thetaMove2 = 3.0f/2.0*M_PI;

				for (int i = 0; i < 32; i++)
				{


					boss.circle.move2[i] = { 0,0 };
				}
				Player.Hp = 5;
				boss.circle.ModeChange = 0;
				break;
				//Player.Hp = 5;
			}
		
		
			break;
		case tutorial:

			if (keys[DIK_SPACE]&&preKeys[DIK_SPACE]==0)
			{
				game = home;
				if (!Novice::IsPlayingAudio(sound.Select))
				{
					Novice::PlayAudio(sound.Select, false, 1.0);
				}
			}

				break;
		case play:
			Player.PosCenter.x = Player.position.x + Player.radius;
			Player.PosCenter.y = Player.position.y + Player.radius;// Player.radius;



			//四隅position
			HitBoxFanction(
				Player.radius, Player.PosCenter.x, Player.PosCenter.y,
				Player.hitbox.LeTo.x, Player.hitbox.LeTo.y,
				Player.hitbox.RiTo.x, Player.hitbox.RiTo.y,
				Player.hitbox.LeBo.x, Player.hitbox.LeBo.y,
				Player.hitbox.RiBo.x, Player.hitbox.RiBo.y
			);

		




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


			//Novice::ScreenPrintf(0, 0, "%d", Player.Hp);
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

						
						if (mine.position.y - 32 <= Player.shoot[i].position.y - 16
							&&
							Player.shoot[i].position.y <= mine.position.y + 32
							)
						{
							

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

				
						if (mine.position.y - 32 <= Player.RightMachine.shoot[i].position.y - 16
							&&
							Player.RightMachine.shoot[i].position.y <= mine.position.y + 32
							)
						{
						

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

						if (mine.position.y - 32 <= Player.LeftMachine.shoot[i].position.y - 16
							&&
							Player.LeftMachine.shoot[i].position.y <= mine.position.y + 32
							)
						{
						

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

			if (boss.SpawnCount >= 2500)
			{
				boss.SpawnFlag = 1;
				Player.RightMachine.SpawnFlag = 1;
				Player.LeftMachine.SpawnFlag = 1;
			}

			if (boss.SpawnFlag >= 1)
			{
				
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
								if (!Novice::IsPlayingAudio(sound.playerhit))
								{
									Novice::PlayAudio(sound.playerhit, false, 1.0);
								}
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
								if (!Novice::IsPlayingAudio(sound.playerhit))
								{
									Novice::PlayAudio(sound.playerhit, false, 1.0);
								}
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
								if (!Novice::IsPlayingAudio(sound.playerhit))
								{
									Novice::PlayAudio(sound.playerhit, false, 1.0);
								}
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
			if (boss.HP <= 300)
			{
				//mine.SpawnFlag = 10;
				boss.circle.Flag = 1;
			}
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
				for (int i = 0; i < 100; i++)
				{
					if (boss.RightLaser[i].position.x <= Player.position.x + 32
						&&
						Player.position.x <= boss.RightLaser[i].position.x + 32
						)
					{


						if (boss.RightLaser[i].position.y <= Player.position.y + 32
							&&
							Player.position.y <= boss.RightLaser[i].position.y + 32
							)
						{

							if (LazerhitCLTflag == 0)
							{



								for (int i = 0; i < 1; i++)
								{
									Player.Hp--;
									if (!Novice::IsPlayingAudio(sound.playerhit))
									{
										Novice::PlayAudio(sound.playerhit, false, 1.0);
									}
								}
								LazerhitCLTflag = 1;
							}
						}
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
				for (int i = 0; i < 100; i++)
				{
					if (boss.LeftLaser[i].position.x <= Player.position.x + 32
						&&
						Player.position.x <= boss.LeftLaser[i].position.x + 32
						)
					{


						if (boss.LeftLaser[i].position.y <= Player.position.y + 32
							&&
							Player.position.y <= boss.LeftLaser[i].position.y + 32
							)
						{


							if (LazerhitCLTflag == 0)
							{



								for (int i = 0; i < 1; i++)
								{
									Player.Hp--;
									if (!Novice::IsPlayingAudio(sound.playerhit))
									{
										Novice::PlayAudio(sound.playerhit, false, 1.0);
									}
								}
								LazerhitCLTflag = 1;
							}


						}
					}
				}

			}
			if (boss.LeftLaserFlag == 2 && boss.RightLaserFlag == 2)
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



			if (LazerhitCLTflag == 1)
			{
				LazerhitCLT++;
				if (LazerhitCLT >= 60)
				{
					LazerhitCLTflag = 0;
					LazerhitCLT = 0;

				}

			}
			if (boss.circle.Flag==1)
			{
				for (int i = 0; i < 32; i++)
				{
					if (boss.circle.attack[i].position.x <= Player.position.x + 32
						&&
						Player.position.x <= boss.circle.attack[i].position.x + 32
						)
					{


						if (boss.circle.attack[i].position.y <= Player.position.y + 32
							&&
							Player.position.y <= boss.circle.attack[i].position.y + 32
							)
						{



							if (LazerhitCLTflag == 0)
							{



								for (int i = 0; i < 1; i++)
								{
									Player.Hp--;
									if (!Novice::IsPlayingAudio(sound.playerhit))
									{
										Novice::PlayAudio(sound.playerhit, false, 1.0);
									}
								}
								LazerhitCLTflag = 1;

							}
						}
					}
				}
				boss.circle.timer++;
				if (boss.circle.timer>=0&& boss.circle.timer <= 60)
				{
					boss.circle.ModeChange = 0;
				}
				if (boss.circle.timer >= 61 && boss.circle.timer <= 120)
				{
					boss.circle.ModeChange = 1;
				}
				if (boss.circle.timer >= 121 && boss.circle.timer <= 240)
				{
					boss.circle.ModeChange = 2;
					for (int i = 16; i < 32; i++)
					{
						WASDPush(boss.circle.thetaMove2, boss.circle.move2[i].x, boss.circle.move2[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.y += boss.circle.move2[i].y;

					}
					for (int i = 0; i < 16; i++)
					{
						WASDPush(boss.circle.thetaMove1, boss.circle.move2[i].x, boss.circle.move2[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.y += boss.circle.move2[i].y;

					}
				}
				if (boss.circle.timer >= 241 && boss.circle.timer <= 360)
				{
					boss.circle.ModeChange = 3;
					for (int i = 16; i < 32; i++)
					{
						WASDPush(boss.circle.thetaMove1, boss.circle.move2[i].x, boss.circle.move2[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.y += boss.circle.move2[i].y;

					}
					for (int i = 0; i < 16; i++)
					{
						WASDPush(boss.circle.thetaMove2, boss.circle.move2[i].x, boss.circle.move2[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.y += boss.circle.move2[i].y;

					}
				}
				if (boss.circle.timer>=360)
				{
					boss.circle.timer = 121;
				}

				if (boss.circle.ModeChange == 0)
				{


					for (int i = 0; i < 8; i++)
					{
						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x += boss.circle.move[i].x;
						boss.circle.attack[i].position.y += boss.circle.move[i].y;

					}
				
					for (int i = 16; i < 24; i++)
					{
						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x += boss.circle.move[i].x;
						boss.circle.attack[i].position.y += boss.circle.move[i].y;

					}

					for (int i = 8; i < 16; i++)
					{

						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x += boss.circle.move[i].x;
						boss.circle.attack[i].position.y += boss.circle.move[i].y;



					}

					for (int i = 24; i < 32; i++)
					{

						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x += boss.circle.move[i].x;
						boss.circle.attack[i].position.y += boss.circle.move[i].y;



					}
				}
				if (boss.circle.ModeChange == 2)
				{

					for (int i = 0; i < 8; i++)
					{
						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x += boss.circle.move[i].x;
						boss.circle.attack[i].position.y += boss.circle.move[i].y;

					}

					for (int i = 16; i < 24; i++)
					{
						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x += boss.circle.move[i].x;
						boss.circle.attack[i].position.y += boss.circle.move[i].y;

					}
					for (int i = 8; i < 16; i++)
					{

						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x -= boss.circle.move[i].x;
						boss.circle.attack[i].position.y -= boss.circle.move[i].y;



					}

					for (int i = 24; i < 32; i++)
					{

						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x -= boss.circle.move[i].x;
						boss.circle.attack[i].position.y -= boss.circle.move[i].y;



					}
				}
				if (boss.circle.ModeChange==3)
				{
					for (int i = 0; i < 8; i++)
					{
						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x -= boss.circle.move[i].x;
						boss.circle.attack[i].position.y -= boss.circle.move[i].y;

					}

					for (int i = 16; i < 24; i++)
					{
						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x -= boss.circle.move[i].x;
						boss.circle.attack[i].position.y -= boss.circle.move[i].y;

					}
					
					for (int i = 8; i < 16; i++)
					{
			
						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x += boss.circle.move[i].x;
						boss.circle.attack[i].position.y += boss.circle.move[i].y;



					}
				
					for (int i = 24; i < 32; i++)
					{

						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x += boss.circle.move[i].x;
						boss.circle.attack[i].position.y += boss.circle.move[i].y;



					}
				
				}
			
				if (boss.circle.ModeChange==1)
				{
					for (int i = 0; i < 24; i++)
					{
						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

					}




					for (int i = 0; i < 8; i++)
					{
						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x -= boss.circle.move[i].x;
						boss.circle.attack[i].position.y -= boss.circle.move[i].y;

					}

					for (int i = 16; i < 24; i++)
					{
						WASDPush(boss.circle.theta[i], boss.circle.move[i].x, boss.circle.move[i].y, boss.circle.speed.x);

						boss.circle.attack[i].position.x -= boss.circle.move[i].x;
						boss.circle.attack[i].position.y -= boss.circle.move[i].y;

					}
				}

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
				if (!Novice::IsPlayingAudio(sound.over))
				{
					Novice::PlayAudio(sound.over, false, 1.0);
				}

			}
			if (boss.HP<=0)
			{
				game = clear;
				if (!Novice::IsPlayingAudio(sound.clear))
				{
					Novice::PlayAudio(sound.clear, false, 1.0);
				}
			}




			//描画処理

			Sprite4Fanction(Player.FlameCount, 60, Player.Flame, 0, 15, 30, 45);

			Sprite4Fanction(boss.Flamecount, 60, boss.Flame, 0, 15, 30, 45);






			break;
		case clear:
			Player.barrier1.position = { 0, 0 };
			Player.barrier2.position = { 0, 0 };
			Player.barrier3.position = { 0, 0 };
			Player.barrier4.position = { 0, 0 };

			

			LazerhitCLTflag = 0;
			LazerhitCLT = 0;
			for (int i = 0; i < 100; i++)
			{
				Player.shoot[i].position = { -200,-50 };
				Player.LeftMachine.shoot[i].position = { -200,-50 };
				Player.RightMachine.shoot[i].position = { -200,-50 };


			}
			for (int i = 0; i < 16; i++)
			{
				mine.bullet[i].position = { -900,-50 };
				mine.bullet[i].isShoot = 0;
			}
			Player.RightMachine.SpawnFlag = 0;
			Player.LeftMachine.SpawnFlag = 0;
			if (keys[DIK_SPACE]&&preKeys[DIK_SPACE]==0)
			{
				game = title;
				if (!Novice::IsPlayingAudio(sound.Select))
				{
					Novice::PlayAudio(sound.Select, false, 1.0);
				}
			}
			break;
		case over:

			LazerhitCLTflag = 0;
			LazerhitCLT = 0;


			for (int i = 0; i < 100; i++)
			{
				Player.shoot[i].position = { -200,-50 };
				Player.LeftMachine.shoot[i].position = { -200,-50 };
				Player.RightMachine.shoot[i].position = { -200,-50 };


			}

				 for (int i = 0; i < 16; i++)
				 {
					 mine.bullet[i].position = { -900,-50 };
					 mine.bullet[i].isShoot = 0;
				 }
				 Player.RightMachine.SpawnFlag = 0;
				 Player.LeftMachine.SpawnFlag = 0;
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
		{

			game = title;
			if (!Novice::IsPlayingAudio(sound.Select))
			{
				Novice::PlayAudio(sound.Select, false, 1.0);
			}
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

//	Novice::ScreenPrintf(0, 0, "fjaihfh" );
	Novice::DrawSprite(0, 0, tex.SelectBack, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(0, 0, tex.titlename, 1, 1, 0.0f, WHITE);
	break;

case home:
	Novice::DrawSprite(0, 0, tex.SelectBack, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(355, 200, tex.tutorial, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(355, 450, tex.Play, 1, 1, 0.0f, WHITE);
	if (GameCount==0)
	{
	
		Novice::DrawSprite(250, 180, tex.selectMark, 3, 3, 0.0f, WHITE);
			
		
		
		Novice::DrawSprite(355, 200, tex.tutorialSelect,1,1,0.0f,WHITE);

	}

	if (GameCount == 1)
	{
		Novice::DrawSprite(250, 430, tex.selectMark, 3, 3, 0.0f, WHITE);
		Novice::DrawSprite(355, 450, tex.PlaySelect, 1, 1, 0.0f, WHITE);

	}


	break;

case tutorial:

	Novice::DrawSprite(0, 0, tex.TutorialSelectPlay, 1, 1, 0.0f, WHITE);

	break;

case play:

	Novice::DrawSprite(scroll.FrontPosition.x, scroll.FrontPosition.y, tex.starback, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(scroll.BackPosition.x, scroll.BackPosition.y, tex.starback, 1, 1, 0.0f, WHITE);
	//Novice::ScreenPrintf(0, 40, "%d", boss.SpawnCount);



	
	if (Player.RightMachine.SpawnFlag == 1)
	{

		Novice::DrawSprite(
			Player.RightMachine.position.x,
			Player.RightMachine.position.y,
			tex.PlayerRiLe, 1, 1, 0.0f, WHITE


		);
	}
	if (Player.LeftMachine.SpawnFlag == 1)
	{


		Novice::DrawSprite(
			Player.LeftMachine.position.x,
			Player.LeftMachine.position.y,
			tex.PlayerRiLe, 1, 1, 0.0f, WHITE


		);
	}
	//地雷　
	if (mine.SpawnFlag == 1)
	{
		Novice::DrawSprite(mine.position.x, mine.position.y, tex.Mine, 1, 1, 0.0f, WHITE);

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
		



		Novice::DrawSprite(
			Player.barrier1.position.x-8, Player.barrier1.position.y-8,
			tex.playerHP, 1, 1, 0.0f, WHITE
		);
	}

	if (Player.barrier2.Flag == 1)
	{		
		Novice::DrawSprite(
			Player.barrier2.position.x-8, Player.barrier2.position.y-8,
			tex.playerHP, 1, 1, 0.0f, WHITE
		);
	}

	if (Player.barrier4.Flag == 1)
	{

		Novice::DrawSprite(
			Player.barrier4.position.x-8, Player.barrier4.position.y-8,
			tex.playerHP, 1, 1, 0.0f, WHITE
		);
	}

	if (Player.barrier3.Flag == 1)
	{

		Novice::DrawSprite(
			Player.barrier3.position.x-8, Player.barrier3.position.y-8,
			tex.playerHP, 1, 1, 0.0f, WHITE
		);
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
		
	}
	if (isenemyAlive == 2)
	{
		Tex4Sprite(zakoriactionFrame, zako.position.x, zako.position.y, 0, 0, 65, 0, 130, 0, 195, 0,
			tex.Explosion, 64, 0.25, 1, 0.0f
		);
	}



	if (boss.SpawnFlag >= 1)
	{
		if (boss.circle.Flag == 1)
		{
			for (int i = 0; i < 32; i++)
			{
				Novice::DrawSprite(
					boss.circle.attack[i].position.x - 16,
					boss.circle.attack[i].position.y - 16,
					tex.MineBullet,
					1, 1, 0.0f, WHITE


				);
			}



		}

		Novice::DrawSprite(boss.position.x - 32, boss.position.y - 38, tex.playerHP, 1, 1, 0.0f, WHITE);


		Novice::DrawQuad(
			boss.position.x+boss.HP , boss.position.y-38,
			boss.position.x, boss.position.y - 38,
			boss.position.x+boss.HP, boss.position.y - 24,
			boss.position.x, boss.position.y - 24,
			
			0, 0,
			32, 16,
			tex.BossHP,
			WHITE
		);

		for (int i = 0; i < 100; i++)
		{
			if (boss.MainShoot[i].isShoot == 1)
			{

				//Novice::DrawBox(boss.MainShoot[i].position.x, boss.MainShoot[i].position.y, 32, 32, 0.0f, RED, kFillModeSolid);
				Tex4Sprite(boss.Flame,
					boss.MainShoot[i].position.x, boss.MainShoot[i].position.y,
					0, 0,
					33, 0,
					65, 0,
					97, 0,
					tex.BossBullet,
					32, 0.25, 1, 0.0f);

			}
			if (boss.RightShoot[i].isShoot == 1)
			{

				//Novice::DrawBox(boss.RightShoot[i].position.x, boss.RightShoot[i].position.y, 32, 32, 0.0f, RED, kFillModeSolid);
				Tex4Sprite(boss.Flame,
					boss.RightShoot[i].position.x, boss.RightShoot[i].position.y,
					0, 0,
					33, 0,
					65, 0,
					97, 0,
					tex.BossBullet,
					32, 0.25, 1, 0.0f);
			}
			if (boss.LeftShoot[i].isShoot == 1)
			{

				//Novice::DrawBox(boss.LeftShoot[i].position.x, boss.LeftShoot[i].position.y, 32, 32, 0.0f, RED, kFillModeSolid);
				Tex4Sprite(boss.Flame,
					boss.LeftShoot[i].position.x, boss.LeftShoot[i].position.y,
					0, 0,
					33, 0,
					65, 0,
					97, 0,
					tex.BossBullet,
					32, 0.25, 1, 0.0f);
			}
		}
		Tex4Sprite(boss.Flame, boss.position.x, boss.position.y, 0, 0, 96, 0, 193, 0, 288, 0,
			tex.Boss, 96, 0.25, 1, 0.0f
		);
	}
	if (boss.RightLaserFlag == 1)
	{

		for (int i = 0; i < 100; i++)
		{
			if (boss.RightLaser[i].isShoot == 1)
			{

				//Novice::DrawBox(boss.RightLaser[i].position.x, boss.RightLaser[i].position.y, 32, 32, 0.0f, GREEN, kFillModeSolid);
				Novice::DrawSprite(boss.RightLaser[i].position.x, boss.RightLaser[i].position.y, tex.lazerBullet,
					1, 1, 0.0f, WHITE);
			}
		}
	}
	if (boss.LeftLaserFlag == 1)
	{

		for (int i = 0; i < 100; i++)
		{
			if (boss.LeftLaser[i].isShoot == 1)
			{

				//Novice::DrawBox(boss.LeftLaser[i].position.x, boss.LeftLaser[i].position.y, 32, 32, 0.0f, GREEN, kFillModeSolid);
				Novice::DrawSprite(boss.LeftLaser[i].position.x, boss.LeftLaser[i].position.y, tex.lazerBullet,
					1, 1, 0.0f, WHITE);
			}
		}
	}
	if (boss.circle.Flag==1)
	{
		for ( int i = 0; i <32; i++)
		{
			Novice::DrawSprite(
				boss.circle.attack[i].position.x - 16,
				boss.circle.attack[i].position.y - 16,
				tex.MineBullet,
				1, 1, 0.0f, WHITE


			);
		}



	}



	Tex4Sprite(Player.Flame,
		Player.position.x,
		Player.position.y,
		0, 0,
		32, 0,
		64, 0,
		96, 0,
		tex.Player,
		32, 0.25, 1, 0.0f);

	
	break;
	case over:
		Novice::DrawSprite(0, 0, tex.gameover, 1, 1, 0.0f, WHITE);

		break;

	case clear:
		Novice::DrawSprite(0, 0, tex.gameclear, 1, 1, 0.0f, WHITE);
		break;


default:
	break;

}


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
