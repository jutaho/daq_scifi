#include "Q_DebugStream.h"

Q_DebugStream* debugStreamHandle;

Q_DebugStream::Q_DebugStream(std::ostream &stream, QTextBrowser* text_edit) : m_stream(stream)
{
    debugStreamHandle = this;   //we can use a global variable as only one instance of QDebugStream can be active
    displayMask = DS_INFO | DS_WARNING | DS_CRITICAL | DS_FATAL;
   // detailsMask = DS_WARNING | DS_CRITICAL | DS_FATAL; //why not info too?
    detailsMask = DS_CRITICAL | DS_FATAL;
    log_window = text_edit;
    m_old_buf = stream.rdbuf();
    stream.rdbuf(this);
}

Q_DebugStream::~Q_DebugStream()
{
    m_stream.rdbuf(m_old_buf);
}

void Q_DebugStream::registerQDebugMessageHandler()
{
    qInstallMessageHandler(myQDebugMessageHandler);
}


void Q_DebugStream::myQDebugMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    //std::cout << msg.toStdString().c_str();
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type)
    {
    case QtDebugMsg:
        if (debugStreamHandle->displayMask & DS_DEBUG)
        {
            std::cout << "[DEBUG] " << localMsg.constData();
            if (debugStreamHandle->detailsMask & DS_DEBUG)
                std::cout << " (" << context.file << ":" << context.line << ", " << context.function << ")";
            std::cout << std::endl;
        }
        break;
    case QtInfoMsg:
        if (debugStreamHandle->displayMask & DS_INFO)
        {
            std::cout << "[INFO]      " << localMsg.constData();
            if (debugStreamHandle->detailsMask & DS_INFO)
                std::cout << " (" << context.file << ":" << context.line << ", " << context.function << ")";
            std::cout << std::endl;
        }
        break;
    case QtWarningMsg:
        if (debugStreamHandle->displayMask & DS_WARNING)
        {
            std::cout << "[WARNING]   " << localMsg.constData();
            if (debugStreamHandle->detailsMask & DS_WARNING)
                std::cout << " (" << context.file << ":" << context.line << ", " << context.function << ")";
            std::cout << std::endl;
        }
        break;
    case QtCriticalMsg:
        if (debugStreamHandle->displayMask & DS_CRITICAL)
        {
            std::cout << "[CRITICAL]  " << localMsg.constData();
            if (debugStreamHandle->detailsMask & DS_CRITICAL)
                std::cout << " (" << context.file << ":" << context.line << ", " << context.function << ")";
            std::cout << std::endl;
        }
        break;
    case QtFatalMsg:
        if (debugStreamHandle->displayMask & DS_FATAL)
        {
            std::cout << "[FATAL]     " << localMsg.constData();
            if (debugStreamHandle->detailsMask & DS_FATAL)
                std::cout << " (" << context.file << ":" << context.line << ", " << context.function << ")";
            std::cout << std::endl;
        }
        //abort();
    }
}

//This is called when a std::endl has been inserted into the stream
int Q_DebugStream::overflow(int_type v)
{
    if (v == '\n')
    {
        log_window->append("");
    }
    return v;
}


std::streamsize Q_DebugStream::xsputn(const char *p, std::streamsize n)
{
    QString str(p);
    str = str.left(n);
    if (str.size() == 0)
        return 0;   //don't print empty strings (i.e. don't put newline)
    if(str.contains("\n"))
    {
        QStringList strSplitted = str.split("\n");

        //log_window->moveCursor (QTextCursor::End);
        //log_window->insertPlainText (strSplitted.at(0)); //Index 0 is still on the same old line

        for(int i = 0; i < strSplitted.size(); i++)
        {
            log_window->moveCursor(QTextCursor::End);
            log_window->insertPlainText(strSplitted.at(i));
            log_window->moveCursor(QTextCursor::End);
        }
    }
    else
    {
        //log_window->moveCursor (QTextCursor::End);
        //log_window->insertPlainText (str);
        log_window->moveCursor(QTextCursor::End);
        log_window->insertPlainText(str);
        log_window->moveCursor(QTextCursor::End);
    }
    return n;
}
