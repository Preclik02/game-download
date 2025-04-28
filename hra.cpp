#define NOMINMAX

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <limits>

int main() {
    using std::cout;
    using std::cin;
    using std::string;

    int bank = 0;
    int cash = 500;
    int vydelek = 10;
    int cena = 750;
    int suma;
    int upgrade;
    string akce;
    string username;


    std::ifstream inFile("save.txt");
    if (inFile.is_open()) {
        inFile >> bank;
        inFile >> cash;
        inFile >> vydelek;
        inFile >> cena;
        inFile.close();
    }


    while (true){
        cout << "\n";
        cout << "(vlozit, vybrat, zobrazit, vydelat, ulozit, obchod, reset, konec)\n";
        cout << "Co chces udelat: ";
        cin >> akce;

        if (akce == "vlozit") { 
            cout << "Zadej sumu: ";
            cin >> suma;
            cash -= suma;
            bank += suma;
        }
        else if (akce == "vybrat") {
            cout << "Zadej sumu: ";
            cin >> suma;
            bank -= suma;
            cash += suma;
        }
        else if (akce == "zobrazit") {
            cout << "Banka: " << bank << " Penize: " << cash << "\n";
        }
        else if (akce == "vydelat") {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
            cout << "Vydelavas: " << vydelek << "/s\n";
            cout << "Stiskni Enter pro ukonceni vydelavani\n";
            while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                Sleep(50);
            }
            int elapsedTime = 0;
            while (true) {
                if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                    break;
                }
                Sleep(100);
                elapsedTime += 100;

                if (elapsedTime >= 1000) {
                    cash += vydelek;
                    cout << "Penize: " << cash << "\n";
                    elapsedTime = 0;
                }
            }
        }   
        else if (akce == "obchod"){
            cout << "[0] Odejit z obchodu\n";
            cout << "[1] Upgrade vydelek o 5/s: " << cena << " penez v bance\n\n";
            cout << "Jakej upgrade chces?: ";
            cin >> upgrade;

            if (upgrade == 1) {
                cout << "Upgrade zakoupen\n";
                bank -= cena;
                cena += 50;
                vydelek += 5;
            }
        }
        else if (akce == "konec") {
            std::ofstream outFile("save.txt");
            outFile << bank << "\n";
            outFile << cash << "\n";
            outFile << vydelek << "\n";
            outFile << cena << "\n";
            outFile.close();
            break;
        }
        else if (akce == "ulozit") { 
            cout << "Napis svoje jmeno: ";
            cin >> username;
            std::ofstream saveFile("leaderboard.txt");
            if (saveFile.is_open()) {
                saveFile << "Jmeno: " << username << "\n";
                saveFile << "Penize: " << cash << "\n";
                saveFile << "Banka: " << bank << "\n";
                saveFile.close();
                cout << "Hra ulozena!\n";
                cout << "Pro info o hre: https://preclik02.github.io/game-download/";
            }
        }
        else if (akce == "reset") {
            bank = 0;
            cash = 500; 
            cena = 50;
            vydelek = 10;
            cout << "Hra byla resetovana\n";
        }
        else {
            cout << "Neplatna akce\n";
        }
    }

    return 0;
}