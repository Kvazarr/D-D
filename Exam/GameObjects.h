#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;


class Souls
{
protected:
	int monstersSouls;
	bool darkSoul;
	bool bloodySoul;
	bool saintSoul;
public:
	Souls() :monstersSouls(0), darkSoul(false), bloodySoul(false), saintSoul(false) {}

	void Show()const
	{
		cout << "<><><><>|Souls Inventory|<><><><>" << endl;
		cout << "< Monsters souls: " << monstersSouls << endl;
		cout << "< Soul of Bloody red Dragon: " << bloodySoul << endl;
		cout << "< Saint souls of the thousand - faced apostol: " << saintSoul << endl;
		cout << "< Soul of Darkness: " << darkSoul << endl;
		cout << "<><><><><><><><><><><><><><><><>" << endl;
	}
	int GetMonsterSouls()const
	{
		return monstersSouls;
	}
	int UpMonsterSouls()
	{
		return monstersSouls++;
	}
};


class Spell
{
protected:
	string spellName;
	int healingSpell;
	int damageSpell;
public:
	Spell():spellName("No data"), healingSpell(0), damageSpell(0){}
	Spell(string spellName, int healing, int damage):spellName(spellName), healingSpell(healing), damageSpell(damage){}

	void Show()const
	{
		cout << "| Spell name: " << spellName << endl;
		cout << "| Spell damage: " << damageSpell << endl;
		cout << "| Spell healing: " << healingSpell << endl;
	}
	int GetHeal()const
	{
		return healingSpell;
	}
	int GetDamage()const
	{
		return damageSpell;
	}
};


class Weapon
{
protected:
	string nameWeapon;
	int damageWeapon;
public:
	Weapon():nameWeapon ("No data"), damageWeapon(0){}
	Weapon(string name, int damage):nameWeapon (name), damageWeapon(damage){}

	void Show()const
	{
		cout << "| Name of sword: " << nameWeapon << endl;
		cout << "| Damage of sword: "<< damageWeapon << endl;
	}
	int GetDamageWeapon()const
	{
		return damageWeapon;
	}
};


class Armor
{
protected:
	string nameArmor;
	int helm;
	int corset;
	int gloves;
	int greaves;
	int total;
public:
	Armor():nameArmor("No data"), helm(0), corset(0), gloves(0), greaves(0), total(helm + corset + gloves + greaves){}
	Armor(string name, int helm, int corset, int gloves, int greaves) : nameArmor(name), helm(helm), corset(corset),
		gloves(gloves), greaves(greaves), total(helm + corset + gloves + greaves) {}

	void Show()const
	{
		cout << "| Name of armor: " << nameArmor << endl;
		cout << "| Total defence value: " << total << endl;
	}
	int GetDefence()const
	{
		return total;
	}
};


class Shield
{
protected:
	string nameShield;
	int defenceShield;
public:
	Shield():nameShield("No data"), defenceShield(0){}
	Shield(string name, int defence):nameShield(name), defenceShield(defence){}

	void Show()const
	{
		cout << "| Name of Shield: " << nameShield << endl;
		cout << "| Defence value: " << defenceShield << endl;
	}
	int GetDefend()const
	{
		return defenceShield;
	}
};


class Units
{
protected:
	string name;
	int hp;
	int endurance;
	int damage;
	int lvl;
	int strength;
	int intelligence;
	int agility;
	int defence;
public:
	Units():name("No data"), hp(0), lvl(0), endurance(0), strength(0), intelligence(0), agility(0),damage(0), defence(0){}
	Units(string name, int hp, int damage, int lvl, int endurance, int strength, int intelligence, int agility, int defence) :name(name),
		hp(hp),damage(damage), lvl(lvl), strength(strength), intelligence(intelligence), agility(agility), defence(defence), endurance(endurance){}

