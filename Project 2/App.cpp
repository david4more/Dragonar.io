#include "App.h"
/*
	Features to add:
	
	- menu while opening app, menu on escape
		probably have to be in other files
	- music, sounds
		music - japanese lofi probbly, sounds from 8bit sounds generator
	- shooting
		can be like one of the guns in cuphead, or like a laser beam, which will be hard to aim, or a magic stream or smth
	- enemies
		those will be smart af
	- allies
		those will fly near your head, from the side closest to them
	- multiplayer
		will be like holding a point, or capturing some kind of flags
	- singleplayer
		campaign, a game versus bots or smth else

	Things to learn about:

	git, github
	for which things do you need a new file

*/
void App::init()
{
	/*
		link.setFillColor(sf::Color(94, 195, 99));

		angle3 = std::acos((var2f1.x * var2f2.x + var2f1.y * var2f2.y) / (std::hypot(var2f1.x, var2f1.y) * std::hypot(var2f2.x, var2f2.y)));
		angle3 = angle3 * (180.f / Pi);

			if (angle3 >= 0)
			{
				if (links[i + 1].getTexture() == &bodySegment1)
				{
					if (angle3 > rangeOfMotion * (2.f / 3))
						links[i + 1].setTexture(&bodySegment3);
					else if (angle3 > rangeOfMotion / 3)
						links[i + 1].setTexture(&bodySegment2);
				}
				else if (links[i + 1].getTexture() == &bodySegment2)
				{
					if (angle3 == 0)
						links[i + 1].setTexture(&bodySegment1);
					else if (angle3 < rangeOfMotion)
						links[i + 1].setTexture(&bodySegment1);
					else if (angle3 > rangeOfMotion * (2.f / 3))
						links[i + 1].setTexture(&bodySegment3);
				}
				else if (links[i + 1].getTexture() == &bodySegment3)
				{
					if (angle3 == 0)
						links[i + 1].setTexture(&bodySegment1);
					else if (angle3 < rangeOfMotion)
						links[i + 1].setTexture(&bodySegment1);
					else if (angle3 > rangeOfMotion / 3)
						links[i + 1].setTexture(&bodySegment2);
				}
			}
			else if (angle3 < 0)
			{
				angle3 = std::abs(angle3);
				if (links[i + 1].getTexture() == &bodySegment1)
				{
					if (angle3 > rangeOfMotion * (2 / 3))
					links[i + 1].setTexture(&bodySegment32);
					else if (angle3 > rangeOfMotion / 3)
						links[i + 1].setTexture(&bodySegment22);
				}
				else if (links[i + 1].getTexture() == &bodySegment22)
				{
					if (angle3 < rangeOfMotion)
						links[i + 1].setTexture(&bodySegment1);
					else if (angle3 > rangeOfMotion * (2 / 3))
						links[i + 1].setTexture(&bodySegment32);
				}
				else if (links[i + 1].getTexture() == &bodySegment32)
				{
					if (angle3 < rangeOfMotion)
						links[i + 1].setTexture(&bodySegment1);
					else if (angle3 > rangeOfMotion / 3)
						links[i + 1].setTexture(&bodySegment22);
				}
			}


			nextLinkPos = links[i + 1].getPosition();
			var2f2 = nextLinkPos - linkPos;

			float magnitude1 = std::hypot(var2f1.x, var2f1.y);
			float magnitude2 = std::hypot(var2f2.x, var2f2.y);

			if (magnitude1 > 0) var2f1 /= magnitude1;
			if (magnitude2 > 0) var2f2 /= magnitude2;


			angle3 = std::atan2(var2f2.y, var2f2.x) - std::atan2(var2f1.y, var2f1.x);
			angle3 *= (180.f / Pi);

			while (angle3 > 180) angle3 -= 360;
			while (angle3 < -180) angle3 += 360;

			if (std::abs(angle3) > rangeOfMotion)
				links[i + 1].move((nextLinkPos - lastLinkPos) * adjustmentSpeed * currentSpeed);

			changeTexture(&bodySegment1, &bodySegment2, &bodySegment3, &bodySegment22, &bodySegment32, i + 1, decorRangeOfMotion);
	*/
	srand(time(NULL));

	center = sf::Vector2f((videoMode.width / 2), (videoMode.height / 2));
	windowSize = window->getSize();

	textureptr = nullptr;

	tailScale = sf::Vector2f(2.f, 1.2f);

	head1.loadFromFile("files/dragonHead1.png");
	head2.loadFromFile("files/dragonHead2.png");
	head3.loadFromFile("files/dragonHead3.png");
	head22.loadFromFile("files/dragonHead22.png");
	head32.loadFromFile("files/dragonHead32.png");

	// Head case
	{
		sf::RectangleShape link(sf::Vector2f(size * 2.f, size * 2.28f));
		link.setTexture(&head1);
		link.setOrigin(size, (size * 2.28f) / 2.f);
		link.setPosition(center);
		links.push_back(link);
		totalLinks++;
	}

	tail1.loadFromFile("files/tail1.png");
	tail2.loadFromFile("files/tail2.png");
	tail3.loadFromFile("files/tail3.png");
	tail22.loadFromFile("files/tail22.png");
	tail32.loadFromFile("files/tail32.png");

	bodySegment1.loadFromFile("files/bodySegment1.png");
	bodySegment2.loadFromFile("files/bodySegment2.png");
	bodySegment3.loadFromFile("files/bodySegment3.png");
	bodySegment22.loadFromFile("files/bodySegment22.png");
	bodySegment32.loadFromFile("files/bodySegment32.png");

	spawnLinks();

	backgroundTexture.loadFromFile("files/skyPattern3.jpg");
	backgroundTexture.setRepeated(true);
	background.setTexture(&backgroundTexture);

	backgroundSize = sf::Vector2f(videoMode.width * 10, videoMode.height * 10);
	background.setSize(sf::Vector2f(backgroundSize.x, backgroundSize.y));
	background.setTextureRect(sf::IntRect(0, 0, backgroundSize.x, backgroundSize.y));

	cursorImage.loadFromFile("files/cursor.png");
	cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
	window->setMouseCursor(cursor);
	cursorArrowTexture.loadFromImage(cursorImage);
	cursorArrow.setTexture(&cursorArrowTexture);
	cursorArrow.setSize(sf::Vector2f(32.f, 32.f));

	paws1.loadFromFile("files/paws1.png");
	paws2.loadFromFile("files/paws2.png");
	paws3.loadFromFile("files/paws3.png");
	paws22.loadFromFile("files/paws22.png");
	paws32.loadFromFile("files/paws32.png");

	paws.setTexture(&paws1);
	paws.setSize(sf::Vector2f(size, size * 1.3f * 2));
	paws.setOrigin(sf::Vector2f(size / 2, size * 1.3f));
	paws.setPosition(center);
}

