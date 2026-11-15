#pragma once

#include "chess.h"
#include "engine.h"
#include "notations.h"

#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define NUL_INDEX (-1)

i32 mouse_x = 0;
i32 mouse_y = 0;
bool mouse_left = false;
bool mouse_right = false;
i32 hover_index = NUL_INDEX;
bool mouse_over_board = false;
bool mouse_over_menu = false;

i32 selected_index = NUL_INDEX;
i32 last_turn[2] = { NUL_INDEX, NUL_INDEX };
piece_t selected_piece = EMPTY_PIECE;
piece_t dragged_piece = EMPTY_PIECE;
bool selected_black = false;
u64 selected_turns = 0;

bool in_promotion = false;
i32 promoted_to = NUL_INDEX;
i32 promotion_indexes[4] = { NUL_INDEX, NUL_INDEX, NUL_INDEX, NUL_INDEX };
piece_t promotion_pieces[4] = { QUEEN, KNIGHT, ROOK, BISHOP };

typedef struct {
    i32 from, to;
} arrow_t;
arrow_t arrows[64 * 64] = { 0 };
i32 arrows_count = 0;
i32 selected_arrow = NUL_INDEX;
arrow_t dragged_arrow = { 0, 0 };
bool doing_arrow = false;

i32 evaluation_bar = 0;
i32 engine_active = 0;

Rectangle played_turns_panel_view = { 0 };
Vector2 played_turns_panel_scroll = { 0 };

#define HALFMOVES_MAX 20000
i32 halfmoves_count = 0;
char halfmoves_pgn[HALFMOVES_MAX][10] = { 0 };
position_t start_position = { 0 };
move_t halfmoves[HALFMOVES_MAX] = { 0 };
i32 halfmoves_at = 0;

typedef enum {
    GAME = 0,
    DRAW,
    CHECKMATE
} game_state_e;
game_state_e game_state = GAME;

// 128x128
Texture2D piece_textures[CCOLOR_COUNT][PIECE_MAX];

RenderTexture2D board_texture;
RenderTexture2D menu_texture;

typedef enum {
    SOUND_NOTIFY,
    SOUND_MOVE,
    SOUND_CHECK,
    SOUND_CAPTURE,
    SOUND_PROMOTION,
    SOUND_CASTLING,
    SOUND_GAME_START,
    SOUND_GAME_END,
    SOUND_COUNT
} sound_type_e;
Sound sounds[SOUND_COUNT];


#define SCREEN_BOARD_SIZE 800
#define SCREEN_MENU_WIDTH 400

#define SCREEN_EVAL_BAR_WIDTH  20
#define SCREEN_EVAL_BAR_OFFSET 12
#define SCREEN_EVAL_WIDTH      (SCREEN_EVAL_BAR_WIDTH + SCREEN_EVAL_BAR_OFFSET)
#define SCREEN_CONTROLS_WIDTH  (SCREEN_MENU_WIDTH - SCREEN_EVAL_WIDTH)

#define SCREEN_WIDTH  (SCREEN_BOARD_SIZE + SCREEN_MENU_WIDTH)
#define SCREEN_HEIGHT (SCREEN_BOARD_SIZE)

#define SQUARE_SIDE      100
#define HALF_SQUARE_SIDE 50

#define COLOR_BRIGHT   (Color){0xFF, 0xCF, 0x9F, 0xFF}
#define COLOR_DARK     (Color){0xD2, 0x8C, 0x45, 0xFF}

#define SELECTED_TINT  (Color){0x71, 0x81, 0x68, 0x7F}
#define SELECTED_HOVER (Color){0x71, 0x81, 0x68, 0x5F}
#define SELECTED_MID   (Color){0x71, 0x81, 0x68, 0x4F}
#define SELECTED_BLANK (Color){0x71, 0x81, 0x68, 0x00}
#define SELECTED_COLOR (Color){0x71, 0x81, 0x68, 0xFF}
//#define ARROW_COLOR    (Color){0x6D, 0x7F, 0x58, 0xAF}
#define ARROW_COLOR    (Color){0xC7, 0xC1, 0x10, 0xAF}

#define MOVE_HIGHLIGHT  (Color){0xF7, 0xF1, 0x1D, 0x50}
#define MOVE_HIGHLIGHT2 (Color){0x8B, 0xCE, 0xF7, 0x6F}

#define MATE_HIGHLIGHT  (Color){0xE8, 0x11, 0x23, 0x6F}
#define MATE_TINT       (Color){0xFF, 0xFF, 0xFF, 0x2F}
#define WHITE_WON_COLOR (Color){0xEF, 0xEF, 0xEF, 0xFF}
#define BLACK_WON_COLOR (Color){0x10, 0x10, 0x10, 0xFF}
#define DRAW_COLOR      (Color){0x70, 0x70, 0x70, 0xFF}

#define MENU_BACKGROUND     (Color){0x18, 0x18, 0x18, 0xFF}
// #define EVAL_BACKGROUND     (Color){0x38, 0x38, 0x38, 0xFF}
#define EVAL_BAR_BACKGROUND (Color){0x28, 0x28, 0x28, 0xFF}
// #define EVAL_BLACK          (Color){0x10, 0x10, 0x10, 0xFF}
#define EVAL_BLACK          (Color){0x28, 0x28, 0x28, 0xFF}
#define EVAL_WHITE          (Color){0xEF, 0xEF, 0xEF, 0xFF}

#define PLAYED_TURNS_PANEL_BACKGROUND (Color){0x28, 0x28, 0x28, 0xFF}
#define PLAYED_TURN_NUMBER_BACKGROUND (Color){0x38, 0x38, 0x38, 0xFF}
#define PLAYED_TURN_NUMBER_COLOR      (Color){0x68, 0x68, 0x68, 0xFF}
#define CURRENT_TURN_HIGHLIGHT_COLOR  (Color){0xC8, 0xC8, 0xC8, 0x12}
#define PLAYED_TURNS_TEXT_COLOR       (Color){0xC8, 0xC8, 0xC8, 0xFF}


