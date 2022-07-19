#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

 using namespace std;

ofstream file("protokolas.txt");
string word1 = "SEND";
string word2 = "MORE";
string word3 = "MONEY";

int usedNumbers[10] = {};
long permutationCount = 0;

struct letter
{
    char character;
    int number;
};

void solveCryptarithmetic(string word1, string word2, string word3);
bool backtrack(int count, letter* nodeArr, int n, string word1, string word2, string word3);
int checkSolution(letter* letterArr, int count, string word1, string word2, string word3);

int main()
{
    system("cls");
    cout << "Programa sprendzianti kriptoaritmetikos uzdavini\n" << endl;
    cout << "Uzdavinys:" << endl;
    cout << word1 << " + " << word2 << " = " << word3 << endl << endl;

    file << "PIRMA DALIS. Duomenys" << endl;
    file << "  1) Uzdavinys: " << word1 << " + " << word2 << " = " << word3 << endl << endl;

  
    solveCryptarithmetic(word1, word2, word3);

    file.close();
    return 0;
}

void solveCryptarithmetic(string word1, string word2, string word3)
{
    int letterCount = 0;
  
    int length1 = word1.length();
    int length2 = word2.length();
    int length3 = word3.length();
  
    bool usedLetters[26] = {};
  
    for (int i = 0; i < length1; i++)
    {
        usedLetters[word1[i] - 'A'] = true;
    }
  
    for (int i = 0; i < length2; i++)
    {
        usedLetters[word2[i] - 'A'] = true;
    }
  
    for (int i = 0; i < length3; i++)
    {
        usedLetters[word3[i] - 'A'] = true;
    }
  
    for (int i = 0; i < 26; i++)
    {
        if (usedLetters[i])
        {
            letterCount++;
        }
    }
  
    if (letterCount > 10)
    {
        cout << "Neteisingas uzdavinys" << endl;
        cout << "Skirtingu raidziu skaicius virsija desimtaine sistema" << endl;
        return;
    }

    file << "ANTRA DALIS. Vykdymas" << endl;
  
    letter letterArr[letterCount];
  
    for (int i = 0, j = 0; i < 26; i++)
    {
        if (usedLetters[i])
        {
            letterArr[j].character = char(i + 'A');
            j++;
        }
    }

    if (backtrack(letterCount, letterArr, 0, word1, word2, word3))
    {
        cout << "Perrinkta " << permutationCount << " variantu" << endl;
        cout << "Sprendinys rastas" << endl;
        cout << "Sprendinys:";

        file << endl << "TRECIA DALIS. Rezultatai" << endl;
        file << "  1) Perrinkta " << permutationCount << " variantu" << endl;
        file << "  2) Sprendinys rastas" << endl;
        file << "  3) Sprendinys:";

        for (int j = 0; j < letterCount; j++)
        {
            cout << " " << letterArr[j].character << "=" << letterArr[j].number;
            file << " " << letterArr[j].character << "=" << letterArr[j].number;

            if(j == letterCount - 1)
            {
                cout << "." << endl;
                file << "." << endl;
            }
            else
            {
                cout << ",";
                file << ",";
            }
        }
    }
    else
    {
        cout << "Perrinkta " << permutationCount << " variantu" << endl;
        cout << "Sprendinys nerastas" << endl;

        file << endl << "TRECIA DALIS. Rezultatai" << endl;
        file << "  1) Perrinkta " << permutationCount << " variantu" << endl;
        file << "  2) Sprendinys nerastas" << endl;
    }
}

bool backtrack(int letterCount, letter* letterArr, int n, string word1, string word2, string word3)
{

    if (n == letterCount - 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (usedNumbers[i] == 0)
            {
                ++permutationCount;

                file << setw(8) << permutationCount << ") ";
                for (int i = 0; i < n; ++i)
                {
                    file << "-";
                }

                letterArr[n].number = i;

                if (checkSolution(letterArr, letterCount, word1, word2, word3) == 1)
                {
                    file << letterArr[n].character << "=" << letterArr[n].number << ". OK" << endl;
                    return true;
                }

                file << letterArr[n].character << "=" << letterArr[n].number << ". Netinka" << endl;
            }
        }

        return false;
    }
  
    for (int i = 0; i < 10; i++)
    {
  
        if (usedNumbers[i] == 0)
        {
            ++permutationCount;
            letterArr[n].number = i;
            usedNumbers[i] = 1;

            file << setw(8) << permutationCount << ") ";
            for (int i = 0; i < n; ++i)
            {
                file << "-";
            }
            file << letterArr[n].character << "=" << letterArr[n].number << ". OK" << endl;
  
            if (backtrack(letterCount, letterArr, n + 1, word1, word2, word3))
            {
                return true;
            }

            usedNumbers[i] = 0;
        }
    }
    return false;
}

int checkSolution(letter* letterArr, int letterCount, string word1, string word2, string word3)
{
    int val1 = 0, val2 = 0, val3 = 0, m = 1, j, i;
  
    for (i = word1.length() - 1; i >= 0; i--)
    {
        char ch = word1[i];
        for (j = 0; j < letterCount; j++)
        {
            if (letterArr[j].character == ch)
            {
                break;
            }
        }
  
        val1 += m * letterArr[j].number;
        m *= 10;
    }
    m = 1;
  
    for (i = word2.length() - 1; i >= 0; i--)
    {
        char ch = word2[i];
        for (j = 0; j < letterCount; j++)
        {
            if (letterArr[j].character == ch)
            {
                break;
            }
        }

        val2 += m * letterArr[j].number;
        m *= 10;
    }
    m = 1;
  
    for (i = word3.length() - 1; i >= 0; i--)
    {
        char ch = word3[i];
        for (j = 0; j < letterCount; j++)
        {
            if (letterArr[j].character == ch)
            {
                break;
            }
        }
  
        val3 += m * letterArr[j].number;
        m *= 10;
    }
  
    if (val3 == (val1 + val2))
    {
        return 1;
    }
  
    return 0;
}