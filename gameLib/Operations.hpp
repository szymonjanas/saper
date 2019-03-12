#pragma once

enum class ShowStatus
{
    LOOSE,
    WIN,
    TABLE,
    CLEAR,
    BOMBS,
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
    NUMBER
};

enum class Level
{
    EASY,
    MEDIUM,
    HARD,
    USER
};
