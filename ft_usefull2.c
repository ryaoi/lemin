#include "lemin.h"

int             total_path(t_lem *lem, t_path *path)
{
    t_path      *ptr;
    int         ret;

    ret = 0;
    ptr = path;
    while (ptr != NULL)
    {
        if (ptr->step < lem->left_ants + lem->short_path_num - 1
            || ptr->step == lem->short_path_num)
            ret++;
        ptr = ptr->next;
    }
    return (ret);
}
