#include <iostream>
#include <cstring>
#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include "myWindow.h"

int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv);

    auto builder = Gtk::Builder::create_from_file("builder.ui");

    MainWindow* window = nullptr;

    builder->get_widget_derived("mainWindow", window);

    app->run(*window);

    return 0;
}
