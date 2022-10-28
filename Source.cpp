#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/window.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;
#define bebo ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define el '\n'
// declaration
const int totalballs = 100;
RenderWindow window(VideoMode(900, 800), "bubble shooter", Style::Close);
Event ev;
Music musicgame, soundgame;
RectangleShape menu[20], OpenedLevels[15];
CircleShape StoredBalls[6], movingball[totalballs];
Texture Tbackground, Tbubbles, Tgun, Tanim, Tmen,
Tlevels, Tgif, Tgif2, Tgifnames, TNumOfLevels, Tbicon,
Tcontrol, Tstars, Tcredit, Tboard, Tgameend, Tloading, Tlogo,
Tthemes[4], Tselect_theme, Tloadingbar, Tlodingbackground, Tourphoto, Tpanner;
//__________________________________________________
Sprite back, madf3, gifback[200], Bicon[2], Sgifnames[36],
Sstar[9], upsound, upmusic, downsound, downmusic,
sound, soundMusic, Scredit, anm, Sboard, Sgameend[3],
Sloading[55], Slogo, Sthemes[4], Sselect_theme,
Sloadingbar[161], Sloadingbackground, Sourphoto;
//__________________________________________________
Text textScore, text2, text3, text4, ournames[7], textscore[15], scorelev[15];
Font font;
//__________________________________________________
Vector2f mouspos;
double SlopeBetweenMouse_madf3, centery, centerx, scale = 1, velocityx[totalballs], velcityy[totalballs];
int idxball = rand(), idxball2 = rand(), idxmoves = 0,
x = 150, colorofmoves[totalballs], ballsleft = totalballs,
thescore = 0, an = 0, tot, i = 0, ii = 0, iii = 0, time111 = 0, time11 = 0, time1 = 0, idxvs = 6, idxvm = 3
, currentlev = 1, cntrand = 6, timeanimation = 0, idx = 0, timerloading = 9, idxloading = 0, r = 0, timeL = 0, timeph = 0, ph = 0;
//__________________________________________________
bool balls_with_the_same_color_visited[500][6];
bool visitedmoves[totalballs];
bool visitedbublle[500][6];
bool ispressed = 1;
bool win = 1;
bool pressed = 1;
bool bombb = 0;
bool loading = 0;
bool balls_with_the_same_color_1 = 0;
//__________________________________________________
vector<pair<int, int>> bub_pushed, upbubble;
map<pair<int, int>, vector<pair<int, int>>> adj;
queue<pair<int, int>> q, q2;
stack<string> opened;
ofstream savegame;
//__________________________________________________
struct levels
{
    bool open = 0;
    int score = 0;
    int stars = 0;

} level[11];
struct numbersOfbubbles
{
    CircleShape bubbles_color[6]; // 6 عدد الالوان
    int velocity[6] = {};
} num[500]; // كوره من كل لون 50
//__________________________________________________
struct panners {
    Sprite Spanner[30];
} NAMES[6];
void drawloadingbar() {
    r %= 160;
    timeL++;
    window.clear();
    window.draw(Sloadingbackground);
    if (timeL == 18)
    {
        window.draw(Sloadingbar[r++]);
        timeL = 0;

    }
    else
    {
        window.draw(Sloadingbar[r]);
    }
    window.display();
}
void loadingbar() {
    Tloadingbar.loadFromFile("Assets/Textures/loadingbar.png");
    Tlodingbackground.loadFromFile("Assets/Textures/loadingbackground.png");
    Sloadingbackground.setTexture(Tlodingbackground);
    int q = 0;
    for (int i = 0; i < 5 * 400; i += 400)
    {
        for (int j = 0; j < 32 * 400; j += 400)
        {

            Sloadingbar[q].setTexture(Tloadingbar);
            Sloadingbar[q].setTextureRect(IntRect(i, j, 400, 400));
            Sloadingbar[q].setPosition(450 - 100, 600);
            Sloadingbar[q].setScale(0.5, 0.5);
            q++;
            drawloadingbar();
        }
    }
}
void loadfiles()
{
    drawloadingbar();
    Tbackground.loadFromFile("Assets/Textures/45.png");
    Tgif.loadFromFile("Assets/Textures/gif.jpg");
    Tgif2.loadFromFile("Assets/Textures/gif2.png");
    drawloadingbar();
    // here
    Tgifnames.loadFromFile("Assets/Textures/black.png");
    Tbubbles.loadFromFile("Assets/Textures/color8.png");
    Tgun.loadFromFile("Assets/Textures/madf3.png");
    drawloadingbar();
    Tanim.loadFromFile("Assets/Textures/bomb.png");
    font.loadFromFile("Assets/Textures/Franklin Gothic Heavy Regular.ttf");
    Tmen.loadFromFile("Assets/Textures/menupng.png");
    drawloadingbar();
    Tlevels.loadFromFile("Assets/Textures/levels.png");
    TNumOfLevels.loadFromFile("Assets/Textures/numoflevels.png");
    Tbicon.loadFromFile("Assets/Textures/backicon.png");
    drawloadingbar();
    Tcontrol.loadFromFile("Assets/Textures/control.png");
    Tstars.loadFromFile("Assets/Textures/stars.png");
    Tcredit.loadFromFile("Assets/Textures/credit.png");
    drawloadingbar();
    Tboard.loadFromFile("Assets/Textures/scoreboard.png");
    Tgameend.loadFromFile("Assets/Textures/win.png");
    Tloading.loadFromFile("Assets/Textures/loading.png");
    drawloadingbar();
    Tlogo.loadFromFile("Assets/Textures/logo.png");
    Tthemes[0].loadFromFile("Assets/Textures/bubbles_theme.png");
    Tthemes[1].loadFromFile("Assets/Textures/bubbles2_theme.png");
    drawloadingbar();
    Tthemes[2].loadFromFile("Assets/Textures/heart_theme.png");
    Tthemes[3].loadFromFile("Assets/Textures/fruits_theme.png");
    Tselect_theme.loadFromFile("Assets/Textures/select_theme.png");
    drawloadingbar();
    Tourphoto.loadFromFile("Assets/Textures/ourphotos.png");
    Tpanner.loadFromFile("Assets/Textures/circle.png");;
}
void settextures()
{
    back.setTexture(Tbackground);
    madf3.setTexture(Tgun);
    madf3.setOrigin(99 / 2, 80);
    madf3.setPosition(450 - 99 / 2 + 40, 800 - 126 + 50);
    for (int i = 1; i < 10; i++) {
        scorelev[i].setFont(font);
        textscore[i].setFont(font);
    }
    textScore.setFont(font);
    text2.setFont(font);
    text3.setFont(font);
    text4.setFont(font);
    anm.setTexture(Tanim);
    Slogo.setTexture(Tlogo);
    Slogo.setOrigin(450, 350);
    Slogo.setScale(0.5, 0.5);
    Slogo.setPosition(450, 400);

    //bubbles theme
    Sthemes[0].setTexture(Tthemes[0]);
    Sthemes[0].setTextureRect(IntRect(0, 0, 68, 50));
    Sthemes[0].setScale(2.5, 2.5);
    Sthemes[0].setPosition(50, 500);
    // bubbles 2 theme
    Sthemes[1].setTexture(Tthemes[1]);
    Sthemes[1].setTextureRect(IntRect(0, 0, 60, 52));
    Sthemes[1].setScale(2, 2);
    Sthemes[1].setPosition(225 + 50, 500);
    // hearts theme 
    Sthemes[2].setTexture(Tthemes[2]);
    Sthemes[2].setTextureRect(IntRect(0, 0, 58, 45));
    Sthemes[2].setScale(2, 2);
    Sthemes[2].setPosition(450 + 50, 500);

    // fruits theme
    Sthemes[3].setTexture(Tthemes[3]);
    Sthemes[3].setTextureRect(IntRect(0, 0, 58, 54));
    Sthemes[3].setScale(2, 2);
    Sthemes[3].setPosition(675 + 50, 500);
    // ----
    Sselect_theme.setTexture(Tselect_theme);
    Sselect_theme.setTextureRect(IntRect(0, 0, 996, 268));
    Sselect_theme.setScale(0.5, 0.5);
    Sselect_theme.setPosition(200, 350);
    Sourphoto.setTexture(Tourphoto);
}
//__________________________________________________
void  loadmusic() {
    switch (currentlev) {
    case 1:
        musicgame.openFromFile("Assets/Sounds/BGM_1.ogg");
        musicgame.setLoop(1);
        musicgame.play();
        return;
    case 2:
        musicgame.openFromFile("Assets/Sounds/BGM_2.ogg");
        musicgame.setLoop(1);
        musicgame.play();
        return;
    case 3:
        musicgame.openFromFile("Assets/Sounds/BGM_3.ogg");
        musicgame.setLoop(1);
        musicgame.play();
        return;
    case 4:
        musicgame.openFromFile("Assets/Sounds/BGM_4.ogg");
        musicgame.setLoop(1);
        musicgame.play();
        return;
    case 5:
        musicgame.openFromFile("Assets/Sounds/BGM_5.ogg");
        musicgame.setLoop(1);
        musicgame.play();
        return;
    case 6:
        musicgame.openFromFile("Assets/Sounds/BGM_6.ogg");
        musicgame.setLoop(1);
        musicgame.play();
        return;
    case 7:
        musicgame.openFromFile("Assets/Sounds/BGM_7.ogg");
        musicgame.setLoop(1);
        musicgame.play();
        return;
    case 8:
        musicgame.openFromFile("Assets/Sounds/BGM_8.ogg");
        musicgame.setLoop(1);
        musicgame.play();
        return;
    case 9:
        musicgame.openFromFile("Assets/Sounds/BGM_9.ogg");
        musicgame.setLoop(1);
        musicgame.play();
        return;
    }
}
void Menu()
{
    for (int i = 0; i < 8; i++)
    {
        // play
        if (i == 0)
        {
            menu[i].setTexture(&Tmen);
            menu[i].setSize(Vector2f(250, 130));
            menu[i].setTextureRect(IntRect(0, 5, 250, 130));
            menu[i].setOrigin(125, 65);
            menu[i].setPosition(450 + 3, 150 + 25);
        }
        // levels
        else if (i == 1)
        {
            menu[i].setTexture(&Tlevels);
            menu[i].setSize(Vector2f(320, 130));
            menu[i].setTextureRect(IntRect(0, 265, 320, 130));
            menu[i].setOrigin(160, 65);
            menu[i].setPosition(450 + 10, 300 + 25);
        }
        // opions
        else if (i == 2)
        {
            menu[i].setTexture(&Tmen);
            menu[i].setSize(Vector2f(320, 130));

            menu[i].setTextureRect(IntRect(0, 265, 320, 130));
            menu[i].setOrigin(160, 65);
            menu[i].setPosition(450 + 10, 450 + 25);
        }
        // quit
        else if (i == 3)
        {
            menu[i].setTexture(&Tmen);
            menu[i].setSize(Vector2f(178, 85));

            menu[i].setTextureRect(IntRect(0, 535, 178, 85));
            menu[i].setOrigin(89, 42.5);
            menu[i].setPosition(450, 600);
        }
        // light play
        else if (i == 4)
        {
            menu[i].setTexture(&Tmen);
            menu[i].setSize(Vector2f(250, 130));

            menu[i].setTextureRect(IntRect(0, 138, 250, 130));
            menu[i].setOrigin(125, 65);
            menu[i].setPosition(450 + 3, 150 + 25);
        }
        // light levels
        else if (i == 5)
        {
            menu[i].setTexture(&Tlevels);
            menu[i].setSize(Vector2f(320, 130));
            menu[i].setTextureRect(IntRect(0, 402, 320, 130));
            menu[i].setOrigin(160, 65);
            menu[i].setPosition(450 + 10, 300 + 25);
        }
        // light options
        else if (i == 6)
        {
            menu[i].setTexture(&Tmen);
            menu[i].setSize(Vector2f(320, 130));
            menu[i].setTextureRect(IntRect(0, 402, 320, 130));
            menu[i].setOrigin(160, 65);
            menu[i].setPosition(450 + 10, 450 + 25);
        }
        // light quit
        else if (i == 7)
        {
            menu[i].setTexture(&Tmen);
            menu[i].setSize(Vector2f(178, 85));
            menu[i].setTextureRect(IntRect(0, 633, 178, 85));
            menu[i].setOrigin(89, 42.5);
            menu[i].setPosition(450, 600);
        }
    }
}
void drawmenu()
{
    for (int i = 4; i < 8; i++)
    {
        //  menu[i].setOrigin(0, 0);
        Vector2f mouspos = Vector2f(Mouse::getPosition(window));
        double minx = menu[i].getPosition().x - menu[i].getSize().x / 2.0;
        double maxx = menu[i].getPosition().x + menu[i].getSize().x / 2.0;
        double miny = menu[i].getPosition().y - menu[i].getSize().y / 2.0;
        double maxy = menu[i].getPosition().y + menu[i].getSize().y / 2.0;
        if (mouspos.x > minx && mouspos.x < maxx && mouspos.y > miny && mouspos.y < maxy)
        {
            menu[i - 4].setScale(1.1, 1.1);
            window.draw(menu[i - 4]);
            if (Mouse::isButtonPressed(Mouse::Left) && pressed)
            {
                if (i - 4 == 0) {
                    soundgame.openFromFile("Assets/Sounds/button.ogg");
                    soundgame.play();
                    loadmusic();
                    opened.push("play");
                    pressed = 0;
                }
                else if (i - 4 == 1) {
                    soundgame.openFromFile("Assets/Sounds/button.ogg");
                    soundgame.play();
                    opened.push("levels");
                    pressed = 0;
                }
                else if (i - 4 == 2)
                {
                    soundgame.openFromFile("Assets/Sounds/button.ogg");
                    soundgame.play();
                    opened.push("options");
                    pressed = 0;
                }
                else if (i - 4 == 3)
                {
                    soundgame.openFromFile("Assets/Sounds/button.ogg");
                    soundgame.play();
                    savegame.close();
                    window.close();

                }
                return;
            }
        }
        else
        {
            window.draw(menu[i]);
        }
    }
}
//__________________________________________________

