/*
 * This file is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AP_CRSF_MAVLink.h"

#if AP_CRSF_MAVLINK_ENABLED

AP_CRSF_MAVLink_UART::AP_CRSF_MAVLink_UART()
{
}

size_t AP_CRSF_MAVLink_UART::_write(const uint8_t *buffer, size_t size)
{
	return _tx_buf.write(buffer, size);
}

ssize_t AP_CRSF_MAVLink_UART::_read(uint8_t *buffer, uint16_t count)
{
	return _rx_buf.read(buffer, count);
}

uint32_t AP_CRSF_MAVLink_UART::_available()
{
	return _rx_buf.available();
}

bool AP_CRSF_MAVLink_UART::_discard_input()
{
	_rx_buf.clear();
	return true;
}

uint32_t AP_CRSF_MAVLink_UART::push_rx(const uint8_t *buf, uint32_t len)
{
	return _rx_buf.write(buf, len);
}

uint32_t AP_CRSF_MAVLink_UART::pop_tx(uint8_t *buf, uint32_t max_len)
{
	return _tx_buf.read(buf, max_len);
}

#endif // AP_CRSF_MAVLINK_ENABLED