	virtual void Show()const
	{
		cout << " -------------------------------------" << endl;
		cout << "| -=-=-=-=->Characteristics<-=-=-=-=-" << endl;
		cout << "| Name: " << name << endl;
		cout << "| LVL: " << lvl << endl;
		cout << "| HP: " << hp << endl;
		cout << "| Damage: " << damage << endl;
		cout << "| Endurance: " << endurance << endl;
		cout << "| Str:" << strength << endl;
		cout << "| Agl: " << agility << endl;
		cout << "| Int: " << intelligence << endl;
		cout << "| Def: " << defence<< endl;
	}
	virtual bool IsAlive()const = 0;
	virtual int GetHP()const = 0;
	virtual int GetLvl()const = 0;
	/*virtual string GetSpell()const = 0;*/
	virtual string GetName()const = 0;
	virtual int GetEndurance()const = 0;
	virtual int GetIntl()const = 0;
	virtual int Attack()const = 0;
	virtual int AttackSpell() = 0;
	virtual void SetDamage() = 0;
	virtual void SetDefence() = 0;
	virtual void SetSpell(int choice) = 0;
	virtual void SetEnduranceNegative() = 0;
	virtual void SetEndurancePositive() = 0;
	virtual void WithdrawHP(int damage) = 0;
	virtual void Defend()const = 0;
	
};


class Hero :public Units, public Weapon, public Armor, public Shield, public Spell, public Souls
{
private:
	vector<Spell> spells;
	Souls souls;
	Weapon sword;
	Armor armor;
	Shield shield;
	Spell spell;
	int money;
public:
	Hero():Units(), money(0){}
	Hero(string name, Spell& spell, int lvl, int damage, int endurance, int hp, int str, int agl, int intl, int def, Weapon& sword, Armor& armor, Shield& shield)
		:Units(name, hp, damage, lvl, endurance, str, intl, agl, def), spell(spell), sword(sword), armor(armor), shield(shield), money(0)
	{
		spells.push_back(Spell("Easy treatment", 100, 0));
		spells.push_back(Spell("Medium treatment", 500, 0));
		spells.push_back(Spell("Extra treatment", 1000, 0));
		spells.push_back(Spell("Fireball", 0, 100));
		spells.push_back(Spell("Ball lightning", 0, 350));
		spells.push_back(Spell("Soul snatching", 0, 1090));
	}

	void Show()const override
	{
		Units::Show();
		cout << "| =-=-=-=-=-=->Equipment<-=-=-=-=-=-=" << endl;
		cout << "| <---Sword--->" << endl;
		sword.Show();
		cout << "| _-_Armor_-_" << endl;
		armor.Show();
		cout << "| /-/Shield\\-\\" << endl;
		shield.Show();
		cout << "| -->Spell<--" << endl;
		spell.Show();
		souls.Show();
	}
	void SetDamage() override
	{
		damage = damage + sword.GetDamageWeapon() + strength + souls.GetMonsterSouls();
	}
	void SetDefence() override
	{
		defence = defence + armor.GetDefence() + agility / 2;
	}
	void SetSpell(int choice)override
	{
		if (choice > 0 && choice < 7)
			spell = spells[choice-1];
		else
		{
			throw out_of_range("Wrond index!");
		}
	}
	void SetEndurance()
	{
		endurance = 10;
	}
	void SetEndurancePositive() override
	{
		if(endurance<10)
			endurance++;
	}
	void SetEnduranceNegative() override
	{
		if(endurance>0)
			endurance--;
	}
	void SetMonsterSouls()
	{
		souls.UpMonsterSouls();
	}
	void WithdrawHP(int damage) override
	{
		hp = hp - (damage - defence);
	}
	void HeroLvlUp(int lvls)
	{
		lvl = lvl + lvls;
	}
	void SetLvl()
	{
		strength = strength + lvl * 2;
		agility = agility + lvl * 2;
		intelligence = intelligence + lvl * 2;
	}
	bool IsAlive()const override
	{
		return hp > 0;
	}
	int GetHP()const override
	{
		return hp;
	}
	int GetLvl()const override
	{
		return lvl;
	}
	int GetEndurance()const override
	{
		return endurance;
	}
	int GetIntl()const override
	{
		return intelligence;
	}
	string GetName()const override
	{
		return name;
	}
	int Attack()const override
	{
		cout << "Attacking with " << damage << " damage" << endl;
		return damage;
	}
	int AttackSpell() override
	{
		if (spell.GetHeal() > 0)
		{
			cout << "The healing spell restores " << spell.GetHeal() + intelligence + souls.GetMonsterSouls() * 2 << " HP" << endl;
			hp = hp + spell.GetHeal() + intelligence;
			return spell.GetHeal() + intelligence + souls.GetMonsterSouls() * 2;
		}
		else
		{
			cout << "The spell does " << spell.GetDamage() + intelligence + souls.GetMonsterSouls() * 2 << " magic damage" << endl;
			return spell.GetDamage() + intelligence + souls.GetMonsterSouls() * 2;
		}
	}
	void Defend()const override
	{
		cout << "Hero rises his shield and up defence to " << defence + shield.GetDefend() << endl;
	}
	void AfterMine(int time)
	{
		if (time >= endurance)
			endurance -= time;
		else
		{
			endurance = 0;
		}
	}
	/*Spell GetSpell()const override
	{
		return spell;
	}*/
};


