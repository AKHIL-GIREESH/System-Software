#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char opcode[10], label[10], operand[10], slabel[10], svalue[10], oopcode[10], ovalue[10];
    int locctr, c, flag = 0, length;
    FILE *finp, *fint, *fopt, *fsym, *flen;
    finp = fopen("input.txt", "r");
    fint = fopen("inter.txt", "w+");
    fopt = fopen("optab.txt", "r");
    fsym = fopen("symtab.txt", "w+");
    flen = fopen("len.txt", "w+");

    fscanf(finp, "%s%s%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0)
    {
        locctr = atoi(operand);
        fprintf(fint, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(finp, "%s%s%s", label, opcode, operand);
    }
    else
    {
        locctr = 0;
    }
    while (strcmp(opcode, "END") != 0)
    {
        fprintf(fint, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        if (strcmp(label, "**") != 0)
        {
            fprintf(fsym, "%s\t%d\n", label, locctr);
        }
        rewind(fopt);
        flag = 0;
        while (!feof(fopt))
        {
            fscanf(fopt, "%s%s", oopcode, ovalue);
            if (strcmp(oopcode, opcode) == 0)
            {
                locctr += 3;
                flag = 1;
                break;
            }
        }
        if (strcmp(opcode, "WORD") == 0)
        {
            locctr += 3;
        }
        else if (strcmp(opcode, "RESW") == 0)
        {
            locctr += 3 * atoi(operand);
        }
        else if (strcmp(opcode, "RESB") == 0)
        {
            locctr += atoi(operand);
        }
        else if (strcmp(opcode, "BYTE") == 0)
        {
            if (operand[0] == 'C')
            {
                locctr += (strlen(operand) - 3);
            }
            else
            {
                locctr += 1;
            }
        }
        else if (flag == 0)
        {
            fprintf(fint, "ERROR\n");
            exit(0);
        }
        fscanf(finp, "%s%s%s", label, opcode, operand);
    }
    printf("Check");
    fprintf(fint, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    fclose(finp);
    fclose(fint);
    fclose(fopt);
    fclose(flen);
    fclose(fsym);

    return 0;
}