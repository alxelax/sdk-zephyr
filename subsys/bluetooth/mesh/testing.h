/**
 * @file testing.h
 * @brief Internal API for Bluetooth testing.
 */

/*
 * Copyright (c) 2017 Intel Corporation
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>

#include <zephyr/bluetooth/mesh.h>
#include <zephyr/bluetooth/mesh/access.h>
#include <zephyr/sys/slist.h>

/** @brief Bluetooth Testing callbacks structure.
 *
 *  Callback structure to be used for Bluetooth testing purposes.
 *  Allows access to Bluetooth stack internals, not exposed by public API.
 */
struct bt_mesh_test_cb {
	void (*net_recv)(uint8_t ttl, uint8_t ctl, uint16_t src, uint16_t dst, const void *payload,
			 size_t payload_len);
	void (*model_recv)(uint16_t src, uint16_t dst, const void *payload, size_t payload_len);
	void (*model_bound)(uint16_t addr, const struct bt_mesh_model *model, uint16_t key_idx);
	void (*model_unbound)(uint16_t addr, const struct bt_mesh_model *model, uint16_t key_idx);
	void (*prov_invalid_bearer)(uint8_t opcode);
	void (*trans_incomp_timer_exp)(void);

	sys_snode_t node;
};

/** Register callbacks for Bluetooth testing purposes
 *
 *  @param cb bt_mesh_test_cb callback structure
 *
 * @retval 0 Success.
 * @retval -EEXIST if @p cb was already registered.
 */
int bt_mesh_test_cb_register(struct bt_mesh_test_cb *cb);

/** Unregister callbacks for Bluetooth testing purposes
 *
 *  @param cb bt_mesh_test_cb callback structure
 */
void bt_mesh_test_cb_unregister(struct bt_mesh_test_cb *cb);

/** Send Friend Subscription List Add message.
 *
 *  Used by Low Power node to send the group address for which messages are to
 *  be stored by Friend node.
 *
 *  @param group Group address
 *
 *  @return Zero on success or (negative) error code otherwise.
 */
int bt_mesh_test_lpn_group_add(uint16_t group);

/** Send Friend Subscription List Remove message.
 *
 *  Used by Low Power node to remove the group addresses from Friend node
 *  subscription list. Messages sent to those addresses will not be stored
 *  by Friend node.
 *
 *  @param groups Group addresses
 *  @param groups_count Group addresses count
 *
 *  @return Zero on success or (negative) error code otherwise.
 */
int bt_mesh_test_lpn_group_remove(uint16_t *groups, size_t groups_count);

/** Clear replay protection list cache.
 *
 *  @return Zero on success or (negative) error code otherwise.
 */
int bt_mesh_test_rpl_clear(void);

void bt_mesh_test_net_recv(uint8_t ttl, uint8_t ctl, uint16_t src, uint16_t dst,
			   const void *payload, size_t payload_len);
void bt_mesh_test_model_recv(uint16_t src, uint16_t dst, const void *payload, size_t payload_len);
void bt_mesh_test_model_bound(uint16_t addr, const struct bt_mesh_model *model, uint16_t key_idx);
void bt_mesh_test_model_unbound(uint16_t addr, const struct bt_mesh_model *model, uint16_t key_idx);
void bt_mesh_test_prov_invalid_bearer(uint8_t opcode);
void bt_mesh_test_trans_incomp_timer_exp(void);

/** Pointer to override confirmation value sent by the provisioner during provisioning.
 *  When non-NULL, this value is sent instead of the computed confirmation.
 *  Must point to a buffer of at least bt_mesh_prov_auth_size_get() bytes.
 */
extern const uint8_t *bt_mesh_prov_test_confirm_val;

/** When true, the provisioner sends the confirmation PDU immediately after
 *  receiving the Capabilities PDU (out-of-sequence attack).
 */
extern bool bt_mesh_prov_test_send_confirm_on_caps;

/** When true, the provisioner injects a raw Confirmation PDU right after
 *  sending Start (before the public key exchange).  The provisionee expects
 *  PUB_KEY at that point and will reject it with PROV_ERR_UNEXP_PDU.
 */
extern bool bt_mesh_prov_test_send_confirm_on_start;

/** When true, the provisioner sends a second raw Confirmation PDU right after
 *  receiving the provisionee's Confirmation (instead of sending Random).
 *  The provisionee expects RANDOM at that point and will reject it with
 *  PROV_ERR_UNEXP_PDU.
 */
extern bool bt_mesh_prov_test_double_confirm;

/** When true, the provisioner injects a raw Confirmation PDU after the full
 *  Confirmation+Random exchange has completed successfully.  The provisionee
 *  expects Provisioning Data at that point and will reject it with
 *  PROV_ERR_UNEXP_PDU.
 */
extern bool bt_mesh_prov_test_send_confirm_on_data;
