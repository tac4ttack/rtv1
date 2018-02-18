#include "rtv1.h"

int		mlx_main_loop(t_env *e)
{
	if (e)
	{
		mlx_keyboard_repeated(e);
		mlx_clear_window(e->mlx, e->win);
		draw(e);

		t_p2i a;
		a.x = WIDTH / 2;
		a.y = HEIGHT / 2 - 15;
		t_p2i b;
		b.x = WIDTH / 2;
		b.y = HEIGHT / 2 + 15;
		mlx_img_line(e->frame, a, b, 0x00660066);
		a.x = WIDTH / 2 - 15;
		a.y = HEIGHT / 2;
		b.x = WIDTH / 2 + 15;
		b.y = HEIGHT / 2;
		mlx_img_line(e->frame, a, b, 0x00660066);

		mlx_put_image_to_window(e->mlx, e->win, e->frame->ptr, 0, 0);
		display_hud(e);
	}
	return (0);
}
