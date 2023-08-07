#include <SFML/Graphics.hpp>

#include "Menu.hpp"

#include <time.h>
#include <vector>
#include <iostream>

using namespace sf;

/*
Nearly perfect but the isIntersecting() and the checkLvl() have a problem with sprites that
do not take up the entire space of the Image.
So the appointed rectangle is calling the function FALSE but we are seeing that sprite fit easily
*/

void nextLvl(std::vector<Sprite>& sprites,std::array<Texture,4>& tex,int& lvl,int& sprite_size){

    switch(lvl){
        case 0:
            sprites.emplace_back(tex[0]);
    sprites[0].setTextureRect(IntRect(0,0,32,32));
    sprites[0].setOrigin((sf::Vector2f)tex[0].getSize() / 2.f);
    sprites[0].setPosition(96,16);

    sprites.emplace_back(tex[1]);
    sprites[1].setTextureRect(IntRect(0,0,32,32));
    sprites[1].setOrigin((sf::Vector2f)tex[1].getSize() / 2.f);
    sprites[1].setPosition(64,16);

    
    sprites.emplace_back(tex[2]);
    sprites[2].setTextureRect(IntRect(0,0,16,16));
    sprites[2].setOrigin((sf::Vector2f)tex[2].getSize() / 2.f);
    sprites[2].setPosition(16,16);

    sprites.emplace_back(tex[3]);
    sprites[3].setTextureRect(IntRect(0,0,16,16));
    sprites[3].setOrigin((sf::Vector2f)tex[3].getSize() / 2.f);
    sprites[3].setPosition(32,16);
    break;

        case 1:
        sprites.clear();
    sprites.emplace_back(tex[0]);
    sprites[0].setTextureRect(IntRect(0,0,32,32));
    sprites[0].setOrigin((sf::Vector2f)tex[0].getSize() / 2.f);
    sprites[0].setPosition(96,16);

    sprites.emplace_back(tex[1]);
    sprites[1].setTextureRect(IntRect(0,0,32,32));
    sprites[1].setOrigin((sf::Vector2f)tex[1].getSize() / 2.f);
    sprites[1].setPosition(64,16);
    break;
        case 2:
    sprites.clear();
    sprites.emplace_back(tex[1]);
    sprites[1].setTextureRect(IntRect(0,0,32,32));
    sprites[1].setOrigin((sf::Vector2f)tex[1].getSize() / 2.f);
    sprites[1].setPosition(64,16);

    sprites.emplace_back(tex[2]);
    sprites[2].setTextureRect(IntRect(0,0,16,16));
    sprites[2].setOrigin((sf::Vector2f)tex[2].getSize() / 2.f);
    sprites[2].setPosition(16,16);
    break;
    
        case 3:
    sprites.clear();
    sprites.emplace_back(tex[1]);
    sprites[0].setTextureRect(IntRect(0,0,32,32));
    sprites[0].setOrigin((sf::Vector2f)tex[1].getSize() / 2.f);
    sprites[0].setPosition(64,16);

    
    sprites.emplace_back(tex[2]);
    sprites[1].setTextureRect(IntRect(0,0,16,16));
    sprites[1].setOrigin((sf::Vector2f)tex[2].getSize() / 2.f);
    sprites[1].setPosition(16,16);

    sprites.emplace_back(tex[3]);
    sprites[2].setTextureRect(IntRect(0,0,16,16));
    sprites[2].setOrigin((sf::Vector2f)tex[3].getSize() / 2.f);
    sprites[2].setPosition(32,16);
    break;

    case 4:
    sprites.clear();
    break;
    }

    ++lvl;
    sprite_size=sprites.size();
}

inline float left(Sprite& shape)
{
    return shape.getPosition().x - shape.getTextureRect().width / 2.f;
}

inline float right(Sprite& shape)
{
    return shape.getPosition().x + shape.getTextureRect().width / 2.f; 
}

inline float top(Sprite& shape)
{
    return shape.getPosition().y - shape.getTextureRect().height / 2.f;
}

inline float bottom(Sprite& shape)
{
    return shape.getPosition().y + shape.getTextureRect().height / 2.f;
}



