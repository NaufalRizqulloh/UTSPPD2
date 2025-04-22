#include <iostream>
#include <string>
#include <conio.h>

#include <fstream>
#include <filesystem>
#include <regex>

#include "../include/Bengkel.h"
#include "../include/helper.h"
#include "../include/Kendaraan.h"
#include "../include/Layanan.h"
#include "../include/mekanik.h"
#include "../include/pelanggan.h"
#include "../include/Transaksi.h"

using namespace std;

void menuBengkel() {
	// Variabel nama file
	string folder = "data";
	string fileLayanan = folder + "/layanan.txt";
	string fileKendaraan = folder + "/kendaraan.txt";
	string filePelanggan = folder + "/pelanggan.txt";
	string fileTransaksi = folder + "/transaksi.txt";

	string nama, kontak, keperluanServis, pn, t, ss;
	int idPelanggan, choiceInt, th;
	char choiceChar;
	bool confirmChoice = false;

	cout << "Selamat datang di Bengkel DMITS!" << endl;

	while (1) {
		Layanan l;
		Kendaraan* kendaraan = new Kendaraan();
		Pelanggan p;
		Transaksi* tr = new Transaksi();

		cout << "Apakah anda ingin melakukan servis hari ini? (y/n) ";
		cin >> choiceChar;
		
		if (choiceChar == 'n' || choiceChar == 'N') {
			cout << "Terima kasih telah menggunakan layanan kami!" << endl;
			break;
		}
		else if (choiceChar != 'y' && choiceChar != 'Y') {
			system("cls");
			cout << "Pilihan tidak valid! Silahkan coba lagi." << endl;
			continue;
		}

		// 1. Isi data pelanggan (pelanggan.cpp/h)
		cout << endl;
		cout << "Silahkan isi data diri anda!" << endl;
		cout << "Nama: ";
		cin.ignore();
		getline(cin, nama);

		cout << "Kontak: ";
		getline(cin, kontak);

		// 2. Isi data kendaraan dan keperluan servis (kendaraan.cpp/h, layanan.cpp/h)
		cout << "Masukkan Plat No: ";
		getline(cin, pn);

		cout << "Masukkan Tahun: ";
		cin >> th;

		cout << "Masukkan Tipe: ";
		cin.ignore();
		getline(cin, t);

		cout << endl;
		cout << "Layanan servis Bengkel DMITS" << endl;
		getHeaderNames(fileLayanan);
		cout << "Masukkan keperluan servis: ";
		cin >> choiceInt;
		keperluanServis = pilihKeahlian(choiceInt, fileLayanan);

		// Variable Storing
		p.setNama(nama);
		p.setKontak(kontak);
		p.setTransaksiId(getLastLineNumber(fileTransaksi));

		kendaraan->setPlatNo(pn);
		kendaraan->setTahun(th);
		kendaraan->setTipe(t);
		kendaraan->setStatusServis(keperluanServis);
		kendaraan->setTransaksiId(p.getTransaksiId());

		tr->keperluanServissetter(keperluanServis);
		tr->biayaServissetter(biayaServisHelper(choiceInt));
		tr->mekanikPJsetter(bengkelPJ(choiceInt));
		tr->transaksiIdsetter(p.getTransaksiId());

		// 3. Check untuk data yang kosong
		system("cls");
		if (p.getNama().empty() || p.getKontak().empty()) {
			if (p.getNama().empty()) {
				cout << "Nama pelanggan kosong" << endl;
			}
			if (p.getKontak().empty()) {
				cout << "Kontak pelanggan kosong" << endl;
			}
			cout << "Data pelanggan tidak valid! Silahkan isi ulang data!" << endl;
			continue;
		}
		else if (kendaraan->getPlatNo().empty() || kendaraan->getTahun() == 0 || kendaraan->getTipe().empty()) {
			if (kendaraan->getPlatNo().empty()) {
				cout << "Plat kendaraan kosong" << endl;
			}
			if (kendaraan->getTahun() == 0) {
				cout << "Tahun kendaraan kosong" << endl;
			}
			if (kendaraan->getTipe().empty()) {
				cout << "Tipe kendaraan kosong" << endl;
			}
			cout << "Data kendaraan tidak valid! Silahkan isi ulang data!" << endl;
			continue;
		}
		else if (kendaraan->getStatusServis().empty()) {
			cout << "Keperluan servis tidak valid! Silahkan isi ulang data!" << endl;
			continue;
		}

		// 4. Check pelanggan.txt, kendaraan.txt dan transaksi.txt untuk data yang sama
		while (checkPlat(kendaraan->getPlatNo()) && checkTahun(kendaraan->getTahun()) && checkTipeKendaraan(kendaraan->getTipe()) && checkNamaPelanggan(p.getNama())) {
			cout << "Data sudah pernah terdaftar!" << endl;
			cout << endl;
			cout << "Data Pelanggan: " << endl;
			cout << getBlockDataByTransaksiId(filePelanggan, p.getTransaksiId()) << endl;
			cout << "Data Kendaraan: " << endl;
			cout << getBlockDataByTransaksiId(fileKendaraan, p.getTransaksiId()) << endl;
			cout << "Data Servis: " << endl;
			cout << getBlockDataByTransaksiId(fileTransaksi, p.getTransaksiId()) << endl;
			cout << endl;
			cout << "Apakah anda ingin melanjutkan servis berdasarkan data di atas? (y/n)";
			cin >> choiceChar;
			system("cls");

			if (choiceChar == 'y' || choiceChar == 'Y' || choiceChar == 'n' || choiceChar == 'N') {
				if (choiceChar == 'n' || choiceChar == 'N') {
					cout << "Melanjutkan pengisian data sebleumnya..." << endl;
					break;
				}
				loadDataByTransaksiID(p.getTransaksiId(), kendaraan, p);
				cout << "Data servis berhasil di load!" << endl;
				cout << "Lanjutkan ke pembayaran" << endl;
				confirmChoice = true;
				break;
			}
			else if (choiceChar == 'n' || choiceChar == 'N') {
				cout << "Pengisian data dibatalkan..." << endl;
			}
			else {
				cout << "Pilihan tidak valid! Silahkan coba lagi." << endl;
			}
		}

		if (confirmChoice) {
			break;
		}

		// 5. Review data servis
		while (1) {
			cout << "Review Data Servis" << endl;
			cout << "Nama Pelanggan: " << p.getNama() << endl;
			cout << "Kontak Pelanggan: " << p.getKontak() << endl;
			cout << "Plat Nomer Kendaraan: " << kendaraan->getPlatNo() << endl;
			cout << "Tipe Kendaraan: " << kendaraan->getTipe() << endl;
			cout << "Tahun Kendaraan: " << kendaraan->getTahun() << endl;
			cout << "Keperluan Servis: " << kendaraan->getStatusServis() << endl;
			cout << endl;
			cout << "Biaya Servis: " << tr->getBiayaServis() << endl;
			cout << "Mekanik Penanggung Jawab: " << tr->getMekanikPJ() << endl;
			cout << endl;
			cout << "Apakah data servis sudah benar? (y/n): ";
			cin >> choiceChar;

			if (choiceChar == 'y' || choiceChar == 'Y') {
				// 6. Simpan data servis ke file transaksi.txt, kendaraan.txt dan pelanggan.txt
				p.pelangganFileWritting(p);
				kendaraan->writeData(*kendaraan);
				tr->transaksiFileWritting(*tr);
								
				cout << "Data servis berhasil disimpan!" << endl;
				_getch();
				system("cls");
				cout << "Selamat datang di Bengkel DMITS!" << endl;
				break;
			}
			else if (choiceChar == 'n' || choiceChar == 'N') {
				cout << "Pengisian data dibatalkan..." << endl;
				system("cls");
				cout << "Selamat datang di Bengkel DMITS!" << endl;
				break;
			}
			else {
				system("cls");
				cout << "Pilihan tidak valid! Silahkan coba lagi." << endl;
			}
		}
	}
}

// 6. Menunggu status servis "Selesai" oleh admin bengkel
// (bisa di skip langsung dari kendaraan.cpp/h jika data kendaraan dan data pelanggan sudah ada di file transaksi.txt)

// 7. Lakukan pembayaran (transaksi.cpp/h)