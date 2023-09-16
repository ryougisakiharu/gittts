#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <graphics.h>
#include <winresrc.h>
#include <math.h>
#include <cfloat>
#include <chrono>

#define WIDTH 1024//չʾ��Ļ��С
#define HEIGHT 648
#define FOOD_NUM 2046
#define DEBUFF_NUM 10
#define MAP_WIDTH (WIDTH*2)//ʵ�ʵ�ͼ��С
#define MAP_HEIGHT (HEIGHT *2)
#define ENEMY_NUM 9//��Ϊ�������⣬���ɶ��ڣ���������

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
	"996",//Ŀǰ��֧������
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

void CreateFood(int i)//����ʳ��
{
	food[i].x = rand() % MAP_WIDTH;
	food[i].y = rand() % MAP_HEIGHT;
	food[i].r = 3;//�ؼ�
	food[i].eatGrade = 2;//�ؼ�
	food[i].flag = true;
	food[i].color = RGB(156, 56, 56);
}
void CreateDebuff(int i)//����DEBUFF
{
	debuff[i].x = rand() % MAP_WIDTH;
	debuff[i].y = rand() % MAP_HEIGHT;
	debuff[i].r = 25;//�ؼ�
	debuff[i].eatGrade = 2;//�ؼ�
	debuff[i].flag = true;
	debuff[i].color = RGB(256, 256, 256);
}
void InitializeGame()//��ʼ����Ϸ
{
	srand(time(NULL));
	player.x = rand() % MAP_WIDTH;//���
	player.y = rand() % MAP_HEIGHT;
	player.eatGrade = 100;
	player.r = sqrt(player.eatGrade);
	player.flag = true;

	for (int i = 0; i < FOOD_NUM; i++)//����ʳ��
	{
		CreateFood(i);
	}

	for (int i = 0; i < DEBUFF_NUM; i++)//����debuff
	{
		CreateDebuff(i);
	}



	for (int i = 0; i < ENEMY_NUM; i++)//�������
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
		// Ϊ���˷�������
		strcpy(enemies[i].name, enemyNames[i]);

		// �����ĵ��˳�ʼ���߼�...
	}
}
//����ƶ�
void MovePlayer(Ball& ball, int speed)
{
	int radiusFactor = static_cast<int>(sqrt(sqrt(ball.r))); //�ð뾶��ƽ������ƽ����
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
//������Ϸ����
void DrawGame()
{
	// ���û�ͼ����Ϊ��ͼ
	SetWorkingImage(&map);
	setbkcolor(WHITE);
	cleardevice();

	// ����������
	setlinecolor(RGB(230, 231, 239));
	for (int i = 0; i < MAP_WIDTH; i += 10)
	{
		line(i, 0, i, MAP_HEIGHT);
		line(0, i, MAP_WIDTH, i);
	}

	// ����ʳ��
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (!food[i].flag)
			continue;
		setfillcolor(food[i].color);
		solidcircle(food[i].x, food[i].y, food[i].r);
	}
	// ����debuff
	for (int i = 0; i < DEBUFF_NUM; i++)
	{
		if (!debuff[i].flag)
			continue;
		setfillcolor(debuff[i].color);
		solidcircle(debuff[i].x, debuff[i].y, debuff[i].r);
	}

	// �����������
	setfillcolor(RGB(66, 204, 255));
	solidcircle(player.x, player.y, player.r);
	// ��������д�������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	char player_name[100];
	sprintf(player_name, "%s", "player");

	for (int j = 0; player_name[j] != '\0'; j++)
	{
		outtextxy(player.x - player.r + j * 8, player.y, player_name[j]);
	}

	//���Ƶ���
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!enemies[i].flag)
			continue;
		setfillcolor(enemies[i].color);
		solidcircle(enemies[i].x, enemies[i].y, enemies[i].r);
	}
	// ��������д��������
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

	//�������λ��
	g_cameraPos.x = player.x - WIDTH / 2;
	g_cameraPos.y = player.y - HEIGHT / 2;
	// ȷ�����λ�ò�������ͼ�߽�
	if (g_cameraPos.x < 0)
		g_cameraPos.x = 0;
	if (g_cameraPos.y < 0)
		g_cameraPos.y = 0;
	if (g_cameraPos.x > MAP_WIDTH - WIDTH)
		g_cameraPos.x = MAP_WIDTH - WIDTH;
	if (g_cameraPos.y > MAP_HEIGHT - HEIGHT)
		g_cameraPos.y = MAP_HEIGHT - HEIGHT;
}

// ������������֮��ľ���
double Distance(Ball* b1, Ball* b2)
{
	return sqrt((b1->x - b2->x) * (b1->x - b2->x) + (b1->y - b2->y) * (b1->y - b2->y));
}

