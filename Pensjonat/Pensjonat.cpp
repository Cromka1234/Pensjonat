#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <windows.h>
#include <locale>
#include <codecvt>
using namespace std;

class Pensjonat {
public:
    void wyswietlinfo() {
        int numer;
        cout << endl;
        cout << "1. Wyświetl dostępne pokoje" << endl;
        cout << "2. Zarezerwuj jeden z pokoi." << endl;
        cout << "3. Wyświetl zajęte pokoje." << endl;
        cout << "4. Usuń rezerwację." << endl;
        cout << "5. Wyświetl opisy pokoi" << endl;
        cout << "6. Dodaj pokój" << endl;
        cout << "7. Usuń pokój" << endl;
        cout << "8. Wyświetl pokoje VIP" << endl;
        cout << "9. Dodaj pokój VIP" << endl;
        cout << "10. Usuń pokój VIP" << endl;
        cout << "11. Wyświetl opisy pokoi VIP" << endl;
        cout << "12. Zarezerwuj pokój VIP" << endl;
        cout << "13. Usuń rezerwację pokoju VIP" << endl;
        cout << "14. Wyświetl zajęte pokoje VIP" << endl;
        cout << "15. Koniec." << endl << endl;
        cin >> numer;
        cout << endl;
        switch (numer) {
        case 1: wyswietldostepnepokoje(); break;
        case 2: zarezerwujjedenzpokoi(); break;
        case 3: wyswietlzajetepokoje(); break;
        case 4: usunrezerwacje(); break;
        case 5: wyswietlopisypokoi(); break;
        case 6: dodawaniepokoju(); break;
        case 7: usuwaniepkoju(); break;
        case 8: wyswietlpokojevip(); break;
        case 9: dodajpokojvip(); break;
        case 10: usunpokojvip(); break;
        case 11: wyswietlopisypokoivip(); break;
        case 12: zarezerwujpokojvip(); break;
        case 13: usunrezerwacjepokojuvip(); break;
        case 14: wyswietlzajetepokojevip(); break;
        case 15: koniec(); break;
        default:
            cout << "Podałeś błędną wartość! Wpisz liczbę od 1-15" << endl;
            wyswietlinfo();
        }
    }

private:
    void wyswietldostepnepokoje() {

        ifstream test("dostepnepokoje.txt", ios::binary | ios::ate);
        if (!test || test.tellg() == 0) {
            cout << "Brak opisów do wyświetlenia" << endl;
            wyswietlinfo();
            return;
        }
        test.close();

        wifstream plik("dostepnepokoje.txt");
        plik.imbue(locale(locale::classic(), new codecvt_utf8_utf16<wchar_t>));
        wstring line;
        if (plik.is_open()) {
            while (getline(plik, line)) {
                wcout << line << endl;
            }
            plik.close();
        }
        else {
            wcout << L"Nie można otworzyć pliku!" << endl;
        }
        wyswietlinfo();
    }

    void zarezerwujjedenzpokoi() {
        cout << "dzialam2" << endl;
        wyswietlinfo();
    }
    void wyswietlzajetepokoje() {

        ifstream test("zajetepokoje.txt", ios::binary | ios::ate);
        if (!test || test.tellg() == 0) {
            cout << "Brak opisów do wyświetlenia" << endl;
            wyswietlinfo();
            return;
        }
        test.close();

        wifstream plik("zajetepokoje.txt");
        plik.imbue(locale(locale::classic(), new codecvt_utf8_utf16<wchar_t>));
        wstring line;
        if (plik.is_open()) {
            while (getline(plik, line)) {
                wcout << line << endl;
            }
            plik.close();
        }
        else {
            wcout << L"Nie można otworzyć pliku!" << endl;
        }
        wyswietlinfo();
    }
    void usunrezerwacje() {
        cout << "dzialam4" << endl;
        wyswietlinfo();
    }
    void wyswietlopisypokoi() {

        ifstream test("opisypokoi.txt", ios::binary | ios::ate);
        if (!test || test.tellg() == 0) {
            cout << "Brak opisów do wyświetlenia" << endl;
            wyswietlinfo();
            return;
        }
        test.close();

        wifstream plik("opisypokoi.txt");
        plik.imbue(locale(locale::classic(), new codecvt_utf8_utf16<wchar_t>));

        if (!plik.is_open()) {
            wcout << L"Nie można otworzyć pliku!" << endl;
            wyswietlinfo();
            return;
        }

        wstring line;
        while (getline(plik, line)) {
            wcout << line << endl;
        }

        plik.close();
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
    void wyswietlpokojevip() {
        cout << "dzialam8" << endl;
        wyswietlinfo();
    }
    void dodajpokojvip() {
        cout << "dzialam9" << endl;
        wyswietlinfo();
    }
    void usunpokojvip() {
        cout << "dzialam10" << endl;
        wyswietlinfo();
    }
    void wyswietlopisypokoivip() {
        cout << "dzialam11" << endl;
        wyswietlinfo();
    }
    void zarezerwujpokojvip() {
        cout << "dzialam12" << endl;
        wyswietlinfo();
    }
    void usunrezerwacjepokojuvip() {
        cout << "dzialam13" << endl;
        wyswietlinfo();
    }
    void wyswietlzajetepokojevip() {
        cout << "dzialam14" << endl;
        wyswietlinfo();
    }
    int koniec() {
        exit(0);
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    wcout.imbue(locale(".UTF8"));

    wcout << L"Witamy w pensjonacie! Wpisz numer jednej z podanych opcji." << endl << endl;
    Pensjonat obiekt1;
    obiekt1.wyswietlinfo();

    return 0;
}
