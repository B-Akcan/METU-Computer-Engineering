#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

char *read();
char *variables(char *p, int length);
void sort(char *p);
void remove_spaces_and_newlines(char *p);
long int operate();
long int eval(char *s);
char **generate_truth_table(int length);
char *replace(char *truth_table_row, char *vars, char *p);

char *Position;

int main()
{
    char *p, *vars, **truth_table, *p_changeable, *p_wo_spaces;
    int i, j, number_of_vars, height, lenp;

    printf("Enter the input...\n");

    p = read();
    lenp = strlen(p);
    vars = variables(p, lenp);
    remove_spaces_and_newlines(vars);
    number_of_vars = strlen(vars);
    height = pow(2, number_of_vars);
    sort(vars);

    p_wo_spaces = malloc(sizeof(char)*lenp);
    for (i=0 ; i<lenp ; i++) p_wo_spaces[i] = p[i];
    remove_spaces_and_newlines(p_wo_spaces);

    truth_table = generate_truth_table(number_of_vars);

    printf("\nTruth table:\n");

    for (i=0 ; vars[i] ; i++) printf("%c ", vars[i]);
    printf("Result\n");

    for (i=0 ; i < height ; i++)
    {
        for (j=0 ; j < number_of_vars + 1 ; j++)
        {
            if (j != number_of_vars) printf("%c ", truth_table[i][j]);
            else
            {
                p_changeable = replace(truth_table[i], vars, p_wo_spaces);
                printf("  %c\n", eval(p_changeable) ? 'T' : 'F');
            }
        }
    }

    printf("\nPress enter to exit.\n");
    getchar();
    return 0;
}

char *read()
{
    char c, *p;
    int i=0;
    p = malloc(sizeof(char)*1);
    while (1)
    {
        scanf("%c", &c);
        if (c == '\n' || c == EOF) break;
        p = realloc(p, sizeof(char)*(i+1));
        p[i] = c;
        i++;
    }
    p[i] = '\0';
    return p;
}

char *variables(char *p, int length)
{
    int i, j=0, k;
    char *r=malloc(sizeof(char)*1);
    for (i=0 ; i<length ; i++)
    {
        if (p[i] != '(' && p[i] != ')' && p[i] != ' ' && p[i] != '&' && p[i] != '-' && p[i] != '>' && p[i] != '|' && p[i] != '=' && p[i] != '^')
        {
            for (k=0 ; k<strlen(r) ; k++)
            {
                if (r[k] == p[i])
                    goto exit;
            }
            r = realloc(r, sizeof(char)*(j+1));
            r[j] = p[i];
            j++;
        }
        exit:;
    }
    r[j] = '\0';
    return r;
}

void sort(char *p)
{
    int i, j;
    for (i=0 ; i<strlen(p) ; i++)
    {
        for (j=i+1 ; j<strlen(p) ; j++)
        {
            if (p[i] > p[j])
            {
                char temp = p[i];
                p[i] = p[j], p[j] = temp;
            }
        }
    }
}

void remove_spaces_and_newlines(char *p)
{
    char *d = p;
    do 
    { while (*d == ' ' || *d == 10) ++d;
    } while (*p++ = *d++);
}

long int operate()
{
    long int left, right;
    char operator;
    if (*Position == '-')
    {
        Position++;
        right = operate();
        return !right;
    }
    else if (*Position == '(')
    {
        Position++;
        left = operate();
        operator = *Position++;
        right = operate();
        Position++;
        switch (operator)
        {
            case '&': return left && right; break;
            case '|': return left || right; break;
            case '>': return !left || right; break;
            case '=': return (!left || right) && (left || !right); break;
            case '^': return (left && !right) || (!left && right); break;
        }
    }
    else
    {
        while (isspace(*Position) || *Position == '\n') Position++;
        sscanf(Position, "%ld", &left);
        while (isdigit(*Position)) Position++;
        return left;
    }
    return 0;
}

long int eval(char *s)
{
    Position = s;
    return operate();
}

char **generate_truth_table(int length)
{
    char **table, *tf, *tfp;
    int i, j, divisor, height=pow(2, length), init;

    tf = malloc(sizeof(char)*height);
    for (i=0 ; i<height ; i++)
    {
        if (i % 2 == 0) tf[i] = 'T';
        else tf[i] = 'F';
    }
    tfp = malloc(sizeof(char)*height);
    for (i=0 ; i<height ; i++) tfp[i] = tf[i];

    table = malloc(sizeof(char*)*height);
    for (i=0 ; i < height ; i++)
        table[i] = malloc(sizeof(char)*length);
    
    for (j=0, divisor=height/2 ; j<length ; j++, divisor/=2, tfp=tf)
    {
        for (i=0, init=0 ; i < height ; i++)
        {
            if (i - init == divisor)
            {
                tfp++;
                init = i;
            }
            table[i][j] = *tfp;
        }
    }

    return table;
}

char *replace(char *truth_table_row, char *vars, char *p)
{
    int i, j, lenp=strlen(p), lenvars=strlen(vars);
    char *p_changed;

    p_changed = malloc(sizeof(char)*lenp);
    for (i=0 ; i<lenp ; i++) p_changed[i] = p[i];

    for (i=0 ; i<lenvars ; i++)
    {
        for (j=0 ; j<lenp ; j++)
        {
            if (p[j] == vars[i] && truth_table_row[i] == 'T') p_changed[j] = '1';
            else if (p[j] == vars[i] && truth_table_row[i] == 'F') p_changed[j] = '0';
        }
    }

    return p_changed;
}