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

#pragma once

#include "AP_RCTelemetry_config.h"

#if AP_CRSF_MAVLINK_ENABLED

#include <AP_HAL/UARTDriver.h>
#include <AP_HAL/utility/RingBuffer.h>

class AP_CRSF_MAVLink_UART : public AP_HAL::UARTDriver {
public:
	AP_CRSF_MAVLink_UART();

	bool is_initialized() override { return true; }
	bool tx_pending() override { return _tx_buf.available() > 0; }
	uint32_t txspace() override { return _tx_buf.space(); }
	uint32_t get_baud_rate() const override { return 57600; }

	// inject reassembled MAVLink data into RX buffer (called by AP_CRSF_Telem)
	uint32_t push_rx(const uint8_t *buf, uint32_t len);

	// read outgoing MAVLink data from TX buffer (called by AP_CRSF_Telem)
	uint32_t pop_tx(uint8_t *buf, uint32_t max_len);

protected:
	void _begin(uint32_t baud, uint16_t rxSpace, uint16_t txSpace) override {}
	void _end() override {}
	void _flush() override {}
	size_t _write(const uint8_t *buffer, size_t size) override;
	ssize_t _read(uint8_t *buffer, uint16_t count) override;
	uint32_t _available() override;
	bool _discard_input() override;

private:
	ByteBuffer _rx_buf{2048};
	ByteBuffer _tx_buf{2048};
};

#endif // AP_CRSF_MAVLINK_ENABLED
