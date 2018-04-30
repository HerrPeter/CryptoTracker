#include "main.h"
#include "MainMenu.h"

#include <gtkmm.h>


int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc,argv,"org.cryptotracker.example");

    MainMenu window;

    return app->run(window, argc, argv);
}

main::~main()
{
    //dtor
}
