/*******************************************************************************
Copyright (C) 2019 Milo Solutions
Contact: https://www.milosolutions.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/


#pragma once

#include <QString>
#include <QMutex>
#include <QFile>
#include <QStandardPaths>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(core)

class QMessageLogContext;

class MLog
{
public:
    enum LogLevel {
        NoLog,
        FatalLog,
        CriticalLog,
        WarningLog,
        InfoLog,
        DebugLog
    };

    static MLog *instance();
    void enableLogToFile(const QString &appName,
                         const QString &directory = QStandardPaths::writableLocation(
                             QStandardPaths::DocumentsLocation));
    void disableLogToFile();

    void enableLogToConsole();
    void disableLogToConsole();

    QString previousLogPath() const;
    QString currentLogPath() const;

    void setLogLevel(const LogLevel level);
    LogLevel logLevel() const;

private:
    Q_DISABLE_COPY(MLog)
    explicit MLog();
    ~MLog();
    static void messageHandler(QtMsgType type,
                               const QMessageLogContext &context,
                               const QString &message);
    void write(const QString &message);
    bool isMessageAllowed(const QtMsgType qtLevel) const;

    static MLog *_instance;

    QFile _logFile;
    QString _previousLogPath;
    QString _currentLogPath;
    QMutex _mutex;
    LogLevel _logLevel = DebugLog;

    static bool _logToFile;
    static bool _logToConsole;
};

MLog *logger();
