#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
    userObj = new CT_User();
    this->resize(400, 200);
    set_border_width(10);




    coinNameText.set_placeholder_text("Coin Name");
    coinNameText2.set_placeholder_text("Coin Name");
    coinAmountText.set_placeholder_text("Coin Amount");



    coinNameButton.add_label("Submit");
    coinAmountButton.add_label("Submit");
    coinNameButton.set_size_request(150, 50);
    coinNameButton2.set_size_request(150, 50);
    coinAmountButton.set_size_request(150, 50);

    coinNameButton.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::coin_button_clicked));
    coinAmountButton.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::amount_button_clicked));
    coinNameButton2.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::holdings_button_clicked));

    mainGrid.attach(coinNameButton, 1, 0, 1, 1);
    mainGrid.attach(coinAmountButton, 1, 1, 1, 1);
    mainGrid.attach(coinNameText, 0, 0, 1, 1);
    mainGrid.attach(coinAmountText, 0, 1, 1, 1);

    secondaryGrid.attach(coinNameText2, 0, 0, 1, 1);
    secondaryGrid.attach(coinNameButton2, 1, 0, 1, 1);


    //mainGrid.add(homeButton);
    //mainGrid.add(exitButton);

    mainGrid.show_all();
    secondaryGrid.show_all();

    selector.append_page(mainGrid, "Home");
    selector.append_page(secondaryGrid, "Holdings");
    add(selector);
    show_all_children();

}

void MainMenu::createLoginDialog() {
    loginDialog = new Gtk::Dialog();
    loginDialog->set_title("Login");
    loginDialog->set_modal(true);
    loginDialog->set_transient_for(*this);
    loginDialog->get_vbox()->add(enterUsername);
    loginButton.add_label("Login");
    loginButton.set_size_request(150, 50);
    loginButton.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::login));
    loginDialog->get_vbox()->add(loginButton);
    loginButton.set_can_default();
    loginButton.grab_default();
    loginDialog->show_all_children();
    loginDialog->set_size_request(200, 100);
    loginDialog->run();
}

void MainMenu::coin_button_clicked() {
    std::cout << "Perform coin lookup" << std::endl;

    if (userObj->isLoggedIn()) {
        std::string coinSym = CC_API_Calls::get_coin_symbol(coinNameText.get_text().raw());
    } else {
        createLoginDialog();
    }


}

void MainMenu::amount_button_clicked() {
    std::cout << "Perform amount addition" << std::endl;

    if (userObj->isLoggedIn()) {
        if (coinNameText.get_text().raw().empty()) {
            // display empty dialog
        } else {
            try {
                int amt = std::stoid(coinAmountText.get_text().raw());
                userObj.add_coin(coinNameText.get_text().raw());
                userObj.add_coinID(CC_API_Calls::get_coin_symbol(coinNameText.get_text().raw()), amt);
            } catch (int e) {
                // display invalid amount dialog
            }

        }
    } else {
        createLoginDialog();
    }
}

void MainMenu::holdings_button_clicked() {
    std::cout << "Perform holdings action" << std::endl;

    if (userObj->isLoggedIn()) {

    } else {
        createLoginDialog();
    }
}

void MainMenu::login() {
    //cout << enterUsername.get_text().raw() << endl;
    if (enterUsername.get_text() != "") {
        userObj = new CT_User(enterUsername.get_text().raw());
        delete loginDialog;
    }
}


MainMenu::~MainMenu()
{
    //dtor
    //delete userObj;

}
