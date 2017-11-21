unsigned int	blend_multiply(unsigned int c1, unsigned int c2)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);
	unsigned int r2 = (c2 & 0x00FF0000) >> 16;
	unsigned int g2 = (c2 & 0x0000FF00) >> 8;
	unsigned int b2 = (c2 & 0x000000FF);

	r = r1 * r2;
	g = g1 * g2;
	b = b1 * b2;
	return ((r << 16) + (g << 8) + b);
}

unsigned int	blend_add(unsigned int c1, unsigned int c2)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);
	unsigned int r2 = (c2 & 0x00FF0000) >> 16;
	unsigned int g2 = (c2 & 0x0000FF00) >> 8;
	unsigned int b2 = (c2 & 0x000000FF);

	if ((r = r1 + r2) > 255)
		r = 255;
	if ((g = g1 + g2) > 255)
		g = 255;
	if ((b = b1 + b2) > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}

unsigned int	blend_ambiant(unsigned int c1)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);

	r = r1 * 0.3;
	g = g1 * 0.3;
	b = b1 * 0.3;
	return ((r << 16) + (g << 8) + b);
}
