#ifndef ROADEVAL_H
#define ROADEVAL_H

#include "_hex.h"

inline tpHex Djikstra_path(int i, _hex& h)
{
    tpHex color = h[i];
    std::vector <bool> visited(h.all_nodes(), false);
    std::vector <int> queue = { i };
    for (; queue.size() != 0; ) {
        i = queue.back();
        queue.pop_back();
        visited[i] = true;
        if (h.is_lower(i) && color == tpHex::Vert) {
            return tpHex::Vert;
        }
        else if (h.is_right(i) && color == tpHex::Horiz) {
            return tpHex::Horiz;
        }
        for (int j = 0, k; j < 6; j++) {
            switch (j) {
            case 0:
                if (!h.is_upper(i) && !h.is_left(i)) {
                    k = i - (h.side() + 1);
                    break;
                }
                j++;
            case 1:
                if (!h.is_upper(i)) {
                    k = i - h.side();
                    break;
                }
                j++;
            case 2:
                if (!h.is_right(i)) {
                    k = i + 1;
                    break;
                }
                j++;
            case 3:
                if (!h.is_lower(i) && !h.is_right(i)) {
                    k = i + (h.side() + 1);
                    break;
                }
                j++;
            case 4:
                if (!h.is_lower(i)) {
                    k = i + h.side();
                    break;
                }
                j++;
            case 5:
                if (!h.is_left(i)) {
                    k = i - 1;
                    break;
                }
                j++;
            }
            if (j<6)
                if (!visited[k]) {
                    if (h[k] == color) {
                        queue.push_back(k);
                    }
                }
        }
    }
    return tpHex::Empty;
}

inline tpHex test_win_path(_hex & h)
{
    for (int i = 0, j = 0; i < h.side(); i++, j += h.side()) {
        if (h[i] == tpHex::Vert)
            if (Djikstra_path(i, h) == tpHex::Vert)
                return tpHex::Vert;
        if (h[j] == tpHex::Horiz)
            if (Djikstra_path(j, h) == tpHex::Horiz)//horiz
                return tpHex::Horiz;
    }
    return tpHex::Empty;
}

inline tpHex test_win_fast(_hex &h)
{
    for (int i = 0; i < h.side(); i++)
        if (h[i] == tpHex::Vert)
            if (Djikstra_path(i, h) == tpHex::Vert)
                return tpHex::Vert;
    return tpHex::Horiz;
}

#endif // ROADEVAL_H