Texture2D load_texture(char* file_path){
    Texture2D texture = LoadTexture(file_path);
    SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
    return texture;
}

void load_assets(){
    piece_textures[CWHITE][PAWN]   = load_texture("resources/white-pawn.png");
    piece_textures[CBLACK][PAWN]   = load_texture("resources/black-pawn.png");
    piece_textures[CWHITE][KNIGHT] = load_texture("resources/white-knight.png");
    piece_textures[CBLACK][KNIGHT] = load_texture("resources/black-knight.png");
    piece_textures[CWHITE][BISHOP] = load_texture("resources/white-bishop.png");
    piece_textures[CBLACK][BISHOP] = load_texture("resources/black-bishop.png");
    piece_textures[CWHITE][ROOK]   = load_texture("resources/white-rook.png");
    piece_textures[CBLACK][ROOK]   = load_texture("resources/black-rook.png");
    piece_textures[CWHITE][QUEEN]  = load_texture("resources/white-queen.png");
    piece_textures[CBLACK][QUEEN]  = load_texture("resources/black-queen.png");
    piece_textures[CWHITE][KING]   = load_texture("resources/white-king.png");
    piece_textures[CBLACK][KING]   = load_texture("resources/black-king.png");

    sounds[SOUND_NOTIFY] = LoadSound("resources/notify.mp3");
    sounds[SOUND_MOVE] = LoadSound("resources/move-self.mp3");
    sounds[SOUND_CHECK] = LoadSound("resources/move-check.mp3");
    sounds[SOUND_CAPTURE] = LoadSound("resources/capture.mp3");
    sounds[SOUND_PROMOTION] = LoadSound("resources/promote.mp3");
    sounds[SOUND_CASTLING] = LoadSound("resources/castle.mp3");
    sounds[SOUND_GAME_START] = LoadSound("resources/game-start.mp3");
    sounds[SOUND_GAME_END] = LoadSound("resources/game-end.mp3");
}

i32 maxv(i32 a, i32 b){
    if(a > b) return a;
    return b;
}

void index_to_position(i32 index, i32* x, i32* y){
    *x = (index & 7) * SQUARE_SIDE;
    *y = SCREEN_HEIGHT - SQUARE_SIDE - ((index >> 3) * SQUARE_SIDE);
}
i32 position_to_index(i32 x, i32 y){
    i32 index = x / SQUARE_SIDE + (((SCREEN_HEIGHT - y) / SQUARE_SIDE) << 3);
    return index;
}

void deselect_piece(){
    selected_index = NUL_INDEX;
    selected_piece = EMPTY_PIECE;
    dragged_piece = EMPTY_PIECE;
}
void select_piece(position_t* pos, i32 index){
    selected_index = index;
    selected_piece = piece_at_all(pos, selected_index, &selected_black);
    if(selected_black == pos->blacks_turn){
        dragged_piece = selected_piece;
    }

    // recalculate masks from other perspective, as position only stores masks for current perspecive
    if(pos->blacks_turn != selected_black){ // todo: fixme
        pos->blacks_turn = selected_black;
        setup_next_turn(pos);
        selected_turns = get_index_legal_turns(pos, selected_black, selected_index, selected_piece);
        pos->blacks_turn = !selected_black;
        setup_next_turn(pos);
    }else{
        selected_turns = get_index_legal_turns(pos, selected_black, selected_index, selected_piece);
    }
}

void select_for_turn_highlight(i32 from, i32 to){
    last_turn[0] = from;
    last_turn[1] = to;
}
void select_for_turn_highlight(move_t move){
    select_for_turn_highlight(move_get_from(move), move_get_to(move));
}
void deselect_for_turn_highlight(){
    select_for_turn_highlight(NUL_INDEX, NUL_INDEX);
}

void write_pgn(position_t* pos, move_t move){
    write_move_pgn(halfmoves_pgn[halfmoves_at], pos, move);
}
void save_halfmove(position_t* pos, move_t move){
    write_pgn(pos, move);
    if(halfmoves_at < halfmoves_count){
        if(halfmoves[halfmoves_at] != move){ // we went back and chose other line
            halfmoves[halfmoves_at++] = move;
            halfmoves_count = halfmoves_at;
        }else{
            halfmoves_at++;
        }
    }else{
        assert(halfmoves_at == halfmoves_count);
        halfmoves[halfmoves_at++] = move;
        halfmoves_count = halfmoves_at;
    }

}

void play_move_sound(position_t* pos, move_t move){
    move_type_e type = move_get_type(move);
    if(game_state == DRAW || game_state == CHECKMATE){
        PlaySound(sounds[SOUND_GAME_END]);
    }else if(in_check(pos)){
        PlaySound(sounds[SOUND_CHECK]);
    }else if(type == CASTLING){
        PlaySound(sounds[SOUND_CASTLING]);
    }else if(type == PROMOTION){
        PlaySound(sounds[SOUND_PROMOTION]);
    }else if(type == CAPTURE || type == ENPASSANT){
        PlaySound(sounds[SOUND_CAPTURE]);
    }else{
        PlaySound(sounds[SOUND_MOVE]);
    }
}

void after_halfmove(position_t* pos, i32 sound_offset){
    play_move_sound(pos, halfmoves[halfmoves_at - sound_offset]);
    if(halfmoves_at > 0) select_for_turn_highlight(halfmoves[halfmoves_at - 1]);
    else deselect_for_turn_highlight();
    deselect_piece();
}
void load_at_halfmove(position_t* pos, i32 halfmove){
    if(halfmoves_at < halfmoves_count || halfmove < halfmoves_count){
        *pos = start_position;

        bool back = halfmove < halfmoves_at;
        if(halfmove > halfmoves_count) halfmove = halfmoves_count;

        for(i32 i = 0; i < halfmove; i++){
            do_move(pos, halfmoves[i]);
        }

        halfmoves_at = halfmove;
        after_halfmove(pos, (back ? 0 : 1));

    }
}
void load_next_halfmove(position_t* pos){
    if(halfmoves_at < halfmoves_count){
        do_move(pos, halfmoves[halfmoves_at]);
        halfmoves_at++;
        if(halfmoves_at > halfmoves_count) halfmoves_at = halfmoves_count;

        after_halfmove(pos, 1);
    }
}
void load_previous_halfmove(position_t* pos){
    if(halfmoves_at > 0){
        load_at_halfmove(pos, halfmoves_at - 1);
    }
}
void load_first_halfmove(position_t* pos){
    if(halfmoves_at > 0){
        *pos = start_position;
        halfmoves_at = 0;
        after_halfmove(pos, 0);
    }
}
void load_last_halfmove(position_t* pos){
    load_at_halfmove(pos, halfmoves_count);
}

