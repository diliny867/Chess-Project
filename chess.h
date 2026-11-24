#pragma once

#include "common.h"
#include "tables.h"

#include <assert.h>

/*
8   56 57 58 59 60 61 62 63
7   48 49 50 51 52 53 54 55
6   40 41 42 43 44 45 46 47
5   32 33 34 35 36 37 38 39
4   24 25 26 27 28 29 30 31
3   16 17 18 19 20 21 22 23
2    8  9 10 11 12 13 14 15
1    0  1  2  3  4  5  6  7

    A  B  C  D  E  F  G  H
*/

typedef enum {
    EMPTY_PIECE = 0, // for some times where you need to store additional piece data
    PAWN = 1,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    PIECE_MAX
} piece_e;
typedef i32 piece_t;

#define PIECE_FROM PAWN

// #define PAWN   0
// #define KNIGHT 1
// #define BISHOP 2
// #define ROOK   3
// #define QUEEN  4
// #define KING   5

#define WHITE_PAWN_POS 0
#define BLACK_PAWN_POS 1
static_assert((i32)BLACK_PAWN_POS == (i32)PAWN && (i32)WHITE_PAWN_POS == (i32)EMPTY_PIECE);

typedef enum{
    CWHITE = 0,
    CBLACK = 1,
    CCOLOR_COUNT
} color_e;
static_assert(CCOLOR_COUNT == 2, "Color count must be 2");

#define RANK_1 0x00000000000000FFULL
#define RANK_2 0x000000000000FF00ULL
#define RANK_3 0x0000000000FF0000ULL
#define RANK_4 0x00000000FF000000ULL
#define RANK_5 0x000000FF00000000ULL
#define RANK_6 0x0000FF0000000000ULL
#define RANK_7 0x00FF000000000000ULL
#define RANK_8 0xFF00000000000000ULL

#define RANK_18 0xFF000000000000FFULL

#define FILE_A 0x0101010101010101ULL
#define FILE_B 0x0202020202020202ULL
#define FILE_C 0x0404040404040404ULL
#define FILE_D 0x0808080808080808ULL
#define FILE_E 0x1010101010101010ULL
#define FILE_F 0x2020202020202020ULL
#define FILE_G 0x4040404040404040ULL
#define FILE_H 0x8080808080808080ULL

#define FILE_AB 0x0303030303030303ULL
#define FILE_GH 0xC0C0C0C0C0C0C0C0ULL
#define FILE_AH 0x8181818181818181ULL

#define A1 0x0000000000000001ULL
#define A2 0x0000000000000100ULL
#define A3 0x0000000000010000ULL
#define A4 0x0000000001000000ULL
#define A5 0x0000000100000000ULL
#define A6 0x0000010000000000ULL
#define A7 0x0001000000000000ULL
#define A8 0x0100000000000000ULL
#define B1 0x0000000000000002ULL
#define B2 0x0000000000000200ULL
#define B3 0x0000000000020000ULL
#define B4 0x0000000002000000ULL
#define B5 0x0000000200000000ULL
#define B6 0x0000020000000000ULL
#define B7 0x0002000000000000ULL
#define B8 0x0200000000000000ULL
#define C1 0x0000000000000004ULL
#define C2 0x0000000000000400ULL
#define C3 0x0000000000040000ULL
#define C4 0x0000000004000000ULL
#define C5 0x0000000400000000ULL
#define C6 0x0000040000000000ULL
#define C7 0x0004000000000000ULL
#define C8 0x0400000000000000ULL
#define D1 0x0000000000000008ULL
#define D2 0x0000000000000800ULL
#define D3 0x0000000000080000ULL
#define D4 0x0000000008000000ULL
#define D5 0x0000000800000000ULL
#define D6 0x0000080000000000ULL
#define D7 0x0008000000000000ULL
#define D8 0x0800000000000000ULL
#define E1 0x0000000000000010ULL
#define E2 0x0000000000001000ULL
#define E3 0x0000000000100000ULL
#define E4 0x0000000010000000ULL
#define E5 0x0000001000000000ULL
#define E6 0x0000100000000000ULL
#define E7 0x0010000000000000ULL
#define E8 0x1000000000000000ULL
#define F1 0x0000000000000020ULL
#define F2 0x0000000000002000ULL
#define F3 0x0000000000200000ULL
#define F4 0x0000000020000000ULL
#define F5 0x0000002000000000ULL
#define F6 0x0000200000000000ULL
#define F7 0x0020000000000000ULL
#define F8 0x2000000000000000ULL
#define G1 0x0000000000000040ULL
#define G2 0x0000000000004000ULL
#define G3 0x0000000000400000ULL
#define G4 0x0000000040000000ULL
#define G5 0x0000004000000000ULL
#define G6 0x0000400000000000ULL
#define G7 0x0040000000000000ULL
#define G8 0x4000000000000000ULL
#define H1 0x0000000000000080ULL
#define H2 0x0000000000008000ULL
#define H3 0x0000000000800000ULL
#define H4 0x0000000080000000ULL
#define H5 0x0000008000000000ULL
#define H6 0x0000800000000000ULL
#define H7 0x0080000000000000ULL
#define H8 0x8000000000000000ULL

#define EDGES  0xFF818181818181FFULL

u64 rank_to_mask[8] = { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8 };
u64 file_to_mask[8] = { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };

// 'The maximum number of moves in any reachable chess position is 218' https://www.chessprogramming.org/Chess_Position
#define MAX_MOVES    256


#define put_bits(value, mask)      ((value) |=  (mask))
#define and_bits(value, mask)      ((value) &=  (mask))
#define toggle_bits(value, mask)   ((value) ^=  (mask))
#define clear_bits(value, mask)    ((value) &= ~(mask))
#define get_bits(value, mask)      ((value) &   (mask))

#define put_bit(value, index)    put_bits((value),    1ull << (index))
#define toggle_bit(value, index) toggle_bits((value), 1ull << (index))
#define clear_bit(value, index)  clear_bits((value),  1ull << (index))
#define get_bit(value, index)    get_bits((value),    1ull << (index))

#define expand_full(value) (~(value) + 1)


#define lsb_zeros(val)                           __builtin_ctzll(val)
#define bit_count(val)                           __builtin_popcountll(val)

#define zero_array(arr)                          memset(arr, 0, sizeof(arr))
#define zero_array_count(arr, count)             memset(arr, 0, sizeof((arr)[0]) * (count))
#define copy_array(dst, src)                     memcpy(dst, src, sizeof(src))
#define compare_array(arr1, arr2)                memcmp(arr1, arr2, sizeof(arr1))
#define array_element_equals(arr1, index, elem) (memcmp(arr1 + index, &elem, sizeof(elem)) == 0)

#define memzero(dst, size)                       memset(dst, 0, size)

#define sign(val) (((val) > 0) - ((val) < 0))


typedef enum {
    MOVE = 0, // need as 1 ?
    CAPTURE,
    PUSH,
    DOUBLE_PUSH,
    ENPASSANT,
    PROMOTION,
    CASTLING
} move_type_e;

//   MOVE, CAPTURE : spec2 = captured piece (0 for MOVE)
//   DOUBLE_PUSH   : spec1 = en passant target square
//   ENPASSANT     : spec1 = square of captured pawn, spec2 = PAWN
//   PROMOTION     : spec1 = promoted piece, spec2 = captured piece (0 if none)
//   CASTLING      : spec1 = rook from, spec2 = rook to

