#ifndef MACROS_H
# define MACROS_H


# define EPSILON 0.0001
# define VEC_EPSILON (t_vec3){EPSILON, EPSILON, EPSILON}
#define RED_INDEX 0
#define GREEN_INDEX 1
#define BLUE_INDEX 2
#define X_INDEX 0
#define Y_INDEX 1
#define Z_INDEX 2
#define W_INDEX 3
#define OBJ_COUNT 6
#define RED_INDEX 0
#define GREEN_INDEX 1
#define BLUE_INDEX 2
#define OBJ_AMB_LIGHT 0
#define OBJ_CAMERA 1
#define OBJ_LIGHT 2
#define OBJ_SPHERE 3
#define OBJ_PLANE 4
#define OBJ_CYLINDER 5
#define OBJ_COUNT 6
#define VEC_MIN -1.0f
#define VEC_MAX 1.0f
#define LIGHT_RATIO_MIN 0.0f
#define LIGHT_RATIO_MAX 1.0f
#define FOV_MIN 0.0f
#define FOV_MAX 180.0f
#define COLOR_MIN 0.0f
#define COLOR_MAX 255.0f
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1000
#define RATIO (16.0f / 9.0f)
#define UPVEC (t_vec3){0.0f, 1.0f, 0.0f}
#endif // !MACROS_H