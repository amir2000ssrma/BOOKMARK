import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt.labs.qmlmodels
import QtQuick.Layouts
import QtQml.Models


Window {
    id: root
    width: 988
    height: 988
    visible: true
    title: qsTr("Hello World")
    // color:"pink"
    property color projectcolor: "#003569"
    property color projectcoloropacity50 : "#00356980"
    property string projectfont: "Roboto"

    Window{
        id: mywnd
        Item{
            anchors.fill: parent
            id:testwindow
        }
        width: 500
        height: 500
        color: "pink"
    }


    Rectangle {
        id: mainrec
        color: "silver"


        width: 380
        height: root.height
        radius: 20
        ColumnLayout {
            anchors.fill: parent
            Layout.fillWidth: true
            Layout.fillHeight: true
            Text {
                id: qarch
                height: 36
                width: 89
                color: projectcolor
                font.family: projectfont
                font.pixelSize: 30
                font.styleName: "Roman"
                font.weight: 700
                lineHeight: 1
                Layout.topMargin:40
                Layout.leftMargin: 91
                text: "Qarch"
            }
            Item{
                id:bookmark
                width:271
                height:20
                Layout.leftMargin: 94
                Layout.topMargin: 31
                Text{
                    color: projectcolor
                    font.family: projectfont
                    font.pixelSize: 20
                    font.styleName: "Roman"
                    font.weight: 400
                    lineHeight: 1
                    text: "Bookmark"
                }
                Image{
                    id:logout
                    source: "qrc:/icons/logout.png"
                    width:20
                    height:20
                    anchors.right: bookmark.right
                    anchors.verticalCenter: bookmark.verticalCenter
                }
            }
            Rectangle{
                color:projectcolor
                opacity: 0.5
                height: 1
                width: 271
                Layout.leftMargin: 91
            }
            TextField {
                implicitHeight: 35
                implicitWidth: 271
                Layout.leftMargin: 91
                leftPadding: 39
                color: "black"
                placeholderText: "Search"
                placeholderTextColor: projectcolor  /************/
                font.family: projectfont
                font.pixelSize: 17
                font.styleName: "Roman"
                font.weight: 400
                Layout.bottomMargin: 15
                background: Rectangle {
                    color: projectcolor
                    opacity: 0.2
                    radius: 15
                    Image {
                        id: searchicon
                        source: "qrc:/icons/search.png"
                        height: 27
                        width: 27
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: 10
                    }
                }
                onTextChanged: {
                    myproxymodel.searchedText = text
                }
            }

            Item{
                id:treeitem
                width:271
                Layout.fillHeight: true
                Layout.leftMargin: 91
                z:0
                TreeView {
                    id:treeview
                    anchors.fill: parent
                    anchors.centerIn: parent
                    model: myproxymodel
                    rowSpacing: 7

                    selectionModel:ItemSelectionModel{
                        id:myselection
                    }

                    delegate: Item {
                        id: treeDelegate
                        readonly property real indent: 20
                        readonly property real padding: 5
                        // Assigned to by TreeView:
                        required property TreeView treeView
                        required property bool isTreeNode
                        required property bool expanded
                        required property int hasChildren
                        required property int depth
                        required property bool selected
                        required property bool current

                        implicitWidth: padding + itemText.x + itemText.implicitWidth + padding
                        implicitHeight: itemText.implicitHeight * 1.5

                        Rectangle{
                            id:backgroundrec
                            anchors.top: itemRect.top
                            anchors.left: itemRect.left
                            width: itemRect.width
                            height: treeDelegate.hasChildren ? (myproxymodel ? (myproxymodel.proxy_rowcount(treeview.index(row,column)) +1) * itemRect.height: 0) :0
                            radius: 12
                            visible: treeDelegate.expanded
                            color:"#DEE3E6"
                            opacity: 0.1
                        }

                        Rectangle {
                            id: itemRect
                            width:271
                            height: 30
                            radius: 12
                            color:{
                                if(treeDelegate.selected)
                                    return "#DEE3E6"
                                else
                                    return treeDelegate.hasChildren ? "#DEE3E6" :"transparent"
                            }
                            RowLayout{
                                anchors.fill: parent
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                spacing: 0
                                Image {
                                    id: itemIcon
                                    source: setitemIcon()
                                    Layout.preferredWidth: 24
                                    Layout.preferredHeight: 24
                                    Layout.leftMargin: 10
                                    Layout.alignment: Qt.AlignVCenter
                                    visible: myproxymodel ? myproxymodel.proxy_is_parent(treeview.index(row,column)) : false
                                    function setitemIcon(){
                                        if(model.display ==="Aircraft")
                                            return "qrc:/icons/aircraft.png"
                                        else if(model.display ==="Square")
                                            return "qrc:/icons/square.png"
                                        else if(model.display ==="Circle")
                                            return "qrc:/icons/circle.png"
                                        else if(model.display ==="Rectangle")
                                            return "qrc:/icons/rectangle.png"
                                        else
                                            return ""
                                    }
                                }
                                Text {
                                    id: itemText
                                    Layout.alignment: Qt.AlignLeft
                                    Layout.leftMargin: 5
                                    text: model.display
                                    font.family: projectfont
                                    font.pixelSize: 15
                                    font.weight: 400
                                    color: projectcolor
                                    Layout.fillWidth: true
                                }
                                Button{
                                    id:popUpBtn
                                    visible: myproxymodel ? !myproxymodel.proxy_is_parent(treeview.index(row,column)) : false
                                    Layout.preferredWidth: 20
                                    Layout.preferredHeight: 20
                                    background: Image {
                                        source: "qrc:/icons/easy-to-find.png"
                                        width: 20
                                        height: 20
                                    }
                                    onClicked: {
                                        console.log("pop up button onclicked called")

                                        var item = myproxymodel.rowItem(treeview.index(row,column))
                                        console.log(item)
                                        mywnd.visible = true
                                        item.parent = testwindow
                                    }
                                }
                                Button{
                                    id:removeBtn
                                    visible: myproxymodel ? !myproxymodel.proxy_is_parent(treeview.index(row,column)) : false
                                    Layout.preferredWidth: 20
                                    Layout.preferredHeight: 20
                                    Layout.rightMargin: 5
                                    background: Image{
                                        source:"qrc:/icons/multiply.png"
                                        width: 20
                                        height: 20
                                    }
                                    onClicked: {
                                        myproxymodel.proxyremovechild(treeview.index(row,column))
                                    }
                                }
                                Image{
                                    id:indicator
                                    rotation: treeDelegate.expanded ? 180 : 0
                                    visible: myproxymodel ? myproxymodel.proxy_is_parent(treeview.index(row,column)) && treeDelegate.hasChildren : false
                                    Layout.preferredWidth: 16
                                    Layout.preferredHeight: 16
                                    Layout.alignment:  Qt.AlignRight
                                    Layout.rightMargin: 5
                                    source: "qrc:/icons/down.png"
                                }
                            }

                            HoverHandler {
                                onHoveredChanged: {
                                    if (hovered) {
                                        myselection.select(treeview.index(row,column),ItemSelectionModel.Select)
                                    } else {
                                        myselection.select(treeview.index(row,column),ItemSelectionModel.Deselect)
                                    }
                                }
                            }

                            MouseArea {
                                id: mousearea
                                anchors.fill: parent
                                z: -5

                                onClicked:{
                                    treeview.toggleExpanded(row)
                                }
                            }
                        }

                    }


                }
            }
        }
    }
}