// total bits: 31  from: 6 bits  to: 6 bits  type: 3 bits  color: 1 bit  piece: 3 bits  spec1: 6 bits  spec2: 6 bits
typedef u32 move_t;
typedef enum {
    MOVE_FROM_POS  = 0,
    MOVE_TO_POS    = 6,
    MOVE_TYPE_POS  = 12,
    MOVE_COLOR_POS = 15,
    MOVE_PIECE_POS = 16,
    MOVE_SPEC1_POS = 19,
    MOVE_SPEC2_POS = 25,
} move_bits_pos_e;
typedef enum {
    MOVE_FROM_BIT  = 0x3F,       // 0x3F << 0
    MOVE_TO_BIT    = 0xFC0,      // 0x3F << 6
    MOVE_TYPE_BIT  = 0x7000,     // 0x7  << 12
    MOVE_COLOR_BIT = 0x8000,     // 0x1  << 15
    MOVE_PIECE_BIT = 0x70000,    // 0x7  << 16
    MOVE_SPEC1_BIT = 0x1F80000,  // 0x3F << 19
    MOVE_SPEC2_BIT = 0x7E000000, // 0x3F << 25
} move_bits_e;

#define move_get_from( move)  (((move) >> MOVE_FROM_POS)  & 0x3F)
#define move_get_to(   move)  (((move) >> MOVE_TO_POS)    & 0x3F)
#define move_get_type( move)  ((move_type_e)(((move) >> MOVE_TYPE_POS)  & 0x7))
#define move_get_color(move)  (((move) >> MOVE_COLOR_POS) & 0x1)
#define move_get_piece(move)  (((move) >> MOVE_PIECE_POS) & 0x7)
#define move_get_spec1(move)  (((move) >> MOVE_SPEC1_POS) & 0x3F)
#define move_get_spec2(move)  (((move) >> MOVE_SPEC2_POS) & 0x3F)

#define move_set_from( move, val)  ((move) = ((move) & ~MOVE_FROM_BIT)  | ((u32)(val) << MOVE_FROM_POS))
#define move_set_to(   move, val)  ((move) = ((move) & ~MOVE_TO_BIT)    | ((u32)(val) << MOVE_TO_POS))
#define move_set_type( move, val)  ((move) = ((move) & ~MOVE_TYPE_BIT)  | ((u32)(val) << MOVE_TYPE_POS))
#define move_set_color(move, val)  ((move) = ((move) & ~MOVE_COLOR_BIT) | ((u32)(val) << MOVE_COLOR_POS))
#define move_set_piece(move, val)  ((move) = ((move) & ~MOVE_PIECE_BIT) | ((u32)(val) << MOVE_PIECE_POS))
#define move_set_spec1(move, val)  ((move) = ((move) & ~MOVE_SPEC1_BIT) | ((u32)(val) << MOVE_SPEC1_POS))
#define move_set_spec2(move, val)  ((move) = ((move) & ~MOVE_SPEC2_BIT) | ((u32)(val) << MOVE_SPEC2_POS))


typedef struct {
    u64 pieces[PIECE_MAX];
    u64 colors[CCOLOR_COUNT];
    piece_t pieces_in_squares[64];
    u64 all_pieces;
    u64 pseudo_attacks[PIECE_MAX];
    u64 all_pseudo_attacks;
    bool lost_castling_rights[CCOLOR_COUNT][2];
    u64 enpassantable;
    u64 pinneds[CCOLOR_COUNT];
    u64 pinned_masks[CCOLOR_COUNT];
    u64 checkers;
    u64 check_mask;
    i32 turns_passed;
    bool blacks_turn;
    bool full_setup_pending; // pins and enemy attacks not calculated yet, see do_move_lazy and ensure_setup
    i32 halfmove_clock;      // 50 move rule
    i32 history_count;       // number of entries of position_history that belong to this position
    u64 hash;                // hash of the current position, same as position_history[history_count - 1]
} position_t;

// Hashes of all positions of the current game or search
#define MAX_HISTORY 20000
u64 position_history[MAX_HISTORY];

u64 zobrist_pieces[CCOLOR_COUNT][PIECE_MAX][64];
u64 zobrist_castling[16]; // indexed by castling_index
u64 zobrist_enpassant[64];
u64 zobrist_side;         // xored in on blacks turn


extern u64 bishop_magics[64];
extern u64 rook_magics[64];
extern u32 bishop_shifts[64];
extern u32 rook_shifts[64];
extern u64 bishop_masks[64];
extern u64 rook_masks[64];

u64 lines[64][64] = { 0 };
u64 rays[64][64] = { 0 };
u64 pseudo_legal_attacks[PIECE_MAX][64] = { 0 };
u64 pseudo_legal_attackers[PIECE_MAX][64] = { 0 };
u64 all_pseudo_legal_attackers[CCOLOR_COUNT][64] = { 0 };

u64 bishop_table[64][512];
u64 rook_table[64][4096];


typedef enum{
    CASTLE_OOO = 0, // queenside
    CASTLE_OO       // kingside
} castling_e;
// squares the king lands on
u64 castle_pos[CCOLOR_COUNT][2]        = { { 0x0000000000000004ULL, 0x0000000000000040ULL }, { 0x0400000000000000ULL, 0x4000000000000000ULL } };
// squares between king and rook that must be empty (b,c,d and f,g)
u64 castle_masks[CCOLOR_COUNT][2]      = { { 0x000000000000000EULL, 0x0000000000000060ULL }, { 0x0E00000000000000ULL, 0x6000000000000000ULL } };
// squares the king passes and lands on that must not be attacked (c,d / f,g), but b file may be attacked
u64 castle_safe_masks[CCOLOR_COUNT][2] = { { 0x000000000000000CULL, 0x0000000000000060ULL }, { 0x0C00000000000000ULL, 0x6000000000000000ULL } };
// squares the rook must stand on
u64 castle_rook_from[CCOLOR_COUNT][2]  = { { A1, H1 }, { A8, H8 } };

#define CASTLING_SQUARES (A1 | E1 | H1 | A8 | E8 | H8)

u64 enpassant_affected_pawns[64] = { 0 };
u64 enpassantable_squares[CCOLOR_COUNT] = { RANK_6, RANK_3 };

// u64 pseudo_attacks[CCOLOR_COUNT][PIECE_MAX];
// u64 all_pseudo_attacks[CCOLOR_COUNT];


static inline i32 pop_lsb(u64* val){
    i32 i = lsb_zeros(*val);
    *val &= *val - 1;
    return i;
}
static inline i32 extract_piece(u64* piece_mask){
    return pop_lsb(piece_mask);
}
static inline i32 mask_to_index(u64 piece_mask){
    return lsb_zeros(piece_mask);
}

u64 next_subset(u64 subset, u64 set){
    return (subset - set) & set;
}

void print_mask(u64 val){
    u8* vals = (u8*)&val;
    for(i32 i = 0; i < 8; i++){
        for(i32 j = 0; j < 8; j++){
            printf("%d", (vals[7 - i] >> j) & 1);
        }
        printf("\n");
    }
}

void print_mask2(u64 val, char num, char space){
    u8* vals = (u8*)&val;
    for(i32 i = 0; i < 8; i++){
        for(i32 j = 0; j < 8; j++){
            printf("%c", ((vals[7 - i] >> j) & 1) ? num : space);
        }
        printf("\n");
    }
}

void print_pieces(position_t* pos, bool black) {
    u64* pieces = pos->pieces;
    u64 color_pieces = pos->colors[black];
	u64 mask;
    print_mask(pos->all_pieces & color_pieces);
    printf("\n");
	for(piece_t p = PIECE_FROM; p < PIECE_MAX; p++) {
        mask = pieces[p] & color_pieces;
        print_mask2(mask, (char)p + 48, '_');
        printf("\n");
	}
}

