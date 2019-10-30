#include QMK_KEYBOARD_H

typedef struct {
  bool is_press_action;
  int state;
} tap;

// Tap Dance states Declarations
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
	DOUBLE_HOLD = 4,
};

// Tap Dance Declarations
enum {
	TD_ESC_GRV = 0,
  CTL_LAYR
};

int cur_dance (qk_tap_dance_state_t *state);

void ql_finished (qk_tap_dance_state_t *state, void *user_data);
void ql_reset (qk_tap_dance_state_t *state, void *user_data);


// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_GRV] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
  [CTL_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		TD(TD_ESC_GRV), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_NO, KC_BSPC,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
		TD(CTL_LAYR), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(1),
		KC_CAPS, KC_LALT, KC_LGUI, KC_SPC, KC_SPC, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

	LAYOUT(
		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_DEL,
		KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_DEC, BL_TOGG, BL_INC, BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
      return SINGLE_TAP;
  } else if (state->count == 2 && state->pressed) {
		return DOUBLE_HOLD;
  }
  else return 8;
}

// Initialize tap structure associated with example tap dance key
static tap ql_tap_state = {
  .is_press_action = true,
  .state = 0
};

// Functions that control what our tap dance key does
void ql_finished (qk_tap_dance_state_t *state, void *user_data) {
  ql_tap_state.state = cur_dance(state);
  switch (ql_tap_state.state) {
    case SINGLE_TAP:
      tap_code(KC_LCTL);
      break;
		case DOUBLE_HOLD:
      layer_on(1);
      break;
  }
};

void ql_reset (qk_tap_dance_state_t *state, void *user_data) {
  // if the key was held down and now is released then switch off the layer
  if (ql_tap_state.state==DOUBLE_HOLD) {
    layer_off(1);
  }
  ql_tap_state.state = 0;
};
