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
		heroSword = Weapon("Стальной меч", 10);
		heroArmor = Armor("Пластинчатая броня", 3, 4, 1, 1);
		heroShield = Shield("Железный щит", 30);
		hero = Hero(name, easeHealing, 1, 65, 10, 150, 10, 10, 10, 5, heroSword, heroArmor, heroShield);
		firstMonsterWeapon = Weapon("Кровавые когти", 7);
		firstMonsterArmor = Armor("Костяной екзоскелет", 1, 3, 0, 0);
		firstMonster = Monster("Мраколап", easeHealing, 1, 40, 10, 110, 12, 6, 1, 14, firstMonsterWeapon, firstMonsterArmor);
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
		string action = "a)Атаковать    b)Защищаться    c)Использовать заклинание";
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
				throw exception("Вы приняли неверное решение и лишились головы.");
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
		string action = "a)Атаковать    b)Защищаться    c)Использовать заклинание";
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
				throw exception("Вы приняли неверное решение и лишились головы.");
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
			string line("a)Подземелье    b)Взять заказ    c)Шахты    d)Магазин    e)Поспать    f)Инвентарь    g)Характеристики");

			system("cls");
			cout << endl;
			CenterText("Village");
			cout << "\n\n";
			cout << setw(76) << "  Дом1       Дом2         Дом3\n";
			cout << setw(74) << "   |          |            |\n";
			cout << setw(74) << "   |          |            |\n";
			cout << setw(76) << "Площадь --- Церковь --- Магазин\n";
			cout << setw(74) << "   |          |            |\n";
			cout << setw(74) << "   |          |            |\n";
			cout << setw(76) << " Шахты     Таверна        Река\n";
			cout << "\n\n";
			CenterText(line);
			cout << ">>> "; cin >> sign;
			if (sign == 'a' || sign == 'A')
			{
				system("cls");
				cout << endl;
				cout << "    Моргрим изначально был великим воином, утратившим свое имя в бескрайних сражениях, Тень Забытого Героя теперь стала" << endl;
				cout << "    древней тьмой, поглощенной бескрайними войнами. Его доспехи, когда-то блестящие и красочные,теперь пропитаны черным" << endl;
				cout << "    мраком и искривлены в виде исковерканных теней." << endl << endl;
				cout << "    Лицо Погребенного Воина скрыто под маской, высеченной из черного металла, и лишь слабые светящиеся глаза  проявляют " << endl;
				cout << "    его потерянную личность. В руках он держит клинок, погруженный в бездонную тьму, способную поглотить свет. Его шаги " << endl;
				cout << "    сотресают землю,  словно он несет на себе бремя тысячелетий бесконечных сражений, которые превратили его в  мертвую " << endl;
				cout << "    великого героя, служившего правой рукой Легендарного короля" << endl;
				cout << endl;
				cout << "                                    ";
				system("pause");

				Spell bossSpell("Soul snatching", 0, 1090);
				Weapon bossSword("Губитель", 200);
				Armor bossArmor("Вуаль Бездны", 60, 80, 20, 20);
				Boss boss("Моргрим, тень забытого героя", bossSpell, 30, 195, 10, 4500, 50, 50, 50, 45, bossSword, bossArmor);
				string opponents1(hero.GetName());
				string opponenst2(boss.GetName());
				string vs = " VS ";
				string line = opponents1 + vs + opponenst2;
				string action = "a)Атаковать    b)Защищаться    c)Использовать заклинание";
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
						throw exception("Вы приняли неверное решение и лишились головы.");
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
				string line("a)Мраколап    b)Варгрим    c)Темный рыцарь");

				system("cls");
				cout << endl;
				cout << "    Выполняя заказы на монстров, которые завелись возле деревни вы получаете золото и уровни. Отдохните если нужно и в бой!" << endl;
				cout << endl<<endl;
				cout << "    Мраколап - существо, скрытое в мраке ночи. Его когти, покрытые грязью и живностью, оставляют след в сердцах своих жертв" << endl;
				cout << "    Он нападает из темных уголков, оставляя лишь шепоты страха в своем следе." << endl << endl;
				cout << "    Варгрим - существо среднего ранга в демонической иерархии, но несмотря на свой средний статус,он представляет серьезную" << endl;
				cout << "    угрозу. Его тело покрыто плотью, напоминающей черный доспех,а его крылья темного цвета могут незаметно мелькать во тьме" << endl<<endl;
				cout << "    Темный рыцарь - воин из древней эпохи Легендарного короля.Тяжелые латы,испещренные рунами темной магии, излучаюь угрозу" << endl;
				cout << "    а его мантия развевается по ветру, словно мрак, который его окружает, окутывая доспехи, чей  цвет напоминает чистую ночь" << endl<<endl;
				CenterText(line);
				cout << ">>>"; cin >> sign;

				switch (sign)
				{
				case'a':
					monsterWeapon = Weapon("Кровавые когти", hero.GetHeroWeaponDamage() - 1);
					monsterArmor = Armor("Костяной екзоскелет", hero.GetHelm() - 1, hero.GetCorset() - 1, hero.GetGloves(), hero.GetGreaves());
					monsterSpell = easeHealing;
					monster = Monster("Мраколап", easeHealing, hero.GetLvl() - 1, hero.GetHeroDamage() - 1, 10, hero.GetHP(), hero.GetStr(), hero.GetAgl(), hero.GetIntl(), hero.GetHeroDefence(), monsterWeapon, monsterArmor);
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
					monsterWeapon = Weapon("Плеть огня", hero.GetHeroWeaponDamage() - 1);
					monsterArmor = Armor("Эбонитовая кожа", hero.GetHelm() - 1, hero.GetCorset() - 1, hero.GetGloves(), hero.GetGreaves());
					monsterSpell = easeHealing;
					monster = Monster("Варгрим", easeHealing, hero.GetLvl() - 1, hero.GetHeroDamage() - 1, 10, hero.GetHP(), hero.GetStr(), hero.GetAgl(), hero.GetIntl(), hero.GetHeroDefence(), monsterWeapon, monsterArmor);
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
					monsterWeapon = Weapon("Теневой клинок", hero.GetHeroWeaponDamage() - 1);
					monsterArmor = Armor("Доспех ночи", hero.GetHelm() - 1, hero.GetCorset() - 2, hero.GetGloves(), hero.GetGreaves());
					monsterSpell = easeHealing;
					monster = Monster("Темный рыцарь", easeHealing, hero.GetLvl(), hero.GetHeroDamage() - 1, 10, hero.GetHP(), hero.GetStr(), hero.GetAgl(), hero.GetIntl(), hero.GetHeroDefence(), monsterWeapon, monsterArmor);
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
					cout << "Очень жаль что вам ничего не подошло. До новых встреч!" << endl;
					Sleep(2);
					break;
				}
			}
			else if (sign == 'c' || sign == 'C')
			{
				int time(0);

				system("cls");
				cout << endl;
				cout << "   Каждый час в шахтах равен одной вашей выносливости, и одному куску золотой руды, из которого получится 2 золотые монеты." << endl;
				cout << "   Каждый десятый час в шахтах принесет вам драгоценность. В шахтах безопасно и нету монстров, но робота затрачивает  силы," << endl;
				cout << "   которые можно будет восстановить в деревне, поспав. Золото и драгоценности нужны для торговли, так что работать придется" << endl << endl;
				cout << "   На сколько часов вы хотите отправить в шахты?>>>"; cin >> time;
				cout << endl;
				if (time <= hero.GetEndurance())
				{
					cout << "Сходив в шахту вы добыли " << time << " кусков золотой руды";
					if (time == 10)
					{
						cout << " и 1 бриллиант!" << endl << endl;
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
					throw logic_error("У вас не хватило сил для работы. Вы упали в обморок и убились об камень.");
				}
			}
			else if (sign == 'd' || sign == 'D')
			{
				char sign;
				string line("a) Оружие    b)Броня    c)Заклинания    d)Монеты");

				system("cls");
				cout << "   В магазине вы можете преобрести новое оружие, броню и заклинания.  Также здесь можно обменять куски золотой руды на монеты" << endl;
				cout << "   Некоторое оружие, броню и заклилание можно купить лишь имея с собой душу главного злодея этого акта, а также души монстров" << endl;
				cout << endl;
				CenterText(line);
				cout << ">>>"; cin >> sign;

				if (sign == 'a' || sign == 'A')
				{
					system("cls");
					cout << "a) --- Меч из Черного железа(100 золотых) ---\n";
					cout << "Этот меч выкован из материала древний цивилизации и найден в древних подземельях.О его пролшом почти ничего не известно" << endl << endl;
					cout << "b) --- Меч Королевского Гвардейца(150 золотых, 1 бриллиант) ---\n";
					cout << "Это меч одного из самых благородных и могущественных людей королевства, Королевского гвардейца,найденого на полях битвы" << endl << endl;
					cout << "c) >>> Теневой Меч Призрака(200 золотых, 5 душ монстров) <<<\n\n";
					cout << "Этот меч выполнен из призрачного металла, пропитанного теневой энергией. При ударе  он оставляет тень, которая движется" << endl;
					cout << "а владелец может использовать ее для невидимых атак.  Сказано,  что  клинок способен взаимодействовать с душами умерших" << endl << endl;
					cout << "d) >>> Меч Звездного Ветра(200 золотых, 5 бриллиантов) <<<\n";
					cout << "Этот изогнутый клинок был создан из звездных материалов. При махе он оставляет за собой след вихря и обладает свойством" << endl;
					cout << "Вызывать легкие ветра. Пассивный эффект: поднимает множитель брони от ловкости в  x2  за счет потока ветра вокруг героя" << endl << endl;
					cout << "e) <<<-->>> Властитель теней: Меч легендарного короля(Душа Тьмы) <<<-->>>\n";
					cout << "Этот меч, выкованный в безднах древности, представляет собой искусное сочетание зловещей красоты  и могущества. Лезвие," << endl;
					cout << "словно сгусток ночи, источает неясный свет, создавая вокруг  себя  мерцающую ауру тьмы.  Золотые рукояти увиты темными " << endl;
					cout << "кожаным шнуром, который служит напоминанием о безумии, поглотившем его великого создателя." << endl << endl;
					cout << "Этот меч стал свидетелем бесчисленных сражений и погружен в самые мраки человеческой души. Поговаривают, что  владелец" << endl;
					cout << "меча становится неизбежно пронизанным тьмой, впитывая в себя все темные силы, что когда-то затмили свет.Познав глубины" << endl;
					cout << "безумия этот древний король владел оружием , способным оживить самые мрачные страхи и поглотить весь свет в мире." << endl;
					cout << endl;
					cout << ">>>"; cin >> sign;
					switch (sign)
					{
					case 'a':
						if (hero.GetMoney() >= 100)
						{
							hero.NewSword("Меч из Черного железа", 55);
							hero.SetMoney(100);
						}
						else
						{
							cout << endl;
							cout << "У вас недостаточно средств. " << endl;
							Sleep(2);
						}
						break;
					case'b':
						if (hero.GetMoney() >= 150 && diamonds.GetQuantity() >= 1)
						{
							hero.NewSword("Меч Королевского Гвардейца", 80);
							hero.SetMoney(150);
							diamonds.SetDiamonds(1);							
						}
						else
						{
							cout << endl;
							cout << "У вас недостаточно средств. " << endl;
							Sleep(2);							
						}
					case'c':
						if (hero.GetMoney() >= 200 && hero.GetMonsterSouls())
						{
							hero.NewSword("Теневой Меч Призрака", 105);
							hero.SetMoney(200);
							hero.MonsterSoulsOrder(5);							
						}
						else
						{
							cout << endl;
							cout << "У вас недостаточно средств. " << endl;
							Sleep(2);
						}
						break;
					case'd':
						if (hero.GetMoney() >= 200 && diamonds.GetQuantity() >= 5)
						{
							hero.NewSword("Меч Звездного Ветра", 115);
							hero.SetMoney(200);
							diamonds.SetDiamonds(5);
						}
						else
						{
							cout << endl;
							cout << "У вас недостаточно средств. " << endl;
							Sleep(2);
						}
						break;
					case'e':
						if (hero.DarkSoul())
						{
							hero.NewSword("Властитель теней: Меч легендарного короля", 199);
						}
						else
						{
							cout << endl;
							cout << "У вас недостаточно средств. " << endl;
							Sleep(2);
						}
						break;
					default:
						cout << endl;
						cout << "Очень жаль что вам ничего не подошло. До новых встреч!" << endl;
						Sleep(2);
						break;
					}
				}
				else if (sign == 'b' || sign == 'B')
				{
					system("cls");
					cout << "a) --- Броня из Черных пластин(100 золотых) ---\n";
					cout << "Броня которую носили рыцари древней цивилизации, очень древняя  но  все  еще  крепкая, неподдающаяся времени и гниению." << endl << endl;
					cout << "b) --- Броня Королевского Гвардейца(150 золотых, 1 бриллиант) ---\n";
					cout << "Броня могущественного и благородного воина, Королевского гвардейца,найденого на полях битвы. Выкована из лучшей  стали." << endl << endl;
					cout << "c) >>> Теневой Доспех Призрака(200 золотых, 5 душ монстров) <<<\n";
					cout << "Эта броня выполнена из призрачного металла, пропитанного теневой энергией. При ударе от  нее  отскакивает сгусток тени, " << endl;
					cout << "а владелец может использовать ее для невидимых атак.  Сказано, что  доспехи способны взаимодействовать с душами умерших" << endl << endl;
					cout << "d) >>> Доспехи Звездной Пыли(200 золотых, 5 бриллиантов) <<<\n";
					cout << "Эта удивительная броня была сделана из звездных материалов. При контакте с доспехами она блестит светом  далеких  звезд" << endl;
					cout << "обдувая рыцаря ветром. Пассивный эффект: поднимает множитель брони от ловкости в  x2  за счет потока ветра вокруг героя" << endl << endl;
					cout << "e) <<<-->>> Мракоплетенные доспехи легендарного короля(Душа Тьмы) <<<-->>>\n";
					cout << "Эти доспехи, созданные во времена,где тьма и безумие плели свои нити вместе,обрамлены таинственным обаянием  и угрозой" << endl;
					cout << "Каждая латунная пластина этого доспеха словно пропитана мраком,и золотые узоры,переплетающиеся вдоль кирасы,напоминают" << endl;
					cout << "о вихре теней. Носитель Мракоплетеных Доспехов чувствует, как тьма и безумие становятся частью его сущности.  Капюшон," << endl;
					cout << "окаймленный золотом, скрывает лицо воина, создавая впечатление вечного мрака, из которого даже свету нету дороги назад" << endl;
					cout << "Эти доспехи не просто защищают своего владельца от ударов, они становятся частью его самого существа,  придавая силу в" << endl;
					cout << "порыве безумия. Те, кто осмеливается стать носителем Мракоплетеных Доспехов, погружаются во мрак навсегда. " << endl;
					cout << endl;
					cout << ">>>"; cin >> sign;
					switch (sign)
					{
					case 'a':
						if (hero.GetMoney() >= 100)
						{
							hero.NewArmor("Броня из Черных пластин", 15, 20, 7, 7);
							hero.SetMoney(100);
						}
						else
						{
							cout << endl;
							cout << "У вас недостаточно средств. " << endl;
							Sleep(2);
						}
						break;
					case'b':
						if (hero.GetMoney() >= 150 && diamonds.GetQuantity() >= 1)
						{
							hero.NewArmor("Броня Королевского Гвардейца", 30, 45, 15, 15);
							hero.SetMoney(150);
							diamonds.SetDiamonds(1);
						}
						else
						{
							cout << endl;
							cout << "У вас недостаточно средств. " << endl;
							Sleep(2);
						}
						break;
					case'c':
						if (hero.GetMoney() >= 200 && hero.GetMonsterSouls())
						{
							hero.NewArmor("Теневой Доспех Призрака", 38, 58, 20, 20);
							hero.SetMoney(200);
							hero.MonsterSoulsOrder(5);
						}
						else
						{
							cout << endl;
							cout << "У вас недостаточно средств. " << endl;
							Sleep(2);
						}
						break;
					case'd':
						if (hero.GetMoney() >= 200 && diamonds.GetQuantity() >= 5)
						{
							hero.NewArmor("Доспехи Звездной Пыли", 34, 55, 18, 18);
							hero.SetMoney(200);
							diamonds.SetDiamonds(5);
						}
						else
						{
							cout << endl;
							cout << "У вас недостаточно средств. " << endl;
							Sleep(2);
						}
						break;
					case'e':
						if (hero.DarkSoul())
						{
							hero.NewArmor("Мракоплетенные доспехи легендарного короля", 65, 80, 45, 45);
						}
						else
						{
							cout << endl;
							cout << "У вас недостаточно средств. " << endl;
							Sleep(2);
						}
						break;
					default:
						cout << endl;
						cout << "Очень жаль что вам ничего не подошло. До новых встреч!" << endl;
						Sleep(2);
						break;
					}
				}
				else if (sign == 'c' || sign == 'C')
				{
					system("cls");
					cout << "a) --- Огненный Шар(50 золотых, 1 бриллиант) ---\n";
					cout << "Выпускает шар огня в противника. Самое простое из атакующий заклинаний" << endl << endl;
					cout << "b) --> Среднее Исциление(100 золотых, 2 бриллиант) <--\n";
					cout << "Исцеление средный силы. Затягивает большинство серьезных ран, восстанавливает силы." << endl << endl;
					cout << "c) --> Шаровая Молния(100 золотых, 2 бриллианта) <--\n";
					cout << "Атакующая магия среднего уровня. Составляет серьезную угрозу и поражает большую область." << endl << endl;
					cout << "d) >>> Мощное Исцеление(150 золотых, 3 бриллиантов) <<<\n";
					cout << "Древняя, очень мощная магия.Говорят людей ее научили ангелы.Способна излечить самые страшные раны,отрастить конечности" << endl << endl;
					cout << "e) >>> Вытягивание души(Душа Тьмы) <<<\n";
					cout << "Проклятая древняя магия легендарного короля. Несет катострофическую угрозу целему королевству." << endl;
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
							cout << "У вас недостаточно средств. " << endl;
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
							cout << "У вас недостаточно средств. " << endl;
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
							cout << "У вас недостаточно средств. " << endl;
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
							cout << "У вас недостаточно средств. " << endl;
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
							cout << "У вас недостаточно средств. " << endl;
							Sleep(2);
						}
						break;
					default:
						cout << endl;
						cout << "Очень жаль что вам ничего не подошло. До новых встреч!" << endl;
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
						cout << "У вас недостаточно золота. " << endl;
						Sleep(2);
					}
				}
			}
			else if (sign == 'e' || sign == 'E')
			{
				hero.SetEndurance();
				hero.Resting();
				system("cls");
				cout << "Выносливость и здоровье полностью восстановлена." << endl;
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
				throw exception("Вы потерялись и утонули в реке. ");
			}
		}
	}
	void Priview();
	void Menu();
	void ActI();
};