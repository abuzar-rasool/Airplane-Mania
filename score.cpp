#include "score.hpp"

// operator overloading for incrementing and decrementing score
void Score::operator + (const int& incOrDecre) {
        score = score + incOrDecre;
    }

// return the current score
int Score::getScore() {
        return score;
    }

// resets the current score
void Score::resetScore() {
        score = 0;
    }

