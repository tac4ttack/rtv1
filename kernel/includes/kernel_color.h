int	blend_multiply(int c1, int c2)
{
	int r, g, b;
	int r1 = (c1 & 0x00FF0000) >> 16;
	int g1 = (c1 & 0x0000FF00) >> 8;
	int b1 = (c1 & 0x000000FF);
	int r2 = (c2 & 0x00FF0000) >> 16;
	int g2 = (c2 & 0x0000FF00) >> 8;
	int b2 = (c2 & 0x000000FF);

	r = r1 * r2;
	g = g1 * g2;
	b = b1 * b2;
	return ((r << 16) + (g << 8) + b);
}
