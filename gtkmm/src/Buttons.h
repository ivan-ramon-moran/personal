#ifndef GTKMM_EXAMPLE_BUTTONS_H
#define GTKMM_EXAMPLE_BUTTONS_H

#include <gtkmm.h>
#include <gtk/gtk.h>
#include <iostream>

using namespace std;

class Buttons : public Gtk::Window
{
public:
	Buttons();
	virtual ~Buttons();
protected:
	//Signal handlers:
	void on_button_clicked();

	//Child widgets:
	Gtk::Box contenedor;
	Gtk::Button m_button;
	Gtk::Button m_button2;
	GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;
};

#endif //GTKMM_EXAMPLE_BUTTONS_H
