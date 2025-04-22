// Mekanik.cpp
#include <iostream>
#include <string>
#include <conio.h>

#include <fstream>
#include <filesystem>
#include <regex>

#include "../include/helper.h"

#include "../include/mekanik.h"

using namespace std;

// Setter and Getter Functions
Mekanik::Mekanik()
    : nama(""), keahlian("") {}

Mekanik::Mekanik(const string& nama, const string& keahlian)
    : nama(nama), keahlian(keahlian) {}

void Mekanik::setNama(const string& _nama) { 
    nama = _nama; 
}

void Mekanik::setKeahlian(const string& _kh) { 
    keahlian = _kh; 
}

string Mekanik::getNama() const { 
    return nama; 
}

string Mekanik::getKeahlian() const { 
    return keahlian; 
}

// Member Function of Mekanik
// Admin Functions
// 1. Fungsi membuat mekanik
void Mekanik::createMekanik() {
	// Deklarasi variabel
	string fileLayanan = "data/layanan.txt";
	string fileMekanik = "data/mekanik.txt";

	Mekanik mekanikBaru;
	string namaMekanik, keahlianMekanik;
	int choiceInt;
	char choice;

	// Masukkan data mekanik
	while (1) {
		cout << "Masukkan nama mekanik: ";
		cin.ignore();
		getline(cin, namaMekanik);
		mekanikBaru.setNama(namaMekanik);

		cout << "List layanan bengkel DMITS:" << endl;
		getHeaderNames(fileLayanan);
		cout << "Pilih keahlian mekanik sesuai layanan bengkel: ";
		cin >> choiceInt;
		keahlianMekanik = pilihKeahlian(choiceInt, fileLayanan);

		if (keahlianMekanik.empty()) {
			system("cls");
			cout << "Pilihan tidak valid! Silahkan isi data kembali!" << endl;
			cin.ignore();
			continue;
		}
		else if (checkKeahlian(choiceInt, fileMekanik)) {
			system("cls");
			cout << "Keahlian sudah terdaftar! Silahkan isi data kembali!" << endl;
			cin.ignore();
			continue;
		} 
		else {
			mekanikBaru.setKeahlian(keahlianMekanik);
			break;
		}
	}

	// Review data mekanik
	system("cls");
	while (1) {
		cout << "Review Penambahan Data Mekanik" << endl;
		cout << "Nama Mekanik: " << mekanikBaru.getNama() << endl;
		cout << "Keahlian Mekanik: " << mekanikBaru.getKeahlian() << endl;
		cout << endl;
		cout << "Apakah data mekanik sudah benar? (y/n): ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y') {
			system("cls");
			mekanikBaru.mekanikFileWritting(mekanikBaru);
			cout << endl;
			break;
		}
		else if (choice == 'n' || choice == 'N') {
			system("cls");
			cout << "Penambahan mekanik dibatalkan" << endl;
			break;
		}
		else {
			system("cls");
			cout << "Pilihan tidak valid!" << endl;
		}
	}
}

void Mekanik::mekanikFileWritting(Mekanik m) {
	string folder = "data";
	string filename = folder + "/mekanik.txt";
	int lastLineNumber = getLastLineNumber(filename) + 1;

	// Deklarasi folder jika folder tidak ada di directory
	if (!filesystem::exists(folder)) {
		filesystem::create_directory(folder);
		cout << "Folder 'data' created." << endl;
	}

	// Membuat file dengan data mekanik
	ofstream outFile(filename, ios::app);
	if (outFile.is_open()) {
		cout << "Membuat data mekanik di folder 'data'." << endl;
		outFile << lastLineNumber << "." << endl;
		outFile << "Nama Mekanik: " << m.getNama() << endl;
		outFile << "Keahlian Mekanik: " << m.getKeahlian() << endl;
		outFile.close();
		cout << "Data mekanik " << m.getNama() << " berhasil ditambahkan!" << endl;
	}
	else {
		cout << "Failed to create file in folder.\n";
	}
	
}

