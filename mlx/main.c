#include "mlx/mlx.h"
#include <stdlib.h>
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

typedef struct s_player
{
	int posx;
	int posy;
	float O;
} t_player;

t_player *g_player;
void *mlx_ptr;
void *win_ptr;

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

void	cast_rays(int **grid, t_player *p)
{
	int x_dist;
	int y_dist;
	int x;
	int y;
	int dx;
	int dy;
	int dists_fov[60];

	//this part sets the values for x_dist and y_dist (then, whichever is smaller is taken as ray dist; direction facing is set accordingly; then wall length is calculated)
	if (p->O >= 0 && p->O < M_PI / 2)
	{
		//finding x_dist
		dx = (p->posx % 100); //x goes to nearest line on left
		dy = dx * tan(p->O); //diff in y depends on angle
		while (1)
		{
			x = p->posx - dx; //x and y are the positions of the ray when intersecting a vertical line
			y = p->posy - dy;
			if (grid[((y - 1) / 100)][(x - 1) / 100] == 1) //i-j coordinates of the block that the ray is intersecting (on the grid) : \ 
			{
				x_dist = dy / sin(p->O); //length of the ray
				break ;
			}
			dx += 100; //if grid value of block is 0 (empty space), keep going to the next vertical line until intersection with grid value 1 found
			dy += 100 * tan(p->O);
		}
		//finding y_dist
		dy = p->posy % 100;
		dx = dy / tan(p->O);
		while (1)
		{
			x = p->posx - dx;
			y = p->posy - dy;
			if (grid[(y - 1) / 100][((x - 1) / 100)] == 1)
			{
				y_dist = dy / sin(p->O);
				break ;
			}
			dy += 100;
			dx = dy / tan(p->O);
		}
	}
	else if (p->O >= M_PI / 2 && p->O < M_PI)
	{

	}
	else if (p->O >= M_PI && p->O < 3 * M_PI / 2)
	{

	}
	else if (p->O >= 3 * M_PI / 2 && p->O < 2 * M_PI)
	{

	}
}

int	deal_key(int key, t_player *player)
{
		if (key == 53)
		exit(0);
	// if (key) //A
	// 	printf("%d\n", key);
	// 	// (pos[1]) -= 10 ;
	if (key == 0) //A
		player->posx -= 10;
	if (key == 13) //W
		player->posy -= 10;
	if (key == 2) //D
		player->posx += 10;
	if (key == 1) //S
		player->posy += 10;
	mlx_erase();
	mlx_pixel_put(mlx_ptr, win_ptr, g_player->posx, g_player->posy, 0xffffff);
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
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 500, 500, "fdf");
	mlx_pixel_put(mlx_ptr, win_ptr, g_player->posx, g_player->posy, 0xffffff);
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