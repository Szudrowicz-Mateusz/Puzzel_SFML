#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define Max_main_menu 4

class MainMenu
{
    public:
    MainMenu(float width,float height);
    ~MainMenu()=default;

    void draw(RenderWindow& window);
    void moveUp();
    void moveDown();

    int mainMenuPressed(){
        return mainMenuSelected;
    }

    private:

    int mainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
    
};