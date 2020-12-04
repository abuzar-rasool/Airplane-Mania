

class Score {
    int score = 0;

    public:

    // operator overloading for incrementing or decrementing score
    void operator + (const int& incOrDecre);
    // getter for score
    int getScore();
    // resetting score
    void resetScore();

};