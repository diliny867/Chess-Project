#pragma once

#include "chess.h"

#include <time.h>


#define MATE_VALUE   1000000
#define INF_VALUE    2000000

// Values from:
// https://chessprogramming.org/PeSTO%27s_Evaluation_Function
// https://www.talkchess.com/forum3/viewtopic.php?f=2&t=68311&start=19

// indexed by piece_e (PAWN == 1), index 0 unused
i32 piece_values_mg[PIECE_MAX] = { 0, 82, 337, 365, 477, 1025,  12000};
i32 piece_values_eg[PIECE_MAX] = { 0, 94, 281, 297, 512,  936,  12000};

i32 pawn_increase_mg[64] = {
      0,   0,   0,   0,   0,   0,  0,   0,
     98, 134,  61,  95,  68, 126, 34, -11,
     -6,   7,  26,  31,  65,  56, 25, -20,
    -14,  13,   6,  21,  23,  12, 17, -23,
    -27,  -2,  -5,  12,  17,   6, 10, -25,
    -26,  -4,  -4, -10,   3,   3, 33, -12,
    -35,  -1, -20, -23, -15,  24, 38, -22,
      0,   0,   0,   0,   0,   0,  0,   0,
};
i32 pawn_increase_eg[64] = {
      0,   0,   0,   0,   0,   0,   0,   0,
    178, 173, 158, 134, 147, 132, 165, 187,
     94, 100,  85,  67,  56,  53,  82,  84,
     32,  24,  13,   5,  -2,   4,  17,  17,
     13,   9,  -3,  -7,  -7,  -8,   3,  -1,
      4,   7,  -6,   1,   0,  -5,  -1,  -8,
     13,   8,   8,  10,  13,   0,   2,  -7,
      0,   0,   0,   0,   0,   0,   0,   0,
};

i32 knight_increase_mg[64] = {
    -167, -89, -34, -49,  61, -97, -15, -107,
     -73, -41,  72,  36,  23,  62,   7,  -17,
     -47,  60,  37,  65,  84, 129,  73,   44,
      -9,  17,  19,  53,  37,  69,  18,   22,
     -13,   4,  16,  13,  28,  19,  21,   -8,
     -23,  -9,  12,  10,  19,  17,  25,  -16,
     -29, -53, -12,  -3,  -1,  18, -14,  -19,
    -105, -21, -58, -33, -17, -28, -19,  -23,
};
i32 knight_increase_eg[64] = {
    -58, -38, -13, -28, -31, -27, -63, -99,
    -25,  -8, -25,  -2,  -9, -25, -24, -52,
    -24, -20,  10,   9,  -1,  -9, -19, -41,
    -17,   3,  22,  22,  22,  11,   8, -18,
    -18,  -6,  16,  25,  16,  17,   4, -18,
    -23,  -3,  -1,  15,  10,  -3, -20, -22,
    -42, -20, -10,  -5,  -2, -20, -23, -44,
    -29, -51, -23, -15, -22, -18, -50, -64,
};

i32 bishop_increase_mg[64] = {
    -29,   4, -82, -37, -25, -42,   7,  -8,
    -26,  16, -18, -13,  30,  59,  18, -47,
    -16,  37,  43,  40,  35,  50,  37,  -2,
     -4,   5,  19,  50,  37,  37,   7,  -2,
     -6,  13,  13,  26,  34,  12,  10,   4,
      0,  15,  15,  15,  14,  27,  18,  10,
      4,  15,  16,   0,   7,  21,  33,   1,
    -33,  -3, -14, -21, -13, -12, -39, -21,
};
i32 bishop_increase_eg[64] = {
    -14, -21, -11,  -8, -7,  -9, -17, -24,
     -8,  -4,   7, -12, -3, -13,  -4, -14,
      2,  -8,   0,  -1, -2,   6,   0,   4,
     -3,   9,  12,   9, 14,  10,   3,   2,
     -6,   3,  13,  19,  7,  10,  -3,  -9,
    -12,  -3,   8,  10, 13,   3,  -7, -15,
    -14, -18,  -7,  -1,  4,  -9, -15, -27,
    -23,  -9, -23,  -5, -9, -16,  -5, -17,
};

