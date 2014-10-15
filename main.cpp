#include "widget.h"
#include <QApplication>
#include <QTextCodec>

/**
 * @brief Fonction principale de l’application.
 *
 * @param argc
 * @param argv[]
 * @return int      supérieur ou égal à 0 si erreur. généré par QApplication.exec()
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    Widget w;
    w.show();

    return a.exec();
}
