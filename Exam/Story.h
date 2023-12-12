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
		heroSword = Weapon("Steal sword", 10);
		heroArmor = Armor("Plate armor", 3, 4, 1, 1);
		heroShield = Shield("Iron shield", 30);
		hero = Hero(name, easeHealing, 1, 65, 10, 150, 10, 10, 10, 5, heroSword, heroArmor, heroShield);
		firstMonsterWeapon = Weapon("Bloody claws", 7);
		firstMonsterArmor = Armor("Bone exoskeleton", 1, 3, 0, 0);
		firstMonster = Monster("Darkclow", easeHealing, 1, 40, 10, 110, 12, 6, 1, 14, firstMonsterWeapon, firstMonsterArmor);
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
		string action = "a)Attack    b)Defend    c)Use spell";
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
				throw exception("You made a bad decision and lost your head.");
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
		string action = "a)Attack    b)Defend    c)Use spell";
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
				throw exception("You made a bad decision and lost your head.");
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
			string line("a)Dungeon    b)Take an order    c)Mines    d)Shop    e)Rest    f)Inventory    g)Characteristics");

			system("cls");
			cout << endl;
			CenterText("Village");
			cout << "\n\n";
			cout << setw(78) << " House1     House2       House3\n";
			cout << setw(75) << "   |          |            |\n";
			cout << setw(75) << "   |          |            |\n";
			cout << setw(76) << " Square --- Church  ---  Shop\n";
			cout << setw(75) << "   |          |            |\n";
			cout << setw(75) << "   |          |            |\n";
			cout << setw(77) << " Mines      Tavern       River\n";
			cout << "\n\n";
			CenterText(line);
			cout << ">>> "; cin >> sign;
			if (sign == 'a' || sign == 'A')
			{
				system("cls");
				cout << endl;
				cout << "    Morgrim was originally a great warrior who lost his name in the vast battles,  the Shadow of the Forgotten Hero now " << endl;
				cout << "    became the an ancient darkness consumed by endless wars. His armor, once shiny and colorful, is now soaked in black" << endl;
				cout << "    dark and twisted in the form of twisted shadows." << endl << endl;
				cout << "    The face of the Buried Warrior is hidden beneath  a  mask carved from black metal,  and only the faint glowing eyes  " << endl;
				cout << "    show the his lost identity.  In his hands he holds  a  blade plunged into a bottomless darkness that can swallow up " << endl;
				cout << "    light.  His footsteps shake the earth  as  if it bore the burden of millennia of endless battles that had turned it  " << endl;
				cout << "    into a dead the shadow of the great hero who served as the Legendary King's right hand." << endl;
				cout << endl;
				cout << "                                    ";
				system("pause");

				Spell bossSpell("Soul snatching", 0, 1090);
				Weapon bossSword("Destroyer", 200);
				Armor bossArmor("The Veil of the Abyss", 60, 80, 20, 20);
				Boss boss("Morgrim, shadow of a forgotten hero", bossSpell, 30, 195, 10, 4500, 50, 50, 50, 45, bossSword, bossArmor);
				string opponents1(hero.GetName());
				string opponenst2(boss.GetName());
				string vs = " VS ";
				string line = opponents1 + vs + opponenst2;
				string action = "a)Attack    b)Defend    c)Use spell";
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
						throw exception("You made a bad decision and lost your head.");
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
						hero.HeroLvlUp(10);
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
				string line("a)Darkclow    b)Vargrim    c)Dark Knight");

				system("cls");
				cout << endl;
				CenterText("By fulfilling orders on monsters that have appeared near the village you get gold and levels.");
				cout << endl<<endl;
				cout << "    Darkclow - a creature hidden in the darkness of night.Its claws,covered in dirt and critters,leave a mark in the hearts" << endl;
				cout << "    of its victims. He attacks from dark corners, leaving only whispers of fear in his wake." << endl << endl;
				cout << "    Vargrim - a middle-ranking creature in the demonic hierarchy,  but despite his middle - ranking status, he represents a" << endl;
				cout << "    serious menace.His body is covered in flesh that resembles black armor,and his dark-colored wings can flicker unnoticed" << endl;
				cout << "    in the darkness. " << endl << endl;
				cout << "    DarK knight - a warrior from the ancient era of the Legendary King.  Heavy armor, inscribed with runes  of  dark magic," << endl;
				cout << "    radiates menace. His robe flutters in the wind like the darkness that surrounds him,  enveloping armor whose dark color" << endl;
				cout << "    resembles pure night." << endl << endl;
				CenterText(line);
				cout << ">>>"; cin >> sign;

				switch (sign)
				{
				case'a':
					monsterWeapon = Weapon("Bloody Clows", hero.GetHeroWeaponDamage() - 1);
					monsterArmor = Armor("Bone exoskeleton", hero.GetHelm() - 1, hero.GetCorset() - 1, hero.GetGloves(), hero.GetGreaves());
					monsterSpell = easeHealing;
					monster = Monster("Darkclow", easeHealing, hero.GetLvl() - 1, hero.GetHeroDamage() - 1, 10, hero.GetHP(), hero.GetStr(), hero.GetAgl(), hero.GetIntl(), hero.GetHeroDefence(), monsterWeapon, monsterArmor);
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
					monsterWeapon = Weapon("The lash of fire", hero.GetHeroWeaponDamage() - 1);
					monsterArmor = Armor("Ebonite skin", hero.GetHelm() - 1, hero.GetCorset() - 1, hero.GetGloves(), hero.GetGreaves());
					monsterSpell = easeHealing;
					monster = Monster("Vargrim", easeHealing, hero.GetLvl() - 1, hero.GetHeroDamage() - 1, 10, hero.GetHP(), hero.GetStr(), hero.GetAgl(), hero.GetIntl(), hero.GetHeroDefence(), monsterWeapon, monsterArmor);
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
					monsterWeapon = Weapon("Shadow Blade", hero.GetHeroWeaponDamage() - 1);
					monsterArmor = Armor("The armor of the night", hero.GetHelm() - 1, hero.GetCorset() - 2, hero.GetGloves(), hero.GetGreaves());
					monsterSpell = easeHealing;
					monster = Monster("Dark Knight", easeHealing, hero.GetLvl(), hero.GetHeroDamage() - 1, 10, hero.GetHP(), hero.GetStr(), hero.GetAgl(), hero.GetIntl(), hero.GetHeroDefence(), monsterWeapon, monsterArmor);
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
					cout << "I'm sorry you didn't get anything. See you again!" << endl;
					Sleep(2);
					break;
				}
			}
			else if (sign == 'c' || sign == 'C')
			{
				int time(0);

				system("cls");
				cout << endl;
				cout << "   Each hour in the mines equals one of your stamina,  and one piece of gold ore, which will produce  2  gold coins. Every" << endl;
				cout << "   tenth hour in the mines will bring you a jewel. The mines are safe and there are no monsters, but the robot uses energy" << endl;
				cout << "   that can be recovered in the village by sleeping.Gold and jewels are needed for trading,so you will have to work for it" << endl << endl;
				cout << "   How many hours do you want to send to the mines?>>>"; cin >> time;
				cout << endl;
				if (time <= hero.GetEndurance())
				{
					cout << "When you went to the mine, you mined " << time << " chunks of gold ore";
					if (time == 10)
					{
						cout << " and 1 brilliant!" << endl << endl;
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
					throw logic_error("You didn't have the strength for the job. You fainted and killed yourself on a rock.");
				}
			}
			else if (sign == 'd' || sign == 'D')
			{
				char sign;
				string line("a)Weapon    b)Armor    c)Spells    d)Coins");

				system("cls");
				cout << "   In the store you can buy new weapons,armor and spells.Here you can also exchange pieces of gold ore for coins.Some weapons" << endl;
				cout << "   armor,and spells can only be purchased by carrying the soul of the main villain of the act,as well as the soul of monsters" << endl;
				cout << endl;
				CenterText(line);
				cout << ">>>"; cin >> sign;

				if (sign == 'a' || sign == 'A')
				{
					system("cls");
					cout << "a) --- Black Iron Sword (100 gold) ---\n";
					cout << "This sword is forged from the material of an ancient civilization and found in ancient dungeons.There is almost nothing" << endl;
					cout << "known about its history." << endl << endl;
					cout << "b) --- Sword of the Kingsguard (150 gold, 1 diamond) ---\n";
					cout << "This is the sword of one of the noblest and most powerful men in the kingdom,  a Kingsguard, found on the battlefields." << endl << endl;
					cout << "c) >>> Shadow Ghost Sword (200 gold, 5 monster souls) <<<\n\n";
					cout << "This sword is made of ghostly metal imbued with shadow energy. When struck,  it casts a shadow that moves in motion and" << endl;
					cout << "the wielder can use it for invisible attacks.  The blade is said to be able to interact with the souls of the dead." << endl << endl;
					cout << "d) >>> Sword of the Star Wind (200 gold, 5 diamonds) <<<\n";
					cout << "This curved blade was created from stellar materials.When swung, it leaves a vortex trail behind it and has the ability" << endl;
					cout << "to summon light winds. Passive effect:  raises the armor multiplier from dexterity due to the wind flow around the hero" << endl << endl;
					cout << "e) <<<-->>> Lord of Shadows: Sword of the Legendary King (Soul of Darkness) <<<-->>>\n";
					cout << "Forged in the abysses of antiquity, this sword is a skillful combination of sinister beauty and power. The blade,like a" << endl;
					cout << "blob of night, it exudes an indistinct light, creating a flickering aura of darkness around it.  The golden handles are" << endl;
					cout << "covered in dark with a leather cord that serves as a reminder of the madness that consumed its great creator." << endl;
					cout << "This sword has witnessed countless battles and is steeped in the darkest recesses of the human soul.It is said that the" << endl;
					cout << "wielder the sword becomes inevitably permeated with darkness,  absorbing all the dark forces that once overshadowed the" << endl;
					cout << "light. Knowing the depths This ancient king wielded a weapon capable of reviving the darkest fears and nightmares. " << endl;
					cout << endl;
					cout << ">>>"; cin >> sign;
					switch (sign)
					{
					case 'a':
						if (hero.GetMoney() >= 100)
						{
							hero.NewSword("Black Iron Sword", 55);
							hero.SetMoney(100);
						}
						else
						{
							cout << endl;
							cout << "You don't have enough funds." << endl;
							Sleep(2);
						}
						break;
					case'b':
						if (hero.GetMoney() >= 150 && diamonds.GetQuantity() >= 1)
						{
							hero.NewSword("Sword of the Kingsguard", 80);
							hero.SetMoney(150);
							diamonds.SetDiamonds(1);							
						}
						else
						{
							cout << endl;
							cout << "You don't have enough funds." << endl;
							Sleep(2);							
						}
					case'c':
						if (hero.GetMoney() >= 200 && hero.GetMonsterSouls())
						{
							hero.NewSword("Shadow Ghost Sword", 105);
							hero.SetMoney(200);
							hero.MonsterSoulsOrder(5);							
						}
						else
						{
							cout << endl;
							cout << "You don't have enough funds." << endl;
							Sleep(2);
						}
						break;
					case'd':
						if (hero.GetMoney() >= 200 && diamonds.GetQuantity() >= 5)
						{
							hero.NewSword("Sword of the Star Wind(", 115);
							hero.SetMoney(200);
							diamonds.SetDiamonds(5);
						}
						else
						{
							cout << endl;
							cout << "You don't have enough funds." << endl;
							Sleep(2);
						}
						break;
					case'e':
						if (hero.DarkSoul())
						{
							hero.NewSword("Lord of Shadows: Sword of the Legendary King", 199);
						}
						else
						{
							cout << endl;
							cout << "You don't have enough funds." << endl;
							Sleep(2);
						}
						break;
					default:
						cout << endl;
						cout << "I'm sorry you didn't get anything. See you again!" << endl;
						Sleep(2);
						break;
					}
				}
				else if (sign == 'b' || sign == 'B')
				{
					system("cls");
					cout << "a) --- Black Plate Armor (100 gold) ---\n";
					cout << "The armor worn by the knights of an ancient civilization, very ancient but still strong,  impervious to time and decay." << endl << endl;
					cout << "b) --- Royal Guardsman Armor (150 gold, 1 diamond) ---\n";
					cout << "The armor of a mighty and noble warrior, a Kingsguard, found on the battlefields. Forged from the finest steel." << endl << endl;
					cout << "c) >>> Shadow Ghost Armor (200 gold, 5 monster souls) <<<\n";
					cout << "This armor is made of ghostly metal imbued with shadow energy.  When struck,  it  bounces off a blob of shadow, and the" << endl;
					cout << "wearer can use it for invisible attacks.  The armor is said to be able to interact with the souls of the dead." << endl << endl;
					cout << "d) >>> Stardust Armor (200 gold, 5 diamonds) <<<\n";
					cout << "This amazing armor was made from stellar materials. When it comes in contact with the armor, it glistens with the light" << endl;
					cout << "of distant stars blowing wind around the knight. Passive effect:  raises the armor multiplier from dexterity due to the" << endl;
					cout << "wind flow around the hero." << endl << endl;
					cout << "e) <<<-->>> The darkwoven armor of the legendary king (Soul of Darkness) <<<-->>>\n";
					cout << "This armor, created in a time where darkness and madness weave their threads together,is framed with a mysterious charm" << endl;
					cout << "and menace. Each brass plate of this armor seems to be imbued with darkness,  and the golden patterns intertwined along" << endl;
					cout << "the cuirass are reminiscent of the vortex of shadows.  The wearer of the Darkwoven Armor feels the darkness and madness" << endl;
					cout << "become part of his essence.  Hood, fringed with gold,  hides the face of the warrior,  giving the impression of eternal" << endl;
					cout << "darkness, from which even the light has no way back. This armor doesn't just protect its wearer from blows,  it becomes" << endl;
					cout << "part of his very being, lending strength to the in a fit of madness.  Those who dare to become wearers of the Darkwoven" << endl;
					cout << "Armor are plunged into darkness forever." << endl;
					cout << endl;
					cout << ">>>"; cin >> sign;
					switch (sign)
					{
					case 'a':
						if (hero.GetMoney() >= 100)
						{
							hero.NewArmor("Black Plate Armor", 15, 20, 7, 7);
							hero.SetMoney(100);
						}
						else
						{
							cout << endl;
							cout << "You don't have enough funds." << endl;
							Sleep(2);
						}
						break;
					case'b':
						if (hero.GetMoney() >= 150 && diamonds.GetQuantity() >= 1)
						{
							hero.NewArmor("Royal Guardsman Armor", 30, 45, 15, 15);
							hero.SetMoney(150);
							diamonds.SetDiamonds(1);
						}
						else
						{
							cout << endl;
							cout << "You don't have enough funds." << endl;
							Sleep(2);
						}
						break;
					case'c':
						if (hero.GetMoney() >= 200 && hero.GetMonsterSouls())
						{
							hero.NewArmor("Shadow Ghost Armor", 38, 58, 20, 20);
							hero.SetMoney(200);
							hero.MonsterSoulsOrder(5);
						}
						else
						{
							cout << endl;
							cout << "You don't have enough funds." << endl;
							Sleep(2);
						}
						break;
					case'd':
						if (hero.GetMoney() >= 200 && diamonds.GetQuantity() >= 5)
						{
							hero.NewArmor("Stardust Armor", 34, 55, 18, 18);
							hero.SetMoney(200);
							diamonds.SetDiamonds(5);
						}
						else
						{
							cout << endl;
							cout << "You don't have enough funds." << endl;
							Sleep(2);
						}
						break;
					case'e':
						if (hero.DarkSoul())
						{
							hero.NewArmor("The Darkwoven Armor of the Legendary King", 65, 80, 45, 45);
						}
						else
						{
							cout << endl;
							cout << "You don't have enough funds." << endl;
							Sleep(2);
						}
						break;
					default:
						cout << endl;
						cout << "I'm sorry you didn't get anything. See you again!" << endl;
						Sleep(2);
						break;
					}
				}
				else if (sign == 'c' || sign == 'C')
				{
					system("cls");
					cout << "a) --- Fireball (50 gold, 1 diamond) ---\n";
					cout << "Fires a fireball at an enemy. The simplest of the attack spells." << endl << endl;
					cout << "b) --> Medium Exquisition (100 gold, 2 diamonds) <--\n";
					cout << "Healing of medium strength. Heals most serious wounds, restores strength." << endl << endl;
					cout << "c) --> Ball Lightning (100 gold, 2 diamonds) <--\n";
					cout << "Medium level attack magic. Poses a serious threat and affects a large area." << endl << endl;
					cout << "d) >>> Powerful Healing (150 gold, 3 diamonds) <<<\n";
					cout << "Ancient, very powerful magic. They say it was taught to humans by angels. Can heal the worst wounds, regrow limbs." << endl << endl;
					cout << "e) >>> Soul Pulling (Soul of Darkness) <<<\n";
					cout << "The cursed ancient magic of a legendary king. It poses a catastrophic threat to the target kingdom." << endl;
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
							cout << "You don't have enough funds." << endl;
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
							cout << "You don't have enough funds." << endl;
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
							cout << "You don't have enough funds." << endl;
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
							cout << "You don't have enough funds." << endl;
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
							cout << "You don't have enough funds." << endl;
							Sleep(2);
						}
						break;
					default:
						cout << endl;
						cout << "I'm sorry you didn't get anything. See you again!" << endl;
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
						cout << "You don't have enough gold ore. " << endl;
						Sleep(2);
					}
				}
			}
			else if (sign == 'e' || sign == 'E')
			{
				hero.SetEndurance();
				hero.Resting();
				system("cls");
				cout << "Stamina and health fully restored." << endl;
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
				throw exception("You got lost and drowned in the river.");
			}
		}
	}
	void Gotoxy(int x, int y);
	void Priview();
	void Menu();
	void ActI();
};