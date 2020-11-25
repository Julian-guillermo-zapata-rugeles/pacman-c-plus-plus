#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>

class pacman : public QObject
{
    Q_OBJECT
public:
    explicit pacman(QObject *parent = nullptr);

signals:

};

#endif // PACMAN_H
