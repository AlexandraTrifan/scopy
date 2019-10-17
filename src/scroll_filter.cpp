/*
 * Copyright 2017 Analog Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file LICENSE.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "scroll_filter.hpp"

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QEvent>
#include <QLineEdit>
#include <QSpinBox>
#include <QWidget>

using namespace adiscope;

MouseWheelWidgetGuard::MouseWheelWidgetGuard(QObject *parent)
	: QObject(parent) {}

bool MouseWheelWidgetGuard::eventFilter(QObject *o, QEvent *e) {
	const QWidget *widget = dynamic_cast<QWidget *>(o);
	if (e->type() == QEvent::Wheel && widget && !widget->hasFocus()) {
		e->ignore();
		return true;
	}
	return QObject::eventFilter(o, e);
}

void MouseWheelWidgetGuard::installEventRecursively(QWidget *parentWidget) {
	if (parentWidget->children().count() == 0) {
		return;
	}
	QList<QComboBox *> comboBoxes =
		parentWidget->findChildren<QComboBox *>();
	for (auto ch : comboBoxes) {
		ch->installEventFilter(new MouseWheelWidgetGuard(ch));
		ch->setFocusPolicy(Qt::StrongFocus);
	}

	QList<QDoubleSpinBox *> doubleSpinBoxes =
		parentWidget->findChildren<QDoubleSpinBox *>();
	for (auto ch : doubleSpinBoxes) {
		ch->installEventFilter(new MouseWheelWidgetGuard(ch));
		ch->setFocusPolicy(Qt::StrongFocus);
	}

	QList<QSpinBox *> spinBoxes = parentWidget->findChildren<QSpinBox *>();
	for (auto ch : spinBoxes) {
		ch->installEventFilter(new MouseWheelWidgetGuard(ch));
		ch->setFocusPolicy(Qt::StrongFocus);
	}

	QList<QLineEdit *> lineEdits =
		parentWidget->findChildren<QLineEdit *>();
	for (auto ch : lineEdits) {
		ch->installEventFilter(new MouseWheelWidgetGuard(ch));
		ch->setFocusPolicy(Qt::StrongFocus);
	}
}
