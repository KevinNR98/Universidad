#include <stdio.h>
#include "utils.h"


int createBigFile(const char* filename, unsigned asize){
    int i;
    tdat dat;
    FILE* pf = fopen(filename, "wb");
    if(!pf){
        return 0;
    }
    for(i=1;i<=asize;i++){
        dat.key = i;

        dat.deleted = 0;
        fwrite(&dat, sizeof(dat), 1, pf);
    }
    fclose(pf);

    shuffleFile(filename, sizeof(tdat));

    return 1;
}


int shuffleFile(const char* filename, size_t recordsize){
    FILE* pf = fopen(filename, "r+b");
    size_t n;
    size_t offset;

    void* sufO;
    void* sufR;
    int i;
    if(!pf){
        return 0;
    }

    sufO = malloc(recordsize);
    sufR = malloc(recordsize);
    if(!sufO || !sufR){
        return 0;
    }



    fseek(pf, 0L, SEEK_END);
    n = ftell(pf)/recordsize;
    fseek(pf, 0L, SEEK_SET);


    for (i = 0; i < n - 1; i++){
        offset = (rand() % n-i-1);

        fseek(pf, i*recordsize, SEEK_SET);

        fread(sufO, recordsize, 1, pf);
        fseek(pf, offset*recordsize, SEEK_CUR);
        fread(sufR, recordsize, 1, pf);

        fseek(pf, -1*recordsize, SEEK_CUR);
        fwrite(sufO, recordsize, 1, pf);
        //fseek(pf, 0L, SEEK_SET);
        fseek(pf, i*recordsize, SEEK_SET);
        fwrite(sufR, recordsize, 1, pf);

    }

    fclose(pf);
    free(sufO);
    free(sufR);
    return 1;
}
