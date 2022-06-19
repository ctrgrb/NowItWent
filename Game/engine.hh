#ifndef ENGINE_HH
#define ENGINE_HH

#include "studentmainwindow.hh"
#include "city.hh"
#include <QImage>

namespace StudentSide {

class Engine : public QObject
{
    Q_OBJECT

public:
    Engine();
    void createGame();

private:
    std::shared_ptr<StudentSide::City> city_;
    int seconds_;
    bool big_background_;

};

} // namespace

#endif // ENGINE_HH
