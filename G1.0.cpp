#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <graphics.h>
#include <winresrc.h>
#include <math.h>
#include <cfloat>
#include <chrono>

#define WIDTH 1024//展示屏幕大小
#define HEIGHT 648
#define FOOD_NUM 2046
#define DEBUFF_NUM 10
#define MAP_WIDTH (WIDTH*2)//实际地图大小
#define MAP_HEIGHT (HEIGHT *2)
#define ENEMY_NUM 9//因为名字问题，不可多于，不可少于

IMAGE map(MAP_WIDTH, MAP_HEIGHT);
POINT g_cameraPos;

struct Ball
{
	int x;
	int y;
	int r;
	bool flag;
	COLORREF color;
	DWORD eatGrade;
};

struct Enemy : Ball
{
	char name[100];
};

const char* enemyNames[ENEMY_NUM] = {
	"996",//目前不支持中文
	"Enemy 2",
	"Enemy 3",
	"Enemy 4",
	"Enemy 5",
	"Enemy 6",
	"Enemy 7",
	"Enemy 8",
	"Enemy 9",
  /*"Enemy 10",
	"Enemy 11",
	"Enemy 12",
	"Enemy 13",
	"Enemy 14",
	"Enemy 15",
	"Enemy 16",
	"Enemy 17",
	"Enemy 18",
	"Enemy 19",
	*/
};

Ball player;
Ball food[FOOD_NUM];
Ball debuff[DEBUFF_NUM];
Enemy enemies[ENEMY_NUM];

void CreateFood(int i)//创建食物
{
	food[i].x = rand() % MAP_WIDTH;
	food[i].y = rand() % MAP_HEIGHT;
	food[i].r = 3;//关键
	food[i].eatGrade = 2;//关键
	food[i].flag = true;
	food[i].color = RGB(156, 56, 56);
}
void CreateDebuff(int i)//创建DEBUFF
{
	debuff[i].x = rand() % MAP_WIDTH;
	debuff[i].y = rand() % MAP_HEIGHT;
	debuff[i].r = 25;//关键
	debuff[i].eatGrade = 2;//关键
	debuff[i].flag = true;
	debuff[i].color = RGB(256, 256, 256);
}
void InitializeGame()//初始化游戏
{
	srand(time(NULL));
	player.x = rand() % MAP_WIDTH;//玩家
	player.y = rand() % MAP_HEIGHT;
	player.eatGrade = 100;
	player.r = sqrt(player.eatGrade);
	player.flag = true;

	for (int i = 0; i < FOOD_NUM; i++)//生成食物
	{
		CreateFood(i);
	}

	for (int i = 0; i < DEBUFF_NUM; i++)//生成debuff
	{
		CreateDebuff(i);
	}



	for (int i = 0; i < ENEMY_NUM; i++)//定义敌人
	{
		enemies[i].x = rand() % MAP_WIDTH;
		enemies[i].y = rand() % MAP_HEIGHT;
		enemies[i].eatGrade = 100;
		enemies[i].r = sqrt(enemies[i].eatGrade);
		enemies[i].flag = true;
		enemies[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// 为敌人分配名字
		strcpy(enemies[i].name, enemyNames[i]);

		// 其他的敌人初始化逻辑...
	}
}
//玩家移动
void MovePlayer(Ball& ball, int speed)
{
	int radiusFactor = static_cast<int>(sqrt(sqrt(ball.r))); //用半径的平方根的平方根
	if (radiusFactor <= 0)
		radiusFactor = 1;

	if (GetAsyncKeyState(VK_UP))
	{
		ball.y -= speed / radiusFactor;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		ball.y += speed / radiusFactor;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		ball.x -= speed / radiusFactor;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		ball.x += speed / radiusFactor;
	}
}
//绘制游戏画面
void DrawGame()
{
	// 设置绘图区域为地图
	SetWorkingImage(&map);
	setbkcolor(WHITE);
	cleardevice();

	// 绘制网格线
	setlinecolor(RGB(230, 231, 239));
	for (int i = 0; i < MAP_WIDTH; i += 10)
	{
		line(i, 0, i, MAP_HEIGHT);
		line(0, i, MAP_WIDTH, i);
	}

	// 绘制食物
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (!food[i].flag)
			continue;
		setfillcolor(food[i].color);
		solidcircle(food[i].x, food[i].y, food[i].r);
	}
	// 绘制debuff
	for (int i = 0; i < DEBUFF_NUM; i++)
	{
		if (!debuff[i].flag)
			continue;
		setfillcolor(debuff[i].color);
		solidcircle(debuff[i].x, debuff[i].y, debuff[i].r);
	}

	// 绘制玩家球体
	setfillcolor(RGB(66, 204, 255));
	solidcircle(player.x, player.y, player.r);
	// 在球体上写玩家名字
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	char player_name[100];
	sprintf(player_name, "%s", "player");

	for (int j = 0; player_name[j] != '\0'; j++)
	{
		outtextxy(player.x - player.r + j * 8, player.y, player_name[j]);
	}

	//绘制敌人
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!enemies[i].flag)
			continue;
		setfillcolor(enemies[i].color);
		solidcircle(enemies[i].x, enemies[i].y, enemies[i].r);
	}
	// 在球体上写敌人名字
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		char name[100];
		sprintf(name, "%s", enemies[i].name);

		for (int j = 0; name[j] != '\0'; j++)
		{
			outtextxy(enemies[i].x - enemies[i].r + j * 8, enemies[i].y, name[j]);
		}
	}








	SetWorkingImage();
	putimage(0, 0, WIDTH, HEIGHT, &map, g_cameraPos.x, g_cameraPos.y);

	//更新相机位置
	g_cameraPos.x = player.x - WIDTH / 2;
	g_cameraPos.y = player.y - HEIGHT / 2;
	// 确保相机位置不超出地图边界
	if (g_cameraPos.x < 0)
		g_cameraPos.x = 0;
	if (g_cameraPos.y < 0)
		g_cameraPos.y = 0;
	if (g_cameraPos.x > MAP_WIDTH - WIDTH)
		g_cameraPos.x = MAP_WIDTH - WIDTH;
	if (g_cameraPos.y > MAP_HEIGHT - HEIGHT)
		g_cameraPos.y = MAP_HEIGHT - HEIGHT;
}

