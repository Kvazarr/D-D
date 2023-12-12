#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
#include"Story.h";
using namespace std;


void Story::Gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void Story::Menu()
{
    system("cls");
    int menu_item = 0, x = 11;
    bool running = true;

    Gotoxy(54, x); cout << "->";

    while (running)
    {
        Gotoxy(56, 11);  cout << "Start";
        Gotoxy(56, 12);  cout << "Exit";

        system("pause>nul");

        if (GetAsyncKeyState(VK_DOWN))
        {
            Gotoxy(54, x); cout << "  ";
            x < 12 ? x++ : x = 11;
            Gotoxy(54, x); cout << "->";
            menu_item < 1 ? menu_item++ : menu_item = 0;
            continue;

        }
        if (GetAsyncKeyState(VK_UP))
        {
            Gotoxy(54, x); cout << "  ";
            x > 11 ? x-- : x = 12;
            Gotoxy(54, x); cout << "->";
            menu_item > 0 ? menu_item-- : menu_item = 1;
            continue;
        }
        if (GetAsyncKeyState(VK_RETURN))
        {
            switch (menu_item)
            {
            case 0:
                running = false;
                break;
            case 1:
                system("cls");
                cout << "Good bye.\n\n";
                exit(EXIT_SUCCESS);
            }
        }
    }
}


void Story::Priview()
{
    system("cls");
    cout << "\n\n\n" << endl;
    cout << setw(81) << "**********************************************" << endl;
    cout << setw(81) <<"*                                            *" << endl;
    cout << setw(81) <<"*            DUNGEONS & DRAGONS              *" << endl;
    cout << setw(81) <<"*                                            *" << endl;
    cout << setw(81) <<"**********************************************" << endl;
    cout << setw(78) <<"  _________________________________________" << endl;
    cout << setw(79) <<" |  _____________________________________  |" << endl;
    cout << setw(79) <<" | |                                     | |" << endl;
    cout << setw(79) <<" | |  Welcome to the world of adventure! | |" << endl;
    cout << setw(79) <<" | |  Grab your dice and embark on a     | |" << endl;
    cout << setw(79) <<" | |  journey full of magic and monsters.| |" << endl;
    cout << setw(79) <<" | |_____________________________________| |" << endl;
    cout << setw(79) <<" |_________________________________________|" << endl;
    cout << "\n\n";
    cout << "                                    ";
    system("pause");
    system("cls");
}
void Story::ActI()
{
    system("cls");
    cout << "\n\n\n\n\n\n";
    string line("===== Act I: Shadows of the Past =====");
    CenterText(line);
    cout << "\n\n";
    cout << "   The protagonist, a brave adventurer, ventures into the caverns of a forgotten dungeon in search of treasure and glory."<<endl;
    cout << "   In dusty corridors,he discovers an ancient scroll that reveals the riddle of the awakening of an ancient dark soul.The" << endl;
    cout << "   clues on the scroll lead the hero deeper into the dungeon, where he encounters the ghosts of the past,guardians of the" << endl;
    cout << "   forgotten secrets of ancient. " << endl;
    cout << endl;
    cout << "   In dark labyrinths,  the  hero finds the remains of old civilizations covered with the cobwebs of time. Here,  ancient" << endl;
    cout << "   mechanisms are recovering from their long sleep, creating shadowy maneuvers and traps. Shadows bend  and  bounce along" << endl;
    cout << "   the walls. The first battle ahead." << endl;
    cout << "\n\n";
    cout << "                                         ";
    system("pause");
    system("cls");
    cout << endl;
    cout << "    You have encountered your first monster in the game.Combat takes place until either the player or the monster has" << endl;
    cout << "    no HP remaining. Each round you take a turn with a choice:  attack by spending stamina. Defend and regain stamina" << endl;
    cout << "    Use a spell or drink a potion. The spell also spends stamina. On the left side of the console is  a  panel player" << endl;
    cout << "    right side of the enemy panel. You can't leave the battle, each of you is fighting to the death." << endl;
    hero.Show();
    system("pause");
    try
    {
        FirstFight();
    }
    catch (runtime_error& ex)
    {
        system("cls");
        cout << ex.what() << endl << endl;
        cout << "                                    ";
        system("pause");
        exit(EXIT_SUCCESS);
    }
    catch (exception& ex)
    {
        system("cls");
        cout << ex.what() << endl << endl;
        cout << "                                    ";
        system("pause");
        exit(EXIT_SUCCESS);
    }
    system("cls");
    cout << "\n\n";
    cout << "    After a hard victory the corridor leads the hero out of the gloom,  the  sunlight falls on his eyes making them cry out" << endl;
    cout << "    in pain, but this pain is pleasant, it makes the hero realize that he is still alive.  On the way to the dungeon, other" << endl;
    cout << "    travelers told me, that in these woods where he found himself " << hero.GetName() << " there is a village where you can" << endl;
    cout << "    find everything a warrior and wanderer needs." << endl;
    cout << endl;
    cout << "    A few hours later, the cozy village of Lost Light, lost among the dark old forests,  opens before the hero. The morning" << endl;
    cout << "    sun casts its first rays  on  the roofs of the houses, coloring them  in  warm shades. Narrow wooden paths weave amidst" << endl;
    cout << "    picturesqu houses and gardens.Near the central square stands an ancient well from which fresh water rises.The character" << endl;
    cout << "    hears the distant sounds of chicken cries and children's laughter, creating  an  atmosphere of warmth and security. The" << endl;
    cout << "    aroma of fresh bread and forest berries fill the air. The locals, in blooming robes, greet  the  hero with smiles.  The " << endl;
    cout << "    peasants labor in their fields, and the blacksmith in his workshop is busy making new implements.Along  the  street are " << endl;
    cout << "    seen merchants offering goods ranging from fresh produce  to  handmade items.  The village elders invite  the hero to a " << endl;
    cout << "    tavern where the sound of the cheerful music, and the aroma of home cooking invites everyone to dine." << endl;
    cout << endl;
    cout << "    In this safe zone, the hero can rest, resupply, and get the information he needs before going back out again embrake on" << endl;
    cout << "    a world of adventure and mystery  in the first act.  As long as evil lives  in  ancient dungeons, this land will not be" << endl;
    cout << "    peaceful. From the village you can go to the dungeon to meet the boss of the first act,go to the store and buy new gear" << endl;
    cout << "    go into the mine to get gold and jewelry or check the bulletin board and take an order for a monster, getting a reward." << endl<<endl;
    cout << "                                    ";
    system("pause");
    try
    {
        InVillage();
    }
    catch (exception& ex)
    {
        system("cls");
        cout << ex.what() << endl << endl;
        cout << "                                    ";
        system("pause");
        exit(EXIT_SUCCESS);
    }
    catch (logic_error& ex)
    {
        system("cls");
        cout << ex.what() << endl << endl;
        cout << "                                    ";
        system("pause");
        exit(EXIT_SUCCESS);
    }
}