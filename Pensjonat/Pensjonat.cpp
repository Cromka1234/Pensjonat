#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <windows.h>
#include <locale>
#include <codecvt>
#include <vector>
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
        cin.clear();
        cin.ignore(10000, '\n'); 

        int maxnum = 0;
        ifstream fin("dostepnepokoje.txt");
        if (fin.is_open()) {
            string linia;
            while (getline(fin, linia)) {
                if (linia == "") continue;
                int j = 0;
                int len = (int)linia.length();
                // znajdź pierwszą cyfrę
                while (j < len && !(linia[j] >= '0' && linia[j] <= '9')) j++;
                int start = j;
                while (j < len && (linia[j] >= '0' && linia[j] <= '9')) j++;
                if (start < j) {
                    string numstr = linia.substr(start, j - start);
                    int num = 0;
                    try {
                        num = stoi(numstr);
                    } catch (...) {
                        num = 0;
                    }
                    if (num > maxnum) maxnum = num;
                }
            }
            fin.close();
        }

        int nowyNr = maxnum + 1;

        cout << "Podaj nazwę pokoju: ";
        string nazwa;
        getline(cin, nazwa);
        if (nazwa == "") {
            cout << "Nie podano nazwy. Anulowano dodawanie." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Podaj cenę (liczba, bez PLN): ";
        string cena;
        getline(cin, cena);
        if (cena == "") {
            cout << "Nie podano ceny. Anulowano dodawanie." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Podaj opis pokoju. Zakończ wpis linią zawierającą tylko kropkę '.'" << endl;
        string opisLinia;
        vector<string> opisWiersze;
        while (true) {
            if (!getline(cin, opisLinia)) break;
            if (opisLinia == ".") break;
            opisWiersze.push_back(opisLinia);
        }
        if ((int)opisWiersze.size() == 0) {
            cout << "Nie podano opisu. Anulowano dodawanie." << endl;
            wyswietlinfo();
            return;
        }

        ofstream out("dostepnepokoje.txt", ios::app);
        if (!out) {
            cout << "Błąd otwarcia pliku dostepnepokoje.txt" << endl;
            wyswietlinfo();
            return;
        }
        out << nowyNr << ". " << nazwa << " - " << cena << " PLN" << '\n';
        out.close();

        bool opisPusty = true;
        ifstream testopis("opisypokoi.txt", ios::binary | ios::ate);
        if (testopis) {
            if (testopis.tellg() > 0) opisPusty = false;
            testopis.close();
        }
        ofstream outOpis("opisypokoi.txt", ios::app);
        if (!outOpis) {
            cout << "Błąd otwarcia pliku opisypokoi.txt" << endl;
            wyswietlinfo();
            return;
        }
        if (!opisPusty) outOpis << '\n';
        outOpis << nowyNr << ". " << opisWiersze[0] << '\n';
        int idx = 1;
        int total = (int)opisWiersze.size();
        while (idx < total) {
            outOpis << opisWiersze[idx] << '\n';
            idx = idx + 1;
        }
        outOpis << '\n';
        outOpis.close();

        cout << "Dodano pokój nr " << nowyNr << " wraz z opisem." << endl;
        wyswietlinfo();
    }

    void usuwaniepkoju() {
        vector<string> dost;
        string linia;
        ifstream fin("dostepnepokoje.txt");
        if (fin.is_open()) {
            while (getline(fin, linia)) {
                if (linia != "") dost.push_back(linia);
            }
            fin.close();
        }
        cout << "Dostępne pokoje:" << endl;
        int i = 0;
        int ileDost = (int)dost.size();
        while (i < ileDost) {
            cout << (i + 1) << ". " << dost[i] << endl;
            i = i + 1;
        }

        vector<string> zaj;
        ifstream fin2("zajetepokoje.txt");
        if (fin2.is_open()) {
            while (getline(fin2, linia)) {
                if (linia != "") zaj.push_back(linia);
            }
            fin2.close();
        }
        cout << "Zajęte pokoje:" << endl;
        i = 0;
        int ileZaj = (int)zaj.size();
        while (i < ileZaj) {
            cout << (i + 1) << ". " << zaj[i] << endl;
            i = i + 1;
        }

        if (ileDost == 0 && ileZaj == 0) {
            cout << "Brak pokoi do usunięcia." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Usuń z (d)ostępne czy (z)ajęte? ";
        char wybor = ' ';
        cin >> wybor;
        cout << endl;
        if (!(wybor == 'd' || wybor == 'D' || wybor == 'z' || wybor == 'Z')) {
            cout << "Nieprawidłowy wybór." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Podaj numer pokoju do usunięcia: ";
        int numer = 0;
        if (!(cin >> numer)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Nieprawidłowy numer." << endl;
            wyswietlinfo();
            return;
        }

        string usunietaLinia = "";
        if (wybor == 'd' || wybor == 'D') {
            if (numer < 1 || numer > ileDost) {
                cout << "Numer poza zakresem listy dostępnych." << endl;
                wyswietlinfo();
                return;
            }
            int idx = 0;
            while (idx < ileDost) {
                if (idx == (numer - 1)) {
                    usunietaLinia = dost[idx];
                }
                idx = idx + 1;
            }
            ofstream out("dostepnepokoje.txt", ios::trunc);
            if (!out) {
                cout << "Błąd zapisu pliku dostepnepokoje.txt" << endl;
                wyswietlinfo();
                return;
            }
            idx = 0;
            while (idx < ileDost) {
                if (idx != (numer - 1)) {
                    out << dost[idx] << '\n';
                }
                idx = idx + 1;
            }
            out.close();
        } else {
            if (numer < 1 || numer > ileZaj) {
                cout << "Numer poza zakresem listy zajętych." << endl;
                wyswietlinfo();
                return;
            }
            int idx = 0;
            while (idx < ileZaj) {
                if (idx == (numer - 1)) {
                    usunietaLinia = zaj[idx];
                }
                idx = idx + 1;
            }
            ofstream out("zajetepokoje.txt", ios::trunc);
            if (!out) {
                cout << "Błąd zapisu pliku zajetepokoje.txt" << endl;
                wyswietlinfo();
                return;
            }
            idx = 0;
            while (idx < ileZaj) {
                if (idx != (numer - 1)) {
                    out << zaj[idx] << '\n';
                }
                idx = idx + 1;
            }
            out.close();
        }

        string numstr = "";
        int j = 0;
        int dllen = (int)usunietaLinia.length();
        while (j < dllen && !(usunietaLinia[j] >= '0' && usunietaLinia[j] <= '9')) j++;
        int start = j;
        while (j < dllen && (usunietaLinia[j] >= '0' && usunietaLinia[j] <= '9')) j++;
        if (start < j) {
            numstr = usunietaLinia.substr(start, j - start);
        }

        if (numstr == "") {
            cout << "Nie udało się odnaleźć numeru pokoju do usunięcia opisu." << endl;
            wyswietlinfo();
            return;
        }

        vector<string> all;
        ifstream finOpis("opisypokoi.txt");
        if (finOpis.is_open()) {
            while (getline(finOpis, linia)) {
                all.push_back(linia);
            }
            finOpis.close();
        }

        int total = (int)all.size();
        int startLine = -1;
        int p = 0;
        while (p < total) {
            string l = all[p];
            int k = 0;
            int llen = (int)l.length();
            while (k < llen && l[k] == ' ') k++;
            int needLen = (int)numstr.length();
            if (k + needLen < llen) {
                bool match = true;
                int t = 0;
                while (t < needLen) {
                    if (k + t >= llen || l[k + t] != numstr[t]) { match = false; break; }
                    t = t + 1;
                }
                if (match && k + needLen < llen && l[k + needLen] == '.') {
                    startLine = p;
                    break;
                }
            }
            p = p + 1;
        }

        if (startLine != -1) {
            int q = startLine;
            while (q < total) {
                if (all[q] == "") {
                    break;
                }
                q = q + 1;
            }
            vector<string> nowy;
            int r = 0;
            while (r < startLine) {
                nowy.push_back(all[r]);
                r = r + 1;
            }
            if (q < total) {
                r = q + 1;
            } else {
                r = q;
            }
            while (r < total) {
                nowy.push_back(all[r]);
                r = r + 1;
            }
            ofstream outOpis("opisypokoi.txt", ios::trunc);
            if (outOpis.is_open()) {
                int s = 0;
                int nTotal = (int)nowy.size();
                while (s < nTotal) {
                    outOpis << nowy[s] << '\n';
                    s = s + 1;
                }
                outOpis.close();
            } else {
                cout << "Błąd zapisu pliku opisypokoi.txt" << endl;
                wyswietlinfo();
                return;
            }
        } else {
            cout << "Nie znaleziono opisu pokoju o numerze " << numstr << " w pliku opisypokoi.txt" << endl;
        }

        cout << "Usunięto pokój i (jeśli znaleziono) jego opis. Numer: " << numstr << endl;
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