char piece_codes[PIECE_MAX] = { '?', 'p', 'n', 'b', 'r', 'q', 'k' };
void print_move_on_board(piece_t piece, i32 index){
    i32 x = index & 7;
    i32 y = index >> 3;
    char p = piece_codes[piece];
    char letter = 'a' + x;
    char number = '1' + y;
    printf("%c%c%c", p, letter, number);
}
void print_move(move_t move){
    piece_t piece = move_get_piece(move);
    i32 from = move_get_from(move);
    i32 to = move_get_to(move);
    // move_type_e move_type = move_get_type(move);
    // u32 spec1 = move_get_spec1(move);
    // u32 spec2 = move_get_spec2(move);
    print_move_on_board(piece, from);
    printf(" -> ");
    print_move_on_board(piece, to);
}

i32 get_dist_to_edge(i32 index, i32 direction){
    i32 r = index >> 3;
    i32 f = index & 7;
    switch (direction){
    case 1:
        return 7 - f;
    case 8:
        return 7 - r;
    case -1:
        return f;
    case -8:
        return r;
    case 7:
        return min(7 - r, f);
    case 9:
        return min(7 - r, 7 - f);
    case -7:
        return min(r, 7 - f);
    case -9:
        return min(r, f);
    }
    return 0;
}
u64 gen_slider_attack(i32 index, i32 directions[4], u64 mask){
    u64 attack = 0;
    u64 val;
    i32 direction, iters, shift;
    for(i32 i = 0; i < 4; i++){
        direction = directions[i];
        iters = get_dist_to_edge(index, direction);
        shift = index;
        for(i32 j = 0; j < iters; j++){
            shift += direction;
            val = 1ull << shift;
            attack |= val;
            if((val & mask) != 0){
                break;
            }
        }
    }
    return attack;
}
void fill_bishop_table(){
    u64 mask, hash, shift, magic, sub, *table;
    for(i32 i = 0; i < 64; i++){
        mask = bishop_masks[i];
        magic = bishop_magics[i];
        shift = bishop_shifts[i];
        table = bishop_table[i];
        sub = 0;
        for(i32 j = 0; j < 512; j++){
            hash = (sub * magic) >> shift;
            table[hash] = gen_slider_attack(i, (i32[4]){ 7, 9, -9, -7 }, sub);
            sub = next_subset(sub, mask);
        }
    }
}
void fill_rook_table(){
    u64 mask, hash, shift, magic, sub, *table;
    for(i32 i = 0; i < 64; i++){
        mask = rook_masks[i];
        magic = rook_magics[i];
        shift = rook_shifts[i];
        table = rook_table[i];
        sub = 0;
        for(i32 j = 0; j < 4096; j++){
            hash = (sub * magic) >> shift;
            table[hash] = gen_slider_attack(i, (i32[4]){ 1, 8, -8, -1 }, sub);
            sub = next_subset(sub, mask);
        }
    }
}

i32 get_direction(i32 from, i32 to){
    if(from == to){
        return 0;
    }
    i32 xf = from & 7;
    i32 yf = from >> 3;
    i32 xt = to & 7;
    i32 yt = to >> 3;

    i32 diffx = xt - xf;
    i32 diffy = yt - yf;

    i32 direction = 0;
    if(abs(diffx) == abs(diffy)){
        if(diffx > 0 && diffy > 0){
            direction = 9;
        }else if(diffx < 0 && diffy < 0){
            direction = -9;
        }
        if(diffx > 0 && diffy < 0){
            direction = -7;
        }else if(diffx < 0 && diffy > 0){
            direction = 7;
        }
    }else if((diffx == 0) ^ (diffy == 0)){
        if(diffx > 0){
            direction = 1;
        }else if(diffx < 0){
            direction = -1;
        }
        if(diffy > 0){
            direction = 8;
        }else if(diffy < 0){
            direction = -8;
        }
    }
    return direction;
}
u64 gen_ray(i32 from, i32 to){ // non horizontal/vertical/diagonal will be 0
    i32 direction = get_direction(from, to);
    if(direction == 0){
        return 0;
    }
    u64 mask = 0;
    while(from != to){
        put_bit(mask, from);
        from += direction;
    }
    return mask;
}
void fill_rays_table(){
    for(i32 i = 0; i < 64; i++){
        for(i32 j = 0; j < 64; j++){
            rays[i][j] = gen_ray(i, j);
        }
    }
}


static inline u64 bishop_moves(u64 board, i32 index){
    u64 mask = board & bishop_masks[index];
    u64 hash = (mask * bishop_magics[index]) >> bishop_shifts[index];
    return bishop_table[index][hash];
}
static inline u64 rook_moves(u64 board, i32 index){
    u64 mask = board & rook_masks[index];
    u64 hash = (mask * rook_magics[index]) >> rook_shifts[index];
    return rook_table[index][hash];
}
static inline u64 queen_moves(u64 board, i32 index){
    return bishop_moves(board, index) | rook_moves(board, index);
}

// edge to edge line through two aligned squares
void fill_lines_table(){
    for(i32 a = 0; a < 64; a++){
        for(i32 b = 0; b < 64; b++){
            i32 d = get_direction(a, b);
            if(d == 0) continue; // not aligned

            u64 mask = (abs(d) == 1 || abs(d) == 8) ? (rook_moves(0, a) & rook_moves(0, b))
                                                 : (bishop_moves(0, a) & bishop_moves(0, b));
            lines[a][b] = mask | (1ull << a) | (1ull << b);
        }
    }
}

static inline bool index_occupied(u64 board, i32 index){
    return get_bit(board, index);
}

static inline i32 find_piece(position_t* pos, bool black, piece_t piece){
    return mask_to_index(pos->pieces[piece] & pos->colors[black]);
}

static inline bool check_index_piece(position_t* pos, piece_t piece, i32 index){
    return !!get_bit(pos->pieces[piece], index);
}

// #define piece_check(pcs, mask, piece)  (!!(pcs[(piece)] & (mask)))
// #define piece_value_here(pcs, mask, piece)   (piece_check(pcs, mask, piece) * (piece))
// static force_inline piece_t piece_at(position_t* pos, bool black, i32 index){
//     u64 mask = get_bit(pos->colors[black], index);
//     if(mask == 0){
//         return EMPTY_PIECE;
//     }
//     u64* pieces = pos->pieces;
//     i32 val = piece_value_here(pieces, mask, PAWN) + piece_value_here(pieces, mask, KNIGHT) + piece_value_here(pieces, mask, BISHOP)
//             + piece_value_here(pieces, mask, ROOK) + piece_value_here(pieces, mask, QUEEN)  + piece_value_here(pieces, mask, KING);
//     return val;
// }
// static force_inline piece_t piece_at(position_t* pos, u64 mask){
//     u64* pieces = pos->pieces;
//     i32 val = piece_value_here(pieces, mask, PAWN) + piece_value_here(pieces, mask, KNIGHT) + piece_value_here(pieces, mask, BISHOP)
//             + piece_value_here(pieces, mask, ROOK) + piece_value_here(pieces, mask, QUEEN)  + piece_value_here(pieces, mask, KING);
//     return val;
// }
// static force_inline piece_t piece_at_all(position_t* pos, i32 index, bool* black){
//     piece_t piece = piece_at(pos, CWHITE, index);
//     if(piece != EMPTY_PIECE){
//         *black = CWHITE;
//         return piece;
//     }
//     *black = CBLACK;
//     return piece_at(pos, CBLACK, index);
// }