// ��ҳ�ʳ��
void PlayerEatFood()
{
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag && Distance(&food[i], &player) < player.r)
		{
			food[i].flag = false;

			player.eatGrade += food[i].r * food[i].r;
			player.r = sqrt(player.eatGrade);
			CreateFood(i);//ʹʳ��һֱ����
		}
	}
}

// ��ҳ�debuff
void PlayerEatDebuff()
{
	for (int i = 0; i < DEBUFF_NUM; i++)
	{
		if (debuff[i].flag && Distance(&debuff[i], &player) < player.r&&debuff[i].r<player.r)
		{
			debuff[i].flag = false;

			player.eatGrade = 0.5*player.eatGrade+100;
			player.r = sqrt(player.eatGrade);
			
			CreateDebuff(i);//ʹdebuffһֱ����
		}
	}
}





// ��ҳԵ���
void PlayerEatEnemies()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemies[i].flag && Distance(&enemies[i], &player) < player.r && player.r > enemies[i].r)
		{
			enemies[i].flag = false;

			player.eatGrade += enemies[i].r * enemies[i].r;
			player.r = sqrt(player.eatGrade);
			// ���õ���״̬
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
			// �������״̬
			player.flag = true;
			player.eatGrade = 0.1 * player.eatGrade+100;
			player.r = sqrt(player.eatGrade);
			player.x = rand() % MAP_WIDTH;
			player.y = rand() % MAP_HEIGHT;


		}


	}
}
//��������˻���
void EnemiesEatEnemies()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//i��j
		for (int j = 0; j < ENEMY_NUM; j++)
		if (enemies[i].flag && enemies[j].flag && Distance(&enemies[i], &enemies[j]) < enemies[i].r && enemies[j].r < enemies[i].r)
		{
			enemies[j].flag = false;

			enemies[i].eatGrade += enemies[j].r * enemies[j].r;
			enemies[i ].r = sqrt(enemies[i].eatGrade);
			// ���õ���״̬
			enemies[j].flag = true;
			enemies[j].eatGrade = 0.5 * enemies[j].eatGrade;
			enemies[j].r = sqrt(enemies[j].eatGrade);
			enemies[j].x = rand() % MAP_WIDTH;
			enemies[j].y = rand() % MAP_HEIGHT;


		}
		

	}
}


// ���˳�ʳ��
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
// ���˳�debuff
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

//�����ƶ�
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



//��ʾ�÷�
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
	TCHAR s[] = _T("player");//�������
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
	// ��ʼ��ͼ�ν���
	initgraph(WIDTH, HEIGHT);
	// ��ʼ����Ϸ
	InitializeGame();
	// ��ʼ��������
	BeginBatchDraw();
	auto startTime = std::chrono::steady_clock::now(); // ��¼��Ϸ��ʼʱ��


	while (true)
	{
		DrawGame();// ������Ϸ����
		MovePlayer(player, 11);// �ƶ���ң���һ����ٶ�
		PlayerEatFood();// ��ҳ�ʳ��
		PlayerEatDebuff();
		PlayerEatEnemies();
		
		EnemiesEatEnemies();

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			MoveEnemy(enemies[i], 8);//����
			EnemyEatFood(enemies[i]);
			EnemyEatDebuff(enemies[i]);

		}

		auto currentTime = std::chrono::steady_clock::now(); // ��ȡ��ǰʱ��
		auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count(); // ������Ϸ������ʱ�䣨�룩
		if (elapsedTime >= 2)//1��
		{
			
			
			player.eatGrade = 0.99* player.eatGrade;
			player.r = sqrt(player.eatGrade);

			for (int i = 0; i < ENEMY_NUM; i++)
			{
				
				enemies[i].eatGrade = 0.99* enemies[i].eatGrade;
				enemies[i].r = sqrt (enemies[i].eatGrade); // ���˰뾶����
				
			}


			
			
			startTime = currentTime; // ���¿�ʼʱ��
		}


		ShowEnemyGrade(enemies[1]);  // ��ʾ���˵÷ֺ�����

		ShowGrade(player);// ��ʾ�÷�



		FlushBatchDraw();// ˢ�»���
		Sleep(50);// ��΢�ӳ�
		if (GetAsyncKeyState(VK_ESCAPE))
			break;

	}
	int highestScore = player.eatGrade;  // ��ʼ����ߵ÷�Ϊ��ҵĵ÷�
	int firstPlaceIndex = -1;  // ��һ����������Ĭ��Ϊ��Ч����

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
		firstPlaceIndex = -1;  // ��һ������ң�������Ϊ��Ч
	}

	if (firstPlaceIndex == -1)
		printf("��һ����player �÷֣�%d\n", highestScore);
	else
		printf("��һ����%s �÷֣�%d\n", enemies[firstPlaceIndex].name, highestScore);
	// �ر�ͼ�ν���
	closegraph();
	return 0;
	

}