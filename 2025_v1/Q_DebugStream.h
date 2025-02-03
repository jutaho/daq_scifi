#ifndef Q_DEBUGSTREAM_H
#define Q_DEBUGSTREAM_H

#include <iostream>
#include <streambuf>
#include <string>

#include <QTextBrowser>
#include <QtGlobal>

#define DS_DEBUG    0x01
#define DS_INFO     0x02
#define DS_WARNING  0x04
#define DS_CRITICAL 0x08
#define DS_FATAL    0x10


class Q_DebugStream : public std::basic_streambuf<char>
{
public:
    Q_DebugStream(std::ostream &stream, QTextBrowser* text_edit);
    ~Q_DebugStream();
    static void registerQDebugMessageHandler();

    int displayMask;
    int detailsMask;

private:

    static void myQDebugMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

protected:

    //This is called when a std::endl has been inserted into the stream
    virtual int_type overflow(int_type v);
    virtual std::streamsize xsputn(const char *p, std::streamsize n);


private:
    std::ostream &m_stream;
    std::streambuf *m_old_buf;
    QTextBrowser* log_window;
};


#endif // Q_DEBUGSTREAM_H
