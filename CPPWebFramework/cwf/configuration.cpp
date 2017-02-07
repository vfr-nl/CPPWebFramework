/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "configuration.h"

namespace CWF
{
    Configuration::Configuration(const QString &serverFilesPath)
    {
        const QString configFile = getConfigFile(serverFilesPath);
        if(!configFile.isEmpty())
        {
            QSettings settings(configFile, QSettings::IniFormat);
            settings.beginGroup("config");
            host.setAddress(settings.value("host").toString());
            port                  = settings.value("port").toInt();
            maxThread             = settings.value("maxThread").toInt();
            cleanupInterval       = settings.value("cleanupInterval").toInt();
            timeOut               = settings.value("timeOut").toInt();
            sslKeyFile            = settings.value("sslKeyFile").toString();
            sslCertFile           = settings.value("sslCertFile").toString();
            sessionExpirationTime = settings.value("sessionExpirationTime").toInt();
            logFilePath           = settings.value("logFilePath").toString();
            path                  = settings.value("path").toString();
            maxUploadFile         = settings.value("maxUploadFile").toLongLong();
            indexPage             = settings.value("indexPage").toString();
            accessCPPWebIni       = settings.value("accessCPPWebIni").toBool();
            suffix                = settings.value("suffix").toString();
            accessServerPages     = settings.value("accessServerPages").toBool();
            settings.endGroup();

            FileManager fileManager;
            fileManager.removeLastBar(path);
            fileManager.removeFirstBar(sslCertFile);
            fileManager.removeFirstBar(sslKeyFile);
            fileManager.removeFirstBar(logFilePath);
            fileManager.removeLastBar(logFilePath);
            logFilePath = path + "/" + logFilePath;

            if(!sslKeyFile.isEmpty())
                sslKeyFile           = path + "/" + sslKeyFile;
            if(!sslCertFile.isEmpty())
                sslCertFile          = path + "/" + sslCertFile;
        }
    }

    QString Configuration::getConfigFile(const QString &serverFilesPath) const
    {
        if (serverFilesPath.isEmpty())
            return QString();

        QString configFile = serverFilesPath;
        FileManager().removeLastBar(configFile);
        configFile += "/config/CPPWeb.ini";

        if(!FileManager::exists(configFile))
        {
            qDebug() << "The server config file (CPPWeb.ini) could not be found.";
            return QString();
        }

        return configFile;
    }

    int Configuration::getTimeOut() const
    {
        return timeOut;
    }

    void Configuration::setTimeOut(int value)
    {
        timeOut = value;
    }

    int Configuration::getSessionExpirationTime() const
    {
        return sessionExpirationTime;
    }

    void Configuration::setSessionExpirationTime(int value)
    {
        sessionExpirationTime = value;
    }

    int Configuration::getCleanupInterval() const
    {
        return cleanupInterval;
    }

    void Configuration::setCleanupInterval(int value)
    {
        cleanupInterval = value;
    }

    int Configuration::getPort() const
    {
        return port;
    }

    void Configuration::setPort(int value)
    {
        port = value;
    }

    int Configuration::getMaxThread() const
    {
        return maxThread;
    }

    void Configuration::setMaxThread(int value)
    {
        maxThread = value;
    }

    QString Configuration::getSslKeyFile() const
    {
        return sslKeyFile;
    }

    void Configuration::setSslKeyFile(const QString &value)
    {
        sslKeyFile = value;
    }

    QString Configuration::getSslCertFile() const
    {
        return sslCertFile;
    }

    void Configuration::setSslCertFile(const QString &value)
    {
        sslCertFile = value;
    }

    QString Configuration::getPath() const
    {
        return path;
    }

    void Configuration::setPath(const QString &value)
    {
        path = value;
    }

    QString Configuration::getDomain() const
    {
        return domain;
    }

    void Configuration::setDomain(const QString &value)
    {
        domain = value;
    }

    QString Configuration::getLogFilePath() const
    {
        return logFilePath;
    }

    void Configuration::setLogFilePath(const QString &value)
    {
        logFilePath = value;
    }

    QHostAddress Configuration::getHost() const
    {
        return host;
    }

    void Configuration::setHost(const QHostAddress &value)
    {
        host = value;
    }

    qint64 Configuration::getMaxUploadFile() const
    {
        return maxUploadFile;
    }

    void Configuration::setMaxUploadFile(const qint64 &value)
    {
        maxUploadFile = value;
    }

    bool Configuration::isValid()
    {
        return !host.isNull() && port != 0;
    }
}
