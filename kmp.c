#include <stdio.h>
#include <string.h>

int next[80];
next[0] = -999;

void get_next(char T[], int next[])
{
    int k = -1;
    int j = 0;
    int l = strlen(T);
    next[j] = k;

    while (j < l)
    {
        if ( (k == -1) || (T[j] == T[k]) )
        {
            k++;
            j++;
            next[j] = k;
        }
        else
        {
            k = next[k]; 
        }
    }
}

int index_KMP(char S[], char T[], int pos)
{
    int i = pos;
    int j = 0;

    while ( (i < strlen(S)) && (j < strlen(T)) )
    {
        if ( (j == -1)  || S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }

    if (strlen(T) == j)
    {
        return i - strlen(T);
    }
    else
    {
        return -1;
    }
}

int main()
{
    char s[6] = "abcde";
    char t[80];
    cin >> s;
    cin >> t;
    int pos = 0;
    get_next(t, next);
    int index = index_KMP(s, t, pos);
    cout << index;
}
