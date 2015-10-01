#include "main.hpp"
#include "Gui.hpp"

static const int PANEL_HEIGHT=7;
static const int BAR_WIDTH=20;
static const int MSG_X=BAR_WIDTH + 2;
static const int MSG_HEIGHT=PANEL_HEIGHT-1;

Gui::Gui(){
    con = new TCODConsole(engine.screenWidth,PANEL_HEIGHT);
}

Gui::~Gui(){
    delete con;
    log.clearAndDelete();
}

void Gui::render(){
    //clear the GUI console
    con->setDefaultBackground(TCODColor::black);
    con->clear();
    
    //draw the health bar
    renderBar(1,1,BAR_WIDTH,"HP",engine.player->destructible->hp,
            engine.player->destructible->maxHp,TCODColor::lightRed,TCODColor::darkerRed);
    TCODConsole::blit(con,0,0,engine.screenWidth,PANEL_HEIGHT,
            TCODConsole::root,0,engine.screenHeight-PANEL_HEIGHT);
    
    //draw the message log
    int y=1;
    float colorCoef=0.4f;
    for(Message **it=log.begin(); it != log.end(); it++) {
        Message *message=*it;
        con->setDefaultForeground(message-> * colorCoef);
        con->print(MSG_X,y,message->text);
        
    }
}

void Gui::renderBar(int x, int y, int width, const char* name, float value, 
        float maxValue, const TCODColor& barColor, const TCODColor& backColor){
    con->setDefaultBackground(backColor);
    con->rect(x,y,width,1,false,TCOD_BKGND_SET);
    
    int barWidth = (int)(value/ maxValue * width);
    if(barWidth > 0){
        //draw the bar
        con->setDefaultBackground(barColor);
        con->rect(x,y,barWidth,1,false,TCOD_BKGND_SET);
    }
    con->setDefaultForeground(TCODColor::white);
    con->printEx(x+width/2,y,TCOD_BKGND_NONE,TCOD_CENTER,
            "%s: %g/%g",name, value, maxValue);
}

Gui::Message::Message(const char *text, const TCODColor &col) :
	text(strdup(text)),col(col){
}

Gui::Message::~Message(){
	free(text);
}
