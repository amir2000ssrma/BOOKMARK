#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "mytreemodel.h"
#include "myproxymodel.h"
#include <QQuickItem>
#include <QQmlComponent>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    myTreeModel mytreemodel;



    Myproxymodel myproxymodel;
    myproxymodel.setSourceModel(&mytreemodel);
    engine.rootContext()->setContextProperty("myproxymodel", &myproxymodel);
    QQmlComponent* comp = new QQmlComponent(&engine);
    QObject::connect(comp, &QQmlComponent::statusChanged, [&](QQmlComponent::Status status){
        if(status == QQmlComponent::Error){
            qDebug()<<"Can not load this: "<<comp->errorString();
        }

        if(status == QQmlComponent::Ready){
            QQuickItem *item = qobject_cast<QQuickItem*>(comp->create());

            mytreemodel.createparent("Aircraft");
            mytreemodel.createparent("Square");
            mytreemodel.createparent("Circle");
            mytreemodel.createparent("Rectangle");

            mytreemodel.appendtoparent("Aircraft","NFT2526", item);
            mytreemodel.appendtoparent("Aircraft","NFT2526", item);
            mytreemodel.appendtoparent("Square","sqr1", item);
            mytreemodel.appendtoparent("Square","sqr2", item);
            mytreemodel.appendtoparent("Circle","cir1", item);
            mytreemodel.appendtoparent("Circle","cir2", item);
            mytreemodel.appendtoparent("Rectangle","rec1", item);
            mytreemodel.appendtoparent("Rectangle","rec2", item);
        }
    });
    comp->loadUrl(QUrl("qrc:/ShowWindow.qml"));
    const QUrl url(u"qrc:/BOOKMARK/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