bool mouse_is_over_board(){
    return mouse_x >= 0 && mouse_x < SCREEN_BOARD_SIZE && mouse_y >= 0 && mouse_y < SCREEN_BOARD_SIZE;
}
bool mouse_is_over_menu(){
    return mouse_x >= SCREEN_BOARD_SIZE && mouse_x < (SCREEN_BOARD_SIZE + SCREEN_MENU_WIDTH) && mouse_y >= 0 && mouse_y < SCREEN_BOARD_SIZE;
}

bool is_piece_selected(){
    return selected_piece != EMPTY_PIECE;
}
bool is_selected(){
    return selected_index != NUL_INDEX;
}
bool is_piece_dragging(){
    return dragged_piece != EMPTY_PIECE;
}

void draw_square(i32 x, i32 y, Color color){
    DrawRectangle(x, y, SQUARE_SIDE, SQUARE_SIDE, color);
}
void draw_square_by_index(i32 index, Color color){
    i32 x, y;
    index_to_position(index, &x, &y);
    draw_square(x, y, color);
}
void draw_piece(i32 x, i32 y, bool black, piece_t piece){
    //DrawTexture(piece_textures[black][piece], x, y, WHITE);
    DrawTexturePro(piece_textures[black][piece], (Rectangle){ 0.f, 0.f, 128.f, 128.f }, (Rectangle){ (f32)x, (f32)y, SQUARE_SIDE, SQUARE_SIDE }, (Vector2){ 0.f, 0.f }, 0, WHITE);
}
void draw_piece_by_index(i32 index, bool black, piece_t piece){
    i32 x, y;
    index_to_position(index, &x, &y);
    draw_piece(x, y, black, piece);
}
void draw_pieces_mask(u64 mask, bool black, piece_t piece){
    i32 index;
    while(mask){
        index = extract_piece(&mask);
        draw_piece_by_index(index, black, piece);
    }
}
void draw_attack(i32 x, i32 y){
    DrawCircleGradient(x, y, 15, SELECTED_MID, SELECTED_COLOR);
}
void draw_attacks(u64 mask){
    i32 index, x, y;
    while(mask){
        index = extract_piece(&mask);
        index_to_position(index, &x, &y);
        draw_attack(x + HALF_SQUARE_SIDE, y + HALF_SQUARE_SIDE);
    }
}
void draw_arrow(i32 from, i32 to){
    i32 xf, yf, xt, yt;
    index_to_position(from, &xf, &yf);
    if(from == to){
        DrawRing((Vector2){ xf + HALF_SQUARE_SIDE, yf + HALF_SQUARE_SIDE }, 35, 40, 0, 360, 0, ARROW_COLOR);
    }else {
        index_to_position(to, &xt, &yt);
        f32 size = hypotf(xt - xf, yt - yf) - 7;
        f32 angle = Vector2LineAngle((Vector2){ xf, yf }, (Vector2){ xt, yt }) * RAD2DEG;
        DrawRectanglePro((Rectangle){ xf + HALF_SQUARE_SIDE, yf + HALF_SQUARE_SIDE, size, 16 }, (Vector2){ 8, 8 }, -angle, ARROW_COLOR);
        DrawPoly((Vector2){ xt + HALF_SQUARE_SIDE, yt + HALF_SQUARE_SIDE }, 3, 30, -angle, ARROW_COLOR);
    }
}
void draw_arrows(){
    for(i32 i = 0; i < arrows_count; i++){
        draw_arrow(arrows[i].from, arrows[i].to);
    }
    if(mouse_over_board && doing_arrow && dragged_arrow.from != dragged_arrow.to){
        draw_arrow(dragged_arrow.from, dragged_arrow.to);
    }
}
void draw_pieces(position_t* pos){
    for(i32 i = 0; i < CCOLOR_COUNT; i++){
        for(i32 j = PAWN; j < PIECE_MAX; j++){
            draw_pieces_mask(pos->pieces[j] & pos->colors[i], i, j);
        }
    }
}
void draw_selected(position_t* pos){
    if(last_turn[0] != NUL_INDEX && last_turn[1] != NUL_INDEX){
        draw_square_by_index(last_turn[0], MOVE_HIGHLIGHT);
        draw_square_by_index(last_turn[1], MOVE_HIGHLIGHT);
    }
    if(is_selected()){
        draw_square_by_index(selected_index, SELECTED_TINT);
        draw_attacks(selected_turns);
    }
    if(is_piece_dragging()){
        if(get_bit(selected_turns, hover_index)){
            draw_square_by_index(hover_index, SELECTED_HOVER);
        }
        draw_piece(mouse_x - HALF_SQUARE_SIDE, mouse_y - HALF_SQUARE_SIDE, selected_black, dragged_piece);
    }
}
void draw_check(position_t* pos){
    if(in_check(pos)){
        draw_square_by_index(find_piece(pos, pos->blacks_turn, KING), MATE_HIGHLIGHT);
    }
}
void draw_promotion(position_t* pos){
    if(!in_promotion){
        return;
    }
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SELECTED_HOVER);
    i32 index;
    for(i32 i = 0; i < 4; i++){
        index = promotion_indexes[i];
        draw_piece_by_index(index, pos->blacks_turn, promotion_pieces[i]);
        if(index == hover_index){
            draw_square_by_index(index, SELECTED_TINT);
        }
    }
}
void draw_board_to_texture(){ //draw it to texture then render that texture, because why not
    BeginTextureMode(board_texture);
    Color color;
    for(i32 i = 0; i < 64; i++){
        color = ((i + !(i & 8)) & 1) ? COLOR_DARK : COLOR_BRIGHT;
        draw_square_by_index(i, color);
    }
    char text_letter[2] = { 'a', '\0' };
    char text_number[2] = { '1', '\0' };
    int font_size = 20;
    for(i32 i = 0; i < 8; i++){
        color = (i & 1) ? COLOR_DARK : COLOR_BRIGHT;
        DrawText(text_letter, 85 + i * SQUARE_SIDE, SCREEN_HEIGHT - 5 - font_size                     , font_size, color);
        DrawText(text_number, 5                   , SCREEN_HEIGHT - (75 + i * SQUARE_SIDE) - font_size, font_size, color);
        text_letter[0]++;
        text_number[0]++;
    }
    EndTextureMode();
}
void draw_board() {
    DrawTextureRec(board_texture.texture, (Rectangle){ 0, 0, (f32)board_texture.texture.width, (f32)-board_texture.texture.height }, (Vector2){ 0, 0 }, WHITE);
}

