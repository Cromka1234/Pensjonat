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
        }
        else {
            wcout << L"Nie można otworzyć pliku!" << endl;
        }
        wyswietlinfo();
    }

    void zarezerwujjedenzpokoi() {
        ifstream plik_testowy("dostepnepokoje.txt", ios::binary);
        if (!plik_testowy) {
            cout << "Brak dostępnych pokoi do rezerwacji (plik nie istnieje)." << endl;
            wyswietlinfo();
            return;
        }
        plik_testowy.seekg(0, ios::end);
        long long rozmiar_pliku = plik_testowy.tellg();
        if (rozmiar_pliku == 0) {
            plik_testowy.close();
            cout << "Brak dostępnych pokoi do rezerwacji (plik pusty)." << endl;
            wyswietlinfo();
            return;
        }
        plik_testowy.close();

        ifstream plik_wejsciowy("dostepnepokoje.txt");
        if (!plik_wejsciowy) {
            cout << "Nie można otworzyć pliku z dostępnymi pokojami." << endl;
            wyswietlinfo();
            return;
        }

        vector<string> lista_pokoi;
        string linia;
        while (getline(plik_wejsciowy, linia)) {
            if (linia != "") {
                lista_pokoi.push_back(linia);
            }
        }
        plik_wejsciowy.close();

        int liczba_pokoi = (int)lista_pokoi.size();
        if (liczba_pokoi == 0) {
            cout << "Brak dostępnych pokoi (po wczytaniu)." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Dostępne pokoje:" << endl;
        for (int i = 0; i < liczba_pokoi; ++i) {
            cout << (i + 1) << ". " << lista_pokoi[i] << endl;
        }

        cout << "Podaj numer pokoju, który chcesz zarezerwować: ";
        int numer_pokoju = 0;
        if (!(cin >> numer_pokoju)) {
            cin.clear();
            cin.ignore(10000, '\n'); 
            cout << "Nieprawidłowy numer." << endl;
            wyswietlinfo();
            return;
        }

        if (numer_pokoju < 1 || numer_pokoju > liczba_pokoi) {
            cout << "Numer poza zakresem." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Na ile dni chcesz zarezerwować pokój? ";
        int liczba_dni = 0;
        if (!(cin >> liczba_dni)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Nieprawidłowa liczba dni." << endl;
            wyswietlinfo();
            return;
        }
        if (liczba_dni <= 0) {
            cout << "Liczba dni musi być większa od zera." << endl;
            wyswietlinfo();
            return;
        }

        string wybrany_pokoj = lista_pokoi[numer_pokoju - 1];
        vector<string> nowe_pokoje;
        for (int i = 0; i < liczba_pokoi; ++i) {
            if (i != (numer_pokoju - 1)) {
                nowe_pokoje.push_back(lista_pokoi[i]);
            }
        }

        ofstream plik_wyjsciowy("dostepnepokoje.txt", ios::trunc);
        if (!plik_wyjsciowy) {
            cout << "Błąd zapisu pliku z dostępnymi pokojami." << endl;
            wyswietlinfo();
            return;
        }
        for (int i = 0; i < (int)nowe_pokoje.size(); ++i) {
            plik_wyjsciowy << nowe_pokoje[i] << '\n';
        }
        plik_wyjsciowy.close();

        ofstream plik_zajete("zajetepokoje.txt", ios::app);
        if (!plik_zajete) {
            cout << "Błąd dopisania do pliku z zajętymi pokojami." << endl;
            wyswietlinfo();
            return;
        }
        plik_zajete << wybrany_pokoj << " - " << liczba_dni << " dni" << '\n';
        plik_zajete.close();

        cout << "Pokój został zarezerwowany i przeniesiony do zajętych pokoi." << endl;
        wyswietlinfo();
    }


    void wyswietlzajetepokoje() {
        ifstream test("zajetepokoje.txt", ios::binary | ios::ate);
        if (!test || test.tellg() == 0) {
            cout << "Brak pokojów do wyświetlenia" << endl;
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
        ifstream plik_testowy("zajetepokoje.txt", ios::binary);
        if (!plik_testowy) {
            cout << "Brak rezerwacji do usunięcia (plik nie istnieje)." << endl;
            wyswietlinfo();
            return;
        }
        plik_testowy.seekg(0, ios::end);
        long long rozmiar_pliku = plik_testowy.tellg();
        if (rozmiar_pliku == 0) {
            plik_testowy.close();
            cout << "Brak rezerwacji do usunięcia (plik pusty)." << endl;
            wyswietlinfo();
            return;
        }
        plik_testowy.close();

        ifstream plik_wyswietl("zajetepokoje.txt");
        if (!plik_wyswietl) {
            cout << "Nie można otworzyć pliku z rezerwacjami." << endl;
            wyswietlinfo();
            return;
        }

        string linia;
        int licznik_rezerwacji = 0;
        cout << "Zajęte pokoje:" << endl;
        while (getline(plik_wyswietl, linia)) {
            if (linia != "") {
                licznik_rezerwacji++;
                cout << licznik_rezerwacji << ". " << linia << endl;
            }
        }
        plik_wyswietl.close();

        if (licznik_rezerwacji == 0) {
            cout << "Brak rezerwacji do wyświetlenia." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Podaj numer rezerwacji, którą chcesz usunąć: ";
        int numer_rezerwacji = 0;
        if (!(cin >> numer_rezerwacji)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Nieprawidłowy numer." << endl;
            wyswietlinfo();
            return;
        }
        if (numer_rezerwacji < 1 || numer_rezerwacji > licznik_rezerwacji) {
            cout << "Numer poza zakresem." << endl;
            wyswietlinfo();
            return;
        }

        ifstream plik_czytaj("zajetepokoje.txt");
        if (!plik_czytaj) {
            cout << "Nie można ponownie otworzyć pliku z rezerwacjami." << endl;
            wyswietlinfo();
            return;
        }

        string zawartosc_pliku = "";
        string rezerwacja_do_usuniecia = "";
        int obecny_numer = 0;
        while (getline(plik_czytaj, linia)) {
            if (linia == "") {
                continue;
            }
            obecny_numer++;
            if (obecny_numer == numer_rezerwacji) {
                rezerwacja_do_usuniecia = linia;
            }
            else {
                zawartosc_pliku += linia + '\n';
            }
        }
        plik_czytaj.close();

        ofstream plik_zapisz("zajetepokoje.txt", ios::trunc);
        if (!plik_zapisz) {
            cout << "Błąd zapisu pliku z rezerwacjami." << endl;
            wyswietlinfo();
            return;
        }
        plik_zapisz << zawartosc_pliku;
        plik_zapisz.close();

        string nazwa_pokoju = "";
        int dlugosc = (int)rezerwacja_do_usuniecia.length();
        int i = 0;
        while (i < dlugosc) {
            if (i + 2 < dlugosc && rezerwacja_do_usuniecia[i] == ' ' &&
                rezerwacja_do_usuniecia[i + 1] == '-' && rezerwacja_do_usuniecia[i + 2] == ' ') {
                break;
            }
            nazwa_pokoju += rezerwacja_do_usuniecia[i];
            i++;
        }
        if (nazwa_pokoju == "") {
            nazwa_pokoju = rezerwacja_do_usuniecia;
        }

        ofstream plik_dostepne("dostepnepokoje.txt", ios::app);
        if (!plik_dostepne) {
            cout << "Błąd dopisania do pliku z dostępnymi pokojami." << endl;
            wyswietlinfo();
            return;
        }
        plik_dostepne << nazwa_pokoju << '\n';
        plik_dostepne.close();

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

        int maksymalny_numer = 0;
        ifstream plik_dostepne("dostepnepokoje.txt");
        if (plik_dostepne.is_open()) {
            string linia;
            while (getline(plik_dostepne, linia)) {
                if (linia == "") continue;
                int indeks = 0;
                int dlugosc = (int)linia.length();
                while (indeks < dlugosc && !(linia[indeks] >= '0' && linia[indeks] <= '9')) indeks++;
                int start = indeks;
                while (indeks < dlugosc && (linia[indeks] >= '0' && linia[indeks] <= '9')) indeks++;
                if (start < indeks) {
                    string numerStr = linia.substr(start, indeks - start);
                    int numer = 0;
                    try {
                        numer = stoi(numerStr);
                    }
                    catch (...) {
                        numer = 0;
                    }
                    if (numer > maksymalny_numer) maksymalny_numer = numer;
                }
            }
            plik_dostepne.close();
        }

        int nowy_numer = maksymalny_numer + 1;

        cout << "Podaj nazwę pokoju: ";
        string nazwa_pokoju;
        getline(cin, nazwa_pokoju);
        if (nazwa_pokoju == "") {
            cout << "Nie podano nazwy. Anulowano dodawanie." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Podaj cenę (liczba, bez PLN): ";
        string cena_pokoju;
        getline(cin, cena_pokoju);
        if (cena_pokoju == "") {
            cout << "Nie podano ceny. Anulowano dodawanie." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Podaj opis pokoju. Zakończ wpis linią zawierającą tylko kropkę '.'" << endl;
        string linia_opisu;
        vector<string> opis_pokoju;
        while (true) {
            if (!getline(cin, linia_opisu)) break;
            if (linia_opisu == ".") break;
            opis_pokoju.push_back(linia_opisu);
        }
        if ((int)opis_pokoju.size() == 0) {
            cout << "Nie podano opisu. Anulowano dodawanie." << endl;
            wyswietlinfo();
            return;
        }

        ofstream plik_dopisz("dostepnepokoje.txt", ios::app);
        if (!plik_dopisz) {
            cout << "Błąd otwarcia pliku dostepnepokoje.txt" << endl;
            wyswietlinfo();
            return;
        }
        plik_dopisz << nowy_numer << ". " << nazwa_pokoju << " - " << cena_pokoju << " PLN" << '\n';
        plik_dopisz.close();

        bool plik_opis_pusty = true;
        ifstream test_opis("opisypokoi.txt", ios::binary | ios::ate);
        if (test_opis) {
            if (test_opis.tellg() > 0) plik_opis_pusty = false;
            test_opis.close();
        }
        ofstream plik_opis("opisypokoi.txt", ios::app);
        if (!plik_opis) {
            cout << "Błąd otwarcia pliku opisypokoi.txt" << endl;
            wyswietlinfo();
            return;
        }
        if (!plik_opis_pusty) plik_opis << '\n';
        plik_opis << nowy_numer << ". " << opis_pokoju[0] << '\n';
        int indeks = 1;
        int calkowita_liczba_wierszy = (int)opis_pokoju.size();
        while (indeks < calkowita_liczba_wierszy) {
            plik_opis << opis_pokoju[indeks] << '\n';
            indeks++;
        }
        plik_opis << '\n';
        plik_opis.close();

        cout << "Dodano pokój nr " << nowy_numer << " wraz z opisem." << endl;
        wyswietlinfo();
    }

    void usuwaniepkoju() {
        vector<string> lista_dostepnych;
        string linia;
        ifstream plik_dostepne("dostepnepokoje.txt");
        if (plik_dostepne.is_open()) {
            while (getline(plik_dostepne, linia)) {
                if (linia != "") lista_dostepnych.push_back(linia);
            }
            plik_dostepne.close();
        }

        cout << "Dostępne pokoje:" << endl;
        int i = 0;
        int liczba_dostepnych = (int)lista_dostepnych.size();
        while (i < liczba_dostepnych) {
            cout << (i + 1) << ". " << lista_dostepnych[i] << endl;
            i++;
        }

        vector<string> lista_zajetych;
        ifstream plik_zajete("zajetepokoje.txt");
        if (plik_zajete.is_open()) {
            while (getline(plik_zajete, linia)) {
                if (linia != "") lista_zajetych.push_back(linia);
            }
            plik_zajete.close();
        }

        cout << "Zajęte pokoje:" << endl;
        i = 0;
        int liczba_zajetych = (int)lista_zajetych.size();
        while (i < liczba_zajetych) {
            cout << (i + 1) << ". " << lista_zajetych[i] << endl;
            i++;
        }

        if (liczba_dostepnych == 0 && liczba_zajetych == 0) {
            cout << "Brak pokoi do usunięcia." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Usuń z dostępne(d) czy zajęte(z)? ";
        char wybor = ' ';
        cin >> wybor;
        cout << endl;
        if (!(wybor == 'd' || wybor == 'D' || wybor == 'z' || wybor == 'Z')) {
            cout << "Nieprawidłowy wybór." << endl;
            wyswietlinfo();
            return;
        }

        cout << "Podaj numer pokoju do usunięcia: ";
        int numer_pokoju = 0;
        if (!(cin >> numer_pokoju)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Nieprawidłowy numer." << endl;
            wyswietlinfo();
            return;
        }

        string usunieta_linia = "";
        if (wybor == 'd' || wybor == 'D') {
            if (numer_pokoju < 1 || numer_pokoju > liczba_dostepnych) {
                cout << "Numer poza zakresem listy dostępnych." << endl;
                wyswietlinfo();
                return;
            }
            for (int idx = 0; idx < liczba_dostepnych; idx++) {
                if (idx == (numer_pokoju - 1)) usunieta_linia = lista_dostepnych[idx];
            }
            ofstream out("dostepnepokoje.txt", ios::trunc);
            if (!out) {
                cout << "Błąd zapisu pliku dostepnepokoje.txt" << endl;
                wyswietlinfo();
                return;
            }
            for (int idx = 0; idx < liczba_dostepnych; idx++) {
                if (idx != (numer_pokoju - 1)) out << lista_dostepnych[idx] << '\n';
            }
            out.close();
        }
        else {
            if (numer_pokoju < 1 || numer_pokoju > liczba_zajetych) {
                cout << "Numer poza zakresem listy zajętych." << endl;
                wyswietlinfo();
                return;
            }
            for (int idx = 0; idx < liczba_zajetych; idx++) {
                if (idx == (numer_pokoju - 1)) usunieta_linia = lista_zajetych[idx];
            }
            ofstream out("zajetepokoje.txt", ios::trunc);
            if (!out) {
                cout << "Błąd zapisu pliku zajetepokoje.txt" << endl;
                wyswietlinfo();
                return;
            }
            for (int idx = 0; idx < liczba_zajetych; idx++) {
                if (idx != (numer_pokoju - 1)) out << lista_zajetych[idx] << '\n';
            }
            out.close();
        }

        string numer_str = "";
        int j = 0;
        int dlugosc_linii = (int)usunieta_linia.length();
        while (j < dlugosc_linii && !(usunieta_linia[j] >= '0' && usunieta_linia[j] <= '9')) j++;
        int start = j;
        while (j < dlugosc_linii && (usunieta_linia[j] >= '0' && usunieta_linia[j] <= '9')) j++;
        if (start < j) numer_str = usunieta_linia.substr(start, j - start);

        if (numer_str == "") {
            cout << "Nie udało się odnaleźć numeru pokoju do usunięcia opisu." << endl;
            wyswietlinfo();
            return;
        }

        vector<string> wszystkie_opisy;
        ifstream plik_opisy("opisypokoi.txt");
        if (plik_opisy.is_open()) {
            while (getline(plik_opisy, linia)) wszystkie_opisy.push_back(linia);
            plik_opisy.close();
        }

        int total = (int)wszystkie_opisy.size();
        int startLinia = -1;
        for (int p = 0; p < total; p++) {
            string lin = wszystkie_opisy[p];
            int k = 0;
            int len_lin = (int)lin.length();
            while (k < len_lin && lin[k] == ' ') k++;
            int needLen = (int)numer_str.length();
            if (k + needLen < len_lin) {
                bool match = true;
                for (int t = 0; t < needLen; t++) {
                    if (k + t >= len_lin || lin[k + t] != numer_str[t]) { match = false; break; }
                }
                if (match && k + needLen < len_lin && lin[k + needLen] == '.') {
                    startLinia = p;
                    break;
                }
            }
        }

        if (startLinia != -1) {
            int q = startLinia;
            while (q < total && wszystkie_opisy[q] != "") q++;
            vector<string> nowa_lista;
            for (int r = 0; r < startLinia; r++) nowa_lista.push_back(wszystkie_opisy[r]);
            if (q < total) for (int r = q + 1; r < total; r++) nowa_lista.push_back(wszystkie_opisy[r]);
            ofstream outOpis("opisypokoi.txt", ios::trunc);
            if (outOpis.is_open()) {
                for (int s = 0; s < (int)nowa_lista.size(); s++) outOpis << nowa_lista[s] << '\n';
                outOpis.close();
            }
            else {
                cout << "Błąd zapisu pliku opisypokoi.txt" << endl;
                wyswietlinfo();
                return;
            }
        }
        else {
            cout << "Nie znaleziono opisu pokoju o numerze " << numer_str << " w pliku opisypokoi.txt" << endl;
        }

        cout << "Usunięto pokój i (jeśli znaleziono) jego opis. Numer: " << numer_str << endl;
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
        }
        else {
            wcout << L"Nie można otworzyć pliku VIP!" << endl;
        }

        wyswietlinfo();
    }

    void dodajpokojvip() {
        cin.clear();
        cin.ignore(10000, '\n');

        int maxnum = 0;
        ifstream fin("dostepnepokojevip.txt");
        string linia;
        while (getline(fin, linia)) {
            if (linia == "") continue;
            int j = 0, len = (int)linia.length();
            while (j < len && !(linia[j] >= '0' && linia[j] <= '9')) j++;
            int start = j;
            while (j < len && (linia[j] >= '0' && linia[j] <= '9')) j++;
            if (start < j) {
                int num = 0;
                try { num = stoi(linia.substr(start, j - start)); }
                catch (...) { num = 0; }
                if (num > maxnum) maxnum = num;
            }
        }
        fin.close();
        int nowyNr = maxnum + 1;

        cout << "Podaj nazwę pokoju VIP: ";
        string nazwa; getline(cin, nazwa);
        if (nazwa == "") { cout << "Nie podano nazwy. Anulowano."; wyswietlinfo(); return; }

        cout << "Podaj cenę VIP (liczba, bez PLN): ";
        string cena; getline(cin, cena);
        if (cena == "") { cout << "Nie podano ceny. Anulowano."; wyswietlinfo(); return; }

        cout << "Podaj opis pokoju VIP. Zakończ wpis linią zawierającą tylko kropkę '.'" << endl;
        string opisLinia; vector<string> opisWiersze;
        while (true) {
            if (!getline(cin, opisLinia)) break;
            if (opisLinia == ".") break;
            opisWiersze.push_back(opisLinia);
        }
        if (opisWiersze.empty()) { cout << "Nie podano opisu. Anulowano."; wyswietlinfo(); return; }

        ofstream out("dostepnepokojevip.txt", ios::app);
        out << nowyNr << ". " << nazwa << " - " << cena << " PLN" << endl;
        out.close();

        bool opisPusty = true;
        ifstream testopis("opispokoivip.txt", ios::binary | ios::ate);
        if (testopis) { if (testopis.tellg() > 0) opisPusty = false; testopis.close(); }

        ofstream outOpis("opispokoivip.txt", ios::app);
        if (!opisPusty) outOpis << '\n';
        outOpis << nowyNr << ". " << opisWiersze[0] << '\n';
        for (int idx = 1; idx < (int)opisWiersze.size(); idx++) outOpis << opisWiersze[idx] << '\n';
        outOpis << '\n';
        outOpis.close();

        cout << "Dodano pokój VIP nr " << nowyNr << " wraz z opisem." << endl;
        wyswietlinfo();
    }

    void usunpokojvip() {
        cout << "dzialam10" << endl;
        wyswietlinfo();
    }

    void wyswietlopisypokoivip() {

        ifstream test("opispokoivip.txt", ios::binary | ios::ate);
        if (!test || test.tellg() == 0) {
            cout << "Brak opisów pokoi VIP" << endl;
            wyswietlinfo();
            return;
        }
        test.close();

        wifstream plik("opispokoivip.txt");
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
        ifstream testPlik("dostepnepokojevip.txt", ios::binary);
        if (!testPlik) {
            cout << "Brak dostępnych pokoi VIP do rezerwacji (plik nie istnieje)." << endl;
            wyswietlinfo();
            return;
        }
        testPlik.seekg(0, ios::end);
        long long rozmiar = testPlik.tellg();
        if (rozmiar == 0) {
            testPlik.close();
            cout << "Brak dostępnych pokoi VIP do rezerwacji (plik pusty)." << endl;
            wyswietlinfo();
            return;
        }
        testPlik.close();

        ifstream in("dostepnepokojevip.txt");
        vector<string> linie;
        string tmp;
        while (getline(in, tmp)) if (tmp != "") linie.push_back(tmp);
        in.close();

        if (linie.empty()) { cout << "Brak dostępnych pokoi VIP." << endl; wyswietlinfo(); return; }

        cout << "Dostępne pokoje VIP:" << endl;
        for (int i = 0; i < linie.size(); i++) cout << i + 1 << ". " << linie[i] << endl;

        cout << "Podaj numer pokoju VIP do rezerwacji: ";
        int numerPokoju; cin >> numerPokoju;
        if (numerPokoju<1 || numerPokoju>(int)linie.size()) { cout << "Błędny numer!" << endl; wyswietlinfo(); return; }

        cout << "Na ile dni chcesz zarezerwować pokój VIP? ";
        int iloscDni; cin >> iloscDni;
        if (iloscDni <= 0) { cout << "Liczba dni musi być >0"; wyswietlinfo(); return; }

        string wybrany = linie[numerPokoju - 1];
        vector<string> nowa;
        for (int i = 0; i < linie.size(); i++) if (i != (numerPokoju - 1)) nowa.push_back(linie[i]);

        ofstream out("dostepnepokojevip.txt", ios::trunc);
        for (auto& s : nowa) out << s << endl;
        out.close();

        ofstream zajete("zajetepokojevip.txt", ios::app);
        zajete << wybrany << " - " << iloscDni << " dni" << endl;
        zajete.close();

        cout << "Pokój VIP został zarezerwowany i przeniesiony do zajętych." << endl;
        wyswietlinfo();
    }


    void usunrezerwacjepokojuvip() {
        ifstream testPlik("zajetepokojevip.txt");
        if (!testPlik || testPlik.peek() == ifstream::traits_type::eof()) { cout << "Brak rezerwacji VIP"; wyswietlinfo(); return; }
        testPlik.close();

        ifstream pokaz("zajetepokojevip.txt");
        vector<string> linie;
        string tmp;
        while (getline(pokaz, tmp)) if (tmp != "") linie.push_back(tmp);
        pokaz.close();

        cout << "Zajęte pokoje VIP:" << endl;
        for (int i = 0; i < linie.size(); i++) cout << i + 1 << ". " << linie[i] << endl;

        cout << "Podaj numer rezerwacji VIP do usunięcia: ";
        int numer; cin >> numer;
        if (numer<1 || numer>(int)linie.size()) { cout << "Błędny numer!"; wyswietlinfo(); return; }

        string usuwana = linie[numer - 1];
        linie.erase(linie.begin() + numer - 1);

        ofstream out("zajetepokojevip.txt", ios::trunc);
        for (auto& s : linie) out << s << endl;
        out.close();


        string nazwa = "";
        int i = 0;
        while (i < (int)usuwana.length()) {
            if (i + 2 < (int)usuwana.length() && usuwana[i] == ' ' && usuwana[i + 1] == '-' && usuwana[i + 2] == ' ') break;
            nazwa += usuwana[i]; i++;
        }
        if (nazwa == "") nazwa = usuwana;

        ofstream dost("dostepnepokojevip.txt", ios::app);
        dost << nazwa << endl;
        dost.close();

        cout << "Usunięto rezerwację pokoju VIP i przywrócono go do dostępnych." << endl;
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
        }
        else {
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
