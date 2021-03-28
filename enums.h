#ifndef ENUMS_H
#define ENUMS_H

enum State
{
    PREPARE,
    PLAYER_MOVE,
    COMPUTER_MOVE,
    TIE,
    PLAYER_WON,
    COMPUTER_WON,
    NONE
};

enum Field {
    COMPUTER,
    PLAYER,
    EMPTY
};

#endif // ENUMS_H
