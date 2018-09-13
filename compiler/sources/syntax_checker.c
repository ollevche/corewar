#include "../headers/asm.h"

int check_syntax(char *line, char **columns)
{
    int check;
    int i;

    i = 0;
    check = 0;
    if ((check = check_command_s(columns[0], columns[1])) < 1)
        return (line - check - 1);
    else
    {
        while (columns[i] != NULL)
        {
            check = check_arg_s(columns[i], columns[i + 1]);
            if (check < 1)
                return (line - check - 1);
            i++;
        }
    }
    return (DEF_T);

}

int     check_arg_s(char *start, char *end)
{
    while ()
    {

    }
}

char *check_command_s(char *start, char *end)
{
    int i;

    while (*start && start < end && *start != ' ' && *start != '\t')
    {
        if (ft_strchr(LABEL_CHARS, *start) == NULL && *start != '#')
            return (start);
        start++;
    }
    i = skip_wspaces(start);
    return (start + i);
}

void test()
{
    char *line;
    char *start;
    char *end;
    char *ret;

    line = ft_strdup("		-st-i r4, %:arriere, r3");
    end = ft_strchr(line, 'r');
    start = line + 2;
    ft_printf("start = %s\nend = %s\n", start, end);
    ret = check_command_s(start, end);
    if (ret < end)
        ft_printf("%s error at [1:%d]\n", ERROR_M, ret - line + 1);
    else
        ft_printf("NORMAS");
    ft_printf("\nret = %s\n", ret);

}