#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string digits;

    BigInt(string s = "0") {
        digits = s;
    }

    bool isLess(BigInt other) {
        if (digits.length() != other.digits.length())
            return digits.length() < other.digits.length();
        return digits < other.digits;
    }

    BigInt operator+(BigInt other) {
        string result = "";
        int i = digits.length() - 1;
        int j = other.digits.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry) {
            int d1 = 0, d2 = 0;

            if (i >= 0) d1 = digits[i--] - '0';
            if (j >= 0) d2 = other.digits[j--] - '0';

            int sum = d1 + d2 + carry;
            result += char((sum % 10) + '0');
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
            int d1 = digits[i--] - '0';
            int d2 = 0;
            if (j >= 0) d2 = other.digits[j--] - '0';

            int diff = d1 - d2 - borrow;

            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result += char(diff + '0');
        }

        while (result.length() > 1 && result.back() == '0')
            result.pop_back();

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
        for (int x : product) {
            if (!(result.empty() && x == 0))
                result += char(x + '0');
        }

        if (result.empty())
            return BigInt("0");
        else
            return BigInt(result);
    }

    BigInt operator/(BigInt other) {
        if (other.digits == "0")
            return BigInt("Error");

        string result = "";
        string currentChunk = "";

        for (char c : digits) {
            currentChunk += c;

            while (currentChunk.size() > 1 && currentChunk[0] == '0')
                currentChunk.erase(0, 1);

            BigInt current(currentChunk);
            int count = 0;

            while (!current.isLess(other)) {
                current = current - other;
                if (current.digits == "0")
                    currentChunk = "";
                else
                    currentChunk = current.digits;
                count++;
            }

            result += char(count + '0');
        }

        size_t firstNonZero = result.find_first_not_of('0');

        if (firstNonZero == string::npos)
            return BigInt("0");
        else
            return BigInt(result.substr(firstNonZero));
    }
};

struct Compare {
    bool operator()(pair<BigInt, BigInt> a, pair<BigInt, BigInt> b) {
        return b.first.isLess(a.first);
    }
};

void dijkstraBigIntPrimes(int limit) {
    priority_queue<pair<BigInt, BigInt>, vector<pair<BigInt, BigInt>>, Compare> minHeap;

    cout << "2 ";
    minHeap.push({BigInt("4"), BigInt("2")});

    for (int number = 3; number <= limit; number++) {
        BigInt currentNumber(to_string(number));

        if (currentNumber.isLess(minHeap.top().first)) {
            cout << number << " ";
            minHeap.push({currentNumber * currentNumber, currentNumber});
        } else {
            while (currentNumber.digits == minHeap.top().first.digits) {
                auto topPair = minHeap.top();
                minHeap.pop();
                minHeap.push({topPair.first + topPair.second, topPair.second});
            }
        }
    }
    cout << endl;
}

int main() {
    dijkstraBigIntPrimes(1000);
    return 0;
}
