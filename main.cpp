#include "main.h"
#include "MainMenu.h"

#include <gtkmm.h>

// compiler options:
// `pkg-config gtkmm-3.0 --cflags`
// `pkg-config glibmm-2.4 --cflags`

// linker settings:
// `pkg-config gtkmm-3.0 --libs`
// `pkg-config glibmm-2.4 --libs`


int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc,argv,"org.cryptotracker.example");

    MainMenu window;

    return app->run(window, argc, argv);
}

main::~main()
{
    //dtor
}
