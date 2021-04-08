#include "creationcompte.h"

#include "vueaccueil.h"

#include <QString>

creationCompte::creationCompte(QWidget *parent): QDialog(parent)
{
    setFixedSize(500, 300);

    labeltitre = new QLabel("nom utilisateur : ", this);
    labeltitre->move(5, 10);
    login1 = new QLineEdit(this);
    login1->move(60, 10);

    labelauteur = new QLabel("mdp : ", this);
    labelauteur->move(5, 40);
    mdp1 = new QLineEdit(this);
    mdp1->move(60, 40);

    m_boutonDialogue2 = new QPushButton("Enregistrer", this);
    m_boutonDialogue2->move(70, 160);

    //QObject::connect(m_boutonDialogue, SIGNAL(clicked()),this, SLOT(ouvrirDialogue()));
    QObject::connect(m_boutonDialogue2, SIGNAL(clicked()),this, SLOT(oki()));
}

void  creationCompte::ouvrirDialogue()
{
    QMessageBox::information(this, "Jauneattend", "bravo ta ouvert un dialogue!");
    //QMessageBox::warning(this, "Jauneattend", "Je suis un génie");
    //QMessageBox::question(this, "Jauneattend", "Je suis un génie?");
    //QMessageBox::critical(this, "Jauneattend", "Je suis un génie");
}


void  creationCompte::oki()
    {
     QString m_login;
     QString m_mdp;

     m_login = login1->text();
     m_mdp = mdp1->text();

     qDebug() << "m_login : " << m_login;
     qDebug() << "m_mdp : " << m_mdp;

     QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
     db.setHostName("localhost");
     db.setDatabaseName("C:/Qt/BDD local/"+ m_login +"");//pour BDD local juste a preciser ou sauvegarder
     db.setUserName("romai");
     db.setPassword("");
     bool ok = db.open();

     //création de table
     QString sql = QString("CREATE TABLE livres(mdp char,titre char,auteur char)");
     QSqlQuery query(db);
     ok = query.exec(sql);

     QSqlQuery requete;
     if (ok == true)
     {
    if(requete.exec("SELECT * FROM livres"))
         {
        qDebug() << "Ok";
     //requete.exec("DELETE FROM livres");//permet de delete les lignes avec id=1
     //requete.exec("Create Table utilisateurs(id INTEGER PRIMARY KEY, nom varchar(20), mdp varchar(20))");
     requete.exec("INSERT INTO livres (mdp)" "VALUES('"+ m_mdp +"')");//permet d'insérer une ligne dans la BDD
     qDebug() << "mdp rentrer";
     requete.exec("SELECT * FROM livres");
     while(requete.next()){
     qDebug() << requete.value("mdp") << " " << requete.value("titre") << " " << requete.value("auteur");
                }
         }
     }
     db.close();
}
