#pragma once

enum class ShowStatus
{
    LOOSE,
    WIN,
    TABLE,
    CLEAR,
    SHOW_BOARD,
    SCORES
};

enum class OperationOnField
{
    CHECK_FIELD,
    MAKE_FLAG,
    DELETE_FLAG
};

enum class FieldStatus
{
    FLAG,
    HIDDEN,
    EMPTY,
    BOMB,
    NUMBER,
    ERROR,
    BLOW_UP
};

enum class Level
{
    EASY,
    MEDIUM,
    HARD,
    USER
};

enum class GameStatus
{
    RUNNING,
    FINISH_WIN,
    FINISH_LOOSE
};

enum class Debug
{
    DEBUG
};

enum class Layer
{
    CONSOLE,
    GRAPHIC
};
