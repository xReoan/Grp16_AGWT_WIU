#pragma once

class Entity
{
public:
	Entity(int hp, int meleeDef, int projectileDef);

	int gethp();
	int getmaxhp();
	
	//new code (pharrell) getter 
	int getMeleeDefense();
	int getProjectileDefense();

	bool isalive();
	void takeDamage(int damage, bool isProjectile); //check for projectile or melee damage


	//new code(pharrell) setters
	void setMeleeDefense(int meleeDef);
	void setProjectileDefense(int projectileDef);


private:
	int hp;
	int maxhp;

	//new code (pharrell)
	int meleeDefense;
	int projectileDefense;
};