void App::spawnLinks()
{
	for (int i = 1; i < defaultLinks; i++)
	{
		sf::RectangleShape link(sf::Vector2f(size * 1.3f, size));
		link.setTexture(&bodySegment1);
		link.setOrigin((size * 1.3f) / 2.f, size / 2.f);
		link.setPosition(links[links.size() - 1].getPosition());

		if (i == defaultLinks - 1)
			link.setScale(tailScale.x, tailScale.y);

		links.push_back(link);
		totalLinks++;
	}
}

void App::addLink()
{
	sf::RectangleShape link(sf::Vector2f(size * 1.3f, size));
	link.setTexture(&bodySegment1);
	link.setOrigin((size * 1.3f) / 2.f, size / 2.f);
	link.setPosition(links[links.size() - 1].getPosition());

	link.setScale(tailScale.x, tailScale.y);
	links[totalLinks - 1].setScale(1.f, 1.f);

	links.push_back(link);
	totalLinks++;
}

void App::removeLink()
{
	if (totalLinks > 1)
	{
		links.pop_back();
		totalLinks--;
		links[totalLinks - 1].setScale(tailScale.x, tailScale.y);
	}
	if (totalLinks == 5)
	{
		window->close();
	}
}

void App::pollEvents()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			updateMousePos();
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				lmbHeld = true;
				window->setMouseCursorVisible(false);
				break;
			case sf::Mouse::Right:
				boost(true);
				break;
			}
			break;

		case sf::Event::MouseButtonReleased:
			updateMousePos();
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				lmbHeld = false;
				window->setMouseCursorVisible(true);
				break;
			case sf::Mouse::Right:
				boost(false);
				break;
			}
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window->close();
				break;
			}
			break;

		case sf::Event::Closed:
			window->close();
			break;
		}
	}
	if (lmbHeld || currentSpeed != 0)
	{
		movement(currentSpeed);
	}
}

