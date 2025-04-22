#include <iostream>
#include <string>
#include <conio.h>

#include <fstream>
#include <filesystem>
#include <regex>

#include "../include/helper.h"
#include "../include/Transaksi.h"

using namespace std;

// Define the file path
const string folder = "data";
const string kendaraanFile = folder + "/kendaraan.txt";
const string layananFile = folder + "/layanan.txt";
const string pelangganFile = folder + "/pelanggan.txt";
const string transaksiFile = folder + "/transaksi.txt";

// 1. File writting
void Transaksi::transaksiFileWritting(Transaksi t) {
	if (!filesystem::exists(folder)) {
		filesystem::create_directory(folder);
		cout << "Folder 'data' created." << endl;
	}

	ofstream outFile(transaksiFile, ios::app);
	if (outFile.is_open()) {
		int lastLineNumber = getLastLineNumber(transaksiFile) + 1;
		outFile << lastLineNumber << ". " << endl;
		outFile << "Keperluan Servis: " << t.getKeperluanServis() << endl;
		outFile << "Biaya Servis: " << t.getBiayaServis() << endl;
		outFile << "Mekanik Penanggung Jawab: " << t.getMekanikPJ() << endl;
		outFile << "ID Transaksi: " << t.getTransaksiId() + 1 << endl;
		outFile.close();
	}
	else {
		cout << "Gagal membuka file." << endl;
	}
}

// 2. Edit Transaksi
void Transaksi::editTransaksi() {
	Kendaraan k;
	Pelanggan p;
	Transaksi t;
	string line, namaPelanggan, kontakPelanggan;
	smatch match;

	cout << "Data transaksi lama: " << endl;
	int choiceInt =	t.showTransaksi();
	char choiceChar;

	// Pelanggan edit
	vector<string> dataBaruPelanggan = t.editPelanggan(choiceInt, p);
	cout << endl;

	// Kendaraan edit
	vector<string> dataBaruKendaraan = t.editKendaraan(choiceInt, k);
	cout << endl;

	// Transaksi edit
	vector<string> dataTransaksiBaru = t.editTransaksiFile(choiceInt, p, k, t);
	system("cls");

	// Review edit data
	while (1) {
		cout << "Review Update Data Transaksi" << endl;
		cout << "Data Pelanggan" << endl;
		cout << "Nama Pelanggan : " << p.getNama() << endl;
		cout << "Kontak Pelanggan : " << p.getKontak() << endl;
		cout << endl;
		cout << "Data Kendaraan" << endl;
		cout << "Plat Nomor : " << k.getPlatNo() << endl;
		cout << "Tahun Kendaraan : " << k.getTahun() << endl;
		cout << "Tipe Kendaraan : " << k.getTipe() << endl;
		cout << endl;
		cout << "Data Transaksi" << endl;
		cout << "Keperluan Servis : " << t.getKeperluanServis() << endl;
		cout << "Biaya Servis : " << t.getBiayaServis() << endl;
		cout << "Mekanik Penanggung Jawab : " << t.getMekanikPJ() << endl;
		cout << endl;
		cout << "Apakah data layanan sudah benar? (y/n): ";
		cin >> choiceChar;

		if (choiceChar == 'y' || choiceChar == 'Y') {
			// Overwrite file with updated data
			// Pelanggan file
			ofstream outFilePelanggan(pelangganFile);
			for (const string& plString : dataBaruPelanggan) {
				outFilePelanggan << plString << endl;
			}
			outFilePelanggan.close();
			
			// Kendaraan file
			ofstream outFileKendaraan(kendaraanFile);
			for (const string& knString : dataBaruKendaraan) {
				outFileKendaraan << knString << endl;
			}
			outFileKendaraan.close();

			// Transaksi file
			ofstream outFileTransaksi(transaksiFile);
			for (const string& trString : dataTransaksiBaru) {
				outFileTransaksi << trString << endl;
			}
			outFileTransaksi.close();

			cout << "\nLayanan berhasil diupdate!\n";
			_getch();
			system("cls");
			break;
		}
		else if (choiceChar == 'n' || choiceChar == 'N') {
			system("cls");
			cout << "Update layanan dibatalkan!" << endl;
			break;
		}
		else {
			system("cls");
			cout << "Pilihan tidak valid!" << endl;
			continue;
		}
	}
}

