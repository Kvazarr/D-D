#pragma once
#include<iomanip>
#include<string>
#include<Windows.h>
#include<chrono>
#include<thread>
#include"GameObjects.h";

class Story
{
private:
	Hero hero;
	Weapon heroSword;
	Armor heroArmor;
	Shield heroShield;
	Spell easeHealing;
	Monster firstMonster;
	Weapon firstMonsterWeapon;
	Armor firstMonsterArmor;
	Gold gold;
	Diamonds diamonds;
public:
	Story(string name)
	{
		easeHealing = Spell();
		heroSword = Weapon("Steel sword", 10);
		heroArmor = Armor("Leather armor", 3, 4, 1, 1);
		heroShield = Shield("Iron shield", 30);
		hero = Hero(name, easeHealing, 1, 65, 10, 150, 10, 10, 10, 5, heroSword, heroArmor, heroShield);
		firstMonsterWeapon = Weapon("Rusty claymore", 7);
		firstMonsterArmor = Armor("Rusty elder armor", 1, 3, 0, 0);
		firstMonster = Monster("Living armor", easeHealing, 1, 40, 10, 110, 12, 6, 1, 14, firstMonsterWeapon, firstMonsterArmor, "Eternal life");
		outfitHero();
		try
		{
			hero.SetSpell(1);
			firstMonster.SetSpell(1);
		}
		catch (out_of_range& wrondIndex)
		{
			cout << wrondIndex.what() << endl;
		}
	}
	void outfitHero()
	{
		hero.SetDamage();
		hero.SetDefence();
		hero.SetLvl();
	}
	void Sleep(int seconds)
	{
		this_thread::sleep_for(chrono::seconds(seconds));
	}
	void CenterText(const string line)
	{
		int consoleWidth(0);
#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO coord;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coord);
		consoleWidth = coord.srWindow.Right - coord.srWindow.Left + 1;
#endif 
		int padding = (consoleWidth - static_cast<int>(line.length())) / 2;
		cout << setw(padding + line.length()) << line << endl;
	}
	void FirstFight()
	{
		string opponents1(hero.GetName());
		string opponenst2(firstMonster.GetName());
		string vs = " VS ";
		string line = opponents1 + vs + opponenst2;
		string action = "a)���������    b)����������    c)������������ ����������";
		char choice;
		system("cls");
		int countRounds(1);

		while (hero.IsAlive() && firstMonster.IsAlive())
		{
			CenterText(line);
			cout << endl;
			cout << "------------------------------------------------------- Round " << countRounds << " --------------------------------------------------------" << endl;
			cout << "LVL: " << hero.GetLvl() << setw(112) << "LVL: " << firstMonster.GetLvl() << endl;
			cout << "HP: " << hero.GetHP() << setw(109) << "HP: " << firstMonster.GetHP() << endl;
			cout << "Endurance: " << hero.GetEndurance() << setw(105) << "Endurance: " << firstMonster.GetEndurance() << endl<<endl;
			CenterText(action);
			cout << ">>> "; cin >> choice;
			cout << "\n\n";
			
			if (choice == 'a' || choice == 'A')
			{
				if (hero.GetEndurance() > 0)
				{
					firstMonster.WithdrawHP(hero.Attack());
					hero.SetEnduranceNegative();
				}
				else
				{
					cout << "Not enough stamina. Stamina is " << hero.GetEndurance() << ". You're missing a move" << endl;
				}
			}
			else if (choice == 'b' || choice == 'B')
			{
				hero.Defend();
				hero.SetEndurancePositive();
			}
			else if (choice == 'c' || choice == 'C')
			{
				if (hero.GetEndurance() > 1)
				{
					firstMonster.WithdrawHP(hero.AttackSpell());
					for (int i = 0; i < 2; i++)
					{
						hero.SetEnduranceNegative();
					}
				}
				else
				{
					cout << "Not enough stamina. Stamina is " << hero.GetEndurance() << ". You're missing a move" << endl;
				}
			}
			else
			{
				throw exception("�� ������� �������� ������� � �������� ��� � �����.");
			}
			if (firstMonster.IsAlive())
			{
				cout << "The enemy's move!" << endl;
				int temp(1 + rand() % 3);
				if (firstMonster.GetEndurance() == 0)
					temp = 2;
				if (firstMonster.GetEndurance() == 10)
					temp = 1;
				if (temp == 1)
				{
					hero.WithdrawHP(firstMonster.Attack());
					firstMonster.SetEnduranceNegative();
				}
				else if (temp == 2)
				{
					firstMonster.Defend();
					firstMonster.SetEndurancePositive();
				}
				else if (temp == 3)
				{
					if (firstMonster.GetEndurance() > 1)
					{
						hero.WithdrawHP(firstMonster.AttackSpell());
						for (int i = 0; i < 2; i++)
						{
							firstMonster.SetEnduranceNegative();
						}
					}
					else
					{
						cout << "Not enough stamina. Stamina is " << firstMonster.GetEndurance() << ". Opponent missing a move" << endl;
					}
				}
			}
			else
			{
				cout << "The monster has fallen." << endl;
				hero.UpMonsterSouls();
				hero.HeroLvlUp(1);
			}
			if (!hero.IsAlive())
			{
				throw runtime_error("YOU DIED!");
			}
			countRounds++;
		}
	}
	void InVillage()
	{
		while (true)
		{
			char sign;
			string line("a)����������    b)����� �����    c)�����    d)�������    e)�������");
			system("cls");
			cout << endl;
			CenterText("Village");
			cout << "\n\n";
			cout << setw(76) << "  ���1       ���2         ���3\n";
			cout << setw(74) << "   |          |            |\n";
			cout << setw(74) << "   |          |            |\n";
			cout << setw(76) << "������� --- ������� --- �������\n";
			cout << setw(74) << "   |          |            |\n";
			cout << setw(74) << "   |          |            |\n";
			cout << setw(76) << " �����     �������        ����\n";
			cout << "\n\n";
			CenterText(line);
			cout << ">>> "; cin >> sign;
			if (sign == 'a' || sign == 'A')
			{

			}
			else if (sign == 'b' || sign == 'B')
			{

			}
			else if (sign == 'c' || sign == 'C')
			{
				int time(0);
				system("cls");
				cout << endl;
				cout << "   ������ ��� � ������ ����� ����� ����� ������������, � ������ ����� ������� ����, �� �������� ��������� 2 ������� ������." << endl;
				cout << "   ������ ������� ��� � ������ �������� ��� �������������. � ������ ��������� � ���� ��������, �� ������ �����������  ����," << endl;
				cout << "   ������� ����� ����� ������������ � �������, ������. ������ � ������������� ����� ��� ��������, ��� ��� �������� ��������" << endl << endl;
				cout << "�� ������� ����� �� ������ ��������� � �����?>>>"; cin >> time;
				cout << endl;
				if (time <= hero.GetEndurance())
				{
					cout << "������ � ����� �� ������ " << time << " ������ ������� ����";
					if (time == 10)
					{
						cout << " � 1 ���������!" << endl;
						diamonds.DiamondsUpCount();
						cout << "                                    ";
						system("pause");
					}
					else
					{
						cout << endl<<endl;
						cout << "                                    ";
						system("pause");
					}
					gold.UpGoldCount(time);
					hero.AfterMine(time);
				}
				else
				{
					throw logic_error("� ��� �� ������� ��� ��� ������. �� ����� � ������� � ������� �� ������.");
				}
			}
			else if (sign == 'd' || sign == 'D')
			{
				
			}
			else if (sign == 'e' || sign == 'E')
			{
				hero.SetEndurance();
				system("cls");
				cout << "������������ ��������� �������������." << endl;
				Sleep(2);
			}
			else
			{
				throw exception("�� ���������� � ������� � ����. ");
			}
		}
	}
	void Priview();
	void Menu();
	void ActI();
};