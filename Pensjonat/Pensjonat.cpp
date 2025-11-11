
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
		cout << "6. Zamknij stronę pensjonatu." << endl;
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
			koniec();
		}
		else {
			cout << "Podałeś błędną wartość! Wpisz poprawną liczbę od 1-6" << endl;
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
	int koniec() {
		exit(0);
	}
};
int main()
{
	Pensjonat obiekt1;
	obiekt1.wyswietlinfo();
	return 0;
}

