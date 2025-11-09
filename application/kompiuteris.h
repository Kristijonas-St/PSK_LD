#ifndef BAZINE_H
#define BAZINE_H
#include "bazine.h"
#endif
#include <iostream>

using namespace std;

class kompiuteris : public bazine
{
public:
    void paskyrimas()
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                klenta[i][j] = 0;
                kdisplay[i][j] = '.';
                sablonas[i][j] = '.';
            }
        }
        srand(time(0));
        int sustatymas = 0;
        sustatymas = rand() % 5 + 1;
        if (sustatymas == 1)
        {
            for (int j = 1; j < 6; j++) 
            {
                klenta[0][j] = 5;
                kdisplay[0][j] = 2;
            }
            for (int i = 3; i < 7; i++)
            {
                klenta[i][0] = 4;
                kdisplay[i][0] = 3;
            }
            for (int j = 2; j < 5; j++)
            {
                klenta[4][j] = 3;
                kdisplay[4][j] = 4;
            }
            for (int i = 3; i < 6; i++)
            {
                klenta[i][5] = 2;
                kdisplay[i][5] = 5;
            }
            for (int j = 2; j < 4; j++)
            {
                klenta[2][j] = 1;
                kdisplay[2][j] = 6;
            }
        }
        else if (sustatymas == 2)
        {
            for (int j = 1; j < 6; j++)
            {
                klenta[0][j] = 5;
                kdisplay[0][j] = 2;
            }
            for (int j = 1; j < 5; j++)
            {
                klenta[6][j] = 4;
                kdisplay[6][j] = 3;
            }
            for (int j = 2; j < 5; j++)
            {
                klenta[3][j] = 3;
                kdisplay[3][j] = 4;
            }
            for (int i = 0; i < 3; i++)
            {
                klenta[i][0] = 2;
                kdisplay[i][0] = 5;
            }
            for (int i = 4; i < 6; i++)
            {
                klenta[i][6] = 1;
                kdisplay[i][6] = 6;
            }
        }
        else if (sustatymas == 3)
        {
            for (int j = 0; j < 5; j++)
            {
                klenta[0][j] = 5;
                kdisplay[0][j] = 2;
            }
            for (int i = 1; i < 5; i++)
            {
                klenta[i][0] = 4;
                kdisplay[i][0] = 3;
            }
            for (int j = 5; j < 8; j++)
            {
                klenta[0][j] = 3;
                kdisplay[0][j] = 4;
            }
            for (int j = 1; j < 4; j++)
            {
                klenta[6][j] = 2;
                kdisplay[6][j] = 5;
            }
            for (int i = 5; i < 7; i++)
            {
                klenta[i][0] = 1;
                kdisplay[i][0] = 6;
            }
        }
        else if (sustatymas == 4)
        {
            for (int i = 2; i < 7; i++)
            {
                klenta[i][4] = 5;
                kdisplay[i][4] = 2;
            }
            for (int i = 3; i < 7; i++)
            {
                klenta[i][7] = 4;
                kdisplay[i][7] = 3;
            }
            for (int j = 5; j < 8; j++)
            {
                klenta[0][j] = 3;
                kdisplay[0][j] = 4;
            }
            for (int i = 4; i < 7; i++)
            {
                klenta[i][0] = 2;
                kdisplay[i][0] = 5;
            }
            for (int j = 0; j < 2; j++)
            {
                klenta[2][j] = 1;
                kdisplay[2][j] = 6;
            }
        }
        else if (sustatymas == 5)
        {
            for (int j = 0; j < 5; j++)
            {
                klenta[1][j] = 5;
                kdisplay[1][j] = 2;
            }
            for (int j = 4; j < 8; j++)
            {
                klenta[6][j] = 4;
                kdisplay[6][j] = 3;
            }
            for (int i = 3; i < 6; i++)
            {
                klenta[i][1] = 3;
                kdisplay[i][1] = 4;
            }
            for (int j = 3; j < 6; j++)
            {
                klenta[3][j] = 2;
                kdisplay[3][j] = 5;
            }
            for (int i = 0; i < 2; i++)
            {
                klenta[i][7] = 1;
                kdisplay[i][7] = 6;
            }
        }
    }
    void i_mane_pataike()
    {
        klenta[eil - 1][stul - 1] = 8;
    }
};