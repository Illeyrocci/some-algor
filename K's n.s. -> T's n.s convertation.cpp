#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
long long st(int l, int i){
    long long s = l;
    for (int n = 1; n < i; ++n)
        s *= l;
    if (i == 0)
        return 1;
    return s;
}

long long toDec(string n, int k){
    long long s = 0, i = 0;
    string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (i < n.length()){
        if (n[n.length() - i - 1] - 48){
            s += alphabet.rfind(n[n.length() - i - 1]) * st(k, i);
        }
        i +=1;
    }
    return s;
}
string convert(long long n, int k){
    string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    long long symbol = 0;
    string str = "";
    while(n > 0)
    {
        symbol = n % k;
        n = n / k;
        str.push_back(alphabet[symbol]);
    }
    if (str.size() == 0) {return "0";}
    reverse(str.begin(), str.end());
    return str;
} 

int main(){
    int K,T; cin >> K >> T;
    string s; cin >> s;
    long long dec = toDec(s, K);
    s = convert(dec, T);
    cout << s;
}
