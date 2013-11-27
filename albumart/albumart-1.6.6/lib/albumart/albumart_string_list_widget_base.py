# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'albumart_string_list_widget_base.ui'
#
# Created: ma elo    18 23:07:11 2008
#      by: The PyQt User Interface Compiler (pyuic) 3.17.4
#
# WARNING! All changes made in this file will be lost!


from qt import *


class StringListWidgetBase(QWidget):
    def __init__(self,parent = None,name = None,fl = 0):
        QWidget.__init__(self,parent,name,fl)

        if not name:
            self.setName("StringListWidgetBase")


        StringListWidgetBaseLayout = QVBoxLayout(self,11,6,"StringListWidgetBaseLayout")

        self.listBox = QListBox(self,"listBox")
        StringListWidgetBaseLayout.addWidget(self.listBox)

        layout2 = QGridLayout(None,1,1,0,6,"layout2")

        self.removeButton = QPushButton(self,"removeButton")
        self.removeButton.setEnabled(0)

        layout2.addWidget(self.removeButton,1,2)

        self.lineEdit = QLineEdit(self,"lineEdit")

        layout2.addMultiCellWidget(self.lineEdit,0,0,0,2)

        self.addButton = QPushButton(self,"addButton")
        self.addButton.setEnabled(0)

        layout2.addWidget(self.addButton,1,1)
        spacer1 = QSpacerItem(241,21,QSizePolicy.Expanding,QSizePolicy.Minimum)
        layout2.addItem(spacer1,1,0)
        StringListWidgetBaseLayout.addLayout(layout2)

        self.languageChange()

        self.resize(QSize(454,384).expandedTo(self.minimumSizeHint()))
        self.clearWState(Qt.WState_Polished)

        self.connect(self.listBox,SIGNAL("selectionChanged()"),self.itemSelected)
        self.connect(self.addButton,SIGNAL("clicked()"),self.addButtonClicked)
        self.connect(self.removeButton,SIGNAL("clicked()"),self.removeButtonClicked)
        self.connect(self.lineEdit,SIGNAL("textChanged(const QString&)"),self.textChanged)


    def languageChange(self):
        self.setCaption(self.__tr("StringListWidget"))
        self.removeButton.setText(self.__tr("&Remove"))
        self.removeButton.setAccel(QKeySequence(self.__tr("Alt+R")))
        self.addButton.setText(self.__tr("&Add"))
        self.addButton.setAccel(QKeySequence(self.__tr("Alt+A")))


    def itemSelected(self):
        print "StringListWidgetBase.itemSelected(): Not implemented yet"

    def addButtonClicked(self):
        print "StringListWidgetBase.addButtonClicked(): Not implemented yet"

    def removeButtonClicked(self):
        print "StringListWidgetBase.removeButtonClicked(): Not implemented yet"

    def textChanged(self):
        print "StringListWidgetBase.textChanged(): Not implemented yet"

    def __tr(self,s,c = None):
        return qApp.translate("StringListWidgetBase",s,c)
