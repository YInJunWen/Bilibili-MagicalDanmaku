#ifndef SQLSERVICE_H
#define SQLSERVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonObject>
#include "livedanmaku.h"
#include "myjson.h"

class SqlService : public QObject
{
    Q_OBJECT
public:
    explicit SqlService(QObject *parent = nullptr);
    virtual ~SqlService();

    bool isOpen() const;
    void setDbPath(const QString& dbDir);
    QString getDbPath() const;
    QSqlDatabase getDb() const;
    QSqlQuery getQuery(const QString& sql) const;

    QString getNextFansArchive();
    MyJson getFansArchives(const QString &uid);
    QList<MyJson> getUserDanmakuList(const QString &uid, qint64 startTime, int maxCount = 100);
    QList<MyJson> getUserGiftList(const QString &uid, qint64 startTime, int maxCount = 100);
    void clearFansArchivesAll();
    void clearFansArchivesByRoomId(const QString& roomId);
    void clearFansArchivesByNoRoom();

signals:
    void signalError(const QString& err);

public slots:
    void open();
    void close();
    void initTables();
    void upgradeDb(const QString& newVersion);
    void insertDanmaku(const LiveDanmaku& danmaku);
    void insertMusic(const LiveDanmaku& danmaku);
    void insertCmd(const QString& cmd, const QString &data);
    void insertFansArchive(const QString& uid, const QString& uname, const QString& archive);
    bool exec(const QString& sql);
    bool tryExec(const QString& sql);

private:
    bool hasTable(const QString& name) const;
    bool createTable(const QString& sql);

private:
    QString dbPath;
    QSqlDatabase db;
};

#endif // SQLSERVICE_H
