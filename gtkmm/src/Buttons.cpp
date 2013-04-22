#include "Buttons.h"
#include <iostream>

Buttons::Buttons()
{
  m_button.add_pixlabel("info.xpm", "cool button");
  m_button2.add_pixlabel("info.xpm","cool button2");

  m_button.set_name("m_button");
  set_title("Pixmap'd buttons!");
  set_border_width(10);

  m_button.signal_clicked().connect( sigc::mem_fun(*this, &Buttons::on_button_clicked) );

  add(contenedor);
  /*---------------- CSS ----------------------------------------------------------------------------------------------------*/
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gsize bytes_written, bytes_read;

    const gchar* home = "style.css";  // your path, for instance: /home/zerohour/Documents/programming/cssexternal.css

    GError *error = 0;

     gtk_css_provider_load_from_path (provider,
                                        g_filename_to_utf8(home, strlen(home), &bytes_read, &bytes_written, &error),
                                        NULL);
    g_object_unref (provider);
  /*-------------------------------------------------------------------------------------------------------------------------*/

  contenedor.pack_start(m_button);
  contenedor.pack_start(m_button2);
  show_all_children();
}

Buttons::~Buttons()
{
}

void Buttons::on_button_clicked()
{
  std::cout << "The Button was clicked." << std::endl;
}
