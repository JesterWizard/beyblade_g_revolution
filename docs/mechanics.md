# Battle mechanics

How launch RPM is built, and what Attack, Defense, and Endurance actually do. The numbers below are the retail formulas (`sub_08031728`, `sub_0803CECC`, `sub_0802FFAC`, `sub_080300D4`, `sub_0803E2AC`). The status screen and the tutorial never state them.

Two different “experience” counters exist, and only one of them is the launch base. Level is a label on top of a counter. It is not a multiplier.

## The four numbers on the status screen

| What the screen calls it | What it actually is | Does it change launch RPM? |
|---|---|---|
| Bit-beast experience | Signed halfword on the blade record, 0..16383 | Yes. It is the launch base. |
| Character experience | `MainWork.expPoints`, also capped at 16383 | No, while the blade has a bit-beast record. |
| Level | A bracket lookup on one of those two counters | No. It only shifts the computer’s timing table. |
| Strength | Character strength, 0..99 | Yes. Added after experience is scaled by the launch. |

Stamina, Power, and Speed on the HUD are the launch timing meters. They are not Attack, Defense, or Endurance.

## Launch RPM

`sub_0803CECC` builds the player’s launch RPM from four inputs:

- `base` — bit-beast experience
- `power` — the first launch meter, stored as `100` minus the amount you missed the window (`sub_0803C500`)
- `boost` — the second launch meter, stored as the value you actually hit (`sub_0803C5DC`)
- `strength` — character strength, 0..99

```
quot = (base << 16) / 25600
rpm  = (quot * (power << 8)) >> 16
rpm += (quot * (boost << 8)) >> 16
rpm += strength * (power + boost)
```

`25600` is `200 << 7`. Experience is scaled into a quotient first, then power and boost each take a fraction of that quotient. Strength is not scaled by experience. It is added as `strength * (power + boost)`.

If both meters are above 94, the result is increased by a quarter (`rpm += rpm >> 2`), and the spin ceiling for that side is raised by 3072. The ordinary ceiling written just before the formula is 9216.

A fresh blade (base 0, power 80, boost 75, strength 10) launches at 1550. The same launch with 1000 experience and strength 20 is 5400. Experience 16383 with power 80, boost 75, and strength 50 is 33143. A perfect launch (both meters 100, strength 99) on that same experience is 65705, including the quarter bonus.

The opponent does not use your meters or your character strength. Its power is a random 80..99, its boost is a random 75..99, and the strength term is the blade record’s own strength byte, not the 0..99 character stat. The same multiply applies, including the quarter bonus when both of its random meters are above 94.

The code does add a second halfword from the blade record onto the base before the multiply. Every blade definition in the ROM stores 0 there, and the experience award only writes the bit-beast experience field, so that add contributes nothing.

### What the launch number is spent on

The value is the pool the clash spends. Releasing an attack also spends RPM immediately, before anyone is hit:

| Charge counter | Attack power | RPM spent on release |
|---|---|---|
| 0..29 (low) | Attack × 1 | Endurance / 2 |
| 30..59 (medium) | Attack × 2 | Endurance |
| 60..120 (high) | Attack × 3 | Endurance × 3 / 2 |

Charge is the counter sampled when the attack button is released (`sub_08030388`). Past 120 the release is not one of these three attacks.

### Two overflow bugs

The launch shift and the per-frame spin step are both signed. A base of 32768 or more makes `(base << 16)` negative, so the launch itself comes out negative (32768 with the 80/75/50 example is −43041). Separately, once the stored RPM is 32768 or more, the spin step (`sub_080302E0`) shifts it into a negative delta and the fight treats the blade as stopped. Experience 16383 with an ordinary launch already produces 33143, which is past that line. The digits on screen stop at 99999 because the field is five digits wide. The battle is using the signed value underneath.

## Character experience and level

Character experience and bit-beast experience are awarded together by `BtlApplyClampedScore`, then capped at 16383. The score starts as one of the two counters divided by 10, then clamped to 20..100. One pool receives the whole score and the other receives a quarter:

