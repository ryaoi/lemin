#include "lemin.h"

static int  count_all_ants(t_path *path, int *smallest)
{
    int     total;
    t_line  *ptr_line;
    t_path  *ptr;

    ptr = path;
    total = 0;
    while (ptr != NULL)
    {
        ptr_line = ptr->line->next;
        while (ptr_line != NULL)
        {
            if (*smallest > ptr_line->ants && ptr_line->ants != 0)
                *smallest = ptr_line->ants;
            if (ptr_line->ants != 0)
                total++;
            ptr_line = ptr_line->next;
        }
        ptr = ptr->next;
    }
    return (total);
}

static void search_and_print(t_path *path, int size, int *i, int total)
{
    t_line  *ptr_line;
    t_path  *ptr;

    ptr = path;
    while (ptr != NULL)
    {
        ptr_line = ptr->line->next;
        while (ptr_line != NULL)
        {
            if (size == ptr_line->ants)
            {
                ft_printf("L%d-%s", ptr_line->ants, ptr_line->line);
                if (*i < total - 1)
                    ft_putstr(" ");
                else
                    ft_putstr("\n");
                (*i)++;
            }
            ptr_line = ptr_line->next;
        }
        ptr = ptr->next;
    }
}

void        print_ants(t_path *path, t_lem *lem)
{
    int     smallest;
    int     total;
    int     i;

    smallest = lem->ants;
    total = count_all_ants(path, &smallest);
    i = 0;
    while (smallest <= lem->ants)
    {
        search_and_print(path, smallest, &i, total);
        smallest++;
    }
}
