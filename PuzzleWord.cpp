/**
 * @file PuzzleWord.cpp
 * @author Hussein Khadra
 * @brief A program that looks for words that exist in a crossword puzzle.
 * @version 0.1
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <cstring>

using namespace std;

//max row and column = 20;
//user can only input <= 40 words
//length of word should be <= 20

const int max_row = 20;
const int max_cols = 20;
const int max_word_len = 20;
const int max_words = 40;

struct Word
{
    char word[max_word_len];
    bool found;
    int row,col;
    char direction;
};

void getPuzzle(char[][max_word_len],int,int);
void getWords(Word[],int);
void findWord(char[][max_word_len],Word[],int,int);
void searchWord(char[][max_word_len],Word&,int);
void searchHorizontal(char [][max_word_len],Word &,int);
void searchVertical(char [][max_word_len],Word &,int);
void searchDiagonal(char [][max_word_len],Word &,int);
void searchDiagonalBLtoTR(char [][max_word_len],Word &,int);
void DisplayWords(Word[],int);
void DisplayFindWords(Word[],int);



int main()
{
    int row,col,numOftargetWords;

    char inputWord[max_words][max_word_len];
    Word searchWords[max_words],word;

    cout << "How many rows and columns: ";
    cin >> row;

    col = row;
    int size = row;

    cout << "Enter the characters, " << row << " per row:\n";
    getPuzzle(inputWord,row,col);
   
    
    cout << "How many words should I look for: ";
    cin >> numOftargetWords;

    cout << "\nEnter words to look for: \n";
    getWords(searchWords,numOftargetWords);

    cout << "\n*****HIDDEN WORDS*****\n";
    cout << "************************\n";
    DisplayFindWords(searchWords,numOftargetWords);
    cout << '\n';
    

    findWord(inputWord,searchWords,numOftargetWords,size);

    DisplayWords(searchWords,numOftargetWords);
    return 0;
}


void getPuzzle(char input[][max_word_len],int row,int col)
{    
    for(int i = 0;i < row;i++)
    {
        for(int j = 0;j < col;j++)
        {
            cin >> input[i][j];
        }
    }
}


void getWords(Word searchWord[],int numOfwords)
{
    for(int i = 0;i < numOfwords;i++)
    {
        cin >> searchWord[i].word;
        searchWord[i].found = false;
    }
}


void DisplayFindWords(Word findWords[],int numOfWords)
{
    for(int i = 0;i < numOfWords;i++)
    {
        cout << findWords[i].word << '\n';
    }
}


void findWord(char input[][max_word_len],Word word[],int numOfwords,int size)
{
    for(int i = 0;i < numOfwords;i++)
    {
        searchWord(input,word[i],size);
    }
}


void searchWord(char input[][max_word_len],Word &word,int size)
{
    searchHorizontal(input,word,size);
    if(word.found)
    {
        return;
    }
    searchVertical(input,word,size);
    if(word.found)
    {
        return;
    }
    searchDiagonal(input,word,size);
    if(word.found)
    {
        return;
    }
    searchDiagonalBLtoTR(input,word,size);
    if(word.found)
    {
        return;
    }
}

void DisplayWords(Word word[],int row)
{
    for(int i = 0;i < row;i++)
    {
        cout << word[i].word << "    ";
        if(word[i].found)
        {
            cout << " FOUND at (ROW: " << word[i].row << ",COLUMN: " << word[i].col <<",Direction: ";
            switch(word[i].direction)
            {
                case 'H':
                    cout << "Horizontally)\n";
                break;
                case 'V':
                    cout << "Vertically)\n";
                break;
                case 'D':
                    cout << "Diagonally)\n";
                break;
            }
        }else
        {
            cout << "NOT FOUND\n";
        }
    }
}


void searchHorizontal(char input[][max_word_len],Word &word,int size)
{
    for(int i = 0;i < size;i++)
    {
        for(int j = 0;j < size;j++)
        {
            if(input[i][j] == word.word[0])
            {
                bool match = true;
                for (int k = 1; k < strlen(word.word) && match; k++) {
                    if (j+k >= size || input[i][j+k] != word.word[k]) {
                        match = false;
                    }
                }
                if(match)
                {
                    word.found = true;
                    word.col = j;
                    word.row = i;
                    word.direction = 'H';
                    return;
                }
            }
        }
    }
}


void searchVertical(char input[][max_word_len],Word &word,int size)
{
    for(int i = 0;i < size;i++)
    {
        for(int j = 0;j < size;j++)
        {
            if(input[i][j] == word.word[0])
            {
                bool match = true;
                for (int k = 1; k < strlen(word.word) && match; k++) {
                    if (i+k >= size || input[i+k][j] != word.word[k]) {
                        match = false;
                    }
                }
                if(match)
                {
                    word.found = true;
                    word.col = j;
                    word.row = i;
                    word.direction = 'V';
                    return;
                }
            }
        }
    }
}


void searchDiagonal(char input[][max_word_len],Word &word,int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) 
        {
            if (input[i][j] == word.word[0]) 
            {
                bool match = true;
                for (int k = 1; k < strlen(word.word) && match; k++) 
                {
                    if (i+k >= size || j+k >= size || input[i+k][j+k] != word.word[k]) 
                    {
                        match = false;
                    }
                }
                if(match)
                {
                    word.found = true;
                    word.col = j;
                    word.row = i;
                    word.direction = 'D';
                }
            }
        }
    }   
}

void searchDiagonalBLtoTR(char input[][max_word_len],Word &word,int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        for (int j = 0; j < size; j++) 
        {
            if (input[i][j] == word.word[0]) 
            {
                bool match = true;
                for (int k = 1; k < strlen(word.word); k++) 
                {
                    if (i-k < 0 || j+k >= size || input[i-k][j+k] != word.word[k])
                    {
                        match = false;
                        break;
                    }
                }
                if(match)
                {
                    word.found = true;
                    word.row = i;
                    word.col = j;
                    word.direction = 'D';
                }
            }
        }
    }
}