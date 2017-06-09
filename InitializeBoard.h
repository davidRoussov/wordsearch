#include <vector>
#include <string>

enum Direction {W, NW, N, NE, E, SE, S, SW};

class InitializeBoard
{
    private:
        int _number_of_special_words;
        int _grid_size;
        char** _board;

        void _createRandomBoard();
        std::vector<std::string> _getRandomWords();
        bool _isPositionValid(std::string random_word, Direction direction, int x, int y);

    public:
        InitializeBoard(int number_of_special_words, int grid_size);

        void printBoard();
        char** generate();
};