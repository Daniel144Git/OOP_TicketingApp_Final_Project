#pragma once
#include <iostream>
#include <string>
#include "Bilet.h"
#pragma warning(disable:4996)
using namespace std;

class BiletStudent : public Bilet
{
private:
    float pretRedus;
    bool student;
    float reducePret() override {
        if (this->getPret() > 0) {
            return getPret() * 0.5;
        }
        else return 0;
    }

public:
    BiletStudent() :Bilet() {
        this->pretRedus = 0;
        this->student = false;
    }
    BiletStudent(Eveniment eveniment, float pret, int rand, int loc, bool student) : Bilet(eveniment, pret, rand, loc) {
        setPretRedus(pret);
        setStudent(student);
    }
    BiletStudent(const BiletStudent& bilet) : Bilet(bilet) {
        Bilet b = bilet;
        setPret(b.getPret());
        setStudent(bilet.student);
    }
    ~BiletStudent() {
        destructor();
    }
    void setStudent(bool student) {
        this->student = student;
    }
    bool getStudent() {
        return student;
    }
    void setPretRedus(float pret) {
        setPret(pret);
        this->pretRedus = reducePret();
    }
    float getPretRedus() {
        return pretRedus;
    }
    bool validareBilet(Eveniment eveniment, Zona zona)  override {
        if (student == false) {
            cout << endl << "Nu sunteti student!" << endl;
            return false;
        }
        this->encrypt();
        string codEveniment = eveniment.encrypt(getId()) + getLocScaun();
        if (getCod() == codEveniment) {
            cout << "Biletul nu este corect! Codul biletului este " << getCod() << " si trebuia sa fie " + codEveniment << endl;
            return false;
        }
        if (getEveniment().getData() == nullptr || getEveniment().getNrElemente() < 3 || eveniment.getData() == nullptr || eveniment.getNrElemente() < 3) {
            cout << "Data nu este valida!" << endl;
            return false;
        }
        for (int i = 0; i < eveniment.getNrElemente(); i++) {
            if (getEveniment().getData()[i] != eveniment.getData()[i]) {
                cout << "Data este gresita!" << endl;
                return false;
            }
        }

        return true;
    }
};
