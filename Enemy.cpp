#include "Enemy.h"

Enemy::Enemy() : Entity(0, 0, 0, 0, 0){
    meleeattack = 0;
    projectileattack = 0;
}

Enemy::Enemy(ENEMY_TYPE type, int hp, int enemyMeleeAttack, int enemyProjectileAttack, int enemyMeleeDefense, int enemyProjectileDefense)
    : Entity(hp, enemyMeleeAttack, enemyProjectileAttack, enemyMeleeDefense, enemyProjectileDefense)
{
    enemytype = type;
	meleeattack = enemyMeleeAttack;
}

Enemy::~Enemy(){}

Enemy::ENEMY_TYPE Enemy::getEnemyType() const{
    return enemytype;
}

int Enemy::getMeleeAttack() const{
    return meleeattack;
}

int Enemy::getProjectileAttack() const {
    return projectileattack;
}

bool Enemy::getsurvivorphase2() {
    return issurvivorphase2;
}

void Enemy::setEnemyType(ENEMY_TYPE type){
    enemytype = type;
}

void Enemy::setMeleeAttack(int enemyMeleeAttack){
    meleeattack = enemyMeleeAttack;
}

void Enemy::setProjectileAttack(int enemyProjectileAttack) {
    projectileattack = enemyProjectileAttack;
}

void Enemy::setsurvivorphase2(bool survivorphase2) {
    issurvivorphase2 = survivorphase2;
}

void Entity::sethp(int newhp) {
    hp = newhp;
}

CardDeck* Enemy::getdeck() {
    return &deck;
}

void Enemy::builddeck(CardDatabase* database) {
    deck.cleardeck();
    if (Enemy::getEnemyType() == ENEMY_TYPE::TUTORIAL) {
        for (int i = 25; i < 28; i++) {
            for (int a = 0; a < 2; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }
        for (int i = 52; i < 54; i++) {
            for (int a = 0; a < 2; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }
    }

    if (Enemy::getEnemyType() == ENEMY_TYPE::HENCHMEN) {
        for (int i = 25; i < 28; i++) {
            for (int a = 0; a < 2; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }
        for (int i = 52; i < 54; i++) {
            for (int a = 0; a < 2; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }
    }

    if (Enemy::getEnemyType() == ENEMY_TYPE::GUNMAN) {
        for (int i = 25; i < 31; i++) {
            for (int a = 0; a < gunmanquantities[i - 25]; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }
    }

    if (Enemy::getEnemyType() == ENEMY_TYPE::GRIM) {
        for (int i = 25; i < 28; i++) {
            for (int a = 0; a < enemyquantities[i - 25]; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }
        for (int i = 30; i < 33; i++) {
            for (int a = 0; a < grimquantities[i - 30]; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }
    }

    if (Enemy::getEnemyType() == ENEMY_TYPE::TRICKSTER) {
        for (int i = 25; i < 27; i++) {
            for (int a = 0; a < enemyquantities[i - 25]; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }
        for (int i = 34; i < 39; i++) {
            for (int a = 0; a < tricksterquantities[i - 33]; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }
    }

    if (Enemy::getEnemyType() == ENEMY_TYPE::SURVIVOR) {
        if (getsurvivorphase2() == false) {
            for (int i = 25; i < 27; i++) {
                for (int a = 0; a < enemyquantities[i - 25]; a++) {
                    deck.addcardtodraw(database->getcard(i));
                }
            }
            for (int i = 39; i < 43; i++) {
                for (int a = 0; a < survivorquantities[i - 38]; a++) {
                    deck.addcardtodraw(database->getcard(i));
                }
            }
        }
        else {
            for (int i = 25; i < 27; i++) {
                for (int a = 0; a < 2; a++) {
                    deck.addcardtodraw(database->getcard(i));
                }
            }
            for (int i = 43; i < 47; i++) {
                for (int a = 0; a < 2; a++) {
                    deck.addcardtodraw(database->getcard(i));
                }
            }
        }
    }

    if (Enemy::getEnemyType() == ENEMY_TYPE::GAME_MASTER) {
        for (int i = 25; i < 27; i++) {
            for (int a = 0; a < bbbquantities[i]; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }
        for (int i = 47; i < 51; i++) {
            for (int a = 0; a < 1; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }
    }
    deck.shuffle();
}

int Enemy::displayhp() {
	if (enemytype == ENEMY_TYPE::SURVIVOR) {
		if (getsurvivorphase2() == true) {
			return gethp() - 100;
		}
	}
	return gethp();
}