// 计算两个球体之间的距离
double Distance(Ball* b1, Ball* b2)
{
	return sqrt((b1->x - b2->x) * (b1->x - b2->x) + (b1->y - b2->y) * (b1->y - b2->y));
}

// 玩家吃食物
void PlayerEatFood()
{
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag && Distance(&food[i], &player) < player.r)
		{
			food[i].flag = false;

			player.eatGrade += food[i].r * food[i].r;
			player.r = sqrt(player.eatGrade);
			CreateFood(i);//使食物一直存在
		}
	}
}

// 玩家吃debuff
void PlayerEatDebuff()
{
	for (int i = 0; i < DEBUFF_NUM; i++)
	{
		if (debuff[i].flag && Distance(&debuff[i], &player) < player.r&&debuff[i].r<player.r)
		{
			debuff[i].flag = false;

			player.eatGrade = 0.5*player.eatGrade+100;
			player.r = sqrt(player.eatGrade);
			
			CreateDebuff(i);//使debuff一直存在
		}
	}
}





// 玩家吃敌人
void PlayerEatEnemies()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemies[i].flag && Distance(&enemies[i], &player) < player.r && player.r > enemies[i].r)
		{
			enemies[i].flag = false;

			player.eatGrade += enemies[i].r * enemies[i].r;
			player.r = sqrt(player.eatGrade);
			// 重置敌人状态
			enemies[i].flag = true;
			enemies[i].eatGrade = 0.1* enemies[i].eatGrade+100;
			enemies[i].r = sqrt(enemies[i].eatGrade);
			enemies[i].x = rand() % MAP_WIDTH;
			enemies[i].y = rand() % MAP_HEIGHT;


		}
		if (enemies[i].flag && Distance(&enemies[i], &player) < player.r && player.r < enemies[i].r)
		{
			player.flag = false;

			enemies[i].eatGrade += player.r * player.r;
			enemies[i].r = sqrt(enemies[i].eatGrade);
			// 重置玩家状态
			player.flag = true;
			player.eatGrade = 0.1 * player.eatGrade+100;
			player.r = sqrt(player.eatGrade);
			player.x = rand() % MAP_WIDTH;
			player.y = rand() % MAP_HEIGHT;


		}


	}
}
//敌人与敌人互吃
void EnemiesEatEnemies()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//i吃j
		for (int j = 0; j < ENEMY_NUM; j++)
		if (enemies[i].flag && enemies[j].flag && Distance(&enemies[i], &enemies[j]) < enemies[i].r && enemies[j].r < enemies[i].r)
		{
			enemies[j].flag = false;

			enemies[i].eatGrade += enemies[j].r * enemies[j].r;
			enemies[i ].r = sqrt(enemies[i].eatGrade);
			// 重置敌人状态
			enemies[j].flag = true;
			enemies[j].eatGrade = 0.5 * enemies[j].eatGrade;
			enemies[j].r = sqrt(enemies[j].eatGrade);
			enemies[j].x = rand() % MAP_WIDTH;
			enemies[j].y = rand() % MAP_HEIGHT;


		}
		

	}
}


// 敌人吃食物
void EnemyEatFood(Enemy& enemy)
{
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag && Distance(&food[i], &enemy) < enemy.r)
		{
			food[i].flag = false;

			enemy.eatGrade += food[i].r * food[i].r;
			enemy.r = sqrt(enemy.eatGrade);
			CreateFood(i);
		}
	}
}
// 敌人吃debuff
void EnemyEatDebuff(Enemy& enemy)
{
	for (int i = 0; i < DEBUFF_NUM; i++)
	{
		if (debuff[i].flag && Distance(&debuff[i], &enemy) < enemy.r && debuff[i].r < enemy.r)
		{
			debuff[i].flag = false;

			enemy.eatGrade = 0.5 * enemy.eatGrade+100;
			enemy.r = sqrt(enemy.eatGrade);
			CreateDebuff(i);
		}
	}
}

