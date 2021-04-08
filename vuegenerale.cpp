#include "vuegenerale.h"
#include "vueaccueil.h"

#include "connection.h"
#include <stdlib.h>
#include <QLabel>
#include <QApplication>


VueGenerale::VueGenerale(QWidget *parent) : QWidget(parent)
{

    setFixedSize(500, 300);

    labelpage2 = new QLabel("Tu es bien a la page 2 ", this);
    labelpage2->move(5, 10);

    labelpage2 = new QLabel("connecté en tant que : ", this);
    labelpage2->move(30, 50);

    m_exit = new QPushButton("Revenir a l'accueil", this);
    m_exit->move(70, 160);

    QObject::connect(m_exit, SIGNAL(clicked()),this, SLOT(clos()));
}


int VueGenerale::clos()
{
    close();//pour fermer une fenetre
    if (!createConnection()) // obligatoire pour afficher le logo creation de compte
        return EXIT_FAILURE;

    VueAccueil *toto = new VueAccueil("items", "images");
    toto->show();
    return 1;
}
