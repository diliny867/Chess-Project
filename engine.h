#pragma once

#include "chess.h"
#include "notations.h"

// https://github.com/rigtorp/Seqlock
#include <Seqlock.h>

#include <thread>
#include <atomic>
#include <math.h>
#include <time.h>


#define INF_VALUE         2000000
#define MATE_VALUE        1000000
#define MAX_PLY           256
#define MATE_BOUND_VALUE  (MATE_VALUE - MAX_PLY)

#define TT_MOVE_VALUE     MATE_VALUE
#define KILLER_1_VALUE    9500
#define KILLER_2_VALUE    9000
#define MAX_HISTORY_VALUE 8000 // below killer values

#define PRUNING_DELTA     200


#define COMMUNICATION_CHECK_MASK 4095


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
#define whites_index(index) ((index) ^ 56)

// https://web.archive.org/web/20180714011607/https://www.stmintz.com/ccc/index.php?id=341763
// & this mask with enemy pawns mask to check if any prevent passing pawn
u64 passed_pawn_masks[CCOLOR_COUNT][64] = { 0 };
i32 passed_pawn_increase_table[64] = {
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
     90,  90,  90,  90,  90,  90,  90,  90,
     60,  60,  60,  60,  60,  60,  60,  60,
     50,  50,  50,  50,  50,  50,  50,  50,
     40,  40,  40,  40,  40,  40,  40,  40,
     30,  30,  30,  30,  30,  30,  30,  30,
      0,   0,   0,   0,   0,   0,   0,   0,
};
i32 passed_pawn_increase[CCOLOR_COUNT][64];


// https://web.archive.org/web/20071031100051/http://www.brucemo.com/compchess/programming/hashing.htm
typedef enum {
    TT_EXACT = 0,
    TT_LOWER = 1,
    TT_UPPER = 2
} tt_flag_e;
typedef struct {
    u64 hash;
    move_t move;
    i32 score;
    u8 depth;
    u8 flag;
} transposition_t;

#define TRANSPOSITION_TABLE_SIZE 0x800000
static_assert(bit_count(TRANSPOSITION_TABLE_SIZE) == 1, "Bit count of not 1 breaks entry index calculation code");

transposition_t transposition_table[TRANSPOSITION_TABLE_SIZE];


typedef struct {
    u64 nodes;                         // checked nodes count
    u64 max_nodes;
    clock_t start_ms;
    i32 max_time_ms;
    i32 history_from;                  // initial pos.history_count - 1
    i32 depth;                         // also check so we dont stop on depth == 1
    move_t killers[MAX_PLY][2];        // https://chessprogramming.org/Killer_Heuristic
    i32 history[CCOLOR_COUNT][64][64]; // https://chessprogramming.org/History_Heuristic
    move_t pv[MAX_PLY][MAX_PLY];       // https://chessprogramming.org/Triangular_PV-Table two dim array to avoid index calculations
    i32 pv_length[MAX_PLY];            // avoids null move check
    bool can_stop;
    bool stop;
} search_state_t;
search_state_t search_state;

i32 positions_searched = 0;

typedef struct {
    u64 max_nodes;   // check every 2048 nodes, 0 to off this limit
    i32 max_time_ms; // 0 to off this limit
    i32 max_depth;   // 0 to off this limit
} search_limits_t;

typedef struct {
    u64 nodes;
    move_t move; // 0 if no legal moves
    i32 score;
    i32 time_ms;
    i32 depth;
} search_result_t;
rigtorp::Seqlock<search_result_t> public_res; // we have one writer and one reader, with seqlock writer never blocks

std::thread search_thread;
std::atomic<bool> search_running{false};
std::atomic<bool> search_stop_requested{false};


void print_search_result(position_t* pos, search_result_t res){
    printf("%3d search result:\n", positions_searched);
    i32 time_ms = res.time_ms <= 0 ? 1 : res.time_ms;
    double nodes_per_second = ((double)res.nodes / time_ms) * 1000.0;
    double mn_per_sec = nodes_per_second / 1000000.0;
    printf("Checked nodes: %10llu at depth: %3d for %5dms at %2.1lf Mn/s\n", res.nodes, res.depth, time_ms, mn_per_sec);
    char best_move_pgn[10] = { 0 };
    write_move_pgn(best_move_pgn, pos, res.move);
    printf("Got best move: %s with score: %d\n", best_move_pgn, res.score);
}

