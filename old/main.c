#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define CEIL 0x59bfff
#define FLOOR 0x003300
#define WWALL 0xff0000
#define NWALL 0x00ff00
#define EWALL 0x0000ff
#define SWALL 0xffff00

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

typedef struct s_player
{
	int posx;
	int posy;
	float O;
} t_player;

t_player *g_player;
void *mlx_ptr;
void *win_ptr;

int max(int a, int b)
{
	return (a > b ? a : b);
}

int min(int a, int b)
{
	return (a > b ? b : a);
}

void mlx_erase(void)
{
	int i;
	int j;

	i = 0;
	while (i < 500)
	{
		j = 0;
		while (j < 500)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

void	cast_rays(t_player *p, int grid_w, int grid_h)
{
	int x_dist;
	int y_dist;
	int mindist;
	int x;
	int y;
	int dx;
	int dy;
	int wall; //W=1, N=2, E=3, S=4;
	int dists_fov[100][2];
	int i;
	int j;
	float O;

	i = -1;
	O = p->O - 0.6;
	while (++i < 100)
	{
		if (O < 0)
			O += (2 * M_PI);
		else if (O > (2 * M_PI))
			O -= (2 * M_PI);
		//this part sets the values for x_dist and y_dist (then, whichever is smaller is taken as ray dist; direction facing is set accordingly; then wall length is calculated)
		x_dist = 200 * max(grid_w, grid_h);
		y_dist = 200 * max(grid_w, grid_h);
		if (O >= 0 && O < M_PI / 2)
		{
			//finding x_dist
			dx = (p->posx % 100); //x goes to nearest line on left
			dy = dx * tan(O); //diff in y depends on angle
			x = p->posx - dx; //x and y are the positions of the ray when intersecting a vertical line
			y = p->posy - dy;
			while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
			{
				if (grid[((y - 1) / 100)][(x - 1) / 100] == 1) //i-j coordinates of the block that the ray is intersecting (on the grid) :
				{
					x_dist = dx / cos(O); //length of the ray
					break ;
				}
				dx += 100; //if grid value of block is 0 (empty space), keep going to the next vertical line until intersection with grid value 1 found
				dy = dx * tan(O);
				x = p->posx - dx;
				y = p->posy - dy;
			}
			//finding y_dist
			dy = p->posy % 100;
			dx = dy / tan(O);
			while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
			{
				x = p->posx - dx;
				y = p->posy - dy;
				if (grid[(y - 1) / 100][((x - 1) / 100)] == 1)
				{
					y_dist = dy / sin(O);
					break ;
				}
				dy += 100;
				dx = dy / tan(O);
			}
			mindist = min(x_dist, y_dist);
			wall = (x_dist > y_dist ? 4 : 3);
		}
		else if (O >= M_PI / 2 && O < M_PI)
		{
			dx = 100 - (p->posx % 100);
			dy = dx * tan(M_PI - O);
			x = p->posx + dx;
			y = p->posy - dy;
			while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
			{
				if (grid[((y-1) / 100)][(x + 1) / 100] == 1)
				{
					x_dist = dy / sin(M_PI - O);
					break ;
				}
				dx += 100;
				dy = dx * tan(M_PI - O);
				x = p->posx + dx;
				y = p->posy - dy;
			}
			dy = p->posy % 100;
			dx = dy / tan(M_PI - O);
			x = p->posx + dx;
			y = p->posy - dy;
			while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
			{
				if (grid[(y - 1) / 100][x / 100] == 1)
				{
					y_dist = dy / sin(M_PI - O);
					break ;
				}
				dy += 100;
				dx = dy / tan(M_PI - O);
				x = p->posx + dx;
				y = p->posy - dy;
			}
			mindist = min(x_dist, y_dist);
			wall = (x_dist > y_dist ? 4 : 1);
		}
		else if (p->O >= M_PI && p->O < 3 * M_PI / 2)
		{
			dx = 100 - (p->posx % 100);
			dy = dx * tan(O - M_PI);
			x = p->posx + dx;
			y = p->posy + dy;
			while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
			{
				if (grid[(y / 100)][(x + 1) / 100] == 1)
				{
					x_dist = dx / cos(O - M_PI);
					break ;
				}
				dx += 100;
				dy = dx * tan(O - M_PI);
				x = p->posx + dx;
				y = p->posy + dy;
			}
			dy = 100 - (p->posy % 100);
			dx = dy / tan(O - M_PI);
			x = p->posx + dx;
			y = p->posy + dy;
			while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
			{
				if (grid[(y + 1) / 100][x / 100] == 1)
				{
					y_dist = dy / sin(O - M_PI);
					break ;
				}
				dy += 100;
				dx = dy / tan(O - M_PI);
				x = p->posx + dx;
				y = p->posy + dy;
			}
			mindist = min(x_dist, y_dist);
			wall = (x_dist > y_dist ? 2 : 1);
		}
		else if (p->O >= 3 * M_PI / 2 && p->O < 2 * M_PI)
		{
			dx = (p->posx % 100);
			dy = dx * tan((2 * M_PI) - O);
			x = p->posx - dx;
			y = p->posy + dy;
			while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
			{
				if (grid[(y / 100)][(x - 1) / 100] == 1)
				{
					x_dist = dy / sin((2 * M_PI) - O);
					break ;
				}
				dx += 100;
				dy = dx * tan((2 * M_PI) - O);
				x = p->posx - dx;
				y = p->posy + dy;
			}
			dy = 100 - (p->posy % 100);
			dx = dy / tan((2 * M_PI) - O);
			x = p->posx - dx;
			y = p->posy + dy;
			while (x > 0 && x < (grid_w * 100) && y > 0 && y < (grid_h * 100))
			{
				if (grid[(y) / 100][(x-1) / 100] == 1)
				{
					y_dist = dy / sin((2 * M_PI) - O);
					break ;
				}
				dy += 100;
				dx = dy / tan((2 * M_PI) - O);
				x = p->posx - dx;
				y = p->posy + dy;
			}
			mindist = min(x_dist, y_dist);
			wall = (x_dist > y_dist ? 2 : 3);
		}
		dists_fov[i][0] = 50000 / (mindist * cos(fabsf(p->O - O)));
		dists_fov[i][1] = wall;
		O += 0.012;
		// printf ("mindist = %i, len = %i, wall = %i\n", mindist, dists_fov[i][0], wall);
		// break ;
		// printf("%f: [%i] [%i] [%i]\n", O, mindist, dists_fov[i][0], dists_fov[i][1]);
	}
	
	// for (int j = 0; j < 100; j++)
	// {
	// 	printf("%i: [%i] [%i]\n", j, dists_fov[j][0], dists_fov[j][1]);
	// }

	i = 0;
	while (i < 500)
	{
		// mlx_pixel_put(mlx_ptr, win_ptr, i, 5, 0xffffff);
		j = 0;
		while (j < (250 - (dists_fov[i / 5][0] / 2)))
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, CEIL);
			j++;
		}
		while (j < (250 + (dists_fov[i / 5][0] / 2)) && j < 500)
		{
			if (dists_fov[i / 5][1] == 1)
				wall = WWALL;
			else if (dists_fov[i / 5][1] == 2)
				wall = NWALL;
			else if (dists_fov[i / 5][1] == 3)
				wall = EWALL;
			else if (dists_fov[i / 5][1] == 4)
				wall = SWALL;
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, wall);
			j++;
		}
		while (j < 500)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, FLOOR);
			j++;
		}
		i++;
	}
}

