#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>

namespace Ui {
class startDialog;
}

class startDialog : public QDialog
{
    Q_OBJECT

public:
    explicit startDialog(QWidget *parent = nullptr);
    ~startDialog();
    int return_time_input();
    bool return_dialog_size();
    void play_button_enabled(bool truth_value);

private slots:
    void on_five_min_clicked();
    void on_two_min_clicked();
    void on_ten_min_clicked();    
    void on_checkBox_clicked();

private:
    Ui::startDialog *dialog_ui;
    int time_;
    bool big_background_ = false;
};

#endif // STARTDIALOG_HH
