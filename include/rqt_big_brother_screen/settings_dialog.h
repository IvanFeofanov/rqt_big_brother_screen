#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <rqt_big_brother_screen/ui_settings_dialog.h>

#include <image_transport/image_transport.h>

#include <QDialog>
#include <QString>
#include <QSet>
#include <QList>

namespace rqt_big_brother_screen
{

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget* parent = 0);

    ~SettingsDialog();

    void selectTopicImage(const QString &topic);
    QString topicImage();

private slots:
    void updateTopicList();
    void updateInputImageTopicsList();

private:
    QSet<QString> getTopics(const QSet<QString> &message_types);

private:
    Ui::Settings* ui_;

};

}
#endif
