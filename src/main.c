#include "cub3d.h"

int main(int argc, char *argv[])
{
    t_app app;
    if (argc != 2)
        return (printf("Usage : ./cub3D map.cub"));
    init_game(&app, argv[1]);
    launch_game(&app);
    free_game(&app);
    return (0);
}