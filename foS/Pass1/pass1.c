#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{

    FILE *fin, *finter, *fopt, *fsym, *flen;

    char label[10], opcode[10], operand[10], oOpcode[10], oOmc[10], sLabel[10], sVal[10];
    int locctr = 0, start;

    fin = fopen("input.txt", "r");
    finter = fopen("intermediate.txt", "w+");
    fopt = fopen("optab.txt", "r");
    fsym = fopen("symtab.txt", "w+");
    flen = fopen("len.txt", "w+");

    fscanf(fin, "%s%s%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0)
    {
        start = atoi(operand);
        locctr = start;
        fprintf(finter, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fin, "%s%s%s", label, opcode, operand);
    }

    while (strcmp(opcode, "END") != 0)
    {
        if (strcmp(label, "**") != 0)
        {
            fprintf(fsym, "%s\t%d\n", label, locctr);
        }
        rewind(fopt);
        int flag = 0;
        while (!feof(fopt))
        {
        }
    }

    fclose(fin);
    fclose(finter);
    fclose(fopt);
    fclose(fsym);
    fclose(flen);

    return 0;
}