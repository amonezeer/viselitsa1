#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

const vector<string> HANGMAN = {
    R"(
     ------
     |    |
     |
     |
     |
     |
     |
    ----------
    )",
    R"(
     ------
     |    |
     |    O
     |
     |
     |
     |
    ----------
    )",
    R"(
     ------
     |    |
     |    O
     |    |
     | 
     |   
     |    
    ----------
    )",
    R"(
     ------
     |    |
     |    O
     |   /|
     |   
     |   
     |   
    ----------
    )",
    R"(
     ------
     |    |
     |    O
     |   /|\
     |   
     |   
     |     
    ----------
    )",
    R"(
     ------
     |    |
     |    O
     |   /|\
     |   /
     |   
     |    
    ----------
    )",
    R"(
     ------
     |    |
     |    O
     |   /|\
     |   / \
     |   
     |   
    ----------
    )"
};

const vector<string> WORDS = { "������", "����������", "����������������" ,"�����", "��������", "���", };

string selectRandomWord(const vector<string>& words) {
    srand(time(0));
    int index = rand() % words.size();
    return words[index];
}

bool contains(const string& word, char guess) {
    return word.find(guess) != string::npos;
}

int main() {
    system("chcp 1251");

    string word = selectRandomWord(WORDS);
    string so_far(word.size(), '_');
    vector<char> used;
    int wrong = 0;
    int max_wrong = HANGMAN.size() - 1;

    auto start = high_resolution_clock::now();

    cout << "����� ���������� � ���� ��������!\n";
    cout << "���������� ������� �����:\n";

    while (wrong < max_wrong && so_far != word) {
        cout << HANGMAN[wrong] << endl;
        cout << "\n�� ������������ ��������� �����:\n";
        for (char letter : used) {
            cout << letter << " ";
        }
        cout << "\n\n�� ������ ������ ����� �������� ���:\n" << so_far << endl;

        char guess;
        cout << "\n\n������� ���� �������: ";
        cin >> guess;

        while (find(used.begin(), used.end(), guess) != used.end()) {
            cout << "�� ��� ������� ����� " << guess << ". ����������, ������� ������ �����: ";
            cin >> guess;
        }

        used.push_back(guess);

        if (contains(word, guess)) {
            cout << "\n��, ����� \"" << guess << "\" ���� � �����!\n";
            for (int i = 0; i < word.size(); ++i) {
                if (word[i] == guess) {
                    so_far[i] = guess;
                }
            }
        }
        else {
            cout << "\n� ���������, ����� \"" << guess << "\" ��� � �����.\n";
            ++wrong;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);

    if (wrong == max_wrong) {
        cout << HANGMAN[wrong] << endl;
        cout << "\n��� ��������!\n";
    }
    else {
        cout << "\n�� ������� �����!\n";
    }
    cout << "\n���������� ����� ����: \"" << word << "\"\n";
    cout << "���������� �������: " << used.size() << endl;
    cout << "����� ����������: " << duration.count() << " ������." << endl;
    return 0;
}
