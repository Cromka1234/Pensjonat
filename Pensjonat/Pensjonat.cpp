#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

void wyswietlinfo();

void wyswietldostepnepokoje() {
    ifstream plik("dostepnepokoje.txt");
    if (!plik.is_open()) {
        cout << "Brak pliku z dostepnymi pokojami." << endl;
        wyswietlinfo();
        return;
    }
    string linia;
    cout << "Dostepne pokoje:" << endl;
    while (getline(plik, linia)) {
        if (linia != "") cout << linia << endl;
    }
    plik.close();
    cout << endl;
    wyswietlinfo();
}

void zarezerwujjedenzpokoi() {
    ifstream plik("dostepnepokoje.txt");
    if (!plik.is_open()) {
        cout << "Brak dostepnych pokoi do rezerwacji." << endl;
        wyswietlinfo();
        return;
    }

    vector<string> pokoje;
    string linia;

    while (getline(plik, linia)) {
        if (linia != "") pokoje.push_back(linia);
    }
    plik.close();

    if (pokoje.size() == 0) {
        cout << "Brak wolnych pokoi." << endl;
        wyswietlinfo();
        return;
    }

    cout << "Dostepne pokoje:" << endl;
    for (int i = 0; i < pokoje.size(); i++) {
        cout << i + 1 << ". " << pokoje[i] << endl;
    }

    cout << "Wybierz numer pokoju: ";
    int wybor;
    cin >> wybor;

    if (wybor < 1 || wybor > pokoje.size()) {
        cout << "Niepoprawny numer." << endl;
        wyswietlinfo();
        return;
    }

    cout << "Na ile dni rezerwacja? ";
    int dni;
    cin >> dni;

    string wybrany = pokoje[wybor - 1];

    ofstream zaj("zajetepokoje.txt", ios::app);
    zaj << wybrany << " - " << dni << " dni" << endl;
    zaj.close();

    ofstream dost("dostepnepokoje.txt", ios::trunc);
    for (int i = 0; i < pokoje.size(); i++) {
        if (i != wybor - 1) dost << pokoje[i] << endl;
    }
    dost.close();

    cout << "Zarezerwowano pokoj." << endl;
    wyswietlinfo();
}

void wyswietlzajetepokoje() {
    ifstream plik("zajetepokoje.txt");
    if (!plik.is_open()) {
        cout << "Brak pliku z zajetymi pokojami." << endl;
        wyswietlinfo();
        return;
    }
    cout << "Zajete pokoje:" << endl;
    string linia;
    while (getline(plik, linia)) {
        if (linia != "") cout << linia << endl;
    }
    plik.close();
    cout << endl;
    wyswietlinfo();
}

void usunrezerwacje() {
    ifstream plik("zajetepokoje.txt");
    if (!plik.is_open()) {
        cout << "Brak zajetych pokoi." << endl;
        wyswietlinfo();
        return;
    }

    vector<string> zajete;
    string linia;

    while (getline(plik, linia)) {
        if (linia != "") zajete.push_back(linia);
    }
    plik.close();

    if (zajete.size() == 0) {
        cout << "Brak rezerwacji do usuniecia." << endl;
        wyswietlinfo();
        return;
    }

    cout << "Zajete pokoje:" << endl;
    for (int i = 0; i < zajete.size(); i++) {
        cout << i + 1 << ". " << zajete[i] << endl;
    }

    cout << "Wybierz numer rezerwacji do usuniecia: ";
    int wybor;
    cin >> wybor;

    if (wybor < 1 || wybor > zajete.size()) {
        cout << "Niepoprawny numer." << endl;
        wyswietlinfo();
        return;
    }

    string pokoj = zajete[wybor - 1];

    int poz = pokoj.find('-');
    string czysty = pokoj.substr(0, poz - 1);

    ofstream dost("dostepnepokoje.txt", ios::app);
    dost << czysty << endl;
    dost.close();

    ofstream zaj("zajetepokoje.txt", ios::trunc);
    for (int i = 0; i < zajete.size(); i++) {
        if (i != wybor - 1) zaj << zajete[i] << endl;
    }
    zaj.close();

    cout << "Rezerwacja usunieta." << endl;
    wyswietlinfo();
}
void wyswietlopisypokoi() {
    ifstream plik("opisypokoi.txt");
    if (!plik.is_open()) {
        cout << "Brak opisów pokoi." << endl;
        wyswietlinfo();
        return;
    }

    cout << "Opisy pokoi:" << endl;
    string linia;
    while (getline(plik, linia)) {
        if (linia != "") cout << linia << endl;
    }
    plik.close();
    cout << endl;
    wyswietlinfo();
}

