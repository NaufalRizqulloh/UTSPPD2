#include <iostream>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdlib>

#include "../include/helper.h"
#include "../include/Motor.h"
#include "../include/Mobil.h"
#include "../include/Truk.h"
#include "../include/Kendaraan.h"

using namespace std;

// Define derived class
Mobil mb;
Motor mt;
Truk tr;

// Define the file path
const string folder = "data";
const string filename = folder + "/kendaraan.txt";

// Gunakan syntax MenuKendaraan(); di main()
void MenuKendaraan() {
	Kendaraan k;
	string pn;

	int Choice;
	do {
		pn = "";
		cout << "==========================" << endl;
		cout << "      Menu Kendaraan" << endl;
		cout << "==========================" << endl;
		cout << "1. Input Data Kendaraan" << endl;
		cout << "2. Tampilkan Data Kendaraan" << endl;
		cout << "3. Edit Data Kendaraan" << endl;
		cout << "4. Hapus Data Kendaraan" << endl;
		cout << "5. Ubah Status Servis" << endl;
		cout << "6. Cari Plat Nomer Kendaraan" << endl;
		cout << "7. Keluar" << endl;
		cout << "==========================" << endl;
		cout << "Pilih menu: ";
		cin >> Choice;
		cin.ignore();
		switch (Choice) {
		case 1:
			k.inputData();
			break;
		case 2:
			k.tampilkanData();
			break;
		case 3:
			k.editData(pn);
			break;
		case 4:
			k.deleteData(pn);
			break;
		case 5:
			k.ubahStatusServis(pn);
			break;
		case 6:
			k.cariPlatNomer();
			break;
		case 7:
			cout << "Keluar dari menu kendaraan..." << endl;
			return;
		default:
			cout << "Pilihan tidak valid!" << endl;
			break;
		}
	} while (Choice != 7);
}

// Setter function
void Kendaraan::setTipe(const string& tp) {
	if (tp == "Mobil" || tp == "mobil") {
		tipe = mb.setTipeMobil();
	}
	else if (tp == "Motor" || tp == "motor") {
		tipe = mt.setTipeMotor();
	}
	else if (tp == "Truk" || tp == "truk") {
		tipe = tr.setTipeTruk();
	}
	else {
		return;
	}
}

// Untuk input data kendaraan
void Kendaraan::inputData() {
	string pn, t, ss;
	int th;

	cout << "Masukkan Plat No: ";
	getline(cin, pn);

	cout << "Masukkan Tahun: ";
	cin >> th;

	cout << "Masukkan Tipe: ";
	cin.ignore();
	getline(cin, t);

	if (t == "Mobil" || t == "mobil") {
		Mobil m;
	
		m.plat_no = pn;
		m.tahun = th;
	}
	else if (t == "Motor" || t == "motor") {
		Motor m;
		m.plat_no = pn;
		m.tahun = th;
	}
	else if (t == "Truk" || t == "truk") {
		Truk m;
		m.plat_no = pn;
		m.tahun = th;
	}
}

void Kendaraan::writeData(Kendaraan k) {
	if (!filesystem::exists(folder)) {
		filesystem::create_directory(folder);
		cout << "Folder 'data' created." << endl;
	}

	ofstream outFile(filename, ios::app);
	if (outFile.is_open()) {
		int lastLineNumber = getLastLineNumber(filename) + 1;
		outFile << lastLineNumber << ". " << endl;
		outFile << "Plat Nomor: " << k.getPlatNo() << endl;
		outFile << "Tahun Kendaraan: " << k.getTahun() << endl;
		outFile << "Tipe Kendaraan: " << k.getTipe() << endl;
		outFile << "Keperluan Servis: " << k.getStatusServis() << endl;
		outFile << "ID Transaksi: " << k.getTransaksiId() + 1 << endl;
		outFile.close();
	}
	else {
		cout << "Gagal membuka file." << endl;
	}
}

// Also fix this
string Kendaraan::searchData(const string& plat) {
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Gagal membuka file." << endl;
		return "";
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string platInFile;

		getline(ss, platInFile, ',');

		if (platInFile == plat) {
			file.close();
			return line;
		}
	}
	cout << "Data tidak ditemukan!";
	file.close();
	return "";
}

// This too
// Fungsi untuk mengedit data kendaraan
void Kendaraan::editData(std::string& pn) {
	int i = 0;
	bool valid;
	std::system("cls");
	cout << "Edit Data Kendaraan" << endl;
	do {
		valid = false;
		if (pn.empty() || i != 0) {
			cout << "Masukkan plat nomer kendaraan yang ingin diubah: ";
			getline(cin, pn);
		}
		string lineToEdit = searchData(pn);
		if (!lineToEdit.empty()) {
			cout << "Data ditemukan!\n";
			valid = true;

			stringstream ss(lineToEdit);
			string plate, tahun, tipe, status;
			getline(ss, plate, ',');
			getline(ss, tahun, ',');
			getline(ss, tipe, ',');
			getline(ss, status);

			cout << "Data saat ini:\n";
			showData(lineToEdit);

			string newTahun, newTipe, newStatus;
			cout << "Masukkan tahun baru: ";
			getline(cin, newTahun);
			cout << "Masukkan tipe baru: ";
			getline(cin, newTipe);
			cout << "Masukkan status servis baru: ";
			getline(cin, newStatus);

			ifstream inFile(filename);
			vector<string> lines;
			string line;
			while (getline(inFile, line)) {
				stringstream s(line);
				string tempPlate;
				getline(s, tempPlate, ',');
				if (tempPlate == pn) {
					line = pn + "," + newTahun + "," + newTipe + "," + newStatus;
				}
				lines.push_back(line);
			}
			inFile.close();

			ofstream outFile(filename, ios::trunc);
			for (const string& l : lines) {
				outFile << l << "\n";
			}
			outFile.close();
			std::system("cls");
			cout << "Data berhasil diperbarui!\n";
			return;
		}
		i++;
		cout << " Silahkan coba lagi.\n";
	} while (!valid);
}