void App::updateObjects()
{
	// foods
	if (clockFood.getElapsedTime() >= spawnFoodInterval && totalFoods < maxFoods)
	{
		sf::RectangleShape food;
		food.setFillColor(sf::Color(77, 204, 14));
		food.setSize(sf::Vector2f(foodSize, foodSize));
		do
		{
			foodPos.x = rand() % (windowSize.x - static_cast<int>(foodSize));
			foodPos.y = rand() % (windowSize.y - static_cast<int>(foodSize));

			food.setPosition(foodPos);
		} while ((foodPos.x >= anchorPos.x - safeZone && foodPos.x <= anchorPos.x + safeZone) &&
			(foodPos.y >= anchorPos.y - safeZone && foodPos.y <= anchorPos.y + safeZone));

		foods.push_back(food);
		totalFoods++;

		clockFood.restart();
	}
	for (int i = 0; i < totalFoods; i++)
	{
		if (foods[i].getGlobalBounds().contains(links[0].getPosition()))
		{
			addLink();

			foods.erase(foods.begin() + i);
			totalFoods--;
			break;
		}
	}

	// poisons
	if (clockPoison.getElapsedTime() >= spawnPoisonInterval && totalPoisons < maxPoisons)
	{
		sf::RectangleShape poison;
		poison.setFillColor(sf::Color(66, 57, 78));
		poison.setSize(sf::Vector2f(poisonSize, poisonSize));
		do
		{
			poisonPos.x = rand() % (windowSize.x - static_cast<int>(poisonSize));
			poisonPos.y = rand() % (windowSize.y - static_cast<int>(poisonSize));

			poison.setPosition(poisonPos);
		} while ((poisonPos.x >= anchorPos.x - safeZone && poisonPos.x <= anchorPos.x + safeZone) &&
			(poisonPos.y >= anchorPos.y - safeZone && poisonPos.y <= anchorPos.y + safeZone));

		poisons.push_back(poison);
		totalPoisons++;

		clockPoison.restart();
	}
	for (int i = 0; i < totalPoisons; i++)
	{
		if (poisons[i].getGlobalBounds().contains(links[0].getPosition()))
		{
			removeLink();

			poisons.erase(poisons.begin() + i);
			totalPoisons--;
			break;
		}
	}
	/*
	for (int i = 0; i < totalPoisons; i++)
	{
		for (int j = totalLinks - 1; j >= 1; j--)
		{
			if (links[j].getGlobalBounds().intersects(poisons[i].getGlobalBounds()))
			{
				poisons.erase(poisons.begin() + i);
				totalPoisons--;
				break;
			}
		}
	}
	*/
}

