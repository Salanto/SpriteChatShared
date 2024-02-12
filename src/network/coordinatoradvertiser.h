#ifndef COORDINATORADVERTISER_H
#define COORDINATORADVERTISER_H

#include <QObject>

class CoordinatorAdvertiser : public QObject
{
    Q_OBJECT

  public:
    explicit CoordinatorAdvertiser(QObject *parent = nullptr);

  signals:
};

#endif // COORDINATORADVERTISER_H
