#include "ReaperBoss.h"

float GetDistance(sf::Vector2f a, sf::Vector2f b);

ReaperBoss::ReaperBoss(int inputHealth, sf::RenderWindow& renderWindow, Character& player, float &DeltaTime, Map &map) : Character(DeltaTime, map), renderWindow(renderWindow), player(player)
{
	reaperBossIdleTex.loadFromFile("resources/character/Reaper Boss-Idle.png");
	reaperBossSlashTex.loadFromFile("resources/character/Reaper Boss-Attack.png");
	reaperBossSummonTex.loadFromFile("resources/character/Reaper Boss-Magic.png");
	reaperBossTeleportTex.loadFromFile("resources/character/Reaper Boss-Teleport.png");
	reaperBossSkin[0] = sf::IntRect(0, 0, 192, 192);
	reaperBossSkin[1] = sf::IntRect(192, 0, 192, 192);
	reaperBossSkin[2] = sf::IntRect(0, 192, 192, 192);
	reaperBossSkin[3] = sf::IntRect(192, 192, 192, 192);
	reaperBossSkin[4] = sf::IntRect(0, 384, 192, 192);

	sprite.setOrigin(96, 96);

	currentHealth = inputHealth;

	strength = 10;

	hit = false;

	float tempX = 2267;
	float tempY = 2605;

	position.x = tempX;
	position.y = tempY;

	sprite.setPosition(position.x, position.y);

	sprite.setTexture(reaperBossIdleTex);
	
	timer = clock.getElapsedTime().asSeconds();

}

void ReaperBoss::DoShortAttack()
{
	sprite.setTexture(reaperBossSlashTex);
	attacking = true;
			
		if (clock.getElapsedTime().asSeconds() > 0.15)
		{
			if (reaperBossSkinInt < 4)
			{
				reaperBossSkinInt += 1;
			}
			else
			{
				reaperBossSkinInt = 0;
			}
			clock.restart();
		}
	
			sf::Vector2f movement(0, 0);

			if (attackTime.getElapsedTime().asSeconds() > 1) 
			{
				int damage = (strength / 2) + (rand() % strength + 1);
				player.currentHealth -= damage;

				attackTime.restart();
			}
				
		
		}

void ReaperBoss::DoLongAttack()
{
	sprite.setTexture(reaperBossSummonTex);
	attacking = true;

		if (clock.getElapsedTime().asSeconds() > 0.15)
		{
			if (reaperBossSkinInt < 4)
			{
				reaperBossSkinInt += 1;
			}
			else
			{
				reaperBossSkinInt = 0;
			}
			clock.restart();
		}

		sf::Vector2f movement(0, 0);

		if (attackTime.getElapsedTime().asSeconds() > 2)
		{


			attackTime.restart();
		}

		
	//(rand() % 4 + 0);
}

void ReaperBoss::move()
	{
		sf::Vector2f movement(0, 0);

		float deltaSpeed = 200 * DeltaTime;

		if (position.x > player.position.x + 50) {
			movement.x -= deltaSpeed;
		}
		if (position.x < player.position.x - 50) {
			movement.x += deltaSpeed;
		}
		if (position.y > player.position.y + 20) {
			movement.y -= deltaSpeed;
		}
		if (position.y < player.position.y + 40) {
			movement.y += deltaSpeed;
		}

		sprite.move(movement);

		if (DoesCollide()) // if we collide with something
		{
			sprite.move(movement.x * -1, movement.y);

			if (DoesCollide()) // if we collide with something
			{
				// undo the movement we just applied
				sprite.move(movement.x, movement.y * -1);
			}
		}

		if (DoesCollide()) // if we collide with something
			{
				// undo the movement we just applied
			sprite.move(movement.x, movement.y * -1);
		}
	}

float GetDistance(sf::Vector2f a, sf::Vector2f b) {
	float deltaX = a.x - b.x;
	float deltaY = a.y - b.y;
	return sqrt(deltaX * deltaX + deltaY * deltaY);

}

void ReaperBoss::attack()
{
	/*	if (position.x > player.position.x - 50 && position.x < player.position.x + 50 && position.y > player.position.y - 41 && position.y < player.position.y + 41)*/
	
		if (GetDistance(position, player.position) < 150)
		
		{
			move();
			DoShortAttack();
		}

		else if (GetDistance(position, player.position) < 600)
		{
			DoLongAttack();
		}
		else
		{
			attacking = false;
			move();
		}
		
}

void ReaperBoss::Update()
{
	if (alive)
	{
	if (currentHealth <= 0) 
	{
		alive = false;
	}

		position = sprite.getPosition();

	attack();

			if (!attacking)
			{
				sprite.setTexture(reaperBossIdleTex);
			}

	if (clock.getElapsedTime().asSeconds() > 0.5) 
	{
		if (reaperBossSkinInt < 3) 
		{
			reaperBossSkinInt += 1;
		}
		else 
		{
			reaperBossSkinInt = 0;
		}
		clock.restart();
	}
	}


	sprite.setTextureRect(sf::IntRect(reaperBossSkin[reaperBossSkinInt]));

	renderWindow.draw(sprite);
	
}