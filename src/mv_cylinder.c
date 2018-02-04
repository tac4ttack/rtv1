#include "rtv1.h"

void        mv_cylinder(t_env *e)
{
   	if (KP_I)
		e->cylinders[e->mv_objects.target_obj.id].dir = rotx(e->cylinders[0].dir, 1 * DEG2RAD);
	if (KP_K)
		e->cylinders[e->mv_objects.target_obj.id].dir = rotx(e->cylinders[0].dir, -1 * DEG2RAD);
	if (KP_J)
		e->cylinders[e->mv_objects.target_obj.id].dir = roty(e->cylinders[0].dir, 1 * DEG2RAD);
	if (KP_L)
		e->cylinders[e->mv_objects.target_obj.id].dir = roty(e->cylinders[0].dir, -1 * DEG2RAD);
	if (KP_U)
		e->cylinders[e->mv_objects.target_obj.id].dir = rotz(e->cylinders[0].dir, 1 * DEG2RAD);
	if (KP_O)
    	e->cylinders[e->mv_objects.target_obj.id].dir = rotz(e->cylinders[0].dir, -1 * DEG2RAD);

   	if (KP_N1)
		e->cylinders[e->mv_objects.target_obj.id].pos.x -= e->mv_objects.mv_ratio;
	if (KP_N2)
		e->cylinders[e->mv_objects.target_obj.id].pos.y -= e->mv_objects.mv_ratio;
	if (KP_N3)
		e->cylinders[e->mv_objects.target_obj.id].pos.x += e->mv_objects.mv_ratio;
	if (KP_N4)
		e->cylinders[e->mv_objects.target_obj.id].pos.z -= e->mv_objects.mv_ratio;
	if (KP_N5)
		e->cylinders[e->mv_objects.target_obj.id].pos.y += e->mv_objects.mv_ratio;
	if (KP_N6)
    	e->cylinders[e->mv_objects.target_obj.id].pos.z += e->mv_objects.mv_ratio;
}