// 2.1 Edit Pelanggan
vector<string> Transaksi::editPelanggan(int choiceInt, Pelanggan& p) {
	regex numberRegex(R"(^\s*(\d+)\.\s*$)");
	smatch match;
	vector<string> linesPelanggan;
	string line, namaPelanggan, kontakPelanggan;

	ifstream inFile(pelangganFile);
	while (getline(inFile, line)) {
		linesPelanggan.push_back(line);
	}
	inFile.close();

	for (size_t i = 0; i < linesPelanggan.size(); ++i) {
		if (regex_match(linesPelanggan[i], match, numberRegex)) {
			int number = stoi(match[1]);
			if (number == choiceInt) {

				cout << "Masukkan data pelanggan baru " << endl;
				cout << "Nama Pelanggan : ";
				getline(cin, namaPelanggan);
				p.setNama(namaPelanggan);
				linesPelanggan[i + 1] = "Nama Pelanggan: " + p.getNama();

				cout << "Kontak Pelanggan : ";
				cin.ignore();
				getline(cin, kontakPelanggan);
				p.setKontak(kontakPelanggan);
				linesPelanggan[i + 2] = "Kontak Pelanggan: " + p.getKontak();

				return linesPelanggan;
			}
		}
	}
}

// 2.2 Edit Kendaraan
vector<string> Transaksi::editKendaraan(int choiceInt, Kendaraan& k) {
	regex numberRegex(R"(^\s*(\d+)\.\s*$)");
	smatch match;
	vector<string> linesKendaraan;
	string line, platNomor, tipeKendaraan, servis;
	int tahun;

	ifstream inFile(kendaraanFile);
	while (getline(inFile, line)) {
		linesKendaraan.push_back(line);
	}
	inFile.close();

	for (size_t i = 0; i < linesKendaraan.size(); ++i) {
		if (regex_match(linesKendaraan[i], match, numberRegex)) {
			int number = stoi(match[1]);
			if (number == choiceInt) {

				cout << "Masukkan data kendaraan baru" << endl;
				cout << "Plat Nomor : ";
				getline(cin, platNomor);
				k.setPlatNo(platNomor);
				linesKendaraan[i + 1] = "Plat Nomor: " + k.getPlatNo();

				cout << "Tahun Kendaraan : ";
				cin >> tahun;
				k.setTahun(tahun);
				linesKendaraan[i + 2] = "Tahun Kendaraan: " + to_string(k.getTahun());

				cout << "Tipe Kendaraan : ";
				cin.ignore();
				getline(cin, tipeKendaraan);
				k.setTipe(tipeKendaraan);
				linesKendaraan[i + 3] = "Tipe Kendaraan: " + k.getTipe();
				

				cout << "List layanan bengkel DMITS:" << endl;
				getHeaderNames(layananFile);
				cout << "Pilih keperluan servis sesuai layanan bengkel: ";
				cin >> choiceInt;
				k.setStatusServis(pilihKeahlian(choiceInt, layananFile));
				linesKendaraan[i + 4] = "Keperluan Servis: " + k.getStatusServis();

				return linesKendaraan;
			}
		}
	}
}

// 2.3 Edit Transaksi File
vector<string> Transaksi::editTransaksiFile(int choiceInt, Pelanggan& p, Kendaraan& k, Transaksi& t) {
	regex numberRegex(R"(^\s*(\d+)\.\s*$)");
	smatch match;
	vector<string> linesTransaksi;
	string line;

	ifstream inFile(transaksiFile);
	while (getline(inFile, line)) {
		linesTransaksi.push_back(line);
	}
	inFile.close();

	for (size_t i = 0; i < linesTransaksi.size(); ++i) {
		if (regex_match(linesTransaksi[i], match, numberRegex)) {
			int number = stoi(match[1]);
			if (number == choiceInt) {
				string layananName = k.getStatusServis();
				int idServis = getLayananHeaderByName(layananName);
				int biayaServiss = biayaServisHelper(idServis);
				string mekanikPJ = bengkelPJ(idServis);

				t.keperluanServissetter(layananName);
				linesTransaksi[i + 1] = "Keperluan Servis: " + t.getKeperluanServis();

				t.biayaServissetter(biayaServiss);
				linesTransaksi[i + 2] = "Biaya Servis: " + to_string(t.getBiayaServis());

				t.mekanikPJsetter(mekanikPJ);
				linesTransaksi[i + 3] = "Mekanink Penanggung Jawab: " + t.getMekanikPJ();

				return linesTransaksi;
			}
		}
	}
}

