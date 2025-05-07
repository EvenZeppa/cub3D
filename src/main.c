#include "cub3d.h"

int launch_game(t_app *app)
{

    return (0);
}

int main(int argc, char *argv[])
{
    t_app app;

    if (argc != 2)
        return (printf("Usage : ./cub3D map.cub"));
    if (init_game(&app, argv[1]))
        exit_error("Init game");
    if (launch_game(&app))
        exit_error("Launch game");
    if (free_game(&app))
        exit_error("Free game");
    return (0);
}