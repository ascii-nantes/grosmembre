#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QIODevice>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    bool estDedans(QString nom, QString prenom, QString numEtu);
    ~Widget();
public slots:
    void setMail(QString s);
    void flush();
    void addMember();
    //void deleteMember(); //!TODO
    void listMember();
    void updatelistMember();
    //void verifyMemberInServices(); //!TODO
    //void deleteMemberInServices(); //!TODO
private:
    QFormLayout m_layout;
    QLineEdit m_nom;
    QLineEdit m_prenom;
    QLineEdit m_pseudo;
    QLineEdit m_mail;
    QLineEdit m_num;
    QLineEdit m_numCarte;
    QCheckBox m_estPaye;
    QPushButton m_ok;
    QPushButton m_list;
    QPushButton m_verify;
    QTableWidget m_table;
};

#endif // WIDGET_H
