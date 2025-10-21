#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <set>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <map>
using namespace std;
// privaloma panaudoti konstruktoriai, destruktorius, perkrovimai, paveldimumai
class bazine
{
protected:
    char display[7][8], sablonas[7][8], kdisplay[7][8], stovejimas;
    int lenta[7][8] = { 0 }, klenta[7][8], indeksas;
    int pradzia_x, galas_x, eilute;
    int pradzia_y, galas_y, stulpelis;
    int eil, stul, temp_eil, temp_stul;
    int pataikytas_laivas, kompo_pataikytas_laivas;
    bool taip_galima_pastatyti_laiva, laivai_dubliuojasi, netinkamas_laivo_ilgis;
    //
    bool pataikei = false, kompas_pataikei = false;
    vector <int> kompo_sautos_eilutes;
    vector <int> kompo_sauti_stulpeliai;
    bool pataiko_virs = false, pataiko_zemyn = false, pataiko_kaire = false, pataiko_desine = false;
    bool hit = false;
    int atskaita_eil, atskaita_stul;

public:

    bazine() : pradzia_x(0), pradzia_y(0), galas_x(0), galas_y(0), indeksas(0), eilute(0), stulpelis(0), taip_galima_pastatyti_laiva(0), stovejimas(0), laivai_dubliuojasi(0), netinkamas_laivo_ilgis(0), eil(0), stul(0), temp_eil(0), temp_stul(0), pataikytas_laivas(0), kompo_pataikytas_laivas(0) {}
    bazine(int x, int y, int z, int a, int ind) : pradzia_x(x), pradzia_y(y), galas_x(z), galas_y(a), indeksas(ind) {}
    ~bazine() {}
    
