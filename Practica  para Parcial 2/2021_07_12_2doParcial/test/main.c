#include <stdio.h>
#include <stdlib.h>

int restarChar(const void* a, const void* b);

int main()
{
    char cad[21] = "HDDSSD2TB";
    char cad2[21] = "HDDSSD2TB";
    int resu;

    resu = restarChar(cad, cad2);
    printf("%d\n", resu);
    return 0;
}


int restarChar(const void* a, const void* b)
{
//    return (*(int*)a) - (*(int*)b);
    if((*(char*)a) && (*(char*)b))
    {
        while((*(char*)a) == (*(char*)b) && (*(char*)a)!= '\0' && (*(char*)b)!= '\0')
        {
            *(char*)a++;
            *(char*)b++;
        }
    }

    if((*(char*)a) == (*(char*)b))
    {
        return 0;
    }
    else if ((*(char*)a) > (*(char*)b))
    {
        return -1;
    }
    else
    {
        return 1;
    }



}
