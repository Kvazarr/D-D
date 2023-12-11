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
		heroSword = Weapon("�������� ���", 10);
		heroArmor = Armor("������������ �����", 3, 4, 1, 1);
		heroShield = Shield("�������� ���", 30);
		hero = Hero(name, easeHealing, 1, 65, 10, 150, 10, 10, 10, 5, heroSword, heroArmor, heroShield);
		firstMonsterWeapon = Weapon("�������� �����", 7);
		firstMonsterArmor = Armor("�������� ����������", 1, 3, 0, 0);
		firstMonster = Monster("��������", easeHealing, 1, 40, 10, 110, 12, 6, 1, 14, firstMonsterWeapon, firstMonsterArmor);
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
					firstMonster.PointsWithdrawHP(hero.GetHeroDamage());
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
					hero.AttackSpell();
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
				throw exception("�� ������� �������� ������� � �������� ������.");
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
					hero.PointsWithdrawHP(firstMonster.GetMonsterDamage());
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
						firstMonster.AttackSpell();
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
				Sleep(2);
				hero.SetDefence();
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
	void Fight(Monster& opponent)
	{
		hero.SetDamage();
		opponent.SetDamage();
		string opponents1(hero.GetName());
		string opponenst2(firstMonster.GetName());
		string vs = " VS ";
		string line = opponents1 + vs + opponenst2;
		string action = "a)���������    b)����������    c)������������ ����������";
		char choice;
		system("cls");
		int countRounds(1);

		while (hero.IsAlive() && opponent.IsAlive())
		{
			CenterText(line);
			cout << endl;
			cout << "------------------------------------------------------- Round " << countRounds << " --------------------------------------------------------" << endl;
			cout << "LVL: " << hero.GetLvl() << setw(112) << "LVL: " << opponent.GetLvl() << endl;
			cout << "HP: " << hero.GetHP() << setw(109) << "HP: " << opponent.GetHP() << endl;
			cout << "Endurance: " << hero.GetEndurance() << setw(105) << "Endurance: " << opponent.GetEndurance() << endl << endl;
			CenterText(action);
			cout << ">>> "; cin >> choice;
			cout << "\n\n";

			if (choice == 'a' || choice == 'A')
			{
				if (hero.GetEndurance() > 0)
				{
					opponent.PointsWithdrawHP(hero.GetHeroDamage());
					opponent.WithdrawHP(hero.Attack());
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
					if (hero.GetHeroHeal() < 0)
						hero.HealingSpell();
					else
					{
						opponent.PointsWithdrawHP(hero.GetHeroMagicDamage());
						opponent.WithdrawHP(hero.AttackSpell());
					}
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
				throw exception("�� ������� �������� ������� � �������� ������.");
			}
			if (opponent.IsAlive())
			{
				cout << "The enemy's move!" << endl;
				int temp(1 + rand() % 3);
				if (opponent.GetEndurance() == 0)
					temp = 2;
				if (opponent.GetEndurance() == 10)
					temp = 1;
				if (temp == 1)
				{
					hero.PointsWithdrawHP(opponent.GetMonsterDamage());
					hero.WithdrawHP(opponent.Attack());
					firstMonster.SetEnduranceNegative();
				}
				else if (temp == 2)
				{
					opponent.Defend();
					opponent.SetEndurancePositive();
				}
				else if (temp == 3)
				{
					if (opponent.GetEndurance() > 1)
					{
						if (opponent.GetMonsterHeal() < 0)
							opponent.HealingSpell();
						else
						{
							hero.PointsWithdrawHP(opponent.GetMonsterMagicDamage());
							opponent.WithdrawHP(opponent.AttackSpell());
						}
						for (int i = 0; i < 2; i++)
						{
							opponent.SetEnduranceNegative();
						}
					}
					else
					{
						cout << "Not enough stamina. Stamina is " << opponent.GetEndurance() << ". Opponent missing a move" << endl;
					}
				}
			}
			else
			{
				cout << "The monster has fallen." << endl;
				Sleep(2);
				hero.UpMonsterSouls();
				hero.HeroLvlUp(1);
				if (hero.GetMonsterSouls() >= 20)
					hero.DarkSoulUp();
			}
			if (!hero.IsAlive())
			{
				throw runtime_error("YOU DIED!");
			}
			hero.SetDefence();
			opponent.SetDefence();
			countRounds++;
		}
	}
	void InVillage()
	{
		while (hero.IsAlive())
		{
			char sign;
			string line("a)����������    b)����� �����    c)�����    d)�������    e)�������    f)���������    g)��������������");

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
				system("cls");
				cout << endl;
				cout << "    ������� ���������� ��� ������� ������, ���������� ���� ��� � ���������� ���������, ���� �������� ����� ������ �����" << endl;
				cout << "    ������� �����, ����������� ����������� �������. ��� �������, �����-�� ��������� � ���������,������ ��������� ������" << endl;
				cout << "    ������ � ���������� � ���� ������������� �����." << endl << endl;
				cout << "    ���� ������������ ����� ������ ��� ������, ���������� �� ������� �������, � ���� ������ ���������� �����  ��������� " << endl;
				cout << "    ��� ���������� ��������. � ����� �� ������ ������, ����������� � ��������� ����, ��������� ��������� ����. ��� ���� " << endl;
				cout << "    ��������� �����,  ������ �� ����� �� ���� ����� ����������� ����������� ��������, ������� ���������� ��� �  ������� " << endl;
				cout << "    �������� �����, ���������� ������ ����� ������������ ������" << endl;
				cout << endl;
				cout << "                                    ";
				system("pause");

				Spell bossSpell("Soul snatching", 0, 1090);
				Weapon bossSword("��������", 200);
				Armor bossArmor("����� ������", 60, 80, 20, 20);
				Boss boss("�������, ���� �������� �����", bossSpell, 30, 195, 10, 4500, 50, 50, 50, 45, bossSword, bossArmor);
				string opponents1(hero.GetName());
				string opponenst2(boss.GetName());
				string vs = " VS ";
				string line = opponents1 + vs + opponenst2;
				string action = "a)���������    b)����������    c)������������ ����������";
				char choice;
				system("cls");
				int countRounds(1);
				hero.SetDamage();
				boss.SetDamage();

				while (hero.IsAlive() && boss.IsAlive())
				{
					CenterText(line);
					cout << endl;
					cout << "------------------------------------------------------- Round " << countRounds << " --------------------------------------------------------" << endl;
					cout << "LVL: " << hero.GetLvl() << setw(112) << "LVL: " << boss.GetLvl() << endl;
					cout << "HP: " << hero.GetHP() << setw(109) << "HP: " << boss.GetHP() << endl;
					cout << "Endurance: " << hero.GetEndurance() << setw(105) << "Endurance: " << boss.GetEndurance() << endl << endl;
					CenterText(action);
					cout << ">>> "; cin >> choice;
					cout << "\n\n";

					if (choice == 'a' || choice == 'A')
					{
						if (hero.GetEndurance() > 0)
						{
							boss.PointsWithdrawHP(hero.GetHeroDamage());
							boss.WithdrawHP(hero.Attack());
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
							if (hero.GetHeroHeal() < 0)
								hero.HealingSpell();
							else
							{
								boss.PointsWithdrawHP(hero.GetHeroMagicDamage());
								boss.WithdrawHP(hero.AttackSpell());
							}
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
						throw exception("�� ������� �������� ������� � �������� ������.");
					}
					if (boss.IsAlive())
					{
						cout << "The enemy's move!" << endl;
						if (boss.GetHP() <= boss.CheckRage())
							boss.RageMode();
						int temp(1 + rand() % 3);

						if (boss.GetEndurance() == 0)
							temp = 2;
						if (boss.GetEndurance() == 10)
							temp = 1;
						if (temp == 1)
						{
							hero.PointsWithdrawHP(boss.GetBossDamage());
							hero.WithdrawHP(boss.Attack());
							firstMonster.SetEnduranceNegative();
						}
						else if (temp == 2)
						{
							boss.Defend();
							boss.SetEndurancePositive();
						}
						else if (temp == 3)
						{
							if (boss.GetEndurance() > 1)
							{
								hero.PointsWithdrawHP(boss.GetBossMagicDamage());
								hero.WithdrawHP(boss.AttackSpell());
								for (int i = 0; i < 2; i++)
								{
									boss.SetEnduranceNegative();
								}
							}
							else
							{
								cout << "Not enough stamina. Stamina is " << boss.GetEndurance() << ". Opponent missing a move" << endl;
							}
						}
					}
					else
					{
						cout << "The Morgrim has fallen." << endl;
						Sleep(3);
						hero.UpMonsterSouls();
						hero.HeroLvlUp(1);
						if (hero.GetMonsterSouls() >= 20)
							hero.DarkSoulUp();
					}
					if (!hero.IsAlive())
					{
						throw runtime_error("YOU DIED!");
					}
					hero.SetDefence();
					boss.SetDefence();
					countRounds++;
				}
			}
			else if (sign == 'b' || sign == 'B')
			{
				Weapon monsterWeapon;
				Armor monsterArmor;
				Spell monsterSpell;
				Monster monster;
				char sign;
				string line("a)��������    b)�������    c)������ ������");

				system("cls");
				cout << endl;
				cout << "    �������� ������ �� ��������, ������� �������� ����� ������� �� ��������� ������ � ������. ��������� ���� ����� � � ���!" << endl;
				cout << endl<<endl;
				cout << "    �������� - ��������, ������� � ����� ����. ��� �����, �������� ������ � ���������, ��������� ���� � ������� ����� �����" << endl;
				cout << "    �� �������� �� ������ �������, �������� ���� ������ ������ � ����� �����." << endl << endl;
				cout << "    ������� - �������� �������� ����� � ������������ ��������, �� �������� �� ���� ������� ������,�� ������������ ���������" << endl;
				cout << "    ������. ��� ���� ������� ������, ������������ ������ ������,� ��� ������ ������� ����� ����� ��������� �������� �� ����" << endl<<endl;
				cout << "    ������ ������ - ���� �� ������� ����� ������������ ������.������� ����,����������� ������ ������ �����, �������� ������" << endl;
				cout << "    � ��� ������ ����������� �� �����, ������ ����, ������� ��� ��������, �������� �������, ���  ���� ���������� ������ ����" << endl<<endl;
				CenterText(line);
				cout << ">>>"; cin >> sign;

				switch (sign)
				{
				case'a':
					monsterWeapon = Weapon("�������� �����", hero.GetHeroWeaponDamage() - 1);
					monsterArmor = Armor("�������� ����������", hero.GetHelm() - 1, hero.GetCorset() - 1, hero.GetGloves(), hero.GetGreaves());
					monsterSpell = easeHealing;
					monster = Monster("��������", easeHealing, hero.GetLvl() - 1, hero.GetHeroDamage() - 1, 10, hero.GetHP(), hero.GetStr(), hero.GetAgl(), hero.GetIntl(), hero.GetHeroDefence(), monsterWeapon, monsterArmor);
					try
					{
						Fight(monster);
					}
					catch (exception& ex)
					{
						system("cls");
						cout << ex.what() << endl << endl;
						Sleep(2);
						exit(EXIT_SUCCESS);
					}
					catch (runtime_error& ex)
					{
						system("cls");
						cout << ex.what() << endl << endl;
						Sleep(2);
						exit(EXIT_SUCCESS);
					}
					break;
				case'b':
					monsterWeapon = Weapon("����� ����", hero.GetHeroWeaponDamage() - 1);
					monsterArmor = Armor("���������� ����", hero.GetHelm() - 1, hero.GetCorset() - 1, hero.GetGloves(), hero.GetGreaves());
					monsterSpell = easeHealing;
					monster = Monster("�������", easeHealing, hero.GetLvl() - 1, hero.GetHeroDamage() - 1, 10, hero.GetHP(), hero.GetStr(), hero.GetAgl(), hero.GetIntl(), hero.GetHeroDefence(), monsterWeapon, monsterArmor);
					try
					{
						Fight(monster);
					}
					catch (exception& ex)
					{
						system("cls");
						cout << ex.what() << endl << endl;
						Sleep(2);
						exit(EXIT_SUCCESS);
					}
					catch (runtime_error& ex)
					{
						system("cls");
						cout << ex.what() << endl << endl;
						Sleep(2);
						exit(EXIT_SUCCESS);
					}
					break;
				case'c':
					monsterWeapon = Weapon("������� ������", hero.GetHeroWeaponDamage() - 1);
					monsterArmor = Armor("������ ����", hero.GetHelm() - 1, hero.GetCorset() - 2, hero.GetGloves(), hero.GetGreaves());
					monsterSpell = easeHealing;
					monster = Monster("������ ������", easeHealing, hero.GetLvl(), hero.GetHeroDamage() - 1, 10, hero.GetHP(), hero.GetStr(), hero.GetAgl(), hero.GetIntl(), hero.GetHeroDefence(), monsterWeapon, monsterArmor);
					try
					{
						Fight(monster);
					}
					catch (exception& ex)
					{
						system("cls");
						cout << ex.what() << endl << endl;
						Sleep(2);
						exit(EXIT_SUCCESS);
					}
					catch (runtime_error& ex)
					{
						system("cls");
						cout << ex.what() << endl << endl;
						Sleep(2);
						exit(EXIT_SUCCESS);
					}
					break;
				default:
					cout << endl;
					cout << "����� ���� ��� ��� ������ �� �������. �� ����� ������!" << endl;
					Sleep(2);
					break;
				}
			}
			else if (sign == 'c' || sign == 'C')
			{
				int time(0);

				system("cls");
				cout << endl;
				cout << "   ������ ��� � ������ ����� ����� ����� ������������, � ������ ����� ������� ����, �� �������� ��������� 2 ������� ������." << endl;
				cout << "   ������ ������� ��� � ������ �������� ��� �������������. � ������ ��������� � ���� ��������, �� ������ �����������  ����," << endl;
				cout << "   ������� ����� ����� ������������ � �������, ������. ������ � ������������� ����� ��� ��������, ��� ��� �������� ��������" << endl << endl;
				cout << "   �� ������� ����� �� ������ ��������� � �����?>>>"; cin >> time;
				cout << endl;
				if (time <= hero.GetEndurance())
				{
					cout << "������ � ����� �� ������ " << time << " ������ ������� ����";
					if (time == 10)
					{
						cout << " � 1 ���������!" << endl << endl;
						diamonds.DiamondsUpCount();
						Sleep(2);
					}
					else
					{
						cout << endl<<endl;
						Sleep(2);
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
				char sign;
				string line("a) ������    b)�����    c)����������    d)������");

				system("cls");
				cout << "   � �������� �� ������ ���������� ����� ������, ����� � ����������.  ����� ����� ����� �������� ����� ������� ���� �� ������" << endl;
				cout << "   ��������� ������, ����� � ���������� ����� ������ ���� ���� � ����� ���� �������� ������ ����� ����, � ����� ���� ��������" << endl;
				cout << endl;
				CenterText(line);
				cout << ">>>"; cin >> sign;

				if (sign == 'a' || sign == 'A')
				{
					system("cls");
					cout << "a) --- ��� �� ������� ������(100 �������) ---\n";
					cout << "���� ��� ������� �� ��������� ������� ����������� � ������ � ������� �����������.� ��� ������� ����� ������ �� ��������" << endl << endl;
					cout << "b) --- ��� ������������ ���������(150 �������, 1 ���������) ---\n";
					cout << "��� ��� ������ �� ����� ����������� � �������������� ����� �����������, ������������ ���������,��������� �� ����� �����" << endl << endl;
					cout << "c) >>> ������� ��� ��������(200 �������, 5 ��� ��������) <<<\n\n";
					cout << "���� ��� �������� �� ����������� �������, ������������ ������� ��������. ��� �����  �� ��������� ����, ������� ��������" << endl;
					cout << "� �������� ����� ������������ �� ��� ��������� ����.  �������,  ���  ������ �������� ����������������� � ������ �������" << endl << endl;
					cout << "d) >>> ��� ��������� �����(200 �������, 5 �����������) <<<\n";
					cout << "���� ��������� ������ ��� ������ �� �������� ����������. ��� ���� �� ��������� �� ����� ���� ����� � �������� ���������" << endl;
					cout << "�������� ������ �����. ��������� ������: ��������� ��������� ����� �� �������� �  x2  �� ���� ������ ����� ������ �����" << endl << endl;
					cout << "e) <<<-->>> ���������� �����: ��� ������������ ������(���� ����) <<<-->>>\n";
					cout << "���� ���, ���������� � ������� ���������, ������������ ����� �������� ��������� �������� �������  � ����������. ������," << endl;
					cout << "������ ������� ����, �������� ������� ����, �������� ������  ����  ��������� ���� ����.  ������� ������� ����� ������� " << endl;
					cout << "������� ������, ������� ������ ������������ � �������, ����������� ��� �������� ���������." << endl << endl;
					cout << "���� ��� ���� ���������� ������������ �������� � �������� � ����� ����� ������������ ����. ������������, ���  ��������" << endl;
					cout << "���� ���������� ��������� ����������� �����, �������� � ���� ��� ������ ����, ��� �����-�� ������� ����.������ �������" << endl;
					cout << "������� ���� ������� ������ ������ ������� , ��������� ������� ����� ������� ������ � ��������� ���� ���� � ����." << endl;
					cout << endl;
					cout << ">>>"; cin >> sign;
					switch (sign)
					{
					case 'a':
						if (hero.GetMoney() >= 100)
						{
							hero.NewSword("��� �� ������� ������", 55);
							hero.SetMoney(100);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					case'b':
						if (hero.GetMoney() >= 150 && diamonds.GetQuantity() >= 1)
						{
							hero.NewSword("��� ������������ ���������", 80);
							hero.SetMoney(150);
							diamonds.SetDiamonds(1);							
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);							
						}
					case'c':
						if (hero.GetMoney() >= 200 && hero.GetMonsterSouls())
						{
							hero.NewSword("������� ��� ��������", 105);
							hero.SetMoney(200);
							hero.MonsterSoulsOrder(5);							
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					case'd':
						if (hero.GetMoney() >= 200 && diamonds.GetQuantity() >= 5)
						{
							hero.NewSword("��� ��������� �����", 115);
							hero.SetMoney(200);
							diamonds.SetDiamonds(5);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					case'e':
						if (hero.DarkSoul())
						{
							hero.NewSword("���������� �����: ��� ������������ ������", 199);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					default:
						cout << endl;
						cout << "����� ���� ��� ��� ������ �� �������. �� ����� ������!" << endl;
						Sleep(2);
						break;
					}
				}
				else if (sign == 'b' || sign == 'B')
				{
					system("cls");
					cout << "a) --- ����� �� ������ �������(100 �������) ---\n";
					cout << "����� ������� ������ ������ ������� �����������, ����� �������  ��  ���  ���  �������, ������������� ������� � �������." << endl << endl;
					cout << "b) --- ����� ������������ ���������(150 �������, 1 ���������) ---\n";
					cout << "����� ��������������� � ������������ �����, ������������ ���������,��������� �� ����� �����. �������� �� ������  �����." << endl << endl;
					cout << "c) >>> ������� ������ ��������(200 �������, 5 ��� ��������) <<<\n";
					cout << "��� ����� ��������� �� ����������� �������, ������������ ������� ��������. ��� ����� ��  ���  ����������� ������� ����, " << endl;
					cout << "� �������� ����� ������������ �� ��� ��������� ����.  �������, ���  ������� �������� ����������������� � ������ �������" << endl << endl;
					cout << "d) >>> ������� �������� ����(200 �������, 5 �����������) <<<\n";
					cout << "��� ������������ ����� ���� ������� �� �������� ����������. ��� �������� � ��������� ��� ������� ������  �������  �����" << endl;
					cout << "������� ������ ������. ��������� ������: ��������� ��������� ����� �� �������� �  x2  �� ���� ������ ����� ������ �����" << endl << endl;
					cout << "e) <<<-->>> �������������� ������� ������������ ������(���� ����) <<<-->>>\n";
					cout << "��� �������, ��������� �� �������,��� ���� � ������� ����� ���� ���� ������,��������� ������������ ��������  � �������" << endl;
					cout << "������ �������� �������� ����� ������� ������ ��������� ������,� ������� �����,��������������� ����� ������,����������" << endl;
					cout << "� ����� �����. �������� ������������� �������� ���������, ��� ���� � ������� ���������� ������ ��� ��������.  �������," << endl;
					cout << "����������� �������, �������� ���� �����, �������� ����������� ������� �����, �� �������� ���� ����� ���� ������ �����" << endl;
					cout << "��� ������� �� ������ �������� ������ ��������� �� ������, ��� ���������� ������ ��� ������ ��������,  �������� ���� �" << endl;
					cout << "������ �������. ��, ��� ������������ ����� ��������� ������������� ��������, ����������� �� ���� ��������. " << endl;
					cout << endl;
					cout << ">>>"; cin >> sign;
					switch (sign)
					{
					case 'a':
						if (hero.GetMoney() >= 100)
						{
							hero.NewArmor("����� �� ������ �������", 15, 20, 7, 7);
							hero.SetMoney(100);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					case'b':
						if (hero.GetMoney() >= 150 && diamonds.GetQuantity() >= 1)
						{
							hero.NewArmor("����� ������������ ���������", 30, 45, 15, 15);
							hero.SetMoney(150);
							diamonds.SetDiamonds(1);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					case'c':
						if (hero.GetMoney() >= 200 && hero.GetMonsterSouls())
						{
							hero.NewArmor("������� ������ ��������", 38, 58, 20, 20);
							hero.SetMoney(200);
							hero.MonsterSoulsOrder(5);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					case'd':
						if (hero.GetMoney() >= 200 && diamonds.GetQuantity() >= 5)
						{
							hero.NewArmor("������� �������� ����", 34, 55, 18, 18);
							hero.SetMoney(200);
							diamonds.SetDiamonds(5);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					case'e':
						if (hero.DarkSoul())
						{
							hero.NewArmor("�������������� ������� ������������ ������", 65, 80, 45, 45);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					default:
						cout << endl;
						cout << "����� ���� ��� ��� ������ �� �������. �� ����� ������!" << endl;
						Sleep(2);
						break;
					}
				}
				else if (sign == 'c' || sign == 'C')
				{
					system("cls");
					cout << "a) --- �������� ���(50 �������, 1 ���������) ---\n";
					cout << "��������� ��� ���� � ����������. ����� ������� �� ��������� ����������" << endl << endl;
					cout << "b) --> ������� ���������(100 �������, 2 ���������) <--\n";
					cout << "��������� ������� ����. ���������� ����������� ��������� ���, ��������������� ����." << endl << endl;
					cout << "c) --> ������� ������(100 �������, 2 ����������) <--\n";
					cout << "��������� ����� �������� ������. ���������� ��������� ������ � �������� ������� �������." << endl << endl;
					cout << "d) >>> ������ ���������(150 �������, 3 �����������) <<<\n";
					cout << "�������, ����� ������ �����.������� ����� �� ������� ������.�������� �������� ����� �������� ����,��������� ����������" << endl << endl;
					cout << "e) >>> ����������� ����(���� ����) <<<\n";
					cout << "��������� ������� ����� ������������ ������. ����� ���������������� ������ ������ �����������." << endl;
					cout << endl;
					cout << ">>>"; cin >> sign;
					switch (sign)
					{
					case 'a':
						if (hero.GetMoney() >= 50 && diamonds.GetQuantity() >= 1)
						{
							hero.NewSpell("Fireball");
							hero.SetMoney(50);
							diamonds.SetDiamonds(1);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					case'b':
						if (hero.GetMoney() >= 100 && diamonds.GetQuantity() >= 2)
						{
							hero.NewSpell("Medium treatment");
							hero.SetMoney(100);
							diamonds.SetDiamonds(2);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					case'c':
						if (hero.GetMoney() >= 100 && diamonds.GetQuantity() >= 2)
						{
							hero.NewSpell("Ball lightning");
							hero.SetMoney(100);
							hero.MonsterSoulsOrder(2);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					case'd':
						if (hero.GetMoney() >= 150 && diamonds.GetQuantity() >= 3)
						{
							hero.NewSpell("Extra treatment");
							hero.SetMoney(150);
							diamonds.SetDiamonds(3);
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					case'e':
						if (hero.DarkSoul())
						{
							hero.NewSpell("Soul snatching");
						}
						else
						{
							cout << endl;
							cout << "� ��� ������������ �������. " << endl;
							Sleep(2);
						}
						break;
					default:
						cout << endl;
						cout << "����� ���� ��� ��� ������ �� �������. �� ����� ������!" << endl;
						Sleep(2);
						break;
					}
				}
				else if (sign == 'd' || sign == 'D')
				{
					if(gold.GetQuantity()!=0)
					{
						while (gold.GetQuantity() != 0)
						{
							hero.Exchange();
							gold.Exchange();
						}
					}
					else
					{
						cout << endl;
						cout << "� ��� ������������ ������. " << endl;
						Sleep(2);
					}
				}
			}
			else if (sign == 'e' || sign == 'E')
			{
				hero.SetEndurance();
				hero.Resting();
				system("cls");
				cout << "������������ � �������� ��������� �������������." << endl;
				Sleep(2);
			}
			else if (sign == 'f' || sign == 'F')
			{
				system("cls");
				cout << " -------------------------------------" << endl;
				hero.SoulsInventory();
				gold.Show();
				diamonds.Show();
				cout << "| Money: " << hero.GetMoney() << endl;
				cout << " -------------------------------------" << endl;
				cout << "                                       ";
				system("pause");
			}
			else if (sign == 'g' || sign == 'G')
			{
				system("cls");
				hero.Show();
				cout << "                                       ";
				system("pause");
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