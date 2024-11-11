#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE *fin, *fopt, *fsym1, *fsym2, *fout;

    char label[10], mneu[10], oper[10], optMneu[10], optVal[10], symLabel[10], symVal[10], outObj1[10], outObj2[10], st[10], q[20];
    int start, locctr, m[50], iter1 = 0, iter2 = 0;

    fin = fopen("input.txt", "r");
    fopt = fopen("optab.txt", "r");
    fsym1 = fopen("mySymtab.txt", "w+");
    fsym2 = fopen("mySymtab2", "w+");
    fout = fopen("myOutput.txt", "w+");

    fscanf(fin, "%s%s%s", label, mneu, oper);
    if (strcmp(mneu, "START") == 0)
    {
        strcpy(st, mneu);
        start = atoi(oper);
        locctr = start;
    }

    fscanf(fin, "%s%s%s", label, mneu, oper);
    while (strcmp(mneu, "END") != 0)
    {
        if (strcmp(label, "-") == 0)
        {
            rewind(fopt);
            fscanf(fopt, "%s%s", optMneu, optVal);
            while (!feof(fopt))
            {
                if (strcmp(mneu, optMneu) == 0)
                {
                    fprintf(fsym1, "%s\t%s\n", oper, "*");
                    fprintf(fout, "%s\t%s\n", optVal, "0000");
                    m[iter1++] = locctr + 1;
                    locctr += 3;
                    break;
                }
                fscanf(fopt, "%s%s", optMneu, optVal);
            }
        }
        else
        {
            rewind(fsym1);
            fscanf(fsym1, "%s%s", symLabel, symVal);
            while (!feof(fsym1))
            {
                if (strcmp(label, symLabel) == 0)
                {
                    fprintf(fsym2, "%s\t%d\n", symLabel, locctr);
                    fprintf(fout, "%d\t%d\n", m[iter2++], locctr);
                    break;
                }
                fscanf(fsym1, "%s%s", symLabel, symVal);
            }

            if (strcmp(mneu, "WORD") == 0)
            {
                locctr += 3;
                fprintf(fout, "%s\t%s\n", oper, "#");
            }
            else if (strcmp(mneu, "BYTE") == 0)
            {
                for (int i = 2; i < strlen(oper) - 1; i++)
                {
                    q[i - 2] = oper[i];
                }
                locctr += strlen(oper) - 3;
                fprintf(fout, "%s\t%s\n", q, "-");
            }
            else if (strcmp(mneu, "RESB") == 0)
            {
                locctr += atoi(oper);
            }
            else if (strcmp(mneu, "RESW") == 0)
            {
                locctr += 3 * atoi(oper);
            }
        }

        fscanf(fin, "%s%s%s", label, mneu, oper);
    }

    fclose(fin);
    fclose(fopt);
    fclose(fsym1);
    fclose(fsym2);
    fclose(fout);

    return 0;
}