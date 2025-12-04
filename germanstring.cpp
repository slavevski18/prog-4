#include <bits/stdc++.h>
using namespace std;

class GermanString {
private:
    char* data;
    int32_t len;
    char* pre;

public:
    GermanString() {
        len = 0;
        data = nullptr;
        pre = nullptr;
    }

    GermanString(const char* src) {
        if (src) {
            len = strlen(src);

            data = new char[len + 1];
            for (int i = 0; i < len; i++)
                data[i] = src[i];
            data[len] = '\0';

            if (len <= 12) {
                pre = new char[5];
                int copyLimit = min(4, len);
                for (int i = 0; i < copyLimit; i++)
                    pre[i] = src[i];
                pre[copyLimit] = '\0';
            } else {
                pre = nullptr;
            }
        } else {
            data = nullptr;
            pre = nullptr;
            len = 0;
        }
    }

    GermanString(const GermanString& other) {
        len = other.len;

        if (len > 0) {
            data = new char[len + 1];
            for (int i = 0; i < len; i++)
                data[i] = other.data[i];
            data[len] = '\0';

            if (len <= 12 && other.pre) {
                pre = new char[5];
                int limit = min(4, len);
                for (int i = 0; i < limit; i++)
                    pre[i] = other.pre[i];
                pre[limit] = '\0';
            } else {
                pre = nullptr;
            }
        } else {
            data = nullptr;
            pre = nullptr;
        }
    }

    GermanString& operator=(const GermanString& rhs) {
        if (this == &rhs) return *this;

        delete[] data;
        delete[] pre;

        len = rhs.len;

        if (len > 0) {
            data = new char[len + 1];
            for (int i = 0; i < len; i++)
                data[i] = rhs.data[i];
            data[len] = '\0';

            if (len <= 12 && rhs.pre) {
                pre = new char[5];
                int limit = min(4, len);
                for (int i = 0; i < limit; i++)
                    pre[i] = rhs.pre[i];
                pre[limit] = '\0';
            } else {
                pre = nullptr;
            }
        } else {
            data = nullptr;
            pre = nullptr;
        }

        return *this;
    }

    ~GermanString() {
        delete[] data;
        delete[] pre;
    }

    int length() const {
        return len;
    }

    void show() const {
        for (int i = 0; i < len; i++)
            cout << data[i];
        cout << '\n';
    }

    void clear() {
        len = 0;
        delete[] data;
        data = nullptr;
        delete[] pre;
        pre = nullptr;
    }

    const char& operator[](int idx) const {
        return data[idx];
    }

    char& operator[](int idx) {
        return data[idx];
    }

    int locate(char c) const {
        for (int i = 0; i < len; i++)
            if (data[i] == c)
                return i;
        return -1;
    }
};


GermanString operator+(const GermanString& a, const GermanString& b)
{
    int total = a.length() + b.length();
    char* combined = new char[total + 1];

    for (int i = 0; i < a.length(); i++)
        combined[i] = a[i];

    for (int i = 0; i < b.length(); i++)
        combined[a.length() + i] = b[i];

    combined[total] = '\0';

    GermanString res(combined);
    delete[] combined;
    return res;
}


int main()
{
    GermanString s("Matej");
    GermanString t("Slavevski");

    cout << s.length() << endl;
    s.show();

    cout << s[2] << endl;

    s[2] = 'p';
    cout << s[2] << endl;

    cout << s.locate('a') << endl;

    GermanString res = s + t;
    res.show();

    return 0;
}
