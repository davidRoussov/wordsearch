#include "InitializeBoard.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

struct convert {
    void operator()(char& c) { c = toupper((unsigned char)c); }
};

InitializeBoard::InitializeBoard(int number_of_special_words, int grid_size)
{
    _number_of_special_words = number_of_special_words;
    _grid_size = grid_size;

    srand(time(NULL));
}

char** InitializeBoard::_createBoard(char** optional_copy_board = NULL)
{
    char** board = 0;
    board = new char*[_grid_size];

    for (int i = 0; i < _grid_size; i++)
    {
        board[i] = new char[_grid_size];

        for (int j = 0; j < _grid_size; j++)
        {
            if (optional_copy_board)
            {
                board[i][j] = optional_copy_board[i][j];
            }
            else
            {
                board[i][j] = NULL;
            }
        }
    }

    return board;
}

void InitializeBoard::printBoard()
{
    for (int x = 0; x < _grid_size; x++)
    {
        for (int y = 0; y < _grid_size; y++)
        {
            if (_board[x][y] == NULL) cout << "* ";
            else cout << _board[x][y] << " ";
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
    for_each(random_word.begin(), random_word.end(), convert());
    int length = random_word.length();
    char** board_copy = _createBoard(_board);

    for (int i = 0; i < length; i++)
    {
        switch(direction)
        {
            case W:
                if ((x - i < 0) || (board_copy[x - i][y] != NULL)) return false;
                else board_copy[x - i][y] = random_word[i];
                break;
            case NW:
                if ((x - i < 0) || (y - i < 0) || (board_copy[x - i][y - i] != NULL)) return false;
                else board_copy[x - i][y - i] = random_word[i];
                break;
            case N:
                if ((y - i < 0) || (board_copy[x][y - i] != NULL)) return false;
                else board_copy[x][y - i] = random_word[i];
                break;
            case NE:
                if ((y - i < 0) || (x + i >= _grid_size) || (board_copy[x + i][y - i] != NULL)) return false;
                else board_copy[x + i][y - i] = random_word[i];
                break;
            case E:
                if ((x + i >= _grid_size) || (board_copy[x + i][y] != NULL)) return false;
                else board_copy[x + i][y] = random_word[i];
                break;
            case SE:
                if ((x + i >= _grid_size) || (y + i >= _grid_size) || (board_copy[x + i][y + i] != NULL)) return false;
                else board_copy[x + i][y + i] = random_word[i];
                break;
            case S:
                if ((y + i >= _grid_size) || (board_copy[x][y + i] != NULL)) return false;
                else board_copy[x][y + i] = random_word[i];
                break;
            case SW:
                if ((x - i < 0) || (y + i >= _grid_size) || (board_copy[x - i][y + i] != NULL)) return false;
                else board_copy[x - i][y + i] = random_word[i];
                break;
            default:
                cout << "invalid direction" << endl;
        }
    }

    _board = board_copy;
    return true;
}

void InitializeBoard::_populateRandomLetters(char** board)
{
    for (int i = 0; i < _grid_size; i++)
    {
        for (int j = 0; j < _grid_size; j++)
        {
            if (board[i][j] == NULL)
            {
                board[i][j] = 'A' + rand() % 26;
            }
        }
    }
}

char** InitializeBoard::generate()
{
    _board = _createBoard();

    vector<string> random_words = _getRandomWords();
    const int number_of_words = random_words.size();
    for (int i = 0; i < _number_of_special_words; i++)
    {
        int random_word_index = rand() % static_cast<int>(number_of_words);
        string random_word = random_words[random_word_index];
        cout << "random word: " << random_word << endl;

        bool validPosition = false;
        while (!validPosition)
        {
            int rand_board_x = rand() % static_cast<int>(_grid_size);
            int rand_board_y = rand() % static_cast<int>(_grid_size);

            Direction direction = static_cast<Direction>(rand() % SW);

            validPosition = _isPositionValid(random_word, direction, rand_board_x, rand_board_y);
        }
    }

    _populateRandomLetters(_board);

    printBoard();
    return _board;
}

