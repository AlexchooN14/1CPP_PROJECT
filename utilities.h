#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

#define KEYBOARD_BUTTON_UP      72
#define KEYBOARD_BUTTON_DOWN    80
#define KEYBOARD_BUTTON_ENTER   13
#define KEYBOARD_CTRL_C         3
#define KEYBOARD_ESC            27


template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec);

ostream& operator<<(ostream& os, const tm& time);

bool stringToBool(const std::string& str);

#endif // UTILITIES_H