void draw_text_centered(const char* text, i32 x, i32 y, i32 font_size, Color color){
    i32 text_width = MeasureText(text, font_size);
    i32 textx = x - text_width / 2;
    i32 texty = y - font_size / 2;
    DrawText(text, textx, texty, font_size, color);
}

void draw_end_screen(position_t* pos){
    i32 king_index = find_piece(pos, pos->blacks_turn, KING);
    draw_square_by_index(king_index, MATE_HIGHLIGHT);
    if(game_state != DRAW){
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, MATE_TINT);
    }
    const char* text = (game_state == CHECKMATE) ? (pos->blacks_turn ? "White Won" : "Black Won") : "Draw";
    Color color = (game_state == CHECKMATE) ? (pos->blacks_turn ? WHITE_WON_COLOR : BLACK_WON_COLOR) : DRAW_COLOR;
    draw_text_centered(text, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 120, color);
    draw_text_centered("Press ENTER to restart", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 120, 40, color);
}


void menu_init(){
    GuiSetStyle(BUTTON, BASE_COLOR_DISABLED,   0xa8a8a8ff);
    GuiSetStyle(BUTTON, BORDER_COLOR_DISABLED, 0x8a8a8aff);
    GuiSetStyle(BUTTON, TEXT_COLOR_DISABLED,   0x7a7a7aff);

    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED,    0xe8e8e8ff);
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED,  0xa0a0a0ff);
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED,    0x707070ff);

    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED,    0xf5f5f5ff);
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED,  0x909090ff);
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED,    0x505050ff);

    GuiSetStyle(TOGGLE, BASE_COLOR_DISABLED,   0xa8a8a8ff);
    GuiSetStyle(TOGGLE, BORDER_COLOR_DISABLED, 0x8a8a8aff);
    GuiSetStyle(TOGGLE, TEXT_COLOR_DISABLED,   0x7a7a7aff);

    GuiSetStyle(TOGGLE, BASE_COLOR_FOCUSED,    0xe8e8e8ff);
    GuiSetStyle(TOGGLE, BORDER_COLOR_FOCUSED,  0xa0a0a0ff);
    GuiSetStyle(TOGGLE, TEXT_COLOR_FOCUSED,    0x707070ff);

    GuiSetStyle(TOGGLE, BASE_COLOR_PRESSED,    0xf5f5f5ff);
    GuiSetStyle(TOGGLE, BORDER_COLOR_PRESSED,  0x909090ff);
    GuiSetStyle(TOGGLE, TEXT_COLOR_PRESSED,    0x505050ff);

    GuiSetStyle(SLIDER, BASE_COLOR_DISABLED,   0xa8a8a8ff);
    GuiSetStyle(SLIDER, BORDER_COLOR_DISABLED, 0x8a8a8aff);
    GuiSetStyle(SLIDER, TEXT_COLOR_DISABLED,   0x7a7a7aff);

    GuiSetStyle(SLIDER, BASE_COLOR_FOCUSED,    0xe8e8e8ff);
    GuiSetStyle(SLIDER, BORDER_COLOR_FOCUSED,  0xa0a0a0ff);
    GuiSetStyle(SLIDER, TEXT_COLOR_FOCUSED,    0x707070ff);

    GuiSetStyle(SLIDER, BASE_COLOR_PRESSED,    0xf5f5f5ff);
    GuiSetStyle(SLIDER, BORDER_COLOR_PRESSED,  0x909090ff);
    GuiSetStyle(SLIDER, TEXT_COLOR_PRESSED,    0x505050ff);
}

i32 GuiIconButtonActivatable(Rectangle bounds, i32 icon, bool active){
    i32 old_state = GuiGetState();
    if(!active) GuiSetState(STATE_DISABLED);
    i32 ret = GuiButton(bounds, GuiIconText(icon, NULL));
    GuiSetState(old_state);
    return ret;
}