inline bool isIntersecting(Sprite& A,Sprite& B)
{
    return right(A)>= left(B) && left(A) <= right(B) && bottom(A) >= top(B) && top(A) <= bottom(B);
}

bool checkLvl(RectangleShape& game,std::vector<Sprite>& sprites,const int game_width,
const int game_length,const int size_s){

                //Checking if The puzzles is in the rectangle
                for(int i=0;i<size_s;i++)
            {
                if(game.getPosition().x+game_width/2>sprites[i].getPosition().x+sprites[i].getTextureRect().width/2 &&
                game.getPosition().x-game_width/2<sprites[i].getPosition().x-sprites[i].getTextureRect().width/2 &&
                game.getPosition().y+game_length/2>sprites[i].getPosition().y+sprites[i].getTextureRect().height/2 &&
                game.getPosition().y-game_length/2<sprites[i].getPosition().y-sprites[i].getTextureRect().height/2)
                continue;
                else return false;
            }

            // Checking if Puzzles dont overlaping
            for(int i=0;i<size_s;i++)
            {
                for(int j=i+1;j<size_s;j++)
                {
                    if(isIntersecting(sprites[i],sprites[j])==true)
                    {
                        return false;
                    }
                }
            }

            
            return true;
}


int main()
{   
    int window_width=320,window_length=480;
    int game_width=200, game_length=200;
    RenderWindow window(VideoMode(window_width, window_length), "The Game!");

    std::array<Texture,4> tex;
    tex[0].loadFromFile("/home/mati/Dokumenty/Puzzle/images/roslina.png");
    tex[1].loadFromFile("/home/mati/Dokumenty/Puzzle/images/Zaba.png");
    tex[2].loadFromFile("/home/mati/Dokumenty/Puzzle/images/krolik.png");
    tex[3].loadFromFile("/home/mati/Dokumenty/Puzzle/images/Waz.png");

    std::vector<Sprite> sprites;
    int size_s=0; //Size of the vector ^
    int lvl=0; //Level of our game
    
    //setSprites(sprites,tex,size_s);
    nextLvl(sprites,tex,lvl,size_s);
            ///Place we are fit our puzzles///
    RectangleShape game;
    game.setFillColor(Color::Green);
    Vector2f game_size(game_width,game_length);
    game.setSize(game_size);
    game.setOrigin(game_size/2.f);
    game.setPosition(window_width/2,window_length/2);

            ///Auxiliary variables///
    bool is_move=false;
    bool next_lvl=false;
    int index=0;

    while (window.isOpen())
    {

                    ///Event: Moving, Rotating, Ecsaping///
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();


                //Chose the sprite to move
                if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left)
                {
                    Vector2f mousePos=Vector2f(Mouse::getPosition(window));
                    
                    //Checking if bound with mouse is overlaping
                    for(int i=0;i<size_s;i++)
                    if(sprites[i].getGlobalBounds().contains(mousePos))
                    {
                        is_move=true;
                        index=i;
                    }
                }

                        ///Moving and Rotating///
                if(is_move)
                {
                        ///Rotating///
                    if (e.type == Event::KeyPressed)
                    {
                        if (e.key.code==Keyboard::Space)
                        {
                            sprites[index].rotate(15.f);      
                        }
                    }

                        ///Moving///
                //Realising mouse button
                if (e.type == Event::MouseButtonReleased)
                if (e.key.code == Mouse::Left)
                 {
                 Vector2f newPos=Vector2f(Mouse::getPosition(window));
                 sprites[index].setPosition(newPos);
                 is_move=false;
                 } 
                }

                        ///Checking Puzzles///
                if (e.type == Event::KeyPressed)
                    if (e.key.code==Keyboard::P)
                        next_lvl=true;

        }



            ///Checking Puzzles///
        if(next_lvl)
        {
           if(checkLvl(game,sprites,game_width,game_length,size_s))
            {
                nextLvl(sprites,tex,lvl,size_s);
            }
            next_lvl=false;
        }

    window.clear(Color::Blue);

    //Draw
    window.draw(game);

    for(auto& s:sprites)
    {
        window.draw(s);
    } 

    window.display();
    }

    return 0;
}