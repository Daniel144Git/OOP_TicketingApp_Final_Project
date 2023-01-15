#include <iostream>
#include <string>
#include <ctime>
#include "Eveniment.h"
#include "Zona.h"
#include "Bilet.h"
#include "BiletStudent.h"
#pragma warning(disable:4996)
using namespace std;

void vizualizareBilete(Bilet* bilete, int nr) {
    if (bilete != nullptr && nr > 0) {
        for (int i = 0; i < nr; i++) {
            cout << "Bilet " << (i + 1) << ": " << endl << bilete[i] << endl;
        }
    }
    else cout << endl << "Nu ai bilete." << endl;
}
void salvareBileteBinar(Bilet* bilete, int nr) {
    if (bilete != nullptr && nr > 0) {
        ofstream f;
        f.open("bilet.bin", ios::binary | ios::out);
        f.write((char*)&nr, sizeof(nr));
        for (int i = 0; i < nr; i++) {
            bilete[i].serializare(f);
        }
        f.close();
    }
    else cout << endl << "Nu ai bilete de serializat." << endl;
}
void salvareBileteText(Bilet* bilete, int nr) {
    if (bilete != nullptr && nr > 0) {
        ofstream f;
        f.open("bilet.txt", ios::out);
        f << nr << endl;
        for (int i = 0; i < nr; i++) {
            f << bilete[i];
        }
        f.close();
        cout << endl << "Salvat in text!" << endl;
    }
    else cout << endl << "Nu ai bilete de salvat." << endl;
}
Bilet* restaurareBileteBinar(int& nr) {
    nr = 0;
    Bilet* bilete = nullptr;
    ifstream f;
    f.open("bilet.bin", ios::binary | ios::in);
    f.read((char*)&nr, sizeof(nr));
    if (nr > 0) {
        bilete = new Bilet[nr];
        for (int i = 0; i < nr; i++) {
            bilete[i].deserializare(f);
        }

    }
    else cout << endl << "Nu ai bilete de serializat." << endl;
    f.close();
    return bilete;
}
Bilet cumparaBilet(Eveniment& ales, int& rand, int& loc, int NR_EVENIMENTE, Eveniment* evenimente) {
    int nrZone, alegere = 0;
    string type = "";
    while (alegere < 1 || alegere > NR_EVENIMENTE) {
        cout << "Alegeti un eveniment, sau tastati 'exit' pentru a iesi:" << endl;
        for (int i = 0; i < NR_EVENIMENTE; i++) {
            cout << (i + 1) << ". ";
            evenimente[i].afiseazaDetalii();
            cout << endl;
        }
        cout << "Decizia ta:";
        cin >> type;
        alegere = atoi(type.c_str());
    }
    ales = evenimente[((int)alegere) - 1];
    cout << endl << "Ai ales:" << endl << ales << endl;
    Zona* zone = Zona::getZonePentruEveniment(ales.getCategorie(), nrZone);
    cout << "Zonele disponibile sunt: " << endl;
    for (int i = 0; i < nrZone; i++) {
        cout << zone[i] << endl;
    }
    alegere = 0;
    while (alegere<1 || alegere > nrZone) {
        cout << "Alege o zona (numar de la 1 la " << nrZone << "):";
        cin >> type;
        alegere = atoi(type.c_str());
    }
    ales.setZona(zone[alegere - 1]);
    cout << "Ai ales: " << endl << ales.getZona() << endl;
    Bilet bilet(ales, 10 * alegere * (++rand + ++loc), rand, loc);
    cout << "Biletul tau este:" << endl << bilet << endl;
    ofstream f; f.open("bilet.txt", ios::out);
    f << bilet;
    f.close();

    return bilet;
}

BiletStudent cumparaBiletStudent(Eveniment& ales, int& rand, int& loc, int NR_EVENIMENTE, Eveniment* evenimente) {
    bool student = false; string type = "";
    cout << endl << "Sunteti student? (da sau nu)";
    cin >> type;
    if (type == "da")
        student = true;
    int nrZone, alegere = 0;

    while (alegere < 1 || alegere > NR_EVENIMENTE ) {
        cout << "Alegeti un eveniment, sau tastati 'exit' pentru a iesi:" << endl;
        for (int i = 0; i < NR_EVENIMENTE; i++) {
            cout << (i + 1) << ". ";
            evenimente[i].afiseazaDetalii();
            cout << endl;
        }
        cout << "Decizia ta:";
        cin >> type;
        alegere = atoi(type.c_str());
    }
    ales = evenimente[((int)alegere) - 1];
    cout << endl << "Ai ales:" << endl << ales << endl;
    Zona* zone = Zona::getZonePentruEveniment(ales.getCategorie(), nrZone);
    cout << "Zonele disponibile sunt: " << endl;
    for (int i = 0; i < nrZone; i++) {
        cout << zone[i] << endl;
    }
    alegere = 0;
    while (alegere<1 || alegere > nrZone) {
        cout << "Alege o zona (numar de la 1 la " << nrZone << "):";
        cin >> type;
        alegere = atoi(type.c_str());
    }
    ales.setZona(zone[alegere - 1]);
    cout << "Ai ales: " << endl << ales.getZona() << endl;
    BiletStudent bilet(ales, 10 * alegere * (++rand + ++loc), rand, loc, student);
    cout << "Biletul tau este:" << endl << bilet << endl;
    ofstream f; f.open("bilet.txt", ios::out);
    f << bilet;
    f.close();

    return bilet;
}

