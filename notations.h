#pragma once

#include "chess.h"

#include <stdio.h>
#include <ctype.h>

char fen_piece_codes[CCOLOR_COUNT][PIECE_MAX] = { { ' ', 'P', 'N', 'B', 'R', 'Q', 'K'}, {' ', 'p', 'n', 'b', 'r', 'q', 'k'} };

piece_t parse_piece_code(char code, bool *black){
    if(code == 'P'){ if(black) *black = false; return PAWN; }
    if(code == 'N'){ if(black) *black = false; return KNIGHT; }
    if(code == 'B'){ if(black) *black = false; return BISHOP; }
    if(code == 'R'){ if(black) *black = false; return ROOK; }
    if(code == 'Q'){ if(black) *black = false; return QUEEN; }
    if(code == 'K'){ if(black) *black = false; return KING; }

    if(code == 'p'){ if(black) *black = true; return PAWN; }
    if(code == 'n'){ if(black) *black = true; return KNIGHT; }
    if(code == 'b'){ if(black) *black = true; return BISHOP; }
    if(code == 'r'){ if(black) *black = true; return ROOK; }
    if(code == 'q'){ if(black) *black = true; return QUEEN; }
    if(code == 'k'){ if(black) *black = true; return KING; }

    return EMPTY_PIECE;
}

i32 write_unsigned(char* buf, u32 num){
    i32 written = 0;
    do{
        buf[written++] = num % 10 + '0';
        num /= 10;
    }while(num > 0);

    for(i32 i = 0; i < written / 2; i++){
        char tmp = buf[i];
        i32 i2 = written - 1 - i;
        buf[i] = buf[i2];
        buf[i2] = tmp;
    }

    return written;
}
i32 read_unsigned(char* buf, u32* num){
    i32 read = 0;
    *num = 0;

    char c;
    while(isdigit(c = buf[read++])){
        *num *= 10;
        *num += c - '0';
    }

    return read;
}

i32 measure_whitespace(char* str){
    i32 i = 0;
    while(isspace(str[i])) i++;
    return i;
}
i32 measure_nonwhitespace(char* str){
    i32 i = 0;
    while(isgraph(str[i])) i++;
    return i;
}

#define FEN_MAX 100
#define FEN_BUFFERS 4
char* position_to_fen(position_t* pos){
    static char buffers[FEN_BUFFERS][FEN_MAX] = { 0 };
    static i32 buffer_index = 0;
    char* fen_buffer = buffers[buffer_index++];
    if(buffer_index >= 4) buffer_index = 0;
    i32 written = 0;

    // Piece placement
    for(i32 rank = 7; rank >= 0; rank--) {
        i32 empties = 0;
        for(i32 file = 0; file < 8; file++) {
            i32 index = rank * 8 + file;
            bool black;
            piece_t piece = piece_at_all(pos, index, &black);
            char code = fen_piece_codes[black][piece];
            if(code != ' '){
                if(empties != 0){
                    fen_buffer[written++] = '0' + empties;
                    empties = 0;
                }
                fen_buffer[written++] = code;
            }else{
                empties++;
            }
        }
        if(empties != 0)
            fen_buffer[written++] = '0' + empties;
        if(rank > 0)
            fen_buffer[written++] = '/';
    }

    // Side to move
    fen_buffer[written++] = ' ';
    fen_buffer[written++] = pos->blacks_turn ? 'b' : 'w';

    // Castling ability
    fen_buffer[written++] = ' ';
    if(pos->lost_castling_rights[CWHITE][CASTLE_OO] && pos->lost_castling_rights[CWHITE][CASTLE_OOO] &&
       pos->lost_castling_rights[CBLACK][CASTLE_OO] && pos->lost_castling_rights[CBLACK][CASTLE_OOO]){
        fen_buffer[written++] = '-';
    }else{
        if(!pos->lost_castling_rights[CWHITE][CASTLE_OO]){
            fen_buffer[written++] = 'K';
        }
        if(!pos->lost_castling_rights[CWHITE][CASTLE_OOO]){
            fen_buffer[written++] = 'Q';
        }
        if(!pos->lost_castling_rights[CBLACK][CASTLE_OO]){
            fen_buffer[written++] = 'k';
        }
        if(!pos->lost_castling_rights[CBLACK][CASTLE_OOO]){
            fen_buffer[written++] = 'q';
        }
    }

    // En passant target square
    fen_buffer[written++] = ' ';
    if(pos->enpassantable){
        i32 index = mask_to_index(pos->enpassantable);
        i32 rank = index / 8;
        i32 file = index % 8;
        fen_buffer[written++] = 'a' + file;
        fen_buffer[written++] = '1' + rank;
    }else{
        fen_buffer[written++] = '-';
    }

    // Halfmove clock
    fen_buffer[written++] = ' ';
    written += write_unsigned(fen_buffer + written, pos->halfmove_clock);

    // Fullmove counter
    fen_buffer[written++] = ' ';
    written += write_unsigned(fen_buffer + written, pos->turns_passed / 2 + 1);


    fen_buffer[written] = '\0';
    return fen_buffer;
}