//__________________________________________________
                    // on gameloop//
void gameend()
{
    // if win
    if (opened.top() == "win")
    {
        Sgameend[0].setTexture(Tgameend);
        Sgameend[0].setTextureRect(IntRect(0, 270, 644, 121));
        Sgameend[0].setOrigin(322, 60.5);
        Sgameend[0].setPosition(450, 300);
        //===============================
        // next
        if (currentlev < 9) {
            Sgameend[1].setTexture(Tgameend);
            Sgameend[1].setTextureRect(IntRect(186, 536, 178, 87));
            Sgameend[1].setOrigin(89, 43.5);
            Sgameend[1].setPosition(300, 450);
        }
        else {
            // retry
            Sgameend[1].setTexture(Tgameend);
            Sgameend[1].setTextureRect(IntRect(0, 536, 178, 87));
            Sgameend[1].setOrigin(89, 43.5);
            Sgameend[1].setPosition(300, 450);
        }
    }

    else if (opened.top() == "lose")
    {
        // if lose
        // game over
        Sgameend[0].setTexture(Tgameend);
        Sgameend[0].setTextureRect(IntRect(0, 402, 644, 121));
        Sgameend[0].setOrigin(322, 60.5);
        Sgameend[0].setPosition(450, 300);
        //===============================
        // retry
        Sgameend[1].setTexture(Tgameend);
        Sgameend[1].setTextureRect(IntRect(0, 536, 178, 87));
        Sgameend[1].setOrigin(89, 43.5);
        Sgameend[1].setPosition(300, 450);


    }

    // win and los
    // menu
    Sgameend[2].setTexture(Tgameend);
    Sgameend[2].setTextureRect(IntRect(368, 536, 178, 87));
    Sgameend[2].setOrigin(178 / 2.0, 87 / 2.0);
    Sgameend[2].setPosition(600, 450);

    // 663

    if (opened.top() == "lose" || currentlev == 9)
    {
        // retry
        if (mouspos.x > 300 - 89 && mouspos.x < 300 + 89 && mouspos.y > 450 - 43.5 && mouspos.y < 450 + 43.5)
        {
            Sgameend[1].setTextureRect(IntRect(0, 633, 178, 87));

        }
        else
        {
            Sgameend[1].setTextureRect(IntRect(0, 536, 178, 87));
        }
    }
    else if (opened.top() == "win" && currentlev != 9)
    {
        // next
        if (mouspos.x > 300 - 89 && mouspos.x < 300 + 89 && mouspos.y > 450 - 43.5 && mouspos.y < 450 + 43.5)
        {
            Sgameend[1].setTextureRect(IntRect(186, 633, 178, 87));

        }
        else
        {
            Sgameend[1].setTextureRect(IntRect(186, 536, 178, 87));
        }
    }
    if (opened.top() == "win" || opened.top() == "lose") {
        // menu

        if (mouspos.x > 600 - 89 && mouspos.x < 600 + 89 && mouspos.y > 450 - 43.5 && mouspos.y < 450 + 43.5) {
            Sgameend[2].setTextureRect(IntRect(368, 633, 178, 87));
        }
        else {
            Sgameend[2].setTextureRect(IntRect(368, 536, 178, 87));
        }
    }

}
void draw_my_graph()
{

    for (int numb = 0; numb < x; numb++)
    {
        for (int color = 0; color < 6; color++)
        {
            if (num[numb].bubbles_color[color].getTexture() == (&Tbubbles))
            {
                for (int i = 0; i < x; i++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        if (num[i].bubbles_color[j].getTexture() == (&Tbubbles) && !(i == numb && j == color))
                        {
                            double x = num[numb].bubbles_color[color].getPosition().x - num[i].bubbles_color[j].getPosition().x;
                            double y = num[numb].bubbles_color[color].getPosition().y - num[i].bubbles_color[j].getPosition().y;
                            double len = sqrt(x * x + y * y);
                            if (len < 32 * scale + 15 / 64.0 * (32 * scale))
                            {
                                adj[{numb, color}].push_back({ i, j });
                            }
                        }
                    }
                }
            }
        }
    }
}
// store bubbles which are on the madf3 on game
void store()
{
    // storage in 6 colors
     // Because when I click on the left, I can take any color from it I want
    for (int i = 0; i < 6; i++)
    {
        StoredBalls[i].setTexture(&Tbubbles);
        StoredBalls[i].setRadius(16);
        StoredBalls[i].setTextureRect(IntRect(0, i * 32, 32, 32));
        StoredBalls[i].setOrigin(16, 16);
        StoredBalls[i].scale(1.3, 1.3);
        StoredBalls[i].setPosition(450 - 99 / 2 + 40, 800 - 126 + 52);
    }
}
void score()
{
    textScore.setString("Score : ");
    textScore.setPosition(10, 710);
    stringstream ss;
    ss << thescore;
    string stemp = ss.str();
    text2.setString(stemp);
    text2.setPosition(120, 710);
    text2.setFillColor(Color::White);
}
void numballs()
{
    text3.setString("Balls : ");
    text3.setPosition(10, 760);
    text3.setFillColor(Color::Yellow);

    stringstream ss;
    ss << ballsleft;
    string stemp = ss.str();
    text4.setString(stemp);
    text4.setPosition(120, 760);
    if (ballsleft <= 3)
    {
        text4.setFillColor(Color::Red);
    }
    else
        text4.setFillColor(Color::White);
}
//load new game 
void bring_bubbles_lev1() {
    loading = 1;
    musicgame.openFromFile("Assets/Sounds/BGM_1.ogg");
    musicgame.setLoop(1);
    musicgame.play();
    Tbackground.loadFromFile("Assets/Textures/lev1.jpg");
    currentlev = 1;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            if (num[j].bubbles_color[i].getTexture() == (&Tbubbles)) {
                adj[{j, i}].clear();
                num[j].bubbles_color[i].setPosition(2000, 2000);
                visitedbublle[j][i] = 0;
                num[j].velocity[i] = 0;
            }

        }
    }
    int totalballs = 15;
    tot = totalballs;
    idxball = rand(), idxball2 = rand(), idxmoves = 0, x = 150, ballsleft = totalballs,
        thescore = 0, an = 0;
    memset(visitedmoves, 0, size(visitedmoves));
    memset(velocityx, 0, size(velocityx));
    memset(velcityy, 0, size(velcityy));
    bub_pushed.clear();
    upbubble.clear();
    score();
    numballs();
    int purple = 0;
    int blue = 0;
    int yellow = 0;
    int green = 0;
    int black = 0;
    int red = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 14; j++) {
            if ((i == 0 && j >= 12 && j <= 13) ||
                (i == 1 && j >= 11 && j <= 12) ||
                (i == 2 && j >= 11 && j <= 12) ||
                (i == 3 && j >= 10 && j <= 11) ||
                (i == 4 && j >= 10 && j <= 11) ||
                (i == 5 && j >= 9 && j <= 10) ||
                (i == 6 && j >= 9 && j <= 10))
            {
                num[purple].bubbles_color[5].setTexture(&Tbubbles);
                num[purple].bubbles_color[5].setRadius(16);
                num[purple].bubbles_color[5].setOrigin(16, 16);
                num[purple].bubbles_color[5].setScale(2, 2);
                num[purple].bubbles_color[5].setTextureRect(IntRect(0, (5) * 32, 32, 32));
                num[purple].bubbles_color[5].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                purple++;
            }
            else if ((i == 0 && j >= 10 && j <= 11) ||
                (i == 1 && j >= 9 && j <= 10) ||
                (i == 2 && j >= 9 && j <= 10) ||
                (i == 3 && j >= 8 && j <= 9) ||
                (i == 4 && j >= 8 && j <= 9) ||
                (i == 5 && j >= 7 && j <= 8) ||
                (i == 6 && j >= 7 && j <= 8) ||
                (i == 0 && (j == 0 || j == 1)) ||
                (i == 1 && j == 0) ||
                (i == 2 && j == 0)
                )
            {
                num[blue].bubbles_color[4].setTexture(&Tbubbles);
                num[blue].bubbles_color[4].setRadius(16);
                num[blue].bubbles_color[4].setOrigin(16, 16);
                num[blue].bubbles_color[4].setScale(2, 2);
                num[blue].bubbles_color[4].setTextureRect(IntRect(0, (4) * 32, 32, 32));
                num[blue].bubbles_color[4].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                blue++;
            }
            else if ((i == 0 && j >= 8 && j <= 9) ||
                (i == 1 && j >= 7 && j <= 8) ||
                (i == 2 && j >= 7 && j <= 8) ||
                (i == 3 && j >= 6 && j <= 7) ||
                (i == 4 && j >= 6 && j <= 7) ||
                (i == 5 && j >= 5 && j <= 6) ||
                (i == 6 && j >= 5 && j <= 6) ||
                (i == 2 && j == 13) ||
                (i == 3 && j == 12) ||
                (i == 4 && (j == 12 || j == 13)) ||
                (i == 5 && (j == 11 || j == 12)) ||
                (i == 6 && j >= 11 && j <= 13)


                )


            {
                num[green].bubbles_color[3].setTexture(&Tbubbles);
                num[green].bubbles_color[3].setRadius(16);
                num[green].bubbles_color[3].setOrigin(16, 16);
                num[green].bubbles_color[3].setScale(2, 2);
                num[green].bubbles_color[3].setTextureRect(IntRect(0, (3) * 32, 32, 32));
                num[green].bubbles_color[3].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                green++;
            }
            else if ((i == 0 && j >= 6 && j <= 7) ||
                (i == 1 && j >= 5 && j <= 6) ||
                (i == 2 && j >= 5 && j <= 6) ||
                (i == 3 && j >= 4 && j <= 5) ||
                (i == 4 && j >= 4 && j <= 5) ||
                (i == 5 && j >= 3 && j <= 4) ||
                (i == 6 && j >= 3 && j <= 4))
            {
                num[red].bubbles_color[0].setTexture(&Tbubbles);
                num[red].bubbles_color[0].setRadius(16);
                num[red].bubbles_color[0].setOrigin(16, 16);
                num[red].bubbles_color[0].setScale(2, 2);
                num[red].bubbles_color[0].setTextureRect(IntRect(0, 0 * 32, 32, 32));
                num[red].bubbles_color[0].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                red++;
            }
            else if ((i == 0 && j >= 4 && j <= 5) ||
                (i == 1 && j >= 3 && j <= 4) ||
                (i == 2 && j >= 3 && j <= 4) ||
                (i == 3 && j >= 2 && j <= 3) ||
                (i == 4 && j >= 2 && j <= 3) ||
                (i == 5 && j >= 1 && j <= 2) ||
                (i == 6 && j >= 1 && j <= 2))
            {
                num[yellow].bubbles_color[2].setTexture(&Tbubbles);
                num[yellow].bubbles_color[2].setRadius(16);
                num[yellow].bubbles_color[2].setOrigin(16, 16);
                num[yellow].bubbles_color[2].setScale(2, 2);
                num[yellow].bubbles_color[2].setTextureRect(IntRect(0, 2 * 32, 32, 32));
                num[yellow].bubbles_color[2].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                yellow++;
            }
            else if ((i == 0 && j >= 2 && j <= 3) ||
                (i == 1 && j >= 1 && j <= 2) ||
                (i == 2 && j >= 1 && j <= 2) ||
                (i == 3 && j >= 0 && j <= 1) ||
                (i == 4 && j >= 0 && j <= 1) ||
                (i == 5 && j == 0) ||
                (i == 6 && j == 0))
            {
                num[black].bubbles_color[1].setTexture(&Tbubbles);
                num[black].bubbles_color[1].setRadius(16);
                num[black].bubbles_color[1].setOrigin(16, 16);
                num[black].bubbles_color[1].setScale(2, 2);
                num[black].bubbles_color[1].setTextureRect(IntRect(0, 1 * 32, 32, 32));
                num[black].bubbles_color[1].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                black++;
            }

        }
    }
    scale = num[0].bubbles_color[0].getScale().x;
    draw_my_graph();
}
void bring_bubbles_lev2() {
    currentlev = 2;
    loading = 1;
    musicgame.openFromFile("Assets/Sounds/BGM_2.ogg");
    musicgame.setLoop(1);
    musicgame.play();
    Tbackground.loadFromFile("lev2.jfif");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            if (num[j].bubbles_color[i].getTexture() == (&Tbubbles)) {
                adj[{j, i}].clear();
                num[j].bubbles_color[i].setPosition(2000, 2000);
                visitedbublle[j][i] = 0;
                num[j].velocity[i] = 0;
            }

        }
    }
    int totalballs = 15;
    tot = totalballs;
    idxball = rand(), idxball2 = rand(), idxmoves = 0, x = 150, ballsleft = totalballs,
        thescore = 0, an = 0;
    memset(visitedmoves, 0, size(visitedmoves));
    memset(velocityx, 0, size(velocityx));
    memset(velcityy, 0, size(velcityy));
    bub_pushed.clear();
    upbubble.clear();
    score();
    numballs();
    int purple = 0;
    int blue = 0;
    int yellow = 0;
    int green = 0;
    int black = 0;
    int red = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 14; j++) {
            if ((i == 0 && j >= 0 && j <= 6) ||
                (i == 1 && j >= 0 && j <= 6))
            {
                num[purple].bubbles_color[5].setTexture(&Tbubbles);
                num[purple].bubbles_color[5].setRadius(16);
                num[purple].bubbles_color[5].setOrigin(16, 16);
                num[purple].bubbles_color[5].setScale(2, 2);
                num[purple].bubbles_color[5].setTextureRect(IntRect(0, (5) * 32, 32, 32));
                num[purple].bubbles_color[5].setPosition((64 * j + 32), 64 * (i)+32);
                purple++;
            }
            else if ((i == 0 && j >= 7 && j <= 14) ||
                (i == 1 && j >= 7 && j <= 14)) {
                num[blue].bubbles_color[4].setTexture(&Tbubbles);
                num[blue].bubbles_color[4].setRadius(16);
                num[blue].bubbles_color[4].setOrigin(16, 16);
                num[blue].bubbles_color[4].setScale(2, 2);
                num[blue].bubbles_color[4].setTextureRect(IntRect(0, (4) * 32, 32, 32));
                num[blue].bubbles_color[4].setPosition((64 * j + 32), 64 * (i)+32);
                blue++;
            }

            else if ((i == 2 && j >= 0 && j <= 6) ||
                (i == 3 && j >= 0 && j <= 6)) {
                num[green].bubbles_color[3].setTexture(&Tbubbles);
                num[green].bubbles_color[3].setRadius(16);
                num[green].bubbles_color[3].setOrigin(16, 16);
                num[green].bubbles_color[3].setScale(2, 2);
                num[green].bubbles_color[3].setTextureRect(IntRect(0, (3) * 32, 32, 32));
                num[green].bubbles_color[3].setPosition((64 * j + 32), 64 * (i)+32);
                green++;
            }
            else if ((i == 2 && j >= 7 && j <= 14) ||
                (i == 3 && j >= 7 && j <= 14)) {
                num[red].bubbles_color[0].setTexture(&Tbubbles);
                num[red].bubbles_color[0].setRadius(16);
                num[red].bubbles_color[0].setOrigin(16, 16);
                num[red].bubbles_color[0].setScale(2, 2);
                num[red].bubbles_color[0].setTextureRect(IntRect(0, 0 * 32, 32, 32));
                num[red].bubbles_color[0].setPosition((64 * j + 32), 64 * (i)+32);
                red++;

            }

            else if ((i == 4 && j >= 0 && j <= 6) ||
                (i == 5 && j >= 0 && j <= 6)) {
                num[yellow].bubbles_color[2].setTexture(&Tbubbles);
                num[yellow].bubbles_color[2].setRadius(16);
                num[yellow].bubbles_color[2].setOrigin(16, 16);
                num[yellow].bubbles_color[2].setScale(2, 2);
                num[yellow].bubbles_color[2].setTextureRect(IntRect(0, 2 * 32, 32, 32));
                num[yellow].bubbles_color[2].setPosition((64 * j + 32), 64 * (i)+32);
                yellow++;
            }
            else if ((i == 4 && j >= 7 && j <= 14) ||
                (i == 5 && j >= 7 && j <= 14)) {
                num[black].bubbles_color[1].setTexture(&Tbubbles);
                num[black].bubbles_color[1].setRadius(16);
                num[black].bubbles_color[1].setOrigin(16, 16);
                num[black].bubbles_color[1].setScale(2, 2);
                num[black].bubbles_color[1].setTextureRect(IntRect(0, 1 * 32, 32, 32));
                num[black].bubbles_color[1].setPosition((64 * j + 32), 64 * (i)+32);
                black++;
            }
        }
    }
    scale = num[0].bubbles_color[0].getScale().x;
    draw_my_graph();
}
void bring_bubbles_lev3() {
    currentlev = 3;
    loading = 1;
    musicgame.openFromFile("Assets/Sounds/BGM_3.ogg");
    musicgame.setLoop(1);
    musicgame.play();
    Tbackground.loadFromFile("Assets/Textures/lev3.jpg");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            if (num[j].bubbles_color[i].getTexture() == (&Tbubbles)) {
                adj[{j, i}].clear();
                num[j].bubbles_color[i].setPosition(2000, 2000);
                visitedbublle[j][i] = 0;
                num[j].velocity[i] = 0;
            }

        }
    }
    int totalballs = 20;
    tot = totalballs;
    idxball = rand(), idxball2 = rand(), idxmoves = 0, x = 150, ballsleft = totalballs,
        thescore = 0, an = 0;
    memset(visitedmoves, 0, size(visitedmoves));
    memset(velocityx, 0, size(velocityx));
    memset(velcityy, 0, size(velcityy));
    bub_pushed.clear();
    upbubble.clear();
    score();
    numballs();
    int purple = 0;
    int blue = 0;
    int yellow = 0;
    int green = 0;
    int black = 0;
    int red = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 14; j++) {
            if (
                (i == 1 && (j == 0 || j == 13)) ||
                (i == 2 && (j == 0 || j == 13)) ||
                (i == 3 && (j == 0 || j == 13)) ||
                (i == 4 && (j == 0 || j == 13)) ||
                (i == 5 && (j == 0 || j == 13)) ||
                (i == 6) ||
                (i == 0 && (j == 0 || j == 13)))

            {
                num[purple].bubbles_color[5].setTexture(&Tbubbles);
                num[purple].bubbles_color[5].setRadius(16);
                num[purple].bubbles_color[5].setOrigin(16, 16);
                num[purple].bubbles_color[5].setScale(2, 2);
                num[purple].bubbles_color[5].setTextureRect(IntRect(0, (5) * 32, 32, 32));
                num[purple].bubbles_color[5].setPosition((32 + j * 64), (i * 64 + 32));
                purple++;
            }
            else if (
                (i == 1 && (j == 1 || j == 12)) ||
                (i == 2 && (j == 1 || j == 12)) ||
                (i == 3 && (j == 1 || j == 12)) ||
                (i == 4 && (j == 1 || j == 12)) ||
                (i == 5 && (j >= 1 || j <= 12)) ||
                (i == 0 && (j == 1 || j == 12)))
            {
                num[blue].bubbles_color[4].setTexture(&Tbubbles);
                num[blue].bubbles_color[4].setRadius(16);
                num[blue].bubbles_color[4].setOrigin(16, 16);
                num[blue].bubbles_color[4].setScale(2, 2);
                num[blue].bubbles_color[4].setTextureRect(IntRect(0, (4) * 32, 32, 32));
                num[blue].bubbles_color[4].setPosition((32 + j * 64), (i * 64 + 32));
                blue++;
            }
            else if (
                (i == 1 && (j == 2 || j == 11)) ||
                (i == 2 && (j == 2 || j == 11)) ||
                (i == 3 && (j == 2 || j == 11)) ||
                (i == 4 && (j >= 2 || j <= 11))
                ||
                (i == 0 && (j == 2 || j == 11)))
            {
                num[green].bubbles_color[3].setTexture(&Tbubbles);
                num[green].bubbles_color[3].setRadius(16);
                num[green].bubbles_color[3].setOrigin(16, 16);
                num[green].bubbles_color[3].setScale(2, 2);
                num[green].bubbles_color[3].setTextureRect(IntRect(0, (3) * 32, 32, 32));
                num[green].bubbles_color[3].setPosition((32 + j * 64), (i * 64 + 32));
                green++;
            }
            else if (
                (i == 1 && (j == 3 || j == 10)) ||
                (i == 2 && (j == 3 || j == 10)) ||
                (i == 3 && (j >= 3 || j <= 10)) ||
                (i == 0 && (j == 3 || j == 10)))
            {
                num[red].bubbles_color[0].setTexture(&Tbubbles);
                num[red].bubbles_color[0].setRadius(16);
                num[red].bubbles_color[0].setOrigin(16, 16);
                num[red].bubbles_color[0].setScale(2, 2);
                num[red].bubbles_color[0].setTextureRect(IntRect(0, 0 * 32, 32, 32));
                num[red].bubbles_color[0].setPosition((32 + j * 64), (i * 64 + 32));
                red++;
            }
            else if (
                (i == 1 && (j == 4 || j == 9)) ||
                (i == 2 && (j >= 4 || j <= 9)) ||
                (i == 0 && (j == 4 || j == 9)))
            {
                num[yellow].bubbles_color[2].setTexture(&Tbubbles);
                num[yellow].bubbles_color[2].setRadius(16);
                num[yellow].bubbles_color[2].setOrigin(16, 16);
                num[yellow].bubbles_color[2].setScale(2, 2);
                num[yellow].bubbles_color[2].setTextureRect(IntRect(0, 2 * 32, 32, 32));
                num[yellow].bubbles_color[2].setPosition((32 + j * 64), (i * 64 + 32));
                yellow++;
            }
            else if (
                (i == 1 && (j >= 5 || j <= 8))
                || (i == 0 && (j == 5 || j == 6 || j == 7 || j == 8))
                )
            {
                num[black].bubbles_color[1].setTexture(&Tbubbles);
                num[black].bubbles_color[1].setRadius(16);
                num[black].bubbles_color[1].setOrigin(16, 16);
                num[black].bubbles_color[1].setScale(2, 2);
                num[black].bubbles_color[1].setTextureRect(IntRect(0, 1 * 32, 32, 32));
                num[black].bubbles_color[1].setPosition((32 + j * 64), (i * 64 + 32));
                black++;
            }
        }
    }
    scale = num[0].bubbles_color[0].getScale().x;
    draw_my_graph();
}
void bring_bubbles_lev4()
{
    currentlev = 4;
    loading = 1;
    musicgame.openFromFile("Assets/Sounds/BGM_4.ogg");
    musicgame.setLoop(1);
    musicgame.play();
    Tbackground.loadFromFile("Assets/Textures/lev4.jpg");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            if (num[j].bubbles_color[i].getTexture() == (&Tbubbles)) {
                adj[{j, i}].clear();
                num[j].bubbles_color[i].setPosition(2000, 2000);
                visitedbublle[j][i] = 0;
                num[j].velocity[i] = 0;
            }

        }
    }
    int totalballs = 20;
    tot = totalballs;
    idxball = rand(), idxball2 = rand(), idxmoves = 0, x = 60, ballsleft = totalballs, thescore = 0, an = 0;
    score();
    numballs();
    memset(visitedmoves, 0, size(visitedmoves));
    memset(velocityx, 0, size(velocityx));
    memset(velcityy, 0, size(velcityy));
    bub_pushed.clear();
    upbubble.clear();
    // الكور اللي فوق
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            if ((i % 2) && j == 13)
            {
                break;
            }

            num[j].bubbles_color[i].setTexture(&Tbubbles);
            num[j].bubbles_color[i].setRadius(16);
            num[j].bubbles_color[i].setOrigin(16, 16);
            num[j].bubbles_color[i].setScale(2, 2);
            num[j].bubbles_color[i].setTextureRect(IntRect(0, (i) * 32, 32, 32));
            num[j].bubbles_color[i].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)-4 * (i)+32);
        }
    }
    scale = num[0].bubbles_color[0].getScale().x;
    draw_my_graph();
}
void bring_bubbles_lev5()
{
    currentlev = 5;
    loading = 1;
    musicgame.openFromFile("Assets/Sounds/BGM_5.ogg");
    musicgame.setLoop(1);
    musicgame.play();
    Tbackground.loadFromFile("Assets/Textures/lev5.png");

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            if (num[j].bubbles_color[i].getTexture() == (&Tbubbles)) {
                adj[{j, i}].clear();
                num[j].bubbles_color[i].setPosition(2000, 2000);
                visitedbublle[j][i] = 0;
                num[j].velocity[i] = 0;
            }

        }
    }
    int totalballs = 15;
    tot = totalballs;
    idxball = rand(), idxball2 = rand(), idxmoves = 0, x = 100, ballsleft = totalballs, thescore = 0, an = 0;
    memset(visitedmoves, 0, size(visitedmoves));
    memset(velocityx, 0, size(velocityx));
    memset(velcityy, 0, size(velcityy));
    bub_pushed.clear();
    upbubble.clear();
    score();
    numballs();
    // الكور اللي فوق
    int purple = 0;
    int blue = 0;
    int yellow = 0;
    int green = 0;
    int black = 0;
    int red = 0;
    int skip = 0;
    // الكور اللي فوق
    for (int i = 0; i < 7; i++)
    {
        if (i % 2 == 0)
            skip++;
        for (int j = 0; j < 14; j++)
        {
            if ((i % 2) && j == 13)
            {
                break;
            }

            if ((i == 1 && j >= 4 && j <= 8) || (i == 2 && j >= 5 && j <= 8) || (i == 3 && j >= 5 && j <= 7) || (i == 4 && j >= 6 && j <= 7) || (i == 5 && j == 6))
            {
                num[purple].bubbles_color[5].setTexture(&Tbubbles);
                num[purple].bubbles_color[5].setRadius(16);
                num[purple].bubbles_color[5].setOrigin(16, 16);
                num[purple].bubbles_color[5].setScale(2, 2);
                num[purple].bubbles_color[5].setTextureRect(IntRect(0, (5) * 32, 32, 32));
                num[purple].bubbles_color[5].setPosition(!(i % 2) ? (64 * j + 32) :
                    (32 + 64 * j + 32), 64 * (i)+32);
                purple++;
            }

            else if (i < 4 && j < skip)
            {

                num[blue].bubbles_color[4].setTexture(&Tbubbles);
                num[blue].bubbles_color[4].setRadius(16);
                num[blue].bubbles_color[4].setOrigin(16, 16);
                num[blue].bubbles_color[4].setScale(2, 2);
                num[blue].bubbles_color[4].setTextureRect(IntRect(0, (4) * 32, 32, 32));
                num[blue].bubbles_color[4].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                blue++;
            }

            else if (i >= 4 && j < skip)
            {
                num[green].bubbles_color[3].setTexture(&Tbubbles);
                num[green].bubbles_color[3].setRadius(16);
                num[green].bubbles_color[3].setOrigin(16, 16);
                num[green].bubbles_color[3].setScale(2, 2);
                num[green].bubbles_color[3].setTextureRect(IntRect(0, (3) * 32, 32, 32));
                num[green].bubbles_color[3].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                green++;
            }
            else if ((j == skip || (i % 2 == 0 && j == 14 - skip - 1) || (i % 2 && j == 13 - skip - 1)) || (j == skip + 1 || (i % 2 == 0 && j == 14 - skip - 2) || (i % 2 && j == 13 - skip - 2)))
            {
                num[red].bubbles_color[0].setTexture(&Tbubbles);
                num[red].bubbles_color[0].setRadius(16);
                num[red].bubbles_color[0].setOrigin(16, 16);
                num[red].bubbles_color[0].setScale(2, 2);
                num[red].bubbles_color[0].setTextureRect(IntRect(0, 0 * 32, 32, 32));
                num[red].bubbles_color[0].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                red++;
            }

            else if (j >= skip && (i % 2 == 0 && j < 14 - skip) || (i % 2 && j < 13 - skip))
            {

                num[yellow].bubbles_color[2].setTexture(&Tbubbles);
                num[yellow].bubbles_color[2].setRadius(16);
                num[yellow].bubbles_color[2].setOrigin(16, 16);
                num[yellow].bubbles_color[2].setScale(2, 2);
                num[yellow].bubbles_color[2].setTextureRect(IntRect(0, 2 * 32, 32, 32));
                num[yellow].bubbles_color[2].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                yellow++;
            }
            else if (i < 4)
            {
                num[blue].bubbles_color[4].setTexture(&Tbubbles);
                num[blue].bubbles_color[4].setRadius(16);
                num[blue].bubbles_color[4].setOrigin(16, 16);
                num[blue].bubbles_color[4].setScale(2, 2);
                num[blue].bubbles_color[4].setTextureRect(IntRect(0, (4) * 32, 32, 32));
                num[blue].bubbles_color[4].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                blue++;
            }
            else
            {
                num[black].bubbles_color[1].setTexture(&Tbubbles);
                num[black].bubbles_color[1].setRadius(16);
                num[black].bubbles_color[1].setOrigin(16, 16);
                num[black].bubbles_color[1].setScale(2, 2);
                num[black].bubbles_color[1].setTextureRect(IntRect(0, 1 * 32, 32, 32));
                num[black].bubbles_color[1].setPosition(!(i % 2) ? (64 * j + 32) : (32 + 64 * j + 32), 64 * (i)+32);
                black++;
            }
        }
    }
    scale = num[1].bubbles_color[1].getScale().x;
    draw_my_graph();
}
void bring_bubbles_lev6() {
    currentlev = 6;
    loading = 1;

    musicgame.openFromFile("Assets/Sounds/BGM_6.ogg");
    musicgame.setLoop(1);
    musicgame.play();
    Tbackground.loadFromFile("Assets/Textures/lev6.jpg");

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            if (num[j].bubbles_color[i].getTexture() == (&Tbubbles)) {
                adj[{j, i}].clear();
                num[j].bubbles_color[i].setPosition(2000, 2000);
                visitedbublle[j][i] = 0;
                num[j].velocity[i] = 0;
            }

        }
    }
    int totalballs = 15;
    tot = totalballs;
    idxball = rand(), idxball2 = rand(), idxmoves = 0, x = 150, ballsleft = totalballs,
        thescore = 0, an = 0;
    memset(visitedmoves, 0, size(visitedmoves));
    memset(velocityx, 0, size(velocityx));
    memset(velcityy, 0, size(velcityy));
    bub_pushed.clear();
    upbubble.clear();
    score();
    numballs();
    int purple = 0;
    int blue = 0;
    int yellow = 0;
    int green = 0;
    int black = 0;
    int red = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            if ((i == 1 && j >= 0 && j <= 4) ||
                (i == 1 && j >= 15 && j <= 19) ||
                (i == 2 && j == 4) ||
                (i == 2 && j == 14) ||
                (i == 3 && j == 5) ||
                (i == 3 && j == 14) ||
                (i == 4 && j == 5) ||
                (i == 4 && j == 13) ||
                (i == 5 && j == 5) ||
                (i == 5 && j == 14) ||
                (i == 6 && j == 4) ||
                (i == 6 && j == 14)

                )
            {
                num[purple].bubbles_color[5].setTexture(&Tbubbles);
                num[purple].bubbles_color[5].setRadius(16);
                num[purple].bubbles_color[5].setOrigin(16, 16);
                num[purple].bubbles_color[5].setScale(1.4, 1.4);
                num[purple].bubbles_color[5].setTextureRect(IntRect(0, (5) * 32, 32, 32));
                if (i % 2 != 0)
                    num[purple].bubbles_color[5].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[purple].bubbles_color[5].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                purple++;
            }
            if ((i == 0 && j >= 0 && j <= 7) ||
                (i == 0 && j >= 11 && j <= 18) ||
                (i == 2 && j >= 0 && j <= 3) ||
                (i == 2 && j >= 15 && j <= 18) ||
                (i == 3 && j == 4) ||
                (i == 3 && j == 15) ||
                (i == 4 && j == 4) ||
                (i == 4 && j == 14) ||
                (i == 5 && j == 4) ||
                (i == 5 && j == 15) ||
                (i == 6 && j == 3) ||
                (i == 6 && j == 15)
                )
            {
                num[blue].bubbles_color[4].setTexture(&Tbubbles);
                num[blue].bubbles_color[4].setRadius(16);
                num[blue].bubbles_color[4].setOrigin(16, 16);
                num[blue].bubbles_color[4].setScale(1.4, 1.4);
                num[blue].bubbles_color[4].setTextureRect(IntRect(0, (4) * 32, 32, 32));
                if (i % 2 != 0)
                    num[blue].bubbles_color[4].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[blue].bubbles_color[4].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                blue++;
            }
            else if ((i == 0 && j == 9) ||
                (i == 1 && (j == 9 || j == 10)) ||
                (i == 2 && j >= 6 && j <= 12) ||
                (i == 3 && j >= 7 && j <= 12) ||
                (i == 4 && j >= 7 && j <= 11) ||
                (i == 5 && j >= 7 && j <= 12) ||
                (i == 6 && j >= 6 && j <= 12) ||
                (i == 7 && (j == 9 || j == 10)) ||
                (i == 8 && j == 9)
                )
            {
                num[green].bubbles_color[3].setTexture(&Tbubbles);
                num[green].bubbles_color[3].setRadius(16);
                num[green].bubbles_color[3].setOrigin(16, 16);
                num[green].bubbles_color[3].setScale(1.4, 1.4);
                num[green].bubbles_color[3].setTextureRect(IntRect(0, (3) * 32, 32, 32));
                if (i % 2 != 0)
                    num[green].bubbles_color[3].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[green].bubbles_color[3].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                green++;
            }
            else if ((i == 3 && j >= 0 && j <= 3) ||
                (i == 3 && j >= 16 && j <= 19) ||
                (i == 4 && j == 3) ||
                (i == 4 && j == 15) ||
                (i == 5 && j == 3) ||
                (i == 5 && j == 16) ||
                (i == 6 && j == 2) ||
                (i == 6 && j == 16)

                )
            {
                num[red].bubbles_color[0].setTexture(&Tbubbles);
                num[red].bubbles_color[0].setRadius(16);
                num[red].bubbles_color[0].setOrigin(16, 16);
                num[red].bubbles_color[0].setScale(1.4, 1.4);
                num[red].bubbles_color[0].setTextureRect(IntRect(0, 0 * 32, 32, 32));
                if (i % 2 != 0)
                    num[red].bubbles_color[0].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[red].bubbles_color[0].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                red++;
            }
            else if ((i == 0 && (j == 8 || j == 10)) ||
                (i == 1 && j >= 5 && j <= 8) ||
                (i == 1 && j >= 11 && j <= 14) ||
                (i == 2 && j == 5) ||
                (i == 2 && j == 13) ||
                (i == 3 && j == 6) ||
                (i == 3 && j == 13) ||
                (i == 4 && j == 6) ||
                (i == 4 && j == 12) ||
                (i == 5 && j == 6) ||
                (i == 5 && j == 13) ||
                (i == 6 && j == 5) ||
                (i == 6 && j == 13) ||
                (i == 7 && j >= 5 && j <= 8) ||
                (i == 7 && j >= 11 && j <= 14) ||
                (i == 8 && (j == 8 || j == 10)) ||
                (i == 9 && (j == 9 || j == 10))
                )
            {
                num[yellow].bubbles_color[2].setTexture(&Tbubbles);
                num[yellow].bubbles_color[2].setRadius(16);
                num[yellow].bubbles_color[2].setOrigin(16, 16);
                num[yellow].bubbles_color[2].setScale(1.4, 1.4);
                num[yellow].bubbles_color[2].setTextureRect(IntRect(0, 2 * 32, 32, 32));
                if (i % 2 != 0)
                    num[yellow].bubbles_color[2].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[yellow].bubbles_color[2].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                yellow++;
            }
            else if ((i == 4 && j >= 0 && j <= 2) ||
                (i == 4 && j >= 16 && j <= 18) ||
                (i == 5 && j >= 0 && j <= 2) ||
                (i == 5 && j >= 17 && j <= 18) ||
                (i == 6 && j >= 0 && j <= 1) ||
                (i == 6 && j >= 17 && j <= 18)
                )
            {
                num[black].bubbles_color[1].setTexture(&Tbubbles);
                num[black].bubbles_color[1].setRadius(16);
                num[black].bubbles_color[1].setOrigin(16, 16);
                num[black].bubbles_color[1].setScale(1.4, 1.4);
                num[black].bubbles_color[1].setTextureRect(IntRect(0, 1 * 32, 32, 32));
                if (i % 2 != 0)
                    num[black].bubbles_color[1].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[black].bubbles_color[1].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                black++;
            }
        }
    }
    scale = num[1].bubbles_color[1].getScale().x;
    draw_my_graph();
}
void bring_bubbles_lev7()
{
    musicgame.openFromFile("Assets/Sounds/BGM_7.ogg");
    musicgame.setLoop(1);
    musicgame.play();
    Tbackground.loadFromFile("Assets/Textures/lev7.jpg");
    loading = 1;
    currentlev = 7;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            if (num[j].bubbles_color[i].getTexture() == (&Tbubbles)) {
                adj[{j, i}].clear();
                num[j].bubbles_color[i].setPosition(2000, 2000);
                visitedbublle[j][i] = 0;
                num[j].velocity[i] = 0;
            }

        }
    }
    int totalballs = 15;
    tot = totalballs;
    idxball = rand(), idxball2 = rand(), idxmoves = 0, x = 150, ballsleft = totalballs,
        thescore = 0, an = 0;
    memset(visitedmoves, 0, size(visitedmoves));
    memset(velocityx, 0, size(velocityx));
    memset(velcityy, 0, size(velcityy));
    bub_pushed.clear();
    upbubble.clear();
    score();
    numballs();
    int purple = 0;
    int blue = 0;
    int yellow = 0;
    int green = 0;
    int black = 0;
    int red = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (
                (i == 0 && j >= 5 && j <= 14) ||
                (i == 1 && j >= 5 && j <= 13) ||
                (i == 2 && j >= 6 && j <= 13) ||
                (i == 3 && j >= 6 && j <= 12) ||
                (i == 4 && j >= 7 && j <= 12) ||
                (i == 5 && j >= 7 && j <= 11) ||
                (i == 6 && j >= 8 && j <= 11) ||
                (i == 7 && j >= 8 && j <= 10) ||
                (i == 8 && j >= 9 && j <= 10) ||
                (i == 9 && j == 9))
            {
                num[purple].bubbles_color[5].setTexture(&Tbubbles);
                num[purple].bubbles_color[5].setRadius(16);
                num[purple].bubbles_color[5].setOrigin(16, 16);
                num[purple].bubbles_color[5].setScale(1.4, 1.4);
                num[purple].bubbles_color[5].setTextureRect(IntRect(0, (5) * 32, 32, 32));
                if (i % 2 == 0)
                    num[purple].bubbles_color[5].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[purple].bubbles_color[5].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                purple++;
            }
            else if (
                (i == 0 && j >= 1 && j <= 2) ||
                (i == 1 && j >= 1 && j <= 2) ||
                (i == 2 && j >= 2 && j <= 3) ||
                (i == 3 && j >= 2 && j <= 3) ||
                (i == 4 && j >= 3 && j <= 4) ||
                (i == 5 && j >= 3 && j <= 4) ||
                (i == 6 && j >= 3 && j <= 4) ||
                (i == 7 && j >= 2 && j <= 3) ||
                (i == 8 && j >= 2 && j <= 3) ||
                (i == 9 && j >= 1 && j <= 2) ||
                (i == 0 && j >= 17 && j <= 18) ||
                (i == 1 && j >= 16 && j <= 17) ||
                (i == 2 && j >= 16 && j <= 17) ||
                (i == 3 && j >= 15 && j <= 16) ||
                (i == 4 && j >= 15 && j <= 16) ||
                (i == 5 && j >= 14 && j <= 15) ||
                (i == 6 && j >= 15 && j <= 16) ||
                (i == 7 && j >= 15 && j <= 16) ||
                (i == 8 && j >= 16 && j <= 17) ||
                (i == 9 && j >= 16 && j <= 17))
            {
                num[blue].bubbles_color[4].setTexture(&Tbubbles);
                num[blue].bubbles_color[4].setRadius(16);
                num[blue].bubbles_color[4].setOrigin(16, 16);
                num[blue].bubbles_color[4].setScale(1.4, 1.4);
                num[blue].bubbles_color[4].setTextureRect(IntRect(0, (4) * 32, 32, 32));
                if (i % 2 == 0)
                    num[blue].bubbles_color[4].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[blue].bubbles_color[4].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                blue++;
            }
            else if ((i == 0 && j >= 3 && j <= 4) ||
                (i == 1 && j >= 3 && j <= 4) ||
                (i == 2 && j >= 4 && j <= 5) ||
                (i == 3 && j >= 4 && j <= 5) ||
                (i == 4 && j >= 5 && j <= 6) ||
                (i == 5 && j >= 5 && j <= 6) ||
                (i == 6 && j >= 6 && j <= 7) ||
                (i == 7 && j >= 6 && j <= 7) ||
                (i == 8 && j >= 7 && j <= 8) ||
                (i == 9 && j >= 7 && j <= 8) ||
                (i == 0 && j >= 15 && j <= 16) ||
                (i == 1 && j >= 14 && j <= 15) ||
                (i == 2 && j >= 14 && j <= 15) ||
                (i == 3 && j >= 13 && j <= 14) ||
                (i == 4 && j >= 13 && j <= 14) ||
                (i == 5 && j >= 12 && j <= 13) ||
                (i == 6 && j >= 12 && j <= 13) ||
                (i == 7 && j >= 11 && j <= 12) ||
                (i == 8 && j >= 11 && j <= 12) ||
                (i == 9 && j >= 10 && j <= 11))
            {
                num[green].bubbles_color[3].setTexture(&Tbubbles);
                num[green].bubbles_color[3].setRadius(16);
                num[green].bubbles_color[3].setOrigin(16, 16);
                num[green].bubbles_color[3].setScale(1.4, 1.4);
                num[green].bubbles_color[3].setTextureRect(IntRect(0, (3) * 32, 32, 32));
                if (i % 2 == 0)
                    num[green].bubbles_color[3].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[green].bubbles_color[3].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                green++;
            }
            else if (
                (i == 6 && j == 14) ||
                (i == 7 && j >= 12 && j <= 14) ||
                (i == 8 && j >= 12 && j <= 15) ||
                (i == 9 && j >= 12 && j <= 15) ||
                (i == 9 && j >= 3 && j <= 6) ||
                (i == 8 && j >= 4 && j <= 6) ||
                (i == 7 && j >= 4 && j <= 5) ||
                (i == 6 && j == 5))
            {
                num[red].bubbles_color[0].setTexture(&Tbubbles);
                num[red].bubbles_color[0].setRadius(16);
                num[red].bubbles_color[0].setOrigin(16, 16);
                num[red].bubbles_color[0].setScale(1.4, 1.4);
                num[red].bubbles_color[0].setTextureRect(IntRect(0, 0 * 32, 32, 32));
                if (i % 2 == 0)
                    num[red].bubbles_color[0].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[red].bubbles_color[0].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                red++;
            }
            else if (
                (i == 0 && j == 0) ||
                (i == 1 && j == 0) ||
                (i == 2 && j == 1) ||
                (i == 3 && j == 1) ||
                (i == 4 && j == 2) ||
                (i == 5 && j == 2) ||
                (i == 6 && j == 2) ||
                (i == 7 && j == 1) ||
                (i == 8 && j == 1) ||
                (i == 9 && j == 0) ||
                (i == 0 && j == 19) ||
                (i == 1 && j == 18) ||
                (i == 2 && j == 18) ||
                (i == 3 && j == 17) ||
                (i == 4 && j == 17) ||
                (i == 5 && j == 16) ||
                (i == 6 && j == 17) ||
                (i == 7 && j == 17) ||
                (i == 8 && j == 18) ||
                (i == 9 && j == 18))
            {
                num[yellow].bubbles_color[2].setTexture(&Tbubbles);
                num[yellow].bubbles_color[2].setRadius(16);
                num[yellow].bubbles_color[2].setOrigin(16, 16);
                num[yellow].bubbles_color[2].setScale(1.4, 1.4);
                num[yellow].bubbles_color[2].setTextureRect(IntRect(0, 2 * 32, 32, 32));
                if (i % 2 == 0)
                    num[yellow].bubbles_color[2].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[yellow].bubbles_color[2].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                yellow++;
            }
            else if (
                (i == 2 && j == 0) ||
                (i == 3 && j == 0) ||
                (i == 4 && j >= 0 && j <= 1) ||
                (i == 5 && j >= 0 && j <= 1) ||
                (i == 6 && j >= 0 && j <= 1) ||
                (i == 7 && j == 0) ||
                (i == 8 && j == 0) ||
                (i == 2 && j == 19) ||
                (i == 3 && j == 18) ||
                (i == 4 && j >= 18 && j <= 19) ||
                (i == 5 && j >= 17 && j <= 18) ||
                (i == 6 && j >= 18 && j <= 19) ||
                (i == 7 && j == 18) ||
                (i == 8 && j == 19))
            {
                num[black].bubbles_color[1].setTexture(&Tbubbles);
                num[black].bubbles_color[1].setRadius(16);
                num[black].bubbles_color[1].setOrigin(16, 16);
                num[black].bubbles_color[1].setScale(1.4, 1.4);
                num[black].bubbles_color[1].setTextureRect(IntRect(0, 1 * 32, 32, 32));
                if (i % 2 == 0)
                    num[black].bubbles_color[1].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[black].bubbles_color[1].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                black++;
            }
        }
    }

    scale = num[1].bubbles_color[1].getScale().x;
    draw_my_graph();
}
void bring_bubbles_lev8() {
    currentlev = 8;
    loading = 1;
    musicgame.openFromFile("Assets/Sounds/BGM_8.ogg");
    musicgame.setLoop(1);
    musicgame.play();
    Tbackground.loadFromFile("Assets/Textures/lev8.jpg");

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            if (num[j].bubbles_color[i].getTexture() == (&Tbubbles)) {
                adj[{j, i}].clear();
                num[j].bubbles_color[i].setPosition(2000, 2000);
                visitedbublle[j][i] = 0;
                num[j].velocity[i] = 0;
            }

        }
    }
    int totalballs = 15;
    tot = totalballs;
    idxball = rand(), idxball2 = rand(), idxmoves = 0, x = 150, ballsleft = totalballs,
        thescore = 0, an = 0;
    memset(visitedmoves, 0, size(visitedmoves));
    memset(velocityx, 0, size(velocityx));
    memset(velcityy, 0, size(velcityy));
    bub_pushed.clear();
    upbubble.clear();
    score();
    numballs();
    int purple = 0;
    int blue = 0;
    int yellow = 0;
    int green = 0;
    int black = 0;
    int red = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            if ((i == 0 && (j == 4 || j == 5)) ||
                (i == 0 && (j == 15 || j == 16)) ||
                (i == 1 && (j == 3 || j == 4)) ||
                (i == 1 && (j == 15 || j == 16)) ||
                (i == 2 && (j == 3 || j == 4)) ||
                (i == 2 && (j == 16 || j == 17)) ||
                (i == 3 && (j == 3 || j == 4)) ||
                (i == 3 && (j == 15 || j == 16)) ||
                (i == 4 && (j == 3 || j == 4)) ||
                (i == 4 && (j == 16 || j == 17)) ||
                (i == 8 && (j == 4 || j == 5)) ||
                (i == 8 && (j == 15 || j == 16)) ||
                (i == 7 && (j == 3 || j == 4)) ||
                (i == 7 && (j == 15 || j == 16)) ||
                (i == 6 && (j == 3 || j == 4)) ||
                (i == 6 && (j == 16 || j == 17)) ||
                (i == 5 && (j == 3 || j == 4)) ||
                (i == 5 && (j == 15 || j == 16))
                )



            {
                num[purple].bubbles_color[5].setTexture(&Tbubbles);
                num[purple].bubbles_color[5].setRadius(16);
                num[purple].bubbles_color[5].setOrigin(16, 16);
                num[purple].bubbles_color[5].setScale(1.4, 1.4);
                num[purple].bubbles_color[5].setTextureRect(IntRect(0, (5) * 32, 32, 32));
                if (i % 2 == 0)
                    num[purple].bubbles_color[5].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[purple].bubbles_color[5].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                purple++;
            }
            else if (
                (i == 0 && j >= 6 && j <= 9) ||
                (i == 0 && j >= 11 && j <= 14) ||
                (i == 1 && j >= 5 && j <= 8) ||
                (i == 1 && j >= 11 && j <= 14) ||
                (i == 2 && (j == 5 || j == 6)) ||
                (i == 2 && (j == 14 || j == 15)) ||
                (i == 3 && (j == 5 || j == 6)) ||
                (i == 3 && (j == 13 || j == 14)) ||
                (i == 4 && (j == 5 || j == 6)) ||
                (i == 4 && (j == 14 || j == 15)) ||
                (i == 8 && j >= 6 && j <= 9) ||
                (i == 8 && j >= 11 && j <= 14) ||
                (i == 7 && j >= 5 && j <= 8) ||
                (i == 7 && j >= 11 && j <= 14) ||
                (i == 6 && (j == 5 || j == 6)) ||
                (i == 6 && (j == 14 || j == 15)) ||
                (i == 5 && (j == 5 || j == 6)) ||
                (i == 5 && (j == 13 || j == 14))
                )
            {
                num[blue].bubbles_color[4].setTexture(&Tbubbles);
                num[blue].bubbles_color[4].setRadius(16);
                num[blue].bubbles_color[4].setOrigin(16, 16);
                num[blue].bubbles_color[4].setScale(1.4, 1.4);
                num[blue].bubbles_color[4].setTextureRect(IntRect(0, (4) * 32, 32, 32));
                if (i % 2 == 0)
                    num[blue].bubbles_color[4].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[blue].bubbles_color[4].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                blue++;
            }
            else if (
                (i == 0 && (j == 2 || j == 3)) ||
                (i == 0 && j >= 17 && j <= 19) ||
                (i == 1 && (j == 1 || j == 2)) ||
                (i == 1 && j >= 15 && j <= 18) ||
                (i == 2 && (j == 1 || j == 2)) ||
                (i == 2 && j >= 17 && j <= 19) ||
                (i == 3 && (j == 1 || j == 2)) ||
                (i == 3 && (j == 17 || j == 18) ||
                    (i == 4 && (j == 1 || j == 2)) ||
                    (i == 4 && (j == 18 || j == 19))) ||
                (i == 8 && (j == 2 || j == 3)) ||
                (i == 8 && j >= 17 && j <= 19) ||
                (i == 7 && (j == 1 || j == 2)) ||
                (i == 7 && (j == 17 || j == 18)) ||
                (i == 6 && (j == 1 || j == 2)) ||
                (i == 6 && (j == 18 || j == 19)) ||
                (i == 5 && (j == 1 || j == 2)) ||
                (i == 5 && (j == 17 || j == 18))

                )

            {
                num[green].bubbles_color[3].setTexture(&Tbubbles);
                num[green].bubbles_color[3].setRadius(16);
                num[green].bubbles_color[3].setOrigin(16, 16);
                num[green].bubbles_color[3].setScale(1.4, 1.4);
                num[green].bubbles_color[3].setTextureRect(IntRect(0, (3) * 32, 32, 32));
                if (i % 2 == 0)
                    num[green].bubbles_color[3].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[green].bubbles_color[3].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                green++;
            }
            else if (((i == 0 && j == 10)) ||
                (i == 1 && (j == 9 || j == 10)) ||
                (i == 2 && (j >= 7 && j <= 13)) ||
                (i == 3 && j >= 7 && j <= 12) ||
                (i == 4 && j >= 7 && j <= 13))


            {
                num[red].bubbles_color[0].setTexture(&Tbubbles);
                num[red].bubbles_color[0].setRadius(16);
                num[red].bubbles_color[0].setOrigin(16, 16);
                num[red].bubbles_color[0].setScale(1.4, 1.4);
                num[red].bubbles_color[0].setTextureRect(IntRect(0, 0 * 32, 32, 32));
                if (i % 2 == 0)
                    num[red].bubbles_color[0].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[red].bubbles_color[0].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                red++;
            }
            else if ((i == 8 && j == 10) ||
                (i == 7 && (j == 9 || j == 10)) ||
                (i == 6 && j >= 7 && j <= 13) ||
                (i == 5 && j >= 7 && j <= 12)



                )

            {
                num[yellow].bubbles_color[2].setTexture(&Tbubbles);
                num[yellow].bubbles_color[2].setRadius(16);
                num[yellow].bubbles_color[2].setOrigin(16, 16);
                num[yellow].bubbles_color[2].setScale(1.4, 1.4);
                num[yellow].bubbles_color[2].setTextureRect(IntRect(0, 2 * 32, 32, 32));
                if (i % 2 == 0)
                    num[yellow].bubbles_color[2].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[yellow].bubbles_color[2].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                yellow++;
            }
            else if (i == 0 && (j == 0 || j == 1) ||
                (i == 1 && (j == 0)) ||
                (i == 2 && (j == 0) ||
                    (i == 3 && j == 0) ||
                    (i == 4 && j == 0)) ||
                (i == 8 && (j == 0 || j == 1)) ||
                (i == 7 && j == 0) ||
                (i == 6 && j == 0) ||
                (i == 5 && j == 0)



                )
            {
                num[black].bubbles_color[1].setTexture(&Tbubbles);
                num[black].bubbles_color[1].setRadius(16);
                num[black].bubbles_color[1].setOrigin(16, 16);
                num[black].bubbles_color[1].setScale(1.4, 1.4);
                num[black].bubbles_color[1].setTextureRect(IntRect(0, 1 * 32, 32, 32));
                if (i % 2 == 0)
                    num[black].bubbles_color[1].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                else
                    num[black].bubbles_color[1].setPosition((44.8 * j + 44), 44.8 * (i)+25);
                black++;
            }
        }
    }
    scale = num[1].bubbles_color[1].getScale().x;
    draw_my_graph();
}
void bring_bubbles_lev9() {
    loading = 1;
    musicgame.openFromFile("Assets/Sounds/BGM_9.ogg");
    musicgame.setLoop(1);
    musicgame.play();
    Tbackground.loadFromFile("Assets/Textures/lev9.jpg");
    currentlev = 9;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            if (num[j].bubbles_color[i].getTexture() == (&Tbubbles)) {
                adj[{j, i}].clear();
                num[j].bubbles_color[i].setPosition(2000, 2000);
                visitedbublle[j][i] = 0;
                num[j].velocity[i] = 0;
            }

        }
    }
    int totalballs = 30;
    tot = totalballs;
    idxball = rand(), idxball2 = rand(), idxmoves = 0, x = 200, ballsleft = totalballs, thescore = 0, an = 0;
    score();
    numballs();
    memset(visitedmoves, 0, sizeof(visitedmoves));
    memset(velocityx, 0, sizeof(velocityx));
    memset(velcityy, 0, sizeof(velcityy));
    bub_pushed.clear();
    upbubble.clear();
    int purple = 0;
    int blue = 0;
    int yellow = 0;
    int green = 0;
    int black = 0;
    int red = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            if ((i == 6 && (j == 0 || j == 2 || j == 3 || j == 4 || j == 5 || j == 6 || j == 10 || j == 11 || j == 13 || j == 14 || j == 18 || j == 19)) ||
                (i == 7 && j >= 2 && j <= 11) ||
                (i == 7 && j >= 13 && j <= 19) ||
                (i == 7 && j == 0)
                )
            {
                num[purple].bubbles_color[5].setTexture(&Tbubbles);
                num[purple].bubbles_color[5].setRadius(16);
                num[purple].bubbles_color[5].setOrigin(16, 16);
                num[purple].bubbles_color[5].setScale(1.4, 1.4);
                num[purple].bubbles_color[5].setTextureRect(IntRect(0, (5) * 32, 32, 32));
                num[purple].bubbles_color[5].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                purple++;
            }
            else if ((i == 4 && (j == 0 || j == 4 || j == 5 || j == 7 || j == 8 || j == 9 || j == 10 || j == 11 || j == 13 || j == 14 || j == 18 || j == 19)) ||
                (i == 5 && (j == 0 || j == 2 || j == 3 || j == 4 || j == 5 || j == 2 || j == 8 || j == 9 || j == 10 || j == 11 || j == 13 || j == 14 || j == 15 || j == 16 || j == 18 || j == 19))
                )
            {
                num[blue].bubbles_color[4].setTexture(&Tbubbles);
                num[blue].bubbles_color[4].setRadius(16);
                num[blue].bubbles_color[4].setOrigin(16, 16);
                num[blue].bubbles_color[4].setScale(1.4, 1.4);
                num[blue].bubbles_color[4].setTextureRect(IntRect(0, (4) * 32, 32, 32));
                num[blue].bubbles_color[4].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                blue++;
            }
            else if ((i == 2 && (j == 0 || j == 6 || j == 10 || j == 11 || j == 13 || j == 14 || j == 18 || j == 19)) ||
                (i == 3 && j == 0) ||
                (i == 3 && j >= 2 && j <= 5) ||
                (i == 3 && j >= 8 && j <= 11) ||
                (i == 3 && (j == 13 || j == 14)) ||
                (i == 3 && j >= 16 && j <= 19)
                )
            {
                num[green].bubbles_color[3].setTexture(&Tbubbles);
                num[green].bubbles_color[3].setRadius(16);
                num[green].bubbles_color[3].setOrigin(16, 16);
                num[green].bubbles_color[3].setScale(1.4, 1.4);
                num[green].bubbles_color[3].setTextureRect(IntRect(0, (3) * 32, 32, 32));
                num[green].bubbles_color[3].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                green++;
            }
            else if ((i == 0 && j >= 0 && j <= 11) ||
                (i == 0 && j >= 13 && j <= 19) ||
                (i == 1) ||
                (i == 0 && j == 12)
                )
            {
                num[yellow].bubbles_color[2].setTexture(&Tbubbles);
                num[yellow].bubbles_color[2].setRadius(16);
                num[yellow].bubbles_color[2].setOrigin(16, 16);
                num[yellow].bubbles_color[2].setScale(1.4, 1.4);
                num[yellow].bubbles_color[2].setTextureRect(IntRect(0, 2 * 32, 32, 32));
                num[yellow].bubbles_color[2].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                yellow++;
            }
            else if ((i == 2 && j >= 15 && j <= 17) ||
                (i == 3 && j == 15) ||
                (i == 4 && j >= 15 && j <= 17) ||
                (i == 5 && j == 17) ||
                (i == 6 && j >= 15 && j <= 17) ||
                (i >= 2 && i <= 7 && j == 1) ||
                (i == 2 && j >= 2 && j <= 5) ||
                (i == 4 && (j == 2 || j == 3)) ||
                (i == 2 && j >= 7 && j <= 9) ||
                (i == 4 && j == 6) ||
                (i == 6 && j >= 7 && j <= 9) ||
                (i >= 2 && i <= 7 && j == 12)
                )
            {
                num[red].bubbles_color[0].setTexture(&Tbubbles);
                num[red].bubbles_color[0].setRadius(16);
                num[red].bubbles_color[0].setOrigin(16, 16);
                num[red].bubbles_color[0].setScale(1.4, 1.4);
                num[red].bubbles_color[0].setTextureRect(IntRect(0, 0 * 32, 32, 32));
                num[red].bubbles_color[0].setPosition((44.8 * j + 22), 44.8 * (i)+25);
                red++;
            }
            else if ((i == 3 && j == 6) || (i == 5 && j == 6)) {
                num[red].bubbles_color[0].setTexture(&Tbubbles);
                num[red].bubbles_color[0].setRadius(16);
                num[red].bubbles_color[0].setOrigin(16, 16);
                num[red].bubbles_color[0].setScale(1.4, 1.4);
                num[red].bubbles_color[0].setTextureRect(IntRect(0, 0 * 32, 32, 32));
                num[red].bubbles_color[0].setPosition((44.8 * j + 40), 44.8 * (i)+25);
                red++;
            }
        }
    }
    scale = num[0].bubbles_color[0].getScale().x;
    draw_my_graph();
}
int loadlastgame() {
    for (int lastgame = 9; lastgame > 0; lastgame--) {
        if (level[lastgame].open) {
            switch (lastgame)
            {
            case 1:
                bring_bubbles_lev1();
                return 1;
            case 2:
                bring_bubbles_lev2();
                return 2;
            case 3:
                bring_bubbles_lev3();
                return 3;
            case 4:
                bring_bubbles_lev4();
                return 4;
            case 5:
                bring_bubbles_lev5();
                return 5;
            case 6:
                bring_bubbles_lev6();
                return 6;
            case 7:
                bring_bubbles_lev7();
                return 7;
            case 8:
                bring_bubbles_lev8();
                return 8;
            case 9:
                bring_bubbles_lev9();
                return 9;
            }

        }

    }
}
int loadgame() {
    switch (currentlev) {
    case 1:
        bring_bubbles_lev1();
        return 1;
    case 2:
        bring_bubbles_lev2();
        return 2;
    case 3:
        bring_bubbles_lev3();
        return 3;
    case 4:
        bring_bubbles_lev4();
        return 4;
    case 5:
        bring_bubbles_lev5();
        return 5;
    case 6:
        bring_bubbles_lev6();
        return 6;
    case 7:
        bring_bubbles_lev7();
        return 7;
    case 8:
        bring_bubbles_lev8();
        return 8;
    case 9:
        bring_bubbles_lev9();
        return 9;
    }
}
// Collision with the same color
void clear_balls_with_the_same_color(int color)
{

    while (!q.empty())
    {
        soundgame.openFromFile("Assets/Sounds/bomb.ogg");
        soundgame.play();
        bub_pushed.push_back(
            { num[q.front().first].bubbles_color[q.front().second].getPosition().x,
             num[q.front().first].bubbles_color[q.front().second].getPosition().y });
        thescore += 10;
        score();
        balls_with_the_same_color_visited[q.front().first][q.front().second] = 1;
        num[q.front().first].bubbles_color[q.front().second].setPosition(2000, 2000);
        for (auto child : adj[q.front()])
        {
            int i = child.first;
            int j = child.second;
            if (!visitedbublle[i][j] && !balls_with_the_same_color_visited[i][j] && j == color)
            {
                q.push({ i, j });
                visitedbublle[i][j] = 1;
            }
        }
        q.pop();
    }
}
int random(int min, int max) // range : [min, max]
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL)); // seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}
//Clear_the_ball_suspended_in_the_air
void clearballs()
{
    while (!q.empty())
    {
        balls_with_the_same_color_visited[q.front().first][q.front().second] = 1;
        for (auto child : adj[q.front()])
        {
            int i = child.first;
            int j = child.second;
            if (!visitedbublle[i][j] && !balls_with_the_same_color_visited[i][j])
            {
                q.push({ i, j });
            }
        }
        q.pop();
    }
}
void Clear_the_ball_suspended_in_the_air()
{
    for (auto ball : upbubble)
    {
        if (!visitedbublle[ball.first][ball.second] && !balls_with_the_same_color_visited[ball.first][ball.second])
        {
            q.push({ ball.first, ball.second });
            clearballs();
        }
    }
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < x; i++)
        {
            if (!balls_with_the_same_color_visited[i][j] && !visitedbublle[i][j] && num[i].bubbles_color[j].getTexture() == &Tbubbles)
            {
                visitedbublle[i][j] = 1;
                num[i].velocity[j] = random(15, 30);
                thescore += 10;
                score();
            }
        }
    }
}
// make directions on game
void directionsOfObjects()
{

    // center of the gun 

    centerx = StoredBalls[0].getPosition().x;
    centery = StoredBalls[0].getPosition().y;

    // position mouse in
    mouspos = Vector2f(Mouse::getPosition(window));
    // atan= Shift tan ;
    SlopeBetweenMouse_madf3 = atan((mouspos.x - centerx) / (centery - mouspos.y));
    // as long as the mouse is above the cannon, it rolls with it
    if (mouspos.y < centery - 55)
        madf3.setRotation(1 * SlopeBetweenMouse_madf3 * 180 / (22 / 7.0)); // Convert from radians to degree
}
// clicks on  game
void clicks()
{


    if (ev.type == Event::MouseButtonReleased)
    {
        ispressed = 1; // عشان لو فضل دايس مايطلعش كل الكور ورا بعض
    }
    if (Mouse::isButtonPressed(Mouse::Left) &&
        idxmoves < tot && ispressed && (visitedmoves[idxmoves - 1] || idxmoves == 0) &&
        (mouspos.y < centery - 55))
    {
        soundgame.openFromFile("Assets/Sounds/bucket_shoot.ogg");
        soundgame.play();
        ballsleft--;
        numballs();
        float slopex = (mouspos.x - centerx);
        float slopey = -1 * (centery - mouspos.y);
        movingball[idxmoves] = StoredBalls[idxball % 6]; // باخد من الكور اللي مخزنها كوره
        movingball[idxmoves].setScale(scale, scale);
        colorofmoves[idxmoves] = idxball % 6;
        // بحفظ الميل بتاع كل كوره
        velocityx[idxmoves] = slopex;
        velcityy[idxmoves] = slopey;
        idxmoves++;

        if (idxmoves < tot)
        {
            idxball = idxball2;
            if (cntrand == 6)
            {
                idxball2 = rand(); // كوره عشوائيه
                cntrand = 0;
            }
            else
            {
                idxball2 = cntrand++;
            }
        }

        ispressed = 0;
    }

    // لو داس كليك يمين يبدل بين الكورتين
    if (Mouse::isButtonPressed(Mouse::Right) && (idxmoves < tot - 1))
    {
        if (Event::MouseButtonReleased)
            swap(idxball, idxball2);
    }
}
// draw game
void drawObjects()
{
    int totalballs = tot;
    //draw background
    window.draw(back);

    //moving ball 
    for (int i = 0; i < idxmoves; i++)
    {
        // if it doesn't move before 
        if (!visitedmoves[i])
        {
            double ceta = atan2(velcityy[i], velocityx[i]);
            // move with ceta 
            movingball[i].move(15 * cos(ceta), 15 * sin(ceta));
            // if it hit the wall -> move with -velocity x
            if (movingball[i].getPosition().x > 900 - scale * 16 || movingball[i].getPosition().x < scale * 16)
            {
                velocityx[i] *= -1;
            }
            //arrray to store ( number of the ball and color of it ) my collided balls 
            int cnt = 0;
            int number[10];
            int colorr[10];
            for (int color1 = 0; color1 < 6; color1++)
            {
                for (int j1 = 0; j1 < x; j1++)
                {
                    // set balls_with_the_same_color =0 
                    balls_with_the_same_color_visited[j1][color1] = 0;
                    if (!visitedbublle[j1][color1])
                    {
                        // store the The ball hanging from the ceiling
                        if ((num[j1].bubbles_color[color1].getPosition().y <= 16 * scale + 5)) {
                            upbubble.push_back({ j1,color1 });
                        }
                        //store the collided balls
                        if (movingball[i].getGlobalBounds().intersects(num[j1].bubbles_color[color1].getGlobalBounds()))
                        {
                            number[cnt] = j1;
                            colorr[cnt] = color1;
                            cnt++;
                        }
                    }
                }
            }
            //check if the stored collided ball 
            for (int idx = 0; idx < cnt; idx++)
            {
                //if with same color -> clear all the balls with the same color
                if (colorofmoves[i] == colorr[idx])
                {
                    q.push({ number[idx], colorofmoves[i] });
                    clear_balls_with_the_same_color(colorofmoves[i]);
                    Clear_the_ball_suspended_in_the_air();
                    movingball[i].setPosition(-2000, 2000);
                    visitedmoves[i] = 1;
                    break;
                }
                else if (idx == cnt - 1)
                {
                    double x1, y1, len;
                    //add ball and adjust his position well 
                    for (int idxx = 0; idxx < cnt; idxx++)
                    {

                        x1 = num[number[idxx]].bubbles_color[colorr[idxx]].getPosition().x - movingball[i].getPosition().x;
                        y1 = num[number[idxx]].bubbles_color[colorr[idxx]].getPosition().y - movingball[i].getPosition().y;
                        len = sqrt(x1 * x1 + y1 * y1) - scale * 32;
                        if (idxx > 0 && len < 0) {
                            movingball[i].setPosition(movingball[i].getPosition().x + len * cos(atan2(y1, x1)),
                                movingball[i].getPosition().y + len * sin(atan2(y1, x1)));
                        }
                        else if (idxx == 0) {
                            movingball[i].setPosition(movingball[i].getPosition().x + len * cos(atan2(y1, x1)),
                                movingball[i].getPosition().y + len * sin(atan2(y1, x1)));
                        }
                        pair<int, int> node1 = { number[idxx], colorr[idxx] }, node2 = { x, colorofmoves[i] };
                        adj[node1].push_back(node2);
                        adj[node2].push_back(node1);
                    }
                    num[x].bubbles_color[colorofmoves[i]] = movingball[i];

                    if (num[x].bubbles_color[colorofmoves[i]].getPosition().x < 16 * scale)
                    {
                        num[x].bubbles_color[colorofmoves[i]].setPosition(16 * scale,
                            num[x].bubbles_color[colorofmoves[i]].getPosition().y);
                    }
                    else if (num[x].bubbles_color[colorofmoves[i]].getPosition().x > 900 - scale * 16)
                    {
                        num[x].bubbles_color[colorofmoves[i]].setPosition(900 - 16 * scale,
                            num[x].bubbles_color[colorofmoves[i]].getPosition().y);
                    }
                    x++;
                    thescore -= 3;
                    score();
                    movingball[i].setPosition(-2000, 2000);
                    visitedmoves[i] = 1;
                }
            }
        }
        // if there are no any ball collided the moving ball and collided my ceiling
        // -> add ball and adjust his position well 

        if (movingball[i].getPosition().y < 16 * scale)
        {
            num[x].bubbles_color[colorofmoves[i]] = movingball[i];
            num[x].bubbles_color[colorofmoves[i]].setPosition(movingball[i].getPosition().x, 16 * scale);
            if (num[x].bubbles_color[colorofmoves[i]].getPosition().x < 16 * scale)
            {
                num[x].bubbles_color[colorofmoves[i]].setPosition(16 * scale, 16 * scale);
            }
            else if (num[x].bubbles_color[colorofmoves[i]].getPosition().x > 900 - 16 * scale)
            {
                num[x].bubbles_color[colorofmoves[i]].setPosition(900 - 16 * scale, 16 * scale);
            }
            x++;
            thescore -= 3;
            score();
            movingball[i].setPosition(-2000, 2000);
            visitedmoves[i] = 1;
        }
        window.draw(movingball[i]);

    }
    //draw my gun 
    window.draw(madf3);
    //draw the ball which at my gun
    if (idxmoves < totalballs)
    {
        window.draw(StoredBalls[idxball % 6]);
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < x; j++)
        {
            //draw the balls in the window
            num[j].bubbles_color[i].move(0, num[j].velocity[i]);
            window.draw(num[j].bubbles_color[i]);
            int x = num[j].bubbles_color[i].getPosition().x;
            int y = num[j].bubbles_color[i].getPosition().y;
            //if there are  balls in the window -> win=0 :( ; 
            if (y >= 16 * scale && y <= 800 - 16 * scale && x >= 16 * scale && x <= 900 - 16 * scale && num[j].bubbles_color[i].getTexture() == &Tbubbles)
            {
                win = 0;
            }
        }
    }
}
//draw animation
void drawanimation()
{


    for (int push = 0; push < bub_pushed.size(); push++)
    {

        anm.setTextureRect(IntRect(an * 64, 0, 64, 64));
        anm.setOrigin(32, 32);
        anm.setScale(scale / 2.0, scale / 2.0);
        anm.setPosition(bub_pushed[push].first, bub_pushed[push].second);
        window.draw(anm);

    }
    an++;
    if (an == 16)
    {
        bub_pushed.clear();
        an = 0;
    }

}
//__________________________________________________
               // animation backgrounds