void prezentareLaEveniment(Bilet* bilete, int nr, int NR_EVENIMENTE, Eveniment* evenimente) {
    int nrZone, alegere = 0;
    string type = "";
    while (alegere < 1 || alegere > NR_EVENIMENTE) {
        cout << "Alegeti un eveniment la care doriti sa participati, sau tastati 'exit' pentru a iesi:" << endl;
        for (int i = 0; i < NR_EVENIMENTE; i++) {
            cout << (i + 1) << ". ";
            evenimente[i].afiseazaDetalii();
            cout << endl;
        }
        cout << "Decizia ta:";
        cin >> type;
        alegere = atoi(type.c_str());
    }
    Eveniment eveniment = evenimente[((int)alegere) - 1];
    cout << endl << "Ai ales:" << endl << eveniment << endl;

    cout << "Dati codul:";
    string cod;
    cin >> cod;
    Bilet* bilet = nullptr;
    if (bilete == nullptr || nr < 1) {
        cout << endl << "Nu ai bilete." << endl;
        return;
    }
    for (int i = 0; i < nr; i++) {
        if (bilete[i].getCod() == cod) {
            bilet = &bilete[i];
        }
    }
    if (bilet == nullptr) {
        cout << "Bilet invalid!" << endl;
        return;
    }
    eveniment.setZona(bilet->getEveniment().getZona());
    bilet->validareBilet(eveniment, bilet->getEveniment().getZona()) ? (cout << "Bilet valid" << endl) : cout << "Bilet invalid";
}
void afiseazaOptiuni() {
    cout << endl << "Bine ai venit!" << endl;
    cout << "Alege ce doresti:" << endl;
    cout << "1. Afiseaza evenimente disponibile si cumpara bilet." << endl;
    cout << "2. Prezinta-te la eveniment." << endl;
    cout << "3. Vizualizeaza-ti biletele" << endl;
    cout << "4. Salveaza-ti biletele (in binar)" << endl;
    cout << "5. Cumpara bilet student" << endl;
    cout << "6. Salveaza-ti biletele (in text)" << endl;
}
Bilet* adaugabilet(Bilet noua, Bilet* bilete, int& nr) {
    Bilet* copy = nullptr;
    if (bilete != nullptr && nr > 0) {
        copy = new Bilet[nr + 1];
        for (int i = 0; i < nr; i++) {
            copy[i] = bilete[i];
        }
        copy[nr] = noua;
        nr++;
    }
    else {
        copy = new Bilet[1];
        copy[0] = noua; nr = 1;
    }
    return copy;
}
int main(int nrArg, char* args[]) {
    BiletStudent biletstud;
    int nrBilete = 0;
    Bilet* bilete = nullptr;
    if (nrArg == 2) {
        ifstream f; f.open(args[1], ios::in);
        int nrB = 0;
        f >> nrB;
        if (nrB > 0) {
            nrBilete = nrB;
            bilete = new Bilet[nrB];
            for (int i = 0; i < nrB; i++) {
                f >> bilete[i];
            }
        }
        f.close();

    }
    else {
        nrBilete = 0;
        bilete = restaurareBileteBinar(nrBilete);

    }
    int NR_EVENIMENTE;
    Eveniment* evenimente = Eveniment::genereazaEvenimente(NR_EVENIMENTE);

    Bilet b;
    string type = ""; int ales = 0; int rand = 0, loc = 0; Eveniment e;
    while (type != "exit") {
        afiseazaOptiuni();
        cout << "Decizia ta:";
        cin >> type;
        try {
            ales = atoi(type.c_str());
        }
        catch (exception e) {
            ales = 0;
        }

        if (ales == 1) {
            if (nrBilete < 5) {
                Bilet bilet = cumparaBilet(e, rand, loc, NR_EVENIMENTE, evenimente);
                bilete = adaugabilet(bilet, bilete, nrBilete);
            }
            else cout << "Aveti deja 5 bilete." << endl;
        }
        else if (ales == 2) prezentareLaEveniment(bilete, nrBilete, NR_EVENIMENTE, evenimente);
        else if (ales == 3) vizualizareBilete(bilete, nrBilete);
        else if (ales == 4) salvareBileteBinar(bilete, nrBilete);
        else if (ales == 5) {
            if (nrBilete < 5) {
                Bilet bilet = cumparaBiletStudent(e, rand, loc, NR_EVENIMENTE, evenimente);
                bilete = adaugabilet(bilet, bilete, nrBilete);
            }
            else cout << "Aveti deja 5 bilete." << endl;
        }
        else if (ales == 6) salvareBileteText(bilete, nrBilete);

    }

    return 0;
}