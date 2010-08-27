#ifndef LOGIN_PROCESS_H
#define LOGIN_PROCESS_H

#include "UnicornSession.h"

#include "lib/DllExportMacro.h"

#include <QObject>

class QHostAddress;
class QTcpServer;
class QTcpSocket;

namespace unicorn
{


/**
* This class is used during the web authentication process in order to be able
* to return to the application after the authentication is completed.
*/
class UNICORN_DLLEXPORT TinyWebServer: public QObject
{
    Q_OBJECT
public:
    TinyWebServer( QObject* parent = 0 );

    int serverPort() const;
    QHostAddress serverAddress() const;

signals:
    void gotToken( QString token );

private:
    void processRequest();
    void sendRedirect();

private slots:
    void onNewConnection();
    void readFromSocket();

private:
    QTcpServer* m_tcpServer;
    QTcpSocket* m_clientSocket;
    QString     m_header;
    QString     m_token;
};

/**
 * This class encapsulates the whole login process.
 *
 * Call the authenticate function to start the login process
 * and connect to the gotSession signal to be notified when
 * the process finishes.
 * Whenever you call the method session() directly make sure you check
 * if it's a valid session. If it's not, you can use the showError method
 * to show a dialog with the error message.
 */
class UNICORN_DLLEXPORT LoginProcess : public QObject
{
    Q_OBJECT
public:
    LoginProcess( QObject* parent = 0 );
    ~LoginProcess();
    QString token() const;
    Session* session() const;
    QUrl authUrl() const;
    void showError() const;

public slots:
    void authenticate();
    void getSession( QString token );
    void cancel();

signals:
    void gotSession( unicorn::Session* s );

private slots:
    void onGotSession();

private: 
    TinyWebServer* m_webServer;
    Session* m_session;
    QString m_token;
    lastfm::ws::ParseError m_lastError;
    QNetworkReply::NetworkError m_lastNetworkError;
    QUrl m_authUrl;
};

}// namespace unicorn

#endif // LOGIN_PROCESS_H
