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

    symbolLabel.set_text("Symbol:");
    symbolValue.set_text("");
    priceLabel.set_text("Price:");
    priceValue.set_text("");


    mainGrid.attach(coinNameText, 0, 0, 2, 1);
    mainGrid.attach(coinNameButton, 2, 0, 2, 1);

    mainGrid.attach(symbolLabel, 0, 1, 1, 1);
    mainGrid.attach(symbolValue, 1, 1, 1, 1);
    mainGrid.attach(priceLabel, 2, 1, 1, 1);
    mainGrid.attach(priceValue, 3, 1, 1, 1);

    mainGrid.attach(coinAmountText, 0, 2, 2, 1);
    mainGrid.attach(coinAmountButton, 2, 2, 2, 1);


    secondaryGrid.attach(coinNameText2, 0, 0, 1, 1);
    secondaryGrid.attach(coinNameButton2, 1, 0, 1, 1);

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
    std::string coinSym = CC_API_Calls::get_coin_symbol(coinNameText.get_text().raw());
    if (coinSym == "") {
        // display coin not found dialog
        Gtk::MessageDialog *emptyMessage = new Gtk::MessageDialog("Invalid coin name");
        emptyMessage->set_modal(true);
        emptyMessage->set_transient_for(*this);
        emptyMessage->set_title("Invalid coin name");
        emptyMessage->set_size_request(200, 100);
        emptyMessage->show_all_children();
        emptyMessage->run();
        delete emptyMessage;
    } else {
        symbolValue.set_text(coinSym);
        std::string coinPrice = CC_API_Calls::get_price(coinSym);
        priceValue.set_text("$" + coinPrice);
    }
}

void MainMenu::amount_button_clicked() {
    std::cout << "Perform amount addition" << std::endl;

    if (userObj->isLoggedIn()) {
        if (coinNameText.get_text().raw().empty()) {
            // display empty dialog
            Gtk::MessageDialog *emptyMessage = new Gtk::MessageDialog("Please enter a coin name");
            emptyMessage->set_modal(true);
            emptyMessage->set_transient_for(*this);
            emptyMessage->set_title("Invalid coin name");
            emptyMessage->set_size_request(200, 100);
            emptyMessage->show_all_children();
            emptyMessage->run();
            delete emptyMessage;
        } else {
            try {
                double amt = std::stod(coinAmountText.get_text().raw());

                std::string coinSym = CC_API_Calls::get_coin_symbol(coinNameText.get_text().raw());
                if (coinSym != "") {

                    // insert coin into database, and credit amount to user's account
                    userObj->add_coin(coinNameText.get_text().raw());
                    userObj->add_coinID(CC_API_Calls::get_coin_symbol(coinNameText.get_text().raw()), amt);
                } else {
                    // display coin not found dialog
                    Gtk::MessageDialog *emptyMessage = new Gtk::MessageDialog("Invalid coin name");
                    emptyMessage->set_modal(true);
                    emptyMessage->set_transient_for(*this);
                    emptyMessage->set_title("Invalid coin name");
                    emptyMessage->set_size_request(200, 100);
                    emptyMessage->show_all_children();
                    emptyMessage->run();
                    delete emptyMessage;
                }
            } catch (int e) {
                // display invalid amount dialog
                Gtk::MessageDialog *invalidAmount = new Gtk::MessageDialog("Please enter a valid amount");
                invalidAmount->set_modal(true);
                invalidAmount->set_transient_for(*this);
                invalidAmount->set_title("Invalid Amount");
                invalidAmount->set_size_request(200, 100);
                invalidAmount->show_all_children();
                invalidAmount->run();
                delete invalidAmount;
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
