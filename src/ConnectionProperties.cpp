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

#include "ConnectionProperties.h"

ConnectionProperties::ConnectionProperties(websocketpp::connection_hdl client) :
	_client(),
	_authenticated(false),
	_volMeters(),
	_volMetersMutex(QMutex::Recursive)
{
}

ConnectionProperties::~ConnectionProperties()
{
	QMutexLocker locker(&_volMetersMutex);
	for (auto volMeter : _volMeters.values()) {
		obs_volmeter_destroy(volMeter);
	}
	_volMeters.clear();
}

websocketpp::connection_hdl ConnectionProperties::getClient()
{
	return _client;
}

bool ConnectionProperties::isAuthenticated()
{
    return _authenticated.load();
}

void ConnectionProperties::setAuthenticated(bool authenticated)
{
    _authenticated.store(authenticated);
}

AudioMeterInfo* ConnectionProperties::addVolMeter(obs_source_t* source)
{
	QMutexLocker locker(&_volMetersMutex);

	if (_volMeters.contains(source)) {
		return nullptr;
	}

	obs_volmeter_t* volMeter = obs_volmeter_create(OBS_FADER_CUBIC);
	obs_volmeter_attach_source(volMeter, source);
	_volMeters.insert(source, volMeter);
	return volMeter;
}

void ConnectionProperties::removeVolMeter(obs_source_t* source)
{
	AudioMeterInfo* meterInfo = _volMeters.take(source);
	if (meterInfo) {
		obs_volmeter_destroy(volMeter);
	}
}

AudioMeterInfo* ConnectionProperties::getVolMeter(obs_source_t* source)
{
	return _volMeters.value(source);
}
