#include<iostream>
#include<locale>
#include"Story.h";
#include"GameObjects.h";
using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	setlocale(LC_ALL, "russian");
	string heroName;
	cout << "Enter your name, hero: "; cin >> heroName;

	Story start(heroName);
	start.Menu();
	start.Priview();
	start.ActI();
}