static force_inline i32 search_time_elapsed_ms(){
    return (i32)(((u64)(clock() - search_state.start_ms) * 1000) / CLOCKS_PER_SEC);
}
static force_inline void check_stop(){
    if(!search_state.can_stop) return;
    if((search_state.max_nodes && search_state.nodes >= search_state.max_nodes) || (search_state.max_time_ms && search_time_elapsed_ms() >= search_state.max_time_ms) || search_stop_requested.load()){
        search_state.stop = true;
    }
}

bool is_search_running(){
    return search_running.load();
}
// void request_search_stop(){
//     search_stop_requested.store(true);
// }

static inline void communicate(){
    check_stop();
}
search_result_t poll_current_result(){
    return public_res.load();
}

static inline void update_history(move_t move, i32 bonus){
    i32* entry = &search_state.history[move_get_color(move)][move_get_from(move)][move_get_to(move)];
    bonus = clamp(bonus, -MAX_HISTORY_VALUE, MAX_HISTORY_VALUE);
    *entry += bonus - *entry * abs(bonus) / MAX_HISTORY_VALUE;
}

static force_inline void clear_tt(){
    zero_array(transposition_table);
}

static force_inline i32 score_to_tt(i32 score, i32 ply){
    if(score >=  MATE_BOUND_VALUE) return score + ply;
    if(score <= -MATE_BOUND_VALUE) return score - ply;
    return score;
}
static force_inline i32 score_from_tt(i32 score, i32 ply){
    if(score >=  MATE_BOUND_VALUE) return score - ply;
    if(score <= -MATE_BOUND_VALUE) return score + ply;
    return score;
}

static force_inline transposition_t* read_tt(u64 hash){
    transposition_t* entry = &transposition_table[hash & (TRANSPOSITION_TABLE_SIZE - 1)];

    if(entry->hash == hash){
        return entry;
    }
    return NULL;
}
static force_inline void write_tt(u64 hash, move_t move, i32 score, i32 depth, u8 flag, i32 ply){
    transposition_t* entry = &transposition_table[hash & (TRANSPOSITION_TABLE_SIZE - 1)];

    entry->hash = hash;
    entry->move = move;
    entry->score = score_to_tt(score, ply);
    entry->depth = depth > 255 ? 255 : depth;
    entry->flag = flag;
}


void init_piece_tables(){
    for (piece_t p = PIECE_FROM; p < PIECE_MAX; p++) {
        for (i32 i = 0; i < 64; i++) {
            piece_values_table_mg[CWHITE][p][i] = piece_values_mg[p] + pesto_tables_mg[p][whites_index(i)];
            piece_values_table_mg[CBLACK][p][i] = piece_values_mg[p] + pesto_tables_mg[p][i];
            piece_values_table_eg[CWHITE][p][i] = piece_values_eg[p] + pesto_tables_eg[p][whites_index(i)];
            piece_values_table_eg[CBLACK][p][i] = piece_values_eg[p] + pesto_tables_eg[p][i];
        }
    }

    for(i32 i = 0; i < 64; i++){
        i32 rank = i / 8;
        i32 file = i % 8;
        u64 whites_mask = ~0;
        u64 blacks_mask = ~0;

        // clear non influencing squares
        for(i32 file_it = 0; file_it <= 7; file_it++){
            u64 mask = file_to_mask[file_it];
            if(file_it < file - 1){
                whites_mask &= ~mask;
                blacks_mask &= ~mask;
            }
            if(file_it > file + 1){
                whites_mask &= ~mask;
                blacks_mask &= ~mask;
            }
        }
        for(i32 rank_it = 0; rank_it <= 7; rank_it++){
            u64 mask = rank_to_mask[rank_it];
            if(rank_it <= rank){
                whites_mask &= ~mask;
            }
            if(rank_it >= rank){
                blacks_mask &= ~mask;
            }
        }

        passed_pawn_masks[CWHITE][i] = whites_mask;
        passed_pawn_masks[CBLACK][i] = blacks_mask;
    }

    for(i32 i = 0; i < 64; i++){
        passed_pawn_increase[CWHITE][i] = passed_pawn_increase_table[whites_index(i)];
        passed_pawn_increase[CBLACK][i] = passed_pawn_increase_table[i];
    }
}
void reset_engine(){
    clear_tt();
    public_res.store({0, 0, 0, 0, 0});
}
void init_engine(){
    init_piece_tables();
    reset_engine();
}

