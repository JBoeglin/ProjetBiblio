#ifndef VUEACCUEIL_H
#define VUEACCUEIL_H

//#include <QWidget>
#include <QtWidgets>
#include <QtSql>

class ImageItem;
class creationCompte;

class VueAccueil : public QGraphicsView
{
    Q_OBJECT
public:
    explicit VueAccueil(QWidget *parent = nullptr);

    VueAccueil();
    VueAccueil(const QString &items, const QString &images, QWidget *parent = nullptr);
    QString getLogin();
    void setLogin(QString);
    QString getMdp();
    void setMdp(QString);


protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void updateImage(int id, const QString &fileName);
    void openbdd();
private:
    void addItems();

    creationCompte *findWindow() const;
    void showInformation(ImageItem *image);

    QGraphicsScene *scene;
    QList<creationCompte *> creationcompte;

    QSqlRelationalTableModel *itemTable;

    QLabel *label;
    QLabel *labeltitre;
    QLineEdit *login ;
    QString m_login;
    QLineEdit *mdp ;
    QString m_mdp;
    QPushButton *m_boutonConnection;
};
#endif // VUEACCUEIL_H
