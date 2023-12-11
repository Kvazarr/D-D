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
public:
	Souls() :monstersSouls(0), darkSoul(false) {}

	void Show()const
	{
		cout << "| <><><>|Souls Inventory|<><><><>" << endl;
		cout << "| Monsters souls: " << monstersSouls << endl;
		cout << "| Soul of Darkness: " << darkSoul << endl;
		cout << "| <><><><><><><><><><><><><><><>" << endl;
	}
	int GetMonstersSouls()const
	{
		return monstersSouls;
	}
	void SetMonstersSouls(int price)
	{
		monstersSouls -= price;
	}
	int UpMonsterSouls()
	{
		return monstersSouls++;
	}
	bool GetDarkSoul()const
	{
		return darkSoul > 0;
	}
	void DarkSoulUp()
	{
		darkSoul = true;
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
	string GetName()const
	{
		return spellName;
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
	void SetNewSword(string name, int damage)
	{
		nameWeapon = name;
		damageWeapon = damage;
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
	void SetNewArmor(string name, int helm, int corset, int gloves, int greaves)
	{
		nameArmor = name;
		this->helm = helm;
		this->corset = corset;
		this->gloves = gloves;
		this->greaves = greaves;
		total = 0;
		total = total + helm, corset, gloves, greaves;
	}
	int GetHelmDef()const
	{
		return helm;
	}
	int GetCorsetDef()const
	{
		return corset;
	}
	int GetGlovesDef()const
	{
		return corset;
	}
	int GetGreavesDef()const
	{
		return greaves;
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
	virtual string GetName()const = 0;
	virtual int GetEndurance()const = 0;
	virtual int GetIntl()const = 0;
	virtual int Attack()const = 0;
	virtual int AttackSpell() = 0;
	virtual void HealingSpell() = 0;
	virtual void SetDamage() = 0;
	virtual void SetDefence() = 0;
	virtual void SetSpell(int choice) = 0;
	virtual void SetEnduranceNegative() = 0;
	virtual void SetEndurancePositive() = 0;
	virtual void WithdrawHP(int damage) = 0;
	virtual void PointsWithdrawHP(int damage) = 0;
	virtual void Defend() = 0;
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
		cout << "| <---Armor--->" << endl;
		armor.Show();
		cout << "| <---Shield--->" << endl;
		shield.Show();
		cout << "| <---Spell--->" << endl;
		spell.Show();
		cout << " -------------------------------------" << endl;
	}
	void SoulsInventory() const
	{
		souls.Show();
	}
	void SetDamage() override
	{
		damage = 65;
		damage = damage + sword.GetDamageWeapon() + strength + souls.GetMonstersSouls();
	}
	void SetDefence() override
	{
		defence = 5;
		defence = defence + armor.GetDefence() + agility;
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
	void MonsterSoulsOrder(int price)
	{
		souls.SetMonstersSouls(price);
	}
	bool DarkSoul()const
	{
		return souls.GetDarkSoul();
	}
	void GainDarkSous()
	{
		souls.DarkSoulUp();
	}
	void SetMoney(int price)
	{
		money -= price;
	}
	void Exchange()
	{
		money += 2;
	}
	void WithdrawHP(int damage) override
	{
		if(damage>0 && damage>= defence)
			hp = hp - (damage - defence);
	}
	void PointsWithdrawHP(int damage) override
	{
		int temp = damage - defence;
		cout << "Damage: " << temp << endl;
	}
	void HeroLvlUp(int lvls)
	{
		lvl = lvl + lvls;
		SetLvl();
		SetDamage();
	}
	void SetLvl()
	{
		strength = strength + 2;
		agility = agility + 2;
		intelligence = intelligence + 2;
		hp = hp + 150;
	}
	void Resting()
	{
		hp = 150;
		for (int i = 1; i < lvl; i++)
		{
			hp += 150;
		}
	}
	bool IsAlive()const override
	{
		return hp > 0;
	}
	int GetHeroDamage()const
	{
		return damage;
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
	int GetStr()const
	{
		return strength;
	}
	int GetAgl()const
	{
		return agility;
	}
	string GetName()const override
	{
		return name;
	}
	int GetMoney()const
	{
		return money;
	}
	int GetMonsterSouls()const
	{
		return souls.GetMonstersSouls();
	}
	int GetHelm()const
	{
		return armor.GetHelmDef();
	}
	int GetCorset()const
	{
		return armor.GetCorsetDef();
	}
	int GetGloves()const
	{
		return armor.GetGlovesDef();
	}
	int GetGreaves()const
	{
		return armor.GetGreavesDef();
	}
	int GetHeroWeaponDamage()const
	{
		return sword.GetDamageWeapon();
	}
	int GetHeroHeal()const
	{
		return spell.GetHeal();
	}
	int GetHeroMagicDamage()const
	{
		return spell.GetDamage() + damage + intelligence;
	}
	int Attack()const override
	{
		return damage;
	}
	int GetHeroDefence()const
	{
		return defence;
	}
	int AttackSpell() override
	{
		cout << "The spell does " << spell.GetDamage() + intelligence + souls.GetMonstersSouls() * 2 << " magic damage" << endl;
		return spell.GetDamage() + intelligence + souls.GetMonstersSouls() * 2;
	}
	void HealingSpell() override
	{
		cout << "The healing spell restores " << spell.GetHeal() + intelligence + souls.GetMonstersSouls() * 2 << " HP" << endl;
		hp = hp + spell.GetHeal() + intelligence;
	}
	void Defend() override
	{
		defence = defence + shield.GetDefend();
		cout << "Hero rises his shield and up defence to " << defence + shield.GetDefend() << endl;
	}
	void AfterMine(int time)
	{
		if (time <= endurance)
			endurance -= time;
		else
		{
			endurance = 0;
		}
	}
	void NewSword(string name, int damageSword)
	{
		sword.SetNewSword(name, damageSword);
		damage = damage + sword.GetDamageWeapon();
	}
	void NewArmor(string name, int helm, int corset, int gloves, int greaves)
	{
		armor.SetNewArmor(name, helm, corset, gloves, greaves);
		defence = defence + armor.GetDefence();
	}
	void NewSpell(string name)
	{
		for (int i = 0; i < spells.size(); i++)
		{
			if (name == spells[i].GetName())
			{
				spell = spells[i];
			}
		}
	}
};


class Enemy :public Units, public Weapon, public Armor, public Shield, public Spell
{
protected:
	Weapon weapon;
	Armor armor;
	Spell spell;
public:
	Enemy() :Units() {}
	Enemy(string name, Spell& spell, int lvl, int damage, int endurance, int hp, int str, int agl, int intl, int def, Weapon& weapon, Armor& armor)
		:Units(name, hp, damage, lvl, endurance, str, intl, agl, def), spell(spell), weapon(weapon), armor(armor) {}

	void Show()const override
	{
		Units::Show();
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
public:
	Boss(): Enemy(){}
	Boss(string name, Spell& spell, int lvl, int damage, int endurance, int hp, int str, int agl, int intl, int def, Weapon& weapon, Armor& armor)
		:Enemy(name, spell, lvl, damage, endurance, hp, str, agl, intl, def, weapon, armor)
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
		defence = 45;
		defence = defence + armor.GetDefence() + agility;
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
		if (damage > 0 && damage >= defence)
			hp = hp - (damage - defence);
	}
	void PointsWithdrawHP(int damage) override
	{
		int temp = damage - defence;
		cout << "Damage: " << temp << endl;
	}
	bool IsAlive()const override
	{
		return hp > 0;
	}
	int Attack()const override
	{
		return damage;
	}
	int AttackSpell() override
	{
		cout << "The spell does " << spell.GetDamage() + intelligence << " magic damage" << endl;
		return spell.GetDamage() + intelligence;
	}
	void HealingSpell() override
	{
		cout << "The healing spell restores " << spell.GetHeal() + intelligence << " HP" << endl;
		hp = hp + spell.GetHeal() + intelligence;
	}
	void Defend() override
	{
		defence += defence / 2;
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
	string GetName()const override
	{
		return name;
	}
	int GetBossMagicDamage()const
	{
		return spell.GetDamage();
	}
	int CheckRage()const
	{
		return hp / 10;
	}
	void RageMode()
	{
		cout << "RAGE MODE" << endl;
		hp * 2;
		damage * 1.5;
		strength += 30;
		agility += 30;
		intelligence += 30;
	}
	int GetBossDamage()const
	{
		return damage;
	}
};


class Monster :public Enemy
{
private:
	vector<Spell> spells;
public:
	Monster():Enemy(){}
	Monster(string name, Spell& spell, int lvl, int damage, int endurance, int hp, int str, int agl, int intl, int def, Weapon& weapon, Armor& armor)
		:Enemy(name, spell, lvl, damage, endurance, hp, str, agl, intl, def, weapon, armor)
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
		damage = 65;
		damage = damage + weapon.GetDamageWeapon() + strength;
	}
	void SetDefence() override
	{
		defence = 5;
		defence = defence + armor.GetDefence() + agility;
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
		if (damage > 0 && damage >= defence)
			hp = hp - (damage - defence);
	}
	void PointsWithdrawHP(int damage) override
	{
		int temp = damage - defence;
		cout << "Damage: " << temp << endl;
	}
	bool IsAlive()const override
	{
		return hp > 0;
	}
	int Attack()const override
	{
		return damage;
	}
	int AttackSpell() override
	{
		cout << "The spell does " << spell.GetDamage() + intelligence << " magic damage" << endl;
		return spell.GetDamage() + intelligence;
	}
	void HealingSpell() override
	{
		cout << "The healing spell restores " << spell.GetHeal() + intelligence << " HP" << endl;
		hp = hp + spell.GetHeal() + intelligence;
	}
	void Defend() override
	{
		defence += defence / 2;
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
	string GetName()const override
	{
		return name;
	}
	int GetMonsterDamage()const
	{
		return damage;
	}
	int GetMonsterHeal()const
	{
		return spell.GetHeal();
	}
	int GetMonsterMagicDamage()const
	{
		return spell.GetDamage();
	}
};


class Resources
{
protected:
	int quantity;
public:
	Resources():quantity(0){}

	virtual void Show()const = 0;
	virtual int GetQuantity()const = 0;
};


class Gold :public Resources
{
public:
	Gold():Resources(){}

	void Show()const override
	{
		cout << "| Quantity of gold: " << quantity << endl;
	}
	void UpGoldCount(int count)
	{
		quantity += count;
	}
	int GetQuantity()const override
	{
		return quantity;
	}
	void Exchange()
	{
		quantity--;
	}
};


class Diamonds :public Resources
{
public:
	Diamonds():Resources(){}

	void Show()const override
	{
		cout << "| Quantity of diamonds: " << quantity << endl;
	}
	int DiamondsUpCount()
	{
		return quantity++;
	}
	int GetQuantity()const override
	{
		return quantity;
	}
	void SetDiamonds(int price)
	{
		quantity -= price;
	}
};