i32 index_reverse_file(i32 index){
    i32 rank = index / 8;
    i32 file = index % 8;
    i32 new_index = rank * 8 + (7 - file);
    return new_index;
}
position_t parse_fen(char* fen){
    position_t pos = (position_t){ 0 };
    i32 written = 0;

    // Piece placement
    written += measure_whitespace(fen + written);
    i32 square_index = 63;
    for(; written < FEN_MAX; written++){
        char code = fen[written];
        if(isdigit(code)){
            square_index -= code - '0';
            continue;
        }
        if(code == '/'){
            continue;
        }
        if(code == ' ' || code == '\0'){
            break;
        }
        bool black = false;
        piece_t piece = parse_piece_code(code, &black);
        put_piece(&pos, black, piece, index_reverse_file(square_index--));
    }

    // Side to move
    written += measure_whitespace(fen + written);
    pos.blacks_turn = fen[written++] == 'b';

    // Castling ability
    written += measure_whitespace(fen + written);
    if(fen[written++] != '-'){
        if(fen[written] != 'K'){
            written++;
            pos.lost_castling_rights[CWHITE][CASTLE_OO] = true;
        }
        if(fen[written] != 'Q'){
            written++;
            pos.lost_castling_rights[CWHITE][CASTLE_OOO] = true;
        }
        if(fen[written] != 'k'){
            written++;
            pos.lost_castling_rights[CBLACK][CASTLE_OO] = true;
        }
        if(fen[written] != 'q'){
            written++;
            pos.lost_castling_rights[CBLACK][CASTLE_OOO] = true;
        }
    }

    // En passant target square
    written += measure_whitespace(fen + written);
    i32 file = fen[written++] - 'a';
    i32 rank = fen[written++] - '1';
    pos.enpassantable = 1ull << (rank * 8 + file);

    // Halfmove clock
    written += measure_whitespace(fen + written);
    written += read_unsigned(fen + written, (u32*)&pos.halfmove_clock);

    // Fullmove counter
    written += measure_whitespace(fen + written);
    written += read_unsigned(fen + written, (u32*)&pos.turns_passed);

    return pos;
};


i32 append_char(char* buf, char c){
    if(c == '\0') return 0;
    buf[0] = c;
    return 1;
}
i32 append_string(char* buf, const char* str){
    int i = 0;
    while(str[i]){
        buf[i] = str[i];
        i++;
    }
    return i;
}

