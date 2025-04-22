// Pelanggan.h
#ifndef PELANGGAN_H
#define PELANGGAN_H

#include <string>
#include <iostream>

using namespace std;

class Pelanggan {
private:
    string nama;
    string kontak;
    int transaksiId;
public:
    Pelanggan();
    Pelanggan(const string& nama, const string& kontak, const int transaksiId);

    // setter
    void setNama(const string& nama);
    void setKontak(const string& kontak);
    void setTransaksiId(int id);

    // getter
    string getNama() const;
    string getKontak() const;
    int getTransaksiId() const;

    // Main member function
    void pelangganFileWritting(Pelanggan p);
    void display() const;
};

#endif // PELANGGAN_H