// 2. Fungsi mengedit mekanik
void Mekanik::editMekanik() {
	string fileMekanik = "data/mekanik.txt";
	string fileLayanan = "data/layanan.txt";
	string choice;
	string line;
	regex numberRegex(R"(^\s*(\d+)\.\s*$)");
	smatch match;
	Mekanik mekanikBaru;

	string namaMekanik, keahlianMekanik;
	int idMekanik = 0;
	int choiceInt = 0;
	char choiceChar;
	int choiceNumber = 0;

	while (1) {
		vector<string> lines;
		ifstream inFile(fileMekanik);
		while (getline(inFile, line)) {
			lines.push_back(line);
		}
		inFile.close();

		bool mekanikFound = false;
		cout << "Mekanik Bengkel DMITS" << endl;
		getHeaderNames(fileMekanik);
		cout << endl << "Pilih Mekanik untuk di edit. (Ketik 'back' untuk kembali)" << endl;
		getline(cin, choice);

		if (choice.empty()) {
			system("cls");
			continue;
		}

		if (choice == "back") {
			system("cls");
			return;
		}

		if (!isDigitsOnly(choice)) {
			system("cls");
			cout << "Data mekanik tidak ditemukan!" << endl;
			continue;
		}

		// Takes user input if it finds the right number
		choiceNumber = stoi(choice);
		for (size_t i = 0; i < lines.size(); ++i) {
			if (regex_match(lines[i], match, numberRegex)) {
				int number = stoi(match[1]);
				if (number == choiceNumber) {
					system("cls");
					mekanikFound = true;
					while (mekanikFound) {
						cout << "Data mekanik lama" << endl;
						cout << lines[i + 1] << endl;
						cout << lines[i + 2] << endl;
						cout << endl;

						cout << "Masukkan data mekanik baru" << endl;
						cout << "Masukkan nama mekanik: ";
						getline(cin, namaMekanik);
						mekanikBaru.setNama(namaMekanik);

						cout << "List layanan bengkel DMITS:" << endl;
						getHeaderNames(fileLayanan);
						cout << "Pilih keahlian mekanik sesuai layanan bengkel: ";
						cin >> choiceInt;
						keahlianMekanik = pilihKeahlian(choiceInt, fileLayanan);
						mekanikBaru.setKeahlian(keahlianMekanik);

						bool keahlianSama = "Keahlian Mekanik: " + mekanikBaru.getKeahlian() == lines[i + 2];
						if (keahlianMekanik.empty()) {
							system("cls");
							cout << "Pilihan tidak valid! Silahkan isi data kembali!" << endl;
							cin.ignore();
							continue;
						}
						else if (checkKeahlian(choiceInt, fileMekanik) && !keahlianSama) {
							system("cls");
							cout << "Keahlian sudah terdaftar! Silahkan isi data kembali!" << endl;
							cin.ignore();
							continue;
						}
						else {
							lines[i + 1] = "Nama Mekanik: " + mekanikBaru.getNama();
							lines[i + 2] = "Keahlian Mekanik: " + mekanikBaru.getKeahlian();
							system("cls");
							break;
						}
					}
				}
			}
		}

		// Update the data, else skips
		if (mekanikFound) {
			while (1) {
				cout << "Review Update Data Mekanik" << endl;
				cout << "Nama Mekanik: " << mekanikBaru.getNama() << endl;
				cout << "Keahlian Mekanik: " << mekanikBaru.getKeahlian() << endl;
				cout << endl;
				cout << "Apakah data mekanik sudah benar? (y/n): ";
				cin >> choiceChar;

				if (choiceChar == 'y' || choiceChar == 'Y') {
					// Overwrite file with updated data
					ofstream outFile(fileMekanik);
					for (const string& l : lines) {
						outFile << l << endl;
					}
					outFile.close();

					cout << "\nMekanik berhasil diupdate!\n";
					_getch();
					system("cls");
					break;
				}
				else if (choiceChar == 'n' || choiceChar == 'N') {
					system("cls");
					cout << "Update mekanik dibatalkan!" << endl;
					break;
				}
				else {
					system("cls");
					cout << "Pilihan tidak valid!" << endl;
					continue;
				}
			}
		}
		else {
			system("cls");
			cout << "Data mekanik tidak ditemukan!" << endl;
		}
	}
}

// 3. Fungsi menghapus mekanik
void Mekanik::deleteMekanik() {
	string filename = "data/mekanik.txt";
	string choice;
	string line;
	regex numberRegex(R"(^\s*(\d+)\.\s*$)");
	smatch match;
	int choiceNumber = 0;

	while (1) {
		vector<string> lines;
		ifstream inFile(filename);
		while (getline(inFile, line)) {
			lines.push_back(line);
		}
		inFile.close();

		bool mekanikFound = false;
		cout << "Mekanik Bengkel DMITS" << endl;
		getHeaderNames(filename);
		cout << endl << "Pilih mekanik yang ingin dihapus. (Ketik 'back' untuk kembali)" << endl;
		getline(cin, choice);

		if (choice.empty()) {
			system("cls");
			continue;
		}

		if (choice == "back") {
			system("cls");
			return;
		}

		if (!isDigitsOnly(choice)) {
			system("cls");
			cout << "Input tidak valid!" << endl;
			continue;
		}

		choiceNumber = stoi(choice);

		size_t indexToRemove = -1;
		for (size_t i = 0; i < lines.size(); ++i) {
			if (regex_match(lines[i], match, numberRegex)) {
				int number = stoi(match[1]);
				if (number == choiceNumber) {
					indexToRemove = i;
					mekanikFound = true;
					break;
				}
			}
		}

		if (!mekanikFound) {
			system("cls");
			cout << "Data mekanik tidak ditemukan!" << endl;
			continue;
		}

		// Confirm deletion
		system("cls");
		cout << "\nAnda yakin ingin menghapus mekanik berikut?" << endl;
		cout << lines[indexToRemove + 1] << endl;
		cout << lines[indexToRemove + 2] << endl;
		cout << "\nKetik 'y' untuk hapus, lainnya untuk batal: ";
		char confirm;
		cin >> confirm;
		cin.ignore();

		if (confirm == 'y' || confirm == 'Y') {
			lines.erase(lines.begin() + indexToRemove, lines.begin() + indexToRemove + 3);

			// Re-number everything
			int newIndex = 1;
			for (size_t i = 0; i < lines.size(); ++i) {
				if (regex_match(lines[i], numberRegex)) {
					lines[i] = to_string(newIndex) + ".";
					++newIndex;
				}
			}

			// Write updated data
			ofstream outFile(filename);
			for (const auto& l : lines) {
				outFile << l << endl;
			}
			outFile.close();

			system("cls");
			cout << "Mekanik berhasil dihapus!" << endl;
			_getch();
		}
		else {
			system("cls");
			cout << "Penghapusan dibatalkan." << endl;
		}
	}
}

// 4. Fungsi melihat mekanik
void Mekanik::showMekanik() {
	ifstream inFile("data/mekanik.txt");
	string line;
	if (inFile.is_open()) {
		cout << "Data mekanik Bengkel DMITS:" << endl;
		while (getline(inFile, line)) {
			cout << line << endl;
		}
		inFile.close();
	}
	else {
		cout << "Failed to open file." << endl;
	}
	cout << endl << "Press anything to close...";
	_getch();
	system("cls");
}