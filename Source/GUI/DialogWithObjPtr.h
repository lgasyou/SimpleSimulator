#pragma once
#include <QWidget>
#include <algorithm>
#include <vector>

#include "Source/Interface.h"

class DialogWithObjPtr : public QWidget {
    Q_OBJECT

public:
    using QWidget::QWidget;

    static void updateData(Object *oldData, Object *newData);

private:
    static std::vector<DialogWithObjPtr *> ptrs_;

    Object *data_;
};

inline void DialogWithObjPtr::updateData(Object *oldData, Object *newData) {
    auto it = std::find_if(ptrs_.begin(), ptrs_.end(), [=](DialogWithObjPtr *p) {
        return p->data_ == oldData;
    });
}