class Enemy :public Units, public Weapon, public Armor, public Shield, public Spell
{
protected:
	Weapon weapon;
	Armor armor;
	Spell spell;
	string power;
public:
	Enemy() :Units(), power("No data") {}
	Enemy(string name, Spell& spell, int lvl, int damage, int endurance, int hp, int str, int agl, int intl, int def, Weapon& weapon, Armor& armor, string power)
		:Units(name, hp, damage, lvl, endurance, str, intl, agl, def), spell(spell), weapon(weapon), power(power), armor(armor) {}

	void Show()const override
	{
		Units::Show();
		cout << "| =-=-=-=-=-=-=->Power<-=-=-=-=-=-=-=" << endl;
		cout << "| Power: " << power << endl;
		cout << "| =-=-=-=-=-=-=->Weapon<-=-=-=-=-=-=-=" << endl;
		weapon.Show();
		cout << "| =-=-=-=-=-=-=->Armor<-=-=-=-=-=-=-=" << endl;
		armor.Show();
		cout << "| =-=-=-=-=-=-=->Spell<-=-=-=-=-=-=-=" << endl;
		spell.Show();
		cout << " -------------------------------------" << endl;
	}
};


class Boss :public Enemy
{
private:
	vector <Spell> spells;
	string rage;
public:
	Boss(): Enemy(), rage("No data"){}
	Boss(string name, Spell& spell, int lvl, int damage, int endurance, int hp, int str, int agl, int intl, int def, Weapon& weapon, Armor& armor, string power, string rage)
		:Enemy(name, spell, lvl, damage, endurance, hp, str, agl, intl, def, weapon, armor, power), rage(rage)
	{
		spells.push_back(Spell("Easy treatment", 100, 0));
		spells.push_back(Spell("Medium treatment", 500, 0));
		spells.push_back(Spell("Extra treatment", 1000, 0));
		spells.push_back(Spell("Fireball", 0, 100));
		spells.push_back(Spell("Ball lightning", 0, 350));
		spells.push_back(Spell("Soul snatching", 0, 1090));
	}

	void Show()const override
	{
		Enemy::Show();
		cout << ">>>RAGE MODE: " << rage << endl;
	}
	void SetDamage() override
	{
		damage = damage + weapon.GetDamageWeapon() + strength;
	}
	void SetDefence() override
	{
		defence = defence + armor.GetDefence() + agility / 2;
	}
	void SetSpell(int choice)override
	{
		if (choice > 0 && choice < 7)
			spell = spells[choice - 1];
		else
		{
			throw out_of_range("Wrond index!");
		}
	}
	void SetEndurancePositive() override
	{
		if (endurance < 10)
			endurance++;
	}
	void SetEnduranceNegative() override
	{
		if (endurance > 0)
			endurance--;
	}
	void WithdrawHP(int damage) override
	{
		hp = hp - (damage - defence);
	}
	bool IsAlive()const override
	{
		return hp > 0;
	}
	int Attack()const override
	{
		cout << "Attacking with " << damage << " damage" << endl;
		return damage;
	}
	int AttackSpell() override
	{
		if (spell.GetHeal() > 0)
		{
			cout << "The healing spell restores " << spell.GetHeal() + intelligence << " HP" << endl;
			hp = hp + spell.GetHeal() + intelligence;
			return spell.GetHeal() + intelligence;
		}
		else
		{
			cout << "The spell does " << spell.GetDamage() + intelligence << " magic damage" << endl;
			return spell.GetDamage() + intelligence;
		}
	}
	void Defend()const override
	{
		cout << "The opponent regains stamina and raises defense by " << defence + defence / 2 << endl;
	}
	int GetHP()const override
	{
		return hp;
	}
	int GetLvl()const override
	{
		return lvl;
	}
	int GetEndurance()const override
	{
		return endurance;
	}
	int GetIntl()const override
	{
		return intelligence;
	}
	/*Spell GetSpell()const override
	{
		return spell;
	}*/
	string GetName()const override
	{
		return name;
	}
};


