#pragma once

#include "CorePrivate.h"
#include "ClassFactory.h"

namespace BM
{
    class CORE_DLL Application : public QApplication
    {
        Q_OBJECT

    public:
        typedef QHash<QString, QSettings::SettingsMap> SettingsCollection;

    public:
        Application(QString name, int argc, char* argv[]);

    public:
        virtual int Run();

        const QDir& DataDir() { return m_DataDir; }
        
        QSettings::SettingsMap& Settings(const QString& name) { return m_Settings[name]; }
        QVariant GetSetting(const QString& name, const QString& key, const QVariant& defaultValue = QVariant()) const;

    protected:
        virtual bool Init();
        virtual void InitDataDir();
        virtual void LoadSettings();

        virtual void LoadSettings(QDir dir);

    protected slots:
        virtual void Exit();

    protected:
        QDir                m_DataDir;
        SettingsCollection  m_Settings;

    public:
        static Application& Instance() { return *(qobject_cast<Application*>(instance())); }
    };
}