// material from the point of view of the side to move
static inline i32 evaluate_relative(position_t* pos) {
    u64* pieces = pos->pieces;
    u64* colors = pos->colors;
    bool black = pos->blacks_turn;

    i32 mg[CCOLOR_COUNT] = { 0, 0 };
    i32 eg[CCOLOR_COUNT] = { 0, 0 };
    i32 phase = 0;

    for(i32 c = CWHITE; c <= CBLACK; c++){
        u64 other_mask = pieces[PAWN] & colors[!c];
        u64 mask       = pieces[PAWN] & colors[c];
        while(mask){
            i32 index = extract_piece(&mask);
            i32 passed_pawn = (i32)!(passed_pawn_masks[c][index] & other_mask); // no blocking pawns for our pawns
            mg[c] += piece_values_table_mg[c][PAWN][index];
            eg[c] += piece_values_table_eg[c][PAWN][index] + passed_pawn * passed_pawn_increase[c][index];
            // phase += gamephase_increase[PAWN]; // += 0
        }

        for(piece_t p = PAWN+1; p < PIECE_MAX; p++){
            u64 mask = pieces[p] & colors[c];
            while(mask){
                i32 index = extract_piece(&mask);
                mg[c] += piece_values_table_mg[c][p][index];
                eg[c] += piece_values_table_eg[c][p][index];
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


// captures of valuable pieces by cheap pieces first, queen promotions early, underpromotions last
// https://www.chessprogramming.org/MVV-LVA
static force_inline i32 score_move(move_t move){
    i32 score = 0;
    i32 captured = move_get_spec2(move);
    if(captured) score = piece_values_mg[captured] * 16 - move_get_piece(move) + 10000; // all captures before quiet moves
    if(move_get_type(move) == PROMOTION){
        score += (move_get_spec1(move) == QUEEN) ? 20000 : -5000;
    }
    return score;
}
// https://chessprogramming.org/Quiet_Moves
static force_inline bool move_is_quiet(move_t move){
    move_type_e type = move_get_type(move);
    return type == MOVE || type == PUSH || type == DOUBLE_PUSH || type == CASTLING;
}
static force_inline i32 score_search_move(move_t move, move_t tt_move, i32 ply){
    if(move == tt_move)      return TT_MOVE_VALUE; // https://www.chessprogramming.org/Hash_Move
    if(!move_is_quiet(move)) return score_move(move);
    if(move == search_state.killers[ply][0]) return KILLER_1_VALUE; // https://chessprogramming.org/Killer_Move
    if(move == search_state.killers[ply][1]) return KILLER_2_VALUE;
    return search_state.history[move_get_color(move)][move_get_from(move)][move_get_to(move)]; // https://www.chessprogramming.org/History_Heuristic
}
// https://chessprogramming.org/Beta-Cutoff
static force_inline void quiet_cutoff(move_t move, i32 ply, i32 depth, move_t* tried, i32 count){
    if(search_state.killers[ply][0] != move){
        search_state.killers[ply][1] = search_state.killers[ply][0];
        search_state.killers[ply][0] = move;
    }
    i32 bonus = min(70 * depth - 40, 1000);
    update_history(move, bonus);    // reward this move
    for(i32 i = 0; i < count; i++){ // punish other moves
        if(tried[i] != move) update_history(tried[i], -bonus);
    }
}


// moves the best remaining move to index i and returns it, dont sort the rest after a beta cutoff
static force_inline move_t pick_move(move_t* moves, i32* scores, i32 i, i32 count){
    i32 best = i;
    for(i32 j = i + 1; j < count; j++){
        if(scores[j] > scores[best]) best = j;
    }
    move_t move = moves[best]; moves[best] = moves[i]; moves[i] = move;
    i32 score = scores[best];  scores[best] = scores[i]; scores[i] = score;
    return move;
}

// https://www.chessprogramming.org/Quiescence_Search
static i32 quiescence(position_t* pos, i32 alpha, i32 beta, i32 ply){
    search_state.pv_length[ply] = 0;
    if((++search_state.nodes & COMMUNICATION_CHECK_MASK) == 0) communicate();
    if(search_state.stop) return 0;
    if(ply > MAX_PLY) return evaluate_relative(pos);

    bool checked = in_check(pos);
    i32 stand_pat = -INF_VALUE; // https://chessprogramming.org/Quiescence_Search#standing-pat
    i32 best = -INF_VALUE;
    if(!checked){
        stand_pat = best = evaluate_relative(pos);
        if(best >= beta) return best;
        if(best > alpha) alpha = best;
    }

    move_t moves[MAX_MOVES];
    i32 scores[MAX_MOVES];
    i32 moves_count = checked ? get_moves(pos, moves, true) : get_captures(pos, moves);
    if(checked && moves_count == 0) return -(MATE_VALUE - ply);
    for(i32 i = 0; i < moves_count; i++)
        scores[i] = score_move(moves[i]);

    position_t start_pos = *pos;
    for(i32 i = 0; i < moves_count; i++){
        move_t move = pick_move(moves, scores, i, moves_count);
        // https://www.chessprogramming.org/Delta_Pruning   TODO: off this for endgame phase
        if(!checked && (move_get_type(move) != PROMOTION) && (stand_pat + piece_values_mg[move_get_spec2(move)] + PRUNING_DELTA < alpha)) continue;

        do_move_lazy(pos, move);
        i32 score = -quiescence(pos, -beta, -alpha, ply + 1);
        *pos = start_pos;
        if(search_state.stop) return 0;

        if(score > best){
            best = score;
            if(score > alpha){
                alpha = score;
                if(score >= beta)
                    break;
            }
        }
    }
    return best;
}

// https://www.chessprogramming.org/Fail-Soft
static i32 search_node(position_t* pos, i32 alpha, i32 beta, i32 depth, i32 ply, bool allow_null){
    search_state.pv_length[ply] = 0;
    if(has_repeated(pos, search_state.history_from)) return 0;
    if(ply > MAX_PLY) return evaluate_relative(pos);

    bool checked = in_check(pos);
    if(checked && ply < search_state.depth * 2) depth++; // https://www.chessprogramming.org/Check_Extensions with limit
    if(depth <= 0) return quiescence(pos, alpha, beta, ply);

    if((++search_state.nodes & COMMUNICATION_CHECK_MASK) == 0) communicate();
    if(search_state.stop) return 0;

    bool pv = beta - alpha > 1;
    move_t tt_move = 0;
    transposition_t* tt_entry = read_tt(pos->hash);
    if(tt_entry){
        tt_move = tt_entry->move;
        if(!pv && tt_entry->depth >= depth){
            i32 score = score_from_tt(tt_entry->score, ply);
            i32 flag = tt_entry->flag;
            if(flag == TT_EXACT)                   return score; // fail-soft
            if(flag == TT_LOWER && score >= beta)  return score;
            if(flag == TT_UPPER && score <= alpha) return score;
        }
    }

    position_t start_pos = *pos;

    // https://www.chessprogramming.org/Null_Move_Pruning so passing the turn gives a score above beta, position is good
    u64 color_pieces_no_pawns = pos->colors[pos->blacks_turn] & ~(pos->pieces[PAWN] | pos->pieces[KING]);
    if(allow_null && !pv && !checked && depth >= 3 && color_pieces_no_pawns && evaluate_relative(pos) >= beta){
        do_null_move(pos);
        i32 r = 3 + depth / 6; // https://chessprogramming.org/Depth_Reduction_R  maybe use 2 + (i32)(depth >= 6) or just plain 3
        i32 score = -search_node(pos, -beta, -beta + 1, depth - r, ply + 1, false);
        *pos = start_pos;

        if(search_state.stop) return 0;
        if(score >= beta && score < MATE_BOUND_VALUE) return score;
        // if(score >= beta) return score >= MATE_BOUND_VALUE ? beta : score;
    }

    move_t moves[MAX_MOVES];
    i32 moves_count = get_moves(pos, moves, true);
    if(moves_count == 0) return checked ? -(MATE_VALUE - ply) : 0;
    if(is_fifty_move_draw(pos)) return 0; // check this after mate: mate on the 100th half move still wins

    i32 scores[MAX_MOVES];
    for(i32 i = 0; i < moves_count; i++)
        scores[i] = score_search_move(moves[i], tt_move, ply);

    move_t quiets[64];
    i32 quiets_count = 0;
    i32 old_alpha = alpha;
    move_t best_move = 0;
    i32 best = -INF_VALUE;
    for(i32 i = 0; i < moves_count; i++){
        move_t move = pick_move(moves, scores, i, moves_count);
        bool quiet = move_is_quiet(move);

        do_move_lazy(pos, move);
        // i32 score = -search_node(pos, -beta, -alpha, depth - 1, ply + 1, true);

        // https://chessprogramming.org/Principal_Variation_Search
        i32 score;
        if(i == 0){
            score = -search_node(pos, -beta, -alpha, depth - 1, ply + 1, true);
        }else{
            // https://www.chessprogramming.org/Late_Move_Reductions
            i32 reduction = 0;
            if(depth >= 3 && i >= 3 && quiet && !checked){
                reduction = (i32)(0.99 + log((double)depth) * log((double)i) / 3.14);
            }
            score = -search_node(pos, -alpha - 1, -alpha, depth - 1 - reduction, ply + 1, true);
            if(score > alpha && reduction > 0) score = -search_node(pos, -alpha - 1, -alpha, depth - 1, ply + 1, true);
            if(score > alpha && score < beta)  score = -search_node(pos, -beta, -alpha, depth - 1, ply + 1, true);
        }
        *pos = start_pos;

        if(search_state.stop) return 0;

        if(quiet && quiets_count < 64)
            quiets[quiets_count++] = move;

        if(score > best){
            best = score;
            best_move = move;
            if(score > alpha){
                alpha = score;
                if(pv){
                    search_state.pv[ply][0] = move;
                    memcpy(&search_state.pv[ply][1], search_state.pv[ply + 1], search_state.pv_length[ply + 1] * sizeof(move_t));
                    search_state.pv_length[ply] = search_state.pv_length[ply + 1] + 1;
                }
                if(score >= beta){
                    if(quiet)
                        quiet_cutoff(move, ply, depth, quiets, quiets_count);
                    break;
                }
            }
        }
    }

    tt_flag_e flag = best >= beta ? TT_LOWER : (best > old_alpha ? TT_EXACT : TT_UPPER);
    write_tt(pos->hash, flag == TT_UPPER ? 0 : best_move, alpha, depth, flag, ply);

    return best;
}

static search_result_t _search_position(position_t* pos, search_limits_t limits){
    positions_searched++;

    public_res.store({0, 0, 0, 0, 0});

    limits.max_depth   = clamp(limits.max_depth,   0, MAX_PLY - 1);
    limits.max_time_ms = clamp(limits.max_time_ms, 0, 99999);
    i32 max_depth = limits.max_depth == 0 ? MAX_PLY - 1 : limits.max_depth; // max depth for 0

    // reset_engine();

    search_state = { 0 };
    search_state.start_ms = clock();
    search_state.max_nodes = limits.max_nodes;
    search_state.max_time_ms = limits.max_time_ms;
    search_state.history_from = pos->history_count - 1;

    search_result_t res = { 0 };

    move_t moves[MAX_MOVES];
    i32 moves_count = get_moves(pos, moves, true);
    if(moves_count == 0)
        return res;

    i32 scores[MAX_MOVES];
    for(i32 i = 0; i < moves_count; i++)
        scores[i] = score_search_move(moves[i], 0, 0);
    for(i32 i = 0; i < moves_count; i++)
        pick_move(moves, scores, i, moves_count); // sort now, so dont resort every depth iteration

    position_t start_pos = *pos;
    for(i32 depth = 1; depth <= max_depth; depth++){ // https://chessprogramming.org/Iterative_Deepening
        search_state.depth = depth;
        search_state.can_stop = depth > 1; // so always a move at depth 1

        res = { 0 };
        i32 alpha  = -INF_VALUE;
        i32 best   = -INF_VALUE;
        i32 best_i = 0;
        for(i32 i = 0; i < moves_count; i++){
            move_t move = moves[i];
            do_move_lazy(pos, move);
            // i32 score = -search_node(pos, -INF_VALUE, -alpha, depth - 1, 1, true);

            // https://chessprogramming.org/Principal_Variation_Search fail-soft
            i32 score;
            if(i == 0){
                score = -search_node(pos, -INF_VALUE, -alpha, depth - 1, 1, true);
            }else{
                score = -search_node(pos, -alpha - 1, -alpha, depth - 1, 1, true);
                if(score > alpha) score = -search_node(pos, -INF_VALUE, -alpha, depth - 1, 1, true);
            }
            *pos = start_pos;

            if(search_state.stop) break;

            if(score > best){
                best = score;
                best_i = i;
                alpha = score;
                res.move = move;
                res.score = score;
                res.depth = depth;
                public_res.store(res);
            }
        }
        if(search_state.stop){
            // some moves were aborted but other need to be checked
            if(res.move != 0 && depth > 1){
                res.depth = depth - 1; // last fully finished depth
            }else{
                res = public_res.load(); // reset res because it contains incorrect data
            }
            break;
        }
        if(res.score >= MATE_BOUND_VALUE && (MATE_VALUE - res.score <= depth)) break; // found shortest mate (it fits in depth (that iteratively increases))
        // if(moves_count == 1 && limits.max_time_ms) break; // 1 move, so dont think if dont need to (incorrect position score if we break here)

        // set best move first for next iterations
        move_t tmp = moves[0];
        moves[0] = moves[best_i];
        moves[best_i] = tmp;
    }

    res.nodes = search_state.nodes;
    res.time_ms = search_time_elapsed_ms();
    public_res.store(res);

    return res;
}

search_result_t search_position(position_t* pos, search_limits_t limits){
    search_result_t res = _search_position(pos, limits);

    // bool black = pos->blacks_turn;
    // i32 whites_perspetive = black ? -res.score : res.score;
    // res.score = (res.move == 0 ? (in_check(pos, black) ? -MATE_VALUE : 0) : whites_perspetive);

    return res;
}

void stop_search(){
    if(search_thread.joinable()){
        search_stop_requested.store(true);
        search_thread.join();
    }
}
void start_search(position_t* pos, search_limits_t limits){
    stop_search();
    search_running.store(true);
    search_stop_requested.store(false);

    position_t local_pos = *pos;
    search_thread = std::thread([local_pos, limits]() mutable { // copy these by value
        search_result_t res = _search_position(&local_pos, limits);
        public_res.store(res);
        search_running.store(false);
        print_search_result(&local_pos, res);
    });
}

void clean_engine(){
    stop_search();
}


// returns best move for the side to move (0 if there are no legal moves); score is from the mover's perspective
// move_t find_best_move(position_t* pos, i32 depth, i32* out_score){
//     search_limits_t limits = { 0 };
//     limits.max_depth = depth < 1 ? 1 : depth;

//     search_result_t res = _search_position(pos, limits);

//     printf("Searched %llu nodes at %d depth\n", res.nodes, res.depth);

//     bool black = pos->blacks_turn;
//     i32 whites_perspetive = black ? -res.score : res.score;
//     if(out_score) *out_score = (res.move == 0 ? (in_check(pos, black) ? -MATE_VALUE : 0) : whites_perspetive);
//     return res.move;
// }


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
bool perft_at_depth(i32 depth){
    assert(depth <= 10);

    char* fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    position_t pos = parse_fen(fen, put_piece);

    printf("Evaluating from start position: %s\n", fen);
    // clock_t begin = clock();
    u64 total_moves = perft(&pos, depth);
    // clock_t end = clock();
    // printf("Runtime: %lldms\n", (long long)(end - begin) * 1000 / CLOCKS_PER_SEC);

    i64 diff = total_moves - possible_moves[depth];
    printf("Moves checked: %llu  Expected: %llu  Diff: %lld \n", total_moves, possible_moves[depth], diff);

    return diff == 0;
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
// negamax from the start position; also compares the leaf count with the known perft numbers
i32 get_score(position_t* pos, i32 depth){
    assert(depth <= 10);

    printf("Evaluating from %s perspective\n", pos->blacks_turn ? "blacks" : "whites");
    total_moves = 0;
    // clock_t begin = clock();
    i32 score = nega_max(pos, depth);
    // clock_t end = clock();
    // printf("Runtime: %lldms\n", (long long)(end - begin) * 1000 / CLOCKS_PER_SEC);

    printf("Moves checked: %llu  Expected: %llu  Diff: %lld \n", (unsigned long long)total_moves,
           (unsigned long long)possible_moves[depth], (long long)(total_moves - possible_moves[depth]));
    return score;
}