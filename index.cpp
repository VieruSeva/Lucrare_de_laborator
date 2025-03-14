#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;


class Vehicul {
protected:
    string numarInmatriculare;
    int oraIntrare;
    int oraIesire;

public:
    Vehicul(string numar, int intrare, int iesire) 
        : numarInmatriculare(numar), oraIntrare(intrare), oraIesire(iesire) {}
    virtual ~Vehicul() {}
    int calculeazaTimpParcare() { return oraIesire - oraIntrare; }
    virtual double calculeazaTarif() = 0;
    virtual void afisare() {
        cout << "Numar: " << numarInmatriculare
             << ", Timp: " << calculeazaTimpParcare() << " ore, Tarif: ";
    }
};


class Masina : public Vehicul {
public:
    Masina(string numar, int intrare, int iesire)
        : Vehicul(numar, intrare, iesire) {}
    double calculeazaTarif() override { return calculeazaTimpParcare() * 5; }
    void afisare() override {
        cout << "Masina "; Vehicul::afisare();
        cout << calculeazaTarif() << " lei" << endl;
    }
};


class Motocicleta : public Vehicul {
public:
    Motocicleta(string numar, int intrare, int iesire)
        : Vehicul(numar, intrare, iesire) {}
    double calculeazaTarif() override { return calculeazaTimpParcare() * 3; }
    void afisare() override {
        cout << "Motocicleta "; Vehicul::afisare();
        cout << calculeazaTarif() << " lei" << endl;
    }
};


class Camion : public Vehicul {
public:
    Camion(string numar, int intrare, int iesire)
        : Vehicul(numar, intrare, iesire) {}
    double calculeazaTarif() override { return calculeazaTimpParcare() * 10; }
    void afisare() override {
        cout << "Camion "; Vehicul::afisare();
        cout << calculeazaTarif() << " lei" << endl;
    }
};


class Bicicleta : public Vehicul {
public:
    Bicicleta(string numar, int intrare, int iesire)
        : Vehicul(numar, intrare, iesire) {}
    double calculeazaTarif() override {
        int timp = calculeazaTimpParcare();
        return (timp > 2) ? (timp - 2) * 2 : 0;
    }
    void afisare() override {
        cout << "Bicicleta "; Vehicul::afisare();
        cout << calculeazaTarif() << " lei" << endl;
    }
};


vector<Vehicul*> citesteVehicule(string numeFisier) {
    ifstream fisier(numeFisier);
    vector<Vehicul*> vehicule;
    string linie;
    while (getline(fisier, linie)) {
        stringstream ss(linie);
        string tip, numar;
        int intrare, iesire;
        ss >> tip >> numar >> intrare >> iesire;
        if (tip == "Masina") vehicule.push_back(new Masina(numar, intrare, iesire));
        else if (tip == "Motocicleta") vehicule.push_back(new Motocicleta(numar, intrare, iesire));
        else if (tip == "Camion") vehicule.push_back(new Camion(numar, intrare, iesire));
        else if (tip == "Bicicleta") vehicule.push_back(new Bicicleta(numar, intrare, iesire));
    }
    return vehicule;
}


int main() {
    vector<Vehicul*> vehicule = citesteVehicule("parcare.txt");
    for (Vehicul* v : vehicule) {
        v->afisare();
        delete v; 
    }
    return 0;
}