float angle_change(int dir, float ang)
{
	// if (ang < 0.1 && dir == 0)
	// 	return ((2 * M_PI) - 0.1 + ang);
	// else if (ang >= (2 * M_PI) - 0.1 && dir == 1)
	// 	return ((2 * M_PI) - ang);
	// else if (dir == 0)
	// 	return (ang - 0.1);
	// else
	// 	return (ang + 0.1);
	if (dir == 0)
		ang -= 0.1;
	else if (dir == 1)
		ang += 0.1;
	if (ang < 0)
		ang += (2 * M_PI);
	else if (ang > 2 * M_PI)
		ang -= (2 * M_PI);
	return (ang);
}

int	deal_key(int key, t_player *player)
{
	if (key == 53)
		exit(0);
	// if (key) //A
	// 	printf("%d\n", key);
	// 	// (pos[1]) -= 10 ;
	if (key == 0) //A
	{
		player->posx -= 10 * cos(player->O - M_PI / 2);
		player->posy -= 10 * sin(player->O - M_PI / 2);
	}
	// player->posx -= 10;
	if (key == 13) //W
	{
		player->posx -= 10 * cos(player->O);
		player->posy -= 10 * sin(player->O);
	}
		// player->posy -= 10;
	if (key == 2) //D
	{
		player->posx -= 10 * cos(player->O + M_PI / 2);
		player->posy -= 10 * sin(player->O + M_PI / 2);
	}
		// player->posx += 10;
	if (key == 1) //S
	{
		player->posx += 10 * cos(player->O);
		player->posy += 10 * sin(player->O);
	}
		// player->posy += 10;
	if (key == 123)
		player->O = angle_change(0, player->O);
	if (key == 124)
		player->O = angle_change(1, player->O);
	// mlx_erase();
	cast_rays(g_player, 8, 8);
	// mlx_pixel_put(mlx_ptr, win_ptr, g_player->posx, g_player->posy, 0xffffff);
	// printf("X: %f, Y: %f\n", player->posx, player->posy);
	return (0);
}

void coord_to_pixel(int x, int y) // x and y are i-j coordinates of player's spawining position
{
	g_player->posx = (x * 100) + 50;
	g_player->posy = (y * 100) + 50;
}

int main(void)
{
    
	// int i;
	// int j;
	
	// t_player player_sub;

	g_player = malloc(sizeof(t_player));
	// player = &player_sub;
	g_player->posx = 300;
	g_player->posy = 300;
	g_player->O = 3 * M_PI / 4;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 500, 500, "fdf");
	cast_rays(g_player, 8, 8);
	// mlx_pixel_put(mlx_ptr, win_ptr, g_player->posx, g_player->posy, 0xffffff);
	mlx_key_hook(win_ptr, deal_key, g_player);
    mlx_loop(mlx_ptr);
}

// int	main(void)
// {
// 	void	*mlx;
// 	void	*img;
// 	char	*relative_path = "./test.xpm";
// 	int		img_width;
// 	int		img_height;

// 	mlx = mlx_init();
// 	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
//     mlx_loop(mlx);

// }

// i = 0;
// 	j = 0;
// 	while (i < 500)
// 	{
// 		j = 0;
// 		while (j < 250)
// 		{
// 			mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0x59bfff);
// 			j++;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < 500)
// 	{
// 		j = 250;
// 		while (j < 500)
// 		{
// 			mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0x003300);
// 			j++;
// 		}
// 		i++;
// 	}