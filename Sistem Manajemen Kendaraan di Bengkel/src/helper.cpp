#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <regex>

#include "../include/helper.h"
#include "../include/Kendaraan.h"
#include "../include/pelanggan.h"

using namespace std;

// Other Functions to help with the member functions
// Numbering function
int getLastLineNumber(const string& filename) {
	ifstream inFile(filename);
	string line;
	int lastNumber = 0;
	regex numberDotRegex(R"(^\s*(\d+)\.\s*$)");

	while (getline(inFile, line)) {
		if (!line.empty()) {
			// Extract the number from the beginning of the line
			if (regex_match(line, numberDotRegex)) {
				int number = std::stoi(line.substr(0, line.length() - 1));
				lastNumber = number;
			}
		}
	}

	return lastNumber;
}

// Get the number and header names from file
void getHeaderNames(const string& filename) {
	ifstream inFile(filename);
	string line;
	regex numberDotRegex(R"(^\s*(\d+)\.\s*$)");
	int lineCounter = 0;

	while (getline(inFile, line)) {
		lineCounter++;
		if (regex_match(line, numberDotRegex)) {
			string number = line;

			if (getline(inFile, line)) { // Next line should be the header name
				string header = line;
				cout << number << " " << header << "\n";
			}
			getline(inFile, line);
		}
	}
	inFile.close();
}

