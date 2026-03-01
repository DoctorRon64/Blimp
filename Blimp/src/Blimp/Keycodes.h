#pragma once

/* Keyboard key codes mapped to GLFW values (shared across Windows/Linux). */
#define BLIMP_KEY_UNKNOWN            -1
#define BLIMP_KEY_SPACE              32
#define BLIMP_KEY_APOSTROPHE         39  /* ' */
#define BLIMP_KEY_COMMA              44  /* , */
#define BLIMP_KEY_MINUS              45  /* - */
#define BLIMP_KEY_PERIOD             46  /* . */
#define BLIMP_KEY_SLASH              47  /* / */
#define BLIMP_KEY_0                  48
#define BLIMP_KEY_1                  49
#define BLIMP_KEY_2                  50
#define BLIMP_KEY_3                  51
#define BLIMP_KEY_4                  52
#define BLIMP_KEY_5                  53
#define BLIMP_KEY_6                  54
#define BLIMP_KEY_7                  55
#define BLIMP_KEY_8                  56
#define BLIMP_KEY_9                  57
#define BLIMP_KEY_SEMICOLON          59  /* ; */
#define BLIMP_KEY_EQUAL              61  /* = */
#define BLIMP_KEY_A                  65
#define BLIMP_KEY_B                  66
#define BLIMP_KEY_C                  67
#define BLIMP_KEY_D                  68
#define BLIMP_KEY_E                  69
#define BLIMP_KEY_F                  70
#define BLIMP_KEY_G                  71
#define BLIMP_KEY_H                  72
#define BLIMP_KEY_I                  73
#define BLIMP_KEY_J                  74
#define BLIMP_KEY_K                  75
#define BLIMP_KEY_L                  76
#define BLIMP_KEY_M                  77
#define BLIMP_KEY_N                  78
#define BLIMP_KEY_O                  79
#define BLIMP_KEY_P                  80
#define BLIMP_KEY_Q                  81
#define BLIMP_KEY_R                  82
#define BLIMP_KEY_S                  83
#define BLIMP_KEY_T                  84
#define BLIMP_KEY_U                  85
#define BLIMP_KEY_V                  86
#define BLIMP_KEY_W                  87
#define BLIMP_KEY_X                  88
#define BLIMP_KEY_Y                  89
#define BLIMP_KEY_Z                  90
#define BLIMP_KEY_LEFT_BRACKET       91  /* [ */
#define BLIMP_KEY_BACKSLASH          92  /* \ */
#define BLIMP_KEY_RIGHT_BRACKET      93  /* ] */
#define BLIMP_KEY_GRAVE_ACCENT       96  /* ` */
#define BLIMP_KEY_WORLD_1            161 /* non-US #1 */
#define BLIMP_KEY_WORLD_2            162 /* non-US #2 */
#define BLIMP_KEY_ESCAPE             256
#define BLIMP_KEY_ENTER              257
#define BLIMP_KEY_TAB                258
#define BLIMP_KEY_BACKSPACE          259
#define BLIMP_KEY_INSERT             260
#define BLIMP_KEY_DELETE             261
#define BLIMP_KEY_RIGHT              262
#define BLIMP_KEY_LEFT               263
#define BLIMP_KEY_DOWN               264
#define BLIMP_KEY_UP                 265
#define BLIMP_KEY_PAGE_UP            266
#define BLIMP_KEY_PAGE_DOWN          267
#define BLIMP_KEY_HOME               268
#define BLIMP_KEY_END                269
#define BLIMP_KEY_CAPS_LOCK          280
#define BLIMP_KEY_SCROLL_LOCK        281
#define BLIMP_KEY_NUM_LOCK           282
#define BLIMP_KEY_PRINT_SCREEN       283
#define BLIMP_KEY_PAUSE              284
#define BLIMP_KEY_F1                 290
#define BLIMP_KEY_F2                 291
#define BLIMP_KEY_F3                 292
#define BLIMP_KEY_F4                 293
#define BLIMP_KEY_F5                 294
#define BLIMP_KEY_F6                 295
#define BLIMP_KEY_F7                 296
#define BLIMP_KEY_F8                 297
#define BLIMP_KEY_F9                 298
#define BLIMP_KEY_F10                299
#define BLIMP_KEY_F11                300
#define BLIMP_KEY_F12                301
#define BLIMP_KEY_F13                302
#define BLIMP_KEY_F14                303
#define BLIMP_KEY_F15                304
#define BLIMP_KEY_F16                305
#define BLIMP_KEY_F17                306
#define BLIMP_KEY_F18                307
#define BLIMP_KEY_F19                308
#define BLIMP_KEY_F20                309
#define BLIMP_KEY_F21                310
#define BLIMP_KEY_F22                311
#define BLIMP_KEY_F23                312
#define BLIMP_KEY_F24                313
#define BLIMP_KEY_F25                314
#define BLIMP_KEY_KP_0               320
#define BLIMP_KEY_KP_1               321
#define BLIMP_KEY_KP_2               322
#define BLIMP_KEY_KP_3               323
#define BLIMP_KEY_KP_4               324
#define BLIMP_KEY_KP_5               325
#define BLIMP_KEY_KP_6               326
#define BLIMP_KEY_KP_7               327
#define BLIMP_KEY_KP_8               328
#define BLIMP_KEY_KP_9               329
#define BLIMP_KEY_KP_DECIMAL         330
#define BLIMP_KEY_KP_DIVIDE          331
#define BLIMP_KEY_KP_MULTIPLY        332
#define BLIMP_KEY_KP_SUBTRACT        333
#define BLIMP_KEY_KP_ADD             334
#define BLIMP_KEY_KP_ENTER           335
#define BLIMP_KEY_KP_EQUAL           336
#define BLIMP_KEY_LEFT_SHIFT         340
#define BLIMP_KEY_LEFT_CONTROL       341
#define BLIMP_KEY_LEFT_ALT           342
#define BLIMP_KEY_LEFT_SUPER         343
#define BLIMP_KEY_RIGHT_SHIFT        344
#define BLIMP_KEY_RIGHT_CONTROL      345
#define BLIMP_KEY_RIGHT_ALT          346
#define BLIMP_KEY_RIGHT_SUPER        347
#define BLIMP_KEY_MENU               348
#define BLIMP_KEY_LAST               BLIMP_KEY_MENU
