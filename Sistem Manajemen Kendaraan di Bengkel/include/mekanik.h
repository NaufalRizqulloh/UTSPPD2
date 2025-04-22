// Mekanik.h
#ifndef MEKANIK_H
#define MEKANIK_H

#include <iostream>
#include <string>

using namespace std;

class Mekanik {
private:
    string nama;
    string keahlian; // Sesuai layanan.h
public:
    Mekanik();
    Mekanik(const string& nama, const string& keahlian);

    // setter
    void setNama(const string& nama);
    void setKeahlian(const string& keahlian);

    // getter
    string getNama() const;
    string getKeahlian() const;

    // Main Member Function
    void createMekanik();
	void mekanikFileWritting(Mekanik m);
    void editMekanik();
    void deleteMekanik();
    void showMekanik();
};

#endif // MEKANIK_H
