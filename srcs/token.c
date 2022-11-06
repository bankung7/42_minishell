#include "minishell.h"

int ft_cleartoken(t_token **token)
{
    t_token *head;

    if (*token == 0)
        return (0);
    head = *token;
    while (*token)
    {
        *token = (*token)->next;
        free(head->string);
        free(head);
        head = (*token);
    }
    return (0);
}

int ft_addtoken(t_token **token, char *str, int type)
{
    t_token *node;

    node = malloc(sizeof(t_token));
    if (!node)
        return (-1);
    node->string = str;
    node->type = type;
    node->pipe = 0;
    node->next = 0;
    
    if (*token == 0)
        *token = node;
    else
    {
        t_token *head;
        head = *token;
        while (head->next)
            head = head->next;
        head->next = node;
    }
    return (0);
}

int ft_isdelimit(char *str, int i)
{
    if (str[i] == ' ' || str[i] == '\t')
        return (DELIMITER);
    else if (str[i] == '|' && str[i + 1] == '|')
        return (OR);
    else if (str[i] == '|')
        return (PIPE);
    else if (str[i] == '<' && str[i + 1] == '<')
        return (HEREDOC);
    else if (str[i] == '<')
        return (INFILE);
    else if (str[i] == '>' && str[i + 1] == '>')
        return (APPEND);
    else if (str[i] == '>')
        return (OUTFILE);
    else if (str[i] == '\'')
        return (SQUOTE);
    else if (str[i] == '"')
        return (DQUOTE);
    else if (str[i] == '$')
        return (DSIGN);
    return (-1);
}

int ft_stoken(t_token **token, char *str, int i, int type)
{
    int j;
    char *tmp;

    j = type % 2;
    if (type == SQUOTE || type == DQUOTE)
    {
        i++;
        while (str[i + j] && ft_isdelimit(str, i + j) != type)
            j++;
        if (str[i + j] == 0)
        {
            printf("no quote found!\n");
            ft_addtoken(token, 0, ERROR_TOKEN);
            return (0);
        }
        tmp = ft_substr(str, i, j);
        // printf("%s\n", tmp);
        // free(tmp);
        ft_addtoken(token, tmp, WORD);
        return (j + 1);
    }
    if (j == 0)
        j = 2;
    tmp = ft_substr(str, i, j);
    // printf("%s\n", tmp);
    // free(tmp);
    ft_addtoken(token, tmp, type);
    return (j - 1);
}

int ft_wtoken(t_token **token, char *str, int i)
{
    int j;
    char *tmp;

    j = 0;
    while (str[i + j])
    {
        if (ft_isdelimit(str, i + j) == -1)
            j++;
        if ((str[i + j + 1] == 0 && j > 0) || ft_isdelimit(str, i + j) != -1)
        {
            if (str[i + j + 1] == 0)
                j += 1;
            tmp = ft_substr(str, i, j);
            // free(tmp);
            ft_addtoken(token, tmp, WORD);
            // printf("%s\n", tmp);
            return (j - 1);
        }
    }
    return (j);
}

void ft_tokenize(t_token **token, char *str)
{
    int i;
    int instance;

    i = 0;
    while (str[i])
    {
        instance = ft_isdelimit(str, i);
        if (instance == -1)
            i += ft_wtoken(token, str, i);
        else if (instance > 0)
            i += ft_stoken(token, str, i, instance);
        i++;
    }
}