#ifndef APPCONTROL_HPP
#define APPCONTROL_HPP

#include <QObject>

class Main_Window;

class AppControl : public QObject
{
    Q_OBJECT

private:
    Main_Window* mainWindow;

public:
    explicit AppControl(QObject *parent = nullptr);

signals:

private slots:
    void saveCurrent(QString const& content);
    void saveAs(QString const& name, QString const& content);

};

#endif // APPCONTROL_HPP
