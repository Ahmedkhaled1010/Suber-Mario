#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include <fstream>
#include <iostream>
#include "menu.h"
#include <string>
using namespace std;
using namespace sf;
sf::Texture g, playertex, castle;
sf::Sprite  d, s_castle, s_mash;

RectangleShape walk1, walk2, walk3, walk4, walk5, walk6, _pipe[8], Up_walk[8], Down_walk[8], pipe8, pipe1, pipe5, ccccc;
int x_mario_r = 0, y_mario = 0, x_mario_l = 61;
int   y = 0, n = 11, i = 1, life = 0, count_ = 0, coins_count = 0;
const float gravity = 0.015f;
int groundheight = 945;
float movespeed = 1.0f, jumpspeed = 3.0f;
Vector2f velocity;
const float speed = 2.f;
bool jumping = false, jump = false, life_ = false;
RectangleShape dof[4], player(Vector2f(60, 110));
Texture dof_[4];
RectangleShape daid[4], right_walk[16], left_walk[16];
RectangleShape pay[5];
RectangleShape doc[4];
Texture doc_[4];
RectangleShape daid_d[4];
RectangleShape marsh(Vector2f(50.0f, 50.0f));
Texture  marsh_;
bool  v_ = false, o = false, m[4] = { false,false,false,false }, dd[4] = { false,false,false,false }, dd_[4] = { false,false,false,false };
bool v_d[4] = { false,false,false,false };
int big = 0, q = 0, b = 0;
float c = 0;
float dt;
void screen()
{
    if (!g.loadFromFile("back.PNG")) {
        cout << "error" << endl;
    }
    d.setTexture(g);
    if (!castle.loadFromFile("castle.PNG")) {
        cout << "rr";
    }
    s_castle.setTexture(castle);
    s_castle.setPosition(6300, 574);
    if (!playertex.loadFromFile("bb.PNG")) {
        cout << "error" << endl;
    }

    player.setTexture(&playertex);

}
void photo_map()
{

    for (int i = 0; i < 4; i++)
    {
        dof_[i].loadFromFile("kk.png");
        dof[i].setTexture(&dof_[i]);
        doc_[i].loadFromFile("doc.png");
        doc[i].setTexture(&doc_[i]);
    }
    if (!marsh_.loadFromFile("9.PNG")) {
        cout << "error";
    }
    marsh.setTexture(&marsh_);
    marsh.setPosition(2970, 590);
    /*marsh.setPosition(300, 590);*/

}
void dofdaa()
{
    Vector2u textsize = dof_[0].getSize();
    textsize.x /= 3;
    textsize.y /= 1;
    Vector2u textsize_d = doc_[0].getSize();
    textsize_d.x /= 4;
    textsize_d.y /= 2;
    for (int i = 0; i < 4; i++)
    {
        if (((player.getGlobalBounds().intersects(dof[i].getGlobalBounds()) && m[i] == false)) || (player.getGlobalBounds().intersects(doc[i].getGlobalBounds()) && dd[i] == false))
        {
            if (c >= 1)
                big = 3;
            if (big == 1)
                big = 2;
            if ((big == 3 || big == 0) && o == 0)
            {
                o = true;
                player.move(0.0f, -500.0f);
                life++;

            }
        }
        if (big <= 3)
        {
            q = dof[3].getPosition().x;
            if (q >= 3800)
                v_ = false;
            else if (q <= 3600)
                v_ = true;
            if (b < 2)
            {
                if (m[i] == false)
                {
                    dof[i].setTextureRect(IntRect(textsize.x * b, textsize.y * 0, textsize.x, textsize.y));

                    if (v_ == false)
                    {
                        dof[i].move(-2.0f, 0.0f);
                        daid[i].move(-2.0f, 0.0f);
                    }
                    else if (v_ == true)
                    {
                        dof[i].move(2.0f, 0.0f);
                        daid[i].move(2.0f, 0.0f);
                    }
                }
            }
            for (int n = 7; n < 14; n++)
            {
                if (doc[i].getGlobalBounds().intersects(right_walk[n].getGlobalBounds()))
                {
                    v_d[i] = true;
                }
                if (doc[i].getGlobalBounds().intersects(left_walk[n].getGlobalBounds()))
                {
                    v_d[i] = false;
                }
                if (dd[i] == false)
                {
                    if (v_d[i] == false)
                    {
                        if (dd_[i] == false)
                        {
                            doc[i].setTextureRect(IntRect(textsize_d.x * b, textsize_d.y * 0, textsize_d.x, textsize_d.y));
                        }
                        doc[i].move(-0.70f, 0.0f);
                        daid_d[i].move(-0.70f, 0.0f);
                    }
                    else if (v_d[i] == true)
                    {
                        if (dd_[i] == false)
                        {
                            doc[i].setTextureRect(IntRect(textsize_d.x * (b + 2), textsize_d.y * 1, textsize_d.x, textsize_d.y));
                        }
                        doc[i].move(0.40f, 0.0f);
                        daid_d[i].move(0.40f, 0.0f);
                    }
                }
            }
        }
        if (player.getGlobalBounds().intersects(daid[i].getGlobalBounds()) && jump == true && o == false && m[i] == false)
        {

            m[i] = true;
            dof[i].move(0.0f, 0.0f);
            daid[i].move(0.0f, 0.0f);
            dof[i].setTextureRect(IntRect(textsize.x * 2, textsize.y * 0, textsize.x, textsize.y));
            count_ += 10;
        }
        if (player.getGlobalBounds().intersects(daid_d[i].getGlobalBounds()) && jump == true && o == false && dd[i] == false)
        {
            dd_[i] = true;
            if (y == 0)
                player.move(70.0f, -20.0f);
            else
                player.move(-70.0f, -20.0f);
            dd[i] = true;
            doc[i].move(0.0f, 0.0f);
            daid_d[i].move(0.0f, 0.0f);
            doc[i].setTextureRect(IntRect(textsize_d.x * 3, textsize_d.y * 0, textsize_d.x, textsize_d.y));
            count_ += 10;
        }
        if (player.getGlobalBounds().intersects(doc[i].getGlobalBounds()) && o == false && dd[i] == true)
        {
            if (player.getPosition().x > doc[i].getPosition().x)
            {
                v_d[i] = false;
                player.move(50, 0);
            }
            else
            {
                v_d[i] = true;
                player.move(-50, 0);
            }
            dd[i] = false;
        }
        if (player.getPosition().x > dof[i].getPosition().x + 200 && m[i] == true)
        {
            dof[i].setTextureRect(IntRect(textsize.x * 3, textsize.y * 0, textsize.x, textsize.y));
        }
        if (player.getGlobalBounds().intersects(daid_d[i].getGlobalBounds()) && jump == true && o == false && dd[i] == true)
        {
            doc[i].move(0.0f, 55.0f);
        }
    }
    b++;
    if (b == 2)
    {
        b = 0;
    }
    if (player.getGlobalBounds().intersects(ccccc.getGlobalBounds()) && (big == 0 || big == 1 || big == 2 || big == 3) && life < 3)
    {
        o = true;
        player.move(0.0f, -500.0f);
        life++;
    }
}
void marsho()
{
    Vector2u text = marsh_.getSize();;
    text.x /= 3;
    text.y /= 1;
    if (big == 2)
    {
        c = c + .01;

    }
    if (big == 0)
        marsh.setTextureRect(IntRect(text.x * 1, text.y * 0, text.x, text.y));
    //marsh.move(-1.0f, 0.0f);
    if (player.getGlobalBounds().intersects(marsh.getGlobalBounds()) && o == 0 && big == 0)
        big = 1;
    else
    {
        if (big == 1 || big == 2 || big == 3)
            marsh.setTextureRect(IntRect(text.x * 3, text.y * 0, text.x, text.y));
    }

}
RectangleShape walk_bounded(float width, float height, float x, float y)
{
    sf::RectangleShape walk_bottom(sf::Vector2f(width, height));

    walk_bottom.setPosition(x, y);
    return walk_bottom;
}
void mario_move()
{

    walk1 = walk_bounded(1127, 1, 0, 967);
    walk2 = walk_bounded(784, 1, 1345, 967);
    walk3 = walk_bounded(727, 1, 4505, 967);
    walk4 = walk_bounded(1909, 1, 2350, 967);
    walk5 = walk_bounded(2499, 1, 5470, 967);
    int count = 0;
    RectangleShape s, d;
    d = walk_bounded(5000, 1, 0, 530);
    Vector2u textsize = playertex.getSize();
    textsize.x /= 13;
    textsize.y /= 4;
    if ((player.getGlobalBounds().intersects(walk1.getGlobalBounds()) || player.getGlobalBounds().intersects(walk2.getGlobalBounds())
        || player.getGlobalBounds().intersects(walk3.getGlobalBounds()) || player.getGlobalBounds().intersects(walk4.getGlobalBounds()) ||
        player.getGlobalBounds().intersects(walk5.getGlobalBounds()) || player.getGlobalBounds().intersects(pipe1.getGlobalBounds()) ||
        player.getGlobalBounds().intersects(pipe5.getGlobalBounds()) || player.getGlobalBounds().intersects(pipe8.getGlobalBounds())
        || ((player.getGlobalBounds().intersects(Up_walk[0].getGlobalBounds()) || player.getGlobalBounds().intersects(Up_walk[1].getGlobalBounds()) ||
            player.getGlobalBounds().intersects(Up_walk[2].getGlobalBounds()) || player.getGlobalBounds().intersects(Up_walk[3].getGlobalBounds()) ||
            player.getGlobalBounds().intersects(Up_walk[4].getGlobalBounds()) || player.getGlobalBounds().intersects(Up_walk[5].getGlobalBounds()) ||
            player.getGlobalBounds().intersects(Up_walk[6].getGlobalBounds()) || player.getGlobalBounds().intersects(Up_walk[7].getGlobalBounds())
            /*&&player.getGlobalBounds().intersects(s_cbox[0].getGlobalBounds())*/)) ||
        player.getGlobalBounds().intersects(_pipe[0].getGlobalBounds()) || player.getGlobalBounds().intersects(_pipe[1].getGlobalBounds()) ||
        player.getGlobalBounds().intersects(_pipe[2].getGlobalBounds()) || player.getGlobalBounds().intersects(_pipe[3].getGlobalBounds()) ||
        player.getGlobalBounds().intersects(_pipe[4].getGlobalBounds()) || player.getGlobalBounds().intersects(_pipe[5].getGlobalBounds())) && o == false)
    {

        jumping = true;
        jump = false;
    }
    if (o == true)
    {
        player.setTextureRect(IntRect(textsize.x * 6, textsize.y * 1, textsize.x, textsize.y));
    }
    if (y == 0 && o == false)
    {
        if (big == 0 || big == 2)
            player.setTextureRect(IntRect(textsize.x * 0, textsize.y * 1, textsize.x, textsize.y));
        else if (big == 1)
            player.setTextureRect(IntRect(textsize.x * 0, textsize.y * 0, textsize.x, textsize.y));
    }
    if (y == 1 && o == false)
    {
        if (big == 0 || big == 2)
            player.setTextureRect(IntRect(textsize.x * 12, textsize.y * 2, textsize.x, textsize.y));
        else if (big == 1)
            player.setTextureRect(IntRect(textsize.x * 12, textsize.y * 3, textsize.x, textsize.y));
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right) && o == false)
    {
        s = walk_bounded(1, 665, 5000, 0);
        if (player.getGlobalBounds().intersects(s.getGlobalBounds()))
            player.move(0.0f, 0.0f);
        else
        {
            velocity.x += speed * dt;
            y = 0;
            if (big == 0 || big == 2)
            {
                player.setTextureRect(IntRect(textsize.x * i, textsize.y * 1, textsize.x, textsize.y));
                if (i >= 3)
                    i = 1;
                i++;
            }
            if (big == 1)
            {
                player.setTextureRect(IntRect(textsize.x * i, textsize.y * 0, textsize.x, textsize.y));
                if (i >= 3)
                    i = 1;
                i++;
            }

        }
        player.move(1.9, 0);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Left) && o == false)
    {
        s = walk_bounded(1, 665, 50, 0);
        if (player.getGlobalBounds().intersects(s.getGlobalBounds()))
            player.move(0.0f, 0.0f);
        else
        {
            {
                velocity.x += -speed * dt;
                y = 1;
                if (big == 0 || big == 2)
                {
                    player.setTextureRect(IntRect(textsize.x * n, textsize.y * 2, textsize.x, textsize.y));
                    if (n <= 9)
                        n = 11;
                    n--;
                }
                if (big == 1)
                {
                    player.setTextureRect(IntRect(textsize.x * n, textsize.y * 3, textsize.x, textsize.y));
                    if (n <= 9)
                        n = 11;
                    n--;
                }

            }
        }
        player.move(-1.9, 0);
    }
    /* else
     {
         velocity.x = 0;
     }*/


    if (Keyboard::isKeyPressed(Keyboard::Key::Space) && o == false && jumping == true)
    {
        velocity.y += -speed * dt;
        jump = true;
        //jumping = false;

        if (big == 0 || big == 2)
        {
            if (y == 0)
                player.setTextureRect(IntRect(textsize.x * 5, textsize.y * 1, textsize.x, textsize.y));
            if (y == 1)
                player.setTextureRect(IntRect(textsize.x * 7, textsize.y * 2, textsize.x, textsize.y));
        }
        else if (big == 1)
        {
            if (y == 0)
                player.setTextureRect(IntRect(textsize.x * 5, textsize.y * 0, textsize.x, textsize.y));
            if (y == 1)
                player.setTextureRect(IntRect(textsize.x * 7, textsize.y * 3, textsize.x, textsize.y));
        }
        player.move(0, -10);
    }

    /* if (player.getPosition().y + player.getSize().y < groundheight || velocity.y < 0) {
         velocity.y += gravity;
     }
     else
     {
         player.setPosition(player.getPosition().x, groundheight - player.getPosition().y);
     }
     if ((player.getGlobalBounds().intersects(walk1.getGlobalBounds()) || player.getGlobalBounds().intersects(walk2.getGlobalBounds())
         || player.getGlobalBounds().intersects(walk3.getGlobalBounds()) || player.getGlobalBounds().intersects(walk4.getGlobalBounds()) ||
         player.getGlobalBounds().intersects(walk5.getGlobalBounds()))) {
         count =0;
     }*/
}
//void mario_move()
//{
//    velocity.x = 0.f;
//    velocity.y = 0.f;
//    RectangleShape bounded;
//   
//   
//    
//    Vector2u textsize = playertex.getSize();
//
//    textsize.x /= 62;
//    textsize.y /= 2;
//    player.setTextureRect(IntRect(textsize.x * x_mario_l, textsize.y * y_mario, textsize.x, textsize.y));
//    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//
//        player.setTextureRect(IntRect(textsize.x * 0, textsize.y * 0, textsize.x, textsize.y));
//
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//    {
//        bounded = walk_bounded(1, 1090, 2, 0);
//        if (player.getGlobalBounds().intersects(bounded.getGlobalBounds()))
//        {
//
//            player.move(0, 0);
//        }
//        else {
//            velocity.x -= speed * dt;
//            player.setTextureRect(IntRect(textsize.x * x_mario_r, textsize.y * y_mario, textsize.x, textsize.y));
//            y_mario = 1;
//
//            if (x_mario_r <= 62) {
//                x_mario_r++;
//            }
//            else if (x_mario_r > 62) {
//                x_mario_r = 0;
//
//
//            }
//
//        }
//
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//        bounded = walk_bounded(1, 1090, 7455, 0);
//        if (player.getGlobalBounds().intersects(bounded.getGlobalBounds())) {
//            player.move(0, 0);
//        }
//        else {
//          /* velocity.x += speed * dt;*/
//            player.move(30, 0);
//            player.setTextureRect(IntRect(textsize.x * x_mario_r, textsize.y * y_mario, textsize.x, textsize.y));
//            y_mario = 0;
//            if (x_mario_r <= 61) {
//                x_mario_r++;
//            }
//            else if (x_mario_r >= 61) {
//                x_mario_r = 0;
//
//
//            }
//
//        }
//    }
//    
//
//    if (Keyboard::isKeyPressed(Keyboard::Key::Space))
//    {
//        velocity.y += -speed * dt;
//    }
//   /* if (Keyboard::isKeyPressed(Keyboard::Key::Space) && (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))) {
//        velocity.y += -speed * dt;
//        velocity.x += speed * dt;
//    }*/
//    player.move(velocity);
//}

