#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class App
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	std::string title;
	sf::View* view;

	sf::Texture head1, head2, head3, head22, head32, bodySegment1, bodySegment2, bodySegment3, bodySegment22, bodySegment32, 
		tail1, tail2, tail3, tail22, tail32, paws1, paws2, paws3, paws22, paws32;
	sf::Texture backgroundTexture;
	sf::Texture* textureptr;
	sf::RectangleShape background;
	sf::Vector2f backgroundSize;
	sf::Vector2f tailScale;
	sf::Image cursorImage;
	sf::Cursor cursor;
	sf::Texture cursorArrowTexture;
	sf::RectangleShape cursorArrow;
	sf::RectangleShape paws;
	unsigned int pawsPosition = 4;			// not index but the number of element, head is 1

	const float sizeCoeff = 0.5f;
	const float Pi = 3.141593;
	const float size = 45.f * sizeCoeff;
	const float distance = 35.f * sizeCoeff;

	const unsigned int defaultLinks = 70;
	unsigned int totalLinks = 0;
	unsigned int index = 0;
	std::vector<sf::RectangleShape> links;
	sf::Vector2i mousePos;
	sf::Vector2f globalMousePos;
	sf::Vector2f anchorPos;
	sf::Vector2f direction;
	sf::Vector2f velocity;
	float anchorDirectionModule, currentSpeed;
	float maxSpeed = 2.5f;
	float acceleration = maxSpeed * 0.02f;
	const float friction = 0.98f;
	const float speedLossCoeff = 0.1f;
	const float boostCoeff = 2.5f;

	sf::Vector2f linkPos;
	sf::Vector2f lastLinkPos;
	sf::Vector2f nextLinkPos;
	sf::Vector2f linkDirection;
	float linkDirectionModule;

	sf::Vector2f var2f1, var2f2;
	float var1, var2;
	float angle1, angle2, angle3, angle4;
	float dotProduct;
	const float rangeOfMotion = maxSpeed * 4.f;
	const float rangeOfMotionCurvature = maxSpeed * 1.8f;			// 1.3f   // 1.8f
	float adjustmentSpeed = maxSpeed * 0.035f;						// 0.015f // 0.055f // 0.035f
	float adjustmentCurvingSpeed = maxSpeed * 0.001f;				// 0.055f // 0.015f // 0.001f
	float adjustmentCurvingCoeff = 0.1f;							// 1.8f   // 10.f
	unsigned int adjustmentPower = 3;
	sf::Clock textureChangeReset;
	sf::Time textureChangeResetTime = sf::seconds(0.5f);

	float decorRangeOfMotion = rangeOfMotion * 1.f;
	float decorRangeOfMotionHead = decorRangeOfMotion * 5.f;
	float decorRangeOfMotionTail = rangeOfMotion * 1.6f;
	float decorRangeOfMotionPaws = rangeOfMotion * 1.f;

	sf::Vector2f center;
	sf::Vector2u windowSize;

	std::vector<sf::RectangleShape> foods;
	std::vector<sf::RectangleShape> poisons;
	const float foodSize = 15.f;
	const float poisonSize = 40.f;
	const float safeZone = 200.f;
	unsigned int totalFoods = 0;
	const unsigned int maxFoods = 10;
	unsigned int totalPoisons = 0;
	const unsigned int maxPoisons = 10;
	sf::Vector2f foodPos;
	sf::Vector2f poisonPos;
	sf::Clock clockFood, clockPoison;
	sf::Time spawnFoodInterval = sf::seconds(2.f);
	sf::Time spawnPoisonInterval = sf::seconds(1.f);

	sf::Clock clockDebug;
	sf::Time debugClockInterval = sf::seconds(1.f);

	bool lmbHeld = false, boostActive = false;

	void initWindow();
	void init();
	void spawnLinks();
public:
	void movement(float& currentSpeed);
	void boost(bool start); 
	void changeTexture(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3, sf::Texture* texture22, sf::Texture* texture32, int i, float rangeOfMotion);
	void updateMousePos();
	void addLink();
	void removeLink();

	App();
	~App();

	const bool isRunning() const;

	void pollEvents();
	void updateObjects();
	void update();
	void render();
};
