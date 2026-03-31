#!/usr/bin/env bash
# Copyright 2025 Nordic Semiconductor
# SPDX-License-Identifier: Apache-2.0

source $(dirname "${BASH_SOURCE[0]}")/../../_mesh_test.sh

# Tests for fake/out-of-sequence Confirmation PDU attacks at every stage of
# the provisioning state machine.  Each test pair verifies that the provisionee
# correctly rejects a PROV_CONFIRM frame when it is not expected, and that a
# subsequent valid provisioning attempt still succeeds.

# --- Stage: right after Capabilities (provisionee expects START) ---
RunTest mesh_prov_confirm_after_caps \
	prov_device_confirm_after_caps \
	prov_provisioner_confirm_after_caps

overlay=overlay_pst_conf
RunTestFlash mesh_prov_pst_confirm_after_caps \
	prov_device_confirm_after_caps -flash_erase \
	prov_provisioner_confirm_after_caps -flash_erase

# --- Stage: right after Start (provisionee expects PUB_KEY) ---
RunTest mesh_prov_confirm_after_start \
	prov_device_confirm_after_start \
	prov_provisioner_confirm_after_start

overlay=overlay_pst_conf
RunTestFlash mesh_prov_pst_confirm_after_start \
	prov_device_confirm_after_start -flash_erase \
	prov_provisioner_confirm_after_start -flash_erase

# --- Stage: second CONFIRM instead of Random (provisionee expects RANDOM) ---
RunTest mesh_prov_double_confirm \
	prov_device_double_confirm \
	prov_provisioner_double_confirm

overlay=overlay_pst_conf
RunTestFlash mesh_prov_pst_double_confirm \
	prov_device_double_confirm -flash_erase \
	prov_provisioner_double_confirm -flash_erase

# --- Stage: CONFIRM instead of Data (provisionee expects DATA) ---
RunTest mesh_prov_confirm_instead_of_data \
	prov_device_confirm_instead_of_data \
	prov_provisioner_confirm_instead_of_data

overlay=overlay_pst_conf
RunTestFlash mesh_prov_pst_confirm_instead_of_data \
	prov_device_confirm_instead_of_data -flash_erase \
	prov_provisioner_confirm_instead_of_data -flash_erase

# --- Invalid confirmation value (correct stage, wrong crypto) ---
RunTest mesh_prov_invalid_confirm \
	prov_device_invalid_confirm \
	prov_provisioner_invalid_confirm

overlay=overlay_pst_conf
RunTestFlash mesh_prov_pst_invalid_confirm \
	prov_device_invalid_confirm -flash_erase \
	prov_provisioner_invalid_confirm -flash_erase
