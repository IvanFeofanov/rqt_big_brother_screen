#ifndef EDIT_MODE_H
#define EDIT_MODE_H

#include <QObject>

class EditMode : public QObject
{
    Q_OBJECT

public:
    explicit EditMode(QObject* parent = 0);

public slots:
    virtual void cancel() = 0;
    virtual void save() = 0;
};

#endif
