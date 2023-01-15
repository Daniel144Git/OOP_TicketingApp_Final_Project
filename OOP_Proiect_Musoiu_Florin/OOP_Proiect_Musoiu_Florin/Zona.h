#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "iSerializabil.h"
#pragma warning(disable:4996)
using namespace std;

class Zona : iSerializabil
{
private:
    string tipLoc;
    int nrRanduri;
    int* nrLocuriPerRand;

public:
    void serializare(ofstream& f) override
    {
        int length = tipLoc.length();
        length++;
        f.write((char*)&length, sizeof(length));
        f.write(tipLoc.c_str(), length);

        int v = nrRanduri;
        f.write((char*)&v, sizeof(v));

        for (int i = 0; i < v; i++) {
            f.write((char*)&nrLocuriPerRand[i], sizeof(nrLocuriPerRand[i]));
        }
    }
    void deserializare(ifstream& f) override
    {
        int length = 0, x = 0;

        f.read((char*)&length, sizeof(length));
        char* aux = new char[length];
        f.read(aux, length);
        this->tipLoc = aux;

        f.read((char*)&x, sizeof(x));
        if (x > 0) {
            int* copy = new int[x];
            for (int i = 0; i < x; i++) {
                f.read((char*)&copy[i], sizeof(copy[i]));
            }
            setRanduriPerLoc(x, copy);
        }

    }
    // constructori
    Zona() {
        this->tipLoc = "";
        this->nrRanduri = 0;
        this->nrLocuriPerRand = nullptr;
    }
    Zona(string tipLoc, int nrRanduri, int* nrLocuriPerRand) : Zona() {
        if (tipLoc == "loja" || tipLoc == "peluza" || tipLoc == "tribuna 1" || tipLoc == "tribuna 2" ||
            tipLoc == "categoria 1" || tipLoc == "VIP" || tipLoc == "normal" || tipLoc == "categoria 2") {
            this->tipLoc = tipLoc;
        }
        if (nrRanduri > 0 && nrLocuriPerRand != nullptr) {
            this->nrRanduri = nrRanduri;
            this->nrLocuriPerRand = new int[nrRanduri];
            for (int i = 0; i < nrRanduri; i++) {
                this->nrLocuriPerRand[i] = nrLocuriPerRand[i];
            }
        }
    }
    Zona(const Zona& zona) : Zona() {
        if (zona.tipLoc == "loja" || zona.tipLoc == "peluza" || zona.tipLoc == "tribuna 1" || zona.tipLoc == "tribuna 2" ||
            zona.tipLoc == "categoria 1" || zona.tipLoc == "VIP" || zona.tipLoc == "normal" || zona.tipLoc == "categoria 2") {
            this->tipLoc = zona.tipLoc;
        }
        if (zona.nrRanduri > 0 && zona.nrLocuriPerRand != nullptr) {
            this->nrRanduri = zona.nrRanduri;
            this->nrLocuriPerRand = new int[zona.nrRanduri];
            for (int i = 0; i < zona.nrRanduri; i++) {
                this->nrLocuriPerRand[i] = zona.nrLocuriPerRand[i];
            }
        }
    }
    Zona& operator= (const Zona& zona) {
        if (this->nrLocuriPerRand != nullptr) {
            delete[] this->nrLocuriPerRand;
            this->nrLocuriPerRand = nullptr;
        }
        if (zona.tipLoc == "loja" || zona.tipLoc == "peluza" || zona.tipLoc == "tribuna 1" || zona.tipLoc == "tribuna 2" ||
            zona.tipLoc == "categoria 1" || zona.tipLoc == "VIP" || zona.tipLoc == "normal" || zona.tipLoc == "categoria 2") {
            this->tipLoc = zona.tipLoc;
        }
        if (zona.nrRanduri > 0 && zona.nrLocuriPerRand != nullptr) {
            this->nrRanduri = zona.nrRanduri;
            this->nrLocuriPerRand = new int[zona.nrRanduri];
            for (int i = 0; i < zona.nrRanduri; i++) {
                this->nrLocuriPerRand[i] = zona.nrLocuriPerRand[i];
            }
        }
        return *this;
    }
    friend ofstream& operator<<(ofstream& out, const Zona m) {
        out << m.tipLoc << endl;
        out << m.nrRanduri << endl;
        if (m.nrRanduri > 0 && m.nrLocuriPerRand != nullptr) {
            for (int i = 0; i < m.nrRanduri; i++)
                out << m.nrLocuriPerRand[i] << endl;
        }

        return out;
    }
    friend ifstream& operator>>(ifstream& in, Zona& m) {
        in >> ws;
        getline(in, m.tipLoc);
        int nr = 0;
        in >> nr;
        if (nr > 0) {
            int* copy = new int[nr];
            for (int i = 0; i < nr; i++)
                in >> copy[i];
            m.setRanduriPerLoc(nr, copy);
        }
        return in;
    }
    // getteri si setteri
    void setTipLoc(string tipLoc) {
        if (tipLoc != "") {
            this->tipLoc = tipLoc;
        }
    }

    string getTipLoc() {
        return this->tipLoc;
    }

