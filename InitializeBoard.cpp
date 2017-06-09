#include "InitializeBoard.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// vector<string> current_words;

// void temp()
// {

//     const int number_of_words = data.size();
//     for (int i = 0; i < NUMBER_SPECIAL_WORDS; i++)
//     {
//         int random_word_index = rand() % static_cast<int>(number_of_words);
//         string random_word = data[random_word_index];


//         bool validPosition = false;
//         while (!validPosition)
//         {
//             const int rand_board_x = rand() % static_cast<int>(GRID_SIZE);
//             const int rand_board_y = rand() % static_cast<int>(GRID_SIZE);

//             Direction direction = static_cast<Direction>(rand() % SW);

//             validPosition = isPositionValid(direction, rand_board_x, rand_board_y);
//         }
        
//     }



//     // for (vector<string>::const_iterator i = data.begin(); i != data.end(); ++i)
//     // {
//     //    // cout << *i << endl;
//     // }

// }

InitializeBoard::InitializeBoard(int number_of_special_words, int grid_size)
{
    _number_of_special_words = number_of_special_words;
    _grid_size = grid_size;

    srand(time(NULL));
}

void InitializeBoard::_createRandomBoard()
{
    char** board = 0;
    board = new char*[_grid_size];

    for (int i = 0; i < _grid_size; i++)
    {
        board[i] = new char[_grid_size];

        for (int j = 0; j < _grid_size; j++)
        {
            //char random_letter = 'A' + rand() % 26;
            board[i][j] = NULL;
        }
    }

    _board = board;
}

void InitializeBoard::printBoard()
{
    for (int x = 0; x < _grid_size; x++)
    {
        for (int y = 0; y < _grid_size; y++)
        {
            cout << _board[x][y] << " ";
        }
        cout << endl;
    }
}

vector<string> InitializeBoard::_getRandomWords()
{
    vector <string> data;
    ifstream infile("random_words.txt");

    while (infile)
    {
        string allwords;
        if (!getline( infile, allwords )) break;

        string partial_word = "";
        for (char &c : allwords)
        {
            if (c == ',')
            {
               data.push_back(partial_word);
               partial_word = "";
            }
            else
            {
                partial_word += c;
            }
        }
    }
    if (!infile.eof())
    {
        cerr << "Fooey!\n";
    }

    return data;
}

bool InitializeBoard::_isPositionValid(string random_word, Direction direction, int x, int y)
{
    int length = random_word.length();
    char** board_copy = _board;

    switch(direction) {
        case W:
            for (int i = 1; i <= length; i++)
            {
                if (board_copy[x - i][y] == NULL)
                {
                    cout << "yayayay" << endl;
                }
                else
                {
                    cout << "ggg" << endl;
                }
            }
            break;
    }


    return true;
}

char** InitializeBoard::generate()
{
    _createRandomBoard();

    vector<string> random_words = _getRandomWords();
    const int number_of_words = random_words.size();
    cout << "Number of random words: " << number_of_words << endl;
    for (int i = 0; i < _grid_size; i++)
    {
        int random_word_index = rand() % static_cast<int>(number_of_words);
        string random_word = random_words[random_word_index];

        bool validPosition = false;
        while (!validPosition)
        {
            int rand_board_x = rand() % static_cast<int>(_grid_size);
            int rand_board_y = rand() % static_cast<int>(_grid_size);

            Direction direction = static_cast<Direction>(rand() % SW);

            validPosition = _isPositionValid(random_word, direction, rand_board_x, rand_board_y);
        }
    }

    printBoard();
    return _board;
}