    void operator ++(int)
    {
        cout << endl;
        cout << indeksas + 1 << ". Horizontaliai ar vertikaliai (h ar v)? ";
        cin >> stovejimas;

        if (stovejimas == 'h')
        {
            cout << "Iveskite eilutes nr. ir horizontalias koordinates: ";
            cin >> eilute >> pradzia_x >> galas_x;
        }
        else
        {
            cout << "Iveskite stulpelio nr. ir vertikalias koordintas: ";
            cin >> stulpelis >> pradzia_y >> galas_y;
        }     
    }
    void parodyk_lentas()
    {
        /*cout << endl << endl;
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 8; j++) cout << lenta[i][j];
            cout << endl;
        }
        cout << endl << endl;*/
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 8; j++)
            if (lenta[i][j] == 8)
            {
                nustatyti_raudona_spalva();
                cout << display[i][j];
                nustatyti_zalia_spalva();
            }
            else cout << display[i][j];
            cout << endl;
        }
    }
    void nustatyti_geltona_spalva()
    {
        cout << "\033[33m";
    }
    void nustatyti_raudona_spalva()
    {
        cout << "\033[31m";
    }
    void nustatyti_zalia_spalva()
    {
        cout << "\033[32m";
    }
    void nustatyti_melyna_spalva()
    {
        cout << "\033[34m";
    }
    void grazinti_spalva()
    {
        cout << "\033[0m";
    }
    void parodyk_sablona()
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (klenta[i][j] == 8)
                {
                    nustatyti_raudona_spalva();
                    cout << kdisplay[i][j];
                    nustatyti_geltona_spalva();
                }
                else if (klenta[i][j] == 9)
                {
                    nustatyti_melyna_spalva();
                    cout << sablonas[i][j];
                    nustatyti_geltona_spalva();
                }
                else cout << sablonas[i][j];
            }
            cout << endl;
        }
    }
    void rodyk()
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 8; j++) 
            {
                if (klenta[i][j] == 8)
                {
                    nustatyti_raudona_spalva();
                    cout << kdisplay[i][j];
                    nustatyti_geltona_spalva();
                }
                else if (klenta[i][j] == 9)
                {
                    nustatyti_melyna_spalva();
                    cout << sablonas[i][j];
                    nustatyti_geltona_spalva();
                }
                else cout << kdisplay[i][j];
            }
            cout << endl;
        }
    }
    void saudymas()
    {
        cout << "Iveskite eilute ir stulpeli: ";
        while (true)
        {
            cin >> eil >> stul;
            if (eil <= 7 && stul <= 8) break;
            else cout << "Netinkama ivestis. Iveskite dar karta." << endl;
        }

        if (kdisplay[eil - 1][stul - 1] != '.')
        {
            pataikei = true;
            pataikytas_laivas = klenta[eil - 1][stul - 1];
            klenta[eil - 1][stul - 1] = 8;
        }
        else
        {
            pataikei = false;
            klenta[eil - 1][stul - 1] = 9;
        }
    }
    void kompo_saudymas()
    {
        if (!hit)
        {
            int temp1 = 0, temp2 = 0;
            bool pasikartojo = false, baigesi = false;
            srand(time(0));
            while (true)
            {
                temp_eil = rand() % 7 + 1;
                temp_stul = rand() % 8 + 1;
                kompo_sautos_eilutes.push_back(temp_eil);
                kompo_sauti_stulpeliai.push_back(temp_stul);
                //cout << "Vektorius: " << endl;
                for (int i = 0; i < kompo_sautos_eilutes.size(); i++)// cout << kompo_sautos_eilutes[i] << " " << kompo_sauti_stulpeliai[i] << endl;
                {
                    temp1 = kompo_sautos_eilutes[i];
                    temp2 = kompo_sauti_stulpeliai[i];
                    for (int j = i + 1; j < kompo_sautos_eilutes.size(); j++)
                    {
                        if (kompo_sautos_eilutes[j] == temp1 && kompo_sauti_stulpeliai[j] == temp2)
                        {
                            //cout << "PASIKARTOJO" << endl;
                            kompo_sautos_eilutes.erase(kompo_sautos_eilutes.begin() + j);
                            kompo_sauti_stulpeliai.erase(kompo_sauti_stulpeliai.begin() + j);
                            pasikartojo = true;
                        }
                    }
                }
                //for (int i = 0; i < kompo_sautos_eilutes.size(); i++) cout << kompo_sautos_eilutes[i] << " " << kompo_sauti_stulpeliai[i] << endl;
                if (!pasikartojo)
                {
                    cout << "Kompiuteris sauna eil " << temp_eil << " ir stul " << temp_stul << endl;
                    break;
                }
                //if (lenta[temp_eil - 1][temp_stul - 1] != 9 && lenta[temp_eil - 1][temp_stul - 1] != 8) break;
            }
            if (lenta[temp_eil - 1][temp_stul - 1] != 0 && lenta[temp_eil - 1][temp_stul - 1] != 8 && lenta[temp_eil - 1][temp_stul - 1] != 9)
            {
                hit = true;
                cout << "Kompiuteris pataike: " << temp_eil << " " << temp_stul << endl;
                kompo_pataikytas_laivas = lenta[temp_eil - 1][temp_stul - 1];
                lenta[temp_eil - 1][temp_stul - 1] = 8;
                atskaita_eil = temp_eil;
                atskaita_stul = temp_stul;
            }
            else 
            {
                cout << "Kompiuteris nepataike. " << endl;
                lenta[temp_eil - 1][temp_stul - 1] = 9;
            }
        }
        else
        {      
            if (lenta[atskaita_eil - 1][atskaita_stul - 2] != 0 && lenta[atskaita_eil - 1][atskaita_stul - 2] != 8 && lenta[atskaita_eil - 1][atskaita_stul - 2] != 9) // kairen
            {
                cout << "Kompiuteris sauna: " << atskaita_eil << " " << atskaita_stul - 1 << endl;               
                lenta[atskaita_eil - 1][atskaita_stul - 2] = 8;
                atskaita_stul--;
                pataiko_kaire = true;
            }
            else if (lenta[atskaita_eil - 1][atskaita_stul] != 0 && lenta[atskaita_eil - 1][atskaita_stul] != 8 && lenta[atskaita_eil - 1][atskaita_stul] != 9) // desine
            {
                cout << "Kompiuteris sauna: " << atskaita_eil << " " << atskaita_stul + 1 << endl;                
                lenta[atskaita_eil - 1][atskaita_stul] = 8;
                atskaita_stul++;
                pataiko_desine = true;
            }
            else if (lenta[atskaita_eil - 2][atskaita_stul - 1] != 0 && lenta[atskaita_eil - 2][atskaita_stul - 1] != 8 && lenta[atskaita_eil - 2][atskaita_stul - 1] != 9) // virsu
            {
                cout << "Kompiuteris sauna: " << atskaita_eil - 1 << " " << atskaita_stul << endl;                
                lenta[atskaita_eil - 2][atskaita_stul - 1] = 8;
                atskaita_eil--;
                pataiko_virs = true;
            }
            else if (lenta[atskaita_eil][atskaita_stul - 1] != 0 && lenta[atskaita_eil][atskaita_stul - 1] != 8 && lenta[atskaita_eil][atskaita_stul - 1] != 9) // zemyn
            {
                cout << "Kompiuteris sauna: " << atskaita_eil + 1 << " " << atskaita_stul - 1 << endl;                
                lenta[atskaita_eil][atskaita_stul - 1] = 8;
                atskaita_eil++;
                pataiko_zemyn = true;
            }
            else hit = false;
        }
    }
        int kompas_pataike_i()
        {
            return kompo_pataikytas_laivas;
        }
        bool get_pataikei()
        {
            if (pataikei) return true;
        }
        bool get_kompas_pataikei()
        {
            if (kompas_pataikei) return true;
        }
        int get_pataikytas_laivas()
        {
            return pataikytas_laivas;
        }
};

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
void titulinis()
{
    cout << "                   LAIVU MUSIS" << endl;
    cout << "   Tikslas: nuskadinti visus 5 oponento  laivus" << endl;
    cout << "               Imanomi penki laivai:" << endl;
    cout << "   1. Carrier - simbolis    " << (char)2 << ", uzima 5 skylutes" << endl;
    cout << "   2. Battleship - simbolis " << (char)3 << ", uzima 4 skylutes" << endl;
    cout << "   3. Cruiser - simbolis    " << (char)4 << ", uzima 3 skylutes" << endl;
    cout << "   4. Submarine - simbolis  " << (char)5 << ", uzima 3 skylutes" << endl;
    cout << "   5. Destroyer - simbolis  " << (char)6 << ", uzima 2 skylutes" << endl;
    cout << endl << "                    Taisykles: " << endl;
    cout << "   1. Jei laivus susistatyti norite pats, verta pamineti, kad jie NEGALI eiti kiauriai vienas kita." << endl;
    cout << "   2. Per ejima galima sauti TIK VIENA karta." << endl;
    cout << "   3. Pataikius i kazkuri laiva, jums bus pranesta i koki butent laiva pataikete." << endl;
    cout << "   4. Zaidimas baigiasi tada, kai kazkurio zaidejo laivynas yra sunaikintas." << endl;

}
void pabaigos_patikra(map <string, int> pataikymai, set<bool> ar_jau_zmogus_laimejo, string laivu_pavadinimai[], bool zmogus_laimejo[], int &ejimas, bool &end_game, map <string, int> kompo_pataikymai, set<bool> kompas_jau_laimejo, bool kompas_laimejo[])
{
    for (auto a : pataikymai)
    {
        if (a.first == laivu_pavadinimai[0] && a.second == 5) zmogus_laimejo[0] = true;
        else if (a.first == laivu_pavadinimai[1] && a.second == 4) zmogus_laimejo[1] = true;
        else if (a.first == laivu_pavadinimai[2] && a.second == 3) zmogus_laimejo[2] = true;
        else if (a.first == laivu_pavadinimai[3] && a.second == 3) zmogus_laimejo[3] = true;
        else if (a.first == laivu_pavadinimai[4] && a.second == 2) zmogus_laimejo[4] = true;
    }
    for (int i = 0; i < 5; i++) ar_jau_zmogus_laimejo.insert(zmogus_laimejo[i]);
    if (ar_jau_zmogus_laimejo.size() == 1)
    {
        for (auto baik_jau : ar_jau_zmogus_laimejo)
        {
            if (baik_jau == 1)
            {
                cout << "Sveikiname laimejus laivu musi! Jus sekmingai sunaikinote prieso laivyna. " << endl;
                cout << "Atliktu ejimu skaicius: " << ejimas << endl;
                end_game = true;
                return;
            }
        }
    }
    ar_jau_zmogus_laimejo.clear();

    for (auto a : kompo_pataikymai)
    {
        if (a.first == laivu_pavadinimai[0] && a.second == 5) kompas_laimejo[0] = true;
        else if (a.first == laivu_pavadinimai[1] && a.second == 4) kompas_laimejo[1] = true;
        else if (a.first == laivu_pavadinimai[2] && a.second == 3) kompas_laimejo[2] = true;
        else if (a.first == laivu_pavadinimai[3] && a.second == 3) kompas_laimejo[3] = true;
        else if (a.first == laivu_pavadinimai[4] && a.second == 2) kompas_laimejo[4] = true;
    }
    for (int i = 0; i < 5; i++) kompas_jau_laimejo.insert(kompas_laimejo[i]);
    if (kompas_jau_laimejo.size() == 1)
    {
        for (auto baik_jau : kompas_jau_laimejo)
        {
            if (baik_jau == 1)
            {
                cout << "Deja! Kompiuteris sunaikino jusu laivyna..." << endl;
                cout << "Atliktu ejimu skaicius: " << ejimas << endl;
                end_game = true;
                return;
            }
        }
    }
    ar_jau_zmogus_laimejo.clear();
}
void zaidimas(zaidejas x, kompiuteris y)
{
    string taip;
    taip = "ne";
    map <string, int> pataikymai, kompo_pataikymai;
    set <bool> ar_jau_zmogus_laimejo, kompas_jau_laimejo;
    bool leidimas = false, zmogus_laimejo[5], end_game = false, kompas_laimejo[5];
    string laivu_pavadinimai[5] = { "Carrier (ilgis 5): ", "Battleship (ilgis 4): ", "Cruiser (ilgis 3): ", "Submarine (ilgis 3): ", "Destroyer (ilgis 2): " };

    cout << "Iveskite laivu h/v, pradzios ir pabaigos koordinates (pvz.: v 1 1, h 1 5, h 2 9). Ivesti 2 skaicius! Lentos ismatavimai 7 eilutes, 8 stulpeliai " << endl;
    y.paskyrimas();    
    
    for (int i = 0; i < 5; i++)
    {
        while (true)
        {
            x++;
            leidimas = x.ar_galima_taip_pastatyti();
            if (x.ar_galima_taip_pastatyti()) // leidimas
            {
                x.pastatymas();
                x.padidiname_indeksas();
                break;
            }
           else x.errorai();
        }
        pataikymai[laivu_pavadinimai[i]] = 0;
        zmogus_laimejo[i] = false;
        kompas_laimejo[i] = false;
    }
    
    cout << "Ar norite pradeti? Iveskite 'taip'. " << endl;
    while (taip != "taip") cin >> taip;
    system("cls");
    
    string testuoju, laivas;
    int kiekis = 0, ejimas = 1;
    char ch[5] = { 2, 3, 4, 5, 6 };
    while (true)
    {
        for (int i = 0; i < 5; i++) cout << laivu_pavadinimai[i] << ch[i] << "; ";
        cout << endl << endl;
        cout << "Raudona - pataikyta, melyna - nepataikyta." << endl << endl;
        cout << "Kompiuteris:" << endl;
        y.nustatyti_geltona_spalva();
        y.rodyk();
        cout << endl << endl;
        y.parodyk_sablona();
        y.grazinti_spalva();
        cout << endl << endl;
        cout << "Jus:" << endl;
        x.nustatyti_zalia_spalva();
        x.parodyk_lentas();
        x.grazinti_spalva();
        
        cout << endl << "Pataikymai" << endl;
        for (auto a : pataikymai)
        {
            //cout << setw(25) << left << a.first << " " << a.second << endl;
            cout << setw(25) << left << a.first << " ";
            if ((a.first == laivu_pavadinimai[0] && a.second == 5) || (a.first == laivu_pavadinimai[1] && a.second == 4) || (a.first == laivu_pavadinimai[2] && a.second == 3) || (a.first == laivu_pavadinimai[3] && a.second == 3) || (a.first == laivu_pavadinimai[4] && a.second == 2))
            {
                y.nustatyti_raudona_spalva();
                cout << a.second << endl;
                y.grazinti_spalva();
            }
            else cout << a.second << endl;
        }
        pabaigos_patikra(pataikymai, ar_jau_zmogus_laimejo, laivu_pavadinimai, zmogus_laimejo, ejimas, end_game, kompo_pataikymai, kompas_jau_laimejo, kompas_laimejo);
        if (end_game) return; 

        cout << ejimas << " ejimas: ";
        
        y.saudymas();
        if (y.get_pataikei())
        {
            cout << "PATAIKETE!" << endl;
            y.i_mane_pataike();
            if (y.get_pataikytas_laivas() == 5)
            {
                cout << "Pataikyta i Carrier. " << endl;
                pataikymai[laivu_pavadinimai[0]]++;
            }
            else if (y.get_pataikytas_laivas() == 4)
            {
                cout << "Pataikyta i Battleship. " << endl;
                pataikymai[laivu_pavadinimai[1]]++;
            }
            else if (y.get_pataikytas_laivas() == 3)
            {
                cout << "Pataikyta i Cruiser. " << endl;
                pataikymai[laivu_pavadinimai[2]]++;
            }
            else if (y.get_pataikytas_laivas() == 2)
            {
                cout << "Pataikyta i Submarine. " << endl;
                pataikymai[laivu_pavadinimai[3]]++;
            }
            else if (y.get_pataikytas_laivas() == 1)
            {
                cout << "Pataikyta i Destroyer. " << endl;
                pataikymai[laivu_pavadinimai[4]]++;
            }
        }
        else cout << "NEPATAIKETE!" << endl;

        x.kompo_saudymas();
        if (x.kompas_pataike_i() == 5) kompo_pataikymai[laivu_pavadinimai[0]]++;
        else if (x.kompas_pataike_i() == 4) kompo_pataikymai[laivu_pavadinimai[1]]++;
        else if (x.kompas_pataike_i() == 3) kompo_pataikymai[laivu_pavadinimai[2]]++;
        else if (x.kompas_pataike_i() == 2) kompo_pataikymai[laivu_pavadinimai[3]]++;
        else if (x.kompas_pataike_i() == 1) kompo_pataikymai[laivu_pavadinimai[4]]++;

        ejimas++;
        this_thread::sleep_for(std::chrono::seconds(3));
        system("cls");   
    }
}
int main()
{
    zaidejas x;
    kompiuteris y;
    titulinis();
    zaidimas(x, y);
}
