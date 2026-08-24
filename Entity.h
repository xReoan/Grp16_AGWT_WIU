#pragma once

class Entity
{
public:
	Entity(int hp, int meleeAtk, int projectileAtk, int meleeDef, int projectileDef);

	int gethp();
	int getmaxhp();
	
	//new code (pharrell) getter 
	int getMeleeAttack();
	int getProjectileAttack();
	int getMeleeDefense();
	int getProjectileDefense();

	bool isalive();
	void takeDamage(int damage); 


	//new code(pharrell) setters
	void setMeleeAttack(int meleeAtk);
	void setProjectileAttack(int projectileAtk);
	void setMeleeDefense(int meleeDef);
	void setProjectileDefense(int projectileDef);
	void sethp(int newhp);


private:
	int hp;
	int maxhp;

	//new code (pharrell)
	int meleeAttack;
	int projectileAttack;
	int meleeDefense;
	int projectileDefense;
};