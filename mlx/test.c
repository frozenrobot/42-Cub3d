#include <stdio.h>
#include <math.h>

int grid[8][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},	
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

int max(int a, int b)
{
	return (a > b ? a : b);
}

int main(void)
{
	int x_dist;
	int y_dist;
	int x;
	int y;
	int dx;
	int dy;
	float O = M_PI;
    int posx = 350;
    int posy = 350;
	int grid_w = 800;
	int grid_h = 800;

	x_dist = 2 * max(grid_w, grid_h);
	y_dist = 2 * max(grid_w, grid_h);
	//this part sets the values for x_dist and y_dist (then, whichever is smaller is taken as ray dist; direction facing is set accordingly; then wall length is calculated)
	if (O >= 0 && O < (M_PI / 2))
	{
		printf("Quad1\n");
		//finding x_dist
		dx = (posx % 100); //x goes to nearest line on left
		dy = dx * tan(O); //diff in y depends on angle
		x = posx - dx; //x and y are the positions of the ray when intersecting a vertical line
		y = posy - dy;
		while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100)) // **** CHANGE CONDITION, CAN GO OUT OF MAP INTO INFINITE LOOP CURRENT WAY **** // maybe convert stuff to float too
		{
            printf("x = %i, y = %i\n", x, y);
            printf("dx = %i, dy = %i\n", dx, dy);
            printf("checking coordinates: %i, %i\n", ((y-1)/ 100), (x-1) / 100);
			if (grid[((y-1) / 100)][(x - 1) / 100] == 1) //i-j coordinates of the block that the ray is intersecting (on the grid)
			{
				printf("dy = %i\nsin0 = %f\n", dy, sin(O));
				x_dist = dx / cos(O); //length of the ray
				break ;
			}
			dx += 100; //if grid value of block is 0 (empty space), keep going to the next vertical line until intersection with grid value 1 found
			dy = dx * tan(O);
			x = posx - dx; //x and y are the positions of the ray when intersecting a vertical line
			y = posy - dy;
		}
		//finding y_dist
		dy = posy % 100;
		dx = dy / tan(O);
		x = posx - dx;
		y = posy - dy;
		while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
		{
            printf("checking coordinates: %i, %i\n", ((y-1)/ 100), (x-1)/ 100 );
			if (grid[(y - 1) / 100][(x-1) / 100] == 1)
			{
				y_dist = dy / sin(O);
				break ;
			}
			dy += 100;
			dx = dy / tan(O);
			x = posx - dx;
			y = posy - dy;
		}
	}
	else if (O >= M_PI / 2 && O < M_PI)
	{
		printf("Quad2\n");
		//finding x_dist
		dx = 100 - (posx % 100); //x goes to nearest line on left
		dy = dx * tan(M_PI - O); //diff in y depends on angle
		x = posx + dx; //x and y are the positions of the ray when intersecting a vertical line
		y = posy - dy;
		while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100)) // **** CHANGE CONDITION, CAN GO OUT OF MAP INTO INFINITE LOOP CURRENT WAY **** // maybe convert stuff to float too
		{
            printf("x = %i, y = %i\n", x, y);
            printf("dx = %i, dy = %i\n", dx, dy);
            printf("checking coordinates: %i, %i\n", ((y-1)/ 100), (x+1) / 100);
			if (grid[((y-1) / 100)][(x + 1) / 100] == 1) //i-j coordinates of the block that the ray is intersecting (on the grid)
			{
				x_dist = dy / sin(M_PI - O); //length of the ray
				break ;
			}
			dx += 100; //if grid value of block is 0 (empty space), keep going to the next vertical line until intersection with grid value 1 found
			dy = dx * tan(M_PI - O);
			x = posx + dx; //x and y are the positions of the ray when intersecting a vertical line
			y = posy - dy;
		}
		//finding y_dist
		dy = posy % 100;
		dx = dy / tan(M_PI - O);
		x = posx + dx;
		y = posy - dy;
		while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
		{
            printf("checking coordinates: %i, %i\n", ((y-1)/ 100), x/ 100 );
			if (grid[(y - 1) / 100][x / 100] == 1)
			{
				y_dist = dy / sin(M_PI - O);
				break ;
			}
			dy += 100;
			dx = dy / tan(M_PI - O);
			x = posx + dx;
			y = posy - dy;
		}
	}
	else if (O >= M_PI && O < 3 * M_PI / 2)
	{
		printf("Quad3\n");
		//finding x_dist
		dx = 100 - (posx % 100); //x goes to nearest line on left
		dy = dx * tan(O - M_PI); //diff in y depends on angle
		x = posx + dx; //x and y are the positions of the ray when intersecting a vertical line
		y = posy + dy;
		while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100)) // **** CHANGE CONDITION, CAN GO OUT OF MAP INTO INFINITE LOOP CURRENT WAY **** // maybe convert stuff to float too
		{
            printf("x = %i, y = %i\n", x, y);
            printf("dx = %i, dy = %i\n", dx, dy);
            printf("checking coordinates: %i, %i\n", ((y-1)/ 100), (x-1) / 100);
			if (grid[(y / 100)][(x + 1) / 100] == 1) //i-j coordinates of the block that the ray is intersecting (on the grid)
			{
				x_dist = dx / cos(O - M_PI); //length of the ray
				break ;
			}
			dx += 100; //if grid value of block is 0 (empty space), keep going to the next vertical line until intersection with grid value 1 found
			dy = dx * tan(O - M_PI);
			x = posx + dx; //x and y are the positions of the ray when intersecting a vertical line
			y = posy + dy;
		}
		//finding y_dist
		dy = 100 - (posy % 100);
		dx = dy / tan(O - M_PI);
		x = posx + dx;
		y = posy + dy;
		while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
		{
            printf("checking coordinates: %i, %i\n", ((y-1)/ 100), (x-1)/ 100 );
			if (grid[(y + 1) / 100][x / 100] == 1)
			{
				y_dist = dy / sin(O - M_PI);
				break ;
			}
			dy += 100;
			dx = dy / tan(O - M_PI);
			x = posx + dx;
			y = posy + dy;
		}
	}
	else if (O >= 3 * M_PI / 2 && O < 2 * M_PI)
	{
		printf("Quad4\n");
		//finding x_dist
		dx = (posx % 100); //x goes to nearest line on left
		dy = dx * tan((2 * M_PI) - O); //diff in y depends on angle
		x = posx - dx; //x and y are the positions of the ray when intersecting a vertical line
		y = posy + dy;
		while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100)) // **** CHANGE CONDITION, CAN GO OUT OF MAP INTO INFINITE LOOP CURRENT WAY **** // maybe convert stuff to float too
		{
            printf("x = %i, y = %i\n", x, y);
            printf("dx = %i, dy = %i\n", dx, dy);
            printf("checking coordinates: %i, %i\n", ((y-1)/ 100), (x-1) / 100);
			if (grid[(y / 100)][(x - 1) / 100] == 1) //i-j coordinates of the block that the ray is intersecting (on the grid)
			{
				x_dist = dy / sin((2 * M_PI) - O); //length of the ray
				break ;
			}
			dx += 100; //if grid value of block is 0 (empty space), keep going to the next vertical line until intersection with grid value 1 found
			dy = dx * tan((2 * M_PI) - O);
			x = posx - dx; //x and y are the positions of the ray when intersecting a vertical line
			y = posy + dy;
		}
		//finding y_dist
		dy = 100 - (posy % 100);
		dx = dy / tan((2 * M_PI) - O);
		x = posx - dx;
		y = posy + dy;
		while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
		{
			printf("x = %i, y = %i\n", x, y);
            printf("dx = %i, dy = %i\n", dx, dy);
            printf("checking coordinates: %i, %i\n", (y/ 100), (x-1)/ 100 );
			if (grid[(y) / 100][(x-1) / 100] == 1)
			{
				y_dist = dy / sin((2 * M_PI) - O);
				break ;
			}
			dy += 100;
			dx = dy / tan((2 * M_PI) - O);
			x = posx - dx;
			y = posy + dy;
		}
	}
    printf("dist_x = %i\ndist_y = %i\n", x_dist, y_dist);
}