// Make sure it's only number
bool isDigitsOnly(const string& str) {
	return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

// Function to choose keahlian
string pilihKeahlian(int choice, const string& filename) {
	string line;
	regex numberRegex(R"(^\s*(\d+)\.\s*$)");
	smatch match;
	bool keahlianFound = false;

	vector<string> lines;
	ifstream inFile(filename);
	while (getline(inFile, line)) {
		lines.push_back(line);
	}
	inFile.close();

	size_t foundedLines = -1;
	for (size_t i = 0; i < lines.size(); ++i) {
		if (regex_match(lines[i], match, numberRegex)) {
			int number = stoi(match[1]);
			if (number == choice) {
				foundedLines = i;
				keahlianFound = true;
				break;
			}
		}
	}

	if (!keahlianFound) {
		system("cls");
		cout << "Data layanan tidak ditemukan!" << endl;
		return "";
	}
	else {
		// Get the keahlian from the next line
		string keahlianLine = lines[foundedLines + 1];
		string prefix = "Nama Layanan: ";
		string keahlian = "";

		if (keahlianLine.find(prefix) == 0) {
			keahlian = keahlianLine.substr(prefix.length());
		}
		else {
			keahlian = keahlianLine;
		}

		return keahlian;
	}
}

// Function to get layanan ID based on the inputted name
int getLayananHeaderByName(const string& serviceName) {
	ifstream inFile("data/layanan.txt");
	string line;
	regex headerRegex(R"(^\s*(\d+)\.\s*$)");
	smatch match;

	int currentHeader = -1;

	while (getline(inFile, line)) {
		if (regex_match(line, match, headerRegex)) {
			currentHeader = stoi(match[1]);
		}

		// Look for the Nama Layanan match
		if (line.find("Nama Layanan:") != string::npos) {
			string layanan = line.substr(line.find(":") + 1);
			layanan = layanan.substr(layanan.find_first_not_of(" "));

			if (layanan == serviceName) {
				return currentHeader; // Found match, return the header number
			}
		}
	}

	return -1; // Not found
}

// Function to get biaya servis based on Layanan
int biayaServisHelper(int choiceInt) {
	string fileName = "data/layanan.txt";
	
	string line;
	regex numberRegex(R"(^\s*(\d+)\.\s*$)");
	smatch match;
	bool servisFound = false;

	vector<string> lines;
	ifstream inFile(fileName);
	while (getline(inFile, line)) {
		lines.push_back(line);
	}
	inFile.close();

	size_t foundedLines = -1;
	for (size_t i = 0; i < lines.size(); ++i) {
		if (regex_match(lines[i], match, numberRegex)) {
			int number = stoi(match[1]);
			if (number == choiceInt) {
				foundedLines = i;
				servisFound = true;
				break;
			}
		}
	}

	if (!servisFound) {
		system("cls");
		cout << "Data layanan tidak ditemukan!" << endl;
		return 0;
	}
	else {
		// Get the harga from the next line
		string keahlianLine = lines[foundedLines + 2];
		string prefix = "Harga Layanan: ";
		int harga = 0;

		if (keahlianLine.find(prefix) == 0) {
			harga = stoi(keahlianLine.substr(prefix.length()));
		}
		else {
			harga = stoi(keahlianLine);
		}

		return harga;
	}
}

// Function to check keahlian and service provided by mekanik
bool checkKeahlian(const int keahlian, const string& filename) {
	ifstream inFile(filename);
	string line;
	regex keahlianRegex(R"(^Keahlian Mekanik:\s*(.*)$)");
	smatch match;
	bool keahlianFound = false;
	// Find the keahlian based on Layanan.txt
	string keahlianString = "Keahlian Mekanik: " + pilihKeahlian(keahlian, "data/layanan.txt");

	// The actual matching
	while (getline(inFile, line)) {
		if (regex_match(line, match, keahlianRegex)) {
			string existingKeahlian = line;
			if (existingKeahlian == keahlianString) {
				keahlianFound = true;
				break;
			}
		}
	}
	inFile.close();
	return keahlianFound;
}

// Function to return bengkel PJ
string bengkelPJ(int choiceInt) {
	ifstream inFile("data/mekanik.txt");
	string line;
	string currentName = "";
	string prefixKeahlian = "Keahlian Mekanik: ";
	string prefixNama = "Nama Mekanik: ";
	string keahlian = pilihKeahlian(choiceInt, "data/layanan.txt");

	while (getline(inFile, line)) {
		if (line.find(prefixNama) == 0) {
			currentName = line.substr(prefixNama.length());
		}
		else if (line.find(prefixKeahlian) == 0) {
			string foundKeahlian = line.substr(prefixKeahlian.length());
			if (foundKeahlian == keahlian) {
				return currentName;
			}
		}
	}

	return "Tidak ada mekanik yang menguasai layanan ini.";
}

// Function to get block data using transaksiId
string getBlockDataByTransaksiId(const string& filename, int targetId) {
	ifstream inFile(filename);
	string line;
	string blockData;
	string currentBlock;
	regex headerRegex(R"(^\s*(\d+)\.\s*$)");
	regex transaksiIdRegex(R"(^ID Transaksi:\s*(\d+)$)");
	smatch match;

	while (getline(inFile, line)) {
		if (regex_match(line, match, headerRegex)) {
			currentBlock = line + "\n";
		}
		else {
			currentBlock += line + "\n";
		}

		if (regex_match(line, match, transaksiIdRegex)) {
			int foundId = stoi(match[1]);
			if (foundId == targetId) {
				blockData = currentBlock;
				break;
			}
		}
	}
	inFile.close();
	return blockData;
}

// Function to load kendaraan and pelanggan data to memory based on transaksiID
void loadDataByTransaksiID(int transaksiID, Kendaraan* kendaraan, Pelanggan& pelanggan) {
	ifstream kendaraanStream("data/kendaraan.txt"), pelangganStream("data/pelanggan.txt");
	string line;
	regex headerRegex(R"(^\s*(\d+)\.\s*$)");
	smatch match;
	bool capturing = false;

	// --- Handle Kendaraan ---
	while (getline(kendaraanStream, line)) {
		if (regex_match(line, match, headerRegex)) {
			capturing = false;
		}
		if (line.find("ID Transaksi:") != string::npos) {
			int id = stoi(line.substr(line.find(":") + 1));
			if (id == transaksiID) {
				capturing = true;
			}
		}

		if (capturing) {
			if (line.find("Plat Nomor:") != string::npos)
				kendaraan->setPlatNo(line.substr(line.find(":") + 2));
			else if (line.find("Tahun Kendaraan:") != string::npos)
				kendaraan->setTahun(stoi(line.substr(line.find(":") + 2)));
			else if (line.find("Tipe Kendaraan:") != string::npos)
				kendaraan->setTipe(line.substr(line.find(":") + 2));
			else if (line.find("Keperluan Servis:") != string::npos)
				kendaraan->setStatusServis(line.substr(line.find(":") + 2));
		}
	}

	// --- Handle Pelanggan ---
	capturing = false;
	while (getline(pelangganStream, line)) {
		if (regex_match(line, match, headerRegex)) {
			capturing = false;
		}
		if (line.find("ID Transaksi:") != string::npos) {
			int id = stoi(line.substr(line.find(":") + 1));
			if (id == transaksiID) {
				capturing = true;
			}
		}

		if (capturing) {
			if (line.find("Nama Pelanggan:") != string::npos)
				pelanggan.setNama(line.substr(line.find(":") + 2));
			else if (line.find("Kontak Pelanggan:") != string::npos)
				pelanggan.setKontak(line.substr(line.find(":") + 2));
		}
	}

	kendaraanStream.close();
	pelangganStream.close();
}

// Function to check if the pelanggan already have service pending (based on kendaraan.txt->plat nomor)
bool checkPlat(const string& platNo) {
	ifstream inFile("data/kendaraan.txt");
	string line;
	regex platNoRegex(R"(^Plat Nomor:\s*(.*)$)");
	smatch match;
	bool platPelanggan = false;
	while (getline(inFile, line)) {
		if (regex_match(line, match, platNoRegex)) {
			string existingPlatNo = match[1];
			if (existingPlatNo == platNo) {
				platPelanggan = true;
				break;
			}
		}
	}
	inFile.close();
	return platPelanggan;
}

// Function to check if the pelanggan already have service pending (based on kendaraan.txt->Tahun)
bool checkTahun(const int tahun) {
	ifstream inFile("data/kendaraan.txt");
	string line;
	regex platNoRegex(R"(^Tahun Kendaraan:\s*(.*)$)");
	smatch match;
	bool platPelanggan = false;
	while (getline(inFile, line)) {
		if (regex_match(line, match, platNoRegex)) {
			int existingPlatNo = stoi(match[1]);
			if (existingPlatNo == tahun) {
				platPelanggan = true;
				break;
			}
		}
	}
	inFile.close();
	return platPelanggan;
}

// Function to check if the pelanggan already have service pending (based on kendaraan.txt->tipe kendaraan)
bool checkTipeKendaraan(const string& tipeKendaraan) {
	ifstream inFile("data/kendaraan.txt");
	string line;
	regex tipeKendaraanRegex(R"(^Tipe Kendaraan:\s*(.*)$)");
	smatch match;
	bool tipePelanggan = false;
	while (getline(inFile, line)) {
		if (regex_match(line, match, tipeKendaraanRegex)) {
			string existingTipeKendaraan = match[1];
			if (existingTipeKendaraan == tipeKendaraan) {
				tipePelanggan = true;
				break;
			}
		}
	}
	inFile.close();
	return tipePelanggan;
}

// Function to check if the pelanggan already have service pending (based on pelanggan.txt->nama)
bool checkNamaPelanggan(const string& namaPelanggan) {
	ifstream inFile("data/pelanggan.txt");
	string line;
	regex namaPelangganRegex(R"(^Nama Pelanggan:\s*(.*)$)");
	smatch match;
	bool namaPelangganFound = false;
	while (getline(inFile, line)) {
		if (regex_match(line, match, namaPelangganRegex)) {
			string existingNamaPelanggan = match[1];
			if (existingNamaPelanggan == namaPelanggan) {
				namaPelangganFound = true;
				break;
			}
		}
	}
	inFile.close();
	return namaPelangganFound;
}