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

#ifndef BAZINE_H
#define BAZINE_H
#include "bazine.h"
#endif

#include "kompiuteris.h"
#include "zaidejas.h"

using namespace std;
// privaloma panaudoti konstruktoriai, destruktorius, perkrovimai, paveldimumai
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
