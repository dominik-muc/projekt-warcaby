enum GameState{
    BLACK_WIN,
    WHITE_WIN,
    ONGOING,
    WRONG_MOVE
};

enum Symbol{
    BLACK,
    WHITE
};

enum FieldType{
    EMPTY,
    WHITE,
    WHITE_QUEEN,
    BLACK,
    BLACK_QUEEN
};

struct Move{
    int row1;
    int colum1;
    int row2;
    int colum2;
};

struct BoardArray{
    int field[8][8];
};