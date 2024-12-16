#include <iostream>

bool is_letter(char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

std::string lower(std::string string) {
    std::string str = "";
    short n = string.length();
    for(int i = 0; i < n; i++) {
        char c = string[i];
        if ('A' <= c && c <= 'Z')
            str += c + ('z' - 'Z');
        else str += c;
    }
    return str;
}

std::string toWord(std::string s) {
    std::string str = "";
    s = lower(s);
    short n = s.length();

    short start = 0;
    char c = s[start];
    while (!is_letter(c)) {
        start++;
        c = s[start];
    }
    short end = n;
    c = s[end];
    while (!is_letter(c)) {
        end--;
        c = s[end];
    }
    for (int i = start; i <= end; i++) {
        char c = s[i];
        str += c;
    }
    return str;
}

bool is_palindrome(std::string s) {
    s = toWord(s);
    int n = s.length();
    int mid = n / 2;
    for(int i = 0; i <= mid; i ++) {
        char c1 = s[i];
        char c2 = s[n - i - 1];
        if (c1 != c2)
            return false;
    }
    return true;
}

bool has_palindroms(std::string* words, int n) {
    for (int i = 0; i < n; i++) {
        if((is_palindrome(words[i])) && (words[i].length() > 1)) return true;
    }
    return false;
}

int countVowels(std::string word) {
    int n = word.length();
    int k = 0;
    for (int i = 0; i < n; i++) {
        switch (word[i])
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'y':
            // fun fact that y is semivowel. It can be consonant and vowel at the same time
            k++;
            break;
        }
    }
    return k;
}

void countWordsVowels(std::string* words, int* counts, int n) {
    for (int i = 0; i < n; i++) {
        counts[i] = countVowels(words[i]);
    }
}

void sortWordsByVowels(std::string* words, int* counts, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (counts[i] > counts[j]) {
                std::swap(words[i], words[j]);
                std::swap(counts[i], counts[j]);
            }
        }
    }
}

void doubleVowels(std::string* words, int n) {
    for (int i = 0; i < n; i++) {
        std::string word = words[i];
        std::string result = "";
        int k = word.length();
        for (int j = 0; j < k; j++) {
            switch (word[j])
            {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'y':
                result += word[j];
                result += word[j];
                break;
            // sometimes y is vowels and sometimes it is consonant
            default:
                result += word[j];
                break;
            }
        }
        words[i] = result;
    }
}

void sortWordsByAlpha(std::string* words, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (words[i] < words[j]) {
                std::swap(words[i], words[j]);
            }
        }
    }
}

void printWords(std::string* words, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << words[i] << " ";
    }
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    int n = input.length();
    std::string words[2000];
    
    int k = 0;
    int j = 0;
    for(int i = 0; i < n + 1; i++) {
        char c = input[i];
        if ((c != ' ') && (i != n)) continue;
        words[k] = toWord(input.substr(j, i - j));
        k++;
        j = i + 1;
    }
    if (has_palindroms(words, k)) {
        int count_vowels[2000] = {0};
        countWordsVowels(words, count_vowels, k);
        sortWordsByVowels(words, count_vowels, k);
    }
    else {
        doubleVowels(words, k);
        sortWordsByAlpha(words, k);
    }
    printWords(words, k);
    return 0;
}