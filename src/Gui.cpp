#include <stdio.h>
#include <stdarg.h>
#include "main.hpp"

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

Gui::Message::Message(const char *text, const TCODColor &col) :
	text(strdup(text)),col(col){
}

Gui::Message::~Message(){
	free(text);
}

void Gui::render(){
    //clear the GUI console
    con->setDefaultBackground(TCODColor::black);
    con->clear();
    
    //draw the health bar
    renderBar(1,1,BAR_WIDTH,"HP",engine.player->destructible->hp,
            engine.player->destructible->maxHp,TCODColor::lightRed,TCODColor::darkerRed);
    
    //draw the message log
    int y=1;
    float colorCoef=0.4f;
    for(auto &message : log){
        con->setDefaultForeground(message->col * colorCoef);
        con->print(MSG_X,y,message->text);
        y++;
        if(colorCoef < 1.0f){
            colorCoef += 0.3f;
        }
    }

    renderMouseLook();
    TCODConsole::blit(con,0,0,engine.screenWidth,PANEL_HEIGHT,
            TCODConsole::root,0,engine.screenHeight-PANEL_HEIGHT);
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

void Gui::message(const TCODColor& col, const char* text, ...){
    //build the text
    va_list ap;
    char buf[128];
    va_start(ap,text);
    vsprintf(buf,text,ap);
    va_end(ap);
    
    char *lineBegin=buf;
    char *lineEnd;
    
    do {
    // make room for the new message
        if ( log.size() == MSG_HEIGHT ) {
            Message *toRemove=log.get(0);
            log.remove(toRemove);
            delete toRemove;
        }
        lineEnd=strchr(lineBegin,'\n');
        if(lineEnd){
            *lineEnd='\0';
        }
        Message *msg = new Message(lineBegin,col);
        log.push(msg);
        lineBegin=lineEnd+1;
    }while(lineEnd);
}

void Gui::renderMouseLook(){
    if( !engine.map->isInFov(engine.mouse.cx,engine.mouse.cy)){
        //out of FOV
        return;
    }
    char buf[128]="";
    bool first=true;
    for(auto &actor : engine.actors){
        if(actor->x == engine.mouse.cx && actor->y == engine.mouse.cy){
            if (!first){
                strcat(buf,", ");
            }else{
                first=false;
            }
            strcat(buf,actor->name);
        }
    }
    
    con->setDefaultForeground(TCODColor::lightGrey);
    con->print(1,0,buf);
}

void Gui::save(TCODZip &zip) {
  zip.putInt(log.size());
  for(Message **iterator=log.begin(); iterator != log.end(); iterator++) {
    zip.putString((*iterator)->text);
    zip.putColor(&(*iterator)->col);
  }
}

void Gui::load(TCODZip &zip) {
  int nbMessages=zip.getInt();
  while (nbMessages>0){
    const char *text=zip.getString();
    TCODColor col = zip.getColor();
    message(col,text);
    nbMessages--;
  }
}
