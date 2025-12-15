#include <cub3d.h>

double	safe_tan(double n)
{
	double	new_n;

	new_n = tan(n);
	if (fabs(new_n) < VERTICAL_RAY_THRESHOLD)
		new_n = VERTICAL_RAY_THRESHOLD;
	return (new_n);
}
