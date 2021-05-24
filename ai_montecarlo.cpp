
#include "ai_montecarlo.h"
#include "roadEval.h"
#include <time.h>

int AI_MonteCarlo::move(_hex& board)
{

    if (first) {

        for (int i = board.side() / 4; i <= (board.side() * 3 / 4); i++)
            for (int j = (board.side() / 4) + i * board.side(); j <= (board.side() * 3 / 4) + i * board.side(); j++)
                if (board[j] != tpHex::Empty) {
                    board.set_node(j, color);
                    first = false;
                    return j;
                }
        for (int i = board.side() / 4; i <= (board.side() * 3 / 4); i++)
            for (int j = (board.side() / 4) + i * board.side(); j <= (board.side() * 3 / 4) + i * board.side(); j++)
                board.set_node(j, tpHex::Horiz); //temporary
    }

    _hex cpy_brd(board);
    std::vector <tpHex*> shuf(cpy_brd.all_nodes());
    std::vector <bool> occupied(cpy_brd.all_nodes(), false);
    int my_steps = 0, his_steps = 0;

    for (int i = 0, j = 0; i < cpy_brd.all_nodes(); i++, j++) {
        if (cpy_brd[i] != tpHex::Empty) {
            occupied[i] = true;
            shuf.erase(shuf.begin() + j);
            j--;
            if (cpy_brd[i] != color)
                my_steps++;
            else his_steps++;
        }
        else shuf[j] = &(*cpy_brd.get_pt())[i];
    }
    int best_move;
    int most_wins = -1, win_case = 0;
    unsigned int k = 0;
    if (cpy_brd.all_nodes() % 2 == 0) {
        if (his_steps > my_steps)
            *(shuf[k++]) = color;
    }

    for (; k < shuf.size() / 2; k++)
        *(shuf[k]) = tpHex::Horiz;

    if (cpy_brd.all_nodes() % 2 != 0)
        if (his_steps == my_steps)
            *(shuf[k++]) = color;

    for (; k < shuf.size(); k++)
        *(shuf[k]) = tpHex::Vert;

    tpHex* temp;
    for (int i = 0, j = 0; i < cpy_brd.all_nodes(); i++) {
        win_case = 0;
        if (occupied[i] == false) {
            if (*(shuf[j]) != color) {
                for (k = 0; *(shuf[k]) != color; k++);
                std::swap(*(shuf[j]), *(shuf[k]));
            }
            temp = shuf[j];
            shuf.erase(shuf.begin() + j);

            for (int tests = 0; tests < testing_cases; tests++) {
                shuffl(shuf.begin(), shuf.end(), std::mt19937(time(0)));
                if (test_win_fast(cpy_brd) == color)
                    win_case++;
            }
            if (win_case > most_wins) {
                most_wins = win_case;
                best_move = i;
            }
            shuf.insert(shuf.begin() + j, temp);
            j++;
        }
    }
    board.set_node(best_move, color);

    if (first) {
        first = false;
        for (int i = board.side() / 4; i <= (board.side() * 3 / 4); i++)
            for (int j = (board.side() / 4) + i * board.side(); j <= (board.side() * 3 / 4) + i * board.side(); j++)
                board.set_node(j, tpHex::Empty);
    }
    return best_move;
}


template <class RandomAccessIterator, class URNG>
void AI_MonteCarlo::shuffl(RandomAccessIterator first, RandomAccessIterator last, URNG&& g)
{
    for (auto i = (last - first) - 1; i > 0; --i) {
        std::uniform_int_distribution<decltype(i)> d(0, i);
        std::swap(*(first[i]), *(first[d(g)]));
    }
}