const char* square_codes[64] = { "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8" };
char pgn_piece_codes[PIECE_MAX] = { '\0', '\0', 'N', 'B', 'R', 'Q', 'K' };
i32 write_move_pgn(char* buf, position_t* pos, move_t move){
    bool black = move_get_color(move);
    piece_t piece = move_get_piece(move);
    move_type_e type = move_get_type(move);
    i32 from = move_get_from(move);
    i32 to = move_get_to(move);

    char piece_char = pgn_piece_codes[piece];

    char out_from_string[4]  = { 0 };
    char out_to_string[4]    = { 0 };
    char promotion_string[4] = { 0 };
    char capture_char        = '\0';
    char check_char          = '\0';

    bool capture = type == CAPTURE || type == ENPASSANT;
    if(type == PROMOTION){
        piece_t promoted = move_get_spec1(move);
        piece_t captured = move_get_spec2(move); // maybe capture
        capture = captured != 0;
        sprintf(promotion_string, "=%c", pgn_piece_codes[promoted]);
    }
    if(capture) capture_char = 'x';

    sprintf(out_to_string, "%s", square_codes[to]);

    // Check if in check or mate or draw after playing this move
    position_t pos_tmp = *pos;
    do_move_lazy(&pos_tmp, move);
    if(in_check(&pos_tmp))                     check_char = '+';
    if(is_checkmate(&pos_tmp) || is_draw(pos)) check_char = '#';

    // Check if need to write from square
    bool write_rank = false;
    bool write_file = capture && piece == PAWN; // write on pawn capture
    i32 rank = from / 8;
    i32 file = from % 8;
    u64 pieces_from_mask = pos->pieces[piece] & pos->colors[black];
    u64 possible_from_mask = piece_targets(pos, !black, to, piece, false) & pieces_from_mask;
    if(bit_count(possible_from_mask) > 1 && type != CASTLING){ // possibly other pieces
        i32 other_piece_count = 0;
        i32 other_piece_indexes[8];

        // check if other piece can legally move there
        u64 mask = possible_from_mask & ~(1ull << from); // exclude moved pieced
        move_t moves[MAX_MOVES];
        while(mask){
            i32 other_index = extract_piece(&mask);
            i32 count = fill_piece_legal_moves(pos, other_index, piece, moves, 0);
            for(i32 i = 0; i < count; i++){ // check if can move to our square
                if((i32)move_get_to(moves[i]) == to){
                    other_piece_indexes[other_piece_count++] = other_index;
                    break;
                }
            }
        }

        // check if need to write file, rank or both
        for(i32 i = 0; i < other_piece_count; i++){
            i32 other_rank = other_piece_indexes[i] / 8;
            i32 other_file = other_piece_indexes[i] % 8;
            if(other_rank == rank) write_file = true;
            if(other_file == file) write_rank = true;
        }
    }
    i32 out_from_string_count = 0;
    if(write_file) out_from_string[out_from_string_count++] = 'a' + file;
    if(write_rank) out_from_string[out_from_string_count++] = '1' + rank;

    i32 written = 0;
    if(type == CASTLING){
        bool queenside_castling = to < from;
        const char* castling_string = queenside_castling ? "O-O-O" : "O-O";
        // written = sprintf(buf, "%s%c", castling_string, check_char);
        written += append_string(buf + written, castling_string);
        written += append_char  (buf + written, check_char);
    }else{
        // written = sprintf(buf, "%c%s%c%s%s%c", piece_char, out_from_string, capture_char, out_to_string, promotion_string, check_char);
        written += append_char  (buf + written, piece_char);
        written += append_string(buf + written, out_from_string);
        written += append_char  (buf + written, capture_char);
        written += append_string(buf + written, out_to_string);
        written += append_string(buf + written, promotion_string);
        written += append_char  (buf + written, check_char);
    }
    buf[written] = '\0';
    return written;
}

#define PGN_MAX 40000
#define PGN_BUFFERS 4
char* moves_to_pgn(position_t* pos, move_t* halfmoves, i32 count){
    static char buffers[PGN_BUFFERS][PGN_MAX] = { 0 };
    static i32 buffer_index = 0;
    char* pgn_buffer = buffers[buffer_index++];
    if(buffer_index >= 4) buffer_index = 0;

    i32 written = 0;
    for(i32 i = 0; i < count; i++){
        if(i % 2 == 0) written += sprintf(pgn_buffer + written, "%d. ", i / 2 + 1);
        written += write_move_pgn(pgn_buffer + written, pos, halfmoves[i]);
        written += sprintf(pgn_buffer + written, " ");
    }

    return pgn_buffer;
}