static force_inline piece_t piece_at(position_t* pos, i32 index){
    return pos->pieces_in_squares[index];
}
static force_inline piece_t piece_at(position_t* pos, bool black, i32 index){
    if(pos->colors[black] & (1ull << index))
        return pos->pieces_in_squares[index];
    return EMPTY_PIECE;
}
static force_inline piece_t piece_at_all(position_t* pos, i32 index, bool* black){
    *black = !!(pos->colors[CBLACK] & (1ull << index)); // something is there
    return pos->pieces_in_squares[index];
}

static force_inline void clear_piece(position_t* pos, bool black, piece_t piece, i32 index){
    clear_bit(pos->pieces[piece], index);
    clear_bit(pos->colors[black], index);
    pos->pieces_in_squares[index] = EMPTY_PIECE;
}
static force_inline void put_piece(position_t* pos, bool black, piece_t piece, i32 index){
    put_bit(pos->pieces[piece], index);
    put_bit(pos->colors[black], index);
    pos->pieces_in_squares[index] = piece;
}
// static force_inline void switch_piece(position_t* pos, piece_t piece_from, piece_t piece_to, i32 index){
//     clear_bit(pos->pieces[piece_from], index);
//     put_bit(pos->pieces[piece_to], index);
//     pos->pieces_in_squares[piece_to] = pos->pieces_in_squares[piece_from];
//     pos->pieces_in_squares[piece_from] = EMPTY_PIECE;
// }
// static force_inline void move_piece(position_t* pos, bool black, piece_t piece, i32 from, i32 to){
//     u64 from_mask = 1ull << from;
//     u64 to_mask   = 1ull << to;
//     clear_bits(pos->pieces[piece], from_mask);
//     clear_bits(pos->colors[black], from_mask);
//     clear_bits(pos->colors[!black], to_mask);
//     for(piece_t p = PIECE_FROM; p < PIECE_MAX; p++){
//         clear_bits(pos->pieces[p], to_mask);
//     }
//     put_bits(pos->pieces[piece], to_mask);
//     put_bits(pos->colors[black], to_mask);
//     pos->pieces_in_squares[to] = pos->pieces_in_squares[from];
//     pos->pieces_in_squares[from] = EMPTY_PIECE;
// }

u64 get_attackers(position_t* pos, bool black, i32 index, piece_t piece, u64 blocking){
    u64 pieces = pos->pieces[piece];
    if(piece == PAWN){
        piece = black ? BLACK_PAWN_POS : WHITE_PAWN_POS;
    }
    if(blocking){
        if(piece == BISHOP){
            return bishop_moves(blocking, index) & pieces;
        }else if(piece == ROOK){
            return rook_moves(blocking, index)   & pieces;
        }else if(piece == QUEEN){
            return queen_moves(blocking, index)  & pieces;
        }
    }
    return pseudo_legal_attackers[piece][index] & pieces;
}
u64 get_all_attackers(position_t* pos, bool black, i32 index, u64 blocking){
    if(blocking){
        u64* pieces = pos->pieces;
        return pseudo_legal_attackers[black ? BLACK_PAWN_POS : WHITE_PAWN_POS][index] & pieces[PAWN]
             | pseudo_legal_attackers[KNIGHT][index] & pieces[KNIGHT]
             | pseudo_legal_attackers[KING][index]   & pieces[KING]
             | bishop_moves(blocking, index) & (pieces[BISHOP] | pieces[QUEEN])
             | rook_moves(blocking, index)   & (pieces[ROOK]   | pieces[QUEEN]);
    }
    return all_pseudo_legal_attackers[black][index] & pos->all_pieces;
}

u64 bishop_xray(position_t* pos, bool black, i32 index){
    u64* colors = pos->colors;
    u64 all_pieces = pos->all_pieces;
    u64 blockers = colors[black]; // no point in also checking enemy pieces
    u64 mask = bishop_moves(all_pieces, index);
    blockers &= mask; // take only attacked pieces
    return mask ^ bishop_moves(all_pieces ^ blockers, index); // out of initially attacked get potential positions for pinners from moves without blocking pieces
}
u64 rook_xray(position_t* pos, bool black, i32 index){
    u64* colors = pos->colors;
    u64 all_pieces = pos->all_pieces;
    u64 blockers = colors[black];
    u64 mask = rook_moves(all_pieces, index);
    blockers &= mask;
    return mask ^ rook_moves(all_pieces ^ blockers, index);
}
void calculate_pinned(position_t* pos, bool black){
    u64* pieces = pos->pieces;
    u64 color_pieces = pos->colors[black];
    u64 other_pieces = pos->colors[!black];
    u64 all_pieces = pos->all_pieces;
    u64 pinned = 0, pin_rays = 0;
    i32 king = mask_to_index(pieces[KING] & color_pieces);

    // enemy sliders that would see the king on an empty board
    u64 snipers = (pseudo_legal_attacks[ROOK][king]   & (pieces[ROOK]   | pieces[QUEEN]) & other_pieces)
                | (pseudo_legal_attacks[BISHOP][king] & (pieces[BISHOP] | pieces[QUEEN]) & other_pieces);
    while(snipers){
        i32 sniper = pop_lsb(&snipers);
        u64 ray = rays[sniper][king];
        u64 between = all_pieces & ray & ~(1ull << sniper);
        if(between && !(between & (between - 1))){ // exactly one piece between, pinned if it is ours
            pinned |= between & color_pieces;
            pin_rays |= ray;
        }
    }

    pos->pinneds[black] = pinned;
    pos->pinned_masks[black] = pin_rays;
}

static inline u64 pawns_attack(bool black, u64 piece_mask){
    return (((piece_mask << 7 & ~FILE_H) | (piece_mask << 9 & ~FILE_A)) &  (black - 1llu)    //white side attacks
         |  ((piece_mask >> 7 & ~FILE_A) | (piece_mask >> 9 & ~FILE_H)) & ~(black - 1llu));  //black side attacks
}
static inline u64 pawns_steps(u64 empties, bool black, u64 piece_mask){
    return ((((piece_mask << 8) | ((piece_mask & RANK_2) << 16) & (empties << 8)) &  (black - 1llu)              //white side steps
         |   ((piece_mask >> 8) | ((piece_mask & RANK_7) >> 16) & (empties >> 8)) & ~(black - 1llu)) & empties); //black side steps
}
static inline u64 knights_attack(u64 piece_mask){
    return (piece_mask << 6 & ~FILE_GH) | (piece_mask << 10 & ~FILE_AB) | (piece_mask << 15 & ~FILE_H) | (piece_mask << 17 & ~FILE_A)
         | (piece_mask >> 6 & ~FILE_AB) | (piece_mask >> 10 & ~FILE_GH) | (piece_mask >> 15 & ~FILE_A) | (piece_mask >> 17 & ~FILE_H);
}
static inline u64 bishops_attack(u64 board, u64 piece_mask){
    u64 mask = 0;
    while(piece_mask){
        mask |= bishop_moves(board, extract_piece(&piece_mask));
    }
    return mask;
}
static inline u64 rooks_attack(u64 board, u64 piece_mask){
    u64 mask = 0;
    while(piece_mask){
        mask |= rook_moves(board, extract_piece(&piece_mask));
    }
    return mask;
}
static inline u64 queens_attack(u64 board, u64 piece_mask){
    u64 mask = 0;
    while(piece_mask){
        mask |= queen_moves(board, extract_piece(&piece_mask));
    }
    return mask;
}
static inline u64 kings_attack(u64 piece_mask){
    return (piece_mask << 1 & ~FILE_A) | (piece_mask << 7 & ~FILE_H) | (piece_mask << 8) | (piece_mask << 9 & ~FILE_A)
         | (piece_mask >> 1 & ~FILE_H) | (piece_mask >> 7 & ~FILE_A) | (piece_mask >> 8) | (piece_mask >> 9 & ~FILE_H);
}

