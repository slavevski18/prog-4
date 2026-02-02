#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string digits;

    BigInt(string s = "0") {
        digits = s;
    }

    bool isLess(BigInt other) {
        if (digits.length() != other.digits.length()) {
            return digits.length() < other.digits.length();
        }
        return digits < other.digits;
    }

    bool operator==(BigInt other) {
        return digits == other.digits;
    }

    BigInt operator+(BigInt other) {
        string result = "";
        int i = digits.length() - 1;
        int j = other.digits.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry) {
            int d1 = 0;
            if (i >= 0) {
                d1 = digits[i] - '0';
                i--;
            }
            int d2 = 0;
            if (j >= 0) {
                d2 = other.digits[j] - '0';
                j--;
            }
            int sum = carry + d1 + d2;
            result += (char)((sum % 10) + '0');
            carry = sum / 10;
        }
        reverse(result.begin(), result.end());
        return BigInt(result);
    }

    BigInt operator-(BigInt other) {
        string result = "";
        int i = digits.length() - 1;
        int j = other.digits.length() - 1;
        int borrow = 0;

        while (i >= 0) {
            int d1 = digits[i] - '0';
            i--;
            int d2 = 0;
            if (j >= 0) {
                d2 = other.digits[j] - '0';
                j--;
            }
            int diff = d1 - d2 - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result += (char)(diff + '0');
        }
        while (result.length() > 1 && result.back() == '0') result.pop_back();
        reverse(result.begin(), result.end());
        return BigInt(result);
    }

    BigInt operator*(BigInt other) {
        int n = digits.length(), m = other.digits.length();
        vector<int> product(n + m, 0);

        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (digits[i] - '0') * (other.digits[j] - '0');
                int sum = mul + product[i + j + 1];
                product[i + j + 1] = sum % 10;
                product[i + j] += sum / 10;
            }
        }

        string result = "";
        for (int k = 0; k < product.size(); k++) {
            int x = product[k];
            if (result.empty() && x == 0) continue;
            result += (char)(x + '0');
        }

        if (result.empty()) return BigInt("0");
        return BigInt(result);
    }

    pair<BigInt, BigInt> divmod(BigInt other) {
        if (other.digits == "0") return {BigInt("Error"), BigInt("Error")};

        string quotientStr = "";
        string currentChunk = "";

        for (int idx = 0; idx < digits.size(); idx++) {
            char digit = digits[idx];
            currentChunk += digit;

            while (currentChunk.size() > 1 && currentChunk[0] == '0')
                currentChunk.erase(0, 1);

            BigInt current(currentChunk);
            int count = 0;

            while (!(current.isLess(other))) {
                current = current - other;
                if (current.digits == "0") currentChunk = "";
                else currentChunk = current.digits;
                count++;
            }
            quotientStr += (char)(count + '0');
        }

        size_t firstNonZero = quotientStr.find_first_not_of('0');
        string quotient;
        if (firstNonZero == -1) quotient = "0";
        else quotient = quotientStr.substr(firstNonZero);

        string remainder;
        if (currentChunk.empty()) remainder = "0";
        else remainder = currentChunk;

        return {BigInt(quotient), BigInt(remainder)};
    }

    BigInt operator/(BigInt other) { return divmod(other).first; }
    BigInt operator%(BigInt other) { return divmod(other).second; }
};


BigInt binpow(BigInt base, BigInt exponent, BigInt modulus) {
    BigInt result("1");
    base = base % modulus;

    while (!(exponent == BigInt("0"))) {
        BigInt remainder = exponent % BigInt("2");

        if (!(remainder == BigInt("0"))) {
            result = (result * base) % modulus;
        }

        base = (base * base) % modulus;
        exponent = exponent / BigInt("2");
    }
    return result;
}



int main() {
    BigInt base("35");
    BigInt exponent("124");
    BigInt modulus("1000");

    BigInt finalResult = binpow(base, exponent, modulus);

    cout << base.digits << endl;
    cout << exponent.digits << endl;
    cout << modulus.digits << endl;
    cout << "Rez " << finalResult.digits << endl;

    return 0;
}
