/*
 * This file is part of the PulseView project.
 *
 * Copyright (C) 2013 Joel Holdsworth <joel@airwebreathe.org.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef PULSEVIEW_PV_VIEW_ROWITEM_HPP
#define PULSEVIEW_PV_VIEW_ROWITEM_HPP

#include "viewitem.hpp"

namespace pv {
namespace view {

class RowItem : public ViewItem
{
	Q_OBJECT
	bool visible_=false;

public:

	bool isVisible();
	void visible(bool check);
	virtual void hover_point_changed();
};

} // namespace view
} // namespace pv

#endif // PULSEVIEW_PV_VIEW_ROWITEM_HPP