u64 get_pseudo_legal_attack(position_t* pos, bool black, u64 piece_mask, piece_t piece){
    u64* pieces = pos->pieces;
    u64* colors = pos->colors;
    // u64 color_pieces = colors[black];
    u64 other_pieces = colors[!black];
    u64 all_pieces = pos->all_pieces;
    u64 board;

    u64 mask = 0;
    switch (piece){
    case PAWN:
        mask  = pawns_attack(black, piece_mask);
        break;
    case KNIGHT:
        mask  = knights_attack(piece_mask);
        break;
    case BISHOP: // exclude enemy king from calculating attacks for sliders
        board = all_pieces ^ (pieces[KING] & other_pieces);
        mask  = bishops_attack(board, piece_mask);
        break;
    case ROOK:
        board = all_pieces ^ (pieces[KING] & other_pieces);
        mask  = rooks_attack(board, piece_mask);
        break;
    case QUEEN:
        board = all_pieces ^ (pieces[KING] & other_pieces);
        mask  = queens_attack(board, piece_mask);
        break;
    case KING:
        mask  = kings_attack(piece_mask);
        break;
    }
    // return mask & ~color_pieces;
    return mask; // dont & ~color_pieces so king cant capture defended piece
}

// attacks of the side NOT to move
void fill_pseudo_legal_attacks(position_t* pos){
    u64* pieces = pos->pieces;
    u64* pseudo_attacks = pos->pseudo_attacks;
    bool black = !pos->blacks_turn;
    u64 color_pieces = pos->colors[black];
    u64 board = pos->all_pieces ^ (pieces[KING] & pos->colors[!black]); // exclude enemy king for sliders

    pseudo_attacks[PAWN]   = pawns_attack(black, pieces[PAWN] & color_pieces);
    pseudo_attacks[KNIGHT] = knights_attack(pieces[KNIGHT] & color_pieces);
    pseudo_attacks[BISHOP] = bishops_attack(board, pieces[BISHOP] & color_pieces);
    pseudo_attacks[ROOK]   = rooks_attack(board, pieces[ROOK] & color_pieces);
    pseudo_attacks[QUEEN]  = queens_attack(board, pieces[QUEEN] & color_pieces);
    pseudo_attacks[KING]   = kings_attack(pieces[KING] & color_pieces);
    pos->all_pseudo_attacks = pseudo_attacks[PAWN] | pseudo_attacks[KNIGHT] | pseudo_attacks[BISHOP]
                            | pseudo_attacks[ROOK] | pseudo_attacks[QUEEN]  | pseudo_attacks[KING];
}

// finishes the work do_move_lazy skipped (enemy attacks, pins)
static force_inline void ensure_setup(position_t* pos){
    if(pos->full_setup_pending){
        fill_pseudo_legal_attacks(pos);
        calculate_pinned(pos, pos->blacks_turn);
        pos->full_setup_pending = false;
    }
}

static force_inline void promote(position_t* pos, bool black, i32 index, piece_t piece){
    clear_bit(pos->pieces[PAWN], index);
    put_bit(pos->pieces[piece], index);
}



static force_inline i32 king_index(position_t* pos, bool black){
    return mask_to_index(pos->pieces[KING] & pos->colors[black]);
}

static force_inline u64 attackers_to(position_t* pos, bool black, i32 index, u64 board){
    u64* pieces = pos->pieces;
    u64 other_pieces = pos->colors[!black];
    return ( (pseudo_legal_attacks[black ? BLACK_PAWN_POS : WHITE_PAWN_POS][index] & pieces[PAWN])
           | (pseudo_legal_attacks[KNIGHT][index] & pieces[KNIGHT])
           | (pseudo_legal_attacks[KING][index]   & pieces[KING])
           | (bishop_moves(board, index) & (pieces[BISHOP] | pieces[QUEEN]))
           | (rook_moves(board, index)   & (pieces[ROOK]   | pieces[QUEEN])) ) & other_pieces;
}

bool in_check(position_t* pos){
    return pos->checkers != 0;
}
bool in_check(position_t* pos, bool black){
    if(black == pos->blacks_turn){
        return pos->checkers != 0;
    }
    return attackers_to(pos, black, king_index(pos, black), pos->all_pieces) != 0;
}

// calculate squares non king pieces may move to
static inline void calculate_check_evasion_mask(position_t* pos, bool black){
    i32 king = king_index(pos, black);
    u64 checkers = attackers_to(pos, black, king, pos->all_pieces);
    pos->checkers = checkers;
    if(!checkers){ // everything if not in check
        pos->check_mask = ~0ull;
    }else if(checkers & (checkers - 1)){ // nothing if double check
        pos->check_mask = 0;
    }else{ // checker + squares between if single check
        pos->check_mask = checkers | rays[mask_to_index(checkers)][king];
    }
}

// squares a pinned piece may move to (through king)
static force_inline u64 pin_line(position_t* pos, bool black, i32 from){
    if(pos->pinneds[black] & (1ull << from)){
        return lines[king_index(pos, black)][from];
    }
    return ~0ull;
}



static force_inline move_t create_move(bool black, i32 from, i32 to, move_type_e move_type, piece_t piece, i32 spec1, i32 spec2){
    return (move_t)(from  << MOVE_FROM_POS  | to    << MOVE_TO_POS    | move_type << MOVE_TYPE_POS
                  | black << MOVE_COLOR_POS | piece << MOVE_PIECE_POS
                  | spec1 << MOVE_SPEC1_POS | spec2 << MOVE_SPEC2_POS);
}

static force_inline u64 get_castling_mask(position_t* pos, bool black, bool castle_type, u64 empties, u64 attacks){
    // castling is not possible
    if(pos->lost_castling_rights[black][castle_type])   return 0;

    // necessary squares need to be available
    u64 need_empty = castle_masks[black][castle_type];
    if((need_empty & empties) != need_empty)            return 0;
    if(castle_safe_masks[black][castle_type] & attacks) return 0;

    // update_castling_rights already invalidates these squares
    // if(!(pos->pieces[ROOK] & pos->colors[black] & castle_rook_from[black][castle_type])) return 0;

    // castling is possible
    return castle_pos[black][castle_type];
}

// targets excluding pawn push, castling and enpassant
static force_inline u64 piece_targets(position_t* pos, bool black, i32 from, piece_t piece, bool legal){
    u64 color_pieces = pos->colors[black];
    u64 board = pos->all_pieces;
    u64 from_mask = 1ull << from;
    u64 mask = 0;
    switch(piece){
    case PAWN:
        mask = pawns_attack(black, from_mask) & pos->colors[!black];
        break;
    case KNIGHT:
        mask = knights_attack(from_mask);
        break;
    case BISHOP:
        mask = bishop_moves(board, from);
        break;
    case ROOK:
        mask = rook_moves(board, from);
        break;
    case QUEEN:
        mask = queen_moves(board, from);
        break;
    case KING:
        mask = kings_attack(from_mask) & ~color_pieces;
        if(legal) mask &= ~pos->all_pseudo_attacks;
        return mask;
    default: break;
    }
    mask &= ~color_pieces;
    if(legal) mask &= pos->check_mask & pin_line(pos, black, from);
    return mask;
}

static force_inline u64 pawn_push_targets(position_t* pos, bool black, i32 from, bool legal){
    u64 mask = pawns_steps(~pos->all_pieces, black, 1ull << from);
    if(legal) mask &= pos->check_mask & pin_line(pos, black, from);
    return mask;
}