// https://lichess.org/page/accuracy
f32 calculate_eval_white_percent(i32 eval){
    return 0.5f + 0.5f * (2.f / (1.f + exp(-0.00368208f * eval)) - 1.f);
}
void draw_eval_bar(){
    i32 eval_x_pos = SCREEN_BOARD_SIZE + SCREEN_EVAL_BAR_OFFSET;
    i32 eval_y_offset = 16;
    i32 eval_width = 20;
    i32 eval_height = SCREEN_HEIGHT - eval_y_offset * 2;

    // f32 roundness = 1.f;
    // i32 roundned_side_size = eval_width * roundness;

    f32 white_eval_percent = calculate_eval_white_percent(evaluation_bar);
    i32 white_eval_height = white_eval_percent * eval_height;

    // DrawRectangle(SCREEN_BOARD_SIZE, 0, SCREEN_EVAL_WIDTH, SCREEN_HEIGHT, EVAL_BACKGROUND);

    DrawRectangle(eval_x_pos, eval_y_offset, eval_width, eval_height, EVAL_BAR_BACKGROUND);
    DrawRectangle(eval_x_pos, eval_y_offset + eval_height - white_eval_height, eval_width, white_eval_height, EVAL_WHITE);
    // DrawRectangleRounded((Rectangle){ eval_x_pos, eval_y_offset, eval_width, eval_height }, roundness, 8, EVAL_BAR_BACKGROUND);
    // DrawRectangleRounded((Rectangle){ eval_x_pos, eval_y_offset + eval_height - white_eval_height, eval_width, white_eval_height }, roundness, 8, EVAL_WHITE);

    f32 eval_number = evaluation_bar / 100.f;

    i32 eval_number_x_pos = SCREEN_BOARD_SIZE + SCREEN_EVAL_WIDTH + 10;
    i32 font_size = 30;
    DrawText(TextFormat("%c%.1f", (eval_number >= 0) ? '+' : '-', fabsf(eval_number)), eval_number_x_pos, eval_y_offset + 4, font_size, EVAL_WHITE);
}
void draw_eval(){
    if(engine_active){
        draw_eval_bar();
    }

    i32 toggle_engine_slider_x_pos = SCREEN_BOARD_SIZE + SCREEN_EVAL_WIDTH + 280;
    GuiToggleSlider((Rectangle){ toggle_engine_slider_x_pos, 18, 64, 32 }, TextFormat("#%d#;#%d#", ICON_CROSS, ICON_OK_TICK), &engine_active);

    // GuiSetStyle(SLIDER, SLIDER_PADDING, 2);
    // GuiToggleSlider((Rectangle){ 900, 480 + 20, 140, 30 }, "ON;OFF", &engine_active);
    // GuiSetStyle(SLIDER, SLIDER_PADDING, 0);
}
i32 pgn_to_icon_id(char pgn){
    switch(pgn){
    case 'N': return ICON_KNIGHT;
    case 'B': return ICON_BISHOP;
    case 'R': return ICON_ROOK;
    case 'Q': return ICON_QUEEN;
    case 'K': return ICON_KING;
    case 'O': return ICON_CASTLING;
    default:  return ICON_PAWN;
    }
}
void draw_played_turn_entry(position_t* pos, i32 x, i32 y, i32 width, i32 height, i32 halfmove, bool show_pieces_as_icons){
    char* halfmove1 = halfmoves_pgn[halfmove];
    char* halfmove2 = halfmove+1 >= halfmoves_count ? NULL : halfmoves_pgn[halfmove+1];
    char halfmove1_text[20] = { 0 };
    char halfmove2_text[20] = { 0 };
    if(show_pieces_as_icons){ // replace first char with icon
        i32 icon1_id = pgn_to_icon_id(halfmove1[0]);
        i32 advance1 = icon1_id != ICON_NONE && icon1_id != ICON_PAWN && icon1_id != ICON_CASTLING ? 1 : 0;
        strcpy(halfmove1_text, GuiIconText(icon1_id, halfmove1 + advance1));
        if(halfmove2 != NULL){
            i32 icon2_id = pgn_to_icon_id(halfmove2[0]);
            i32 advance2 = icon2_id != ICON_NONE && icon2_id != ICON_PAWN && icon2_id != ICON_CASTLING ? 1 : 0;
            strcpy(halfmove2_text, GuiIconText(icon2_id, halfmove2 + advance2));
        }
    }else{
        strcpy(halfmove1_text, halfmove1);
        if(halfmove2 != NULL) strcpy(halfmove2_text, halfmove2);
    }
    i32 turn = halfmove/2 + 1;
    const char* turn_text = TextFormat("%d", turn);

    i32 old_font_size = GuiGetStyle(DEFAULT, TEXT_SIZE);
    i32 font_size = 20;
    i32 turn_text_max_width = 48;
    i32 turn_text_x_pos = x;
    i32 turn_text_y_pos = y;

    DrawRectangle(x, y, turn_text_max_width, height, PLAYED_TURN_NUMBER_BACKGROUND);
    GuiSetStyle(DEFAULT, TEXT_SIZE, font_size);
    GuiDrawText(turn_text, (Rectangle){ turn_text_x_pos, turn_text_y_pos, turn_text_max_width, height }, TEXT_ALIGN_CENTER, PLAYED_TURN_NUMBER_COLOR);

    int old_text_alignment              = GuiGetStyle(BUTTON, TEXT_ALIGNMENT);
    int old_button_text_color           = GuiGetStyle(BUTTON, TEXT_COLOR_NORMAL);
    int old_button_color                = GuiGetStyle(BUTTON, BASE_COLOR_NORMAL);
    int old_button_focused_color        = GuiGetStyle(BUTTON, BASE_COLOR_FOCUSED);
    int old_button_pressed_color        = GuiGetStyle(BUTTON, BASE_COLOR_PRESSED);
    int old_button_border_color         = GuiGetStyle(BUTTON, BORDER_COLOR_NORMAL);
    int old_button_border_focused_color = GuiGetStyle(BUTTON, BORDER_COLOR_FOCUSED);
    int old_button_border_pressed_color = GuiGetStyle(BUTTON, BORDER_COLOR_PRESSED);

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT,       TEXT_ALIGN_LEFT);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL,    ColorToInt(PLAYED_TURNS_TEXT_COLOR));
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL,    0x00000000);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED,   0xffffff0f);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED,   0xffffff1f);
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL,  0x00000000);
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, 0x00000000);
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, 0x00000000);

    i32 pgn_halfmove_text_max_width = (width - turn_text_max_width) / 2;
    i32 pgn_white_x_pos = turn_text_x_pos + turn_text_max_width;
    i32 pgn_white_y_pos = turn_text_y_pos;
    // GuiDrawText(halfmove1, (Rectangle){ pgn_white_x_pos, pgn_white_y_pos, pgn_halfmove_text_max_width, height }, TEXT_ALIGN_CENTER, WHITE);
    if(GuiButton((Rectangle){ pgn_white_x_pos, pgn_white_y_pos, pgn_halfmove_text_max_width, height }, halfmove1_text) && game_state == GAME){
        load_at_halfmove(pos, halfmove + 1);
    }

    i32 pgn_black_x_pos = pgn_white_x_pos + pgn_halfmove_text_max_width;
    i32 pgn_black_y_pos = turn_text_y_pos;
    if(halfmove2 != NULL){
        // GuiDrawText(halfmove2, (Rectangle){ pgn_black_x_pos, pgn_black_y_pos, pgn_halfmove_text_max_width, height }, TEXT_ALIGN_CENTER, WHITE);
        if(GuiButton((Rectangle){ pgn_black_x_pos, pgn_black_y_pos, pgn_halfmove_text_max_width, height }, halfmove2_text) && game_state == GAME){
            load_at_halfmove(pos, halfmove + 2);
        }
    }

    // highlight current turn in side menu
    if(halfmoves_at == halfmove + 1){
        DrawRectangle(pgn_white_x_pos, pgn_white_y_pos, pgn_halfmove_text_max_width, height, CURRENT_TURN_HIGHLIGHT_COLOR);
    }
    else if(halfmoves_at == halfmove + 2 && halfmove + 1 < halfmoves_count){
        DrawRectangle(pgn_black_x_pos, pgn_black_y_pos, pgn_halfmove_text_max_width, height, CURRENT_TURN_HIGHLIGHT_COLOR);
    }

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT,       old_text_alignment);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL,    old_button_text_color);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL,    old_button_color);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED,   old_button_focused_color);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED,   old_button_pressed_color);
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL,  old_button_border_color);
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, old_button_border_focused_color);
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, old_button_border_pressed_color);

    GuiSetStyle(DEFAULT, TEXT_SIZE, old_font_size);
}

