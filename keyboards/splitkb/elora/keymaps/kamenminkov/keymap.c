/* Copyright 2023 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "action_layer.h"
#include "bitwise.h"
#include "encoder.h"
#include "keycodes.h"
#include "pointing_device/pointing_device_auto_mouse.h"
#include "quantum_keycodes.h"
#include "report.h"
#include "config.h"
#include "quantum.h"
#include "rgb_matrix.h"
#include "splitkb/elora/rev1/config.h"
#include "splitkb/elora/rev1/rev1.h"
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NAV,
    _NUM,
    _RGB,
};

// Aliases for readability
#define NUM MO(_NUM)
#define NAV MO(_NAV)
#define NUM MO(_NUM)
#define RGB MO(_RGB)

#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT MT(MOD_LALT, KC_ENT)

enum custom_keycodes {
    DRAG_SCROLL = QK_KB_0,
};

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_myr(
      KC_ESC  , KC_1 ,  KC_2 ,   KC_3   ,   KC_4   ,   KC_5 ,          KC_LSFT,     KC_RSFT,            KC_6   ,  KC_7    , KC_8   , KC_9  , KC_0   , KC_GRV,
      KC_TAB  , KC_Q ,  KC_W ,   KC_E   ,   KC_R   ,   KC_T ,          KC_LCTL,     KC_RCTL,            KC_Y   ,  KC_U    , KC_I   , KC_O  , KC_P   , KC_MINS,
      KC_LCTL , KC_A ,  KC_S ,   KC_D   ,   KC_F   ,   KC_G ,          KC_LALT,     KC_RALT,            KC_H   ,  KC_J    , KC_K   , KC_L  , KC_SCLN, KC_QUOT,
      KC_LSFT , KC_Z ,  KC_X ,   KC_C   ,   KC_V   ,   KC_B , KC_LBRC, KC_LPRN,     KC_DEL ,   KC_RBRC, KC_N   ,  KC_M    , KC_COMM, KC_DOT, KC_SLSH, KC_EQUAL,
                                 KC_LGUI,   KC_LALT,   NAV  , KC_SPC , KC_SPC   ,   KC_ENT ,   KC_ENT , KC_BSPC,  TO(_NUM), KC_BSLS,

      KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP,   KC_MUTE,                            KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP,    KC_MUTE
    ),

    [_NAV] = LAYOUT_myr(
      KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6      ,           _______, _______,          KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12,
      _______, _______, KC_MPLY, _______, _______, _______    ,           _______, _______,          _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______,
      _______, _______, _______, KC_DEL , _______, DRAG_SCROLL,           _______, _______,          KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
      _______, KC_APP , _______, _______, _______, MO(_RGB)   , _______ , _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG,
                                 _______, _______, TO(_QWERTY), MO(_NUM), _______, _______, _______, _______, TO(_NUM), _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    ),

    [_NUM] = LAYOUT_myr(
      _______, _______, _______, _______, _______, _______    ,          _______, _______,          _______, _______ , _______, _______, _______   , _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______    ,          _______, _______,          _______, KC_7    , KC_8   , KC_9   , KC_KP_PLUS, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______    ,          _______, _______,          _______, KC_4    , KC_5   , KC_6   , _______   , _______,
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, MO(_RGB)   , _______, _______, _______, _______, _______, KC_1    , KC_2   , KC_3   , _______   , _______,
                                 _______, _______, TO(_QWERTY), _______, _______, _______, _______, KC_0   , TO(_RGB), _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    ),

    [_RGB] = LAYOUT_myr(
      _______, _______, _______, _______, _______, _______    ,          _______, _______,          RGB_HUD, RGB_HUI    , RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI,
      _______, _______, _______, _______, _______, _______    ,          _______, _______,          _______, _______    , _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______    ,          _______, _______,          _______, _______    , _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______    , _______, _______, _______, _______, _______, _______    , _______, _______, _______, _______,
                                 _______, _______, TO(_QWERTY), _______, _______, _______, _______, _______, TO(_QWERTY), _______,

      _______, _______, _______, _______,          _______,                   _______, _______, _______, _______,          _______
    )
};
// clang-format on

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t value = rgb_matrix_config.hsv.v;

    for (uint8_t i = led_min; i < led_max; i++) {
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _QWERTY:
                rgb_matrix_set_color(i, value, value, value);
                break;
            case _NAV:
                rgb_matrix_set_color(i, value, 0, 0);
                break;
            case _NUM:
                rgb_matrix_set_color(i, 0, value, 0);
                break;
            case _RGB:
                rgb_matrix_set_color(i, 0, 0, value);
                break;
        }
    }

    return false;
}

bool set_scrolling = false;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == DRAG_SCROLL && record->event.pressed) {
        set_scrolling = !set_scrolling;
    }

    return true;
}

#if defined(ENCODER_MAP_ENABLE)
#    define ENCODER_CCW_CW(ccw, cw) \
        { (cw), (ccw) }

bool encoder_update_user(uint8_t index, bool clockwise) {
    return false;
}

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [2] = {ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [3] = {ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif