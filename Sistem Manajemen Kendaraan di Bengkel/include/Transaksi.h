#include <vector>
#include <string>

#include "../include/pelanggan.h"
#include "../include/Kendaraan.h"

using namespace std;

class Transaksi {
private:
	// Member Variable
	string keperluanServis;
	int biayaServis;
	string mekanikPJ;
	int transaksiId;
public:
	// Setter Function
	void keperluanServissetter(string keperluanServis) {
		this->keperluanServis = keperluanServis;
	}
	void biayaServissetter(int biayaServis) {
		this->biayaServis = biayaServis;
	}
	void mekanikPJsetter(string mekanikPJ) {
		this->mekanikPJ = mekanikPJ;
	}
	void transaksiIdsetter(int transaksiId) {
		this->transaksiId = transaksiId;
	}

	// Getter Function
	string getKeperluanServis() {
		return keperluanServis;
	}
	int getBiayaServis() {
		return biayaServis;
	}
	string getMekanikPJ() {
		return mekanikPJ;
	}
	int getTransaksiId() {
		return transaksiId;
	}

	// Member Function
	void transaksiFileWritting(Transaksi t);
	void editTransaksi();
	vector<string> editPelanggan(int choiceInt, Pelanggan& p);
	vector<string> editKendaraan(int choiceInt, Kendaraan& k);
	vector<string> editTransaksiFile(int choiceInt, Pelanggan& p, Kendaraan& k, Transaksi& t);
	void prosesTransaksi();
	int showTransaksi();
};