static force_inline u64 enpassant_target(position_t* pos, bool black, i32 from, bool legal){
    u64 enpassantable = pos->enpassantable;
    if(!enpassantable || !(pawns_attack(black, 1ull << from) & enpassantable & enpassantable_squares[black])) return 0;
    if(legal){
        // simulate the capture to check if possible
        i32 to = mask_to_index(enpassantable);
        u64 captured = 1ull << (to + (black ? 8 : -8));
        u64 board = (pos->all_pieces ^ (1ull << from) ^ captured) | enpassantable;
        if(attackers_to(pos, black, king_index(pos, black), board) & ~captured) return 0;
    }
    return enpassantable;
}

static i32 add_promotions(move_t* moves, i32 count, bool black, i32 from, i32 to, i32 captured){
    moves[count++] = create_move(black, from, to, PROMOTION, PAWN, QUEEN,  captured);
    moves[count++] = create_move(black, from, to, PROMOTION, PAWN, KNIGHT, captured);
    moves[count++] = create_move(black, from, to, PROMOTION, PAWN, ROOK,   captured);
    moves[count++] = create_move(black, from, to, PROMOTION, PAWN, BISHOP, captured);
    return count;
}

// captures_only: captures, en passant and promotions, used by quiescence search
static force_inline i32 fill_piece_moves(position_t* pos, i32 from, piece_t piece, move_t* moves, i32 move_count, bool legal, bool captures_only){
    bool black = pos->blacks_turn;
    i32 to, captured;

    u64 other_pieces = pos->colors[!black];
    u64 mask = piece_targets(pos, black, from, piece, legal);
    if(captures_only) mask &= other_pieces;

    while(mask){
        to = extract_piece(&mask);
        u64 to_mask = 1ull << to;
        if(to_mask & other_pieces){ // only captures need to know what is captured
            captured = piece_at(pos, to);
            if(piece == PAWN && (to_mask & RANK_18)){
                move_count = add_promotions(moves, move_count, black, from, to, captured);
            }else{
                moves[move_count++] = create_move(black, from, to, CAPTURE, piece, 0, captured);
            }
        }else{
            moves[move_count++] = create_move(black, from, to, MOVE, piece, 0, 0);
        }
    }

    if(piece == PAWN){
        mask = pawn_push_targets(pos, black, from, legal);
        if(captures_only) mask &= RANK_18;

        while(mask){
            to = extract_piece(&mask);
            if((1ull << to) & RANK_18){
                move_count = add_promotions(moves, move_count, black, from, to, 0);
            }else if(abs(to - from) == 16){
                moves[move_count++] = create_move(black, from, to, DOUBLE_PUSH, piece, (from + to) >> 1, 0);
            }else{
                moves[move_count++] = create_move(black, from, to, PUSH, piece, 0, 0);
            }
        }
        mask = enpassant_target(pos, black, from, legal);
        if(mask){
            to = mask_to_index(mask);
            moves[move_count++] = create_move(black, from, to, ENPASSANT, piece, to + (black ? 8 : -8), PAWN);
        }
    }else if(piece == KING && !captures_only && !(legal && pos->checkers)){
        u64 attacks = legal ? pos->all_pseudo_attacks : 0;
        for(i32 type = CASTLE_OOO; type <= CASTLE_OO; type++){
            mask = get_castling_mask(pos, black, type, ~pos->all_pieces, attacks);
            if(mask){
                to = mask_to_index(mask);
                i32 rook_from = (type == CASTLE_OOO) ? to - 2 : to + 1;
                i32 rook_to   = (from + to) >> 1;
                moves[move_count++] = create_move(black, from, to, CASTLING, piece, rook_from, rook_to);
            }
        }
    }
    return move_count;
}

static force_inline i32 fill_moves(position_t* pos, move_t* moves, bool legal, bool captures_only){
    if(legal) ensure_setup(pos);
    u64 color_pieces = pos->colors[pos->blacks_turn];
    u64 piece_mask;
    i32 index, move_count = 0;
    for(piece_t p = PIECE_FROM; p < PIECE_MAX; p++){
        piece_mask = pos->pieces[p] & color_pieces;
        while(piece_mask){
            index = extract_piece(&piece_mask);
            move_count = fill_piece_moves(pos, index, p, moves, move_count, legal, captures_only);
        }
    }
    return move_count;
}

static inline i32 fill_piece_pseudo_legal_moves(position_t* pos, i32 from, piece_t piece, move_t* moves, i32 move_count){
    return fill_piece_moves(pos, from, piece, moves, move_count, false, false);
}
static inline i32 fill_piece_legal_moves(position_t* pos, i32 from, piece_t piece, move_t* moves, i32 move_count){
    return fill_piece_moves(pos, from, piece, moves, move_count, true, false);
}
static inline i32 fill_pseudo_legal_moves(position_t* pos, move_t* moves){
    return fill_moves(pos, moves, false, false);
}
static inline i32 fill_legal_moves(position_t* pos, move_t* moves){
    return fill_moves(pos, moves, true, false);
}

// returns move count
i32 get_moves(position_t* pos, move_t* moves, bool legal){
    if(legal) return fill_moves(pos, moves, true, false); // so its inlined
    return fill_moves(pos, moves, false, false);
}

// legal captures, en passant and promotions only (for quiescence search)
i32 get_captures(position_t* pos, move_t* moves){
    return fill_moves(pos, moves, true, true);
}


static inline u64 attack_mask(position_t* pos, bool black, u64 piece_mask, piece_t piece, bool legal){
    if(legal) ensure_setup(pos);
    u64 mask = 0;
    i32 from;
    while(piece_mask){
        from = extract_piece(&piece_mask);
        mask |= piece_targets(pos, black, from, piece, legal);
        if(piece == PAWN) mask |= enpassant_target(pos, black, from, legal);
    }
    return mask;
}
static inline u64 turns_mask(position_t* pos, bool black, u64 piece_mask, piece_t piece, bool legal){
    if(legal) ensure_setup(pos);
    u64 mask = attack_mask(pos, black, piece_mask, piece, legal);
    if(piece == PAWN){
        while(piece_mask){
            mask |= pawn_push_targets(pos, black, extract_piece(&piece_mask), legal);
        }
    }else if(piece == KING && piece_mask && !(legal && pos->checkers)){
        u64 attacks = legal ? pos->all_pseudo_attacks : 0;
        mask |= get_castling_mask(pos, black, CASTLE_OOO, ~pos->all_pieces, attacks)
              | get_castling_mask(pos, black, CASTLE_OO,  ~pos->all_pieces, attacks);
    }
    return mask;
}
u64 get_legal_attack(position_t* pos, bool black, u64 piece_mask, piece_t piece){
    return attack_mask(pos, black, piece_mask, piece, true);
}
u64 get_legal_turns(position_t* pos, bool black, u64 piece_mask, piece_t piece){
    return turns_mask(pos, black, piece_mask, piece, true);
}
u64 get_pseudo_legal_turns(position_t* pos, bool black, u64 piece_mask, piece_t piece){
    return turns_mask(pos, black, piece_mask, piece, false);
}
u64 get_color_legal_turns(position_t* pos, bool black){
    u64 color_pieces = pos->colors[black];
    u64 mask = 0;
    for(piece_t piece = PIECE_FROM; piece < PIECE_MAX; piece++){
        mask |= get_legal_turns(pos, black, pos->pieces[piece] & color_pieces, piece);
    }
    return mask;
}
static inline u64 get_index_legal_turns(position_t* pos, bool black, i32 index, piece_t piece){
    return get_legal_turns(pos, black, 1ull << index, piece);
}

bool is_checkmate(position_t* pos){
    if(!in_check(pos)){
        return false;
    }
    return !get_color_legal_turns(pos, pos->blacks_turn); // if any turns, then not checkmate
}


