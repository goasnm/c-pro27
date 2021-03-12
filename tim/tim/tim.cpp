// 210310_tim용사.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
#include <Windows.h>

using namespace std;

struct Node
{
	char** forst;
	char** heroPoint;
	char** mPoint;
	int s = 0;
};

enum monster_totalHP { forestHP = 30, swampHP = 40, groudHP = 50 };
enum monster_Gold { forestGold = 30, swampGold = 60, groudGold = 80 };
enum monster_XP { forestXP = 30, swampXP = 50, groudXP = 70 };
enum monster_Icon { forestIcon = 'F', swampIcon = 'S', groudIcon = 'G' };
enum Battle_Results { Win = 1, Lose = 2, Draw = 3 };


struct HeroData
{
	string name;
	int level;
	int curHP;
	int maxHP;
	int playerX = 0;
	int playerY = 0;
	int XP = 0;
	int moveCnt = 0;
	int glod = 50;
	bool isAlive = true;
	char Icon = 'P';
};

struct MonData
{
	bool m_isAlive = true;
	int m_curHp;
	int m_totalHP;
	int monGold;
	int monXP;
	char monIcon;
	int m_Su;
	string mRps[3] = { "가위", "바위", "보" };

	
	
};

struct MapData
{
	string gameDifficulty;
	int width;
	int height;
	char mopIcon[3] = { '|','o','^' };
	char mapIcon = '0';
	monster_Icon mIcon;
};

struct SelectData
{
	int startHP[3] = { 100, 70, 50 };
	int monsterNum[3] = { 1, 3, 7 };
	int maze[3][2] = { {5,10},{10,15},{15,20} };
	int mCount = 0;
};

struct StoreData
{
	int recover[3] = { 10, 20, 30 };	//+전체회복
	int cost[4] = { 50, 75, 100, 150 };
	int remain[4] = { 5, 3, 2, 1 };
};

struct Save
{
	int posX=0;
	int posY=0;
};


//void setMap(MapData(*maze)[10]); //enum 쓰기위한 함수생성 *안됨
//
//void printMap(MonData(*maze)[10]);