// Yeah this also
// Fungsi untuk menampilkan data kendaraan per line
void Kendaraan::showData(string line) {
	stringstream ss(line);
	string plat, tahun, tipe, status;

	getline(ss, plat, ',');
	getline(ss, tahun, ',');
	getline(ss, tipe, ',');
	getline(ss, status);

	cout << "Plat nomer     : " << plat << endl;
	cout << "Tahun          : " << tahun << endl;
	cout << "Tipe           : " << tipe << endl;
	cout << "Status servis  : " << status << endl;
	cout << "-------------------------------" << endl;
}

// FIX
// Fungsi untuk menghapus data kendaraan
void Kendaraan::deleteData(std::string& pn) {
	int i = 0;
	bool valid;
	std::system("cls");
	cout << "Hapus Data Kendaraan" << endl;
	do {
		valid = false;
		if (pn.empty() || i != 0) {
			cout << "Masukkan plat nomer kendaraan yang ingin dihapus: ";
			getline(cin, pn);
		}
		string lineToDelete = searchData(pn);
		if (!lineToDelete.empty()) {
			cout << "Data ditemukan!\n";
			valid = true;
			// Read all data and skip the one to delete
			ifstream inFile(filename);
			vector<string> lines;
			string line;
			while (getline(inFile, line)) {
				if (line != lineToDelete) {
					lines.push_back(line);
				}
			}
			inFile.close();
			// Write remaining data back to file
			ofstream outFile(filename, ios::trunc);
			for (const string& l : lines) {
				outFile << l << "\n";
			}
			outFile.close();
			std::system("cls");
			cout << "Data berhasil dihapus!\n";
			return;
		}
		i++;
		cout << " Silahkan coba lagi.\n";
	} while (!valid);
}

// Not reviewed yet
// Fungsi untuk menampilkan semua data kendaraan
void Kendaraan::tampilkanData() {
	std::system("cls");
	cout << "Tampilkan Data Kendaraan" << endl;
	cout << "==========================" << endl;
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Gagal membuka file!" << endl;
		return;
	}
	string line;
	while (getline(file, line)) {
		showData(line);
	}
	file.close();
	cout << "Tekan enter untuk kembali ke menu utama..." << endl;
	cin.get();
	std::system("cls");
}

// Not reviewed yet
// Fungsi untuk mengubah status servis kendaraan
void Kendaraan::ubahStatusServis(string& pn) {
	int i = 0;
	string lineToEdit;

	bool valid;
	std::system("cls");
	cout << "Ubah Status Servis Kendaraan" << endl;
	do {
		valid = false;
		if (pn.empty() || i != 0) {
		cout << "Masukkan plat nomer kendaraan yang ingin diubah status servisnya: ";
		getline(cin, pn);
		}

		lineToEdit = searchData(pn);
		if (!lineToEdit.empty()) {
			cout << "Data ditemukan!\n";
			valid = true;
			stringstream ss(lineToEdit);
			string plate, tahun, tipe, status;
			getline(ss, plate, ',');
			getline(ss, tahun, ',');
			getline(ss, tipe, ',');
			getline(ss, status);
			cout << "Data saat ini:\n";
			showData(lineToEdit);
			string newStatus;
			cout << "Masukkan status servis baru: ";
			getline(cin, newStatus);
			ifstream inFile(filename);
			vector<string> lines;
			string line;
			while (getline(inFile, line)) {
				stringstream s(line);
				string tempPlate;
				getline(s, tempPlate, ',');
				if (tempPlate == pn) {
					line = pn + "," + tahun + "," + tipe + "," + newStatus;
				}
				lines.push_back(line);
			}
			inFile.close();
			ofstream outFile(filename, ios::trunc);
			for (const string& l : lines) {
				outFile << l << "\n";
			}
			outFile.close();
			system("cls");
			cout << "Status servis berhasil diperbarui!\n";
			return;
		}
		i++;
		cout << " Silahkan coba lagi.\n";
	} while (!valid);
}

// Need yeah
// Fungsi untuk mencari plat nomer kendaraan
void Kendaraan::cariPlatNomer() {
	string pn;
	bool plateFound = false;

	std::system("cls");
	cout << "Cari Plat Nomer Kendaraan" << endl;
	do {
		cout << "Masukkan plat nomer kendaraan yang ingin dicari: ";
		getline(cin, pn);

		string line = searchData(pn);
		if (!line.empty()) {
			plateFound = true;
			cout << "Data ditemukan!" << "\n-------------------------------" << endl;

			bool exitMenu = false;
			do {
				showData(line);
				cout << "1. Edit data plat nomer" << endl;
				cout << "2. Hapus data plat nomer" << endl;
				cout << "3. Ubah status servis" << endl;
				cout << "4. Kembali ke menu utama" << endl;
				cout << "Pilih opsi: ";

				int choice;
				cin >> choice;
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				switch (choice) {
				case 1:
					editData(pn);
					break;
				case 2:
					deleteData(pn);
					return;
				case 3:
					ubahStatusServis(pn);
					break;
				case 4:
					std::system("cls");
					cout << "Kembali ke menu utama..." << endl;
					exitMenu = true;
					break;
				default:
					cout << "Pilihan tidak valid! coba lagi." << endl;
					break;
				}
			} while (!exitMenu);
		}
		else {
			cout << " coba lagi." << endl;
		}
	} while (!plateFound);
}