void dodawaniepokoju() {
    cin.ignore();
    cout << "Podaj nazwę pokoju: ";
    string nazwa;
    getline(cin, nazwa);

    cout << "Podaj cenę: ";
    string cena;
    getline(cin, cena);

    cout << "Podaj opis pokoju (koniec kropka '.' w nowej linii): " << endl;
    vector<string> opis;
    string linia;
    while (true) {
        getline(cin, linia);
        if (linia == ".") break;
        opis.push_back(linia);
    }


    ifstream test("dostepnepokoje.txt");
    int maxNr = 0;
    string temp;
    while (getline(test, temp)) {
        if (temp != "") {
            int k = temp.find('.');
            if (k != string::npos) {
                int nr = stoi(temp.substr(0, k));
                if (nr > maxNr) maxNr = nr;
            }
        }
    }
    test.close();
    int nowyNr = maxNr + 1;

    ofstream out("dostepnepokoje.txt", ios::app);
    out << nowyNr << ". " << nazwa << " - " << cena << " PLN" << endl;
    out.close();

    ofstream opisPlik("opisypokoi.txt", ios::app);
    opisPlik << nowyNr << ". " << opis[0] << endl;
    for (int i = 1; i < opis.size(); i++) {
        opisPlik << opis[i] << endl;
    }
    opisPlik << endl;
    opisPlik.close();

    cout << "Dodano pokoj nr " << nowyNr << endl;
    wyswietlinfo();
}
void wyswietlinfo() {
    cout << endl;
    cout << "1. Wyświetl dostępne pokoje" << endl;
    cout << "2. Zarezerwuj jeden z pokoi" << endl;
    cout << "3. Wyświetl zajęte pokoje" << endl;
    cout << "4. Usuń rezerwację" << endl;
    cout << "5. Wyświetl opisy pokoi" << endl;
    cout << "6. Dodaj pokój" << endl;
    cout << "7. Wyjście" << endl;

    int wybor;
    cin >> wybor;

    switch (wybor) {
    case 1: wyswietldostepnepokoje(); break;
    case 2: zarezerwujjedenzpokoi(); break;
    case 3: wyswietlzajetepokoje(); break;
    case 4: usunrezerwacje(); break;
    case 5: wyswietlopisypokoi(); break;
    case 6: dodawaniepokoju(); break;
    case 7: exit(0); break;
    default:
        cout << "Niepoprawny wybor!" << endl;
        wyswietlinfo();
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    cout << "Witamy w programie zarządzania pensjonatem!" << endl;
    wyswietlinfo();
    return 0;
}
void usuwaniepkoju() {
    vector<string> dostepne;
    vector<string> zajete;
    string linia;

    ifstream fin("dostepnepokoje.txt");
    while (getline(fin, linia)) if (linia != "") dostepne.push_back(linia);
    fin.close();

    ifstream fin2("zajetepokoje.txt");
    while (getline(fin2, linia)) if (linia != "") zajete.push_back(linia);
    fin2.close();

    cout << "Dostępne pokoje:" << endl;
    for (int i = 0; i < dostepne.size(); i++) cout << i + 1 << ". " << dostepne[i] << endl;

    cout << "Zajęte pokoje:" << endl;
    for (int i = 0; i < zajete.size(); i++) cout << i + 1 << ". " << zajete[i] << endl;

    if (dostepne.empty() && zajete.empty()) {
        cout << "Brak pokoi do usunięcia." << endl;
        wyswietlinfo();
        return;
    }

    cout << "Usuń z (d)ostępne czy (z)ajęte? ";
    char wybor; cin >> wybor;

    cout << "Podaj numer pokoju do usunięcia: ";
    int numer; cin >> numer;

    string usunieta = "";
    if (wybor == 'd' || wybor == 'D') {
        if (numer < 1 || numer > dostepne.size()) { cout << "Błędny numer!" << endl; wyswietlinfo(); return; }
        usunieta = dostepne[numer - 1];
        ofstream out("dostepnepokoje.txt", ios::trunc);
        for (int i = 0; i < dostepne.size(); i++) if (i != numer - 1) out << dostepne[i] << endl;
        out.close();
    }
    else {
        if (numer < 1 || numer > zajete.size()) { cout << "Błędny numer!" << endl; wyswietlinfo(); return; }
        usunieta = zajete[numer - 1];
        ofstream out("zajetepokoje.txt", ios::trunc);
        for (int i = 0; i < zajete.size(); i++) if (i != numer - 1) out << zajete[i] << endl;
        out.close();
    }


    string numStr = "";
    int i = 0;
    while (i < usunieta.size() && !isdigit(usunieta[i])) i++;
    int start = i;
    while (i < usunieta.size() && isdigit(usunieta[i])) i++;
    if (start < i) numStr = usunieta.substr(start, i - start);

    vector<string> all;
    ifstream finOpis("opisypokoi.txt");
    while (getline(finOpis, linia)) all.push_back(linia);
    finOpis.close();

    int total = all.size();
    int startLine = -1;
    for (int j = 0; j < total; j++) {
        string l = all[j];
        if (l.find(numStr + ".") == 0) { startLine = j; break; }
    }

    if (startLine != -1) {
        int q = startLine;
        while (q < total && all[q] != "") q++;
        vector<string> nowy;
        for (int j = 0; j < startLine; j++) nowy.push_back(all[j]);
        for (int j = q + 1; j < total; j++) nowy.push_back(all[j]);
        ofstream outOpis("opisypokoi.txt", ios::trunc);
        for (auto& s : nowy) outOpis << s << endl;
        outOpis.close();
    }

    cout << "Usunięto pokój i jego opis (jeśli znaleziono). Numer: " << numStr << endl;
    wyswietlinfo();
}



void wyswietlpokojevip() {
    ifstream test("dostepnepokojevip.txt");
    if (!test.is_open() || test.peek() == ifstream::traits_type::eof()) { cout << "Brak pokoi VIP"; wyswietlinfo(); return; }
    string linia;
    while (getline(test, linia)) if (linia != "") cout << linia << endl;
    test.close();
    wyswietlinfo();
}

void wyswietlzajetepokojevip() {
    ifstream test("zajetepokojevip.txt");
    if (!test.is_open() || test.peek() == ifstream::traits_type::eof()) { cout << "Brak zajętych pokoi VIP"; wyswietlinfo(); return; }
    string linia;
    while (getline(test, linia)) if (linia != "") cout << linia << endl;
    test.close();
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
    ifstream testopis("opisypokoivip.txt", ios::binary | ios::ate);
    if (testopis) { if (testopis.tellg() > 0) opisPusty = false; testopis.close(); }

    ofstream outOpis("opisypokoivip.txt", ios::app);
    if (!opisPusty) outOpis << '\n';
    outOpis << nowyNr << ". " << opisWiersze[0] << '\n';
    for (int idx = 1; idx < (int)opisWiersze.size(); idx++) outOpis << opisWiersze[idx] << '\n';
    outOpis << '\n';
    outOpis.close();

    cout << "Dodano pokój VIP nr " << nowyNr << " wraz z opisem." << endl;
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
    if (testPlik.tellg() == 0) {
        testPlik.close();
        cout << "Brak dostępnych pokoi VIP (plik pusty)." << endl;
        wyswietlinfo();
        return;
    }
    testPlik.close();

    ifstream in("dostepnepokojevip.txt");
    vector<string> linie;
    string tmp;
    while (getline(in, tmp)) if (tmp != "") linie.push_back(tmp);
    in.close();

    int ile = (int)linie.size();
    cout << "Dostępne pokoje VIP:" << endl;
    for (int i = 0; i < ile; i++) cout << (i + 1) << ". " << linie[i] << endl;

    cout << "Podaj numer pokoju VIP, który chcesz zarezerwować: ";
    int numerPokoju; cin >> numerPokoju;
    if (numerPokoju<1 || numerPokoju>ile) {
        cout << "Numer poza zakresem." << endl; wyswietlinfo(); return;
    }

    cout << "Na ile dni chcesz zarezerwować pokój VIP? ";
    int iloscDni; cin >> iloscDni;
    if (iloscDni <= 0) { cout << "Liczba dni musi być większa od zera." << endl; wyswietlinfo(); return; }

    string wybrany = linie[numerPokoju - 1];
    vector<string> nowa;
    for (int i = 0; i < ile; i++) if (i != (numerPokoju - 1)) nowa.push_back(linie[i]);

    ofstream out("dostepnepokojevip.txt", ios::trunc);
    for (string& l : nowa) out << l << '\n';
    out.close();

    ofstream zajete("zajetepokojevip.txt", ios::app);
    zajete << wybrany << " - " << iloscDni << " dni" << '\n';
    zajete.close();

    cout << "Pokój VIP został zarezerwowany i przeniesiony do zajętych pokoi VIP." << endl;
    wyswietlinfo();
}

void usunrezerwacjepokojuvip() {
    ifstream testPlik("zajetepokojevip.txt", ios::binary);
    if (!testPlik) { cout << "Brak rezerwacji VIP (plik nie istnieje)." << endl; wyswietlinfo(); return; }
    testPlik.seekg(0, ios::end);
    if (testPlik.tellg() == 0) { testPlik.close(); cout << "Brak rezerwacji VIP (plik pusty)." << endl; wyswietlinfo(); return; }
    testPlik.close();

    ifstream pokaz("zajetepokojevip.txt");
    string linia;
    int licznik = 0;
    cout << "Zajęte pokoje VIP:" << endl;
    while (getline(pokaz, linia)) if (linia != "") { licznik++; cout << licznik << ". " << linia << endl; }
    pokaz.close();
    if (licznik == 0) { cout << "Brak rezerwacji VIP." << endl; wyswietlinfo(); return; }

    cout << "Podaj numer rezerwacji VIP, którą chcesz usunąć: ";
    int numer; cin >> numer;
    if (numer<1 || numer>licznik) { cout << "Numer poza zakresem." << endl; wyswietlinfo(); return; }

    ifstream czytaj("zajetepokojevip.txt");
    string wynik = "", usuwana = "";
    int obecny = 0;
    while (getline(czytaj, linia)) {
        if (linia == "") continue;
        obecny++;
        if (obecny == numer) usuwana = linia; else wynik += linia + '\n';
    }
    czytaj.close();

    ofstream zapisz("zajetepokojevip.txt", ios::trunc);
    zapisz << wynik;
    zapisz.close();

    string nazwa = ""; int dl = (int)usuwana.length(), i = 0;
    while (i < dl) {
        if (i + 2 < dl && usuwana[i] == ' ' && usuwana[i + 1] == '-' && usuwana[i + 2] == ' ') break;
        nazwa += usuwana[i]; i++;
    }
    if (nazwa == "") nazwa = usuwana;

    ofstream dost("dostepnepokojevip.txt", ios::app);
    dost << nazwa << '\n';
    dost.close();

    cout << "Rezerwacja VIP usunięta. Pokój VIP przywrócono do dostępnych." << endl;
    wyswietlinfo();
}

int koniec() {
    exit(0);
}
