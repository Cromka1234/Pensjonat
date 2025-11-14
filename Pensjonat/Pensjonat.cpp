#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class Pensjonat {
public:
	void wyswietlinfo() {
		int numer;
		cout << "Witamy w pensjonacie! Wpisz numer jednej z podanych opcji." << endl << endl;
		cout << "1. Wyświetl dostępne pokoje" << endl;
		cout << "2. Zarezerwuj jeden z pokoi." << endl;
		cout << "3. Wyświetl zajęte pokoje." << endl;
		cout << "4. Usuń rezerwację." << endl;
		cout << "5. Wyświetl opisy pokoi" << endl;
		cout << "6. Dodaj pokój" << endl;
		cout << "7. Usuń pokój" << endl;
		cout << "8. Dodaj opis" << endl;
		cout << "9. Usuń opis" << endl;
		cout << "10. Wyświetl pokoje VIP" << endl;
		cout << "11. Dodaj pokój VIP" << endl;
		cout << "12. Usuń pokój VIP" << endl;
		cout << "13. Usuń opis pokoju VIP" << endl;
		cout << "14. Wyświetl opisy pokoi VIP" << endl;
		cout << "15. Koniec." << endl;
		cin >> numer;
		if (numer == 1) {
			wyswietldostepnepokoje();
		}
		else if (numer == 2) {
			zarezerwujjedenzpokoi();
		}
		else if (numer == 3) {
			wyswietlzajetepokoje();
		}
		else if (numer == 4) {
			usunrezerwacje();
		}
		else if (numer == 5) {
			wyswietlopisypokoi();
		}
		else if (numer == 6) {
			dodawaniepokoju();
		}
		else if (numer == 7) {
			usuwaniepkoju();
		}
		else if (numer == 8) {
			dodawanieopisu();
		}
		else if (numer == 9) {
			usunopis();
		}
		else if (numer == 10) {
			wyswietlpokojevip();
		}
		else if (numer == 11) {
			dodajpokojvip();
		}
		else if (numer == 12) {
			usunpokojvip();
		}
		else if (numer == 13) {
			usunopispokojuvip();
		}
		else if (numer == 14) {
			wyswietlopisypokoivip();
		}
		else if (numer == 15) {
			koniec();
		}
		else {
			cout << "Podałeś błędną wartość! Wpisz poprawną liczbę od 1-15" << endl;
			wyswietlinfo();
		}
	}
private:
	void wyswietldostepnepokoje() {
		cout << "dzialam1" << endl;
		wyswietlinfo();
	}
	void zarezerwujjedenzpokoi() {
		cout << "dzialam2" << endl;
		wyswietlinfo();
	}
	void wyswietlzajetepokoje() {
		cout << "dzialam3" << endl;
		wyswietlinfo();
	}
	void usunrezerwacje() {
		cout << "dzialam4" << endl;
		wyswietlinfo();
	}
	void wyswietlopisypokoi() {
		cout << "dzialam5" << endl;
		wyswietlinfo();
	}
	void dodawaniepokoju() {
		cout << "dzialam6" << endl;
		wyswietlinfo();
	}
	void usuwaniepkoju() {
		cout << "dzialam7" << endl;
		wyswietlinfo();
	}
	void dodawanieopisu() {
		cout << "dzialam8" << endl;
		wyswietlinfo();
	}
	void usunopis() {
		cout << "dzialam9" << endl;
		wyswietlinfo();
	}
	void wyswietlpokojevip() {
		cout << "dzialam10" << endl;
		wyswietlinfo();
	}
	void dodajpokojvip() {
		cout << "dzialam11" << endl;
		wyswietlinfo();
	}
	void usunpokojvip() {
		cout << "dzialam12" << endl;
		wyswietlinfo();
	}
	void usunopispokojuvip() {
		cout << "dzialam13" << endl; 
		wyswietlinfo();
	}
	void wyswietlopisypokoivip() {
		cout << "dzialam14" << endl;
		wyswietlinfo();
	}
	int koniec() {
		exit(0);
	}
};
int main()
{
	setlocale(LC_ALL, "polish");
	Pensjonat obiekt1;
	obiekt1.wyswietlinfo();
	
	return 0;
}
