#include <iostream>
#include <SFML/Window.h>
#include <vector>
#include<SFML/Graphics.hpp>
#include<time.h>
#include<SFML/Window.hpp>
#include<SFML/Graphics.h>
#include<Menu.h>

using namespace sf;
using namespace std;

int main()
{



    RenderWindow screen(VideoMode(800, 600), "SFML Works!");
    screen.display();

    while(screen.isOpen())
    {
        screen.clear(Color::Green);

        RectangleShape rectangle;
        rectangle.setSize(Vector2f(800, 600));
        rectangle.setOutlineColor(Color::Yellow);
        rectangle.setFillColor(Color::Yellow);
        screen.draw(rectangle);



        CircleShape shape(50);

        // set the shape color to green
        shape.setFillColor(Color::Red);
        screen.draw(shape);


        for (clock_t fr = clock(); clock() - fr < 250000;  )
        { cout << "sec: " << clock() - fr << endl;}
        screen.close();
    }
}
