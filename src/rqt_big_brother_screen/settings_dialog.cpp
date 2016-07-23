#include <rqt_big_brother_screen/settings_dialog.h>

#include <ros/master.h>

#include <QDebug>

#include <vector>
#include <string>

namespace rqt_big_brother_screen
{

SettingsDialog::SettingsDialog(QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::Settings)
{
    ui_->setupUi(this);

    connect(ui_->pushButtonRefreshTL, SIGNAL(pressed()),
            this, SLOT(updateTopicList()));

    updateTopicList();
}

SettingsDialog::~SettingsDialog()
{

}

void SettingsDialog::selectTopicImage(const QString &topic)
{
    int index = ui_->comboBoxInputImageTopicsList->findText(topic);

    if(index == -1){
        index = ui_->comboBoxInputImageTopicsList->findText("");
    }

    ui_->comboBoxInputImageTopicsList->setCurrentIndex(index);
}

QString SettingsDialog::topicImage()
{
    return ui_->comboBoxInputImageTopicsList->currentText();
}

void SettingsDialog::updateTopicList()
{
    updateInputImageTopicsList();
}

void SettingsDialog::updateInputImageTopicsList()
{
    //supported types
    QSet<QString> messages_types;
    messages_types.insert("sensor_msgs/Image");

    //curretn topic
    QString selected_topic = ui_->comboBoxInputImageTopicsList->currentText();

    //get topic list
    QStringList topics = getTopics(messages_types).values();
    topics.append("");
    qSort(topics);

    //set topic list
    ui_->comboBoxInputImageTopicsList->clear();
    ui_->comboBoxInputImageTopicsList->insertItems(0, topics);

    //restore previous selection
    selectTopicImage(selected_topic);

}

QSet<QString> SettingsDialog::getTopics(const QSet<QString> &message_types)
{
    //get topic info
    ros::master::V_TopicInfo topic_info;
    ros::master::getTopics(topic_info);

    //get all topics
    QSet<QString> all_topics;
    for(int i = 0; i < topic_info.size(); ++i){
        all_topics.insert(QString(topic_info[i].name.c_str()));
    }

    //
    QSet<QString> topics;
    for(ros::master::V_TopicInfo::const_iterator it = topic_info.begin();
            it != topic_info.end(); ++it){
        if(message_types.contains(it->datatype.c_str())){
            topics.insert(it->name.c_str());
        }
    }

    return topics;
}

}//namespace
