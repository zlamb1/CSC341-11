#include <QApplication>
#include <memory>

#include "data/msgrepo.hpp"
#include "event/handler.hpp"
#include "event/userevent.hpp"
#include "mainwindow.hpp"
#include "service/userservice.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    UserService userService;

    MainWindow mainWindow{userService};
    mainWindow.show();

    auto addUserHandler = CreateHandler<UserEvent>(
        [&](auto event) { mainWindow.addUser(event.user()); });

    userService.addUserAddHandler(addUserHandler);

    auto deleteUserHandler = CreateHandler<UserEvent>(
        [&](auto event) { mainWindow.deleteUser(event.user()); });

    IMessageRepositoryRef globalMessageRepo =
        std::make_shared<MessageRepository>(RepositoryType::GLOBAL);

    mainWindow.setMessageRepository(globalMessageRepo);

    mainWindow.setMessageHandler([&](std::string text) {
        if (auto repo = mainWindow.messageRepository()) {
            repo->createMessage(text, userService.activeUser());
            mainWindow.clearMessageText();
        }
    });

    return app.exec();
}