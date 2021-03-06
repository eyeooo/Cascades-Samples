/* Copyright (c) 2012 Research In Motion Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include "MapViewDemo.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

using namespace bb::cascades;

MapViewDemo::MapViewDemo(bb::cascades::Application *app) :
        QObject(app)
{
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("mapViewTest", this);
    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
}

QString MapViewDemo::worldToPixelInvokable(QObject* mapObject, double lat,
        double lon)
{
    MapView* mapview = qobject_cast<MapView*>(mapObject);
    Point worldCoordinates = Point(lat, lon);
    QPoint pixels = mapview->worldToWindow(worldCoordinates);

    int x = pixels.x();
    int y = pixels.y();

    return (QString::number(x) + " " + QString::number(y));
}

void MapViewDemo::updateMarkers(QObject* mapObject, QObject* containerObject)
{
    MapView* mapview = qobject_cast<MapView*>(mapObject);
    Container* container = qobject_cast<Container*>(containerObject);
    for (int i = 0; i < container->count(); i++) {
        QPoint xy = worldToPixel(mapview,
                container->at(i)->property("lat").value<double>(),
                container->at(i)->property("lon").value<double>());
        container->at(i)->setProperty("x", xy.x());
        container->at(i)->setProperty("y", xy.y());
    }

}

QPoint MapViewDemo::worldToPixel(QObject* mapObject, double lat, double lon)
{
    MapView* mapview = qobject_cast<MapView*>(mapObject);
    Point worldCoordinates = Point(lat, lon);
    return mapview->worldToWindow(worldCoordinates);
}
