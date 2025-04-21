#include <QApplication>
#include <memory>
#include <qobject.h>

#include "data/msgrepo.hpp"
#include "event/handler.hpp"
#include "event/userevent.hpp"
#include "mainwidget.hpp"
#include "service/userservice.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    UserService userService;

    MainWidget mainWidget{userService};
    mainWidget.show();

    auto addUserHandler = CreateHandler<UserEvent>(
        [&](auto event) { mainWidget.addUser(event.user()); });

    userService.addUserAddHandler(addUserHandler);

    auto deleteUserHandler = CreateHandler<UserEvent>(
        [&](auto event) { mainWidget.deleteUser(event.user()); });

    MessageRepositoryRef globalMessageRepo =
        std::make_shared<MessageRepository>(RepositoryType::GLOBAL);

    mainWidget.setMessageRepository(globalMessageRepo);

    mainWidget.setMessageHandler([&](std::string text) {
        if (auto repo = mainWidget.messageRepository()) {
            repo->createMessage(text, userService.activeUser());
            mainWidget.clearMessageText();
        }
    });

    return app.exec();
}