#include "../includes/camera.h"

void recalculate_camera_vectors(t_camera *camera)
{
    // Re-calculate right and up vectors from the direction vector
    // This assumes UPVEC is a global 'up' direction, e.g., (0, 1, 0)
    camera->right = normalize_vec3(cross_vec3(camera->direction, UPVEC));
    camera->up = normalize_vec3(cross_vec3(camera->direction, camera->right));
	camera->right = normalize_vec3(cross_vec3(camera->direction, camera->up));
}
