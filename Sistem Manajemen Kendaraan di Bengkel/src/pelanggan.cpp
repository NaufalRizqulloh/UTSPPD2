// Pelanggan.cpp
#include <iostream>
#include <string>
#include <conio.h>

#include <fstream>
#include <filesystem>
#include <regex>

#include "../include/helper.h"

#include "../include/pelanggan.h"

using namespace std;

Pelanggan::Pelanggan()
    : nama(""), kontak(""), transaksiId(0) {}

Pelanggan::Pelanggan(const std::string& nama, const std::string& kontak, const int transaksiId)
    : nama(nama), kontak(kontak), transaksiId(transaksiId) {}

void Pelanggan::setNama(const std::string& _nama) { 
    nama = _nama; 
}

void Pelanggan::setKontak(const std::string& _kontak) { 
    kontak = _kontak; 
}

void Pelanggan::setTransaksiId(int id) {
	transaksiId = id;
}

string Pelanggan::getNama() const { 
    return nama; 
}

string Pelanggan::getKontak() const { 
    return kontak; 
}

int Pelanggan::getTransaksiId() const {
	return transaksiId;
}

void Pelanggan::display() const {
    cout << "Nama: " << nama << endl;
    cout << "Kontak: " << kontak << endl;
}

// Main member function
// File writting from Bengkel.cpp
void Pelanggan::pelangganFileWritting(Pelanggan p) {
	string folder = "data";
	string filename = folder + "/pelanggan.txt";

	// Deklarasi folder jika folder tidak ada di directory
	if (!filesystem::exists(folder)) {
		filesystem::create_directory(folder);
		cout << "Folder 'data' created." << endl;
	}

	// Membuat file dengan data pelanggan
	ofstream outFile(filename, ios::app);
	if (outFile.is_open()) {
		int lastLineNumber = getLastLineNumber(filename) + 1;
		cout << "Membuat data pelanggan di folder 'data'." << endl;
		outFile << lastLineNumber << ". " << endl;
		outFile << "Nama Pelanggan: " << p.getNama() << endl;
		outFile << "Kontak Pelanggan: " << p.getKontak() << endl;
		outFile << "ID Transaksi: " << p.getTransaksiId() + 1  << endl;
		outFile.close();
		cout << "Data pelanggan " << p.getNama() << " berhasil ditambahkan!" << endl;
	}
	else {
		cout << "Failed to create file in folder.\n";
	}
}