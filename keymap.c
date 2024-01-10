/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 Elliot Powell  <@e11i0t23>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  XCODEBUILD = SAFE_RANGE,
  BSP_DEL,
  TAB_ESC
};

#define LCTLA  LCTL_T(KC_A)
#define LALTS  LALT_T(KC_S)
#define LGUID  LGUI_T(KC_D)

#define GUIK RGUI_T(KC_K) 
#define ALTL RALT_T(KC_L)
#define CTLSCL RCTL_T(KC_SCLN)

#define BKSPLOW LT(_LOWER, KC_BSPC)
#define ENTRAI LT(_RAISE, KC_ENT)
#define UNDRAI LT(_RAISE, KC_UNDS)

#define SFTSPC  LSFT_T(KC_SPACE)
#define SFTENT  RSFT_T(KC_ENT)

#define GUINUBS LGUI_T(KC_NUBS)
#define HYPENT  HYPR(KC_TILD)
#define ADJ LT(_ADJUST, KC_NO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Y,    KC_U,    KC_I,    KC_O,   KC_P, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    LCTLA,   LALTS,   LGUID,    KC_F,    KC_G,                                      KC_H,    KC_J,    GUIK,    ALTL, CTLSCL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          GUINUBS, BKSPLOW,  SFTSPC,     SFTSPC,  ENTRAI, KC_UNDS
  ),

  [_LOWER] = LAYOUT_split_3x5_3(  
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TAB_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                               KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                KC_GRV, KC_ESC,  KC_QUOT, XXXXXXX, XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          GUINUBS, _______,  SFTSPC,     SFTSPC,     ADJ, KC_TILD
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x5_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                               KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_GRV, KC_QUOT, XXXXXXX, XXXXXXX, XXXXXXX,                                XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                               KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          TAB_ESC,     ADJ,  SFTSPC,     SFTSPC, _______, HYPENT
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x5_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, KC_VOLU,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, KC_VOLD,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          GUINUBS, _______,  KC_SPC,     KC_ENT, _______, HYPENT
                                      //`--------------------------'  `--------------------------'
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint8_t saved_mods   = 0;

  switch (keycode) {
    case XCODEBUILD:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LGUI)SS_DOWN(X_G)SS_UP(X_LSFT)SS_UP(X_LCTL)SS_UP(X_LGUI)SS_UP(X_G));
        }
        return false;
        break;
    case BSP_DEL:
        if (record->event.pressed) {
             saved_mods = get_mods() & MOD_MASK_SHIFT;

            if (saved_mods == MOD_MASK_SHIFT) {  // Both shifts pressed
                register_code(KC_DEL);
            } else if (saved_mods) {   // One shift pressed
                del_mods(saved_mods);  // Remove any Shifts present
                register_code(KC_DEL);
                add_mods(saved_mods);  // Add shifts again
            } else {
                register_code(KC_BSPC);
            }
        } else {
            unregister_code(KC_DEL);
            unregister_code(KC_BSPC);
        }
        return false;
        break;
    case TAB_ESC:
        if (record->event.pressed) {
             saved_mods = get_mods() & MOD_MASK_SHIFT;         if (saved_mods) {   // One shift pressed
                del_mods(saved_mods);  // Remove any Shifts present
                register_code(KC_ESC);
                add_mods(saved_mods);  // Add shifts again
            } else {
                register_code(KC_TAB);
            }
        } else {
            unregister_code(KC_ESC);
            unregister_code(KC_TAB);
        }
        return false; 
        break;
  }
  return true;
}
