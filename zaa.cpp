#include "omp/HandEvaluator.h"
#include <iostream>
using namespace omp;
#include <unordered_map>
#include <string>
#include <cmath>
// Create a Hand from a card. CardIdx is an integer between 0 and 51, so that CARD = 4 * RANK + SUIT, where
// rank ranges from 0 (deuce) to 12 (ace) and suit is from 0 (spade) to 3 (diamond).

std::unordered_map<char, int> pip_to_rank = {
    {'2', 0},
    {'3', 1},
    {'4', 2},
    {'5', 3},
    {'6', 4},
    {'7', 5},
    {'8', 6},
    {'9', 7},
    {'T', 8},
    {'J', 9},
    {'Q', 10},
    {'K', 11},
    {'A', 12},
};

std::unordered_map<char, int> suit_to_val = {
    {'S', 0},
    {'H', 1},
    {'C', 2},
    {'D', 3},
};

std::unordered_map<int, std::string> hand_rank_to_name_map = {
    {1, "High Card"},
    {2, "Pair"},
    {3, "Two Pair"},
    {4, "Trips"},
    {5, "Straight"},
    {6, "Flush"},
    {7, "Full House"},
    {8, "Quads"},
    {9, "Straight Flush"},
};

std::string hand_val_to_name(int hand_value)
{
    return hand_rank_to_name_map[std::floor(hand_value / 4096)];
}

int char_to_hand_idx(char pip, char suit)
{
    int rank_val = pip_to_rank[pip];
    int suit_val = suit_to_val[suit];
    int card_idx = 4 * rank_val + suit_val;
    return card_idx;
}

int main()
{
    // aces full of deuces
    HandEvaluator eval;
    Hand h = Hand::empty();                                 // Final hand must include empty() exactly once!
    h += Hand(51) + Hand(48) + Hand(0) + Hand(1) + Hand(2); // AdAs2s2h2c
    std::cout << eval.evaluate(h) << std::endl;             // 28684 = 7 * 4096 + 12

    // Quad aces
    Hand h2 = Hand::empty();                                    // Final hand must include empty() exactly once!
    h2 += Hand(51) + Hand(50) + Hand(49) + Hand(48) + Hand(47); // AdAcAhAsKd
    std::cout << eval.evaluate(h2) << std::endl;                // 28684 = 7 * 4096 + 12

    // quad dueces
    Hand h3 = Hand::empty();                               // Final hand must include empty() exactly once!
    h3 += Hand(0) + Hand(1) + Hand(2) + Hand(3) + Hand(4); // 2s2h2c2d3s
    std::cout << eval.evaluate(h3) << std::endl;           // 28684 = 7 * 4096 + 12

    int hand_val;

    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    int c4 = 0;
    int c5 = 0;

    // royal flush (clubs)
    c1 = char_to_hand_idx('A', 'C');
    c2 = char_to_hand_idx('K', 'C');
    c3 = char_to_hand_idx('Q', 'C');
    c4 = char_to_hand_idx('J', 'C');
    c5 = char_to_hand_idx('T', 'C');

    Hand h4 = Hand::empty();
    h4 += Hand(c1) + Hand(c2) + Hand(c3) + Hand(c4) + Hand(c5);
    hand_val = eval.evaluate(h4);
    std::cout << hand_val << " " << hand_val_to_name(hand_val) << std::endl;

    // royal flush (spades)
    c1 = char_to_hand_idx('A', 'S');
    c2 = char_to_hand_idx('K', 'S');
    c3 = char_to_hand_idx('Q', 'S');
    c4 = char_to_hand_idx('J', 'S');
    c5 = char_to_hand_idx('T', 'S');

    Hand h5 = Hand::empty();
    h5 += Hand(c1) + Hand(c2) + Hand(c3) + Hand(c4) + Hand(c5);
    hand_val = eval.evaluate(h5);
    std::cout << hand_val << " " << hand_val_to_name(hand_val) << std::endl;

    // straight flush (diamonds)
    c1 = char_to_hand_idx('9', 'D');
    c2 = char_to_hand_idx('K', 'D');
    c3 = char_to_hand_idx('Q', 'D');
    c4 = char_to_hand_idx('J', 'D');
    c5 = char_to_hand_idx('T', 'D');

    Hand h6 = Hand::empty();
    h6 += Hand(c1) + Hand(c2) + Hand(c3) + Hand(c4) + Hand(c5);
    hand_val = eval.evaluate(h6);
    std::cout << hand_val << " " << hand_val_to_name(hand_val) << std::endl;

    // straight K-9
    c1 = char_to_hand_idx('9', 'S');
    c2 = char_to_hand_idx('K', 'D');
    c3 = char_to_hand_idx('Q', 'D');
    c4 = char_to_hand_idx('J', 'D');
    c5 = char_to_hand_idx('T', 'D');

    Hand h7 = Hand::empty();
    h7 += Hand(c1) + Hand(c2) + Hand(c3) + Hand(c4) + Hand(c5);
    hand_val = eval.evaluate(h7);
    std::cout << hand_val << " " << hand_val_to_name(hand_val) << std::endl;

    // full house
    c1 = char_to_hand_idx('A', 'D');
    c2 = char_to_hand_idx('A', 'C');
    c3 = char_to_hand_idx('A', 'H');
    c4 = char_to_hand_idx('K', 'H');
    c5 = char_to_hand_idx('K', 'S');

    Hand h8 = Hand::empty();
    h8 += Hand(c1) + Hand(c2) + Hand(c3) + Hand(c4) + Hand(c5);
    hand_val = eval.evaluate(h8);
    std::cout << hand_val << " " << hand_val_to_name(hand_val) << std::endl;

    return 0;
}
