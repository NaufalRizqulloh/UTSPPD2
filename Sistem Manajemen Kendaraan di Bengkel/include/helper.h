#ifndef HELPER_H
#define HELPER_H

#include <string>

#include "../include/Kendaraan.h"
#include "../include/pelanggan.h"

using namespace std;

int getLastLineNumber(const string& filename);
void getHeaderNames(const string& filename);
bool isDigitsOnly(const string& str);
string pilihKeahlian(int choice, const string& filename);
int getLayananHeaderByName(const string& serviceName);
int biayaServisHelper(int choiceInt);
bool checkKeahlian(const int keahlian, const string& filename);
string bengkelPJ(int choiceInt);
string getBlockDataByTransaksiId(const string& filename, int transaksiId);
void loadDataByTransaksiID(int transaksiID, Kendaraan* kendaraan, Pelanggan& pelanggan);
bool checkPlat(const string& platNo);
bool checkTahun(const int tahun);
bool checkTipeKendaraan(const string& platNo);
bool checkNamaPelanggan(const string& keperluanServis);

#endif // !HELPER_H