i32 rook_increase_mg[64] = {
     32,  42,  32,  51, 63,  9,  31,  43,
     27,  32,  58,  62, 80, 67,  26,  44,
     -5,  19,  26,  36, 17, 45,  61,  16,
    -24, -11,   7,  26, 24, 35,  -8, -20,
    -36, -26, -12,  -1,  9, -7,   6, -23,
    -45, -25, -16, -17,  3,  0,  -5, -33,
    -44, -16, -20,  -9, -1, 11,  -6, -71,
    -19, -13,   1,  17, 16,  7, -37, -26,
};
i32 rook_increase_eg[64] = {
    13, 10, 18, 15, 12,  12,   8,   5,
    11, 13, 13, 11, -3,   3,   8,   3,
     7,  7,  7,  5,  4,  -3,  -5,  -3,
     4,  3, 13,  1,  2,   1,  -1,   2,
     3,  5,  8,  4, -5,  -6,  -8, -11,
    -4,  0, -5, -1, -7, -12,  -8, -16,
    -6, -6,  0,  2, -9,  -9, -11,  -3,
    -9,  2,  3, -1, -5, -13,   4, -20,
};

i32 queen_increase_mg[64] = {
    -28,   0,  29,  12,  59,  44,  43,  45,
    -24, -39,  -5,   1, -16,  57,  28,  54,
    -13, -17,   7,   8,  29,  56,  47,  57,
    -27, -27, -16, -16,  -1,  17,  -2,   1,
     -9, -26,  -9, -10,  -2,  -4,   3,  -3,
    -14,   2, -11,  -2,  -5,   2,  14,   5,
    -35,  -8,  11,   2,   8,  15,  -3,   1,
     -1, -18,  -9,  10, -15, -25, -31, -50,
};
i32 queen_increase_eg[64] = {
     -9,  22,  22,  27,  27,  19,  10,  20,
    -17,  20,  32,  41,  58,  25,  30,   0,
    -20,   6,   9,  49,  47,  35,  19,   9,
      3,  22,  24,  45,  57,  40,  57,  36,
    -18,  28,  19,  47,  31,  34,  39,  23,
    -16, -27,  15,   6,   9,  17,  10,   5,
    -22, -23, -30, -16, -16, -23, -36, -32,
    -33, -28, -22, -43,  -5, -32, -20, -41,
};

i32 king_increase_mg[64] = {
    -65,  23,  16, -15, -56, -34,   2,  13,
     29,  -1, -20,  -7,  -8,  -4, -38, -29,
     -9,  24,   2, -16, -20,   6,  22, -22,
    -17, -20, -12, -27, -30, -25, -14, -36,
    -49,  -1, -27, -39, -46, -44, -33, -51,
    -14, -14, -22, -46, -44, -30, -15, -27,
      1,   7,  -8, -64, -43, -16,   9,   8,
    -15,  36,  12, -54,   8, -28,  24,  14,
};
i32 king_increase_eg[64] = {
    -74, -35, -18, -18, -11,  15,   4, -17,
    -12,  17,  14,  17,  17,  38,  23,  11,
     10,  17,  23,  15,  20,  45,  44,  13,
     -8,  22,  24,  27,  26,  33,  26,   3,
    -18,  -4,  21,  24,  27,  23,   9, -11,
    -19,  -3,  11,  21,  23,  16,   7,  -9,
    -27, -11,   4,  13,  14,   4,  -5, -17,
    -53, -34, -21, -11, -28, -14, -24, -43
};

i32 piece_values_table_mg[CCOLOR_COUNT][PIECE_MAX][64];
i32 piece_values_table_eg[CCOLOR_COUNT][PIECE_MAX][64];

i32* pesto_tables_mg[PIECE_MAX] = {
    0, pawn_increase_mg, knight_increase_mg, bishop_increase_mg, rook_increase_mg, queen_increase_mg, king_increase_mg
};
i32* pesto_tables_eg[PIECE_MAX] = {
    0, pawn_increase_eg, knight_increase_eg, bishop_increase_eg, rook_increase_eg, queen_increase_eg, king_increase_eg
};
i32 gamephase_increase[PIECE_MAX] = { 0, 0, 1, 1, 2, 4, 0 };

static force_inline whites_as_blacks_index(i32 index){
    return index ^ 56;
}

void init_tables(){
    for (piece_t p = PIECE_FROM; p < PIECE_MAX; p++) {
        for (i32 i = 0; i < 64; i++) {
            piece_values_table_mg[CWHITE][p][i] = piece_values_mg[p] + pesto_tables_mg[p][i];
            piece_values_table_mg[CBLACK][p][i] = piece_values_mg[p] + pesto_tables_mg[p][whites_as_blacks_index(i)];
            piece_values_table_eg[CWHITE][p][i] = piece_values_eg[p] + pesto_tables_eg[p][i];
            piece_values_table_eg[CBLACK][p][i] = piece_values_eg[p] + pesto_tables_eg[p][whites_as_blacks_index(i)];
        }
    }
}
void init_engine(){
    init_tables();
}

