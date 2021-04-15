#include <QApplication>

#include <QSqlDatabase>
#include <QSqlQuery>

#include "vueaccueil.h"
#include "connection.h"

#include <QApplication>

#include <stdlib.h>
#include <QDate>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //ouvrir BDD
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysql-lpdiebiblio.alwaysdata.net");
    db.setDatabaseName("lpdiebiblio_bdd");
    db.setUserName("229129_jonathan");
    db.setPassword("testlpdie1234");
    db.open();

    QSqlQuery query(db);

    //table Etat
    QString Etat = QString("CREATE TABLE IF NOT EXISTS Etat("
                            "ID_Etat INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                            "Etat VARCHAR(20))");
    query.exec(Etat);

    query.prepare("INSERT INTO Etat(Etat) VALUES(:etat)");
    query.bindValue(":etat", "neuf");
    query.exec();
    query.bindValue(":etat", "abimé");
    query.exec();
    query.bindValue(":etat","a jeter");
    query.exec();

    //table Langue
    QString Langue = QString("CREATE TABLE IF NOT EXISTS Langue("
                            "ID_Langue INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                            "Langue VARCHAR(20))");
    query.exec(Langue);
    query.prepare("INSERT INTO Langue(Langue) VALUES(:langue)");
    query.bindValue(":langue", "anglais");
    query.exec();
    query.bindValue(":langue", "japonais");
    query.exec();
    query.bindValue(":langue", "allemand");
    query.exec();
    query.bindValue(":langue", "espagnol");
    query.exec();
    query.bindValue(":langue", "italien");
    query.exec();

    //table Genre
    QString Genre = QString("CREATE TABLE IF NOT EXISTS Genre("
                            "ID_Genre INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                            "Genre VARCHAR(20))");
    query.exec(Genre);
    query.prepare("INSERT INTO Genre(Genre) VALUES(:genre)");
    query.bindValue(":genre", "aventure");
    query.exec();
    query.bindValue(":genre", "fantastique");
    query.exec();
    query.bindValue(":genre", "Sci-fi");
    query.exec();
    query.bindValue(":genre", "amour");
    query.exec();
    query.bindValue(":genre", "auto-biographie");
    query.exec();
    query.bindValue(":genre", "thriller");
    query.exec();
    query.bindValue(":genre", "comédie");
    query.exec();
    query.bindValue(":genre", "drame");
    query.exec();
    query.bindValue(":genre", "horreur");
    query.exec();

    //table Auteur
    QString Auteur = QString("CREATE TABLE IF NOT EXISTS Auteur("
                              "ID_Auteur INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                              "Prenom VARCHAR(20), "
                              "Nom VARCHAR(20),"
                              "Date_de_naissance DATE)");
    query.exec(Auteur);
    query.prepare("INSERT INTO Auteur(Prenom, Nom, Date_de_naissance) VALUES(Jonathan, BOEGLIN, 1993.08.28')");
    query.exec();
    query.prepare("INSERT INTO Auteur(Prenom, Nom, Date_de_naissance) VALUES(:prenom, :nom, 1995.02.21')");
    query.bindValue(":prenom", "Romain");
    query.bindValue(":nom","ZIRNHELD");
    query.exec();

    //table Livre
    QString Livre = QString("CREATE TABLE IF NOT EXISTS Livre("
                              "ID_Livre INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                              "Titre VARCHAR(20), "
                              "Année YEAR, "
                              "Disponibilité BOOL, "
                              "Image BLOB, "
                              "genreid INTEGER NOT NULL, "
                              "etatid INTEGER NOT NULL, "
                              "langueid INTEGER NOT NULL, "
                              "auteurid INTEGER NOT NULL, ");
    query.exec(Livre);

    query.prepare("INSERT INTO Livre(Titre, Année, Disponibilité,Image, genreid, etatid,langueid,auteurid) VALUES(:titre,:annee,:dispo,:img,:genreid, :etatid, :langueid, :auteurid)");
    query.bindValue(":titre","Jonathan");
    query.bindValue(":annee",1901);
    query.bindValue(":dispo",1);
    query.bindValue(":img","harry-potter-et-l-ordre-du-phenix.jpg");
    query.bindValue(":genreid",1);
    query.bindValue(":etatid",1);
    query.bindValue(":langueid",1);
    query.bindValue(":auteurid",1);
    query.exec();
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
    query.prepare("INSERT INTO Livre(livreid, Date_Debut, Date_Fin) VALUES (:livreid, 1987.03.25, 1989.06.24)");
    query.bindValue(":livreid",1);
    query.exec();


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
                                            ":nomU, :prenomU, :login, :mdp, 1989.01.01, :codeP, :adresse, :ville, :email, :tel, :blacklist)");
    query.bindValue(":nomU","Paire");
    query.bindValue(":prenomU","Benoit");
    query.bindValue(":login","KeepCalm");
    query.bindValue(":mdp","6inarow");
    query.bindValue("codeP",66666);
    query.bindValue(":ville","troupaumé");
    query.bindValue(":adresse","quelquepart");
    query.bindValue(":email","BenoitPaire@atp.com");
    query.bindValue(":tel","0606060606");
    query.bindValue(":blacklist","1");
    query.exec();

    //clé composé table jointure
    Emprunt = QString("ALTER TABLE Emprunt ADD CONSTRAINT FK_Emprunt2 FOREIGN KEY(utilisateurid) REFERENCES Utilisateur(ID_Utilisateur)");query.exec(Emprunt);
    Emprunt = QString("ALTER TABLE Emprunt ADD CONSTRAINT PK_Emprunt2 PRIMARY KEY (ID_Emprunt, livreid, utilisateurid)");query.exec(Emprunt);

    Livre = QString("ALTER TABLE Livre ADD CONSTRAINT FK_Livre FOREIGN KEY(genreid) REFERENCES Genre(ID_Genre)"); query.exec(Livre);
    Livre = QString("ALTER TABLE Livre ADD CONSTRAINT FK_Livre1 FOREIGN KEY(auteurid) REFERENCES Auteur(ID_Auteur)"); query.exec(Livre);
    Livre = QString("ALTER TABLE Livre ADD CONSTRAINT FK_Livre2 FOREIGN KEY(langueid) REFERENCES Langue(ID_Langue)"); query.exec(Livre);
    Livre = QString("ALTER TABLE Livre ADD CONSTRAINT FK_Livre3 FOREIGN KEY(etatid) REFERENCES Etat(ID_Etat)"); query.exec(Livre);
    //query.prepare("INSERT INTO Livre(livreid, utilisateurid, Date_Debut, Date_Fin) VALUES ('1','1', '1987.03.25', '1989.06.24')");query.exec();

    Q_INIT_RESOURCE(Resources);

    if (!createConnection())
        return EXIT_FAILURE;

    VueAccueil vueaccueil("items", "images");
    vueaccueil.show();


    return app.exec();


}
