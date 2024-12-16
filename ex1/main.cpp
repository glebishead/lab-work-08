#include <iostream>
#include <string>
#include <fstream>


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

int countSimilarLetters(std::string s) {
    s = lower(s);
    short const length_of_alpha = 26;
    int m[length_of_alpha] = {0};
    int n = s.length();
    int max = 1;
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (is_letter(c)) {
            m[c - 'a'] += 1;
        }
    }
    for (int j = 0; j < length_of_alpha; j++) {
        if (m[j] > max)
            max = m[j];
    }
    return max;
}

void deleteSimilarWords(std::string* words, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (words[i] == words[j]) {
                words[j] = "";
            }
        }
    }
}

void sortWords(std::string* words, int* similar_letters, int n) {
    for(int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int l1 = words[i].length();
            int l2 = words[j].length();
            if (l1 > l2) {
                std::swap(similar_letters[i], similar_letters[j]);
                std::swap(words[i], words[j]);
            }
        }
    }
}

int main() {
    std::ifstream in("ex1\\input.txt");
    if(!in.is_open()) {
        std::cout << "File not found" << std::endl;
        return -1;
    }

    std::string words[2000];
    int similar_letters[2000];
    int n = 0;

    while(!in.eof()) {
        std::string s;
        in >> s;

        std::string word = toWord(s);
        short n_similar_letters = countSimilarLetters(word);
        if(n_similar_letters > 2) {
            words[n] = word;
            similar_letters[n] = n_similar_letters;
            n++;
        }
    }

    deleteSimilarWords(words, n);
    sortWords(words,similar_letters, n);

    in.close();
    std::ofstream out("ex1\\output.txt");
    for(int i = 0; i < n; i++) {
        if (words[i].length() > 0)
            out << words[i] << std::endl;
    }
    return 0;
}