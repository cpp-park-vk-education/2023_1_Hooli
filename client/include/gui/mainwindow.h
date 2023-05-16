#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "login.h"

#include "oauthprovider.h"

#include "signup.h"
#include <QMainWindow>

#include <QApplication>
#include <QDesktopServices>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

#include "api_client/Base/client.hpp"
#include <memory>

#include <QtNetwork/QNetworkReply>
#include <QtNetworkAuth/QAbstractOAuthReplyHandler>
#include <QtNetworkAuth/QOAuth2AuthorizationCodeFlow>

#include <QUrl>
#include <QWidget>

#include "client/message_info.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void OAuthVK(const std::function<void(QOAuth2AuthorizationCodeFlow *)> &onSuccess);

  void OAuthYT(const std::function<void(QOAuth2AuthorizationCodeFlow *)> &onSuccess);
    /*Callback Methods*/

  /*mainpage*/
  /*колбэки для вк*/
  void MP_VK_getAlbums();
  void MP_VK_getVideo();

  /*Колбеки для ютуба*/
  void MP_YT_getAlbums();
  void MP_YT_getVideo();

private slots:
  void on_main_button_clicked();

  void on_AlbomsButton_clicked();

  void on_VK_button_clicked();

  void on_YT_Button_clicked();

  void on_Config_button_clicked();

  void on_button_login_clicked();

  void on_signUp_button_clicked();

  void on_VK_getAllAlboms_clicked();

  void on_VK_main_import_items_clicked();

private:
  Ui::MainWindow *ui;
  std::unique_ptr<APIClient> api_client;
};

#endif // MAINWINDOW_H
