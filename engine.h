#pragma once

#include "chess.h"

#include <time.h>

#define PAWN_VALUE   100
#define KNIGHT_VALUE 295
#define BISHOP_VALUE 315
#define ROOK_VALUE   500
#define QUEEN_VALUE  900
#define KING_VALUE   50000

#define MATE_VALUE   1000000
#define INF_VALUE    2000000

i32 pawn_values[64] = {
    100, 100, 100, 100, 100, 100, 100, 100,
    100, 100, 100, 100, 100, 100, 100, 100,
    100, 100, 100, 100, 100, 100, 100, 100,
    100, 100, 100, 100, 100, 100, 100, 100,
    100, 100, 100, 100, 100, 100, 100, 100,
    100, 100, 100, 100, 100, 100, 100, 100,
    100, 100, 100, 100, 100, 100, 100, 100,
    100, 100, 100, 100, 100, 100, 100, 100
};
i32 knight_values[64] = {
    295, 295, 295, 295, 295, 295, 295, 295,
    295, 295, 295, 295, 295, 295, 295, 295,
    295, 295, 295, 295, 295, 295, 295, 295,
    295, 295, 295, 295, 295, 295, 295, 295,
    295, 295, 295, 295, 295, 295, 295, 295,
    295, 295, 295, 295, 295, 295, 295, 295,
    295, 295, 295, 295, 295, 295, 295, 295,
    295, 295, 295, 295, 295, 295, 295, 295

};
i32 bishop_values[64] = {
    305, 305, 305, 305, 305, 305, 305, 305,
    305, 305, 305, 305, 305, 305, 305, 305,
    305, 305, 305, 305, 305, 305, 305, 305,
    305, 305, 305, 305, 305, 305, 305, 305,
    305, 305, 305, 305, 305, 305, 305, 305,
    305, 305, 305, 305, 305, 305, 305, 305,
    305, 305, 305, 305, 305, 305, 305, 305,
    305, 305, 305, 305, 305, 305, 305, 305
};
i32 rook_values[64] = {
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500

};
i32 queen_values[64] = {
    900, 900, 900, 900, 900, 900, 900, 900,
    900, 900, 900, 900, 900, 900, 900, 900,
    900, 900, 900, 900, 900, 900, 900, 900,
    900, 900, 900, 900, 900, 900, 900, 900,
    900, 900, 900, 900, 900, 900, 900, 900,
    900, 900, 900, 900, 900, 900, 900, 900,
    900, 900, 900, 900, 900, 900, 900, 900,
    900, 900, 900, 900, 900, 900, 900, 900
};
i32 king_values[64] = {
    50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000,
    50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000,
    50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000,
    50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000,
    50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000,
    50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000,
    50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000,
    50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000
};

// indexed by piece_e (PAWN == 1), index 0 unused
i32 piece_values[PIECE_MAX] = { 0, PAWN_VALUE, KNIGHT_VALUE, BISHOP_VALUE, ROOK_VALUE, QUEEN_VALUE, KING_VALUE };

extern void draw_position(position_t* pos);

#define DELAY 300
void wait_ms(int milliseconds){
    clock_t start_time = clock();
    while((clock() - start_time) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

// material from whites point of view
i32 material_evaluate(position_t* pos) {
    u64* pieces = pos->pieces;
    u64* colors = pos->colors;
    i32 value = 0;
    for(i32 i = PIECE_FROM; i < PIECE_MAX; i++){
        i32 piece_count = bit_count(pieces[i] & colors[CWHITE]) - bit_count(pieces[i] & colors[CBLACK]);
        value += piece_values[i] * piece_count;
    }
    return value;
}

// material from the point of view of the side to move
static inline i32 evaluate_relative(position_t* pos){
    i32 value = material_evaluate(pos);
    return pos->blacks_turn ? -value : value;
}

// captures of valuable pieces by cheap pieces first, queen promotions early, underpromotions last
static i32 move_order_score(move_t move){
    i32 score = 0;
    i32 captured = move_get_spec2(move);
    if(captured) score = piece_values[captured] * 16 - move_get_piece(move) + 10000; // all captures before quiet moves
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