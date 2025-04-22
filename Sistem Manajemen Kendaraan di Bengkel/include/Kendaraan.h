#ifndef KENDARAAN_H
#define KENDARAAN_H

#include <iostream>
#include <string>

#include "../include/Motor.h"
#include "../include/Mobil.h"
#include "../include/Truk.h"

using namespace std;

void MenuKendaraan();

class Kendaraan {
protected:
    string plat_no, tipe, status_servis;
    int tahun, transaksiId;

public:
    virtual ~Kendaraan() {};
    // Setter Function
    void setPlatNo(const string& pn) { plat_no = pn; }
    void setTahun(int t) { tahun = t; }
    void setTipe(const string& tp);
	void setStatusServis(const string& _status) { status_servis = _status; }
	void setTransaksiId(const int id) { transaksiId = id; }

    // Getter function
	string getPlatNo() const { return plat_no; }
    int getTahun() const { return tahun; }
    string getTipe() const { return tipe; }
	string getStatusServis() const { return status_servis; }
	int getTransaksiId() const { return transaksiId; }

    // Main member function
    void inputData();
    void writeData(Kendaraan k);
    string searchData(const string& plat);
    void editData(string& pn);
    void showData(string line);
    void deleteData(string& pn);

    void tampilkanData();
    void ubahStatusServis(string& pn);
	void cariPlatNomer();
};

// Derived class
class Mobil : public Kendaraan {
public:
    string setTipeMobil(void);
};

class Motor : public Kendaraan {
public:
    string setTipeMotor(void);
};

class Truk : public Kendaraan {
public:
    string setTipeTruk(void);
};

#endif