int main()
{
	HeroData herodata;
	MonData mondata;
	MapData mapdata;
	SelectData selectdata;
	StoreData stordata;
	Node node;
	Save *save;

	srand(time(NULL));

	cout << "****플레이시 캐릭터가 안움직이면 한/영 키를 눌러주세요****" << endl;
	cout << endl;
	cout << "용사의 이름을 적어주세요. : " << endl;
	cin >> herodata.name;
	cout << endl;
	cout << "난이도를 선택해 주세요. : " << endl;
	cout << endl;
	cout << "쉬움, 보통 , 어려움" << endl;
	cout << endl;
	cin >> mapdata.gameDifficulty;
	cout << endl;
	

	// 난이도 설정
	while (1)
	{
		if (mapdata.gameDifficulty != "쉬움" && mapdata.gameDifficulty != "보통" && mapdata.gameDifficulty != "어려움")
		{
			cout << "잘못 입력 하셨습니다, 다시 입력 해 주세요." << endl;
			cout << endl;
			cout << "쉬움, 보통 , 어려움" << endl;
			cout << endl;
			cin >> mapdata.gameDifficulty;
			
		}
		else if (mapdata.gameDifficulty == "쉬움")
		{
			herodata.curHP = herodata.maxHP = selectdata.startHP[0];
			mondata.m_Su = selectdata.monsterNum[0];
			mapdata.height = selectdata.maze[0][0];
			mapdata.width = selectdata.maze[0][1];

			break;
		}
		else if (mapdata.gameDifficulty == "보통")
		{
			herodata.curHP = herodata.maxHP = selectdata.startHP[1];
			mondata.m_Su = selectdata.monsterNum[1];
			mapdata.height = selectdata.maze[1][0];
			mapdata.width = selectdata.maze[1][1];
			break;
		}
		else if (mapdata.gameDifficulty == "어려움")
		{
			herodata.curHP = herodata.maxHP = selectdata.startHP[2];
			mondata.m_Su = selectdata.monsterNum[2];
			mapdata.height = selectdata.maze[2][0];
			mapdata.width = selectdata.maze[2][1];
			break;
		}

		
	}


	
		//맵 입력
	system("cls");
	node.forst = new char* [mapdata.height];
	//save = new Save[100];
	for (int i = 0; i < mapdata.height; i++)
	{
		node.forst[i] = new char[mapdata.width];
		for (int j = 0; j < mapdata.width; j++)
		{
			int random = rand() % 3;
			node.forst[i][j] = mapdata.mopIcon[random];
			

			//cout << node.forst[i][j]; // 맵확인
		}
		//cout << endl;
	}

	// 맵에 몬스터 표현
	node.mPoint = new char* [mapdata.height];
	for (int i = 0; i < mapdata.height; i++)
	{
		node.mPoint[i] = new char[mapdata.width];
	}

	int mSpon = 0;

	for (int i = 0; i < mapdata.height; i++)
	{
		for (int j = 0; j < mapdata.width; j++)
		{
			if (mapdata.gameDifficulty.compare("쉬움") == 0)
			{
				
				while (selectdata.monsterNum[0] > mSpon)
				{
					int monsterY = rand() % mapdata.height;
					int monsterX = rand() % mapdata.width;

					while (monsterY == 0 && monsterX == 0)
					{
						monsterY = rand() % mapdata.height;
						monsterX = rand() % mapdata.width;
					}

					if (node.forst[monsterY][monsterY] == '|')
					{
						node.mPoint[monsterY][monsterX] = 'F';
						node.forst[monsterY][monsterX] = node.mPoint[monsterY][monsterX];
						mSpon++;
					}
				}

				break;


			}


			if (mapdata.gameDifficulty.compare("보통") == 0)
			{
				
				while (selectdata.monsterNum[1] > mSpon)
				{
					int monsterY = rand() % mapdata.height;
					int monsterX = rand() % mapdata.width;

					while (monsterY == 0 && monsterX == 0)
					{
						monsterY = rand() % mapdata.height;
						monsterX = rand() % mapdata.width;
					}

					if (node.forst[monsterY][monsterX] == '|')
					{
						node.mPoint[monsterY][monsterX] = 'F';
						node.forst[monsterY][monsterX] = node.mPoint[monsterY][monsterX];
					}
					else if (node.forst[monsterY][monsterX] == 'o')
					{
						node.mPoint[monsterY][monsterX] = 'S';
						node.forst[monsterY][monsterX] = node.mPoint[monsterY][monsterX];
						mSpon++;
					}
				}

				break;

			}


			if (mapdata.gameDifficulty.compare("어려움") == 0)
			{
				
				while (selectdata.monsterNum[2] > mSpon)
				{
					int monsterY = rand() % mapdata.height;
					int monsterX = rand() % mapdata.width;

					while (monsterY == 0 && monsterX == 0)
					{
						monsterY = rand() % mapdata.height;
						monsterX = rand() % mapdata.width;
					}

					if (node.forst[monsterY][monsterX] == '|')
					{
						node.mPoint[monsterY][monsterX] = 'F';
						node.forst[monsterY][monsterX] = node.mPoint[monsterY][monsterX];
					}
					else if (node.forst[monsterY][monsterX] == 'o')
					{
						node.mPoint[monsterY][monsterX] = 'S';
						node.forst[monsterY][monsterX] = node.mPoint[monsterY][monsterX];
					}
					else if (node.forst[monsterY][monsterX] == '^')
					{
						node.mPoint[monsterY][monsterX] = 'G';
						node.forst[monsterY][monsterX] = node.mPoint[monsterY][monsterX];
						mSpon++;
					}

				}

				break;

			}

		}
	}


	


	while (1)
	{
		system("cls");
		////맵 출력
		node.heroPoint = new char* [mapdata.height];
		for (int i = 0; i < mapdata.height; i++)
		{
			node.heroPoint[i] = new char[mapdata.width];
			for (int j = 0; j < mapdata.width; j++)
			{
				if (herodata.playerY == i && herodata.playerX == j)
					cout << herodata.Icon;

				else cout << (char)node.forst[i][j];

			}
			cout << endl;
		}

		cout << "---------------" << endl;
		cout << "용사 이름 " << herodata.name << endl;
		cout << "용사 hp : " << herodata.curHP << endl;
		cout << "소지 골드 : " << herodata.glod << endl;
		cout << "---------------" << endl;

		char inPut = _getch();

		switch (inPut)
		{

		case 'w': case 'W':
			herodata.playerY--;
			if (herodata.playerY < 0)
			{
				herodata.playerY = 0;
			}
			break;
		case's': case'S':
			herodata.playerY++;
			if (herodata.playerY >= mapdata.height)
			{
				herodata.playerY = mapdata.height-1;
			}
			break;
		case'a': case'A':
			herodata.playerX--;
			if (herodata.playerX < 0)
			{
				herodata.playerX = 0;
			}
			break;
		case'd':case'D':
			herodata.playerX++;
			if (herodata.playerX >= mapdata.width)
			{
				herodata.playerX = mapdata.width-1;
			}
			break;
		
		}
		if (node.forst[herodata.playerY][herodata.playerX] == 'F' || node.forst[herodata.playerY][herodata.playerX] == 'S' || node.forst[herodata.playerY][herodata.playerX] == 'G')
		{
			int win = 1, lose = 2, draw = 3;

			bool BattlePage = true;
			bool Store = false;
			system("cls");

			cout << "몬스터 등장 ! " << endl;

			while (BattlePage)
			{
				int BattlePage = 0;
				int randomRps = rand() % 3;
				string heroRps;

				cout << "몬 :" << mondata.mRps[randomRps] << endl;
				cout << endl;
				cout << "가위 , 바위 , 보 를 입력해주세요 :" << endl;
				cin >> heroRps;

				if (heroRps == "가위")
				{
					if (mondata.mRps[randomRps] == "바위")
						BattlePage = lose;
					else if (mondata.mRps[randomRps] == "보")
					{
						BattlePage = win;
						//break;
					}
					else if (mondata.mRps[randomRps] == "가위")
						BattlePage = draw;
				}
				else if (heroRps == "바위")
				{
					if (mondata.mRps[randomRps] == "바위")
						BattlePage = draw;
					else if (mondata.mRps[randomRps] == "보")
						BattlePage = lose;
					else if (mondata.mRps[randomRps] == "가위")
					{
						BattlePage = win;
						//break;
					}
				}
				else if (heroRps == "보")
				{
					if (mondata.mRps[randomRps] == "바위")
					{
						BattlePage = win;
						//break;
					}
					else if (mondata.mRps[randomRps] == "보")
						BattlePage = draw;
					else if (mondata.mRps[randomRps] == "가위")
						BattlePage = lose;
				}
				else
				{
					cout << "다시 입력 해 주세요." << endl;
				}
				

				switch (BattlePage)
				{
				case Battle_Results::Win:
					int dropGold;
					dropGold = rand() % 50;
					BattlePage = false;
					mondata.m_Su--;
					if (mondata.m_Su == 0)
					{
						cout << "던전 정복" << endl;
						
					}
					cout << " 승리 !  골드 : " << dropGold << " 획득" << endl;
					herodata.glod += dropGold;
					cout << "총 소지 골드 : " << herodata.glod << endl;
					cout << " 상점 이동 (1) , 상점 이동 안함 (2)" << endl;
					int goShop;
					cin >> goShop;
					if (goShop == 1)
					{
						Store = true;
						cout << "상점으로 이동 합니다.";
					}

					Sleep(1000);
					break;
					
				case Battle_Results::Lose:
				
					cout << "졌습니다. 영웅의 hp 가 10 만큼 감소 합니다." << endl;
					herodata.curHP -= 10;
				
				Sleep(1000);
					break;
				
				case Battle_Results::Draw:

					cout << "비겼습니다." << endl;

				Sleep(1000);
					break;
				
				default:
					break;
				}
				break;
			}


		}
	}
	




}





//if(player.playerXline == mob[i].mobXline && player.playerYline == mob[i].mobYline && mob[i].isAlive == true)
/*
MonData mon[3]
mon[0].

		node.outLine = new char* [mapdata.height];
		for (int k=0; k==0; k++)
		{
			node.outLine[k] = new char[mapdata.width];
			for(int h=0; h==11; h++)
			{
				node.outLine[k][h] = mapdata.mapIcon;
				cout << node.outLine[k][h];
			}

		}

*/