bool is_file_char(char c){
    return c >= 'a' && c <= 'h';
}
bool is_rank_char(char c){
    return c >= '1' && c <= '8';
}
piece_t pgn_to_piece(char pgn){
    switch(pgn){
    case 'N': return KNIGHT;
    case 'B': return BISHOP;
    case 'R': return ROOK;
    case 'Q': return QUEEN;
    case 'K': return KING;
    case 'O': return KING;
    default:  return PAWN;
    }
}
move_t pgn_build_move(char* pgn, i32 count, position_t* pos, bool black){
    if(count <= 0) return 0;

    i32 readen = 0;

    i32 from = 0;
    i32 to = 0;
    move_type_e move_type = MOVE;
    piece_t piece = pgn_to_piece(pgn[readen]);
    i32 spec1 = 0;
    i32 spec2 = 0;

    if(pgn[readen + 0] == 'O' && pgn[readen + 1] == '-' && pgn[readen + 2] == 'O'){
        bool queenside = pgn[readen + 3] == '-' && pgn[readen + 4] == 'O';
        readen += queenside ? 5 : 3;
        from = black ? 60 : 4;
        i32 advance = queenside ? -2 : 2;
        to = from + advance;
        spec1 = to + advance;
        spec2 = (from + to) >> 1;

        return create_move(black, from, to, CASTLING, piece, spec1, spec2);
    }

    // first known square info
    i32 square1_file = -1;
    i32 square1_rank = -1;
    if(is_file_char(pgn[readen])) square1_file = pgn[readen++] - 'a';
    if(is_rank_char(pgn[readen])) square1_rank = pgn[readen++] - '1';

    // skip capture thing
    // bool capture = false;
    if(pgn[readen] == 'x'){
        // capture = true;
        move_type = CAPTURE;
        readen++;
    }

    // second known square info
    i32 square2_file = -1;
    i32 square2_rank = -1;
    if(is_file_char(pgn[readen])) square2_file = pgn[readen++] - 'a';
    if(is_rank_char(pgn[readen])) square2_rank = pgn[readen++] - '1';

    // now we know our from/to is in these squares
    u64 from_mask = ~0;
    u64 to_mask = ~0;
    if(square2_file != -1){
        to_mask &= file_to_mask[square2_file];
        if(square1_file != -1)
            from_mask &= file_to_mask[square1_file];
    }else{
        if(square1_file != -1)
            to_mask &= file_to_mask[square1_file];
    }
    if(square2_rank != -1){
        to_mask &= rank_to_mask[square2_rank];
        if(square1_rank != -1)
            from_mask &= rank_to_mask[square1_rank];
    }else{
        if(square1_rank != -1)
            to_mask &= rank_to_mask[square1_rank];
    }

    // must be known by now
    assert(bit_count(to_mask) == 1);
    to = mask_to_index(to_mask);

    // possible pieces to move
    u64 candidates = pos->pieces[piece] & pos->colors[black] & from_mask;
    assert(candidates > 0); // must be some
    // check if move can be made
    move_t moves[MAX_MOVES];
    while(candidates){
        i32 candidate_index = extract_piece(&candidates);
        i32 count = fill_piece_legal_moves(pos, candidate_index, piece, moves, 0);
        for(i32 i = 0; i < count; i++){ // check if can move to our square
            if((i32)move_get_to(moves[i]) == to){
                move_type = move_get_type(moves[i]);
                from = candidate_index;
                break;
            }
        }
    }

    if(pgn[readen] == '='){
        move_type = PROMOTION;
        readen++;
        spec1 = pgn_to_piece(pgn[readen]);
    }

    // ignore '+' or '#' at the end
    if(pgn[readen] == '+') readen++;
    if(pgn[readen] == '#') readen++;

    return create_move(black, from, to, move_type, piece, spec1, spec2);
}
i32 measure_next_text(char* pgn, i32 *text_length){
    i32 readen = 0;
    readen += measure_whitespace(pgn);
    i32 post_whitespace = readen;
    readen += measure_nonwhitespace(pgn);
    if(text_length) *text_length = readen - post_whitespace;
    return readen;
}
i32 parse_pgn_play_next_move(char* pgn, position_t* pos){ // dont really validate it
    i32 readen = 0;

    readen += measure_next_text(pgn + readen, 0); // skip number with dot

    i32 white_length, black_length, white_from, black_from;
    readen += measure_next_text(pgn + readen, &white_length);
    white_from = readen - white_length;
    readen += measure_next_text(pgn + readen, &black_length);
    black_from = readen - black_length;

    if(white_length != 0){
         do_move(pos, pgn_build_move(pgn + white_from, white_length, pos, false));
        if(black_length != 0)
            do_move(pos, pgn_build_move(pgn + black_from, black_length, pos, true));
    }

    return readen;
}
position_t parse_pgn(char* pgn){ // dont really validate it
    position_t pos = { 0 };

    i32 readen = 0;
    while(readen += parse_pgn_play_next_move(pgn, &pos))
        ;

    return pos;
}