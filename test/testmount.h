#pragma once

#include "assets/mount.h"
#include "assets/mountaccess.h"

#include <QFile>
#include <QObject>
#include <QtTest/QSignalSpy>
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
        QTest::addColumn<QStringList>("archives");

        QTest::newRow("Load one archive") << QStringList({"archive.zip"});
        QTest::newRow("Load multiple archives") << QStringList({"second_archive.zip", "archive.zip"});
    }
    void openArchive()
    {
        QFETCH(QStringList, archives);
        access->loadMounts(archives);
    }

    void failToOpenArchive_data()
    {
        QTest::addColumn<QStringList>("archives");
        QTest::addColumn<MountError>("expected_error");

        QTest::newRow("Missing archive") << QStringList{"missing_archive.zip"} << MountError::FailedToLoadMount;
        QTest::newRow("Corrupt archive") << QStringList{"corrupt_archive.zip"} << MountError::FailedToLoadMount;
    }
    void failToOpenArchive()
    {
        QFETCH(QStringList, archives);
        QFETCH(MountError, expected_error);

        QSignalSpy spy(access, &MountAccess::errorOccurred);
        access->loadMounts(archives);
        QList<QVariant> results = spy.takeFirst();
        QVERIFY(results.at(0).value<MountError>() == expected_error);
    }

    void tryToFetchContent_data()
    {
        QTest::addColumn<QStringList>("archives");
        QTest::addColumn<QString>("file");
        QTest::addColumn<bool>("result");

        QTest::newRow("Fetch file.txt") << QStringList{"archive.zip"} << QString("file.txt") << true;
        QTest::newRow("Fetch other_file.txt") << QStringList{"second_archive.zip"} << QString("other_file.txt") << true;
        QTest::newRow("Failed to fetch fake_file.txt") << QStringList{"archive.zip"} << QString("fake_file.txt") << false;
    }
    void tryToFetchContent()
    {
        QFETCH(QStringList, archives);
        QFETCH(QString, file);
        QFETCH(bool, result);

        access->loadMounts(archives);
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
