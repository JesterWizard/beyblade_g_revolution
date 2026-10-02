#ifndef GUARD_BGM_H
#define GUARD_BGM_H

/* Background music tracks, the argument of sub_0805FED4. Names for 0-12 and 15-16 are the game's own
 * titles; 13 and 14 are named from where the result screen plays them
 * (sub_08036698: side 1 wins, draw).
 * The overworld picks at random among the first six, up to BGM_A_NEW_DAY. */
#define BGM_BACK_IN_THE_CITY 0
#define BGM_NEW_RIVALS 1
#define BGM_SHADY_ALLEYS 2
#define BGM_A_WALK_IN_THE_PARK 3
#define BGM_DOJO_PRACTICE 4
#define BGM_A_NEW_DAY 5
#define BGM_TITLE 6
#define BGM_BATTLE_THEME_A 7
#define BGM_BATTLE_THEME_B 8
#define BGM_BATTLE_THEME_C 9
#define BGM_BATTLE_THEME_D 10
#define BGM_BATTLE_THEME_E 11
#define BGM_END_OF_BATTLE 12 /* the player wins */
#define BGM_OPPONENT_WINS 13
#define BGM_DRAW 14
#define BGM_FAILED_TO_LAUNCH 15
#define BGM_LOST_BATTLE 16

#define BGM_TRACKS 17

#endif
