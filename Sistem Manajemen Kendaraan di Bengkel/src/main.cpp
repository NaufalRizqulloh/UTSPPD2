#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>

#include "../include/Bengkel.h"
#include "../include/Kendaraan.h"
#include "../include/Layanan.h"
#include "../include/mekanik.h"
#include "../include/Transaksi.h"

using namespace std;

int main() {
	// Deklarasi variabel
	Layanan l;
	Mekanik m;
	Transaksi t;
	
	string passwordAdmin;
	bool isAdmin = false;
	char choice;

	// Login admin (Done)
	while (!isAdmin) {
		cout << "Login sebagai admin? (y/n): ";
		cin >> choice;
		while (choice == 'y' || choice == 'Y') {
			cout << "Masukkan password admin: ";
			getline(cin, passwordAdmin);
			cin >> passwordAdmin;
			if (passwordAdmin == "12345") {
				isAdmin = true;
				system("cls");
				cout << "Selamat datang admin Bengkel DMITS!" << endl;
				break;
			}
			else if (passwordAdmin == "back") {
				system("cls");
				cout << "Login dibatalkan!" << endl;
				break;
			}
			system("cls");
			cout << "Password Salah! Ketik 'back' untuk membatalkan login" << endl;
		}
		if (choice == 'n' || choice == 'N') {
			system("cls");
			break;
		}
		else if (choice != 'y' && choice != 'Y') {
			system("cls");
			cout << "Pilihan tidak valid!" << endl;
		}
	}
	
	// Interface admin ketika berhasil login
	while (isAdmin) {
		cout << "Menu Admin" << endl;	
		cout << "1. Tambah/Edit Layanan" << endl;
		cout << "2. Tambah/Edit Data Mekanik" << endl;
		cout << "3. Tambah/Edit Data Transaksi" << endl;
		cout << "9. Logout" << endl;
		cin >> choice;
		system("cls");

		// Console Layanan (Done)
		if (choice == '1') {
			while (1) {
				cout << "Menu Admin - Layanan" << endl;
				cout << "1. Tambah Layanan" << endl;
				cout << "2. Edit Layanan" << endl;
				cout << "3. Hapus Layanan" << endl;
				cout << "4. Lihat Layanan" << endl;
				cout << "9. Kembali" << endl;
				cin >> choice;
				system("cls");

				if (choice == '1') {
					// Tambah Layanan
					l.createLayanan();
				}
				else if (choice == '2') {
					system("cls");
					l.editLayanan();
				}
				else if (choice == '3') {
					// Hapus Layanan
					l.deleteLayanan();
				}
				else if (choice == '4') {
					// Lihat Layanan
					l.showLayanan();
				}
				else if (choice == '9') {
					break;
				}
				else {
					cout << "Pilihan tidak valid!" << endl;
				}
			}
		}
		// Console Mekanik
		else if (choice == '2') {
			while (1) {
				cout << "Menu Admin - Mekanik" << endl;
				cout << "1. Tambah Mekanik" << endl;
				cout << "2. Edit Mekanik" << endl;
				cout << "3. Hapus Mekanik" << endl;
				cout << "4. Lihat Mekanik" << endl;
				cout << "9. Kembali" << endl;
				cin >> choice;
				system("cls");

				if (choice == '1') {
					// Tambah Mekanik
					m.createMekanik();
				}
				else if (choice == '2') {
					// Edit Mekanik
					m.editMekanik();
				}
				else if (choice == '3') {
					// Hapus Mekanik
					m.deleteMekanik();
				}
				else if (choice == '4') {
					// Lihat Mekanik
					m.showMekanik();					
				}
				else if (choice == '9') {
					break;
				}
				else {
					cout << "Pilihan tidak valid!" << endl;
				}
			}
		}
		// Console Data transaksi
		else if (choice == '3') {
			while (1) {
				cout << "Menu Admin - Transaksi" << endl;
				cout << "1. Tambah Transaksi" << endl;
				cout << "2. Edit Transaksi" << endl;
				cout << "3. Proses Transaksi" << endl;
				cout << "4. Lihat Transaksi" << endl;
				cout << "9. Kembali" << endl;
				cin >> choice;
				system("cls");

				if (choice == '1') {
					// Tambah Transaksi
					menuBengkel(); // Masuk ke menu pengisian data servis
					system("cls");
				}
				else if (choice == '2') {
					// Edit Transaksi
					t.editTransaksi();
				}
				else if (choice == '3') {
					// Proses Transaksi
					t.prosesTransaksi();
				}
				else if (choice == '4') {
					// Lihat Transaksi
					t.showTransaksi();
					cout << "Press anything to continue..." << endl;
					_getch();
					system("cls");
				}
				else if (choice == '9') {
					break;
				}
				else {
					cout << "Pilihan tidak valid!" << endl;
				}
			}
		}
		// Logout
		else if (choice == '9') {
			isAdmin = false;
			system("cls");
			break;
		}
		// Default
		else {
			system("cls");
			cout << "Pilihan tidak valid!" << endl;
		}
	}

	// Interface pelanggan
	menuBengkel();
	
	return 0;
}