void setup_next_turn(position_t* pos){
    pos->all_pieces = pos->colors[CWHITE] | pos->colors[CBLACK];
    fill_pseudo_legal_attacks(pos);                          // attacks of the side NOT to move
    calculate_pinned(pos, pos->blacks_turn);                 // for legal turns
    calculate_check_evasion_mask(pos, pos->blacks_turn);     // for legal turns
    pos->full_setup_pending = false;
}


static inline u64 splitmix64(u64* state){
    u64 v = (*state += 0x9E3779B97F4A7C15ULL);
    v = (v ^ (v >> 30)) * 0xBF58476D1CE4E5B9ULL;
    v = (v ^ (v >> 27)) * 0x94D049BB133111EBULL;
    return v ^ (v >> 31);
}
void init_zobrist(){
    u64 state = 0xA06E1BB74A3523C1ULL; // random seed
    for(i32 c = 0; c < CCOLOR_COUNT; c++){
        for(i32 p = 0; p < PIECE_MAX; p++){
            for(i32 i = 0; i < 64; i++){
                zobrist_pieces[c][p][i] = splitmix64(&state);
            }
        }
    }
    for(i32 i = 0; i < 16; i++) zobrist_castling[i] = splitmix64(&state);
    for(i32 i = 0; i < 64; i++) zobrist_enpassant[i] = splitmix64(&state);
    zobrist_side = splitmix64(&state);
}

static inline i32 castling_index(position_t* pos){
    return  pos->lost_castling_rights[CWHITE][CASTLE_OOO]
         | (pos->lost_castling_rights[CWHITE][CASTLE_OO]  << 1)
         | (pos->lost_castling_rights[CBLACK][CASTLE_OOO] << 2)
         | (pos->lost_castling_rights[CBLACK][CASTLE_OO]  << 3);
}

static inline void update_castling_rights(position_t* pos, i32 from, i32 to){
    u64 mask = (1ull << from) | (1ull << to);
    if(!(mask & CASTLING_SQUARES)) return; // very likely

    i32 old_index = castling_index(pos);
    pos->lost_castling_rights[CWHITE][CASTLE_OOO] |= (mask & (A1 | E1)) != 0;
    pos->lost_castling_rights[CWHITE][CASTLE_OO]  |= (mask & (H1 | E1)) != 0;
    pos->lost_castling_rights[CBLACK][CASTLE_OOO] |= (mask & (A8 | E8)) != 0;
    pos->lost_castling_rights[CBLACK][CASTLE_OO]  |= (mask & (H8 | E8)) != 0;
    pos->hash ^= zobrist_castling[old_index] ^ zobrist_castling[castling_index(pos)];
}


// only when a position is set up
u64 calculate_hash(position_t* pos){
    u64 hash = 0;
    for(i32 color = 0; color < CCOLOR_COUNT; color++){
        for(i32 p = PIECE_FROM; p < PIECE_MAX; p++){
            u64 mask = pos->pieces[p] & pos->colors[color];
            while(mask){
                hash ^= zobrist_pieces[color][p][extract_piece(&mask)];
            }
        }
    }
    if(pos->blacks_turn) hash ^= zobrist_side;
    hash ^= zobrist_castling[castling_index(pos)];
    u64 enpassant = pos->enpassantable;
    if(enpassant) hash ^= zobrist_enpassant[mask_to_index(enpassant)];
    return hash;
}
void reset_history(position_t* pos){
    pos->halfmove_clock = 0;
    pos->history_count = 0;
    pos->hash = calculate_hash(pos);
    position_history[0] = pos->hash;
}

// current position occurrance count since the last irreversible move (pawn or capture)
// same position cant occur 2 halfmoves ago (e.g. you move then opponent), so 4 ago
i32 repetition_count(position_t* pos){
    i32 count = 1;
    i32 lowest = pos->history_count - pos->halfmove_clock;
    if(lowest < 0) lowest = 0;
    for(i32 i = pos->history_count - 4; i >= lowest; i -= 2){
        if(position_history[i] == pos->hash){
            count++;
        }
    }
    return count;
}
// a single repetition inside the search tree is treated as a draw
bool has_repeated(position_t* pos, i32 tree_start){
    i32 count = 1;
    i32 lowest = pos->history_count - pos->halfmove_clock;
    if(lowest < 0) lowest = 0;
    for(i32 i = pos->history_count - 4; i >= lowest; i -= 2){
        if(position_history[i] == pos->hash){
            if(i >= tree_start || ++count >= 3) return true;
        }
    }
    return false;
}
bool is_threefold_repetition(position_t* pos){
    i32 count = 1;
    i32 lowest = pos->history_count - pos->halfmove_clock;
    if(lowest < 0) lowest = 0;
    for(i32 i = pos->history_count - 4; i >= lowest; i -= 2){
        if(position_history[i] == pos->hash){
            if(++count >= 3)
                return true;
        }
    }
    return false;
}
// bool is_fifty_move_draw(position_t* pos){
//     return pos->halfmove_clock >= 100; // 100 half moves = 50 moves of each side
// }
// // always check checkmate and absense of legal moves first
// bool is_draw(position_t* pos){
//     return is_threefold_repetition(pos) || is_fifty_move_draw(pos);
// }

// 100 half moves = 50 moves of each side
#define is_fifty_move_draw(pos) ((pos)->halfmove_clock >= 100)
// but always check checkmate and absense of legal moves first
#define is_draw(pos) (is_threefold_repetition(pos) || is_fifty_move_draw(pos))

// makes a legal move and cheap updates: pieces, hash, history, checkers
// enemy attacks and pins are calculated at ensure_setup, so search leaves never pay for them
void do_move_lazy(position_t* pos, move_t move){
    bool black = move_get_color(move);
    piece_t piece = move_get_piece(move);
    i32 from = move_get_from(move);
    i32 to = move_get_to(move);
    move_type_e move_type = move_get_type(move);
    u64 from_mask = 1ull << from;
    u64 to_mask = 1ull << to;
    u64 hash = pos->hash ^ zobrist_side;
    bool irreversible = piece == PAWN;

    u64* pieces = pos->pieces;
    u64* colors = pos->colors;
    piece_t* pieces_in_squares = pos->pieces_in_squares;

    if(pos->enpassantable) hash ^= zobrist_enpassant[mask_to_index(pos->enpassantable)];
    pos->enpassantable = 0;

    if(to_mask & colors[!black]){ // capture
        piece_t victim = pieces_in_squares[to]; // equivalent to piece_at(pos, to)
        pieces[victim] ^= to_mask;
        colors[!black] ^= to_mask;
        hash ^= zobrist_pieces[!black][victim][to];
        irreversible = true;
    }

    pieces_in_squares[from] = EMPTY_PIECE;
    colors[black] ^= from_mask | to_mask;
    if(move_type == PROMOTION){
        piece_t promoted = move_get_spec1(move);
        pieces[PAWN] ^= from_mask;
        pieces[promoted] ^= to_mask;
        pieces_in_squares[to] = promoted;
        hash ^= zobrist_pieces[black][PAWN][from] ^ zobrist_pieces[black][promoted][to];
    }else{
        pieces[piece] ^= from_mask | to_mask;
        pieces_in_squares[to] = piece;
        hash ^= zobrist_pieces[black][piece][from] ^ zobrist_pieces[black][piece][to];
    }

    pos->hash = hash;
    update_castling_rights(pos, from, to); // also updates pos->hash

    switch(move_type) {
    case DOUBLE_PUSH: {
        i32 enpassant = move_get_spec1(move);
        pos->enpassantable = 1ull << enpassant;
        pos->hash ^= zobrist_enpassant[enpassant];
    } break;
    case ENPASSANT: {
        i32 captured = move_get_spec1(move);
        pieces[PAWN] ^= 1ull << captured;
        colors[!black] ^= 1ull << captured;
        pieces_in_squares[captured] = EMPTY_PIECE;
        pos->hash ^= zobrist_pieces[!black][PAWN][captured];
    } break;
    case CASTLING: {
        i32 rook_from = move_get_spec1(move);
        i32 rook_to = move_get_spec2(move);
        u64 rook_mask = (1ull << rook_from) | (1ull << rook_to);
        pieces[ROOK] ^= rook_mask;
        colors[black] ^= rook_mask;
        pieces_in_squares[rook_from] = EMPTY_PIECE;
        pieces_in_squares[rook_to] = ROOK;
        pos->hash ^= zobrist_pieces[black][ROOK][rook_from] ^ zobrist_pieces[black][ROOK][rook_to];
        irreversible = true;
    } break;
    default:
        break;
    }

    pos->blacks_turn = !pos->blacks_turn;
    pos->halfmove_clock = irreversible ? 0 : pos->halfmove_clock + 1;
    pos->all_pieces = pos->colors[CWHITE] | pos->colors[CBLACK];
    calculate_check_evasion_mask(pos, pos->blacks_turn); // checkers, needed for mate detection
    pos->full_setup_pending = true;
    pos->turns_passed++;

    if(pos->history_count < MAX_HISTORY){
        position_history[++pos->history_count] = pos->hash;
    }
}

