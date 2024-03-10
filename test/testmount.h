#pragma once

#include "assets/mount.h"
#include "assets/mountaccess.h"

#include <QFile>
#include <QObject>
#include <QRegularExpression>
#include <QtTest/QTest>

class TestMount : public QObject
{
    Q_OBJECT

  private Q_SLOTS:
    void init()
    {
        access = new MountAccess;
    }
    void cleanup()
    {
        delete access;
    }

    void openArchive_data()
    {
        QTest::addColumn<QStringList>("paths");

        QTest::newRow("Load one archive") << QStringList({"archive.zip"});
        QTest::newRow("Load multiple archives") << QStringList({"second_archive.zip", "archive.zip"});
    }
    void openArchive()
    {
        QFETCH(QStringList, paths);

        for (QString path : paths) {
            QTest::ignoreMessage(QtInfoMsg, QString("Loading mount at \"%1\"").arg(path).toUtf8());
            QTest::ignoreMessage(QtInfoMsg, QString("Finished loading \"%1\"").arg(path).toUtf8());
        }
        access->loadMounts(paths);
    }

    void failToOpenArchive_data()
    {
        QTest::addColumn<QStringList>("archives");

        QTest::newRow("Missing archive") << QStringList{"missing_archive.zip"};
        QTest::newRow("Corrupt archive") << QStringList{"corrupt_archive.zip"};
    }
    void failToOpenArchive()
    {
        QFETCH(QStringList, archives);

        QVERIFY_THROWS_EXCEPTION(std::exception, access->loadMounts(archives));
    }

    void fetchContent_data()
    {
        QTest::addColumn<QStringList>("paths");
        QTest::addColumn<QString>("file");
        QTest::addColumn<bool>("result");

        QTest::newRow("Fetch file.txt") << QStringList{"archive.zip"} << QString("file.txt") << true;
        QTest::newRow("Fetch other_file.txt") << QStringList{"second_archive.zip"} << QString("other_file.txt") << true;
        QTest::newRow("Failed to fetch fake_file.txt") << QStringList{"archive.zip"} << QString("fake_file.txt") << false;
    }
    void fetchContent()
    {
        QFETCH(QStringList, paths);
        QFETCH(QString, file);
        QFETCH(bool, result);

        access->loadMounts(paths);
        QVERIFY(access->fetch(file).has_value() == result);
    }

    void fetchAndCheckContent_data()
    {
        QTest::addColumn<QStringList>("archives");
        QTest::addColumn<QString>("path");
        QTest::addColumn<QString>("data_path");

        QTest::newRow("file.txt (archive.zip)") << QStringList{"archive.zip"} << "file.txt"
                                                << "file_content.txt";
        QTest::newRow("file.txt (second_archive.zip)") << QStringList{"second_archive.zip", "archive.zip"} << "file.txt"
                                                       << "second_file_content.txt";
        QTest::newRow("other_file.txt (second_archive.zip)") << QStringList{"archive.zip", "second_archive.zip"} << "other_file.txt"
                                                             << "other_file_content.txt";
    }
    void fetchAndCheckContent()
    {
        QFETCH(QStringList, archives);
        QFETCH(QString, path);
        QFETCH(QString, data_path);

        QFile file(data_path);
        file.open(QIODevice::ReadOnly);
        QByteArray expected_data = file.readAll();

        access->loadMounts(archives);
        QCOMPARE(access->fetch(path).value(), expected_data);
    }

  private:
    MountAccess *access = nullptr;
};
