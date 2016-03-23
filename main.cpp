#include <iostream>
#include "ConsoleSettings.h"

int main() {
	ConsoleSettings::HideCursor();
	ConsoleSettings::SetTextColor(0x0F);
	std::cout << "Hello, world!" << std::endl;
	return 0;
}