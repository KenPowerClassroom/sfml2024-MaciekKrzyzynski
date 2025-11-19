#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int N=30,M=20;
static int size=16;
static int width = size*N;
static int height = size*M;
int fruitXPos = 10; 
int fruitYPos = 10;
int const MIN_SQUARE = 0; 

void moveSnake();
void checkBounds();

int dir,num=4;

struct Position 
{
    int x,y;
}  
square[100], fruit;
 



void Tick()
 {

    moveSnake();

    if ((square[MIN_SQUARE].x==fruit.x) && (square[MIN_SQUARE].y==fruit.y)) 
    {
        num++; // increase snake length?
        fruit.x=rand()%N;
        fruit.y=rand()%M;
    }

    checkBounds();
    //Boundary Check

 
    for (int i=1;i<num;i++)
     if (square[MIN_SQUARE].x==square[i].x && square[MIN_SQUARE].y==square[i].y)
         num=i; // snake collision?
 }

void moveSnake()
{
    for (int i = num; i > 0; --i)
    {
        square[i].x = square[i - 1].x;
        square[i].y = square[i - 1].y;
    } // move snake segments

    switch (dir)
    {
    case(0):
        square[MIN_SQUARE].y += 1;
        break;
    case(1):
        square[MIN_SQUARE].x -= 1;
        break;
    case(2):
        square[MIN_SQUARE].x += 1;
        break;
    case(3):
        square[MIN_SQUARE].y -= 1;
        break;
    default:
        break;
    }
}

void checkBounds()
{
    if (square[MIN_SQUARE].x > N)
        square[MIN_SQUARE].x = 0;
    if (square[MIN_SQUARE].x < 0)
        square[MIN_SQUARE].x = N;
    if (square[MIN_SQUARE].y > M)
        square[MIN_SQUARE].y = 0;
    if (square[MIN_SQUARE].y < 0)
        square[MIN_SQUARE].y = M;
}

int snake()
{  
    srand(time(0));

    RenderWindow window(VideoMode(width, height), "Snake Game!");

    Texture t1,t2;
    t1.loadFromFile("images/snake/white.png");
    t2.loadFromFile("images/snake/red.png");

    Sprite sprite1(t1);
    Sprite sprite2(t2);

    Clock clock;
    float timer=0, delay=0.1;

    fruit.x=fruitXPos;
    fruit.y=fruitYPos; 
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time; 

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)      
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) dir=1;   
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir=2;    
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir=3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir=0;

        if (timer>delay) 
        {
            timer=0;
            Tick();
        }

   ////// draw  ///////
    window.clear();
  
    for (int i=0; i<N; i++) 
      for (int j=0; j<M; j++) 
      { 
          sprite1.setPosition(i*size, j*size);
          window.draw(sprite1); //Draw white boxes
      }

    for (int i=0;i<num;i++)
    {
        sprite2.setPosition(square[i].x*size, square[i].y*size);  
        window.draw(sprite2); // draw red boxes
    }
   
    sprite2.setPosition(fruit.x*size, fruit.y*size); 
    window.draw(sprite2);    

    window.display();
    }

    return 0;
}
