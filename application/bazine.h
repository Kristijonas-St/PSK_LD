#include <vector>
#include <iostream>

using namespace std;

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