void App::movement(float& currentSpeed)
{
	anchorPos = links[0].getPosition();
	view->setCenter(anchorPos);
	window->setView(*view);

	if (lmbHeld)
	{
		updateMousePos();
		direction = sf::Vector2f(globalMousePos.x - anchorPos.x, globalMousePos.y - anchorPos.y);
		anchorDirectionModule = std::hypot(direction.x, direction.y);
		velocity += (direction / anchorDirectionModule) * acceleration;		// (direction / anchorDirectionModule) is equal normalized direction, which is a vector with the anchorDirectionModule of 1

		angle1 = std::atan2(velocity.y, velocity.x) * (180.0f / Pi) - 90;
		links[0].setRotation(angle1);

		if (currentSpeed > maxSpeed)
			velocity *= friction;//velocity = (velocity / currentSpeed) * maxSpeed;

		links[0].move(velocity);

		var2f2 = sf::Vector2f(anchorPos - static_cast<sf::Vector2f>(globalMousePos));
		var2f1 = sf::Vector2f(links[1].getPosition() - anchorPos);

		angle3 = std::atan2(var2f1.x * var2f2.y - var2f1.y * var2f2.x, var2f1.x * var2f2.x + var2f1.y * var2f2.y);
		angle3 *= (180.f / Pi);

		if (!boostActive)
			changeTexture(&head1, &head2, &head3, &head22, &head32, 0, decorRangeOfMotionHead);
		else
			changeTexture(&head1, &head2, &head2, &head22, &head22, 0, decorRangeOfMotionHead);

		angle4 = std::atan2(direction.x, direction.y) * (180 / Pi);
		cursorArrow.setPosition(globalMousePos);
		cursorArrow.setRotation(-angle4 -135);
	}
	else
	{
		angle1 = std::atan2(velocity.y, velocity.x) * (180.0f / Pi) - 90;
		links[0].setRotation(angle1);

		if (currentSpeed < 0.04f)
		{
			velocity = sf::Vector2f(0, 0);
			links[0].setTexture(&head1);
		}
		else
		{
			velocity *= friction;
			links[0].move(velocity);
		}
	}
	currentSpeed = std::hypot(velocity.x, velocity.y);

	for (int i = 1; i < totalLinks - 1; i++)
	{
		lastLinkPos = links[i - 1].getPosition();
		linkPos = links[i].getPosition();
		nextLinkPos = links[i + 1].getPosition();

		linkDirection = sf::Vector2f(lastLinkPos.x - linkPos.x, lastLinkPos.y - linkPos.y);
		linkDirectionModule = std::hypot(linkDirection.x, linkDirection.y);

		var2f1 = linkPos - lastLinkPos;
		angle2 = std::atan2(var2f1.y, var2f1.x) * (180.0f / Pi);
		links[i].setRotation(angle2);

		var2f2 = nextLinkPos - linkPos;
		angle3 = std::atan2(var2f1.x * var2f2.y - var2f1.y * var2f2.x, var2f1.x * var2f2.x + var2f1.y * var2f2.y);
		angle3 *= (180.f / Pi);
		
		if (std::abs(angle3) > rangeOfMotion)
			links[i + 1].move((nextLinkPos - lastLinkPos) * adjustmentSpeed * currentSpeed);

		if (boostActive)
		{
			var1 = pow(i, adjustmentPower) * pow(adjustmentCurvingCoeff, adjustmentPower) * pow(currentSpeed, adjustmentPower);
			var2 = adjustmentCurvingSpeed * currentSpeed;
			if (std::abs(angle3) < rangeOfMotionCurvature)
				links[i + 1].move((nextLinkPos - lastLinkPos + sf::Vector2f(angle3 * var1, angle3 * var1)) * var2);

			if (textureChangeReset.getElapsedTime() >= textureChangeResetTime)
			{
				for (int i = 1; i < totalLinks; i++)
				{
					links[i].setTexture(&bodySegment1);
				}
			}
		}
		else
		{
			changeTexture(&bodySegment1, &bodySegment2, &bodySegment3, &bodySegment22, &bodySegment32, i, decorRangeOfMotion);
		}

		if (linkDirectionModule > distance)
		{
			links[i].setPosition(lastLinkPos.x + ((linkDirection.x / linkDirectionModule) * -distance),
				lastLinkPos.y + ((linkDirection.y / linkDirectionModule) * -distance));
		}

		// pawsies
		if (i == pawsPosition)
		{
			paws.setPosition(links[i].getPosition() + (linkDirection / linkDirectionModule) * size);
			paws.setRotation(angle2);

			if (!boostActive)
			{
				if (angle3 > decorRangeOfMotionPaws * (2.f / 3.f))
					textureptr = &paws3;
				else if (angle3 > decorRangeOfMotionPaws / 3.f)
					textureptr = &paws2;
				else if (angle3 < -decorRangeOfMotionPaws * (2.f / 3.f))
					textureptr = &paws32;
				else if (angle3 < -decorRangeOfMotionPaws / 3.f)
					textureptr = &paws22;
				else
					textureptr = &paws1;

				if (textureptr != paws.getTexture())
					paws.setTexture(textureptr);
			}
			else if (paws.getTexture() != &paws1)
				paws.setTexture(&paws1);
		}
	}

	// tail case
	{
		lastLinkPos = links[totalLinks - 2].getPosition();
		linkPos = links[totalLinks - 1].getPosition();
		linkDirection = sf::Vector2f(lastLinkPos.x - linkPos.x, lastLinkPos.y - linkPos.y);
		linkDirectionModule = std::hypot(linkDirection.x, linkDirection.y);

		var2f1 = linkPos - lastLinkPos;

		angle2 = std::atan2(var2f1.y, var2f1.x) * (180.0f / Pi);

		links[totalLinks - 1].setRotation(angle2);

		changeTexture(&tail1, &tail2, &tail3, &tail22, &tail32, totalLinks - 1, decorRangeOfMotionTail);

		if (linkDirectionModule > distance)
		{
			links[totalLinks - 1].setPosition(lastLinkPos.x + ((linkDirection.x / linkDirectionModule) * -distance),
				lastLinkPos.y + ((linkDirection.y / linkDirectionModule) * -distance));
		}
	}

	/*
	 // bounce off edges
	if (anchorPos.x - size < 0)
	{
		velocity.x *= -speedLossCoeff;
		links[0].setPosition(size, anchorPos.y);
	}
	if (anchorPos.x + size > windowSize.x)
	{
		velocity.x *= -speedLossCoeff;
		links[0].setPosition(windowSize.x - size, anchorPos.y);
	}
	if (anchorPos.y - size < 0)
	{
		velocity.y *= -speedLossCoeff;
		links[0].setPosition(anchorPos.x, size);
	}
	if (anchorPos.y + size > windowSize.y)
	{
		velocity.y *= -speedLossCoeff;
		links[0].setPosition(anchorPos.x, windowSize.y - size);
	}

	
		if (clockDebug.getElapsedTime() >= debugClockInterval)
		{
			if (i == 4)
			{
				std::cout << angle3 << '\n';
				clockDebug.restart();
			}
		}
	*/
}

