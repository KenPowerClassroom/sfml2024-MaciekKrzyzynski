#include "pch.h"

const int HEIGHT = 25;
const int WIDTH = 40;
const int tileSize = 18;

#include"../16_SFML_Games/Grid.h"
#include"../16_SFML_Games/Player.h"
#include"../16_SFML_Games/snake.cpp"


TEST(Grid, HasWallsAndInterior) {

	Grid grid;

	EXPECT_EQ(Grid::tile::WALL, grid.cell(0, 0));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(24, 39));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(10, 10));

}

TEST(Grid, CreateNewWall) {

	Grid grid;

	grid.newWall(10, 10);
	EXPECT_EQ(Grid::tile::NEW_WALL, grid.cell(10, 10));

}


TEST(Grid, GridsIsClearedExceptForWalls) {

	Grid grid;

	grid.newWall(10, 10);

	grid.clear();
	EXPECT_EQ(Grid::tile::WALL, grid.cell(0, 0));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(24, 39));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(10, 10));

}

//------------------------
//|                      |
//|                      |
//|         filled       |
//|                      |
//|                      |
//|----------------------|
//|                      |
//|                      |
//|         not filled   |
//|                      |
//|                      |
//------------------------

TEST(Grid, GridsIsFilledWithHorizWall) {

	Grid grid;

	for(int i=1;i<WIDTH-1;i++)
		grid.newWall(10, i);

	grid.markConnectedCellsNotToBeFilled(11, 1);

	grid.fillEmptyCells();

	EXPECT_EQ(Grid::tile::WALL, grid.cell(1, 1));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(9, 38));

	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(11, 1));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(23, 38));

}

//------------------------
//|                      |
//|                      |
//|        not filled    |
//|                      |
//|                      |
//|-------------         |
//|            |         |
//|            |         |
//|   filled   |         |
//|            |         |
//|            |         |
//------------------------

TEST(Grid, GridsIsFilledWithHorizAndVertWall) {

	Grid grid;

	for (int x = 1; x < 10; x++)
		grid.newWall(10, x);
	for (int y = 10; y < HEIGHT-1; y++)
		grid.newWall(y, 10);

	grid.markConnectedCellsNotToBeFilled(2, 2);

	grid.fillEmptyCells();

	EXPECT_EQ(Grid::tile::WALL, grid.cell(11, 1));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(23, 9));

	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(1, 1));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(9, 38));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(23, 38));


}


TEST(Player, ConstrainedHorizontallyRight) {

	Player p;

	p.x = 10, p.y = 10;

	p.goRight();

	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(10, p.y);
	EXPECT_EQ(WIDTH-1, p.x);
}

TEST(Player, ConstrainedHorizontallyLeft) {

	Player p;

	p.x = 10, p.y = 10;

	p.goLeft();

	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(10, p.y);
	EXPECT_EQ(0, p.x);
}

TEST(Player, ConstrainedVerticallyUp) {

	Player p;

	p.x = 10, p.y = 10;

	p.goUp();

	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(0, p.y);
	EXPECT_EQ(10, p.x);
}

TEST(Player, ConstrainedDiagonallyFast) {

	Player p;

	p.x = 10, p.y = 10;
	p.dx = 5;
	p.dy = 6;

	
	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(HEIGHT-1, p.y);
	EXPECT_EQ(WIDTH-1, p.x);
}

TEST(SnakeTest, SnakeCheckBoundaries) {
	SnakeTest t;

	int returnValue = t.checkBounds(10, 1000); // snake outside of boundary on the right
	EXPECT_EQ(0, returnValue);
	returnValue = t.checkBounds(10, 10); //snake within the boundary
	EXPECT_EQ(-1, returnValue);
	returnValue = t.checkBounds(10, -10); //snake outside of boundary on top
	EXPECT_EQ(MAX_HEIGHT, returnValue);
}

TEST(SnakeTest, SnakeMoving) {
	SnakeTest t;
	bool returnBool = t.moveSnake(); 

	EXPECT_TRUE(returnBool); // check if snake is moving 
}

TEST(SnakeTest, IncreaseSnakeLenght) {
	SnakeTest t;
	int returnInt = t.ranomizeFruitSpawnAndIncreaseSnakeLenght();
	int previousNum = num; // get the current lenght of snake

	EXPECT_EQ(-1,returnInt);

	square[MIN_SQUARE].x = fruit.x;
	square[MIN_SQUARE].y = fruit.y; //change values so snake hits the fruit 
	returnInt = t.ranomizeFruitSpawnAndIncreaseSnakeLenght();
	EXPECT_EQ(previousNum + 1, returnInt); // Check if snake lenght was incresed correctly 
}

TEST(SnakeTest, SnakeCollidesWithItself) {
	SnakeTest t;
	square[MIN_SQUARE].x = 10; //place two snake segments somewhere far
	square[MIN_SQUARE].y = 10;
	square[MIN_SQUARE + 1].x = 11;
	square[MIN_SQUARE + 1].y = 11;
	bool returnBool = t.snakeCollision();
	EXPECT_FALSE(returnBool);
	
	square[MIN_SQUARE].x = 10; //place two snake segments in the same position (collision)
	square[MIN_SQUARE].y = 10;
	square[MIN_SQUARE + 1].x = 10;
	square[MIN_SQUARE + 1].y = 10;

	returnBool = t.snakeCollision();
	EXPECT_TRUE(returnBool); 
}