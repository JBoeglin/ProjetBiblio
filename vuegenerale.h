#ifndef VUEGENERALE_H
#define VUEGENERALE_H


#include <QWidget>
#include <QLabel>
#include <QPushButton>

class VueGenerale : public QWidget
{
    Q_OBJECT
public:
    explicit VueGenerale(QWidget *parent = nullptr);

public slots:
    int clos();

private:
    QLabel *labelpage2;
    QPushButton *m_exit;
};

#endif // VUEGENERALE_H