// 3. Proses Transaksi
void Transaksi::prosesTransaksi() {
	Kendaraan k;
	Transaksi t;

	while (1) {
		char choiceChar;
		int choiceInt = t.showTransaksi();
		cout << "Apakah anda ingin memproses servis ini? (y/n) : ";
		cin >> choiceChar;

		if (choiceChar == 'y' || choiceChar == 'Y') {
			regex numberRegex(R"(^\s*(\d+)\.\s*$)");
			smatch match;
			vector<string> linesTransaksi, linesKendaraan;
			string line;
			string layananName = "Sudah diservis";

			// Edit File Kendaraan
			ifstream inFile(kendaraanFile);
			while (getline(inFile, line)) {
				linesKendaraan.push_back(line);
			}
			inFile.close();

			for (size_t i = 0; i < linesKendaraan.size(); ++i) {
				if (regex_match(linesKendaraan[i], match, numberRegex)) {
					int number = stoi(match[1]);
					if (number == choiceInt) {
						k.setStatusServis(layananName);
						linesKendaraan[i + 4] = "Keperluan Servis: " + k.getStatusServis();
					}
				}
			}

			ofstream outFileKendaraan(kendaraanFile);
			for (const string& knString : linesKendaraan) {
				outFileKendaraan << knString << endl;
			}
			outFileKendaraan.close();
	
			// Edit File Transaksi
			ifstream inFileTransaksi(transaksiFile);
			while (getline(inFileTransaksi, line)) {
				linesTransaksi.push_back(line);
			}
			inFileTransaksi.close();

			for (size_t i = 0; i < linesTransaksi.size(); ++i) {
				if (regex_match(linesTransaksi[i], match, numberRegex)) {
					int number = stoi(match[1]);
					if (number == choiceInt) {
						t.keperluanServissetter(layananName);
						linesTransaksi[i + 1] = "Keperluan Servis: " + t.getKeperluanServis();
					}
				}
			}

			ofstream outFileTransaksi(transaksiFile);
			for (const string& trString : linesTransaksi) {
				outFileTransaksi << trString << endl;
			}
			outFileTransaksi.close();


			system("cls");
			cout << "Servis pada kendaraan telah diproses, silahkan informasikan pelanggan terkait pembayaran." << endl;
			break;
		}
		else if (choiceChar == 'n' || choiceChar == 'N') {
			system("cls");
			cout << "Proses Transaksi dibatalkan!" << endl;
			break;
		}
		else {
			system("cls");
			cout << "Pilihan tidak valid!" << endl;
			continue;
		}
	}
}

// 4. Show Available Transaksi
int Transaksi::showTransaksi() {
	string choice;
	string line;
	regex transaksiIdRegex(R"(^ID Transaksi:\s*(\d+)$)");
	smatch match;
	int choiceInt = 0;
	bool transaksiFound = false;

	while (1) {
		vector<string> lines;
		ifstream inFile(pelangganFile);
		while (getline(inFile, line)) {
			lines.push_back(line);
		}
		inFile.close();

		cout << "Data Pelanggan yang melakukan transaksi pada Bengkel DMITS" << endl;
		getHeaderNames(pelangganFile);
		cout << endl;
		cout << "Pilih pelanggan untuk melihat data transaksi (ketik 'back' untuk kembali): ";
		getline(cin, choice);
		system("cls");

		if (choice == "back") {
			return -1;
		}
		else if (choice.empty()) {
			continue;
		}
		else if (!isDigitsOnly(choice)) {
			cout << "Input tidak valid, masukkan angka yang ingin dipilih";
			continue;
		}

		choiceInt = stoi(choice);
		for (size_t i = 0; i < lines.size(); ++i) {
			if (regex_match(lines[i], match, transaksiIdRegex)) {
				int number = stoi(match[1]);
				if (number == choiceInt) {
					transaksiFound = true;
					cout << "Data diri Pelanggan: " << endl;
					cout << getBlockDataByTransaksiId(pelangganFile, number) << endl;
					cout << "Data Kendaraan: " << endl;
					cout << getBlockDataByTransaksiId(kendaraanFile, number) << endl;
					cout << "Data Servis: " << endl;
					cout << getBlockDataByTransaksiId(transaksiFile, number) << endl;
					return number;
				}
			}
		}
		if (!transaksiFound) {
			cout << "Data transaksi tidak ditemukan!" << endl;
		}
	}
}