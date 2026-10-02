#include "debug_menu.h"

const char *BgmName(unsigned int track)
{
    switch (track) {
    case BGM_BACK_IN_THE_CITY: return "Back In The City";
    case BGM_NEW_RIVALS: return "New Rivals";
    case BGM_SHADY_ALLEYS: return "Shady Alleys";
    case BGM_A_WALK_IN_THE_PARK: return "A Walk In The Park";
    case BGM_DOJO_PRACTICE: return "Dojo Practice";
    case BGM_A_NEW_DAY: return "A New Day";
    case BGM_TITLE: return "Title";
    case BGM_BATTLE_THEME_A: return "Battle Theme A";
    case BGM_BATTLE_THEME_B: return "Battle Theme B";
    case BGM_BATTLE_THEME_C: return "Battle Theme C";
    case BGM_BATTLE_THEME_D: return "Battle Theme D";
    case BGM_BATTLE_THEME_E: return "Battle Theme E";
    case BGM_END_OF_BATTLE: return "End of Battle";
    case BGM_OPPONENT_WINS: return "Opponent Wins";
    case BGM_DRAW: return "Draw";
    case BGM_FAILED_TO_LAUNCH: return "Failed to Launch";
    case BGM_LOST_BATTLE: return "Lost Battle";
    }
    return "?";
}
