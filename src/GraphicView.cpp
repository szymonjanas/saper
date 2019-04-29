#include "GraphicView.hpp"

GraphicView::GraphicView(MinesweeperBoard* board,
                         sf::RenderWindow* window)
{
    this->board = board;
    this->window = window;
    this->factory = new FieldShapeDrawingFactory (window, board);
    this->converter = new MousePositionConverter (board);
}

GraphicView::GraphicView(sf::RenderWindow* window)
{
    this->window = window;
    this->converter = new MousePositionConverter (board);
}

GraphicView::~GraphicView()
{
    delete factory;
    delete converter;
}

void GraphicView::drawGameStatusInfo(std::string gameStatusInfo, int screenSizeX)
{
    factory->drawGameStatusInfo(gameStatusInfo, 10, 10, screenSizeX);
}

void GraphicView::showBoard()
{
    int x, y;
    for (int countY = 0; countY < board->getBoardHeight(); ++countY)
    {
        for (int countX = 0; countX < board->getBoardWidth(); ++countX)
        {
            x = converter->codeFieldPosition(countX, countY).x;
            y = converter->codeFieldPosition(countX, countY).y;
            switch (board->getFieldInfo(countX, countY))
            {
            case '#':
                factory->drawField(FieldElement::ERROR, x, y);
                break;
            case 'F':
                factory->drawField(FieldElement::FLAG, x, y);
                break;
            case '_':
                factory->drawField(FieldElement::NOT_REVEALED, x, y);
                break;
            case ' ':
                factory->drawField(FieldElement::EMPTY, x, y);
                break;
            case 'x':
                factory->drawField(FieldElement::MINE, x, y);
                break;
            default:
                int numberOfMines = (int)board->getFieldInfo(countX, countY);
                if (numberOfMines > 48 and numberOfMines <= 56 )
                    factory->drawField(FieldElement::NUMBER, x, y);
                break;
            }
        }
    }
}