void bring_gif()
{
    int jjj = 0;
    for (int i = 0; i < 5 * 478; i += 478)
    {
        for (int j = 0; j < 11 * 479; j += 479)
        {
            drawloadingbar();
            if (j < 10 * 479) {
                Sloading[jjj].setTexture(Tloading);
                Sloading[jjj].setTextureRect(IntRect(i, j, 478, 479));
                Sloading[jjj].setScale(1.9, 1.9);
                jjj++;
            }
            else if (j == 10 * 479 && i < 3 * 478) {
                Sloading[jjj].setTexture(Tloading);
                Sloading[jjj].setTextureRect(IntRect(i, j, 478, 479));
                Sloading[jjj].setScale(1.9, 1.9);
                jjj++;
            }
        }
    }

    int jj = 0;
    for (int i = 0; i < 5 * 540; i += 540)
    {
        for (int j = 0; j < 7 * 763; j += 763)
        {
            drawloadingbar();
            Sgifnames[jj].setTexture(Tgifnames);
            Sgifnames[jj].setTextureRect(IntRect(i, j, 540, 763));
            Sgifnames[jj].setScale(900 / 540.0, 800 / 763.0);
            jj++;
        }
    }
    int ii = 0;
    for (int i = 0; i < 3000; i += 600)
    {
        for (int j = 0; j < 12 * 600; j += 600)
        {
            drawloadingbar();
            gifback[ii].setTexture(Tgif);
            gifback[ii].setTextureRect(IntRect(i, j, 600, 600));
            gifback[ii].setScale(1.5, 1.5);
            ii++;
        }
    }

    for (int i = 0; i < 5 * 480; i += 480)
    {
        for (int j = 0; j < 5 * 480; j += 480)
        {
            drawloadingbar();
            gifback[ii].setTexture(Tgif2);
            gifback[ii].setTextureRect(IntRect(i, j, 480, 480));
            gifback[ii].setScale(1.875, 800 / 480.0);
            ii++;
        }
    }
    // *****************************************************************************************

    for (int x = 0; x < 6; x++) {
        ii = 0;
        for (int i = 0; i < 5 * 400; i += 400) {
            for (int j = 0; j < 6 * 400; j += 400) {
                NAMES[x].Spanner[ii].setTexture(Tpanner);
                NAMES[x].Spanner[ii].setTextureRect(IntRect(i, j, 400, 400));
                NAMES[x].Spanner[ii].setOrigin(200, 200);
                NAMES[x].Spanner[ii].setScale(255.0 / 400 * 1.1, 255.0 / 400 * 1.1);
                if (x == 0) {
                    NAMES[x].Spanner[ii].setPosition(265 * 2 - 114, 229.5 * 2 - 114);

                }
                else if (x == 1) {
                    NAMES[x].Spanner[ii].setPosition(133 * 2 - 114, 348 * 2 - 114);
                }
                else if (x == 2) {
                    NAMES[x].Spanner[ii].setPosition(337.5 * 2 - 114, 376 * 2 - 114);
                }
                else if (x == 3) {
                    NAMES[x].Spanner[ii].setPosition(435.5 * 2 - 114, 271 * 2 - 114);
                }
                else if (x == 4) {
                    NAMES[x].Spanner[ii].setPosition(645, 134);
                }
                else if (x == 5) {
                    NAMES[x].Spanner[ii].setPosition(177, 133);
                }
                ii++;
                drawloadingbar();


            }
        }
    }
}
//__________________________________________________
                  // levels
