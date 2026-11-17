

#include "chess.h"
#include "engine.h"
#include "ui.h"

int main(){

    init_chess();
    init_engine();
    chess_ui_run();

    return 0;
}