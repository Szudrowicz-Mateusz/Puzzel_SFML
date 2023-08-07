#include "Menu.hpp"

MainMenu::MainMenu(float width, float heigth){

    if(!font.loadFromFile("/home/mati/Dokumenty/Puzzle/Terserah.ttf"));
        cout<<"No font is here";

    //Play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(width/2,200);

    //Options
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("Options");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(width/2,300);

    //About
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("About");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(width/2,400);

    //Exit
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("Exit");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(width/2,500);

    mainMenuSelected=-1;
}

void MainMenu::draw(RenderWindow& window){

    for(int i=0;i<Max_main_menu;i++){
        window.draw(mainMenu[i]);
    }
}

void MainMenu::moveUp(){

    if(mainMenuSelected-1>=0){

        mainMenu[mainMenuSelected].setFillColor(Color::White);

        --mainMenuSelected;
        if(mainMenuSelected==-1){
            mainMenuSelected=2;
        }

        mainMenu[mainMenuSelected].setFillColor(Color::Blue);

    }
}

void MainMenu::moveDown(){

    if(mainMenuSelected+1<=Max_main_menu)
    {
        mainMenu[mainMenuSelected].setFillColor(Color::White);

        ++mainMenuSelected;

        if(mainMenuSelected==4){
            mainMenuSelected=0;
        }

        mainMenu[mainMenuSelected].setFillColor(Color::Blue);
    }
}