void stars()
{
    for (int i = 0; i < 9; i++)
    {
        Sstar[i].setTexture(Tstars);
        Sstar[i].setTextureRect(IntRect((level[i + 1].stars) * 105.5, 0, 105.5, 55));
        Sstar[i].setOrigin(105.5 / 2.0, 55 / 2.0);
        Sstar[i].setPosition(OpenedLevels[i].getPosition().x, OpenedLevels[i].getPosition().y - 80);
        window.draw(Sstar[i]);
    }
}
void MainOFLevels()
{
    int ii = 0;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {

            OpenedLevels[ii].setSize(Vector2f(127, 126));
            OpenedLevels[ii].setTexture(&TNumOfLevels);
            OpenedLevels[ii].setTextureRect(IntRect((level[ii + 1].open) ? (ii + 1) * 127 : 0, 0, 127, 126));
            OpenedLevels[ii].setOrigin(127 / 2.0, 126 / 2.0);
            OpenedLevels[ii].setPosition
            (j * 300 - 150, (i == 1) ? i * 800 / 3.0 - 120 : (i == 3) ? i * 800 / 3.0 - 180 : i * 800 / 3.0 - 150);
            textscore[ii + 1].setString("Score : ");
            textscore[ii + 1].setFillColor(Color::Black);
            textscore[ii + 1].setPosition
            (j * 300 - 150 - 127 / 2.0, (i == 1) ? i * 800 / 3.0 - 120 + 126 / 2.0 + 10 : (i == 3) ? i * 800 / 3.0 - 180 + 126 / 2.0 + 10 : i * 800 / 3.0 - 150 + 126 / 2.0 + 10);
            stringstream ss;
            ss << level[ii + 1].score;
            string stemp = ss.str();
            scorelev[ii + 1].setString(stemp);
            scorelev[ii + 1].setPosition(j * 300 - 150 - 127 / 2.0 + 100, (i == 1) ? i * 800 / 3.0 - 120 + 126 / 2.0 + 10 : (i == 3) ? i * 800 / 3.0 - 180 + 126 / 2.0 + 10 : i * 800 / 3.0 - 150 + 126 / 2.0 + 10);
            scorelev[ii + 1].setFillColor(Color::Black);

            window.draw(OpenedLevels[ii]);
            window.draw(textscore[ii + 1]);
            window.draw(scorelev[ii + 1]);
            ii++;
        }
    }
    stars();
}
int enter_levels()
{

    for (int i = 0; i < 9; i++)
    {
        if (mouspos.x > OpenedLevels[i].getPosition().x - 127 / 2.0 &&
            mouspos.x < OpenedLevels[i].getPosition().x + 127 / 2.0 &&
            mouspos.y > OpenedLevels[i].getPosition().y - 126 / 2.0 &&
            mouspos.y < OpenedLevels[i].getPosition().y + 126 / 2.0 &&
            level[i + 1].open && Mouse::isButtonPressed(Mouse::Left))
        {
            soundgame.openFromFile("Assets/Sounds/button.ogg");
            soundgame.play();
            opened.pop();
            opened.push("play");
            return i + 1;
        }
    }
    return -1;
}
//__________________________________________________
                // Back Icon