void draw_played_turns(position_t* pos){
    i32 panel_width = 280;
    i32 panel_height = 540;
    i32 panel_x_pos = SCREEN_BOARD_SIZE + SCREEN_EVAL_WIDTH + (SCREEN_CONTROLS_WIDTH - panel_width) / 2;
    i32 panel_y_pos = 100;
    Rectangle panel_rec = (Rectangle){ panel_x_pos, panel_y_pos, panel_width, panel_height };

    i32 background_color = GuiGetStyle(DEFAULT, BACKGROUND_COLOR);
    i32 scrollbar_width = GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH);
    i32 border_width = GuiGetStyle(DEFAULT, BORDER_WIDTH);
    i32 turns_count = (halfmoves_count + 1) / 2;
    i32 turn_entry_height = 36;
    i32 content_height_turns = turn_entry_height * turns_count;
    i32 content_height_min = panel_height - (border_width-1)*2;
    i32 content_height = maxv(content_height_turns, content_height_min);
    i32 content_width = panel_width - (border_width-1)*2 - (content_height > content_height_min ? scrollbar_width : 0);
    Rectangle content_rec = (Rectangle){ 0, 0, content_width, content_height };
    i32 turn_entry_width = content_rec.width;

    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, ColorToInt(PLAYED_TURNS_PANEL_BACKGROUND));
    GuiSetStyle(DEFAULT, BORDER_WIDTH, 0);
    GuiScrollPanel(panel_rec, NULL, content_rec, &played_turns_panel_scroll, &played_turns_panel_view);
    GuiSetStyle(DEFAULT, BORDER_WIDTH, border_width);
    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, background_color);

    // auto scroll to bottom on new row
    static i32 scroll_delay = 0; // some frame(s) because lowers artifacts
    static i32 last_turns = turns_count;
    i32 default_turns = panel_height / turn_entry_height;
    if(scroll_delay > 0){
        if(--scroll_delay == 0)
            played_turns_panel_scroll.y -= (turns_count - default_turns) * turn_entry_height;
    }
    if(last_turns < turns_count && turns_count > default_turns){
        scroll_delay = 1;
    }
    last_turns = turns_count;

    Rectangle panel_view = played_turns_panel_view;
    Vector2 panel_scroll = played_turns_panel_scroll;

    bool lock_gui = !CheckCollisionPointRec(GetMousePosition(), panel_rec); // mouse is on panel
    if(lock_gui) GuiLock();

    BeginScissorMode(panel_view.x, panel_view.y, panel_view.width, panel_view.height);
        DrawRectangle(panel_rec.x + panel_scroll.x, panel_rec.y + panel_scroll.y, content_rec.width, content_rec.height, PLAYED_TURNS_PANEL_BACKGROUND);
        for(i32 i = 0; i < halfmoves_count; i+=2){
            draw_played_turn_entry(pos, panel_rec.x + panel_scroll.x, panel_rec.y + panel_scroll.y + turn_entry_height * i/2, turn_entry_width, turn_entry_height, i, true);
        }
    EndScissorMode();

    if(lock_gui) GuiUnlock();
}

void draw_controls(position_t* pos){
    i32 buttons_scale = 2;
    i32 buttons_size = 48;
    i32 buttons_x_advance = 80;
    i32 all_buttons_width = buttons_x_advance*3 + buttons_size;
    i32 buttons_x_pos  = SCREEN_BOARD_SIZE + SCREEN_EVAL_WIDTH + (SCREEN_CONTROLS_WIDTH - all_buttons_width) / 2;
    i32 buttons_y_bottom_offset = 100;

    GuiSetIconScale(buttons_scale);
    if(GuiIconButtonActivatable((Rectangle){ buttons_x_pos, SCREEN_BOARD_SIZE - buttons_y_bottom_offset, buttons_size, buttons_size }, ICON_PLAYER_PREVIOUS, true) && game_state == GAME){
        load_first_halfmove(pos);
    }
    if(GuiIconButtonActivatable((Rectangle){ buttons_x_pos + buttons_x_advance, SCREEN_BOARD_SIZE - buttons_y_bottom_offset, buttons_size, buttons_size }, ICON_UNDO, true) && game_state == GAME){
        load_previous_halfmove(pos);
    }
    if(GuiIconButtonActivatable((Rectangle){ buttons_x_pos + buttons_x_advance*2, SCREEN_BOARD_SIZE - buttons_y_bottom_offset, buttons_size, buttons_size }, ICON_REDO, true) && game_state == GAME){
        load_next_halfmove(pos);
    }
    if(GuiIconButtonActivatable((Rectangle){ buttons_x_pos + buttons_x_advance*3, SCREEN_BOARD_SIZE - buttons_y_bottom_offset, buttons_size, buttons_size }, ICON_PLAYER_NEXT, true) && game_state == GAME){
        load_last_halfmove(pos);
    }
}
void draw_menu(position_t* pos){
    DrawRectangle(SCREEN_BOARD_SIZE, 0, SCREEN_MENU_WIDTH, SCREEN_HEIGHT, MENU_BACKGROUND);

    draw_eval();
    draw_played_turns(pos);
    draw_controls(pos);
}


