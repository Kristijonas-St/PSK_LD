#ifndef BAZINE_H
#define BAZINE_H
#include "bazine.h"
#include <set>
#endif

using namespace std;

class zaidejas : public bazine
{
public:
    
    bool ar_galima_taip_pastatyti()
    {
        taip_galima_pastatyti_laiva = 0;
        laivai_dubliuojasi = 0;
        netinkamas_laivo_ilgis = 0;
        set <int> visi_nuliai;
        int testukui[8], k = 0;
        visi_nuliai.clear();
        if (stovejimas == 'h')
        {
            if (eilute <= 7 && galas_x <= 8 && pradzia_x < 8)
            {
                if ((indeksas == 0 && galas_x - pradzia_x == 4) || (indeksas == 1 && galas_x - pradzia_x == 3) || ((indeksas == 2 || indeksas == 3) && galas_x - pradzia_x == 2) || (indeksas == 4 && galas_x - pradzia_x == 1))
                {
                    for (int j = pradzia_x - 1; j < galas_x; j++) visi_nuliai.insert(lenta[eilute - 1][j]);
                    if (visi_nuliai.size() == 1)
                    {
                        for (auto x : visi_nuliai) testukui[0] = x;
                        if (testukui[0] == 0) taip_galima_pastatyti_laiva = true;
                        else
                        {
                            laivai_dubliuojasi = true;
                            taip_galima_pastatyti_laiva = false;
                        }
                    }
                    else
                    {
                        laivai_dubliuojasi = true;
                        taip_galima_pastatyti_laiva = false;
                    }
                }
            }
            else
            {
                taip_galima_pastatyti_laiva = false;
                netinkamas_laivo_ilgis = true;
            }
        } // cia baigiasi horizontaliai
        else
        {
            if (stulpelis <= 8 && galas_y <= 7 && pradzia_y < 7)
            {
                if ((indeksas == 0 && galas_y - pradzia_y == 4) || (indeksas == 1 && galas_y - pradzia_y == 3) || ((indeksas == 2 || indeksas == 3) && galas_y - pradzia_y == 2) || (indeksas == 4 && galas_y - pradzia_y == 1))
                {
                    for (int i = pradzia_y - 1; i < galas_y; i++) visi_nuliai.insert(lenta[i][stulpelis - 1]);
                    if (visi_nuliai.size() == 1)
                    {
                        for (auto x : visi_nuliai) testukui[0] = x;
                        if (testukui[0] == 0) taip_galima_pastatyti_laiva = true;
                        else
                        {
                            laivai_dubliuojasi = true;
                            taip_galima_pastatyti_laiva = false;
                        }
                    }
                    else
                    {
                        laivai_dubliuojasi = true;
                        taip_galima_pastatyti_laiva = false;
                    }
                }
            }
            else
            {
                taip_galima_pastatyti_laiva = false;
                netinkamas_laivo_ilgis = true;
            }
        }
        
        visi_nuliai.clear();
        for (int i = 0; i < 8; i++) testukui[i] = 0;
        
        return taip_galima_pastatyti_laiva;
    }
    void pastatymas()
    {
        if (indeksas == 0 || taip_galima_pastatyti_laiva)
        {
            if (stovejimas == 'h')  
            {
                for (int j = pradzia_x - 1; j < galas_x; j++)
                {
                    if (indeksas == 0) lenta[eilute - 1][j] = 5;
                    else if (indeksas == 1) lenta[eilute - 1][j] = 4;
                    else if (indeksas == 2) lenta[eilute - 1][j] = 3;
                    else if (indeksas == 3) lenta[eilute - 1][j] = 2;
                    else if (indeksas == 4) lenta[eilute - 1][j] = 1;
                }
            }
            else
            {
                for (int i = pradzia_y - 1; i < galas_y; i++)
                {
                    if (indeksas == 0) lenta[i][stulpelis - 1] = 5;
                    else if (indeksas == 1) lenta[i][stulpelis - 1] = 4;
                    else if (indeksas == 2) lenta[i][stulpelis - 1] = 3;
                    else if (indeksas == 3) lenta[i][stulpelis - 1] = 2;
                    else if (indeksas == 4) lenta[i][stulpelis - 1] = 1;
                        
                }
            }
            if (indeksas == 0)
            {
                for (int i = 0; i < 7; i++)
                    for (int j = 0; j < 8; j++)
                        if (lenta[i][j] == 5) display[i][j] = 2;
                        else display[i][j] = '.';
            }
            else
            {
                for (int i = 0; i < 7; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        if (lenta[i][j] == 4) display[i][j] = 3;
                        else if (lenta[i][j] == 3) display[i][j] = 4;
                        else if (lenta[i][j] == 2) display[i][j] = 5;
                        else if (lenta[i][j] == 1) display[i][j] = 6;
                    }
                }
            }
            parodyk_lentas();
        }
    } 
    void padidiname_indeksas()
    {
        indeksas++;
    }
    void errorai()
    {

        if (laivai_dubliuojasi) cout << "Klaida: lavai dubliuojasi." << endl;
        else if (eilute > 7) cout << "Klaida: netinkama eilute." << endl;
        else if (stulpelis > 8) cout << "Klaida: netinkamas stulpelis. " << endl;
        else if ((galas_x == pradzia_x && galas_x !=0) || (galas_y == pradzia_y && galas_y != 0)) cout << "Klaida: laivo pradzia ir galas negali sutapti." << endl;
        else if ((galas_x > 8 && pradzia_x < 8) || (galas_y > 7 && pradzia_y < 7)) cout << "Klaida: galas netinkamoje pozicijoje. Bandykite ivesti kitas koordinates." << endl;
        else if ((galas_x < 8 && pradzia_x > 8) || (galas_y < 7 && pradzia_y > 7)) cout << "Klaida: priekis netinkamoje pozicijoje. Bandykite ivesti kitas koordinates." << endl;
        else if ((galas_x > 8 && pradzia_x > 8) || (galas_y > 7 && pradzia_y > 7)) cout << "Netinkamos koordinates. Bandykite ivesti kitas koordinates." << endl;
        else if (netinkamas_laivo_ilgis) cout << "Klaida: netinkamas laivo ilgis. Bandykite ivesti kitas koordinates." << endl; 
        else if (indeksas == 0 && (galas_x - pradzia_x != 4 || galas_y - pradzia_y != 4)) cout << "Klaida: laivas neuzima 5 poziciju. Bandykite ivesti kitas koordinates." << endl;
        else if (indeksas == 1 && (galas_x - pradzia_x != 3 || galas_y - pradzia_y != 3)) cout << "Klaida: laivas neuzima 4 poziciju. Bandykite ivesti kitas koordinates." << endl;
        else if ((indeksas == 2 || indeksas == 3) && (galas_x - pradzia_x != 2 || galas_y - pradzia_y != 2)) cout << "Klaida: laivas neuzima 3 poziciju. Bandykite ivesti kitas koordinates." << endl;
        else if ((indeksas == 4) && (galas_x - pradzia_x != 1 || galas_y - pradzia_y != 1)) cout << "Klaida: laivas neuzima 2 poziciju. Bandykite ivesti kitas koordinates." << endl;    
    }

};