void Back()
{
    Bicon[0].setTexture(Tbicon);
    Bicon[0].setTextureRect(IntRect(82, 0, 58, 94));
    Bicon[0].setPosition(810 + 28, 680 + 47);
    window.draw(Bicon[0]);
}
//__________________________________________________
              // options
void credit()
{
    Scredit.setTexture(Tcredit);
    Scredit.setTextureRect(IntRect(0, 633, 178, 85));
    Scredit.setOrigin(178 / 2.0, 42.5);
    Scredit.setPosition(450, 700);

    Vector2f mouspos = Vector2f(Mouse::getPosition(window));

    if (mouspos.x > 450 - 178 / 2.0 && mouspos.x < 450 + 178 / 2 && mouspos.y > 700 - 42.5 && mouspos.y < 700 + 42.5)
    {
        Scredit.setTextureRect(IntRect(0, 535, 178, 85));
        Scredit.setScale(1.1, 1.1);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            soundgame.openFromFile("Assets/Sounds/button.ogg");
            soundgame.play();
            musicgame.openFromFile("Assets/Sounds/soundnames.ogg");
            musicgame.setLoop(1);
            musicgame.play();
            opened.push("credit");
        }
    }
    else
        Scredit.setScale(1, 1);
    window.draw(Scredit);
    //_______________________________________________
}
void names()
{


    ph %= 10;
    timeph++;
    for (int i = 0; i < 6; i++) {
        window.draw(NAMES[i].Spanner[ph]);
    }
    if (timeph == 9)
    {

        ph++;
        timeph = 0;
    }

    window.draw(Sourphoto);
}
void soundicon()
{
    menu[18].setSize(Vector2f(91, 92));
    if (idxvs == 0)
    {

        menu[18].setTexture(&Tboard);
    }
    else
    {

        menu[18].setTexture(&Tmen);
    }
    menu[18].setTextureRect(IntRect(0, 922, 91, 1013 - 925));
    menu[18].setPosition(50, 50);
    menu[18].setScale(1.5, 1.5);
    window.draw(menu[18]);
    // -------------------------
    menu[19].setSize(Vector2f(91, 90));
    if (idxvm == 0)
    {
        menu[19].setTexture(&Tboard);
    }
    else
    {

        menu[19].setTexture(&Tmen);
    }

    menu[19].setTextureRect(IntRect(0, 1021, 91, 1010 - 925));
    menu[19].setPosition(50, 220);
    menu[19].setScale(1.5, 1.5);
    window.draw(menu[19]);
}
void soundcontrol()
{

    //--------------------------------
    // soundicon
    sound.setTexture(Tcontrol);
    sound.setTextureRect(IntRect(0, idxvs * 187, 736, 187));
    sound.setPosition(225, 55);
    sound.setScale(0.65, 0.65);
    window.draw(sound);
    upsound.setTexture(Tbicon);
    upsound.setTextureRect(IntRect(82, 0, 58, 94));
    upsound.setScale(0.8, 0.8);
    upsound.setPosition(810, 80);
    bool pressed = 0;
    if (mouspos.x > 810 && mouspos.x < 810 + 58 && mouspos.y > 80 && mouspos.y < 80 + 94 && idxvs < 9)
    {
        upsound.setScale(1.0000000000001, 1.0000000000001);
    }

    window.draw(upsound);
    downsound.setTexture(Tbicon);
    downsound.setTextureRect(IntRect(0, 0, 58, 94));
    downsound.setScale(0.8, 0.8);
    downsound.setPosition(810 - 65, 80);
    if (mouspos.x > 810 - 65 && mouspos.x < 810 + 58 - 65 && mouspos.y > 80 && mouspos.y < 80 + 94 && idxvs > 0)
    {
        downsound.setScale(1.0000000000001, 1.0000000000001);
    }

    window.draw(downsound);

    //--------------------------------
    //      //musicicon
    soundMusic.setTexture(Tcontrol);
    soundMusic.setTextureRect(IntRect(0, idxvm * 187, 736, 187));
    soundMusic.setPosition(225, 220);
    soundMusic.setScale(0.65, 0.65);
    window.draw(soundMusic);
    upmusic.setTexture(Tbicon);
    upmusic.setTextureRect(IntRect(82, 0, 58, 94));
    upmusic.setScale(0.8, 0.8);
    upmusic.setPosition(810, 250);
    if (mouspos.x > 810 && mouspos.x < 810 + 58 && mouspos.y > 250 && mouspos.y < 250 + 94 && idxvm < 9)
    {
        upmusic.setScale(1.0000000000001, 1.0000000000001);
    }

    window.draw(upmusic);
    downmusic.setTexture(Tbicon);
    downmusic.setTextureRect(IntRect(0, 0, 58, 94));
    downmusic.setScale(0.8, 0.8);
    downmusic.setPosition(810 - 65, 250);
    if (mouspos.x > 810 - 65 && mouspos.x < 810 + 58 - 65 && mouspos.y > 250 && mouspos.y < 250 + 94 && idxvm > 0)
    {
        downmusic.setScale(1.0000000000001, 1.0000000000001);
    }

    window.draw(downmusic);
}
//__________________________________________________
            // check clicks on window