    void setRanduriPerLoc(int nrRanduri, int* nrLocuriPerRand) {
        if (nrRanduri > 0 && nrLocuriPerRand != nullptr) {
            this->nrRanduri = nrRanduri;
            if (this->nrLocuriPerRand != nullptr)
                delete[] this->nrLocuriPerRand;
            this->nrLocuriPerRand = new int[nrRanduri];
            for (int i = 0; i < nrRanduri; i++) {
                this->nrLocuriPerRand[i] = nrLocuriPerRand[i];
            }
        }
    }
    int* getRanduriPerLoc() {
        int* copy = nullptr;
        if (this->nrLocuriPerRand != nullptr && this->nrRanduri > 0) {
            copy = new int[this->nrRanduri];
            for (int i = 0; i < nrRanduri; i++) {
                copy[i] = nrLocuriPerRand[i];
            }
        }
        return copy;
    }
    int getNrRanduri() {
        return this->nrRanduri;
    }
    // metode specifice
    int getNrMaximLocuri()
    {
        int nr = 0;
        for (int i = 0; i < nrRanduri; i++) {
            nr += this->nrLocuriPerRand[i];
        }
        return nr;
    }
    string getCodScaun(int rand, int loc)
    {
        if (rand <= nrRanduri && rand > 0 && loc > 0 && loc <= this->nrLocuriPerRand[rand - 1]) {
            string codRand = (rand > 0 && rand < 10) ? "0" + to_string(rand) : to_string(rand);
            string codLoc = (loc > 0 && loc < 10) ? "0" + to_string(loc) : to_string(loc);
            return codRand + codLoc;
        }
        else {
            return "";
        }
    }

    static Zona* getZonePentruEveniment(string eveniment, int& nr) {
        Zona* zone = nullptr;
        int nrRanduri = 20;
        int* locuri = new int[nrRanduri];
        for (int i = 0; i < nrRanduri; i++) {
            locuri[i] = i * 1.5 + 10;
        }
        if (eveniment == "film") {
            nr = 2;
            zone = new Zona[2];
            zone[0] = Zona("normal", nrRanduri, locuri);
            zone[1] = Zona("VIP", nrRanduri, locuri);
        }
        else  if (eveniment == "teatru") {
            nr = 3;
            zone = new Zona[3];
            zone[1] = Zona("categoria 1", nrRanduri, locuri);
            zone[2] = Zona("categoria 2", nrRanduri, locuri);
            zone[0] = Zona("loja", nrRanduri, locuri);
        }
        else  if (eveniment == "fotbal") {
            nr = 3;
            zone = new Zona[3];
            zone[0] = Zona("peluza", nrRanduri, locuri);
            zone[1] = Zona("tribuna 1", nrRanduri, locuri);
            zone[2] = Zona("tribuna 2", nrRanduri, locuri);
        }
        return zone;
    }
    string encrypt(int id)
    {
        string s = "";
        for (int i = 0; i < this->tipLoc.length(); i++) {
            int temp = (this->tipLoc[i] + id);
            s += (char)temp;
        }
        return s;
    }

    string decrypt(string criptat, int id)
    {
        string s = "";
        for (int i = 0; i < criptat.length(); i++) {
            int temp = (criptat[i] - id);
            s += (char)temp;
        }
        return s;
    }

    // destructor
    ~Zona() {
        if (this->nrLocuriPerRand != nullptr) {
            delete[] this->nrLocuriPerRand;
            this->nrLocuriPerRand = nullptr;
        }
    }

    // operatori
    explicit operator int() {
        return getNrMaximLocuri();
    }

    explicit operator string() {
        return this->tipLoc;
    }

    Zona operator!() {
        this->nrRanduri = 0;
        this->nrLocuriPerRand = 0;
    }
    friend ostream& operator<<(ostream&, Zona);
    friend istream& operator>>(istream&, Zona&);
};


ostream& operator<<(ostream& os, Zona c) {
    if (c.tipLoc.length() == 0) os << "Zona nu are tip." << endl;
    else os << "Tip: " << c.tipLoc << endl;
    if (c.nrRanduri > 0 && c.nrLocuriPerRand != nullptr) {
        os << "Sunt " << c.nrRanduri << " randuri, cu un total de " << c.getNrMaximLocuri() << " locuri disponibile." << endl;
    }
    else os << "Zona nu are randuri." << endl;
    return os;
}
istream& operator>>(istream& is, Zona& c) {
    cout << "Introduceti tipul zonei: ";
    is >> c.tipLoc;
    int nr;
    cout << "Dati numarul de randuri: ";
    is >> nr;
    while (nr < 1) {
        cout << "Dati un numar pozitiv! Incercati iar:";
        is >> nr;
    }
    int* locuri = new int[nr];
    for (int i = 0; i < nr; i++) {
        cout << "Randul " << (i + 1) << ":";
        int nrLocuri;
        is >> nrLocuri;
        while (nrLocuri < 1) {
            cout << "Dati un numar pozitiv! Incercati iar:";
            is >> nrLocuri;
        }
        locuri[i] = nrLocuri;
    }
    c.setRanduriPerLoc(nr, locuri);
    return is;
}

#pragma once
