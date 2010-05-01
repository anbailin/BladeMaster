#include "CorePrivate.h"
#include "Application.h"

namespace BM
{
    Application::Application(QString name, int argc, char* argv[])
        : QApplication(argc, argv)
    {
        // this name will be used to get application data
        setApplicationName(name);

        connect(this, SIGNAL(aboutToQuit()), this, SLOT(Exit()));
    }

    int Application::Run()
    {
        if (!Init())
        {
            Exit();
            return -1;
        }
        return exec();
    }

    bool Application::Init()
    {
        InitDataDir();
        LoadSettings();
        return true;
    }

    void Application::Exit()
    {
    }

    void Application::InitDataDir()
    {
        QString app_dir = applicationDirPath();

        QString def_data = "/Data/Default";
        QString app_data = "/Data/" + applicationName();

        QStringList def_data_dirs;
        def_data_dirs << app_dir + def_data;
        def_data_dirs << app_dir + "/.." + def_data;

        QStringList app_data_dirs;
        app_data_dirs << app_dir + app_data;
        app_data_dirs << app_dir + "/../Dev" + app_data;

        QDir::setSearchPaths("DefData", def_data_dirs);
        QDir::setSearchPaths("AppData", app_data_dirs);
        QDir::setSearchPaths("Data",    app_data_dirs + def_data_dirs);
    }

    void Application::LoadSettings()
    {
        LoadSettings(QDir("DefData:Settings"));
        LoadSettings(QDir("AppData:Settings"));
    }

    void Application::LoadSettings(QDir dir)
    {
        if (dir.exists())
        {
            QFileInfoList list = dir.entryInfoList(QStringList("*.ini"));
            for (int i = 0; i < list.count(); i++)
            {
                QSettings settings(list[i].absoluteFilePath(), QSettings::IniFormat);

                QString name = list[i].completeBaseName();
                QSettings::SettingsMap& map = m_Settings[name];

                QStringList keys = settings.allKeys();
                for (int i = 0; i < keys.count(); i++)
                {
                    map[keys[i]] = settings.value(keys[i]);
                }
            }
        }
    }

    QVariant Application::GetSetting(const QString& name, const QString& key, const QVariant& defaultValue) const
    {
        if (m_Settings.contains(name))
        {
            if (m_Settings[name].contains(key))
            {
                return m_Settings[name][key];
            }
            else
            {
                qWarning() << "Failed to get setting" << key << "in" << name + ".ini." << "Key not exists.";
            }
        }
        else
        {
            qWarning() << "Failed to get setting" << key << "in" << name + ".ini." << "File not exists.";
        }
        return defaultValue;
    }
}
