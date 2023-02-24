
//The expression may contain signs of addition, subtraction, multiplication, brackets and spaces (else "WRONG" is output)
//"-5 - 7 * ( -1 + 2 * (-34 + 4 + 3 - (-215 * 1 -1)) ) + 1 + 2*( -4 + 2) + 56 - (-23 - 3) * 3" as an example of a valid input

#include <bits/stdc++.h>
bool isStringOK(std::string s){
    int last = 0;
    for (int i = 1; i < s.length(); i++){
        if ((s[i] > '9' || s[i] <'0') && s[i] != '*' && s[i] != '-' && s[i] != '+' && s[i] != ' ' && s[i] != ')' && s[i] != '(') return 0;
        if (s[i] != ' ') {
            if (s[last] >= '0' && s[last] <= '9' && i - last > 1 && s[i] >= '0' && s[i] <= '9') return 0;
            if ((s[last] == '*' || s[last] == '+' || s[last] == '-' ) && (s[i] == '*' || s[i] == '+' || s[i] == '-' || s[i] == ')')) return 0;
            if (s[last] == '(' && (s[i] == ')' || s[i] == '*' || s[i] == '+')) return 0;
            last = i;
        }
    }
    if (s[(int) s.length()-1] == '+' || s[(int) s.length()-1] == '-' || s[(int) s.length()-1] == '*' || s[(int) s.length()-1] == '(') return 0;
    return 1;
}
bool isPSP(std::string s){
    int balance = 0;
    for (int i = 0; i < s.length(); i++){
        if (s[i] == '(') balance++;
        if (s[i] == ')') {
            balance--;
            if (balance < 0) return 0;
        }
    }
    return !balance;
}   
std::string postfix(std::string s){
    std::string ans = "";
    std::vector<char> stack;
    char prev;
    for (int i = 0; i < s.length(); i++){
        if (s[i] == ' ') continue;
        if (s[i] >= '0' && s[i] <= '9'){
            ans += s[i];
            if (s[i+1] < '0' || s[i+1] > '9') ans += '^';
        }
        else if (s[i] == '*'){
            while ((int) stack.size()) {
                if (stack.back() == '*') {
                    ans += '*';
                    stack.pop_back();
                }
                else {

                    break;
                }
            }
            stack.push_back(s[i]);
        }
        else if (s[i] == '+' || s[i] == '-'){
            while ((int) stack.size()) {
                if (stack.back() == '*' || stack.back() == '-' ||stack.back() == '+') {
                        ans += stack.back();
                        stack.pop_back();
                    
                }
                else {
                  break;
                }
            }
            stack.push_back(s[i]);
        }
        else if (s[i] == '(') stack.push_back('(');
        else {
            while ((int) stack.size()){
                if (stack.back() != '('){
                    ans += stack.back();
                    stack.pop_back();
                }
                else {
                    break;
                }
            }
            stack.pop_back();
        }
        prev = s[i];
    }
    while ((int) stack.size()){
        ans += stack.back();
        stack.pop_back();
    }
    return ans;
}
long long evaluate(std::string s){
    std::vector<long long> stack;
    for (int i = 0; i < s.length(); i++){
        if (s[i] == '^') continue;
        if (s[i] >= '0' && s[i] <= '9') {
            long long n = (int) s[i] - 48;
            while (s[i+1] != '^'){
                n *= 10;
                i++;
                n += (int) s[i] - 48;
            }
            stack.push_back(n);
        }
        else if (s[i] == '-') {
            long long a = stack.back();
            stack.pop_back();
            long long b = stack.back();
            stack.pop_back();
            stack.push_back(b-a);
        }
        else if (s[i] == '+') {
            long long a = stack.back();
            stack.pop_back();
            long long b = stack.back();
            stack.pop_back();
            stack.push_back(b+a);
        }
        else if (s[i] == '*') {
            long long a = stack.back();
            stack.pop_back();
            long long b = stack.back();
            stack.pop_back();
            stack.push_back(b*a);
        }
    }
    return stack.back();
}
int main() {
    std::string s;
    std::getline(std::cin,s);
    if (isStringOK(s) && isPSP(s)){
        char last;
        int cnt =0;
        std::set <int> toDelete;
        if (s[0] == '-') s.insert(s.begin(), '0');
        for (int i = 1; i < s.length(); i++){
            if (s[i] == ' ') continue;
            if (s[i] == '-'){
                cnt++;
                if (last == '('){
                    toDelete.insert(cnt);
                }
            }  
            last = s[i];
        }
        cnt = 0;
        for (int i = 1; i < s.length(); i++){
            if (s[i] == ' ') continue;
            if (s[i] == '-'){
                cnt++;
                if (toDelete.find(cnt) != toDelete.end()) {
                    s.insert(s.begin()+i, '0');
                    i++;
                }
            }
        }
        std::cout << evaluate(postfix(s));
    }
    else {
        std::cout << "WRONG";
    }
}
