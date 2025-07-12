#ifndef BONUS_H
# define BONUS_H

t_color	apply_checkerboard_pattern(t_hit_info *hit_info, t_pattern *pattern);
t_color	get_pattern_color(t_hit_info *hit_info, void *object);
int		parse_pattern(char **data, t_pattern *pattern);
t_vec3	apply_bump_mapping(t_hit_info *hit_info, t_pattern *pattern);
double	noise_function(double x, double y);
t_vec3	calculate_bump_normal(t_hit_info *hit_info, t_pattern *pattern);

#endif
