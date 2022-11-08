#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<player.h>

const char kWindowTitle[] = "学籍番号";
struct Vector2
{
	float x;
	float y;
};

struct HitBox
{
	Vector2 LeTo;
	Vector2 RiTo;
	Vector2 LeBo;
	Vector2 RiBo;

};

struct MACHINE
{
	Vector2 position;
	float speed;

	int Flag;

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
};
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	PLAYER Player
	{
		{0,0},
		{0,0},
		5,
		32,
		WHITE,
		{0,0},

		0.0f,

		{{0,0},{0,0},{0,0}, {0,0}},


		{{0,0},7,0},
		{{0,0},7,0},

		{ {0,0},4,0,{0,0}, 0.0f,32, 1.0f / 64.0f * float(M_PI) },
		{ {0,0},4,0,{0,0}, 1.5875f,32, 1.0f / 64.0f * float(M_PI) },
		{ {0,0},4,0,{0,0}, 3.175f,32, 1.0f / 64.0f * float(M_PI) },
		{ {0,0},4,0,{0,0}, 4.7625f,32, 1.0f / 64.0f * float(M_PI) }
	};

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

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
		Novice::ScreenPrintf(500, 0, "center %f  %f", Player.PosCenter.x, Player.PosCenter.y);
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






		if (keys[DIK_1])
		{
			Player.RightMachine.Flag = 1;
			Player.LeftMachine.Flag = 1;
		}

		if (keys[DIK_2])
		{
			Player.barrier1.Flag = 1;
			Player.barrier2.Flag = 1;
			Player.barrier3.Flag = 1;
			Player.barrier4.Flag = 1;
		}

		if (Player.RightMachine.Flag == 1)
		{

			Player.RightMachine.position.x = Player.PosCenter.x + 70;
			Player.RightMachine.position.y = Player.PosCenter.y - 8;
		}

		if (Player.LeftMachine.Flag == 1)
		{

			Player.LeftMachine.position.x = Player.PosCenter.x - 102;
			Player.LeftMachine.position.y = Player.PosCenter.y - 8;



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
				Player.barrier4.position.x, Player.barrier4.position.y
				, 16, 16, 0.0f, RED,
				kFillModeSolid)
				;
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
			64, 64, 0.0f, WHITE, kFillModeSolid
		);

		Novice::DrawBox(
			Player.RightMachine.position.x,
			Player.RightMachine.position.y,
			32, 32, 0.0f, WHITE, kFillModeSolid
		);
		Novice::DrawBox(
			Player.LeftMachine.position.x,
			Player.LeftMachine.position.y,
			32, 32, 0.0f, WHITE, kFillModeSolid
		);


		Novice::DrawLine(Player.barrier1.position.x, Player.barrier1.position.y,
			Player.barrier3.position.x, Player.barrier3.position.y, WHITE
		);
		Novice::DrawLine(Player.barrier2.position.x, Player.barrier2.position.y,
			Player.barrier4.position.x, Player.barrier4.position.y, WHITE
		);

		Novice::DrawEllipse(Player.position.x + 32, Player.position.y + 32, 100, 100, 0.0f, WHITE, kFillModeWireFrame);





		Novice::DrawBox(10, 10, 10, 10, 0.0f, WHITE, kFillModeSolid);

		
		Novice::DrawBox(50, 50, 50, 50, 0.0f, WHITE, kFillModeSolid);
		Novice::DrawBox(10, 10, 10, 10, 0.0f, WHITE, kFillModeSolid);

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
