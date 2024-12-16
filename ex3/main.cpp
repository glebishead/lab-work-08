#include <iostream>
#include <string>
#include <fstream>


bool is_letter(char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

bool isMostPopular(char c, char* pc1, char* pc2, char* pc3, char* pc4) {
    if ((c == *pc1) || (c == *pc2) || (c == *pc3) || (c == *pc4))
        return true;
    return false;
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

void countLetters(std::string* words, int* letter_count, int n) {
    for (int i = 0; i < n; i++) {
        std::string word = toWord(words[i]);
        for (int j = 0; j < word.length(); j++) {
            char c = word[j];
            if (is_letter(c))
                letter_count[c - 'a'] += 1;
        }
    }
}

void getMostPopular(int* letter_count, int n, char* pc1, char* pc2, char* pc3, char* pc4) {
    int m1, m2, m3, m4;
    char l1, l2, l3, l4;
    m1 = *pc1;
    m2 = *pc2;
    m3 = *pc3;
    m4 = *pc4;
    short n_alpha = 26;
    for(int i = 0; i < n_alpha; i++) {
        int count = letter_count[i];
        if (count > m1) {
            if (count > m2) {
                if (count > m3) {
                    if (count > m4) {
                        m4 = count;
                        l4 = i;
                    }
                    else {
                        m3 = count;
                        l3 = i;
                    }
                }
                else {
                    m2 = count;
                    l2 = i;
                    }
            }
            else {
                m1 = count;
                l1 = i;
                }
        }
    }
    *pc1 = l1 + 'a';
    *pc2 = l2 + 'a';
    *pc3 = l3 + 'a';
    *pc4 = l4 + 'a';
}

void writeFile(std::string fileName, std::string *words, int n) {
    std::ofstream out(fileName);
    for(int i = 0; i < n; i++) {
        out << words[i] << " ";
    }
}

bool conainsTwoMostPopular(std::string s, char* pc1, char* pc2, char* pc3, char* pc4) {
    s = lower(s);
    int n = s.length();
    bool flagFirst = false;
    for(int i = 0; i < n; i++) {
        char c = s[i];
        if(isMostPopular(c, pc1, pc2, pc3, pc4)) {
            if (flagFirst == true) {
                return true;
            }
            flagFirst = true;
        }
        else {
            flagFirst = false;
        }
    }
    return false;
}

std::string upper(std::string string) {
    std::string str = "";
    short n = string.length();
    for(int i = 0; i < n; i++) {
        char c = string[i];
        if ('a' <= c && c <= 'z')
            str += c - ('z' - 'Z');
        else str += c;
    }
    return str;
}

std::string findPopularInWord(std::string word, char* pc1, char* pc2, char* pc3, char* pc4) {
    std::string result = "";
    word = lower(word);
    int n = word.length();
    for(int i = 0; i < n; i++) {
        char c = word[i];
        if (isMostPopular(c, pc1, pc2, pc3, pc4)) {
            result += c;
        }
        else {
            result += "-";
        }
    }
    return result;
}

void makeSomeWordsUpper(std::string* words, int n, char* pc1, char* pc2, char* pc3, char* pc4) {
    for(int i = 0; i < n; i++) {
        std::string word = words[i];
        if(conainsTwoMostPopular(word, pc1, pc2, pc3, pc4)) {
            std::string letters = findPopularInWord(word, pc1, pc2, pc3, pc4);
            words[i] = upper(word) + "(" + letters + ")";
        }
    }
}

int main() {
    std::string words[2000];
    int letter_count[26] = {0};
    char c1, c2, c3, c4;
    c1 = c2 = c3 = c4 = 0;
    int n = 0;

    std::ifstream in("ex3\\input.txt");
    if(!in.is_open()) {
        std::cout << "File not found" << std::endl;
        return -1;
    }
    while(!in.eof()) {
        std::string s;
        in >> s;
        std::string word = s;
        words[n] = word;
        n++;
    }
    in.close();
    
    countLetters(words, letter_count, n);
    getMostPopular(letter_count, n, &c1, &c2, &c3, &c4);
    std::cout << c1 << " " << c2 << " " << c3 << " " << c4 << std::endl;
    makeSomeWordsUpper(words, n, &c1, &c2, &c3, &c4);

    writeFile("ex3\\output.txt", words, n);
    return 0;
}