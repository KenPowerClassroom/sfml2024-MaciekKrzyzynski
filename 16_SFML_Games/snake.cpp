#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int MAX_WIDTH=30,MAX_HEIGHT=20;
static int size=16;
static int width = size*MAX_WIDTH;
static int height = size*MAX_HEIGHT;
int fruitXPos, fruitYPos = 10;
int const MIN_SQUARE = 0; 

void moveSnake();

int dir,num=4;

struct Position 
{
    int x,y;
}  
square[100], fruit;
 
class Test
{
public:
   int checkBounds(int t_x,int t_y);
};


void Tick()
 {

    moveSnake();

    if ((square[MIN_SQUARE].x==fruit.x) && (square[MIN_SQUARE].y==fruit.y)) 
    {
        num++; // increase snake length?
        fruit.x=rand()%MAX_WIDTH;
        fruit.y=rand()%MAX_HEIGHT;
    }

    Test test;
    test.checkBounds(square[MIN_SQUARE].x, square[MIN_SQUARE].y);
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

int Test::checkBounds(int t_x, int t_y)
{
    if (t_x > MAX_WIDTH)
    {
        t_x = 0;
        square[MIN_SQUARE].x = 0;
        return t_x;
    }
    if (t_x < 0)
    {
        t_x = MAX_WIDTH;
        square[MIN_SQUARE].x = MAX_WIDTH;
        return t_x;
    }
    if (t_y > MAX_HEIGHT)
    {
        t_y = 0;
        square[MIN_SQUARE].y = 0;
        return t_y;
    }
    if (t_y < 0)
    {
        t_y = MAX_HEIGHT;
        square[MIN_SQUARE].y = MAX_HEIGHT; 
        return t_y;
    }
    return -1; 
}

int snake()
{  
    srand(time(0));

    RenderWindow window(VideoMode(width, height), "Snake Game!");

    Texture whiteTexture,redTexture;
    whiteTexture.loadFromFile("images/snake/white.png");
    redTexture.loadFromFile("images/snake/red.png");

    Sprite whiteBox(whiteTexture);
    Sprite redBox(redTexture);

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
  
    for (int i=0; i<MAX_WIDTH; i++) 
      for (int j=0; j<MAX_HEIGHT; j++) 
      { 
          whiteBox.setPosition(i*size, j*size);
          window.draw(whiteBox); //Draw white boxes
      }

    for (int i=0;i<num;i++)
    {
        redBox.setPosition(square[i].x*size, square[i].y*size);  
        window.draw(redBox); // draw red boxes
    }
   
    redBox.setPosition(fruit.x*size, fruit.y*size); 
    window.draw(redBox);    

    window.display();
    }

    return 0;
}

