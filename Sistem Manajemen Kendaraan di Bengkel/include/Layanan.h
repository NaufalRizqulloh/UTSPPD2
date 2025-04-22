#ifndef LAYANAN_H
#define LAYANAN_H

#include <iostream>
#include <string>

using namespace std;

// Deklarsi class Layanan
class Layanan {
private:
	string namaLayanan;
	int hargaLayanan = 0;
public:
	// Admin Functions
	void createLayanan();
	void layananFileWritting();
	void editLayanan();
	void deleteLayanan();
	void showLayanan();
};

#endif