- When the award is aimed at you, character experience gets the score and the bit beast gets a quarter.
- When it is aimed at a blade, that blade’s bit-beast experience gets the score and character experience gets a quarter.

Character experience is the launch base only on the fallback path where the blade has no bit-beast record. An equipped blade has one, so raising “your EXP” does not raise RPM. Raising the bit beast’s experience does.

Level is `ExpBracket` (`sub_08042BE8`) over a counter. Character level uses character experience. Bit-beast level uses bit-beast experience. The table is pairs of (level, lower bound):

| Experience | Level |
|---|---|
| 0–99 | 0 |
| 100–249 | 1 |
| 250–349 | 2 |
| 350–899 | 3 |
| 900–1199 | 4 |
| 1200–1499 | 5 |
| 1500–1599 | 6 |
| 1600–1699 | 7 |
| 1700–1799 | 8 |
| 1800–1899 | 9 |
| 1900–1999 | 10 |
| 2000–2299 | 11 |
| 2300–2399 | 12 |
| 2400–2499 | 13 |
| 2500–3499 | 14 |
| 3500–3999 | 15 |
| 4000 and above | none (`-1`) |

Nothing in the launch formula reads that level. The HUD lookup returns −1 from 4000 upward, which is why the level display breaks there even though experience and RPM keep working. The computer’s AI is the one place level changes a battle number: the blade’s type picks a timing table, and the bit-beast level is subtracted from each of its five entries (`sub_08033AE4`).

## Attack, Defense, and Endurance

These are three sums, not a single hidden type stat. Each of the three parts contributes a small triple from a ROM table (the values are mostly 1..4):

| Part | Record field | Examples |
|---|---|---|
| Attack ring | byte `+0x1D` | Cross Dragon, Wing Cross |
| Weight disk | byte `+0x1E` | 6 Balance, 8 Heavy, 10 Wide |
| Blade base | byte `+0x20` | Flat, Sharp, Bearing |

```
attack    = ring.attack    + disk.attack    + base.attack    + baseExp / 100
defense   = ring.defense   + disk.defense   + base.defense   + baseExp / 100
endurance = ring.endurance + disk.endurance + base.endurance + baseExp / 100
```

`baseExp / 100` is integer division of the same launch base, so every 100 bit-beast experience adds 1 to all three. The status screen’s star rating for a column is that column’s sum divided by 3, minus 1 (`sub_0803E328` and the two functions beside it). The type name does not use the experience bonus. It looks only at the three part sums (`sub_0803E2AC`):

| Shown type | Rule, first match wins |
|---|---|
| Attack | attack sum > 8 |
| Defence | defense sum > 8 |
| Endurance | defense sum > 5 and endurance sum > 5 |
| Combination | anything else |

Attack is tested first, so a blade that is high in both attack and defense is Attack. A high endurance sum with defense of 5 or less is Combination, not Endurance. Endurance as a type name means “defense is in the 6..8 band and endurance is above 5.”

### What they do when you clash

The resolver (`sub_080300D4`, then `sub_0802FFAC`) turns the chosen action into a power, then subtracts the opponent’s power from your RPM.

| Action | Power |
|---|---|
| Attack, low / medium / high charge | Attack × 1 / × 2 / × 3 |
| Defense, same three charge steps | Defense × 1 / × 2 / × 3 |
| Both sides attacking | both powers are halved before anything else |
| One side defending | each power is reduced by the other, then clamped at 0 |
| Bit-beast action | Endurance × 3 |
| Combination action | Attack / 2 |

Defending spends your defense power against their attack. If yours is larger, their hit becomes 0 and you deal the difference. If theirs is larger, you take what is left and deal nothing back. Two attackers both lose half of their power, then each loses the other’s remaining power from RPM.

Endurance is the cushion and the attack cost. Incoming power above your endurance sum adds half of the excess to a knockback counter. The attack-release costs in the table above are also fractions of that same endurance sum, taken off RPM when the move starts.

The type name also picks the computer’s behavior. Attack, Defence, Endurance, and Combination each load a different five-number timing table, and the bit-beast level is subtracted from every entry. That changes when the AI acts. It does not change the damage formula, which always uses the three sums.
