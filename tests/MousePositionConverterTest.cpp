#include "catch.hpp"

#include "MousePositionConverter.hpp"
#include "MinesweeperBoardModel.hpp"

SCENARIO("Converter can convert mouse position to model and model to view", "[converter]")
{
    GIVEN ("Board with degub mode and size of graphic board details")
    {
        MinesweeperBoard board(GameMode::DEBUG);
        MousePositionConverter converter(&board);

        WHEN ("Decode from view to model - LEFT SIDE")
        {
            THEN("Field in LEFT TOP corner,no 0x 0y, left top edge")
            {
                REQUIRE(converter.decodeMousePosition(10,10).x == 0);
                REQUIRE(converter.decodeMousePosition(10,10).y == 0);
            }
            THEN("Field in LEFT TOP corner,no 0x 0y, middle")
            {
                REQUIRE(converter.decodeMousePosition(20,20).x == 0);
                REQUIRE(converter.decodeMousePosition(20,20).y == 0);
            }
            THEN("Field in LEFT TOP corner,no 0x 0y, right bottom edge")
            {
                REQUIRE(converter.decodeMousePosition(40,40).x == 0);
                REQUIRE(converter.decodeMousePosition(40,40).y == 0);
            }

            THEN("Field in LEFT BOTTOM corner,no 0x 6y, right top edge")
            {
                REQUIRE(converter.decodeMousePosition(10,250).x == 0);
                REQUIRE(converter.decodeMousePosition(10,250).y == 6);
            }
            THEN("Field in LEFT BOTTOM corner,no 0x 6y, middle")
            {
                REQUIRE(converter.decodeMousePosition(20,260).x == 0);
                REQUIRE(converter.decodeMousePosition(20,260).y == 6);
            }
            THEN("Field in LEFT BOTTOM corner,no 0x 6y, right bottom edge")
            {
                REQUIRE(converter.decodeMousePosition(40,280).x == 0);
                REQUIRE(converter.decodeMousePosition(40,280).y == 6);
            }
        }

        WHEN ("Decode from view to model - RIGHT SIDE")
        {
            THEN("Field in RIGHT TOP corner,no 6x 0y, left top edge")
            {
                REQUIRE(converter.decodeMousePosition(250,10).x == 6);
                REQUIRE(converter.decodeMousePosition(250,10).y == 0);
            }
            THEN("Field in RIGHT TOP corner,no 6x 0y, middle")
            {
                REQUIRE(converter.decodeMousePosition(270,20).x == 6);
                REQUIRE(converter.decodeMousePosition(270,20).y == 0);
            }
            THEN("Field in RIGHT TOP corner,no 6x 0y , right bottom edge")
            {
                REQUIRE(converter.decodeMousePosition(280,40).x == 6);
                REQUIRE(converter.decodeMousePosition(280,40).y == 0);
            }

            THEN("Field in RIGHT BOTTOM corner,no 8x 6y, right top edge")
            {
                REQUIRE(converter.decodeMousePosition(330, 250).x == 8);
                REQUIRE(converter.decodeMousePosition(330, 250).y == 6);
            }
            THEN("Field in RIGHT BOTTOM corner,no 8x 6y, middle")
            {
                REQUIRE(converter.decodeMousePosition(350, 270).x == 8);
                REQUIRE(converter.decodeMousePosition(350, 270).y == 6);
            }
            THEN("Field in RIGHT BOTTOM corner,no 8x 6y, right bottom edge")
            {
                REQUIRE(converter.decodeMousePosition(360, 280).x == 8);
                REQUIRE(converter.decodeMousePosition(360, 280).y == 6);
            }
        }

        WHEN("Code from model to view - LEFT SIDE")
        {
            THEN ("Field in LEFT TOP corner, no 0x 0y")
            {
                REQUIRE(converter.codeFieldPosition(0,0).x == 10);
                REQUIRE(converter.codeFieldPosition(0,0).y == 10);
            }
            THEN ("Field in LEFT BOTTOM corner, no 0x 6y")
            {
                REQUIRE(converter.codeFieldPosition(0,6).x == 10);
                REQUIRE(converter.codeFieldPosition(0,6).y == 250);
            }
        }
        WHEN("Code from model to view - RIGHT SIDE")
        {
            THEN ("Field in RIGHT TOP corner, no 8x 0y")
            {
                REQUIRE(converter.codeFieldPosition(8,0).x == 330);
                REQUIRE(converter.codeFieldPosition(8,0).y == 10);
            }
            THEN ("Field in RIGHT BOTTOM corner, no 8x 6y")
            {
                REQUIRE(converter.codeFieldPosition(8,6).x == 330);
                REQUIRE(converter.codeFieldPosition(8,6).y == 250);
            }
        }

    }
}
