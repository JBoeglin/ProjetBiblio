#include <QApplication>

#include <QSqlDatabase>
#include <QSqlQuery>

#include "vueaccueil.h"
#include "connection.h"

#include <QApplication>

#include <stdlib.h>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //ouvrir BDD
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysql-lpdiebiblio.alwaysdata.net");
    db.setDatabaseName("lpdiebiblio_bdd");
    db.setUserName("229129_romain");
    db.setPassword("romain6868@!");
    db.open();

    QSqlQuery query(db);

    //table Etat
    QString Etat = QString("CREATE TABLE IF NOT EXISTS Etat("
                            "ID_Etat INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                            "Etat VARCHAR(20))");
    query.exec(Etat);
    query.prepare("INSERT INTO Etat(Etat) VALUES('neuf')");query.exec();//ajouter données
    query.prepare("INSERT INTO Etat(Etat) VALUES('abimé')");query.exec();
    query.prepare("INSERT INTO Etat(Etat) VALUES('a jeter')");query.exec();

    //table Langue
    QString Langue = QString("CREATE TABLE IF NOT EXISTS Langue("
                            "ID_Langue INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                            "Langue VARCHAR(20))");
    query.exec(Langue);
    query.prepare("INSERT INTO Langue(Langue) VALUES('français')");query.exec();//ajouter données
    query.prepare("INSERT INTO Langue(Langue) VALUES('anglais')");query.exec();
    query.prepare("INSERT INTO Langue(Langue) VALUES('japonais')");query.exec();
    query.prepare("INSERT INTO Langue(Langue) VALUES('allemand')");query.exec();
    query.prepare("INSERT INTO Langue(Langue) VALUES('espagnol')");query.exec();
    query.prepare("INSERT INTO Langue(Langue) VALUES('chinois')");query.exec();
    query.prepare("INSERT INTO Langue(Langue) VALUES('italien')");query.exec();

    //table Genre
    QString Genre = QString("CREATE TABLE IF NOT EXISTS Genre("
                            "ID_Genre INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                            "Genre VARCHAR(20))");
    query.exec(Genre);
    query.prepare("INSERT INTO Genre(Genre) VALUES('action')");query.exec();
    query.prepare("INSERT INTO Genre(Genre) VALUES('aventure')");query.exec();
    query.prepare("INSERT INTO Genre(Genre) VALUES('fantastique')");query.exec();
    query.prepare("INSERT INTO Genre(Genre) VALUES('Sci-fi')");query.exec();
    query.prepare("INSERT INTO Genre(Genre) VALUES('amour')");query.exec();
    query.prepare("INSERT INTO Genre(Genre) VALUES('auto-biographie')");query.exec();
    query.prepare("INSERT INTO Genre(Genre) VALUES('thriller')");query.exec();
    query.prepare("INSERT INTO Genre(Genre) VALUES('comédie')");query.exec();
    query.prepare("INSERT INTO Genre(Genre) VALUES('drame')");query.exec();
    query.prepare("INSERT INTO Genre(Genre) VALUES('horreur')");query.exec();

    //table Auteur
    QString Auteur = QString("CREATE TABLE IF NOT EXISTS Auteur("
                              "ID_Auteur INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                              "Prenom VARCHAR(20), "
                              "Nom VARCHAR(20),"
                              "Date_de_naissance DATE)");
    query.exec(Auteur);
    query.prepare("INSERT INTO Auteur(Prenom, Nom, Date_de_naissance) VALUES('Jonathan', 'Boeglin', '1993.08.28')");query.exec();
    query.prepare("INSERT INTO Auteur(Prenom, Nom, Date_de_naissance) VALUES('Romain', 'ZIRNHELD', '1995.02.21')");query.exec();

    //table Livre
    QString Livre = QString("CREATE TABLE IF NOT EXISTS Livre("
                              "ID_Livre INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                              "Titre VARCHAR(20), "
                              "Année YEAR, "
                              "Disponibilité BOOL, "
                              "Image BLOB, "
                              "genreid INTEGER NOT NULL, "
                              "etatid INTEGER NOT NULL, "
                              "FOREIGN KEY(genreid) REFERENCES Genre(ID_Genre), "
                              "FOREIGN KEY(etatid) REFERENCES Etat(ID_Etat))");
    query.exec(Livre);
    query.prepare("INSERT INTO Livre(Titre, Année, Disponibilité,Image, genreid, etatid) VALUES('Jonathan','1901','1','C:/Users/romai/Desktop/harry-potter-et-l-ordre-du-phenix.jpg','1', '1')");query.exec();

    //table Emprunt
    QString Emprunt = QString("CREATE TABLE IF NOT EXISTS Emprunt("
                              "ID_Emprunt INTEGER NOT NULL AUTO_INCREMENT,"
                              "livreid INTEGER NOT NULL ,"
                              "utilisateurid INTEGER NOT NULL ,"
                              "Date_Debut DATE,"
                              "Date_Fin DATE,"
                              "CONSTRAINT FK_Emprunt FOREIGN KEY(livreid) REFERENCES Livre(ID_Livre),"
                              "CONSTRAINT PK_Emprunt PRIMARY KEY (ID_Emprunt, livreid))");
                              //"CONSTRAINT FK_Emprunt2 FOREIGN KEY(utilisateurid) REFERENCES Utilisateur(ID_Utilisateur),"
    query.exec(Emprunt);
    query.prepare("INSERT INTO Livre(livreid, Date_Debut, Date_Fin) VALUES ('1', '1987.03.25', '1989.06.24')");query.exec();


    //table utilisateur
    QString Utilisateur = QString("CREATE TABLE IF NOT EXISTS Utilisateur("
                              "ID_Utilisateur INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                              "Nom VARCHAR(30), "
                              "Prenom VARCHAR(30), "
                              "Login VARCHAR(30), "
                              "Mdp VARCHAR(30), "
                              "Date_de_naissance DATE, "
                              "Code_Postal INTEGER, "
                              "Adresse VARCHAR(50), "
                              "Ville VARCHAR(30), "
                              "Email VARCHAR(30), "
                              "Tel VARCHAR(20), "
                              "Blacklist BOOL, "
                              "empruntid INTEGER NOT NULL, "
                              "CONSTRAINT FK_Utilisateur FOREIGN KEY(empruntid) REFERENCES Emprunt(ID_Emprunt))");
    query.exec(Utilisateur);
    query.exec();

    query.prepare("INSERT INTO Utilisateur(Nom, Prenom, Login, Mdp, Date_de_naissance, Code_Postal, Adresse, Ville, Email, Tel, Blacklist) VALUES("
                                            "'Robert', 'Paul', 'Paul68', 'popol', '1953.06.28', '68250', '18 rue de la biere', 'Strasbourg', 'paul@gmail.com', '0646852145', '1')");query.exec();

    //clé composé table jointure
    Emprunt = QString("ALTER TABLE Emprunt ADD CONSTRAINT FK_Emprunt2 FOREIGN KEY(utilisateurid) REFERENCES Utilisateur(ID_Utilisateur)");query.exec(Emprunt);
    Emprunt = QString("ALTER TABLE Emprunt ADD CONSTRAINT PK_Emprunt2 PRIMARY KEY (ID_Emprunt, livreid, utilisateurid)");query.exec(Emprunt);
    //query.prepare("INSERT INTO Livre(livreid, utilisateurid, Date_Debut, Date_Fin) VALUES ('1','1', '1987.03.25', '1989.06.24')");query.exec();

    Q_INIT_RESOURCE(Resources);

    if (!createConnection())
        return EXIT_FAILURE;

    VueAccueil vueaccueil("items", "images");
    vueaccueil.show();


    return app.exec();


}
