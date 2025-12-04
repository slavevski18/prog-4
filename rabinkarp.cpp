<<<<<<< HEAD
#include <iostream>     
#include <string>        
#include <vector>        
using namespace std;

vector<int> rabinKarp(const string &text, const string &pattern) {
    int n = text.size();      
    int m = pattern.size();   
    if (m > n) {
        return {};
    }

    const int d = 256;         
    const int q = 101;        
    int h = 1;               
    int p_hash = 0;           
    int t_hash = 0;           
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        p_hash = (d * p_hash + pattern[i]) % q;
        t_hash = (d * t_hash + text[i]) % q;
    }

    vector<int> occurrences; 
    for (int i = 0; i <= n - m; i++) {
        
        if (p_hash == t_hash) {
           
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                occurrences.push_back(i);
            }
        }

        
        if (i < n - m) {
           
            t_hash = (d * (t_hash - text[i] * h) + text[i + m]) % q;
            if (t_hash < 0) {
                t_hash += q;
            }
        }
    }

    return occurrences;
}

int main() {
    string text, pattern;
    
    cout << "Внеси текст: ";
    getline(cin, text);
    cout << "Внеси pattern: ";
    getline(cin, pattern);

    vector<int> res = rabinKarp(text, pattern);

if (res.empty()) {
    cout << "Pattern не е пронајден\n";
} else {
    cout << "Pattern најден на позиции: ";
    for (int i = 0; i < res.size(); i++) {   
        cout << res[i] << " ";
    }
    cout << "\n";
}
return 0;
}
=======
#include <iostream>     
#include <string>        
#include <vector>        
using namespace std;

vector<int> rabinKarp(const string &text, const string &pattern) {
    int n = text.size();      
    int m = pattern.size();   
    if (m > n) {
        return {};
    }

    const int d = 256;         
    const int q = 101;        
    int h = 1;               
    int p_hash = 0;           
    int t_hash = 0;           
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        p_hash = (d * p_hash + pattern[i]) % q;
        t_hash = (d * t_hash + text[i]) % q;
    }

    vector<int> occurrences; 
    for (int i = 0; i <= n - m; i++) {
        
        if (p_hash == t_hash) {
           
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                occurrences.push_back(i);
            }
        }

        
        if (i < n - m) {
           
            t_hash = (d * (t_hash - text[i] * h) + text[i + m]) % q;
            if (t_hash < 0) {
                t_hash += q;
            }
        }
    }

    return occurrences;
}

int main() {
    string text, pattern;
    
    cout << "Внеси текст: ";
    getline(cin, text);
    cout << "Внеси pattern: ";
    getline(cin, pattern);

    vector<int> res = rabinKarp(text, pattern);

if (res.empty()) {
    cout << "Pattern не е пронајден\n";
} else {
    cout << "Pattern најден на позиции: ";
    for (int i = 0; i < res.size(); i++) {   
        cout << res[i] << " ";
    }
    cout << "\n";
}
return 0;
}
>>>>>>> d50c12451ff0df1feed1cfa35cc1f536ea2838bf