//敌人移动
void MoveEnemy(Enemy& enemy, int speed)
{
	double minDistance = DBL_MAX;
	int targetIndex = -1;

	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag)
		{
			double distance = Distance(&food[i], &enemy);
			if (distance < minDistance)
			{
				minDistance = distance;
				targetIndex = i;
			}
		}
	}

	if (targetIndex != -1)
	{
		int dx = food[targetIndex].x - enemy.x;
		int dy = food[targetIndex].y - enemy.y;

		double length = sqrt(dx * dx + dy * dy);
		if (length != 0)
		{
			dx = static_cast<int>(round(dx / length));
			dy = static_cast<int>(round(dy / length));
		}

		int radiusFactor = static_cast<int>(sqrt(sqrt(enemy.r)));
		if (radiusFactor <= 0)
			radiusFactor = 1;

		enemy.x += dx * (speed / radiusFactor);
		enemy.y += dy * (speed / radiusFactor);
	}
}



//显示得分
void ShowGrade(Ball& ball)
{
	char grade[100];
	sprintf(grade, "%d", ball.eatGrade);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTBLUE);
	for (int i = 0; grade[i] != '\0'; i++)
	{
		outtextxy(900 + i * 8, 20, grade[i]);
	}
	TCHAR s[] = _T("player");//玩家名字
	outtextxy(800, 20, s);

}
void ShowEnemyGrade(Enemy& enemy)
{

	setbkmode(TRANSPARENT);
	settextcolor(LIGHTBLUE);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		char grade[100];
		sprintf(grade, "%d", enemies[i].eatGrade);

		for (int j = 0; grade[j] != '\0'; j++)
		{
			outtextxy(900 + j * 8, 40 + i * 20, grade[j]);
		}
	}


	for (int i = 0; i < ENEMY_NUM; i++)
	{
		char name[100];
		sprintf(name, "%s", enemies[i].name);

		for (int j = 0; name[j] != '\0'; j++)
		{
			outtextxy(800 + j * 8, 40 + i * 20, name[j]);
		}
	}
}





int main()
{
	// 初始化图形界面
	initgraph(WIDTH, HEIGHT);
	// 初始化游戏
	InitializeGame();
	// 开始批量绘制
	BeginBatchDraw();
	auto startTime = std::chrono::steady_clock::now(); // 记录游戏开始时间


	while (true)
	{
		DrawGame();// 绘制游戏画面
		MovePlayer(player, 11);// 移动玩家，玩家基础速度
		PlayerEatFood();// 玩家吃食物
		PlayerEatDebuff();
		PlayerEatEnemies();
		
		EnemiesEatEnemies();

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			MoveEnemy(enemies[i], 8);//移速
			EnemyEatFood(enemies[i]);
			EnemyEatDebuff(enemies[i]);

		}

		auto currentTime = std::chrono::steady_clock::now(); // 获取当前时间
		auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count(); // 计算游戏经过的时间（秒）
		if (elapsedTime >= 2)//1秒
		{
			
			
			player.eatGrade = 0.99* player.eatGrade;
			player.r = sqrt(player.eatGrade);

			for (int i = 0; i < ENEMY_NUM; i++)
			{
				
				enemies[i].eatGrade = 0.99* enemies[i].eatGrade;
				enemies[i].r = sqrt (enemies[i].eatGrade); // 敌人半径减少
				
			}


			
			
			startTime = currentTime; // 更新开始时间
		}


		ShowEnemyGrade(enemies[1]);  // 显示敌人得分和名称

		ShowGrade(player);// 显示得分



		FlushBatchDraw();// 刷新绘制
		Sleep(50);// 稍微延迟
		if (GetAsyncKeyState(VK_ESCAPE))
			break;

	}
	int highestScore = player.eatGrade;  // 初始化最高得分为玩家的得分
	int firstPlaceIndex = -1;  // 第一名的索引，默认为无效索引

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemies[i].flag && enemies[i].eatGrade > highestScore)
		{
			highestScore = enemies[i].eatGrade;
			firstPlaceIndex = i;
		}
	}

	if (player.eatGrade > highestScore)
	{
		highestScore = player.eatGrade;
		firstPlaceIndex = -1;  // 第一名是玩家，索引设为无效
	}

	if (firstPlaceIndex == -1)
		printf("第一名：player 得分：%d\n", highestScore);
	else
		printf("第一名：%s 得分：%d\n", enemies[firstPlaceIndex].name, highestScore);
	// 关闭图形界面
	closegraph();
	return 0;
	

}