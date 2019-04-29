#include"TextView.hpp"

MSBoardTextView::MSBoardTextView(MinesweeperBoard& board)
{
    this->board = &board;
}

void MSBoardTextView::display()
{
    for (int ycount = 0; ycount < board->getBoardHeight(); ++ycount)
    {
        if (ycount == 0) {
            std::cout << "  ";
            for (int xcount = 0; xcount < board->getBoardWidth(); ++xcount)
            {
                if (xcount < 10) std::cout << " " << xcount << " ";
                if (xcount >= 10) std::cout << xcount << " ";
            }
            std::cout << std::endl;
        }
        for (int xcount = 0; xcount < board->getBoardWidth(); ++xcount)
        {
            if (xcount == 0)
            {
                if (ycount < 10) std::cout << " " << ycount;
                if (ycount >= 10) std::cout << ycount;
            }
            std::cout << " " << board->getFieldInfo(xcount,ycount) << " ";
        }
        std::cout << std::endl;
    }
}

MSTextControler::MSTextControler(MinesweeperBoard& board, MSBoardTextView& view)
{
    this->board = &board;
    this->view = &view;
}

void MSTextControler::play()
{
    GameState state = board->getGameState();
    while (state == GameState::RUNNING)
    {
        board->debug_display();
        view->display();
        std::cout << "   Please write your choise:   " << std::endl;
        std::cout << "       1. Check Field          " << std::endl;
        std::cout << "       2. Make/Remove Flag     " << std::endl;
        std::cout << "       0. EXIT                 " << std::endl;
        int number;
        std::cin >> number;

        int x, y;
        std::cout << "  Please write location (x,y): " << std::endl;
        std::cin >> x;
        std::cin >> y;

        switch (number)
        {
        case 1:
            board->revealField(x, y);
            break;
        case 2:
            board->toggleFlag(x, y);
            break;
        case 0: exit(0);
        }
        state = board->getGameState();
    }
    switch (state)
    {
    case GameState::FINISHED_WIN:
        std::cout << "      Congratulacions!      " << std::endl <<
                     "         You win!           " << std::endl;
        break;
    case GameState::FINISHED_LOOSE:
        std::cout << "           Sorry!            " << std::endl <<
                     "         You loose!          " << std::endl;
        break;
    }
}