class Monster :public Enemy
{
private:
	vector<Spell> spells;
public:
	Monster():Enemy(){}
	Monster(string name, Spell& spell, int lvl, int damage, int endurance, int hp, int str, int agl, int intl, int def, Weapon& weapon, Armor& armor,  string power)
		:Enemy(name, spell, lvl, damage, endurance, hp, str, agl, intl, def, weapon, armor, power)
	{
		spells.push_back(Spell("Easy treatment", 100, 0));
		spells.push_back(Spell("Medium treatment", 500, 0));
		spells.push_back(Spell("Extra treatment", 1000, 0));
		spells.push_back(Spell("Fireball", 0, 100));
		spells.push_back(Spell("Ball lightning", 0, 350));
		spells.push_back(Spell("Soul snatching", 0, 1090));
	}

	void Show()const override
	{
		Enemy::Show();
	}
	void SetDamage() override
	{
		damage = damage + weapon.GetDamageWeapon() + strength;
	}
	void SetDefence() override
	{
		defence = defence + armor.GetDefence() + agility / 2;
	}
	void SetSpell(int choice)override
	{
		if (choice > 0 && choice < 7)
			spell = spells[choice - 1];
		else
		{
			throw out_of_range("Wrond index!");
		}
	}
	void SetEndurancePositive() override
	{
		if (endurance < 10)
			endurance++;
	}
	void SetEnduranceNegative() override
	{
		if (endurance > 0)
			endurance--;
	}
	void WithdrawHP(int damage) override
	{
		hp = hp - (damage - defence);
	}
	bool IsAlive()const override
	{
		return hp > 0;
	}
	int Attack()const override
	{
		cout << "Attacking with " << damage << " damage" << endl;
		return damage;
	}
	int AttackSpell() override
	{
		if (spell.GetHeal() > 0)
		{
			cout << "The healing spell restores " << spell.GetHeal() + intelligence << " HP" << endl;
			hp = hp + spell.GetHeal() + intelligence;
			return spell.GetHeal() + intelligence;
		}
		else
		{
			cout << "The spell does " << spell.GetDamage() + intelligence << " magic damage" << endl;
			return spell.GetDamage() + intelligence;
		}
	}
	void Defend()const override
	{
		cout << "The opponent regains stamina and raises defense by " << defence + defence / 2 << endl;
	}
	int GetHP()const override
	{
		return hp;
	}
	int GetLvl()const override
	{
		return lvl;
	}
	int GetEndurance()const override
	{
		return endurance;
	}
	int GetIntl()const override
	{
		return intelligence;
	}
	/*Spell GetSpell()const override
	{
		return spell;
	}*/
	string GetName()const override
	{
		return name;
	}
};


class Resources
{
protected:
	int quantity;
public:
	Resources():quantity(0){}

	virtual void Show()const = 0;
};


class Gold :public Resources
{
public:
	Gold():Resources(){}

	void Show()const override
	{
		cout << "Quantity of gold: " << quantity << endl;
	}
	void UpGoldCount(int count)
	{
		quantity += count;
	}
};


class Coins :public Gold
{
public:
	Coins():Gold(){}

	void Show()const override
	{
		cout << "Quantity of coins: " << quantity << endl;
	}
};


class Diamonds :public Resources
{
public:
	Diamonds():Resources(){}

	void Show()const override
	{
		cout << "Quantity of diamonds: " << quantity << endl;
	}
	int DiamondsUpCount()
	{
		return quantity++;
	}
};