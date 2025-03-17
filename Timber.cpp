//g++ Timber.cpp -o timber -lsfml-graphics -lsfml-window -lsfml-system

#include<SFML/Graphics.hpp>
#include<sstream>
using namespace sf;

const int NUM_BRANCHES=6;
enum class side{LEFT, RIGHT, NONE};
side branchPositions[NUM_BRANCHES];


void updateBranches(int seed);


int main()
{
	VideoMode vm(1920,1200);
	//VideoMode vm(960,540);
	//View view(FloatRect(0,0,1920,1080));
	RenderWindow window(vm, "Timber",Style::Fullscreen);
	//window.setView(view);
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0,0);
	
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(800,0);
	
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud1.setPosition(0,0);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud2.setPosition(0,200);
	spriteCloud3.setTexture(textureCloud);
	spriteCloud3.setPosition(0,400);
	
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0,750);

	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	Sprite spriteBranches[NUM_BRANCHES];
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		spriteBranches[i].setTexture(textureBranch);
		spriteBranches[i].setPosition(2000,2000);
		spriteBranches[i].setOrigin(220,20);

	}
	
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580,720);
	side PlayerSide = side::LEFT;                     //Initially Left Side

	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600,860);

	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700,830);
	const float AXE_POSITION_LEFT=700;
	const float AXE_POSITION_RIGHT=1075;

	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(800,720);
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	Clock clock;
	bool beeActive=false;
	float beeSpeed=0.0f;
	float height;
	bool cloud1Active=false;
	float cloud1Speed=0.0f;
	bool cloud2Active=false;
	float cloud2Speed=0.0f;
	bool cloud3Active=false;
	float cloud3Speed=0.0f;
	bool paused=true;
	Font font;
	font.loadFromFile("fonts/Astroz.ttf");
	Text messageText;
	messageText.setFont(font);
	messageText.setString("Press Enter To Start!!!");
	messageText.setCharacterSize(75);
	messageText.setPosition(1920/2.0f,1080/2.0f);
	messageText.setFillColor(Color::Red);
	
	FloatRect textRect=messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
	
	int score;
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("SCORE=0");
	scoreText.setCharacterSize(50);
	scoreText.setPosition(20,20);
	scoreText.setFillColor(Color::Green);
	
	RectangleShape timeBar;
	float timeBarStartWidth=400;
	float timeBarHeight=40;
	timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
	timeBar.setPosition(1920/2.0f - timeBarStartWidth/2,980);
	timeBar.setFillColor(Color::Red);
	
	float timeRemaining=6.0f;
	float timeBarStartWidthPerSec = timeBarStartWidth/timeRemaining;
	
	
	// updateBranches(1);
    // updateBranches(2);
    // updateBranches(3);
    // updateBranches(4);
    // updateBranches(5);
    // updateBranches(6);

	bool acceptInput=false;

	//GAME LOOP;
	while(window.isOpen())
	{
		Event event1;
			while (window.pollEvent(event1))
			{
				if(event1.type == event1.Closed)
				{
					window.close();
				}

				if (event1.type== Event::KeyReleased&& !paused)
				{
					acceptInput=true;
					spriteAxe.setPosition(2000,spriteAxe.getPosition().y);
				}
			}
		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if(Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused=false;
			score=0;
			timeRemaining=6.0f;
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				branchPositions[i]=side::NONE;
			}

			spritePlayer.setPosition(580,720);
			acceptInput=true;
		}

		if (acceptInput)
		{
			//Right Key Press
			if(Keyboard::isKeyPressed(Keyboard::Right))
			{
				PlayerSide = side::RIGHT;
				score++;
				timeRemaining += (0.15+2/score);
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200,720);
				updateBranches(score);
				logActive = true;
				spriteLog.setPosition(800,720);
				logSpeedX = -5000;
				acceptInput =  false;

			}

			//Left Key Press
			if(Keyboard::isKeyPressed(Keyboard::Left))
			{
				PlayerSide = side::LEFT;
				score++;
				timeRemaining += (0.15+2/score);
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580,720);
				updateBranches(score);
				logActive = true;
				spriteLog.setPosition(800,720);
				logSpeedX = 5000;
				acceptInput =  false;

			}

		}

		if(!paused){
		Time dt=clock.restart();
		
		timeRemaining=timeRemaining - dt.asSeconds();
		timeBar.setSize(Vector2f(timeBarStartWidthPerSec*timeRemaining,timeBarHeight));
		
		if(timeRemaining<=0.0f){
			paused=true;
			messageText.setString("OUT OF TIME!!!");
			messageText.setPosition(1920/2.0f,1080/2.0f);
			FloatRect textRect=messageText.getLocalBounds();
			messageText.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);	
		}
		
		if(! beeActive)
		{
			srand((int)time(0));
			beeSpeed=rand()%130+130;
			srand((int)time(0)*10);
			float height=rand()%500+500;
			spriteBee.setPosition(2000,height);
			beeActive=true;
		}
		else
		{
			spriteBee.setPosition(spriteBee.getPosition().x-beeSpeed*dt.asSeconds(),spriteBee.getPosition().y);
			if(spriteBee.getPosition().x<-100)
			{
				beeActive=false;
			}
		}
		
		if(! cloud1Active)
		{
			srand((int)time(0)*10);
			cloud1Speed=rand()%120+120;
			srand((int)time(0));
			spriteCloud1.setPosition(-200,rand()%150);
			cloud1Active=true;
		}
		else
		{
			spriteCloud1.setPosition(spriteCloud1.getPosition().x+cloud1Speed*dt.asSeconds(),spriteCloud1.getPosition().y);
			if(spriteCloud1.getPosition().x>1920)
			{
				cloud1Active=false;
			}
		}
		
		if(! cloud2Active)
		{
			srand((int)time(0)*20);
			cloud2Speed=rand()%100+100;
			srand((int)time(0));
			spriteCloud2.setPosition(-200,rand()%200+100);
			cloud2Active=true;
		}
		else
		{
			spriteCloud2.setPosition(spriteCloud2.getPosition().x+cloud2Speed*dt.asSeconds(),spriteCloud2.getPosition().y);
			if(spriteCloud2.getPosition().x>1920)
			{
				cloud2Active=false;
			}
		}
		
		if(! cloud3Active)
		{
			srand((int)time(0)*30);
			cloud3Speed=rand()%140+140;
			srand((int)time(0));
			spriteCloud3.setPosition(-200,rand()%200+150);
			cloud3Active=true;
		}
		else
		{
			spriteCloud3.setPosition(spriteCloud3.getPosition().x+cloud3Speed*dt.asSeconds(),spriteCloud3.getPosition().y);
			if(spriteCloud3.getPosition().x>1920)
			{
				cloud3Active=false;
			}
		}

		std::stringstream ss;
		ss<<"Score="<<score;
		scoreText.setString(ss.str());


		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			float height = i*150;
			if (branchPositions[i]==side::LEFT){
				spriteBranches[i].setPosition(610,height);
				spriteBranches[i].setRotation(180);
			}

			else if (branchPositions[i]==side::RIGHT)
			{
				spriteBranches[i].setPosition(1290,height);
			}

			else
				spriteBranches[i].setPosition(3000,height);
		}

		if(logActive)
		{
			spriteLog.setPosition(spriteLog.getPosition().x+logSpeedX*dt.asSeconds()
									  ,spriteLog.getPosition().y+logSpeedY*dt.asSeconds());
				if(spriteLog.getPosition().x<100 || spriteLog.getPosition().x>2000)
				{
					logActive=false;
					spriteLog.setPosition(800,600);
				}
		}


		} //paused end!



		window.clear();
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		for (int i = 0; i < NUM_BRANCHES; i++) {
            window.draw(spriteBranches[i]);
        }
		if(paused)
		{
			window.draw(messageText);
		}
		window.draw(spritePlayer);
		window.draw(spriteRIP);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		window.draw(scoreText);
		window.draw(timeBar);
		window.draw(spriteBee);
		window.display();
	}//end of while loop.
	return 0;
}

void updateBranches(int seed){

	for (int i = NUM_BRANCHES-1; i > 0; i--)
	{
		branchPositions[i]=branchPositions[i-1];
	}

	srand((int)time(0)+seed);
	int t = rand()%5;
	switch(t) {
	  case 0:
	    branchPositions[0]=side::LEFT;
	    break;
	  case 1:
	    branchPositions[0]=side::RIGHT;
	    break;
	  case 2:
	    branchPositions[0]=side::NONE;
	    break;
	  
	}
}
