//============================================================================
// Name        : Ejemplo1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <gtkmm/application.h>
#include <glibmm.h>
#include "Buttons.h"

using namespace std;

int main(int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,"org.gtkmm.examples");

	Buttons buttons;

	return app->run(buttons);
}
