/*
 * Copyright 2018 Analog Devices, Inc.
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

#ifndef OSC_IMPORT_SETTINGS_H
#define OSC_IMPORT_SETTINGS_H

#include "osc_export_settings.h"

namespace Ui {
class ExportSettings;
}

namespace adiscope {
class ImportSettings : public ExportSettings {
	Q_OBJECT

public:
	ImportSettings(QWidget *parent = 0);
	~ImportSettings();
};
} // namespace adiscope

#endif // OSC_IMPORT_SETTINGS_H
