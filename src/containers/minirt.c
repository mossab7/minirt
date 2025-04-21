#include <minirt.h>

int main(int argc,char **argv)
{
	t_program	*program;

	if(argc < 2)
	{
		elog("Usage ./minirt file.rt");
		return (ERROR);
	}
	program = program_init();
	parse_scene(program, argv[1]);
	if(program->error == ERROR)
		cleanexit(program);
	return (OK);
}