void draw_init(){
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");

    InitAudioDevice();

    SetTargetFPS(60);

    load_assets();

    board_texture = LoadRenderTexture(SCREEN_BOARD_SIZE, SCREEN_BOARD_SIZE);
    menu_texture  = LoadRenderTexture(SCREEN_MENU_WIDTH, SCREEN_BOARD_SIZE);

    if(board_texture.id == 0 || menu_texture.id == 0) {
        TraceLog(LOG_FATAL, "Failed to create render texture(s)");
        return;
    }

    draw_board_to_texture();
    menu_init();
}

void clean_draw(){
    for(i32 i = 0; i < CCOLOR_COUNT; i++){
        for(i32 j = PAWN; j < PIECE_MAX; j++){
            UnloadTexture(piece_textures[i][j]);
        }
    }

    UnloadRenderTexture(board_texture);

    for(i32 i = 0; i < SOUND_COUNT; i++){
        UnloadSound(sounds[i]);
    }

    CloseAudioDevice();

    CloseWindow();
}

bool can_move(position_t* pos, i32 new_index){
    return get_bit(selected_turns, new_index) && selected_black == pos->blacks_turn;
}

bool check_enter_promotion(position_t* pos, i32 new_index){
    if(selected_piece == PAWN && ((pos->blacks_turn && new_index <= 7) || (!pos->blacks_turn && new_index >= 56))){
        in_promotion = true;
        promoted_to = new_index;
        for(i32 i = 0; i < 4; i++){
            promotion_indexes[i] = promoted_to + (pos->blacks_turn ? 8 : -8) * i;
        }
        return true;
    }
    return false;
}

void start_arrow(i32 index){
    selected_arrow = index;
    doing_arrow = true;
}
void end_arrow(i32 index){
    // find if arrow exists
    for(i32 i = 0; i < arrows_count; i++){
        if(arrows[i].from == selected_arrow && arrows[i].to == index){
            arrows[i].from = arrows[arrows_count - 1].from;
            arrows[i].to   = arrows[arrows_count - 1].to;
            arrows_count--;
            return;
        }
    }
    arrows[arrows_count].from = selected_arrow;
    arrows[arrows_count].to   = index;
    arrows_count++;
    doing_arrow = false;
}
void clear_arrows(){
    arrows_count = 0;
    doing_arrow = false;
}

void end_turn(position_t* pos){
    if(is_checkmate(pos)){
        game_state = CHECKMATE;
        // PlaySound(sounds[SOUND_NOTIFY]);
        return;
    }else if(is_draw(pos)){
        game_state = DRAW;
        // PlaySound(sounds[SOUND_NOTIFY]);
        return;
    }
}

// pretty rudimentary special move checking
bool move_is_double_pawn_move(piece_t piece, i32 from, i32 to){
    if(piece != PAWN){
        return false;
    }
    i32 diff = abs(to - from);
    return diff == 16;
}
bool move_is_promotion(position_t* pos, piece_t piece, i32 from, i32 to){
    if(piece != PAWN){
        return false;
    }
    u64 mask_from = 1ull << from;
    u64 mask_to   = 1ull << to;
    return ( pos->blacks_turn && (RANK_2 & mask_from) && (RANK_1 & mask_to))
         | (!pos->blacks_turn && (RANK_7 & mask_from) && (RANK_8 & mask_to));
}
bool move_is_enpassant(u64 board, piece_t piece, i32 from, i32 to){
    if(piece != PAWN){
        return false;
    }
    i32 diff = abs(to - from);
    if(diff != 7 && diff != 9){
        return false;
    }
    return !index_occupied(board, to);
}
bool move_is_castling(piece_t piece, i32 from, i32 to){
    if(piece != KING){
        return false;
    }
    i32 diff = abs(to - from);
    return diff == 3 || diff == 2;
}

void play_move(position_t* pos, i32 new_index, i32 arg){
    select_for_turn_highlight(selected_index, new_index);

    bool capture = index_occupied(pos->all_pieces, new_index);
    bool enpassant = move_is_enpassant(pos->all_pieces, selected_piece, selected_index, new_index);

    move_t move = 0;
    move_set_color(move, pos->blacks_turn);
    move_set_type(move, capture ? CAPTURE : MOVE);
    move_set_piece(move, selected_piece);
    move_set_from(move, selected_index);
    move_set_to(move, new_index);

    if(capture){
        move_set_spec2(move, piece_at(pos, new_index));
    }else{
        move_set_spec2(move, 0x7);
    }

    if(move_is_castling(selected_piece, selected_index, new_index)){
        move_set_type(move, CASTLING);
        i32 dir = sign(new_index - selected_index);
        i32 rook_from = new_index + (dir < 0 ? dir * 2: dir);
        i32 rook_to = new_index - dir;
        move_set_spec1(move, rook_from);
        move_set_spec2(move, rook_to);
    }

    if(selected_piece == PAWN){
        if(move_is_promotion(pos, selected_piece, selected_index, new_index)){
            move_set_type(move, PROMOTION);
            move_set_spec1(move, arg);
        }else if(enpassant){
            move_set_type(move, ENPASSANT);
            move_set_spec1(move, new_index + 8 * sign(selected_index - new_index));
        }else if(move_is_double_pawn_move(selected_piece, selected_index, new_index)){
            move_set_type(move, DOUBLE_PUSH);
            move_set_spec1(move, (selected_index + ((new_index - selected_index) >> 1)));
        }else{
            move_set_type(move, capture ? CAPTURE : PUSH);
        }
    }

    // before doing the move
    save_halfmove(pos, move);

    do_move(pos, move);

    end_turn(pos);

    deselect_piece();

    play_move_sound(pos, move);
}

