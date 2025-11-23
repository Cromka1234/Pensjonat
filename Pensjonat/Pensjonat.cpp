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
        } else {
            wcout << L"Nie można otworzyć pliku!" << endl;
        }
        wyswietlinfo();
    }

    void zarezerwujjedenzpokoi() {
        ifstream testPlik("dostepnepokoje.txt", ios::binary);
        if (!testPlik) {
            cout << "Brak dostępnych pokoi do rezerwacji (plik nie istnieje)." << endl;
            wyswietlinfo();
            return;
        }
        testPlik.seekg(0, ios::end);
        long long rozmiar = testPlik.tellg();
        if (rozmiar == 0) {
            testPlik.close();
            cout << "Brak dostępnych pokoi do rezerwacji (plik pusty)." << endl;
            wyswietlinfo();
            return;
        }
        testPlik.close();

        ifstream in("dostepnepokoje.txt");
        if (!in) {
            cout << "Nie można otworzyć pliku z dostępnymi pokojami." << endl;
            wyswietlinfo();
            return;
        }

        vector<string> linie;
        string tmp;
        while (getline(in, tmp)) {
            if (tmp != "") {
                linie.push_back(tmp);
            }
        }
        in.close();

        int ile = (int)linie.size();
        if (ile == 0) {
            cout << "Brak dostępnych pokoi (po wczytaniu)." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Dostępne pokoje:" << endl;
        for (int i = 0; i < ile; ++i) {
            cout << (i + 1) << ". " << linie[i] << endl;
        }

        cout << "Podaj numer pokoju, który chcesz zarezerwować: ";
        int numerPokoju = 0;
        if (!(cin >> numerPokoju)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Nieprawidłowy numer." << endl;
            wyswietlinfo();
            return;
        }

        if (numerPokoju < 1 || numerPokoju > ile) {
            cout << "Numer poza zakresem." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Na ile dni chcesz zarezerwować pokój? ";
        int iloscDni = 0;
        if (!(cin >> iloscDni)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Nieprawidłowa liczba dni." << endl;
            wyswietlinfo();
            return;
        }
        if (iloscDni <= 0) {
            cout << "Liczba dni musi być większa od zera." << endl;
            wyswietlinfo();
            return;
        }

        string wybrany = linie[numerPokoju - 1];
        vector<string> nowa;
        for (int i = 0; i < ile; ++i) {
            if (i != (numerPokoju - 1)) {
                nowa.push_back(linie[i]);
            }
        }

        ofstream out("dostepnepokoje.txt", ios::trunc);
        if (!out) {
            cout << "Błąd zapisu pliku z dostępnymi pokojami." << endl;
            wyswietlinfo();
            return;
        }
        for (int i = 0; i < (int)nowa.size(); ++i) {
            out << nowa[i] << '\n';
        }
        out.close();

        ofstream zajete("zajetepokoje.txt", ios::app);
        if (!zajete) {
            cout << "Błąd dopisania do pliku z zajętymi pokojami." << endl;
            wyswietlinfo();
            return;
        }
        zajete << wybrany << " - " << iloscDni << " dni" << '\n';
        zajete.close();

        cout << "Pokój został zarezerwowany i przeniesiony do zajętych pokoi." << endl;
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
        } else {
            wcout << L"Nie można otworzyć pliku!" << endl;
        }
        wyswietlinfo();
    }

    void usunrezerwacje() {
        ifstream testPlik("zajetepokoje.txt", ios::binary);
        if (!testPlik) {
            cout << "Brak rezerwacji do usunięcia (plik nie istnieje)." << endl;
            wyswietlinfo();
            return;
        }
        testPlik.seekg(0, ios::end);
        long long rozmiar = testPlik.tellg();
        if (rozmiar == 0) {
            testPlik.close();
            cout << "Brak rezerwacji do usunięcia (plik pusty)." << endl;
            wyswietlinfo();
            return;
        }
        testPlik.close();

        ifstream pokaz("zajetepokoje.txt");
        if (!pokaz) {
            cout << "Nie można otworzyć pliku z rezerwacjami." << endl;
            wyswietlinfo();
            return;
        }

        string linia;
        int licznik = 0;
        cout << "Zajęte pokoje:" << endl;
        while (getline(pokaz, linia)) {
            if (linia != "") {
                licznik = licznik + 1;
                cout << licznik << ". " << linia << endl;
            }
        }
        pokaz.close();

        if (licznik == 0) {
            cout << "Brak rezerwacji do wyświetlenia." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Podaj numer rezerwacji, którą chcesz usunąć: ";
        int numer = 0;
        if (!(cin >> numer)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Nieprawidłowy numer." << endl;
            wyswietlinfo();
            return;
        }
        if (numer < 1 || numer > licznik) {
            cout << "Numer poza zakresem." << endl;
            wyswietlinfo();
            return;
        }

        ifstream czytaj("zajetepokoje.txt");
        if (!czytaj) {
            cout << "Nie można ponownie otworzyć pliku z rezerwacjami." << endl;
            wyswietlinfo();
            return;
        }

        string wynik = "";
        string usuwana = "";
        int obecny = 0;
        while (getline(czytaj, linia)) {
            if (linia == "") {
                continue;
            }
            obecny = obecny + 1;
            if (obecny == numer) {
                usuwana = linia; 
            } else {
                wynik += linia;
                wynik += '\n';
            }
        }
        czytaj.close();

        ofstream zapisz("zajetepokoje.txt", ios::trunc);
        if (!zapisz) {
            cout << "Błąd zapisu pliku z rezerwacjami." << endl;
            wyswietlinfo();
            return;
        }
        zapisz << wynik;
        zapisz.close();

        string nazwa = "";
        int dl = (int)usuwana.length();
        int i = 0;
        while (i < dl) {
            if (i + 2 < dl && usuwana[i] == ' ' && usuwana[i + 1] == '-' && usuwana[i + 2] == ' ') {
                break;
            }
            nazwa += usuwana[i];
            i = i + 1;
        }
        if (nazwa == "") {
            nazwa = usuwana;
        }

        ofstream dost("dostepnepokoje.txt", ios::app);
        if (!dost) {
            cout << "Błąd dopisania do pliku z dostępnymi pokojami." << endl;
            wyswietlinfo();
            return;
        }
        dost << nazwa << '\n';
        dost.close();

        cout << "Rezerwacja usunięta. Pokój przywrócono do dostępnych." << endl;
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

        ifstream test("dostepnepokojevip.txt", ios::binary | ios::ate);
        if (!test || test.tellg() == 0) {
            cout << "Brak dostępnych pokoi VIP do wyświetlenia" << endl;
            wyswietlinfo();
            return;
        }
        test.close();

        wifstream plik("dostepnepokojevip.txt");
        plik.imbue(locale(locale::classic(), new codecvt_utf8_utf16<wchar_t>));

        wstring line;
        if (plik.is_open()) {
            while (getline(plik, line)) {
                wcout << line << endl;
            }
            plik.close();
        } else {
            wcout << L"Nie można otworzyć pliku VIP!" << endl;
        }

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

        ifstream test("opisypokoivip.txt", ios::binary | ios::ate);
        if (!test || test.tellg() == 0) {
            cout << "Brak opisów pokoi VIP" << endl;
            wyswietlinfo();
            return;
        }
        test.close();

        wifstream plik("opisypokoivip.txt");
        plik.imbue(locale(locale::classic(), new codecvt_utf8_utf16<wchar_t>));

        if (!plik.is_open()) {
            wcout << L"Nie można otworzyć pliku opisów VIP!" << endl;
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

    void zarezerwujpokojvip() {
        cout << "dzialam12" << endl;
        wyswietlinfo();
    }

    void usunrezerwacjepokojuvip() {
        cout << "dzialam13" << endl;
        wyswietlinfo();
    }

    void wyswietlzajetepokojevip() {

        ifstream test("zajetepokojevip.txt", ios::binary | ios::ate);
        if (!test || test.tellg() == 0) {
            cout << "Brak zajętych pokoi VIP" << endl;
            wyswietlinfo();
            return;
        }
        test.close();

        wifstream plik("zajetepokojevip.txt");
        plik.imbue(locale(locale::classic(), new codecvt_utf8_utf16<wchar_t>));

        wstring line;
        if (plik.is_open()) {
            while (getline(plik, line)) {
                wcout << line << endl;
            }
            plik.close();
        } else {
            wcout << L"Nie można otworzyć pliku zajętych VIP!" << endl;
        }

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
