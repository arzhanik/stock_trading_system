#include "Controller.h"

int main() {
	Controller& controller = Controller::get_controller();
	controller.operations();
	return 0;
}
