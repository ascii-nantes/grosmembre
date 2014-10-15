#include "widget.h"

/**
 * @brief Widget::Widget    widget principal
 * @param parent            prend en paramètre le Widget parent de classe
 * QWidget
 */
Widget::Widget(QWidget *parent)
    : QWidget(parent), m_layout(), m_nom(this), m_prenom(this),
      m_pseudo(this), m_mail(this), m_num(this), m_numCarte(this),
      m_estPaye(this), m_ok("Ajouter"), m_list("Liste"), m_verify("Vérifier"),
      m_table(0,7)
{
    QHBoxLayout* h_box = new QHBoxLayout;

    setFixedSize(500, 400);

    //! \brief s_list
    //! Liste des attributs renseignés lors de l’inscription d’un membre :
    QStringList s_list;
    s_list << "Nom"
           << "Prénom"
           << "Pseudal"
           << "Courriel"
           << "Téléphone"
           << "Carte"
           << "Cotisation payée";

    m_table.setHorizontalHeaderLabels(s_list);
    m_table.setFixedSize(500, 400);
    m_table.setAlternatingRowColors(true);
    m_table.setWindowTitle("Liste des membres");

    // bindings
    // binding #1 un changement du prénom active la génération
    // du pattern de mail étudiant (voir Widget:setMail()).
    connect(&m_prenom,SIGNAL(textChanged(QString)), this, SLOT(setMail(QString)));
    connect(&m_ok, SIGNAL(clicked()), this, SLOT(addMember()));
    connect(&m_list, SIGNAL(clicked()), this, SLOT(listMember()));
    connect(&m_verify, SIGNAL(clicked()), this, SLOT(verifyMemberInServices()));

    m_layout.addRow("Nom: ", &m_nom);
    m_layout.addRow("Prénom: ", &m_prenom);
    m_layout.addRow("Pseudal: ", &m_pseudo);
    m_layout.addRow("Courriel: ", &m_mail);
    m_layout.addRow("Téléphone: ", &m_num);
    m_layout.addRow("N° étudiant: ", &m_numCarte);
    m_layout.addRow("Cotisation payée: ", &m_estPaye);

    h_box->addWidget(&m_ok);
    h_box->addWidget(&m_list);
    h_box->addWidget(&m_verify);

    QVBoxLayout* box = new QVBoxLayout;
    box->addLayout(&m_layout);
    box->addLayout(h_box);

    setLayout(box);
}

/**
 * @brief Vérifie si un individu est membre.
 *
 * @param nom       Nom de l’individu recherché
 * @param prenom    Prénom de l’individu recherché
 * @param numEtu    Numéro étudiant de l’individu recherché
 * @return bool     true si l’individu recherché est bien un membre. false sinon.
 */
bool Widget::estDedans(QString nom, QString prenom, QString numEtu)
{
    QFile file("membres.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream flux(&file);
    QString texte;
    bool tmp = false;

    while(!flux.atEnd()){
        texte = flux.readLine();

        //!
        if (texte.section(";",0,0).compare(nom) != 0 ||
            texte.section(";",1,1).compare(prenom) != 0 ||
            texte.section(";",5,5).compare(numEtu) != 0)
        {
            tmp = true;
            break;
        }
    }
    return tmp;
}

/**
 * @brief Widget::~Widget un destructeur
 */
Widget::~Widget()
{

}

/**
 * @brief Widget::setMail   remplit le champ m_mail (adresse mail)
 *  à partir du pattern 'prenom.nom@etu.univ-nantes.fr
 * @param s                 de type QString
 */
void Widget::setMail(QString s)
{
    m_mail.setText(s.toLower() + "." + m_nom.text().toLower() + "@etu.univ-nantes.fr");
}

void Widget::flush()
{
    m_nom.setText("");
    m_prenom.setText("");
    m_pseudo.setText("");
    m_mail.setText("");
    m_num.setText("");
    m_numCarte.setText("");
    m_estPaye.setChecked(false);
}

/**
 * @brief
 *
 */
void Widget::addMember()
{
    QFile file("membres.txt");

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;

    if (!estDedans(m_nom.text(), m_prenom.text(), m_numCarte.text()))
    {
        QString s(m_nom.text() + ";" + m_prenom.text() + ";" + m_pseudo.text() + ";" + m_mail.text() + ";" + m_num.text() + ";" + m_numCarte.text() + ";" + (m_estPaye.isChecked() ? "oui\n" : "non\n"));
        file.write(s.toLatin1(), s.size());
        flush();
        updatelistMember();
    }
}

/**
 * @brief
 *
 */
void Widget::listMember()
{
    m_table.clear();
    m_table.setRowCount(0);
    QFile file("membres.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream flux(&file);
    QString texte;
    int i = 0;
    while(!flux.atEnd()){
        texte = flux.readLine();

        m_table.insertRow(i);
        m_table.setItem(i, 0, new QTableWidgetItem(texte.section(";",0,0)));
        m_table.setItem(i, 1, new QTableWidgetItem(texte.section(";",1,1)));
        m_table.setItem(i, 2, new QTableWidgetItem(texte.section(";",2,2)));
        m_table.setItem(i, 3, new QTableWidgetItem(texte.section(";",3,3)));
        m_table.setItem(i, 4, new QTableWidgetItem(texte.section(";",4,4)));
        m_table.setItem(i, 5, new QTableWidgetItem(texte.section(";",5,5)));
        m_table.setItem(i, 6, new QTableWidgetItem(texte.section(";",6,6)));

        i++;
    }

    m_table.show();
}

/**
 * @brief
 *
 */
void Widget::updatelistMember()
{
    m_table.clear();
    m_table.setRowCount(0);
    QFile file("membres.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream flux(&file);
    QString texte;
    int i = 0;
    while(!flux.atEnd()){
        texte = flux.readLine();

        m_table.insertRow(i);
        m_table.setItem(i, 0, new QTableWidgetItem(texte.section(";",0,0)));
        m_table.setItem(i, 1, new QTableWidgetItem(texte.section(";",1,1)));
        m_table.setItem(i, 2, new QTableWidgetItem(texte.section(";",2,2)));
        m_table.setItem(i, 3, new QTableWidgetItem(texte.section(";",3,3)));
        m_table.setItem(i, 4, new QTableWidgetItem(texte.section(";",4,4)));
        m_table.setItem(i, 5, new QTableWidgetItem(texte.section(";",5,5)));
        m_table.setItem(i, 6, new QTableWidgetItem(texte.section(";",6,6)));

        i++;
    }
}
