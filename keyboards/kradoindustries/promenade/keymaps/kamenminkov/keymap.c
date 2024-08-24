/*
Copyright 2023 Matt F
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

#include "rgb_matrix.h"
#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "keycodes.h"

// Layer shorthand
enum layer_names {
    _QWE = 0,
    _NAV,
    _NUM,
    _ADJ,
};

#define NAV MO(_NAV)
#define NUM MO(_NUM)
#define ADJ MO(_ADJ)
#define CADL LCA(KC_DEL)
#define PIPE LSFT(KC_BSLS)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_F5,   KC_F12,  KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
        KC_LCTL, KC_A,    KC_S,    KC_D,     KC_F,    KC_G,                      KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,    KC_DEL,  KC_BSLS, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,
        KC_LCTL, KC_LGUI, NAV,     KC_LALT,  NAV,     KC_SPC,  KC_SPC,      KC_ENT,      KC_BSPC, NUM,     PIPE,    KC_BSLS, KC_RCTL
    ),
    [_NAV] = LAYOUT_all(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F12,
        _______, _______, KC_MPLY, _______, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______,
        _______, _______, _______, KC_DEL,  _______, _______,                   KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
        _______, KC_MENU, _______, _______, _______, _______, _______, _______, CADL,    _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, RGB_TOG
    ),
    [_NUM] = LAYOUT_all(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,                   KC_BSPC, KC_4,    KC_5,    KC_6,    _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    _______, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______,      KC_0,    _______, _______, _______, _______
    ),
    [_ADJ] = LAYOUT_all(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAI, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, RGB_SAD, RGB_VAD, RGB_SAI, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, RGB_TOG,     RGB_TOG,      _______, _______, _______, _______, _______
    ),
};
// clang-format on

led_config_t g_led_config = {{
                                 {13, 12, 11, 10, 9, 8, 7},
                                 {0, 1, 2, 3, 4, 5, 6},
                             },
                             {{28, 22},
                              {56, 22},
                              {84, 22},
                              {112, 22},
                              {140, 22},
                              {168, 22},
                              {196, 22},

                              {28, 44},
                              {56, 44},
                              {84, 44},
                              {112, 44},
                              {140, 44},
                              {168, 44},
                              {196, 44}},
                             {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

bool rgb_matrix_indicators_user() {
    uint8_t value = rgb_matrix_config.hsv.v;

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWE:
            rgb_matrix_set_color_all(value, value, value);
            break;
        case _NAV:
            rgb_matrix_set_color_all(value, 0, 0);
            break;
        case _NUM:
            rgb_matrix_set_color_all(0, value, 0);
            break;
        case _ADJ:
            rgb_matrix_set_color_all(0, 0, value);
            break;
    }

    return false;
}