void setup_game(position_t* pos){
    game_state = GAME;
    arrows_count = 0;
    halfmoves_count = 0;
    halfmoves_at = 0;
    select_for_turn_highlight(NUL_INDEX, NUL_INDEX);
    deselect_piece();
    start_position = *pos;
    chess_setup(pos);
}
void restart_game(position_t* pos){
    reset_position(pos);
    setup_game(pos);
}

void poll_events(position_t* pos){
    mouse_x = GetMouseX();
    mouse_y = GetMouseY();
    mouse_left = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    mouse_right = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

    mouse_over_board = mouse_is_over_board();
    hover_index = position_to_index(mouse_x, mouse_y);

    if(game_state != GAME){
        if(IsKeyPressed(KEY_ENTER)){
            PlaySound(sounds[SOUND_GAME_START]);
            restart_game(pos);
        }
        return;
    }
    if(IsKeyPressed(KEY_R)){
        PlaySound(sounds[SOUND_GAME_START]);
        restart_game(pos);
        return;
    }

    i32 new_index = hover_index;

    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        if(mouse_over_board){
            //if(selected_index == NUL_INDEX){
                start_arrow(new_index);
                dragged_arrow.from = new_index;
            //}
            in_promotion = false;
            deselect_piece();
        }
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        if(mouse_over_board && doing_arrow){
            dragged_arrow.to = new_index;
        }
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)){
        if(mouse_over_board && doing_arrow){
            end_arrow(new_index);
        }
        doing_arrow = false;
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(mouse_over_board){
            clear_arrows();
            if(in_promotion){
                for(i32 i = 0; i < 4; i++){
                    if(hover_index == promotion_indexes[i]){
                        play_move(pos, promoted_to, promotion_pieces[i]);
                        //promote(blacks_turn, promoted_to, promotion_pieces[i]);
                        break;
                    }
                }
                in_promotion = false;
                deselect_piece();
            }else if(is_piece_selected() && new_index != selected_index && can_move(pos, new_index)){
                if(!check_enter_promotion(pos, new_index)){
                    play_move(pos, new_index, 0);
                }
            }else{
                select_piece(pos, new_index);
            }
        }
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        if(mouse_over_board && is_piece_dragging() && new_index != selected_index && can_move(pos, new_index)){
            if(!check_enter_promotion(pos, new_index)){
                play_move(pos, new_index, 0);
            }
        }
        dragged_piece = EMPTY_PIECE;
    }

    if(IsKeyPressed(KEY_DOWN)){
        load_first_halfmove(pos);
    }
    if(IsKeyPressed(KEY_LEFT)){
        load_previous_halfmove(pos);
    }
    if(IsKeyPressed(KEY_RIGHT)){
        load_next_halfmove(pos);
    }
    if(IsKeyPressed(KEY_UP)){
        load_last_halfmove(pos);
    }

    if(IsKeyPressed(KEY_M)){
        if(GetMasterVolume() == 0.0f) SetMasterVolume(1.0f);
        else                          SetMasterVolume(0.0f);
    }

    if(IsKeyPressed(KEY_P)){
        if(IsKeyDown(KEY_LEFT_SHIFT)){ // load instead if shift held shift
            char* clipboard = (char*)GetClipboardText();
            printf("Clipboard: <%s>\n", clipboard);
            *pos = parse_pgn(clipboard);
            setup_game(pos);
            PlaySound(sounds[SOUND_GAME_START]);
        }else{
            char* pgn = moves_to_pgn(pos, halfmoves, halfmoves_count);
            SetClipboardText(pgn);
            PlaySound(sounds[SOUND_NOTIFY]);
            printf("PGN of current position: %s\n", pgn);
        }
    }

    if(IsKeyPressed(KEY_F)){
        if(IsKeyDown(KEY_LEFT_SHIFT)){ // load instead if shift held shift
            char* clipboard = (char*)GetClipboardText();
            printf("Clipboard: <%s>\n", clipboard);
            *pos = parse_fen(clipboard);
            setup_game(pos);
            PlaySound(sounds[SOUND_GAME_START]);
        }else{
            char* fen = position_to_fen(pos);
            SetClipboardText(fen);
            PlaySound(sounds[SOUND_NOTIFY]);
            printf("FEN of current position: %s\n", fen);
        }
    }

    if(IsKeyPressed(KEY_T)){
        printf("Current material evaluation: %d\n", evaluate_relative(pos));
        i32 depth = 6; // https://en.wikipedia.org/wiki/Shannon_number
        //printf("Engine evaluation: %llu at %d depth\n", get_score(pos, depth), depth);

        printf("Checking moves at %d depth\n", depth);
        bool success = check_moves_at_depth(pos, depth);
        printf(success ? "Success\n" : "Failure\n");
    }

    if(IsKeyPressed(KEY_SPACE)){
        printf("Current material evaluation: %d\n", evaluate_relative(pos));
        i32 depth = 6;

        printf("Checking moves at %d depth\n", depth);
        i32 score;
        move_t move = find_best_move(pos, depth, &score);
        printf("Best move with score: %d is: ", score);
        evaluation_bar = score;

        print_move(move);
        printf("\n");
    }
}

void draw_position(position_t* pos){
    BeginDrawing();

        ClearBackground(RAYWHITE);

        draw_board();
        draw_menu(pos);

        draw_pieces(pos);
        draw_check(pos);
        draw_selected(pos);
        draw_arrows();
        draw_promotion(pos);

        if(game_state == DRAW || game_state == CHECKMATE){
            draw_end_screen(pos);
        }

    EndDrawing();
}

void chess_run(){
    position_t position = { 0 };
    
    chess_reset(&position);

    draw_init();

    restart_game(&position);

    while (!WindowShouldClose()){
        poll_events(&position);

        draw_position(&position);
    }

    clean_draw();
}