void App::changeTexture(sf::Texture* texture1, sf::Texture* texture2, sf::Texture* texture3, sf::Texture* texture22, sf::Texture* texture32, int i, float rangeOfMotion)
{
	if (angle3 > rangeOfMotion * (2.f / 3.f))
		textureptr = texture3;
	else if (angle3 > rangeOfMotion / 3.f)
		textureptr = texture2;
	else if (angle3 < -rangeOfMotion * (2.f / 3.f))
		textureptr = texture32;
	else if (angle3  < -rangeOfMotion / 3.f)
		textureptr = texture22;
	else
		textureptr = texture1;

	if (textureptr != links[i].getTexture())
		links[i].setTexture(textureptr);
}

void App::updateMousePos()
{
	mousePos = sf::Mouse::getPosition(*window);
	globalMousePos = window->mapPixelToCoords(mousePos);
}

void App::boost(bool start)
{
	if (start)
	{
		maxSpeed *= boostCoeff;
		adjustmentSpeed *= boostCoeff;
		boostActive = true;
		for (int i = 1; i < totalLinks; i++)
		{
			if (links[i].getTexture() == &bodySegment3)
				links[i].setTexture(&bodySegment2);
			if (links[i].getTexture() == &bodySegment32)
				links[i].setTexture(&bodySegment22);
		}
		textureChangeReset.restart();
		adjustmentSpeed *= boostCoeff;
		/*
		acceleration *= boostCoeff;
		decorRangeOfMotion /= boostCoeff;
		*/
	}
	else
	{
		maxSpeed *= (1 / boostCoeff);
		adjustmentSpeed *= (1 / boostCoeff);
		boostActive = false;
		adjustmentSpeed /= boostCoeff;
		/*
		acceleration *= (1 / boostCoeff);
		decorRangeOfMotion /= (1 / boostCoeff);
		*/
	}
}

void App::render()
{
	// (224, 251, 252) 
	window->clear(sf::Color(186, 215, 242));
	window->draw(background);

	for (int i = 0; i < totalFoods; i++)
		window->draw(foods[i]);
	for (int i = 0; i < totalPoisons; i++)
		window->draw(poisons[i]);

	for (int i = totalLinks - 1; i >= 0; i--)
		window->draw(links[i]);
	window->draw(paws);

	if (lmbHeld)
		window->draw(cursorArrow);
	window->display();
}	  

App::App()
{
	initWindow();
	init();
}

App::~App()
{
	delete window;
}

const bool App::isRunning() const
{
	return window->isOpen();
}

void App::update()
{
	pollEvents();
	updateObjects();
}

void App::initWindow()
{
	title = "Dragon in question";				// from lizzard to snake, and then - to dragon!
	if (1)
	{
		videoMode = sf::VideoMode(sf::VideoMode::getDesktopMode());
		window = new sf::RenderWindow(videoMode, title, sf::Style::Fullscreen);
	}
	else
	{
		videoMode = sf::VideoMode(1366, 768);
		window = new sf::RenderWindow(videoMode, title);
	}
	window->setFramerateLimit(144);
	view = new sf::View(window->getDefaultView());
}
