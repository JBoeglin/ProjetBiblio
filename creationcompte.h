#ifndef CREATIONCOMPTE_H
#define CREATIONCOMPTE_H

#include <QtWidgets>
#include <QtSql>

class VueAccueil;

class creationCompte: public QDialog
{
     Q_OBJECT

public:
    creationCompte(QWidget *parent = nullptr);

signals:

private slots:
    void ouvrirDialogue();
    void oki();

private:
    QString titi;
    QLabel *labeltitre;
    QLabel *labelauteur;
    QLabel *labelannee;
    QLabel *labeledition;
    QLabel *labelgenre;

    QLineEdit *login1 ;
    QLineEdit *mdp1;
    QLineEdit *Annee;
    QLineEdit *Edition;
    QLineEdit *Genre;

    QPushButton *m_boutonDialogue;
    QPushButton *m_boutonDialogue2;
};

#endif // CREATIONCOMPTE_H
