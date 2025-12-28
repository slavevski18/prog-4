#include <bits/stdc++.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

struct TrieNode {
    bool kraj = false;
    map<wchar_t, TrieNode*> deca;
};

void vnesi(TrieNode* koren, const wstring& zbor) {
    TrieNode* tekoven = koren;
    for (wchar_t c : zbor) {
        if (!tekoven->deca.count(c)) {
            tekoven->deca[c] = new TrieNode();
        }
        tekoven = tekoven->deca[c];
    }
    tekoven->kraj = true;
}

void pecati(TrieNode* jazol, wstring zbor = L"") {
    if (jazol->kraj) {
        wcout << zbor << endl;
    }
    for (auto& [k, d] : jazol->deca) {
        pecati(d, zbor + k);
    }
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    TrieNode* koren = new TrieNode();

    wifstream datoteka(L"MK-dict.txt");
    datoteka.imbue(std::locale(datoteka.getloc(),
        new std::codecvt_utf8<wchar_t>));

    if (!datoteka) {
        wcerr << L"Грешка при отворање на датотеката!" << endl;
        return 1;
    }

    wstring linija;
    while (datoteka >> linija) {
        vnesi(koren, linija);
    }

    pecati(koren);
    return 0;
}