// material from the point of view of the side to move
static force_inline i32 evaluate_relative(position_t* pos) {
    u64* pieces = pos->pieces;
    u64* colors = pos->colors;
    bool black = pos->blacks_turn;

    i32 mg[CCOLOR_COUNT] = { 0, 0 };
    i32 eg[CCOLOR_COUNT] = { 0, 0 };
    i32 phase = 0;

    for(i32 c = CWHITE; c <= CBLACK; c++){
        for(piece_t p = PIECE_FROM; p < PIECE_MAX; p++){
            u64 mask = pieces[p] & colors[c];
            while(mask){
                i32 index = extract_piece(&mask);
                mg[c] += piece_values_table_mg[c][p][index];
                eg[c] += piece_values_table_mg[c][p][index];
                phase += gamephase_increase[p];
            }
        }
    }

    i32 mg_score = mg[black] - mg[!black];
    i32 eg_score = eg[black] - eg[!black];
    i32 mg_phase = phase;
    if(mg_phase > 24) mg_phase = 24; // in case of early promotion
    i32 eg_phase = 24 - mg_phase;
    return (mg_score * mg_phase + eg_score * eg_phase) / 24;
}

// material from whites point of view
// static force_inline i32 material_evaluate(position_t* pos) {
//     u64* pieces = pos->pieces;
//     u64* colors = pos->colors;
//     i32 value = 0;
//     for(i32 i = PIECE_FROM; i < PIECE_MAX; i++){
//         i32 piece_count = bit_count(pieces[i] & colors[CWHITE]) - bit_count(pieces[i] & colors[CBLACK]);
//         value += piece_values[i] * piece_count;
//     }
//     return value;
// }
// material from the point of view of the side to move
// static inline i32 evaluate_relative(position_t* pos){
//     i32 value = material_evaluate(pos);
//     return pos->blacks_turn ? -value : value;
// }

// captures of valuable pieces by cheap pieces first, queen promotions early, underpromotions last
static i32 move_order_score(move_t move){
    i32 score = 0;
    i32 captured = move_get_spec2(move);
    if(captured) score = piece_values_mg[captured] * 16 - move_get_piece(move) + 10000; // all captures before quiet moves
    if(move_get_type(move) == PROMOTION){
        score += (move_get_spec1(move) == QUEEN) ? 20000 : -5000;
    }
    return score;
}

static inline void score_moves(move_t* moves, i32* scores, i32 count){
    for(i32 i = 0; i < count; i++) {
        scores[i] = move_order_score(moves[i]);
    }
}

// moves the best remaining move to index i and returns it, dont sort the rest after a beta cutoff
static inline move_t pick_move(move_t* moves, i32* scores, i32 i, i32 count){
    i32 best = i;
    for(i32 j = i + 1; j < count; j++){
        if(scores[j] > scores[best]) best = j;
    }
    move_t move = moves[best]; moves[best] = moves[i]; moves[i] = move;
    i32 score = scores[best];  scores[best] = scores[i]; scores[i] = score;
    return move;
}

u64 total_moves = 0;

// plain negamax
i32 nega_max(position_t* pos, i32 depth) {
    if (depth == 0) return evaluate_relative(pos);

    move_t moves[MAX_MOVES];

    i32 score, best = -INF_VALUE;
    i32 moves_count = get_moves(pos, moves, true);
    if(depth == 1){
        total_moves += moves_count;
    }
    if(moves_count == 0){
        return in_check(pos, pos->blacks_turn) ? -MATE_VALUE - depth : 0; // checkmate or stalemate
    }

    position_t start_pos = *pos;
    for (i32 i = 0; i < moves_count; i++) {
        do_move_lazy(pos, moves[i]);
        score = -nega_max(pos, depth - 1);
        *pos = start_pos;

        if(score > best)
            best = score;
    }

    return best;
}

