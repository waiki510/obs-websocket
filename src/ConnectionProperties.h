/*
obs-websocket
Copyright (C) 2016-2019	Stéphane Lepin <stephane.lepin@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#pragma once

#include <atomic>
#include <obs-audio-controls.h>
#include <QtCore/QHash>
#include <QtCore/QMutex>
#include <websocketpp/server.hpp>

typedef struct {
	obs_volmeter_t* volMeter;
	obs_source_t* source;
	websocketpp::connection_hdl client;
} AudioMeterInfo;

class ConnectionProperties
{
public:
    explicit ConnectionProperties(websocketpp::connection_hdl client);
	~ConnectionProperties();

	bool isAuthenticated();
    void setAuthenticated(bool authenticated);

	websocketpp::connection_hdl getClient();

	AudioMeterInfo* addVolMeter(obs_source_t* source);
	void removeVolMeter(obs_source_t* source);
	AudioMeterInfo* getVolMeter(obs_source_t* source);

private:
	websocketpp::connection_hdl _client;
    std::atomic<bool> _authenticated;
	QHash<obs_source_t*, AudioMeterInfo*> _meters;
	QMutex _volMetersMutex;
};