void checkclicks(bool& pressed)
{
    if (ev.type == Event::MouseButtonReleased)
        pressed = 1;

    if (mouspos.x > 810 + 28 && mouspos.x < 810 + 28 + 58 / 2.0 && mouspos.y > 47 + 680 && mouspos.y < 94 / 2.0 + 47 + 680 &&
        (opened.top() != "win" && opened.top() != "lose"))
    {
        Bicon[0].setScale(0.5 + 0.09, 0.5 + 0.09);
        if (ev.type == Event::MouseButtonPressed && (ev.mouseButton.button == Mouse::Left && pressed))
        {

            if (opened.size() > 1)
            {
                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                if (opened.top() == "play" || opened.top() == "credit")
                {
                    musicgame.openFromFile("Assets/Sounds/MAIN.ogg");
                    musicgame.setLoop(1);
                    musicgame.play();
                }
                opened.pop();
            }

            pressed = 0;
        }
    }
    else
        Bicon[0].setScale(0.5, 0.5);

    if (opened.top() == "play" && !loading)
    {
        directionsOfObjects();
        clicks();
    }
    else if (opened.top() == "options")
    {
        // theme 0
        if (mouspos.x > 50 && mouspos.x < 50 + 68 * 2 && mouspos.y > 500 && mouspos.y < 500 + 50 * 2) {
            if (ev.type == Event::MouseButtonReleased)
                pressed = 1;
            if (ev.type == Event::MouseButtonPressed && (ev.mouseButton.button == Mouse::Left && pressed))
            {

                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                Sthemes[0].setScale(2.5, 2.5);

                Sthemes[1].setScale(2, 2);
                Sthemes[2].setScale(2, 2);
                Sthemes[3].setScale(2, 2);

                Tbubbles.loadFromFile("Assets/Textures/color8.png");

                pressed = 0;
            }
        }
        // theme 1
        else if (mouspos.x > 225 + 50 && mouspos.x < 225 + 50 + 60 * 2 && mouspos.y > 500 && mouspos.y < 500 + 52 * 2) {
            if (ev.type == Event::MouseButtonReleased)
                pressed = 1;
            if (ev.type == Event::MouseButtonPressed && (ev.mouseButton.button == Mouse::Left && pressed))
            {

                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                Sthemes[1].setScale(2.5, 2.5);

                Sthemes[0].setScale(2, 2);
                Sthemes[2].setScale(2, 2);
                Sthemes[3].setScale(2, 2);



                Tbubbles.loadFromFile("Assets/Textures/color.png");

                pressed = 0;
            }
        }
        // theme 2
        else if (mouspos.x > 500 && mouspos.x < 500 + 58 * 2 && mouspos.y > 500 && mouspos.y < 590) {
            if (ev.type == Event::MouseButtonReleased)
                pressed = 1;
            if (ev.type == Event::MouseButtonPressed && (ev.mouseButton.button == Mouse::Left && pressed))
            {

                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                Sthemes[2].setScale(2.5, 2.5);

                Sthemes[0].setScale(2, 2);
                Sthemes[1].setScale(2, 2);
                Sthemes[3].setScale(2, 2);

                Tbubbles.loadFromFile("Assets/Textures/hearts.png");

                pressed = 0;
            }
        }
        // theme 3 
        else if (mouspos.x > 675 + 50 && mouspos.x < 675 + 50 + 58 * 2 && mouspos.y > 500 && mouspos.y < 500 + 54 * 2) {
            if (ev.type == Event::MouseButtonReleased)
                pressed = 1;
            if (ev.type == Event::MouseButtonPressed && (ev.mouseButton.button == Mouse::Left && pressed))
            {

                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                Sthemes[3].setScale(2.5, 2.5);

                Sthemes[0].setScale(2, 2);
                Sthemes[1].setScale(2, 2);
                Sthemes[2].setScale(2, 2);

                Tbubbles.loadFromFile("Assets/Textures/fruits2.png");

                pressed = 0;
            }
        }

        if (mouspos.x > 810 && mouspos.x < 810 + 58 && mouspos.y > 80 && mouspos.y < 80 + 94 && idxvs < 9)
        {
            if (ev.type == Event::MouseButtonReleased)
                pressed = 1;
            if (ev.type == Event::MouseButtonReleased && (ev.mouseButton.button == Mouse::Left))
            {
                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                ++idxvs;
                pressed = 0;
            }
        }
        if (mouspos.x > 810 - 65 && mouspos.x < 810 + 58 - 65 && mouspos.y > 80 && mouspos.y < 80 + 94 && idxvs > 0)
        {
            if (ev.type == Event::MouseButtonReleased)
                pressed = 1;
            if (ev.type == Event::MouseButtonPressed && (ev.mouseButton.button == Mouse::Left && pressed))
            {
                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                --idxvs;
                pressed = 0;
            }
        }
        if (mouspos.x > 810 - 65 && mouspos.x < 810 + 58 - 65 && mouspos.y > 250 && mouspos.y < 250 + 94 && idxvm > 0)
        {
            if (ev.type == Event::MouseButtonReleased)
                pressed = 1;
            if (ev.type == Event::MouseButtonPressed && (ev.mouseButton.button == Mouse::Left && pressed))
            {
                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                --idxvm;
                pressed = 0;
            }
        }
        if (mouspos.x > 810 && mouspos.x < 810 + 58 && mouspos.y > 250 && mouspos.y < 250 + 94 && idxvm < 9)
        {
            if (ev.type == Event::MouseButtonReleased)
                pressed = 1;
            if (ev.type == Event::MouseButtonPressed && (ev.mouseButton.button == Mouse::Left && pressed))
            {
                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                ++idxvm;
                pressed = 0;
            }
        }
    }

    else if (opened.top() == "levels")
    {
        int level = enter_levels();

        switch (level)
        {
        case 1:
            bring_bubbles_lev1();
            break;
        case 2:
            bring_bubbles_lev2();
            break;
        case 3:
            bring_bubbles_lev3();
            break;
        case 4:
            bring_bubbles_lev4();
            break;
        case 5:
            bring_bubbles_lev5();
            break;
        case 6:
            bring_bubbles_lev6();
            break;
        case 7:
            bring_bubbles_lev7();
            break;
        case 8:
            bring_bubbles_lev8();
            break;
        case 9:
            bring_bubbles_lev9();
            break;
        }
    }
    else if (opened.top() == "lose" || (currentlev == 9 && opened.top() == "win"))
    {
        // retry
        if (mouspos.x > 300 - 89 && mouspos.x < 300 + 89 && mouspos.y > 450 - 43.5 && mouspos.y < 450 + 43.5)
        {
            if (ev.type == Event::MouseButtonReleased)
                pressed = 1;
            if (ev.type == Event::MouseButtonPressed && (ev.mouseButton.button == Mouse::Left && pressed))
            {
                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                loadgame();
                opened.pop();
                opened.push("play");
                pressed = 0;
            }

        }
    }
    else if (opened.top() == "win" && currentlev < 9)
    {
        // next
        if (mouspos.x > 300 - 89 && mouspos.x < 300 + 89 && mouspos.y > 450 - 43.5 && mouspos.y < 450 + 43.5 && currentlev < 9)
        {
            if (ev.type == Event::MouseButtonReleased)
                pressed = 1;
            if (ev.type == Event::MouseButtonPressed && (ev.mouseButton.button == Mouse::Left && pressed))
            {
                currentlev++;
                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                loadgame();
                opened.pop();
                opened.push("play");
                pressed = 0;
            }

        }
    }
    if (opened.top() == "win" || opened.top() == "lose") {
        // menu
        if (mouspos.x > 600 - 89 && mouspos.x < 600 + 89 && mouspos.y > 450 - 43.5 && mouspos.y < 450 + 43.5) {
            if (ev.type == Event::MouseButtonReleased)
                pressed = 1;
            if (ev.type == Event::MouseButtonPressed && (ev.mouseButton.button == Mouse::Left && pressed))
            {
                loadlastgame();
                soundgame.openFromFile("Assets/Sounds/button.ogg");
                soundgame.play();
                while (opened.size() > 1) {
                    opened.pop();
                }
                musicgame.openFromFile("Assets/Sounds/MAIN.ogg");
                musicgame.setLoop(1);
                musicgame.play();
                pressed = 0;
            }
        }
    }
}
//--------------------------------------------------
           // load && save 