int uhigh_score(int x)
{
    int highscore;
    fstream pointz;
    pointz.open("High score.txt", ios::in);
    pointz >> highscore;
    pointz.close();
    pointz.open("High score.txt");
    if (x > highscore) {
        highscore = x;
    }
    pointz << highscore;
    pointz.close();
    return highscore;
}

int main()
{ //window and image ال view يعني 
    RenderWindow win(VideoMode(1930, 1090), "Mario_GAME_GEN28");
    menu menu(win.getSize().x, win.getSize().y);
    sf::Texture menu_, back1, won;
    int yc = 0, time_coin[14] = { 0 };
    Clock coin_clock[14];
    Time time__[14];
    int x_[24] = { 0 }, y_[24] = { 0 }, x__[50] = { 0 }, y__[50] = { 0 }, life_count = 3, second = 0, menute = 0, second_ = 0, menute_ = 0, u_second1 = 0, u_second2 = 0;
    string scorestr, highstr, coinstr, lifestr, timestr, over, time_str, timestr1, timestr2;
    photo_map();
    SoundBuffer so_jump, so_under, so_game_over, so_marsho, so_box, so_end;
    Sound ss_jump, ss_under, ss_game_over, ss_marsho, ss_box, ss_end;
    if (!so_jump.loadFromFile("jump.ogg"))
    {
        cout << " ";
    }
    ss_jump.setBuffer(so_jump);
    if (!so_end.loadFromFile("end.ogg"))
    {
        cout << " ";
    }
    ss_end.setBuffer(so_end);
    if (!so_box.loadFromFile("block.ogg"))
    {
        cout << " ";
    }
    ss_box.setBuffer(so_box);
    if (!so_under.loadFromFile("Underground.ogg"))
    {
        cout << " ";
    }
    ss_under.setBuffer(so_under);
    if (!so_game_over.loadFromFile("game-over2.ogg"))
    {
        cout << "err";
    }
    ss_game_over.setBuffer(so_game_over);
    if (!so_marsho.loadFromFile("marsho.ogg"))
    {
        cout << "err";
    }
    ss_marsho.setBuffer(so_marsho);
    if (!menu_.loadFromFile("menu.PNG")) {
        cout << "ddd";
    }
    sf::Sprite s_menu, won_;
    s_menu.setTexture(menu_);
    screen();
    Time u_time;
    Text text_[14];
    Font _font;
    int win_height = 1090, win_width = 1930, x = 0, y = 0, x1 = 0, width = 6000, height = 1030;
    int x_enenmy = 0, y_enemy = 0, draw_ = 0;
    Clock clock, _clock;
    bool c_draw[14];
    float time[3] = { 0,0,0 };
    bool time_[3] = { false,false,false };
    sf::Texture walk, __coin;
    Vector2i screen(1930, 1090);
    for (int i = 0; i < 4; i++)
    {
        daid[i].setSize(Vector2f(20.0f, 1.0f));
        dof[i].setSize(Vector2f(50.0f, 50.0f));
        doc[i].setSize(Vector2f(50.0f, 50.0f));
        daid_d[i].setSize(Vector2f(40.0f, 1.0f));
    }
    // التحديد

    win.setFramerateLimit(60);
    //اول واجهة
    sf::RectangleShape back_1(Vector2f(3600, 1100));
    sf::Texture  box, coins, pipe, enemey, box2, BOX, nBOX, c_box, about;
    RectangleShape  pipe2, pipe3, pipe4, pipe6, pipe7, pipe9;
    SoundBuffer so_coin, so_pipe, so_start, so_play;
    Sound sso_coin[24], ss_coin[50], sso_pipe, sso_start, sso_play;
    sf::Sprite  s_coins[12], s_pipe, s_enemy, s_BOX0, back12, s_nbox1[39], s_nbox2[39], s_nbox4[39], s_nbox3[39], c_arr[24], c_arr2[50], s_coins_[12], s_about;
    RectangleShape   s_box2, s_box, BOX0, BOX01, s_BOX[39], s_cbox[14], s_ncbox[12], b_mash, nb_mash;
    bool _box[39], nbox[39], _cbox[14], _ncbox[14], _b_mash = true, _nb_mash = false;
    Vector2u textsize = playertex.getSize();
    textsize.x /= 13;
    textsize.y /= 4;
    if (!c_box.loadFromFile("5.PNG"))
    {
        cout << "error";
    }
    if (!about.loadFromFile("about us2.PNG"))
    {
        cout << "error";
    }
    s_about.setTexture(about);
    if (!won.loadFromFile("you win2.PNG"))
    {
        cout << "error";
    }
    won_.setTexture(won);
    if (!so_coin.loadFromFile("coin.ogg")) {
        cout << "err";
    }
    for (int i = 0; i < 24; i++)
    {


        sso_coin[i].setBuffer(so_coin);
    }
    if (!__coin.loadFromFile("999.png")) {
        cout << "ee";
    }
    Vector2u cbox = c_box.getSize();
    cbox.x /= 2;
    b_mash.setTexture(&c_box);
    b_mash.setPosition(2970, 600);
    b_mash.setSize(Vector2f(70, 70));
    b_mash.setTextureRect(IntRect(cbox.x * 0, cbox.y * 0, cbox.x, cbox.y));
    nb_mash.setTexture(&c_box);
    nb_mash.setPosition(2970, 600);
    nb_mash.setSize(Vector2f(70, 70));
    nb_mash.setTextureRect(IntRect(cbox.x * 1, cbox.y * 0, cbox.x, cbox.y));
    if (!so_start.loadFromFile("start.ogg"))
    {
        cout << " ";
    }
    sso_start.setBuffer(so_start);
    if (!back1.loadFromFile("back1.PNG")) {
        cout << "error";
    }
    back12.setTexture(back1);
    if (!box.loadFromFile("23.PNG")) {
        cout << "error";
    }
    s_box.setTexture(&box);
    s_BOX0.setTexture(box);
    if (box2.loadFromFile("box2.PNG")) {
        cout << "error";
    }
    s_box2.setTexture(&box2);
    s_box2.setSize(Vector2f(70, 70));
    if (!so_pipe.loadFromFile("pipe.ogg"))
    {
        cout << " ";
    }
    sso_pipe.setBuffer(so_pipe);
    if (!so_play.loadFromFile("play.ogg"))
    {
        cout << "error";

    }
    sso_play.setBuffer(so_play);
    if (!pipe.loadFromFile("Pipe.PNG")) {
        cout << "error";
    }
    s_pipe.setTexture(pipe);
    if (!enemey.loadFromFile("enemy.PNG")) {
        cout << "error";
    }
    s_enemy.setTexture(enemey);
    s_enemy.setPosition(1450, 815);
    if (!BOX.loadFromFile("img.PNG")) {
        cout << "error";
    }
    s_box.setTexture(&BOX);
    s_box.setSize(Vector2f(49, 49));
    if (!nBOX.loadFromFile("10.png"))
    {
        cout << "error";
    }
    if (!coins.loadFromFile("13.PNG"))
    {
        cout << "error";
    }

    Vector2u b_coins = coins.getSize();
    b_coins.y /= 2;
    /* b = walk_bounded(100, 1, 500, 450);*/
    /* Time time_;
     Time elapsed_;
     Clock clock1;
     elapsed_ = clock1.getElapsedTime();

         time_ = seconds(2);
     if(time_.asSeconds() < elapsed_.asSeconds())

      clock1.restart(); */

    ccccc = walk_bounded(7000, 1, 0, 1050);
    ccccc.setFillColor(Color::White);
    for (int i = 0; i < 38; i++) {

        if (i < 7) {


            s_BOX[i].setTexture(&BOX);
            s_BOX[i].setSize(Vector2f(70, 70));
            s_BOX[i].setPosition(450 + (65) * i, 600);
            s_nbox1[i].setTexture(nBOX);
            s_nbox1[i].setPosition(445 + 65 * i, 595);
            s_nbox2[i].setTexture(nBOX);
            s_nbox2[i].setPosition(495 + 65 * i, 595);
            s_nbox3[i].setTexture(nBOX);
            s_nbox3[i].setPosition(445 + 65 * i, 645);
            s_nbox4[i].setTexture(nBOX);
            s_nbox4[i].setPosition(495 + 65 * i, 645);
            /*  mbox[i] = walk_bounded(50, 1, 450 + 50 * i, 740);
              mbox[i].setFillColor(Color::Red);*/
            s_cbox[i].setTexture(&c_box);
            s_cbox[i].setSize(Vector2f(70, 70));
            s_cbox[i].setTextureRect(IntRect(cbox.x * 0, cbox.y * 0, cbox.x, cbox.y));
            s_cbox[0].setPosition(1880, 600);

            s_cbox[1].setPosition(1485, 600);
            s_cbox[2].setPosition(570, 360);
            s_cbox[3].setPosition(637, 360);
            s_cbox[4].setPosition(1590, 360);
            s_cbox[5].setPosition(2515, 600);
            s_cbox[6].setPosition(3170, 600);
            s_ncbox[i].setTexture(&c_box);
            s_ncbox[i].setSize(Vector2f(70, 70));
            s_ncbox[i].setTextureRect(IntRect(cbox.x * 1, cbox.y * 0, cbox.x, cbox.y));
            s_ncbox[0].setPosition(1880, 600);

            s_ncbox[1].setPosition(1485, 600);
            s_ncbox[2].setPosition(570, 360);
            s_ncbox[3].setPosition(637, 360);
            s_ncbox[4].setPosition(1590, 360);
            s_ncbox[5].setPosition(2515, 600);
            s_ncbox[6].setPosition(3170, 600);
            s_coins[i].setTexture(coins);
            s_coins[i].setTextureRect(IntRect(b_coins.x * 0, b_coins.y * yc, b_coins.x, b_coins.y));
            s_coins[0].setPosition(1880, 540);

            s_coins[1].setPosition(1485, 540);
            s_coins[2].setPosition(570, 300);
            s_coins[3].setPosition(637, 300);
            s_coins[4].setPosition(1590, 300);
            s_coins[5].setPosition(2515, 540);
            s_coins[6].setPosition(3170, 540);
            s_coins_[i].setTexture(coins);
            s_coins_[i].setTextureRect(IntRect(b_coins.x * 0, b_coins.y * 1, b_coins.x, b_coins.y));
            s_coins_[0].setPosition(1880, 540);

            s_coins_[1].setPosition(1485, 540);
            s_coins_[2].setPosition(570, 300);
            s_coins_[3].setPosition(637, 300);
            s_coins_[4].setPosition(1590, 300);
            s_coins_[5].setPosition(2515, 540);
            s_coins_[6].setPosition(3170, 540);
            _cbox[i] = true;
            _ncbox[i] = false;


            Up_walk[i].setFillColor(Color::Red);
            if (big == 1) {
                Up_walk[0] = walk_bounded(450, 1, 450, 600);
                Up_walk[1] = walk_bounded(137, 1, 564, 360);
                Up_walk[2] = walk_bounded(460, 1, 1485, 600);
                Up_walk[3] = walk_bounded(68, 1, 1590, 360);
                Up_walk[4] = walk_bounded(650, 1, 3450, 600);
                Up_walk[5] = walk_bounded(137, 1, 2800, 360);

                Up_walk[6] = walk_bounded(710, 1, 2520, 600);
                Up_walk[7] = walk_bounded(68, 1, 3800, 360);
            }
            if (big == 0 || big == 3) {
                Up_walk[0] = walk_bounded(450, 1, 450, 619);
                Up_walk[1] = walk_bounded(137, 1, 564, 382);
                Up_walk[2] = walk_bounded(460, 1, 1485, 619);
                Up_walk[3] = walk_bounded(68, 1, 1590, 382);
                Up_walk[4] = walk_bounded(650, 1, 3450, 619);
                Up_walk[5] = walk_bounded(137, 1, 2800, 382);

                Up_walk[6] = walk_bounded(710, 1, 2520, 619);
                Up_walk[7] = walk_bounded(68, 1, 3800, 382);
            }
            Down_walk[i].setFillColor(Color::Red);
            Down_walk[0] = walk_bounded(450, 1, 450, 660);
            Down_walk[1] = walk_bounded(137, 1, 564, 410);
            Down_walk[2] = walk_bounded(460, 1, 1485, 650);
            Down_walk[3] = walk_bounded(68, 1, 1590, 410);
            Down_walk[4] = walk_bounded(650, 1, 3450, 650);
            Down_walk[5] = walk_bounded(137, 1, 2800, 410);

            Down_walk[6] = walk_bounded(710, 1, 2520, 650);
            Down_walk[7] = walk_bounded(68, 1, 3800, 410);
            _pipe[i].setFillColor(Color::White);
            _pipe[0] = walk_bounded(95, 1, 2030, 843);
            _pipe[1] = walk_bounded(95, 1, 3300, 843);
            _pipe[2] = walk_bounded(95, 1, 4188, 843);
            _pipe[3] = walk_bounded(95, 1, 4522, 843);
            _pipe[4] = walk_bounded(95, 1, 5133.5, 843);
            _pipe[5] = walk_bounded(95, 1, 5460, 843);
        }
        else if (i < 12 && i >= 7) {

            s_BOX[i].setTexture(&BOX);
            s_BOX[i].setSize(Vector2f(70, 70));
            s_BOX[i].setPosition(1100 + (65) * i, 600);
            s_nbox1[i].setTexture(nBOX);
            s_nbox1[i].setPosition(1095 + 65 * i, 595);
            s_nbox2[i].setTexture(nBOX);
            s_nbox2[i].setPosition(1145 + 65 * i, 595);
            s_nbox3[i].setTexture(nBOX);
            s_nbox3[i].setPosition(1095 + 65 * i, 645);
            s_nbox4[i].setTexture(nBOX);
            s_nbox4[i].setPosition(1145 + 65 * i, 645);
            s_cbox[i].setTexture(&c_box);
            s_cbox[i].setSize(Vector2f(70, 70));
            s_cbox[i].setTextureRect(IntRect(cbox.x * 0, cbox.y * 0, cbox.x, cbox.y));
            s_cbox[7].setPosition(2800, 360);
            s_cbox[8].setPosition(2860, 360);
            s_cbox[9].setPosition(3440, 600);
            s_cbox[10].setPosition(4030, 600);
            s_cbox[11].setPosition(3800, 360);
            s_ncbox[i].setTexture(&c_box);
            s_ncbox[i].setSize(Vector2f(70, 70));

            s_ncbox[i].setTextureRect(IntRect(cbox.x * 1, cbox.y * 0, cbox.x, cbox.y));
            s_ncbox[7].setPosition(2800, 360);
            s_ncbox[8].setPosition(2860, 360);
            s_ncbox[9].setPosition(3440, 600);
            s_ncbox[10].setPosition(4030, 600);
            s_ncbox[11].setPosition(3800, 360);
            /*  mbox[i] = walk_bounded(50, 1, 1280 + 50 * i, 740);
              mbox[i].setFillColor(Color::Red);*/
            _cbox[i] = true;
            _ncbox[i] = false;
            s_coins[i].setTexture(coins);
            s_coins[i].setTextureRect(IntRect(b_coins.x * 0, b_coins.y * yc, b_coins.x, b_coins.y));
            s_coins[7].setPosition(2800, 300);
            s_coins[8].setPosition(2860, 300);
            s_coins[9].setPosition(3440, 540);
            s_coins[10].setPosition(4030, 540);
            s_coins[11].setPosition(3800, 300);
            s_coins_[i].setTexture(coins);
            s_coins_[i].setTextureRect(IntRect(b_coins.x * 0, b_coins.y * 1, b_coins.x, b_coins.y));
            s_coins_[7].setPosition(2800, 300);
            s_coins_[8].setPosition(2860, 300);
            s_coins_[9].setPosition(3440, 540);
            s_coins_[10].setPosition(4030, 540);
            s_coins_[11].setPosition(3800, 300);


        }

        else if (i < 21 && i >= 12 && i != 18) {
            s_BOX[i].setTexture(&BOX);
            s_BOX[i].setPosition(1800 + (65) * i, 600);
            s_BOX[i].setSize(Vector2f(70, 70));
            s_nbox1[i].setTexture(nBOX);
            s_nbox1[i].setPosition(1795 + 65 * i, 595);
            s_nbox2[i].setTexture(nBOX);
            s_nbox2[i].setPosition(1845 + (65 * i), 595);
            s_nbox3[i].setTexture(nBOX);
            s_nbox3[i].setPosition(1795 + 65 * i, 645);
            s_nbox4[i].setTexture(nBOX);
            s_nbox4[i].setPosition(1845 + 65 * i, 645);
            /*   mbox[i] = walk_bounded(50, 1, 2010 + 50 * i, 740);
               mbox[i].setFillColor(Color::Red);*/
               /* s_cbox[12].setPosition(3550, 0);
                s_cbox[13].setPosition(3700, 0);*/

        }
        else if (i < 31 && i >= 23) {
            s_BOX[i].setTexture(&BOX);
            s_BOX[i].setSize(Vector2f(70, 70));
            s_BOX[i].setPosition(2015 + (65) * i, 600);
            s_nbox1[i].setTexture(nBOX);
            s_nbox1[i].setPosition(2010 + 65 * i, 595);
            s_nbox2[i].setTexture(nBOX);
            s_nbox2[i].setPosition(2060 + 65 * i, 595);
            s_nbox3[i].setTexture(nBOX);
            s_nbox3[i].setPosition(2010 + 65 * i, 645);
            s_nbox4[i].setTexture(nBOX);
            s_nbox4[i].setPosition(2060 + 65 * i, 645);
            /*   mbox[i] = walk_bounded(50, 1, 2430 + 50 * i, 740);
               mbox[i].setFillColor(Color::Red);*/
        }
        _box[i] = true;
        nbox[i] = false;


    }
    for (int i = 0; i < 16; i++)
    {
        left_walk[i].setFillColor(Color::Red);
        left_walk[0] = walk_bounded(1, 70, 450, 597);
        left_walk[1] = walk_bounded(1, 70, 564, 360);
        left_walk[2] = walk_bounded(1, 70, 1485, 597);
        left_walk[3] = walk_bounded(1, 70, 1590, 360);
        left_walk[4] = walk_bounded(1, 70, 3450, 597);
        left_walk[5] = walk_bounded(1, 70, 2800, 360);

        left_walk[6] = walk_bounded(1, 70, 2520, 597);
        left_walk[7] = walk_bounded(1, 110, 1420, 825);
        left_walk[8] = walk_bounded(1, 110, 2030, 825);
        left_walk[9] = walk_bounded(1, 110, 2350, 825);
        left_walk[10] = walk_bounded(1, 110, 3300, 825);
        left_walk[11] = walk_bounded(1, 110, 4188, 825);

        left_walk[12] = walk_bounded(1, 110, 4522, 825);

        left_walk[13] = walk_bounded(1, 110, 5133.5, 825);
        left_walk[14] = walk_bounded(1, 70, 3800, 360);

        left_walk[15] = walk_bounded(1, 110, 5460, 825);
        right_walk[i].setFillColor(Color::Red);
        right_walk[0] = walk_bounded(1, 70, 907, 597);
        right_walk[1] = walk_bounded(1, 70, 700, 360);
        right_walk[2] = walk_bounded(1, 70, 1947, 597);
        right_walk[3] = walk_bounded(1, 70, 1660, 360);
        right_walk[4] = walk_bounded(1, 70, 3230, 597);
        right_walk[5] = walk_bounded(1, 70, 2934, 360);

        right_walk[6] = walk_bounded(1, 70, 4100, 597);
        right_walk[7] = walk_bounded(1, 110, 1478, 825);
        right_walk[8] = walk_bounded(1, 110, 2120, 825);
        right_walk[9] = walk_bounded(1, 110, 2440, 825);
        right_walk[10] = walk_bounded(1, 110, 3390, 825);
        right_walk[11] = walk_bounded(1, 110, 4278, 825);

        right_walk[12] = walk_bounded(1, 110, 4612, 825);

        right_walk[13] = walk_bounded(1, 110, 5223.5, 825);
        right_walk[14] = walk_bounded(1, 70, 3860, 360);

        right_walk[15] = walk_bounded(1, 110, 5550, 825);

    }

    /* for (int i = 0; i < 12; i++)
     {
         _cbox[i] = true;
         _ncbox[i] = false;
     }*/
    BOX0 = walk_bounded(6000, 1, 450, 600);
    BOX01 = walk_bounded(6000, 1, 450, 590);
    char map_1[100][1000] = {
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                         ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                 ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                                       ",
     "0                             2            2      2                   2                  2      2            2      2                                                  ",
     "000000000000000000000000      000000000000000     00000000000000000000000000000000000000000     000000000000000     000000000000000000000000000000000000000000000000000",
     "000000000000000000000000      000000000000000     00000000000000000000000000000000000000000     000000000000000     000000000000000000000000000000000000000000000000000",
     "000000000000000000000000      000000000000000     00000000000000000000000000000000000000000     000000000000000     000000000000000000000000000000000000000000000000000",
     "000000000000000000000000      000000000000000     0000000000      0000000000000000000000000     000000000000000     000000000000000000000000000000000000000000000000000",

    };// تاني واجهة
    Texture bibe__;
    for (int i = 0; i < 50; i++) {
        ss_coin[i].setBuffer(so_coin);

    }
    if (!bibe__.loadFromFile("pipe2.png")) {
        cout << "error";
    }
    Sprite down_pipe;
    down_pipe.setTexture(bibe__);




    /*
        dof[0].setPosition(600, 550);
        dof[1].setPosition(1690, 550);
        dof[2].setPosition(2830, 550);
        dof[3].setPosition(3715, 550);
        daid[0].setPosition(609, 535);
        daid[1].setPosition(1699, 535);
        daid[2].setPosition(2839, 535);
        daid[3].setPosition(3724, 535);
        doc[0].setPosition(1740, 900);
        doc[1].setPosition(2835, 900);
        doc[2].setPosition(3751, 900);
        doc[3].setPosition(4815, 900);
        daid_d[0].setPosition(1745, 880);
        daid_d[1].setPosition(2840, 880);
        daid_d[2].setPosition(3756, 880);
        daid_d[3].setPosition(4820, 880);*/


    char map_2[100][100] = {


     "0000000   0000000000000000000000000",
     "0000000   0000000000000000000000000",
     "0000000   0000000000000000000000000",
     "0000000   0000000000000000000000000",



     "0000000                           0                   ",
     "0000000                           0                   ",
     "0000000                           0                   ",

     "0000000                           0                    ",
     "0000000                           0                   ",
     "0000000                           0                   ",
     "0000000                           0                   ",
     "0000000                           0                   ",
     "0000000                           0                   ",
     "0000000   000000000000000         0                                  ",
     "0000000   000000000000000         0                                   ",
     "0000000   000000000000000         0                                      ",
     "00000000000000000000000000000000000",
     "00000000000000000000000000000000000",
     "00000000000000000000000000000000000",
     "00000000000000000000000000000000000",
     "000000000000000000000000000000000000000000000000000000000000000",

    };
    char map_3[100][1000] = {
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                         ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                 ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                            ",
     "0                                                                                                                                                                       ",
     "0                             2             2      2                   2                  2      2            2      2                                                  ",
     "000000000000000000000000000000000000000000000     00000000000000000000000000000000000000000     000000000000000     000000000000000000000000000000000000000000000000000",
     "000000000000000000000000000000000000000000000     00000000000000000000000000000000000000000     000000000000000     000000000000000000000000000000000000000000000000000",
     "000000000000000000000000000000000000000000000     00000000000000000000000000000000000000000     000000000000000     000000000000000000000000000000000000000000000000000",
     "000000000000000000000000000000000000000000000     0000000000      0000000000000000000000000     000000000000000     000000000000000000000000000000000000000000000000000",

    };
    sf::Texture menu_2;
    if (!menu_2.loadFromFile("how to play1.PNG")) {
        cout << "error";

    }
    sf::Sprite s_menu_2;
    s_menu_2.setTexture(menu_2);
    pipe5 = walk_bounded(98, 1, 4510, 830);
    pipe5.setFillColor(Color::Red);

    pipe3 = walk_bounded(70, 1, 1420, 880);
    pipe3.setFillColor(Color::Red);
    pipe4 = walk_bounded(70, 1, 1420, 860);
    pipe4.setFillColor(Color::Red);
    pipe5 = walk_bounded(98, 1, 2350, 830);
    pipe5.setFillColor(Color::Red);

    pipe8 = walk_bounded(98, 1, 2350, 865);
    pipe8.setFillColor(Color::Red);
    pipe9 = walk_bounded(70, 1, 2360, 840);
    pipe9.setFillColor(Color::Red);
    pipe1 = walk_bounded(70, 1, 1420, 845);
    pipe1.setFillColor(Color::Red);
    // pl.setTextureRect(IntRect(0, 48, 66, 48));
    View view;
    view.reset(FloatRect(0, 0, screen.x, screen.y));
    view.setViewport(FloatRect(0, 0, 1.0f, 1.0f));
    Vector2f position(screen.x / 2, screen.y / 2);

    for (int i = 0; i < 24; i++)
    {
        c_arr[i].setTexture(__coin);
        c_arr[0].setPosition(4655, 625);
        c_arr[1].setPosition(4710, 625);
        c_arr[2].setPosition(4765, 625);
        c_arr[3].setPosition(4765, 680);
        c_arr[4].setPosition(4765, 735);
        c_arr[5].setPosition(4710, 735);
        c_arr[6].setPosition(4655, 735);
        c_arr[7].setPosition(4655, 790);
        c_arr[8].setPosition(4655, 845);
        c_arr[9].setPosition(4710, 845);
        c_arr[10].setPosition(4765, 845);

        c_arr[11].setPosition(4865, 625);
        c_arr[12].setPosition(4920, 625);
        c_arr[13].setPosition(4975, 625);
        c_arr[14].setPosition(4975, 680);
        c_arr[15].setPosition(4865, 680);
        c_arr[16].setPosition(4865, 735);
        c_arr[17].setPosition(4920, 735);
        c_arr[18].setPosition(4975, 735);
        c_arr[19].setPosition(4975, 780);
        c_arr[20].setPosition(4865, 780);
        c_arr[21].setPosition(4865, 840);
        c_arr[22].setPosition(4920, 840);
        c_arr[23].setPosition(4975, 840);




    }
    for (int i = 0; i < 14; i++)
    {
        c_draw[i] = false;
    }

    while (win.isOpen()) {

        sf::Event event;
        while (win.pollEvent(event)) {
            /*sso_start.play();*/

            switch (event.type)
            {
            case sf::Event::KeyReleased:

                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();


                    break;
                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;
                case sf::Keyboard::Return:
                {
                    if (menu.GetPressedItem() == 0)
                    {
                        clock.restart();
                        if (!_font.loadFromFile("text11.ttf"))
                        {
                            cout << "error";
                        }
                        for (int j = 0; j < 14; j++) {

                            text_[j].setFont(_font);
                            text_[j].setCharacterSize(50);
                            text_[j].setFillColor(Color::White);
                            text_[j].setOutlineColor(Color::Black);

                        }


                        sso_play.play();
                        sso_start.pause();
                        win.clear();
                        // cout << "Play button had been pressed" << endl;


                        while (win.isOpen()) {
                            Time _time = clock.getElapsedTime();
                            if (o == false) {
                                second = _time.asSeconds();
                                /*if (second == 60)

                                {
                                    second = 0;
                                    menute++;
                                    clock.restart();

                                }*/
                            }
                            sf::Event event2;

                            while (win.pollEvent(event2)) {
                                switch (event2.type)
                case sf::Event::Closed: {

                                    win.close();


                                    ;                            }
                            }

                            text_[13].setFont(_font);
                            text_[13].setCharacterSize(110);

                            text_[13].setFillColor(Color::Red);
                            text_[13].setOutlineColor(Color::Black);
                            /* text_[10].setPosition(500, 500);*/
                            text_[13].setString("Game Over");
                            if (life == 1 && time_[1] == false)
                            {
                                life_count = 2;
                                time[1] = time[1] + .01;
                            }
                            else if (life == 2 && time_[2] == false)
                            {
                                life_count = 1;
                                time[2] = time[2] + .01;
                            }
                            if (life == 1 && time[1] <= 1 && time_[1] == false)
                                life_ = true;
                            else if (life == 2 && time[2] <= 1 && time_[2] == false)
                                life_ = true;
                            if (time[1] > 1)
                            {
                                life_ = false;
                                time[1] = 0;
                                time_[1] = true;
                            }
                            else if (time[2] > 1)
                            {
                                life_ = false;
                                time[2] = 0;
                                time_[2] = true;
                            }
                            if (life < 3 && life_ == false)
                            {

                                dof[0].setPosition(600, 550);
                                dof[1].setPosition(1690, 550);
                                dof[2].setPosition(2830, 550);
                                dof[3].setPosition(3715, 550);
                                daid[0].setPosition(609, 535);
                                daid[1].setPosition(1699, 535);
                                daid[2].setPosition(2839, 535);
                                daid[3].setPosition(3724, 535);
                                doc[0].setPosition(1740, 900);
                                doc[1].setPosition(2835, 900);
                                doc[2].setPosition(3751, 900);
                                doc[3].setPosition(4815, 900);
                                daid_d[0].setPosition(1745, 880);
                                daid_d[1].setPosition(2840, 880);
                                daid_d[2].setPosition(3756, 880);
                                daid_d[3].setPosition(4820, 880);
                                v_ = false;
                                o = false;
                                big = 0;
                                q = 0;
                                b = 0;
                                c = 0;
                                for (int i = 0; i < 4; i++)
                                {
                                    v_d[i] = false;
                                    m[i] = false;
                                    dd[i] = false;
                                    dd_[i] = false;
                                }
                                player.setPosition(100.0f, -2.0f);
                                if (player.getPosition().x == 100)
                                    life_ = true;
                            }
                            if (life == 3)
                            {
                                ss_game_over.play();
                                sso_play.pause();

                                life_count = 0;


                            }

                            cout << player.getPosition().x << endl;

                            if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
                                ss_jump.play();
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                View view2;
                                view2.reset(FloatRect(0, 0, screen.x, screen.y));
                                view2.setViewport(FloatRect(0, 0, 1.0f, 1.0f));
                                win.setView(view2);

                                break;

                            }
                            Vector2u b__coin = __coin.getSize();
                            b__coin.x /= 26;
                            b__coin.x /= 1;
                            for (int i = 0; i < 24; i++) {
                                c_arr[i].setTextureRect(IntRect(b__coin.x * x_[i], b__coin.y * y_[i], b__coin.x, b__coin.y));
                            }
                            //for (int i = 0; i < 24; i++)
                            //{


                            //    if (player.getGlobalBounds().intersects(c_arr[i].getGlobalBounds())) {
                            //        //player.setPosition(Vector2f(50, 200));
                            //        
                            //        count_ += 50;
                            //    }
                            //}
                            for (int i = 0; i < 24; i++) {
                                if (player.getGlobalBounds().intersects(c_arr[i].getGlobalBounds())) {
                                    if (x_[i] != 25) {
                                        coins_count++;
                                        count_ += 20;
                                        sso_coin[i].play();
                                    }
                                    x_[i] = 25;
                                }
                                else if (x_[i] != 25) {

                                    if (x_[i] <= 24)
                                    {
                                        x_[i]++;
                                    }
                                    if (x_[i] > 24)
                                        x_[i] = 0;

                                }
                            }
                            if (life_count == 0 && o == true)
                            {
                                ss_game_over.play();
                            }
                            win.clear();
                            win.draw(d);
                            win.draw(player);
                            dofdaa();
                            marsho();
                            win.draw(marsh);
                            for (int h = 0; h < 1000; h++)
                            {
                                for (int w = 0; w < 100; w++)
                                {
                                    if (map_1[w][h] == '0')
                                    {
                                        Vector2u b_box = box.getSize();
                                        s_box.setPosition((b_box.y - 2) * h, (b_box.x - 2) * w);
                                        win.draw(s_box);

                                    }


                                    else if (map_1[w][h] == '2') {
                                        Vector2u b_pipe = pipe.getSize();
                                        s_pipe.setPosition((b_pipe.y - 103) * h, (b_pipe.x - 55) * w);
                                        win.draw(s_pipe);
                                    }
                                }
                            }
                            mario_move();


                            for (int i = 0; i < 12; i++)
                            {
                                if (player.getGlobalBounds().intersects(s_cbox[i].getGlobalBounds()) && (player.getGlobalBounds().intersects(Down_walk[0].getGlobalBounds()) || player.getGlobalBounds().intersects(Down_walk[1].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(Down_walk[2].getGlobalBounds()) || player.getGlobalBounds().intersects(Down_walk[3].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(Down_walk[4].getGlobalBounds()) || player.getGlobalBounds().intersects(Down_walk[5].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(Down_walk[6].getGlobalBounds()) || player.getGlobalBounds().intersects(Down_walk[7].getGlobalBounds())) && o == false && c_draw[i] == false)
                                    /* c_draw[1] == false&& c_draw[2] == false && c_draw[3] == false && c_draw[4] == false && c_draw[5] == false && c_draw[6] == false && c_draw[7] == false && c_draw[8] == false && c_draw[9] == false &&
                                     c_draw[10] == false && c_draw[11] == false*/ {
                                    _cbox[i] = false;
                                    _ncbox[i] = true;
                                    coins_count++;
                                    count_ += 20;
                                    c_draw[i] = true;
                                    /* c_draw[0] = true;
                                     c_draw[1] = true;
                                     c_draw[2] = true;
                                     c_draw[3] = true;
                                     c_draw[4] = true;
                                     c_draw[5] = true;
                                     c_draw[6] = true;
                                     c_draw[7] = true;
                                     c_draw[8] = true;
                                     c_draw[9] = true;
                                     c_draw[10] = true;
                                     c_draw[11] = true;*/

                                    win.draw(s_coins[i]);
                                }

                            }
                            if (player.getGlobalBounds().intersects(b_mash.getGlobalBounds()) && player.getGlobalBounds().intersects(Down_walk[6].getGlobalBounds())) {
                                _b_mash = false;
                                _nb_mash = true;

                                marsh.move(0, -3);
                                /* if (marsh.getGlobalBounds().intersects(Up_walk[6].getGlobalBounds()))
                                 {
                                     for (int i = 0; i < 10; i++)
                                     {
                                         marsh.move(0, 0.2 * i);
                                     }
                                 }*/
                                ss_marsho.play();
                            }

                            if (player.getGlobalBounds().intersects(marsh.getGlobalBounds()))
                            {


                                ss_marsho.play();
                            }
                            for (int i = 0; i < 38; i++) {

                                {if ((player.getGlobalBounds().intersects(walk1.getGlobalBounds()) || player.getGlobalBounds().intersects(walk2.getGlobalBounds())
                                    || player.getGlobalBounds().intersects(walk3.getGlobalBounds()) || player.getGlobalBounds().intersects(walk4.getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(walk5.getGlobalBounds()) || player.getGlobalBounds().intersects(pipe1.getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(pipe5.getGlobalBounds()) || player.getGlobalBounds().intersects(pipe8.getGlobalBounds())
                                    || ((player.getGlobalBounds().intersects(Up_walk[0].getGlobalBounds()) || player.getGlobalBounds().intersects(Up_walk[1].getGlobalBounds()) ||
                                        player.getGlobalBounds().intersects(Up_walk[2].getGlobalBounds()) || player.getGlobalBounds().intersects(Up_walk[3].getGlobalBounds()) ||
                                        player.getGlobalBounds().intersects(Up_walk[4].getGlobalBounds()) || player.getGlobalBounds().intersects(Up_walk[5].getGlobalBounds()) ||
                                        player.getGlobalBounds().intersects(Up_walk[6].getGlobalBounds()) || player.getGlobalBounds().intersects(Up_walk[7].getGlobalBounds())
                                        && (big == 0 || big == 2))) ||
                                    player.getGlobalBounds().intersects(_pipe[0].getGlobalBounds()) || player.getGlobalBounds().intersects(_pipe[1].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(_pipe[2].getGlobalBounds()) || player.getGlobalBounds().intersects(_pipe[3].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(_pipe[4].getGlobalBounds()) || player.getGlobalBounds().intersects(_pipe[5].getGlobalBounds())) && o == false)
                                {
                                    player.move(0, 0);

                                    jump = false;
                                }
                                else {


                                    if (!Keyboard::isKeyPressed(Keyboard::Key::Space) || o == true || jumping == false)
                                    {
                                        //jumping = true;
                                        if (o == false)
                                        {
                                            if (big == 0 || big == 2)
                                            {
                                                if (y == 0)
                                                    player.setTextureRect(IntRect(textsize.x * 5, textsize.y * 1, textsize.x, textsize.y));
                                                if (y == 1)
                                                    player.setTextureRect(IntRect(textsize.x * 7, textsize.y * 2, textsize.x, textsize.y));
                                            }
                                            else if (big == 1)
                                            {
                                                if (y == 0)
                                                    player.setTextureRect(IntRect(textsize.x * 5, textsize.y * 0, textsize.x, textsize.y));
                                                if (y == 1)
                                                    player.setTextureRect(IntRect(textsize.x * 7, textsize.y * 3, textsize.x, textsize.y));
                                            }
                                        }
                                        player.move(0, 0.1);
                                    }
                                }
                                }


                                if (player.getGlobalBounds().intersects(s_BOX[i].getGlobalBounds()) && (player.getGlobalBounds().intersects(Down_walk[0].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(Down_walk[2].getGlobalBounds()) || player.getGlobalBounds().intersects(Down_walk[4].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(Down_walk[6].getGlobalBounds())) && o == false) {
                                    /*  _box[i] = false; */
                                    s_BOX[i].move(0, -15);
                                    player.move(0, 30);
                                    ss_box.play();
                                }
                                if (BOX0.getGlobalBounds().intersects(s_BOX[i].getGlobalBounds())) {
                                    s_BOX[i].move(0, 1);
                                }
                                if (BOX01.getGlobalBounds().intersects(s_BOX[i].getGlobalBounds())) {
                                    s_BOX[i].move(0, 2);
                                }

                            }

                            if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
                                if (player.getGlobalBounds().intersects(Down_walk[0].getGlobalBounds()) || player.getGlobalBounds().intersects(Down_walk[1].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(Down_walk[2].getGlobalBounds()) || player.getGlobalBounds().intersects(Down_walk[3].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(Down_walk[4].getGlobalBounds()) || player.getGlobalBounds().intersects(Down_walk[5].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(Down_walk[6].getGlobalBounds()) || player.getGlobalBounds().intersects(Down_walk[7].getGlobalBounds()))
                                {
                                    player.move(0, 10);
                                }
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                                if (player.getGlobalBounds().intersects(left_walk[0].getGlobalBounds()) || player.getGlobalBounds().intersects(left_walk[1].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(left_walk[2].getGlobalBounds()) || player.getGlobalBounds().intersects(left_walk[3].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(left_walk[4].getGlobalBounds()) || player.getGlobalBounds().intersects(left_walk[3].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(left_walk[6].getGlobalBounds()) || player.getGlobalBounds().intersects(left_walk[7].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(left_walk[8].getGlobalBounds()) || player.getGlobalBounds().intersects(left_walk[9].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(left_walk[10].getGlobalBounds()) || player.getGlobalBounds().intersects(left_walk[11].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(left_walk[12].getGlobalBounds()) || player.getGlobalBounds().intersects(left_walk[13].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(left_walk[14].getGlobalBounds()) || player.getGlobalBounds().intersects(left_walk[15].getGlobalBounds()))
                                {
                                    player.move(-1.7, 0);
                                }
                            }
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                                if (player.getGlobalBounds().intersects(right_walk[0].getGlobalBounds()) || player.getGlobalBounds().intersects(right_walk[1].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(right_walk[2].getGlobalBounds()) || player.getGlobalBounds().intersects(right_walk[3].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(right_walk[4].getGlobalBounds()) || player.getGlobalBounds().intersects(right_walk[3].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(right_walk[6].getGlobalBounds()) || player.getGlobalBounds().intersects(right_walk[7].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(right_walk[8].getGlobalBounds()) || player.getGlobalBounds().intersects(right_walk[9].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(right_walk[10].getGlobalBounds()) || player.getGlobalBounds().intersects(right_walk[11].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(right_walk[12].getGlobalBounds()) || player.getGlobalBounds().intersects(left_walk[13].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(right_walk[14].getGlobalBounds()) || player.getGlobalBounds().intersects(right_walk[15].getGlobalBounds()))
                                {
                                    player.move(1.7, 0);
                                }
                            }
                            /*for (int i = 0; i < 39; i++) {
                                if (player.getGlobalBounds().intersects(s_BOX[i].getGlobalBounds())&&(player.getGlobalBounds().intersects(Down_walk[0].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(Down_walk[2].getGlobalBounds()) || player.getGlobalBounds().intersects(Down_walk[4].getGlobalBounds()) ||
                                    player.getGlobalBounds().intersects(Down_walk[6].getGlobalBounds()) )&&big==1) {
                                    _box[i] = false;
                                    nbox[i] = true;



                                    for (int j = 1; j < 30; j++) {
                                        s_nbox1[i].move(-0.2 * j, 2 * j);
                                        s_nbox2[i].move(0.2 * j, 2 * j);
                                        s_nbox3[i].move(-0.2 * j, 2 * j);
                                        s_nbox4[i].move(0.2 * j, 2* j);
                                    }
                                }
                            }*/

                            /* {if (player.getGlobalBounds().intersects(walk1.getGlobalBounds()) || player.getGlobalBounds().intersects(walk2.getGlobalBounds())
                                 || player.getGlobalBounds().intersects(walk3.getGlobalBounds()) || player.getGlobalBounds().intersects(walk4.getGlobalBounds()) ||
                                 player.getGlobalBounds().intersects(walk5.getGlobalBounds()) || player.getGlobalBounds().intersects(pipe1.getGlobalBounds())||
                                 player.getGlobalBounds().intersects(pipe5.getGlobalBounds())|| player.getGlobalBounds().intersects(pipe8.getGlobalBounds()))
                             {
                                 player.move(0, 0);
                             }
                             else {


                                 if (!Keyboard::isKeyPressed(Keyboard::Key::Space))
                                     player.move(0.0f, 15.0f);

                             }
                             }*/
                            if (player.getGlobalBounds().intersects(pipe9.getGlobalBounds()))
                            {

                                sso_pipe.play();
                                ss_under.pause();
                                sso_play.play();
                                for (int i = 0; i < 8; i++) {
                                    if (i < 8) {
                                        player.move(0, -0.06 * i);

                                    }
                                }
                            }

                            if (player.getGlobalBounds().intersects(pipe1.getGlobalBounds())) {
                                if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
                                    player.move(0, 3);
                                    sso_pipe.play();
                                    sso_play.pause();
                                }
                            }
                            if (player.getGlobalBounds().intersects(pipe4.getGlobalBounds()))
                            {



                                for (int i = 0; i < 5; i++) {
                                    if (i < 4) {
                                        player.move(0, 0.02 * i);


                                    }
                                }
                            }


                            {if (player.getGlobalBounds().intersects(pipe3.getGlobalBounds()))
                            {


                                ss_under.play();


                                win.clear();
                                player.setPosition(500, 0);
                                RectangleShape walk6;
                                walk6 = walk_bounded(2499, 1, 470, 970);
                                down_pipe.setPosition(2050, -180);
                                while (win.isOpen()) {
                                    /*Time _time = clock.getElapsedTime();*/

                                    sf::Event event2;
                                    while (win.pollEvent(event2)) {
                                        switch (event2.type)
                case sf::Event::Closed: {

                                            win.close();
                                        }
                                    }
                                    /*  second = u_time.asSeconds();

                                      if (second == 10)
                                      {
                                          second++;
                                          second = 0;
                                          _clock.restart();
                                      }*/
                                    mario_move();
                                    pipe6 = walk_bounded(1, 140, 2068, 800);
                                    pipe6.setFillColor(Color::Red);
                                    pipe7 = walk_bounded(1, 140, 2095, 800);
                                    pipe7.setFillColor(Color::Red);
                                    RectangleShape _walk[8];
                                    for (int i = 0; i < 8; i++)
                                    {
                                        _walk[i].setFillColor(Color::Red);
                                        _walk[0] = walk_bounded(1, 250, 672, 0);
                                        _walk[1] = walk_bounded(1900, 1, 672, 230);
                                        _walk[2] = walk_bounded(1, 1080, 2280, 0);
                                        _walk[3] = walk_bounded(1, 1080, 463, 0);
                                        _walk[4] = walk_bounded(180, 1, 2090, 750);
                                        _walk[5] = walk_bounded(1, 250, 678, 800);
                                        _walk[6] = walk_bounded(1, 250, 1700, 800);
                                        _walk[7] = walk_bounded(1030, 1, 678, 800);

                                    }
                                    Vector2u b__coin = __coin.getSize();
                                    b__coin.x /= 26;
                                    b__coin.x /= 1;
                                    for (int i = 0; i < 50; i++) {

                                        c_arr2[i].setTextureRect(IntRect(b__coin.x * x__[i], b__coin.y * y__[i], b__coin.x, b__coin.y));
                                    }
                                    if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
                                        ss_jump.play();
                                    }
                                    //for (int i = 0; i < 50; i++)
                                    //{


                                    //    if (player.getGlobalBounds().intersects(c_arr2[i].getGlobalBounds())) {
                                    //        //player.setPosition(Vector2f(50, 200));
                                    //        count_ += 50;
                                    //    }
                                    //}
                                    for (int i = 0; i < 50; i++) {
                                        if (player.getGlobalBounds().intersects(c_arr2[i].getGlobalBounds())) {
                                            if (x__[i] != 25) {
                                                ss_coin[i].play();
                                                coins_count++;
                                                count_ += 20;
                                            }
                                            x__[i] = 25;
                                        }
                                        else if (x__[i] != 25) {

                                            if (x__[i] <= 24)
                                            {
                                                x__[i]++;
                                            }
                                            if (x__[i] > 24)
                                                x__[i] = 0;

                                        }
                                    }
                                    for (int i = 0; i < 50; i++)
                                    {
                                        c_arr2[i].setTexture(__coin);
                                        c_arr2[0].setPosition(680, 340);
                                        c_arr2[1].setPosition(735, 340);
                                        c_arr2[2].setPosition(790, 340);
                                        c_arr2[3].setPosition(845, 340);
                                        c_arr2[4].setPosition(680, 395);
                                        c_arr2[5].setPosition(680, 450);
                                        c_arr2[6].setPosition(680, 505);
                                        c_arr2[7].setPosition(735, 505);
                                        c_arr2[8].setPosition(790, 505);
                                        c_arr2[9].setPosition(845, 505);
                                        c_arr2[10].setPosition(680, 560);
                                        c_arr2[11].setPosition(680, 615);
                                        c_arr2[12].setPosition(680, 670);
                                        c_arr2[13].setPosition(945, 340);
                                        c_arr2[14].setPosition(1000, 340);
                                        c_arr2[15].setPosition(1055, 340);
                                        c_arr2[16].setPosition(1110, 340);
                                        c_arr2[17].setPosition(945, 395);
                                        c_arr2[18].setPosition(945, 450);
                                        c_arr2[19].setPosition(945, 505);
                                        c_arr2[20].setPosition(945, 560);
                                        c_arr2[21].setPosition(945, 615);
                                        c_arr2[22].setPosition(945, 670);
                                        c_arr2[23].setPosition(1000, 670);
                                        c_arr2[24].setPosition(1055, 670);
                                        c_arr2[25].setPosition(1110, 670);
                                        c_arr2[26].setPosition(1250, 340);
                                        c_arr2[27].setPosition(1250, 395);
                                        c_arr2[28].setPosition(1250, 450);
                                        c_arr2[29].setPosition(1250, 505);
                                        c_arr2[30].setPosition(1250, 560);
                                        c_arr2[31].setPosition(1250, 615);
                                        c_arr2[32].setPosition(1250, 670);
                                        c_arr2[33].setPosition(1380, 340);
                                        c_arr2[34].setPosition(1435, 340);
                                        c_arr2[35].setPosition(1490, 340);
                                        c_arr2[36].setPosition(1545, 340);
                                        c_arr2[37].setPosition(1380, 395);
                                        c_arr2[38].setPosition(1380, 450);
                                        c_arr2[39].setPosition(1380, 505);
                                        c_arr2[40].setPosition(1435, 505);
                                        c_arr2[41].setPosition(1490, 505);
                                        c_arr2[42].setPosition(1545, 505);
                                        c_arr2[43].setPosition(1545, 560);
                                        c_arr2[44].setPosition(1545, 615);
                                        c_arr2[45].setPosition(1545, 670);
                                        c_arr2[46].setPosition(1490, 670);
                                        c_arr2[48].setPosition(1435, 670);
                                        c_arr2[49].setPosition(1380, 670);

                                    }
                                    if (player.getGlobalBounds().intersects(pipe6.getGlobalBounds())) {
                                        sso_pipe.play();
                                        for (int i = 0; i < 5; i++) {
                                            if (i < 4) {
                                                player.move(0.02 * i, 0);


                                            }
                                        }
                                    }
                                    if (player.getGlobalBounds().intersects(pipe7.getGlobalBounds())) {
                                        player.setPosition(2370, 820);
                                        sso_pipe.play();
                                        break;
                                    }
                                    win.clear();
                                    win.draw(back12);
                                    win.draw(player);
                                    win.draw(down_pipe);

                                    for (int h = 0; h < 1000; h++)
                                    {
                                        for (int w = 0; w < 100; w++)
                                        {
                                            if (map_2[w][h] == '0')
                                            {
                                                Vector2u b_box = box2.getSize();
                                                s_box2.setPosition((b_box.y + 38) * h, (b_box.x + 30) * w);
                                                win.draw(s_box2);

                                            }
                                        }
                                    }
                                    {if (player.getGlobalBounds().intersects(walk6.getGlobalBounds()) || player.getGlobalBounds().intersects(_walk[7].getGlobalBounds()) ||
                                        player.getGlobalBounds().intersects(_walk[4].getGlobalBounds())) {
                                        player.move(0, 0);
                                    }
                                    else
                                    {

                                        if (!Keyboard::isKeyPressed(Keyboard::Key::Space))
                                            player.move(0.0f, 15.0f);
                                    }
                                    }
                                    if (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D)) {
                                        if (player.getGlobalBounds().intersects(_walk[0].getGlobalBounds()) || player.getGlobalBounds().intersects(_walk[2].getGlobalBounds()) ||
                                            player.getGlobalBounds().intersects(_walk[5].getGlobalBounds())) {
                                            player.move(-1.7, 0);
                                        }
                                    }

                                    else if (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A)) {

                                        if (player.getGlobalBounds().intersects(_walk[3].getGlobalBounds()) || player.getGlobalBounds().intersects(_walk[6].getGlobalBounds()))
                                        {
                                            player.move(1.7, 0);
                                        }
                                    }
                                    else if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
                                        if (player.getGlobalBounds().intersects(_walk[1].getGlobalBounds())) {
                                            player.move(0, 10);
                                        }
                                    }
                                    {

                                    }
                                    //for (int i = 0; i < 8; i++)
                                    //{
                                    //    win.draw(_walk[i]);
                                    //}
                                    for (int i = 0; i < 50; i++)
                                    {
                                        win.draw(c_arr2[i]);
                                    }


                                    win.display();

                                }


                            }

                            win.draw(s_castle);
                            if (player.getGlobalBounds().intersects(s_castle.getGlobalBounds())) {
                                sso_play.pause();
                                ss_end.play();
                                player.move(0, 0);
                                won_.setPosition(position.x - 200, 400);
                                win.draw(won_);
                                ss_end.play();
                            }

                            /*  if (player.getPosition().x == 600) {
                                  win.clear();
                              }*/



                            Vector2u b_enemy = enemey.getSize();
                            b_enemy.x /= 4;
                            b_enemy.y /= 6;
                            s_enemy.setTextureRect(IntRect(b_enemy.x * x_enenmy, b_enemy.y, b_enemy.x, b_enemy.y));
                            if (player.getPosition().x < 6500)
                                if (player.getPosition().x + 10 > screen.x / 2) {
                                    position.x = player.getPosition().x + 10;

                                }
                                else
                                    position.x = screen.x / 2;
                            view.setCenter(position);
                            win.setView(view);

                            }
                            // high score text
                            text_[0].setString("High Score : ");
                            text_[0].setPosition(Vector2f(position.x - 900, 0.f));
                            //file fuction
                            highstr = to_string(uhigh_score(count_));
                            text_[2].setString(highstr);
                            text_[2].setPosition(Vector2f(position.x - 620, 0.f));

                            //score text
                            text_[1].setString("Score :");
                            text_[1].setPosition(Vector2f(position.x - 350, 0.f));

                            //score number
                            scorestr = to_string(count_);
                            text_[3].setString(scorestr);
                            text_[3].setPosition(Vector2f(position.x - 170, 0.f));

                            //coins number
                            coinstr = to_string(coins_count);
                            text_[4].setString(coinstr);
                            text_[4].setPosition(Vector2f(position.x + 200, 0.f));

                            // coins string
                            text_[5].setString("coins X ");
                            text_[5].setPosition(Vector2f(position.x, 0.f));

                            text_[6].setString("life X  ");
                            text_[6].setPosition(Vector2f(position.x + 300, 0.f));
                            lifestr = to_string(life_count);
                            text_[7].setString(lifestr);
                            text_[7].setPosition(Vector2f(position.x + 430, 0.f));

                            text_[8].setString("time:");
                            text_[8].setPosition(Vector2f(position.x + 600, 0.f));
                            //timestr = to_string(elapsed_);
                            timestr = to_string(second);
                            text_[9].setString(timestr);
                            text_[9].setPosition(Vector2f(position.x + 780, 0.f));
                            /* time_str = to_string(menute);
                             text_[10].setString(time_str);
                             text_[10].setPosition(Vector2f(position.x + 780, 0.f));

                             timestr2 = to_string(menute_);
                             text_[11].setString(timestr2);
                             text_[11].setPosition(Vector2f(position.x + 740, 0.f));*/


                            win.draw(s_mash);

                            /*for (int i = 0; i < 39; i++) {
                                win.draw(s_BOX[i]);
                                win.draw(s_nbox1[i]);
                                win.draw(s_nbox2[i]);
                                win.draw(s_nbox3[i]);
                                win.draw(s_nbox4[i]);


                            }*/
                            /* for (int i = 0; i < 14; i++)
                             {
                                 win.draw(s_cbox[i]);

                             }*/
                            for (int i = 0; i < 38; i++) {
                                if (nbox[i] == true) {
                                    win.draw(s_nbox1[i]);
                                    win.draw(s_nbox2[i]);
                                    win.draw(s_nbox3[i]);
                                    win.draw(s_nbox4[i]);
                                }
                            }
                            for (int i = 0; i < 38; i++) {
                                if (_box[i] == true) {
                                    win.draw(s_BOX[i]);
                                }
                            }
                            for (int i = 0; i < 14; i++)
                            {
                                if (_cbox[i] == true) {
                                    win.draw(s_cbox[i]);

                                }


                            }
                            for (int i = 0; i < 14; i++)
                            {
                                if (_ncbox[i] == true) {
                                    win.draw(s_ncbox[i]);
                                }

                            }

                            /*   for (int i = 0; i < 14; i++) {
                                   if (c_draw[i] == true) {
                                       win.draw(s_coins[i]);
                                   }


                                   }*/
                            if (_nb_mash == true)
                            {
                                win.draw(nb_mash);
                            }
                            else if (_b_mash == true)
                            {
                                win.draw(b_mash);
                            }
                            /*
                             for (int i = 0; i < 8; i++)
                             {
                                 win.draw(Up_walk[i]);
                                 win.draw(Down_walk[i]);
                                 win.draw(_pipe[i]);
                             }
                             for (int i = 0; i < 16; i++)
                             {

                                 win.draw(left_walk[i]);
                                 win.draw(right_walk[i]);
                             }*/

                             /* if (second == 10)
                              {

                                  clock.restart();
                                  second = 0;
                                  second_++;
                              }
                              if (second_ == 6)
                              {

                                  clock.restart();
                                  second_ = 0;
                                  menute++;
                              }*/

                            for (int i = 0; i < 24; i++)
                            {
                                win.draw(c_arr[i]);
                            }
                            for (int i = 0; i < 4; i++)
                            {
                                win.draw(dof[i]);
                                win.draw(doc[i]);
                                /* win.draw(daid_d[i]);
                                 win.draw(daid[i]);*/
                            }
                            for (int j = 0; j < 13; j++)
                            {

                                win.draw(text_[j]);
                            }
                            /*   win.draw(pipe3);
                               win.draw(pipe4);
                               win.draw(pipe1);*/
                            if (life_count == 0)
                            {

                                text_[13].setPosition(position.x - 250, 480);
                                win.draw(text_[13]);
                            }
                            /*      win.draw(ccccc);*/
                            win.display();

                        }
                    }
                    if (menu.GetPressedItem() == 1) {
                        // cout << "How To play button had been pressed " << endl;

                        win.clear();
                        while (win.isOpen()) {
                            sf::Event event3;
                            while (win.pollEvent(event3)) {
                                switch (event3.type)
                case sf::Event::Closed:
                                {
                                    win.close();
                                }
                            }

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                break;

                            }



                            win.draw(s_menu_2);
                            win.display();
                        }

                    }
                    else if (menu.GetPressedItem() == 2) {
                        cout << "Option button had been pressed " << endl;
                        win.clear();
                        while (win.isOpen()) {
                            sf::Event event3;
                            while (win.pollEvent(event3)) {
                                switch (event3.type)
                case sf::Event::Closed:
                                {
                                    win.close();
                                }
                            }

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                break;

                            }



                            win.draw(s_about);
                            win.display();
                        }
                    }
                    else   if (menu.GetPressedItem() == 3)
                        win.close();



                }
                }


                break;


            case  sf::Event::Closed:
                win.close();
                break;
            }
        }






        win.clear();
        win.draw(s_menu);
        menu.draw(win);
        win.display();

    }


    return 0;

}