void do_move(position_t* pos, move_t move){ // does legal move, position fully set up afterwards
    do_move_lazy(pos, move);
    ensure_setup(pos);
}

// passes the turn for null move pruning in search
void do_null_move(position_t* pos){
    pos->hash ^= zobrist_side;
    if(pos->enpassantable) pos->hash ^= zobrist_enpassant[mask_to_index(pos->enpassantable)];
    pos->enpassantable = 0;

    pos->blacks_turn = !pos->blacks_turn;
    pos->halfmove_clock = 0;
    calculate_check_evasion_mask(pos, pos->blacks_turn);
    pos->full_setup_pending = true;
    pos->turns_passed++;

    if(pos->history_count < MAX_HISTORY){
        position_history[++pos->history_count] = pos->hash;
    }
}

bool can_play_move(position_t* pos, move_t move){
    // check if our color and check if piece is on correct place
    if(pos->blacks_turn != move_get_color(move))                                     return false;
    if(pos->pieces_in_squares[move_get_from(move)] != (piece_t)move_get_piece(move)) return false;

    // slow
    move_t moves[MAX_MOVES];
    i32 moves_count = get_moves(pos, moves, true);
    for(i32 i = 0; i < moves_count; i++){
        if(moves[i] == move) return true;
    }
    return false;
}

void reset_position(position_t* pos){
    *pos = (position_t){ 0 };

    for(i32 i = 0; i < 8; i++){
        put_piece(pos, CWHITE, PAWN, 8 + i);
    }
    put_piece(pos, CWHITE, ROOK, 0);
    put_piece(pos, CWHITE, ROOK, 7);
    put_piece(pos, CWHITE, KNIGHT, 1);
    put_piece(pos, CWHITE, KNIGHT, 6);
    put_piece(pos, CWHITE, BISHOP, 2);
    put_piece(pos, CWHITE, BISHOP, 5);
    put_piece(pos, CWHITE, QUEEN, 3);
    put_piece(pos, CWHITE, KING, 4);

    for(i32 i = 0; i < 8; i++){
        put_piece(pos, CBLACK, PAWN, 48 + i);
    }
    put_piece(pos, CBLACK, ROOK, 56);
    put_piece(pos, CBLACK, ROOK, 63);
    put_piece(pos, CBLACK, KNIGHT, 57);
    put_piece(pos, CBLACK, KNIGHT, 62);
    put_piece(pos, CBLACK, BISHOP, 58);
    put_piece(pos, CBLACK, BISHOP, 61);
    put_piece(pos, CBLACK, QUEEN, 59);
    put_piece(pos, CBLACK, KING, 60);
}

void setup_position(position_t* pos){
    setup_next_turn(pos);
    reset_history(pos);
    // setup_board();
}
void chess_reset(position_t* pos){
    reset_position(pos);
    setup_position(pos);
}

void fill_pseudo_legal_attacks_table(){
    position_t empty_position = { 0 };
    u64 piece_mask;
    for(piece_t p = PIECE_FROM; p < PIECE_MAX; p++){
        for(i32 i = 0; i < 64; i++){
            piece_mask = 1ull << i;
            empty_position.all_pieces = piece_mask;
            if(p == PAWN){
                pseudo_legal_attacks[WHITE_PAWN_POS][i] = get_pseudo_legal_attack(&empty_position, CWHITE, piece_mask, p);
                pseudo_legal_attacks[BLACK_PAWN_POS][i] = get_pseudo_legal_attack(&empty_position, CBLACK, piece_mask, p);
            }else{
                pseudo_legal_attacks[p][i] = get_pseudo_legal_attack(&empty_position, false, piece_mask, p);
            }
        }
    }
}


void fill_pseudo_legal_attackers_table(){
    position_t empty_position = { 0 };
    u64 piece_mask, mask;
    i32 index;
    for(piece_t p = PIECE_FROM; p < PIECE_MAX; p++){
        for(i32 i = 0; i < 64; i++){
            piece_mask = 1ull << i;
            empty_position.all_pieces = piece_mask;

            if(p == PAWN){
                mask = get_pseudo_legal_attack(&empty_position, CWHITE, piece_mask, p);
                while(mask){
                    index = extract_piece(&mask);
                    pseudo_legal_attackers[WHITE_PAWN_POS][index] |= piece_mask;
                    all_pseudo_legal_attackers[CWHITE][index] |= piece_mask;
                }
                mask = get_pseudo_legal_attack(&empty_position, CBLACK, piece_mask, p);
                while(mask){
                    index = extract_piece(&mask);
                    pseudo_legal_attackers[BLACK_PAWN_POS][index] |= piece_mask;
                    all_pseudo_legal_attackers[CBLACK][index] |= piece_mask;
                }
            }else{
                mask = get_pseudo_legal_attack(&empty_position, false, piece_mask, p);
                while(mask){
                    index = extract_piece(&mask);
                    pseudo_legal_attackers[p][index] |= piece_mask;
                    all_pseudo_legal_attackers[CWHITE][index] |= piece_mask;
                    all_pseudo_legal_attackers[CBLACK][index] |= piece_mask;
                }
            }
        }
    }
}

void fill_enpassant_affected_pawns_table(){
    i32 wi, bi;
    for(i32 i = 0; i < 8; i++){
        wi = 16 + i;
        bi = 40 + i;
        if(i != 0){
            enpassant_affected_pawns[wi] |= 1ull << (wi + 7);
            enpassant_affected_pawns[bi] |= 1ull << (bi - 9);
        }
        if(i != 7){
            enpassant_affected_pawns[wi] |= 1ull << (wi + 9);
            enpassant_affected_pawns[bi] |= 1ull << (bi - 7);
        }
        enpassant_affected_pawns[wi] |= 1ull << (wi + 8);
        enpassant_affected_pawns[bi] |= 1ull << (bi - 8);
    }
}

void init_chess(){
    fill_rays_table();

    fill_bishop_table();
    fill_rook_table();
    fill_lines_table();

    fill_pseudo_legal_attacks_table();
    fill_pseudo_legal_attackers_table();
    fill_enpassant_affected_pawns_table();

    init_zobrist();
}