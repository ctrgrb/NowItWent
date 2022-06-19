#include "startdialog.hh"
#include "ui_startdialog.h"

startDialog::startDialog(QWidget *parent) :
    QDialog(parent),
    dialog_ui(new Ui::startDialog){
    dialog_ui->setupUi(this);
    connect(dialog_ui->play_button, SIGNAL(pressed()),
            this, SLOT(close()));
    play_button_enabled(false);
}

startDialog::~startDialog(){
    delete dialog_ui;}

int startDialog::return_time_input(){
    return time_;}

bool startDialog::return_dialog_size(){
    return big_background_;}

void startDialog::play_button_enabled(bool truth_value){
    dialog_ui->play_button->setEnabled(truth_value);}

void startDialog::on_five_min_clicked(){
    time_ = 300;
    play_button_enabled(true);}

void startDialog::on_two_min_clicked(){
    time_ = 120;
    play_button_enabled(true);}

void startDialog::on_ten_min_clicked(){
    time_ = 600;
    play_button_enabled(true);}

void startDialog::on_checkBox_clicked(){
    // Set background size
    if (!big_background_){
        big_background_ = true;
    }else{
        big_background_ = false;
    }
}

