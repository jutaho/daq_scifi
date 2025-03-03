#include "Q_DebugStream.h"

Q_DebugStream* globalDebugStream = nullptr;

Q_DebugStream::Q_DebugStream(std::ostream &stream, QTextBrowser* text_edit)
    : m_stream(stream),
    m_old_buf(stream.rdbuf()),
    log_window(text_edit),
    displayMask(DS_DEBUG | DS_INFO | DS_WARNING | DS_CRITICAL | DS_FATAL),
    detailsMask(0)
{
    globalDebugStream = this;
    m_stream.rdbuf(this);
}

Q_DebugStream::~Q_DebugStream()
{
    m_stream.rdbuf(m_old_buf);
}

void Q_DebugStream::registerQDebugMessageHandler()
{
    qInstallMessageHandler(Q_DebugStream::myQDebugMessageHandler);
}

void Q_DebugStream::myQDebugMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (!globalDebugStream)
        return;

    QString logMessage;

    switch (type) {
    case QtDebugMsg:
        if (!(globalDebugStream->displayMask & DS_DEBUG)) return;
        logMessage += "[Debug] ";
        break;
    case QtInfoMsg:
        if (!(globalDebugStream->displayMask & DS_INFO)) return;
        logMessage += "[Info] ";
        break;
    case QtWarningMsg:
        if (!(globalDebugStream->displayMask & DS_WARNING)) return;
        logMessage += "[Warning] ";
        break;
    case QtCriticalMsg:
        if (!(globalDebugStream->displayMask & DS_CRITICAL)) return;
        logMessage += "[Critical] ";
        break;
    case QtFatalMsg:
        if (!(globalDebugStream->displayMask & DS_FATAL)) return;
        logMessage += "[Fatal] ";
        break;
    }

    if (globalDebugStream->detailsMask) {
        logMessage += QString("[%1:%2] ").arg(context.file).arg(context.line);
    }

    logMessage += msg;
    globalDebugStream->log_window->append(logMessage);

    if (type == QtFatalMsg) {
        abort();
    }
}

Q_DebugStream::int_type Q_DebugStream::overflow(int_type v)
{
    if (v == '\n') {
        log_window->append("");
    } else {
        log_window->insertPlainText(QString(QChar(v)));
    }
    return v;
}

std::streamsize Q_DebugStream::xsputn(const char *p, std::streamsize n)
{
    QString str = QString::fromLocal8Bit(p, static_cast<int>(n));
    log_window->moveCursor(QTextCursor::End);
    log_window->insertPlainText(str);
    log_window->moveCursor(QTextCursor::End);

    return n;
}