// negamax with alpha-beta pruning, ply used to prefer faster mates
i32 alpha_beta(position_t* pos, i32 alpha, i32 beta, i32 depth, i32 ply){
    move_t moves[MAX_MOVES];

    if(is_threefold_repetition(pos)) return 0;

    if(depth <= 0){
        // only pay for move generation when in check can we be mated and only after 50 moves the draw matters
        if(pos->checkers || is_fifty_move_draw(pos)){
            if(get_moves(pos, moves, true) == 0) return pos->checkers ? -(MATE_VALUE - ply) : 0;
            if(is_fifty_move_draw(pos)) return 0;
        }
        return evaluate_relative(pos);
    }

    i32 moves_count = get_moves(pos, moves, true);
    if(moves_count == 0){
        return in_check(pos, pos->blacks_turn) ? -(MATE_VALUE - ply) : 0;
    }
    if(is_fifty_move_draw(pos)) return 0; // checked after mate: mate on the 100th half move still wins

    i32 scores[MAX_MOVES];
    score_moves(moves, scores, moves_count);

    position_t start_pos = *pos;
    for(i32 i = 0; i < moves_count; i++){
        move_t move = pick_move(moves, scores, i, moves_count);

        do_move_lazy(pos, move);
        i32 score = -alpha_beta(pos, -beta, -alpha, depth - 1, ply + 1);
        *pos = start_pos;

        if(score >= beta) return beta;
        if(score > alpha) alpha = score;
    }
    return alpha;
}

// returns best move for the side to move (0 if there are no legal moves); score is from the mover's perspective
move_t find_best_move(position_t* pos, i32 depth, i32* out_score){
    move_t moves[MAX_MOVES];
    if(depth < 1) depth = 1;

    i32 moves_count = get_moves(pos, moves, true);
    if(moves_count == 0){
        if(out_score) *out_score = in_check(pos, pos->blacks_turn) ? -MATE_VALUE : 0;
        return 0;
    }

    i32 scores[MAX_MOVES];
    score_moves(moves, scores, moves_count);

    position_t start_pos = *pos;
    move_t best_move = moves[0];
    i32 best = -INF_VALUE, alpha = -INF_VALUE;
    for(i32 i = 0; i < moves_count; i++){
        move_t move = pick_move(moves, scores, i, moves_count);

        do_move_lazy(pos, move);
        i32 score = -alpha_beta(pos, -INF_VALUE, -alpha, depth - 1, 1);
        *pos = start_pos;

        if(score > best){
            best = score;
            best_move = move;
            if(score > alpha) alpha = score;
        }
    }
    i32 whites_perspetive = pos->blacks_turn ? -best : best;
    if(out_score) *out_score = whites_perspetive;
    return best_move;
}

// perft: number of leaf nodes, for verifying move generation
u64 perft(position_t* pos, i32 depth){
    if(depth == 0) return 0;
    move_t moves[MAX_MOVES];
    i32 moves_count = get_moves(pos, moves, true);
    if(depth == 1) return moves_count;

    u64 nodes = 0;
    position_t start_pos = *pos;
    for(i32 i = 0; i < moves_count; i++){
        do_move_lazy(pos, moves[i]);
        nodes += perft(pos, depth - 1);
        *pos = start_pos;
    }
    return nodes;
}

// https://en.wikipedia.org/wiki/Shannon_number
u64 possible_moves[] = { 0, 20, 400, 8902, 197281, 4865609, 119060324, 3195901860, 84998978956, 2439530234167, 69352859712417 };

bool check_moves_at_depth(position_t* pos, i32 depth){
    assert(depth <= 10);

    printf("Evaluating from %s perspective\n", pos->blacks_turn ? "blacks" : "whites");
    clock_t begin = clock();
    u64 total_moves = perft(pos, depth);
    clock_t end = clock();
    printf("Runtime: %lldms\n", (long long)(end - begin) * 1000 / CLOCKS_PER_SEC);

    i64 diff = total_moves - possible_moves[depth];
    printf("Moves checked: %llu  Expected: %llu  Diff: %lld \n", total_moves, possible_moves[depth], diff);

    return diff == 0;
}

// negamax from the start position; also compares the leaf count with the known perft numbers
i32 get_score(position_t* pos, i32 depth){
    assert(depth <= 10);

    printf("Evaluating from %s perspective\n", pos->blacks_turn ? "blacks" : "whites");
    total_moves = 0;
    clock_t begin = clock();
    i32 score = nega_max(pos, depth);
    clock_t end = clock();
    printf("Runtime: %lldms\n", (long long)(end - begin) * 1000 / CLOCKS_PER_SEC);

    printf("Moves checked: %llu  Expected: %llu  Diff: %lld \n", (unsigned long long)total_moves,
           (unsigned long long)possible_moves[depth], (long long)(total_moves - possible_moves[depth]));
    return score;
}