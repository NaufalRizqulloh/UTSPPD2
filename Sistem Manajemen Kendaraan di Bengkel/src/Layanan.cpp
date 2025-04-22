#include <iostream>
#include <string>
#include <conio.h>

#include <fstream>
#include <filesystem>
#include <regex>

#include "../include/helper.h"

#include "../include/Layanan.h"

using namespace std;

// Member Functions of Layanan
// Admin Functions
// 1. Fungsi membuat layanan (Mekanik masih belum terintegrasi)
void Layanan::createLayanan() {
	// Deklarasi variabel
	char choice;

	// Masukkan data layanan
	cout << "Masukkan nama layanan: ";
	cin.ignore();
	getline(cin, namaLayanan);
	cout << "Masukkan harga layanan: ";
	cin >> hargaLayanan;

	// Review data layanan
	system("cls");
	while (1) {
		cout << "Review Penambahan Data Layanan" << endl;
		cout << "Nama Layanan: " << namaLayanan << endl;
		cout << "Harga Layanan: " << hargaLayanan << endl;
		cout << endl;
		cout << "Apakah data layanan sudah benar? (y/n): ";
		cin >> choice;

		if (choice == 'y' || choice == 'Y') {
			system("cls");
			layananFileWritting();
			cout << endl;

			break;
		}
		else if (choice == 'n' || choice == 'N') {
			system("cls");
			cout << "Penambahan layanan dibatalkan" << endl;
			break;
		}
		else {
			system("cls");
			cout << "Pilihan tidak valid!" << endl;
		}
	}
}

void Layanan::layananFileWritting() {
	string folder = "data";
	string filename = folder + "/layanan.txt";

	// Deklarasi folder jika folder tidak ada di directory
	if (!filesystem::exists(folder)) {
		filesystem::create_directory(folder);
		cout << "Folder 'data' created." << endl;	
	}

	// Membuat file dengan data layanan
	ofstream outFile(filename, ios::app);
	if (outFile.is_open()) {
		int lastLineNumber = getLastLineNumber(filename) + 1;
		cout << "Membuat data layanan di folder 'data'." << endl;
		outFile << lastLineNumber << ". " << endl;
		outFile << "Nama Layanan: " << namaLayanan << endl;
		outFile << "Harga Layanan: " << hargaLayanan << endl;
		outFile.close();
		cout << "Data layanan " << namaLayanan << " berhasil ditambahkan!" << endl;
	}
	else {
		cout << "Failed to create file in folder.\n";
	}
}

// 2. Fungsi mengedit layanan
void Layanan::editLayanan() {
	string filename = "data/layanan.txt";
	string choice;
	string line;
	regex numberRegex(R"(^\s*(\d+)\.\s*$)");
	smatch match;
	char choiceChar;
	int choiceNumber = 0;
	
	while (1) {
		vector<string> lines;
		ifstream inFile(filename);
		while (getline(inFile, line)) {
			lines.push_back(line);
		}
		inFile.close();

		bool layananFound = false;
		cout << "Layanan Bengkel DMITS" << endl;
		getHeaderNames(filename);
		cout << endl << "Pilih layanan untuk di edit. (Ketik 'back' untuk kembali)" << endl;
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
			cout << "Data layanan tidak ditemukan!" << endl;
			continue;
		}

		// Takes user input if it finds the right number
		choiceNumber = stoi(choice);
		for (size_t i = 0; i < lines.size(); ++i) {
			if (regex_match(lines[i], match, numberRegex)) {
				int number = stoi(match[1]);
				if (number == choiceNumber) {
					layananFound = true;
					system("cls");
					cout << "Data layanan lama" << endl;
					cout << lines[i + 1] << endl;
					cout << lines[i + 2] << endl;
					cout << endl;

					cout << "Masukkan data layanan baru " << endl;
					cout << "Nama layanan : ";
					getline(cin, namaLayanan);
					lines[i + 1] = "Nama Layanan: " + namaLayanan;

					cout << "Harga layanan : ";
					cin >> hargaLayanan;
					lines[i + 2] = "Harga Layanan: " + to_string(hargaLayanan);

					system("cls");
					break;
				}
			}
		}

		// Update the data, else skips
		if (layananFound) {
			while (1) {
				cout << "Review Update Data Layanan" << endl;
				cout << "Nama layanan : " << namaLayanan << endl;
				cout << "Harga layanan : " << hargaLayanan << endl;
				cout << endl;
				cout << "Apakah data layanan sudah benar? (y/n): ";
				cin >> choiceChar;

				if (choiceChar == 'y' || choiceChar == 'Y') {
					// Overwrite file with updated data
					ofstream outFile(filename);
					for (const string& l : lines) {
						outFile << l << endl;
					}
					outFile.close();

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
		else {
			system("cls");
			cout << "Data layanan tidak ditemukan!" << endl;
		}
	}
}

// 3. Fungsi menghapus layanan
void Layanan::deleteLayanan() {
	string filename = "data/layanan.txt";
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

		bool layananFound = false;
		cout << "Layanan Bengkel DMITS" << endl;
		getHeaderNames(filename);
		cout << endl << "Pilih layanan yang ingin dihapus. (Ketik 'back' untuk kembali)" << endl;
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
					layananFound = true;
					break;
				}
			}
		}

		if (!layananFound) {
			system("cls");
			cout << "Data layanan tidak ditemukan!" << endl;
			continue;
		}

		// Confirm deletion
		system("cls");
		cout << "\nAnda yakin ingin menghapus layanan berikut?" << endl;
		cout << lines[indexToRemove + 1] << endl;
		cout << lines[indexToRemove + 2] << endl;
		cout << "\nKetik 'y' untuk hapus, lainnya untuk batal: ";
		char confirm;
		cin >> confirm;
		cin.ignore(); // to clear newline

		if (confirm == 'y' || confirm == 'Y') {
			// Remove 3 lines: number, name, price
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
			cout << "Layanan berhasil dihapus!" << endl;
			_getch();
		}
		else {
			system("cls");
			cout << "Penghapusan dibatalkan." << endl;
		}
	}
}

// 4. Fungsi melihat layanan
void Layanan::showLayanan() {
	ifstream inFile("data/layanan.txt");
	string line;
	if (inFile.is_open()) {
		cout << "Data Layanan Bengkel DMITS:" << endl;
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