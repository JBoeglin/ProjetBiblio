#include "vueaccueil.h"
#include "creationcompte.h"
#include "imageitem.h"
#include "vuegenerale.h"

#include "connection.h"
#include <stdlib.h>

VueAccueil::VueAccueil(){}

VueAccueil::VueAccueil(const QString &items, const QString &images, QWidget *parent)
    : QGraphicsView(parent)
{
    Q_INIT_RESOURCE(Resources);

    label = new QLabel("Connectez vous !", this);
    label->move(125, 10);

    labeltitre = new QLabel("Nom d'utilisateur : ", this);
    labeltitre->move(125, 30);
    login = new QLineEdit(this);
    login->move(125, 45);

    labeltitre = new QLabel("Mot de passe : ", this);
    labeltitre->move(125, 70);
    mdp = new QLineEdit(this);
    mdp->move(125, 85);

    m_boutonConnection = new QPushButton("Se connecter", this);
    m_boutonConnection->move(225, 120);

    itemTable = new QSqlRelationalTableModel(this);
    itemTable->setTable(items);
    itemTable->setRelation(1, QSqlRelation(images, "itemid", "file"));
    itemTable->select();

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0, 500, 400);
    setScene(scene);

    addItems();

    setMinimumSize(100, 80);
    setMaximumSize(1600, 1400);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 370));
    gradient.setColorAt(0, QColor("#868482"));
    gradient.setColorAt(1, QColor("#5d5b59"));
    setBackgroundBrush(gradient);

    QObject::connect(m_boutonConnection, SIGNAL(clicked()),this, SLOT(openbdd()));



}

void VueAccueil::openbdd()
{
    QString m_login;
    QString m_mdp;
    m_login = login->text();
    m_mdp = mdp->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("C:/Qt/BDD local/"+ m_login +"");//pour BDD local juste a preciser ou sauvegarder
    db.setUserName(m_login);
    db.setPassword(m_mdp);
    bool ok = db.open();

    QSqlQuery query(db);

    QSqlQuery requete;
    if (ok == true)
    {
      if(requete.exec("SELECT * FROM livres"))
         {

              if(requete.first())
                  {
                   qDebug() << requete.value("mdp");
                  }
              if(requete.value("mdp") == m_mdp)
              {
                  qDebug() << "cest ok";
                  qDebug() << db.userName();
                      setFixedSize(0,0);
                      VueGenerale *toto = new VueGenerale;
                      toto->show();

              }
              else
                  db.close();
        }
    }
}

void VueAccueil::addItems()
{
    int itemCount = itemTable->rowCount();

    int imageOffset = 150;
    int leftMargin = 150;
    int topMargin = 200;

    for (int i = 0; i < itemCount; i++) {
        QSqlRecord record = itemTable->record(i);

        int id = record.value("id").toInt();
        QString file = record.value("file").toString();
        QString item = record.value("itemtype").toString();

        int columnOffset = ((i % 2) * 37);
        int x = ((i % 2) * imageOffset) + leftMargin + columnOffset;
        int y = ((i / 2) * imageOffset) + topMargin;

        ImageItem *image = new ImageItem(id, QPixmap(":/" + file));
        image->setData(0, i);
        image->setPos(x, y);
        scene->addItem(image);

        QGraphicsTextItem *label = scene->addText(item);
        label->setDefaultTextColor(QColor("#d7d6d5"));
        QPointF labelOffset((120 - label->boundingRect().width()) / 2, 120.0);
        label->setPos(QPointF(x, y) + labelOffset);
    }
}

void VueAccueil::mouseReleaseEvent(QMouseEvent *event)
{
    if (QGraphicsItem *item = itemAt(event->position().toPoint())) {
        if (ImageItem *image = qgraphicsitem_cast<ImageItem *>(item))
            showInformation(image);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void VueAccueil::showInformation(ImageItem *image)
{
    int id = image->id();
    if (id < 0 || id >= itemTable->rowCount())
        return;

    creationCompte *window = findWindow();
    if (!window) {
        window = new creationCompte(this);

        window->move(pos() + QPoint(20, 40));
        window->show();
        creationcompte.append(window);
    }

    if (window->isVisible()) {
        window->raise();
        window->activateWindow();
    } else
        window->show();
}

void VueAccueil::updateImage(int id, const QString &fileName)
{
    QList<QGraphicsItem *> items = scene->items();

    while(!items.empty()) {
        QGraphicsItem *item = items.takeFirst();

        if (ImageItem *image = qgraphicsitem_cast<ImageItem *>(item)) {
            if (image->id() == id){
                image->setPixmap(QPixmap(":/" +fileName));
                image->adjust();
                break;
            }
        }
    }
}

creationCompte *VueAccueil::findWindow() const
{
    for (auto window : creationcompte) {
        if (window )
            return window;
    }
    return nullptr;
}

void VueAccueil::setLogin(QString log)
{
 m_login = log;
}

QString VueAccueil::getLogin()
{
 return m_login;
}

void VueAccueil::setMdp(QString motdepasse)
{
 m_mdp = motdepasse;
}

QString VueAccueil::getMdp()
{
 return m_mdp;
}
