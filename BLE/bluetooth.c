#include "bluetooth.h"
#include <string.h>

#include "nrf_sdm.h"
#include "ble.h"
#include "ble_gap.h"
#include "ble_gatts.h"
#include "ubit.h"
#include "CAN.h"

#define CUSTOM_UUID_BASE {{\
	0x06, 0x47, 0x6f, 0x24, 0x40, 0xe0, 0x9a, 0x8f, \
	0x78, 0x44, 0xc1, 0xbb, 0x42, 0x3c, 0xd3, 0xf3 \
}}

#define CUSTOM_UUID_SERVICE_UBIT 0xdead
#define CUSTOM_UUID_CHAR_MATRIX 0xbabe

extern uint8_t __data_start__;

static uint8_t m_matrix_attr_value = 0;
static uint8_t m_matrix_attr_value_prev = 0;

static struct 
{
	uint16_t conn_handle;
	uint16_t service_handle;
	ble_gatts_char_handles_t matrix_handles;
} m_service_ubit;

uint32_t bluetooth_init()
{
	uint32_t err_code = 0;

	err_code = sd_softdevice_enable(NULL, NULL);
	if (err_code)
	{
		return err_code;
	}

	static ble_enable_params_t ble_enable_params;
	memset(&ble_enable_params, 0, sizeof(ble_enable_params));
	uint32_t app_ram_base = (uint32_t)&__data_start__;

	ble_enable_params.gap_enable_params.periph_conn_count = 1;
	ble_enable_params.common_enable_params.vs_uuid_count = 1;

	err_code = sd_ble_enable(&ble_enable_params, &app_ram_base);
	return err_code;
}

uint32_t bluetooth_gap_advertise_start()
{
	uint32_t err_code = 0;

	static uint8_t adv_data[] = 
	{
		4, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME,
		'k', 'u', 'l', 
		3, BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE, 
		0x0D, 0x0F
	};
	uint8_t adv_data_length = 9;

	err_code = sd_ble_gap_adv_data_set(adv_data, adv_data_length, NULL, 0);
	if (err_code)
	{
		return err_code;
	}

	ble_gap_adv_params_t adv_params;
	memset(&adv_params, 0, sizeof(adv_params));

	adv_params.type = BLE_GAP_ADV_TYPE_ADV_IND;
	adv_params.interval = BLE_GAP_ADV_INTERVAL_MIN;

	err_code = sd_ble_gap_adv_start(&adv_params);

	(void)adv_data;
	(void)adv_data_length;

	return err_code;
}

uint32_t bluetooth_gatts_start()
{
	uint32_t err_code = 0;
	ble_uuid128_t base_uuid = CUSTOM_UUID_BASE;

	ble_uuid_t ubit_service_uuid;
	ubit_service_uuid.uuid = CUSTOM_UUID_SERVICE_UBIT;

	err_code = sd_ble_uuid_vs_add
	(
		&base_uuid,
		&ubit_service_uuid.type
	);
	
	if (err_code)
	{
		return err_code;
	}

	err_code = sd_ble_gatts_service_add(
		BLE_GATTS_SRVC_TYPE_PRIMARY,
		&ubit_service_uuid,
		&m_service_ubit.service_handle
	);

	if (err_code)
	{
		return err_code;
	}

	//Matrix
	ble_uuid_t matrix_uuid;
	matrix_uuid.uuid = CUSTOM_UUID_CHAR_MATRIX;

	err_code = sd_ble_uuid_vs_add(
		&base_uuid,
		&matrix_uuid.type
	);

	if (err_code)
	{
		return err_code;
	}

	static uint8_t matrix_char_desc[] = 
	{
		'L', 'E', 'D', ' ', 'M', 'a', 't', 'r', 'i', 'x'
	};

	ble_gatts_char_md_t matrix_char_md;
	memset(&matrix_char_md, 0, sizeof(matrix_char_md));
	matrix_char_md.char_props.read  = 1;
	matrix_char_md.char_props.write = 1;
	matrix_char_md.p_char_user_desc = matrix_char_desc;
	matrix_char_md.char_user_desc_max_size = 10;
	matrix_char_md.char_user_desc_size = 10;

	ble_gatts_attr_md_t matrix_attr_md;
	memset(&matrix_attr_md, 0, sizeof(matrix_attr_md));
	matrix_attr_md.read_perm.lv = 1;
	matrix_attr_md.read_perm.sm = 1;
	matrix_attr_md.write_perm.lv = 1;
	matrix_attr_md.write_perm.sm = 1;
	matrix_attr_md.vloc = BLE_GATTS_VLOC_USER;

	ble_gatts_attr_t matrix_attr;
	memset(&matrix_attr, 0, sizeof(matrix_attr));
	matrix_attr.p_uuid = &matrix_uuid;
	matrix_attr.p_attr_md = &matrix_attr_md;
	matrix_attr.init_len = 1;
	matrix_attr.max_len = 1;
	matrix_attr.p_value = &m_matrix_attr_value;

	err_code = sd_ble_gatts_characteristic_add(
		m_service_ubit.service_handle,
		&matrix_char_md,
		&matrix_attr,
		&m_service_ubit.matrix_handles
	);

	return err_code;
}

void bluetooth_serve_forever()
{
	uint8_t ble_event_buffer[100] = {0};
	uint16_t ble_event_buffer_size = 100;

	int i = 1;

	CAN_message m;
	
	while(1)
	{
		if (m_matrix_attr_value != m_matrix_attr_value_prev)
		{
			m_matrix_attr_value_prev = m_matrix_attr_value;
			m.id = BLUETOOTH_MSG;
			m.length = 1;
			m.data[0] = m_matrix_attr_value;
			
			CAN_send(&m);
			
			if (i)
			{
				ubit_led_matrix_turn_on();
				i = 0;
			}
			else
			{
				ubit_led_matrix_turn_off();
				i = 1;
			}
		}

		CAN_receive(&m);

		while (sd_ble_evt_get(ble_event_buffer, 
			        &ble_event_buffer_size) != NRF_ERROR_NOT_FOUND)
		{
			ble_evt_t * p_ble_event = (ble_evt_t *)ble_event_buffer;
			uint16_t event_id = p_ble_event->header.evt_id;

			switch (event_id)
			{
				case BLE_GAP_EVT_CONNECTED:
					m_service_ubit.conn_handle =
						p_ble_event->evt.gap_evt.conn_handle;

					sd_ble_gatts_sys_attr_set(
						m_service_ubit.conn_handle,
						0,
						0,
						0
					);
					break;

				case BLE_GAP_EVT_DISCONNECTED:
					m_service_ubit.conn_handle =
						BLE_CONN_HANDLE_INVALID;

					bluetooth_gap_advertise_start();
					break;

				default:
					break;
			}

			ble_event_buffer_size = 100;
		}
		ble_event_buffer_size = 100;


	}
	
}
