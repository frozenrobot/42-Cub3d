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

int main(void)
{
	int x_dist;
	int y_dist;
	int x;
	int y;
	int dx;
	int dy;
	float O = M_PI/4;
    int posx = 350;
    int posy = 350;

	//this part sets the values for x_dist and y_dist (then, whichever is smaller is taken as ray dist; direction facing is set accordingly; then wall length is calculated)
	if (O >= 0 && O < (M_PI / 2))
	{
		//finding x_dist
		dx = (posx % 100); //x goes to nearest line on left
		dy = dx * tan(O); //diff in y depends on angle
		while (1) // **** CHANGE CONDITION, CAN GO OUT OF MAP INTO INFINITE LOOP CURRENT WAY **** // maybe convert stuff to float too
		{
			x = posx - dx; //x and y are the positions of the ray when intersecting a vertical line
			y = posy - dy;
            printf("x = %i, y = %i\n", x, y);
            printf("dx = %i, dy = %i\n", dx, dy);
            printf("checking coordinates: %i, %i\n", ((y-1)/ 100), (x-1) / 100 );
			if (grid[((y-1) / 100)][(x - 1) / 100] == 1) //i-j coordinates of the block that the ray is intersecting (on the grid)
			{
				x_dist = dy / sin(O); //length of the ray
				break ;
			}
			dx += 100; //if grid value of block is 0 (empty space), keep going to the next vertical line until intersection with grid value 1 found
			dy += 100 * tan(O);
		}
		//finding y_dist
		dy = posy % 100;
		dx = dy / tan(O);
		while (1)
		{
			x = posx - dx;
			y = posy - dy;
            printf("checking coordinates: %i, %i\n", ((y-1)/ 100), (x-1)/ 100 );
			if (grid[(y - 1) / 100][(x-1) / 100] == 1)
			{
				y_dist = dy / sin(O);
				break ;
			}
			dy += 100;
			dx = dy / tan(O);
		}
	}
    printf("dist_x = %i\ndist_y = %i\n", x_dist, y_dist);
}