void load() {
    ifstream load("savedgame.txt");
    while (load.good()) {
        int lev;
        load >> lev;
        level[lev].open = 1;
        load >> level[lev].score >> level[lev].stars;
    }
}
void save() {
    for (int i = 1; i < 10; i++) {
        if (level[i].open) {
            savegame << i << " " << level[i].score << " " << level[i].stars << " ";
        }
    }
}
//__________________________________________________
int main()
{
    bebo
        window.setFramerateLimit(60);
    loadingbar();
    srand(time(0));
    loadfiles();
    bring_gif();
    settextures();
    score();
    numballs();
    store();
    Menu();
    load();
    savegame.open("savedgame.txt");
    save();
    musicgame.setVolume(0);
    loadlastgame();
    musicgame.openFromFile("Assets/Sounds/MAIN.ogg");
    musicgame.setVolume(idxvm);
    musicgame.setLoop(1);
    musicgame.play();
    opened.push("menu");
    while (window.isOpen())
    {
        //-------------------------------------------------------------------------------------
        while (window.pollEvent(ev))
        {

            mouspos = Vector2f(Mouse::getPosition(window));

            switch (ev.type)
            {
            case Event::Closed:
                savegame.close();
                window.close();
                break;
            }
            checkclicks(pressed);
        }
        //-------------------------------------------------------------------------------------
        musicgame.setVolume(idxvm / 9.0 * 100);
        soundgame.setVolume(idxvs / 9.0 * 100);
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
        {
            savegame.close();
            window.close();
        }

        window.clear();

        if (opened.top() == "menu")
        {
            i %= 85;
            time1++;
            if (time1 == 9)
            {
                window.draw(gifback[i++]);
                time1 = 0;
            }
            else
            {
                window.draw(gifback[i]);
            }
            drawmenu();
        }

        else if (opened.top() == "play")
        {
            if (!loading) {
                win = 1;
                drawObjects();
                window.draw(textScore);
                window.draw(text2);
                window.draw(text3);
                window.draw(text4);
                if (bub_pushed.size() > 0) {
                    drawanimation();
                }
                if (movingball[idxmoves - 1].getPosition().y == 2000)
                {

                    if (!ballsleft && !win)
                    {
                        win = 1;
                        for (int i = 0; i < 6; i++)
                        {
                            for (int j = 0; j < x; j++)
                            {
                                num[j].bubbles_color[i].move(0, num[j].velocity[i]);
                                window.draw(num[j].bubbles_color[i]);
                                int x = num[j].bubbles_color[i].getPosition().x;
                                int y = num[j].bubbles_color[i].getPosition().y;
                                if (y <= 16 * scale + 5 && num[j].bubbles_color[i].getTexture() == &Tbubbles)
                                {
                                    win = 0;
                                }
                            }
                        }
                        if (!win) {
                            musicgame.openFromFile("Assets/Sounds/lose.ogg");
                            musicgame.setLoop(0);
                            musicgame.play();
                            opened.pop();
                            opened.push("lose");
                            win = 1;
                            if (thescore > level[currentlev].score) {
                                level[currentlev].score = thescore;
                            }
                            save();
                        }

                    }
                    else if (win)
                    {
                        musicgame.openFromFile("Assets/Sounds/won.ogg");
                        musicgame.setLoop(0);
                        musicgame.play();
                        opened.pop();
                        opened.push("win");
                        level[currentlev + 1].open = 1;
                        if (thescore > level[currentlev].score) {
                            level[currentlev].score = thescore;
                            if (level[currentlev].score <= 500) {
                                level[currentlev].stars = 1;
                            }
                            else if (level[currentlev].score > 500 && level[currentlev].score <= 1000) {
                                level[currentlev].stars = 2;
                            }
                            else if (level[currentlev].score > 1000) {
                                level[currentlev].stars = 3;
                            }
                        }
                        save();
                    }
                }

            }
            else {

                if (!idxloading) {
                    soundgame.openFromFile("Assets/Sounds/ready.ogg");
                    soundgame.play();
                }
                if (timerloading == 9) {
                    window.draw(Sloading[idxloading++]);
                    timerloading = 0;
                }
                else {
                    window.draw(Sloading[idxloading]);
                }
                //  window.draw(Slogo);
                timerloading++;
                if (idxloading == 10) {
                    loading = 0;
                    idxloading = 0;
                    timerloading = 9;
                }
            }
        }
        else if (opened.top() == "options")
        {
            i %= 85;
            time1++;
            if (time1 == 9)
            {
                window.draw(gifback[i++]);
                time1 = 0;
            }
            else
            {
                window.draw(gifback[i]);
            }
            soundicon();
            soundcontrol();
            credit();
            window.draw(Sthemes[0]);
            window.draw(Sthemes[1]);
            window.draw(Sthemes[2]);
            window.draw(Sthemes[3]);
            window.draw(Sselect_theme);
        }

        else if (opened.top() == "levels")
        {
            i %= 85;
            time1++;
            if (time1 == 9)
            {
                window.draw(gifback[i++]);
                time1 = 0;
            }
            else
            {
                window.draw(gifback[i]);

            }
            MainOFLevels();
        }
        else if (opened.top() == "credit")
        {

            window.draw(Sgifnames[0]);
            names();
        }

        if (opened.top() == "win")
        {
            window.draw(back);
            window.draw(madf3);
            if (ballsleft) {
                window.draw(StoredBalls[idxball % 6]);
            }
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < x; j++)
                {
                    window.draw(num[j].bubbles_color[i]);
                }
            }
            gameend();
            window.draw(Sgameend[0]);//win || gameover
            window.draw(Sgameend[1]);// next || retry
            window.draw(Sgameend[2]);//menu
        }
        if (opened.top() == "lose")
        {
            window.draw(back);
            window.draw(madf3);
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < x; j++)
                {
                    window.draw(num[j].bubbles_color[i]);
                }
            }
            gameend();
            window.draw(Sgameend[0]);
            window.draw(Sgameend[1]);
            window.draw(Sgameend[2]);
        }
        if (opened.size() > 1 && opened.top() != "win" && opened.top() != "lose")
        {
            Back();
        }

        window.display();

    }

    return 0;
}
//__________________________________________________