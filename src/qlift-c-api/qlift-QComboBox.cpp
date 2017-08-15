#include <QComboBox>

#define QLIFT_C_API_INTERNAL
#include "qlift-QComboBox.h"


void* QComboBox_new(void *parent) {
    return static_cast<void*>(new QComboBox {static_cast<QWidget*>(parent)});
}

void QComboBox_delete(void *comboBox) {
    delete static_cast<QComboBox*>(comboBox);
}

void QComboBox_addItem(void *comboBox, const char *text, void *userData) {
    if (userData) {
        static_cast<QComboBox*>(comboBox)->addItem(text, *static_cast<QVariant*>(userData));
    } else {
        static_cast<QComboBox*>(comboBox)->addItem(text);
    }
}

void QComboBox_currentIndexChangedInt_connect(void *comboBox, void *receiver, void *info, void (*slot_ptr)(void*, int)) {
    QObject::connect(
        static_cast<QComboBox*>(comboBox),
        static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        static_cast<QObject*>(receiver),
        [info, slot_ptr](int index) {
            (*slot_ptr)(info, index);
        }
    );
}

void QComboBox_currentIndexChangedString_connect(void *comboBox, void *receiver, void *info, void (*slot_ptr)(void*, const char*)) {
    QObject::connect(
        static_cast<QComboBox*>(comboBox),
        static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
        static_cast<QObject*>(receiver),
        [info, slot_ptr](const QString &text) {
            (*slot_ptr)(info, text.toLocal8Bit().data());
        }
    );
}

